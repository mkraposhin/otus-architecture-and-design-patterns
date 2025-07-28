#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "space_battle.hxx"
#include "battle_field_stage.hxx"
#include "battle_field_object.hxx"
#include "translating_object.hxx"
#include "translating_object_adapter.hxx"
#include "object_translation.hxx"
#include "rotating_object.hxx"
#include "rotating_object_adapter.hxx"
#include "object_rotation.hxx"
#include "exception_property_not_found.hxx"
#include "exception_cant_read_property.hxx"
#include "exception_cant_write_property.hxx"

using namespace std;
using namespace game;

/// A minimal class to run Google tests for an object
/// translation and rotatation
class ObjectMotionTest : public ::testing::Test {
protected:

    /// The method is called everytime when a test starts
    virtual void SetUp() {
        stage_origin_ = Vector{0.0, 0.0};
        stage_dimensions_ = Vector{20.0, 20.0};
    };

    /// The method is called everytime when a test finishes
    virtual void TearDown() {

    };

    Vector stage_origin_;
    Vector stage_dimensions_;
};

/// This tests that an object can be translated by a given vector
TEST_F(ObjectMotionTest, Item_7_3a) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);

    obj1.new_property("position");
    obj1.new_property("displacement");

    TranslatingObjectAdapter adapter1 (obj1);

    EXPECT_EQ(adapter1.position(), (Vector{0,0}));
    EXPECT_EQ(adapter1.displacement(), (Vector{0,0}));

    adapter1.position(Vector{12,5});
    adapter1.displacement(Vector{-7,3});

    EXPECT_EQ(adapter1.position(), (Vector{12,5}));
    EXPECT_EQ(adapter1.displacement(), (Vector{-7,3}));

    TranslatingObject &interface1 = adapter1;
    EXPECT_EQ(interface1.position(), (Vector{12,5}));
    EXPECT_EQ(interface1.displacement(), (Vector{-7,3}));
    ObjectTranslation translation1(interface1);
    translation1.Execute();
    EXPECT_EQ(interface1.position(), (Vector{5,8}));
}

/// This tests if reading of unavailable property (position)
/// raises an exception
TEST_F(ObjectMotionTest, Item_7_3b) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);
    TranslatingObjectAdapter adapter1 (obj1);
    obj1.new_property("displacement");

    EXPECT_THROW(adapter1.position(),
                 ExceptionPropertyNotFound);

    ObjectTranslation translation1(adapter1);    
    EXPECT_THROW(translation1.Execute(),
                 ExceptionCantReadProperty);
}

/// This tests if reading of unavailable property (displacement)
/// raises an exception
TEST_F(ObjectMotionTest, Item_7_3c) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);
    TranslatingObjectAdapter adapter1 (obj1);
    obj1.new_property("position");

    EXPECT_THROW(adapter1.displacement(),
                 ExceptionPropertyNotFound);

    ObjectTranslation translation1(adapter1);    
    EXPECT_THROW(translation1.Execute(),
                 ExceptionCantReadProperty);
}

/// This tests if writing to unavailable property (position)
/// raises an exception
TEST_F(ObjectMotionTest, Item_7_3d) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);
    class TranslatingObjectAdapterMock : public TranslatingObject {
    public:
        TranslatingObjectAdapterMock(BattleFieldObject& bfo){};
        Vector position() const override final {
            return Vector{0.0,0.0};
        }

        void position(const Vector& v) override final {
            throw ExceptionPropertyNotFound{"position"};
            return;
        }

        Vector displacement() const override final {
            return Vector{0.0,0.0};
        }
    };
    TranslatingObjectAdapterMock adapter1 (obj1);
    obj1.new_property("position");

    EXPECT_THROW(adapter1.position(Vector{0.0, 0.0}),
                 ExceptionPropertyNotFound);

    ObjectTranslation translation1(adapter1);    
    EXPECT_THROW(translation1.Execute(),
                 ExceptionCantWriteProperty);
}

/// This tests that an object can be rotated by a given angle
TEST_F(ObjectMotionTest, Item_11a) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);

    obj1.new_property("angle");
    obj1.new_property("angle_increment");

    RotatingObjectAdapter adapter1 (obj1);

    EXPECT_EQ(adapter1.angle(), 0.0);
    EXPECT_EQ(adapter1.angle_increment(), 0.0);

    adapter1.angle(45.0);
    adapter1.angle_increment(90.0);

    EXPECT_EQ(adapter1.angle(), 45.0);
    EXPECT_EQ(adapter1.angle_increment(), 90.0);

    RotatingObject &interface1 = adapter1;
    EXPECT_EQ(interface1.angle(), 45.0);
    EXPECT_EQ(interface1.angle_increment(), 90.0);
    ObjectRotation rotation1(interface1);
    rotation1.Execute();
    EXPECT_EQ(interface1.angle(), 135.0);
}

/// This tests if reading of unavailable property (angle)
/// raises an exception
TEST_F(ObjectMotionTest, Item_11b) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);
    RotatingObjectAdapter adapter1 (obj1);
    obj1.new_property("angle_increment");

    EXPECT_THROW(adapter1.angle(),
                 ExceptionPropertyNotFound);

    ObjectRotation rotation1(adapter1);    
    EXPECT_THROW(rotation1.Execute(),
                 ExceptionCantReadProperty);
}

/// This tests if reading of unavailable property (position)
/// raises an exception
TEST_F(ObjectMotionTest, Item_11c) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);
    RotatingObjectAdapter adapter1 (obj1);
    obj1.new_property("angle");

    EXPECT_THROW(adapter1.angle_increment(),
                 ExceptionPropertyNotFound);

    ObjectRotation rotation1(adapter1);    
    EXPECT_THROW(rotation1.Execute(),
                 ExceptionCantReadProperty);
}

/// This tests if reading of unavailable property (displacement)
/// raises an exception
TEST_F(ObjectMotionTest, Item_11d) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);
    TranslatingObjectAdapter adapter1 (obj1);
    obj1.new_property("position");

    EXPECT_THROW(adapter1.displacement(),
                 ExceptionPropertyNotFound);

    ObjectTranslation rotation1(adapter1);    
    EXPECT_THROW(rotation1.Execute(),
                 ExceptionCantReadProperty);
}

/// This tests if writing to unavailable property (position)
/// raises an exception
TEST_F(ObjectMotionTest, Item_11e) {
    BattleFieldStage stage (this->stage_origin_, stage_dimensions_);
    BattleFieldObject obj1 (stage);
    class RotatingObjectAdapterMock : public RotatingObject {
    public:
        RotatingObjectAdapterMock(BattleFieldObject& bfo){};
        const Vector orientation() const override final {
            return Vector{0.0,0.0};
        }
        double angle() const override final {
            return 0.0;
        }
        void angle(double v) override final {
            throw ExceptionPropertyNotFound{"angle"};
            return;
        }
        double angle_increment() const override final {
            return 0.0;
        }
    };
    RotatingObjectAdapterMock adapter1 (obj1);
    obj1.new_property("angle");

    EXPECT_THROW(adapter1.angle(0.0),
                 ExceptionPropertyNotFound);

    ObjectRotation rotation1(adapter1);    
    EXPECT_THROW(rotation1.Execute(),
                 ExceptionCantWriteProperty);
}

int main (int argc, char * argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

//
//END-OF-FILE
//