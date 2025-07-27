#include <cmath>
#include <iostream>
#include <vector>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
const static double meps = numeric_limits<double>::epsilon();
const static double mmin = 1.0*numeric_limits<double>::min();
const static double minf = numeric_limits<double>::infinity();
const static double mnan = numeric_limits<double>::signaling_NaN();
const static double mqnan = numeric_limits<double>::quiet_NaN();

/// Declares an interface for representing an abstract
/// quadratic equation.
class QuadraticEquationI {
public:

    /// Creates a new instance of QuadraticEquationI
    QuadraticEquationI(){};

    /// Destroys the instance of QuadraticEquationI
    virtual ~QuadraticEquationI(){};

    /// Returns a vector with the roots of the quadratic equation
    /// given by coefficients a, b and c
    virtual vector<double> Solve (double a,
                                  double b,
                                  double c) = 0;
};

/// This class is used to create mock objects using the Google
/// mock framework
class QuadraticEquationMock : public QuadraticEquationI {
public:
    MOCK_METHOD(vector<double>, Solve, (double a, double b, double c));
};

/// The class implements a direct solution of a quadratic
/// equation.
class QuadraticEquationImpl : public QuadraticEquationI {

    /// Throws an exception when the specified
    /// double variable contains NaN
    inline void ThrowNan(const double& x,
                         const string msg = "NaN value was detected") {
        if (isnan(x)) {
            throw std::runtime_error(msg);
        }
    }

    /// Throws an exception when the specified
    /// double variable contains overflow value
    inline void ThrowOverflow(const double& x,
                              const string msg =
                                   "Overflow value was detected") {
        if (x == minf || x == -minf) {
            throw std::runtime_error(msg);
        }
    }

    /// Throws an exception when the specified
    /// double variable contains underflow value
    inline void ThrowUnderflow(const double& x,
                               const string msg =
                                   "Underflow value was detected") {
        
        if ((x > 0.0 && x <= mmin) ||
            (x < 0.0 && x >= -mmin)) {
            throw std::runtime_error(msg);
        }
    }

    /// Throws an exception when any of the specified
    /// double variables contain NaN
    inline void ThrowNan(const double& x1,
                         const double& x2,
                         const string msg =
                         "NaN value was detected") {
        ThrowNan(x1);
        ThrowNan(x2);
    }

    /// Throws an exception when any of the specified
    /// double variables contain overflow value
    inline void ThrowOverflow(const double& x1,
                              const double& x2,
                              const string msg =
                              "Overflow value was detected") {
        ThrowOverflow(x1);
        ThrowOverflow(x2);
    }

    /// Throws an exception when any of the specified
    /// double variables contain underflow value
    inline void ThrowUnderflow(const double& x1,
                               const double& x2,
                               const string msg =
                               "Underflow value was detected") {
        ThrowUnderflow(x1);
        ThrowUnderflow(x2);
    }

public:

    /// Creates a new instance of QuadraticEquationImpl
    QuadraticEquationImpl()
    : QuadraticEquationI(){}

    /// Returns roots of the equation given by coefficients a, b, c
    /// as a vector of 0 (no roots), 1 (1 root) or 2 components (2 roots).
    /// In order to reduce the number of
    /// considered regions of the coefficint's space, the equation is
    /// normalized by the coefficient a.
    vector<double> Solve (double a,
                          double b, double c) override final {
        ThrowNan(a);
        ThrowNan(b);
        ThrowNan(c);

        double hatb, hatc;
        hatb = b / a;
        hatc = c / a;

        ThrowNan(hatb, hatc);
        ThrowOverflow(hatb, hatc);
        ThrowUnderflow(hatb, hatc);

        double hatb_sqr, m_hatc4, D;
        hatb_sqr = hatb*hatb;
        m_hatc4 = -hatc * 4.0;
        ThrowOverflow(hatb_sqr, m_hatc4);
        D = hatb_sqr + m_hatc4;
        ThrowOverflow(D);
        if (1.0 + hatb_sqr == 1.0 &&
            1.0 + m_hatc4  == 1.0) { //both coeffs -> 0
            return vector<double>{0.0};
        }
        if (D != hatb_sqr && D == m_hatc4) { // b -> 0
            if (m_hatc4 < 0.0) {
                return vector<double>{};
            }
            return vector<double>{sqrt(-hatc), -sqrt(-hatc)};
        }
        if (1.0 + hatc / hatb == 1) { // c -> 0
            return vector<double>{0.0, -hatb};
        }

        const double k = 0.5; // any coeff less or equal than 0.5
                              // ensures that the result computed
                              // with machine epsilon error
                              // is absorbed by 1.0
        const double left = abs(1.0 + (m_hatc4 / hatb_sqr))*k + 1.0;
        const double right= 1.0;
        if (left == right) { // only one root (D = 0)
            return vector<double>{-hatb / 2.0};
        }
        if (D < 0.0) { // D is negative and outside of the
                       // region where it's constitutents
                       // are indistinguishable
            return vector<double>{};
        }
        // now only 2 cases left:
        // 1) degenerated when a -> 0
        // 2) normal with 2 roots
        // degenerated case is when the any of the root
        // lies near the linear equation root x3
        double x1, x2;
        double x3, x3l, x3r;
        double yl,yr;
        x3 = -hatc / hatb;
        ThrowOverflow(x3);

        // the actual position of x3l and x3r doesn't
        // matter, since only the sign is interesting
        x3l = (1.0 - meps)*x3; //actually this constant is smaller
        x3r = (1.0 + meps)*x3;
        yl = x3l*x3l + hatb*x3l + hatc;
        yr = x3r*x3r + hatb*x3r + hatc;
        if (signbit(yl) ^ signbit(yr)) {
            // Actually, we can use Newton's iteration
            // to find an actual root starting from
            // the approximation obtained using linear
            // equation
            // But for now we use linear equation + Vieta
            // theorem:
            x1 = x3;
            x2 = hatc / x1;
            return vector<double>{x1,x2};
        }

        x1 = (-hatb + sqrt(D))*0.5;
        x2 = (-hatb - sqrt(D))*0.5;

        ThrowOverflow(x1, x2);
        return vector<double>{x1,x2};
    }
};

