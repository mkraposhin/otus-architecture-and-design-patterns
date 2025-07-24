#include "battle_field_object.hxx"
#include "exception_property_not_found.hxx"

game::BattleFieldObject::BattleFieldObject(
    const BattleFieldStage& bfs)
    : bfs_(bfs) {
}

game::Vector game::BattleFieldObject::get_property(
    const std::string& name) const {
    if (properties_.count(name)) {
        return properties_.at(name);
    }
    throw ExceptionPropertyNotFound(name);
    return Vector{};
}

void game::BattleFieldObject::set_property(
    const std::string &name, const Vector &v) {
    if (properties_.count(name)) {
        properties_[name] = v;
        return;
    }
    throw ExceptionPropertyNotFound(name);
}

void game::BattleFieldObject::new_property(
    const std::string &name) {
    properties_[name] = Vector{};
}

//
//
//
