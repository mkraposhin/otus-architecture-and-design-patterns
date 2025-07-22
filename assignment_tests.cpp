#include <cmath>
#include <iostream>
#include <vector>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;
const static double meps = numeric_limits<double>::epsilon();
const static double mind = 2.0*numeric_limits<double>::min();

/// Declares an interface for representing a quadratic equation
class QuadraticEquationI {
public:

    /// Creates a new instance of QuadraticEquationI
    QuadraticEquationI(){};

    /// Destroys the instance of QuadraticEquationI
    virtual ~QuadraticEquationI(){};

    /// Returns a vector with the roots of the quadratic equation
    /// given by coefficients a, b and c
    virtual vector<double> solve (double a,
        double b,
        double c) = 0;
};

/// This class is used to create mock objects using the Google
/// mock framework
class QuadraticEquationMock : public QuadraticEquationI {
public:
    MOCK_METHOD(vector<double>, solve, (double a, double b, double c));
};

/// The class containing sequential approximations to
/// "solve" functions for the computation of a quadratic
/// equation's solution.
template <typename RImpl>
class QuadraticEquationImpl : public QuadraticEquationI {
private:

    /// Forbid the default ctor
    QuadraticEquationImpl() = delete;

     /// An instance of the function to compute a quadratic
     /// equation's roots
     RImpl solve_impl_;

public:

    /// Creates new instance of QuadraticEquationImpl and sets
    /// the solve function implementation
    QuadraticEquationImpl(RImpl r)
    : QuadraticEquationI(), solve_impl_(r){}

    /// Returns solve computed by the current implementation of
    /// root's finding function
    vector<double> solve (double a,
        double b, double c) override final {
            return solve_impl_(a, b, c);
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
    EXPECT_CALL(qemock, solve(1.0, 0.0, 1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{}));
    
    EXPECT_EQ(qemock.solve(1.0, 0.0, 1.0).size(), 0);
}

/// Checks that when a = 1, b = 0 and c = 1 roots are not returned
/// which corresponds to the next equation: x^2 + 1 = 0. The test
/// includes a minimal implementation of the solve function.
TEST(QuadraticEquationTest, Test_Item_4) {
    auto root_impl = [](double a, double b, double c){
        double D = b*b - 4.0*a*c;
        if (D < 0.0) {
            return vector<double>{};
        }
        return vector<double>{0.0, 0.0};
    };
    QuadraticEquationImpl qeimpl(root_impl);
    EXPECT_EQ(qeimpl.solve(1.0, 0.0, 1.0).size(), 0);
    EXPECT_NE(qeimpl.solve(1.0, 0.0, -1.0).size(), 0);
}

/// Checks if a = 1, b = 0 and c = -1, then there are roots x = 1
/// and x = -1 which correspond to the next equation: x^2 - 1 = 0.
// The test is conducted using a mock object.
TEST(QuadraticEquationTest, Test_Item_5) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, solve(1.0, 0.0, -1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{1.0, 1.0}));
    
    EXPECT_EQ(qemock.solve(1.0, 0.0, -1.0), (vector<double>{1.0, 1.0}));
}

/// Checks if a = 1, b = 0 and c = -1, then there are roots x = 1
/// and x = -1 which corresponds to the next equation: x^2 - 1 = 0.
/// The test
/// includes a minimal implementation of the solve function.
TEST(QuadraticEquationTest, Test_Item_6) {
    auto root_impl = [](double a, double b, double c){
        double D = b*b - 4.0*a*c;
        if (D < 0.0) {
            return vector<double>{};
        }
        if (D > 0.0) {
            return vector<double>{
                (-b + sqrt(D) / 2.0 / a),
                (-b - sqrt(D) / 2.0 / a),
            };
        }
        return vector<double>{0.0};
    };
    QuadraticEquationImpl qeimpl(root_impl);
    EXPECT_EQ(qeimpl.solve(1.0, 0.0, -1.0).size(), 2);
    EXPECT_EQ(qeimpl.solve(1.0, 0.0, -1.0), (std::vector<double>{1.0, -1.0}));
}

/// Checks if a = 1, b = 2 and c = 1, then there is a root x = -1
/// which correspond to the next equation: x^2 + 2x + 1 = 0.
// The test is conducted using a mock object.
TEST(QuadraticEquationTest, Test_Item_7) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, solve(1.0, 2.0, 1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{-1.0}));
    
    EXPECT_EQ(qemock.solve(1.0, 2.0, 1.0), (vector<double>{-1.0}));
}

/// Checks if a = 1, b = 2 and c = 1, then there is a root x = -1
/// which corresponds to the next equation: x^2 - 1 = 0.
/// The test
/// includes a minimal implementation of the solve function.
TEST(QuadraticEquationTest, Test_Item_8) {
    auto root_impl = [](double a, double b, double c){
        double D = b*b - 4.0*a*c;
        if (D < 0.0) {
            return vector<double>{};
        }
        if (D > 0.0) {
            return vector<double>{
                (-b + sqrt(D) / 2.0 / a),
                (-b - sqrt(D) / 2.0 / a),
            };
        }
        return vector<double>{-b / 2.0 / a};
    };
    QuadraticEquationImpl qeimpl(root_impl);
    EXPECT_EQ(qeimpl.solve(1.0, 2.0, 1.0).size(), 1);
    EXPECT_EQ(qeimpl.solve(1.0, 2.0, 1.0), (std::vector<double>{-1.0}));
}

/// Checks that 'a' is not equal to 0.
/// In this case we have a degenerated case when
/// the expression for roots is divided by zero.
TEST(QuadraticEquationTest, Test_Item_9) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, solve(mind, 2.0, 1.0))
        .Times(1)
        .WillOnce(testing::Throw(std::runtime_error("a equals to 0")));
    
    EXPECT_THROW(qemock.solve(mind, 2.0, 1.0), std::runtime_error);
}

///
///
///
TEST(QuadraticEquationTest, Test_Item_10) {
    auto root_impl = [](double a, double b, double c){
        if (abs(a) <= mind) {
            throw std::runtime_error("a equals to 0");
            return vector<double>{};
        }
        double D = b*b - 4.0*a*c;
        if (D < 0.0) {
            return vector<double>{};
        }
        if (D > 0.0) {
            return vector<double>{
                (-b + sqrt(D) / 2.0 / a),
                (-b - sqrt(D) / 2.0 / a),
            };
        }
        return vector<double>{-b / 2.0 / a};
    };
    QuadraticEquationImpl qeimpl(root_impl);
    EXPECT_EQ(qeimpl.solve(1.0, 2.0, 1.0).size(), 1);
    EXPECT_THROW(qeimpl.solve(0.0, 2.0, 1.0), std::runtime_error);
    EXPECT_THROW(qeimpl.solve(mind, 2.0, 1.0), std::runtime_error);
    vector v = qeimpl.solve(1.0e-6, 0.0, -1.0);
    std::cout << v[0] << "," << v[1] << std::endl;
}

int main (int argc, char * argv[])
{
    testing::InitGoogleMock(&argc, argv);

    std::cout << meps << std::endl;
    std::cout << bool((1.0 + meps*double(1.0)) == double(1.0)) << std::endl;
    std::cout << bool((1.0 + meps*double(0.5)) == double(1.0)) << std::endl;
    std::cout << bool((1.0 + meps*double(2.0)) == double(1.0)) << std::endl;

    return RUN_ALL_TESTS();
}

// sudo apt-get -y install libgmock-dev
//END-OF-FILE
//