/// A minimal class to run Google tests
class QuadraticEquationTest : public ::testing::Test {
protected:

    /// The method is called everytime when a test starts
    virtual void SetUp() {};

    /// The method is called everytime when a test finishes
    virtual void TearDown() {};
};

/// Checks that when a = 1, b = 0 and c = 1 roots are not returned
/// which corresponds to the next equation: x^2 + 1 = 0. The test
/// is conducted using a mock object.
TEST(QuadraticEquationTest, Test_Item_3) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, Solve(1.0, 0.0, 1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{}));
    
    EXPECT_EQ(qemock.Solve(1.0, 0.0, 1.0).size(), 0);
}

/// Checks that when a = 1, b = 0 and c = 1 roots are not returned
/// which corresponds to the next equation: x^2 + 1 = 0. The test
/// includes a minimal implementation of the Solve function.
TEST(QuadraticEquationTest, Test_Item_4) {
    QuadraticEquationImpl qeimpl{};
    EXPECT_EQ(qeimpl.Solve(1.0, 0.0, 1.0).size(), 0);
    EXPECT_NE(qeimpl.Solve(1.0, 0.0, -1.0).size(), 0);
}

/// Checks if a = 1, b = 0 and c = -1, then there are roots x = 1
/// and x = -1 which correspond to the next equation: x^2 - 1 = 0.
// The test is conducted using a mock object.
TEST(QuadraticEquationTest, Test_Item_5) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, Solve(1.0, 0.0, -1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{1.0, 1.0}));
    
    EXPECT_EQ(qemock.Solve(1.0, 0.0, -1.0), (vector<double>{1.0, 1.0}));
}

/// Checks if a = 1, b = 0 and c = -1, then there are roots x = 1
/// and x = -1 which corresponds to the next equation: x^2 - 1 = 0.
/// The test
/// includes a minimal implementation of the Solve function.
TEST(QuadraticEquationTest, Test_Item_6) {
    QuadraticEquationImpl qeimpl{};
    EXPECT_EQ(qeimpl.Solve(1.0, 0.0, -1.0).size(), 2);
    EXPECT_EQ(qeimpl.Solve(1.0, 0.0, -1.0), (std::vector<double>{1.0, -1.0}));
}

/// Checks if a = 1, b = 2 and c = 1, then there is a root x = -1
/// which correspond to the next equation: x^2 + 2x + 1 = 0.
// The test is conducted using a mock object.
TEST(QuadraticEquationTest, Test_Item_7) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, Solve(1.0, 2.0, 1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{-1.0}));
    
    EXPECT_EQ(qemock.Solve(1.0, 2.0, 1.0), (vector<double>{-1.0}));
}

/// Checks if a = 1, b = 2 and c = 1, then there is a root x = -1
/// which corresponds to the next equation: x^2 + 2x + 1 = 0.
/// The test
/// includes a minimal implementation of the Solve function.
TEST(QuadraticEquationTest, Test_Item_8) {
    QuadraticEquationImpl qeimpl{};
    EXPECT_EQ(qeimpl.Solve(1.0, 2.0, 1.0).size(), 1);
    EXPECT_EQ(qeimpl.Solve(1.0, 2.0, 1.0), (std::vector<double>{-1.0}));
}

