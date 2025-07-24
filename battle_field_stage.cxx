#include "battle_field_stage.hxx"

const game::Vector& game::BattleFieldStage::dimensions() {
    return dimensions_;
}

const game::Vector& game::BattleFieldStage::origin() {
    return origin_;
}

game::BattleFieldStage::BattleFieldStage(const Vector& dimensions,
                                         const Vector& origin)
    : dimensions_(dimensions), origin_(origin) {
}

