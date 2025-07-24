#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "space_battle.hxx"
#include "battle_field_stage.hxx"
#include "battle_field_object.hxx"
#include "translating_object.hxx"
#include "translating_object_adapter.hxx"
#include "object_translation.hxx"

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

int main (int argc, char * argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

//
//END-OF-FILE
//