/// Checks that 'a' is not equal to 0.
/// In this case we have a degenerated case when
/// the expression for roots is divided by zero.
TEST(QuadraticEquationTest, Test_Item_9) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, Solve(mmin, 2.0, 1.0))
        .Times(1)
        .WillOnce(testing::Throw(std::runtime_error("a equals to 0")));
    
    EXPECT_THROW(qemock.Solve(mmin, 2.0, 1.0), std::runtime_error);
}

/// Checks that 'a' is not equal to 0.
/// Also the case when a -> 0 (i.e., the function -> linear)
/// in this case the solution is obtained from the linear
/// approximation and Vieta's theorem
TEST(QuadraticEquationTest, Test_Item_10) {
    QuadraticEquationImpl qeimpl{};
    EXPECT_EQ(qeimpl.Solve(1.0, 2.0, 1.0).size(), 1);
    EXPECT_THROW(qeimpl.Solve(0.0, 2.0, 1.0), std::runtime_error);
    EXPECT_THROW(qeimpl.Solve(mmin, 20.0, 10.0), std::runtime_error);
    /// not a strict check, but should work for most cases
    const double tol = 10.0*meps;
    EXPECT_TRUE(abs(
        qeimpl.Solve(1.0e-18, 1.0, -3.0)[0]-3.0) <= tol);
    EXPECT_TRUE(abs(
        qeimpl.Solve(1.0e-18, 10.0, -4.0)[0]-0.4) <= tol);
}

/// Checks for cases: 1) b = 0, 2) c = 0, 3) b = 0, c = 0
TEST(QuadraticEquationTest, Test_Item_10_other) {
    QuadraticEquationImpl qeimpl{};
    // Case 1:
    EXPECT_EQ(qeimpl.Solve(1.0, 0.0, -0.25).size(), 2);
    EXPECT_EQ(qeimpl.Solve(1.0, 0.0, -0.25),
              (vector<double>{0.5,-0.5}));
    // Case 2:
    EXPECT_EQ(qeimpl.Solve(1.0, 2.0, 0.0).size(), 2);
    EXPECT_EQ(qeimpl.Solve(1.0, 2.0, 0.0),
              (vector<double>{0.0,-2.0}));
    // Case 3:
    // trivial
    EXPECT_EQ(qeimpl.Solve(1.0, 0.0, 0.0).size(), 1);
    EXPECT_EQ(qeimpl.Solve(1.0, 0.0, 0.0),
              (vector<double>{0.0}));
    // less trivial
    EXPECT_EQ(qeimpl.Solve(1.0, meps*0.5, -meps*0.1).size(), 1);
    EXPECT_EQ(qeimpl.Solve(1.0, meps*0.5, -meps*0.1),
              (vector<double>{0.0}));
}

/// Checks the case when D is almost 0, but is
/// still treated as 0
TEST(QuadraticEquationTest, Test_Item_11) {
    QuadraticEquationImpl qeimpl{};
    {
        const double a = 1.0;
        const double b = 0.17;
        const double c = 0.007225;
        const double D = b*b - 4*a*c;
        EXPECT_TRUE (abs(D) > 0.0);
        EXPECT_EQ(qeimpl.Solve(a, b, c).size(), 1);
    }
    {
        const double a = 1.0;
        const double b = 0.4;
        const double c = 0.04;
        const double D = b*b - 4*a*c;
        EXPECT_TRUE (abs(D) > 0.0);
        EXPECT_EQ(qeimpl.Solve(a, b, c).size(), 1);
    }
}

/// Checks the case when NaN, inf or DBL_MIN
/// are supplied as a, b, c coefficients or
/// appear after normalization
TEST(QuadraticEquationTest, Test_Item_12) {
    QuadraticEquationImpl qeimpl{};
    EXPECT_THROW(qeimpl.Solve(0.0, 2.0, 0.0), std::runtime_error);
    EXPECT_THROW(qeimpl.Solve(1.0, 2.0, mqnan), std::runtime_error);
    EXPECT_THROW(qeimpl.Solve(1.0, 2.0, minf), std::runtime_error);
    EXPECT_THROW(qeimpl.Solve(1.0, 2.0, minf), std::runtime_error);
    EXPECT_THROW(qeimpl.Solve(10.0, 2.0, mmin), std::runtime_error);
}

int main (int argc, char * argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

// sudo apt-get -y install libgmock-dev
//END-OF-FILE
//

