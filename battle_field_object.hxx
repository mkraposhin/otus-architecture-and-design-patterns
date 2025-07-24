#ifndef BattleFieldObject_HXX
#define BattleFieldObject_HXX

#include <unordered_map>
#include <string>
#include "space_battle.hxx"

namespace game {

class BattleFieldStage;

/// Represents all objects located in the battle field
class BattleFieldObject {

private:

    BattleFieldObject() = delete;

    BattleFieldObject(const BattleFieldObject&) = delete;

    BattleFieldObject(BattleFieldObject&&) = delete;

public:

    BattleFieldObject (const BattleFieldStage& bfs);

    Vector get_property(const std::string& name) const;

    void set_property(const std::string& name, const Vector &v);

    void new_property(const std::string& name);

private:

    const BattleFieldStage& bfs_;

    /// A list of a BattleFieldObject properties
    std::unordered_map<std::string, Vector> properties_;

};
}

#endif

