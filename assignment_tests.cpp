#include <iostream>
#include <vector>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace std;

/// Declares an interface for representing a quadratic equation
class QuadraticEquationI {
public:

    /// Creates a new instance of QuadraticEquationI
    QuadraticEquationI(){};

    /// Destroys the instance of QuadraticEquationI
    virtual ~QuadraticEquationI(){};

    /// Returns a vector with the roots of the quadratic equation
    /// given by coefficients a, b and c
    virtual vector<double> roots (double a,
        double b,
        double c) = 0;
};

/// This class is used to create mock objects using the Google
/// mock framework
class QuadraticEquationMock : public QuadraticEquationI {
public:
    MOCK_METHOD(vector<double>, roots, (double a, double b, double c));
};

/// The class containing sequential approximations to
/// "roots" functions for the computation of a quadratic
/// equation's solution.
template <typename RImpl>
class QuadraticEquationImpl : public QuadraticEquationI {
private:

    /// Forbid the default ctor
    QuadraticEquationImpl() = delete;

     /// An instance of the function to compute a quadratic
     /// equation's roots
     RImpl roots_impl_;

public:

    /// Creates new instance of QuadraticEquationImpl and sets
    /// the roots function implementation
    QuadraticEquationImpl(RImpl r)
    : QuadraticEquationI(), roots_impl_(r){}

    /// Returns roots computed by the current implementation of
    /// root's finding function
    vector<double> roots (double a,
        double b, double c) override final {
            return roots_impl_(a, b, c);
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
    EXPECT_CALL(qemock, roots(1.0, 0.0, 1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{}));
    
    EXPECT_EQ(qemock.roots(1.0, 0.0, 1.0).size(), 0);
}

/// Checks that when a = 1, b = 0 and c = 1 roots are not returned
/// which corresponds to the next equation: x^2 + 1 = 0. The test
/// includes a minimal implementation of the roots function.
TEST(QuadraticEquationTest, Test_Item_4) {
    auto root_impl = [](double a, double b, double c){
        double D = b*b - 4.0*a*c;
        if (D < 0.0) {
            return vector<double>{};
        }
        return vector<double>{0.0, 0.0};
    };
    QuadraticEquationImpl qeimpl(root_impl);
    EXPECT_EQ(qeimpl.roots(1.0, 0.0, 1.0).size(), 0);
    EXPECT_NE(qeimpl.roots(1.0, 0.0, -1.0).size(), 0);
}

/// Checks if a = 1, b = 0 and c = -1, then there is a root x = 1,
/// which corresponds to the next equation: x^2 -1 1 = 0. The test
/// is conducted using a mock object.
TEST(QuadraticEquationTest, Test_Item_5) {
    QuadraticEquationMock qemock;
    EXPECT_CALL(qemock, roots(1.0, 0.0, -1.0))
        .Times(1)
        .WillOnce(testing::Return(vector<double>{1.0, 1.0}));
    
    EXPECT_EQ(qemock.roots(1.0, 0.0, -1.0), (vector<double>{1.0, 1.0}));
}

/// Checks if a = 1, b = 0 and c = -1, then there is a root x = 1,
/// which corresponds to the next equation: x^2 -1 1 = 0. The test
/// includes a minimal implementation of the roots function.
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
    EXPECT_EQ(qeimpl.roots(1.0, 0.0, -1.0).size(), 2);
    EXPECT_EQ(qeimpl.roots(1.0, 0.0, -1.0), (std::vector<double>{1.0, -1.0}));
}

int main (int argc, char * argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

// sudo apt-get -y install libgmock-dev
//END-OF-FILE
//

