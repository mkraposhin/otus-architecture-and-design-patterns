#ifndef BattleFieldObject_HXX
#define BattleFieldObject_HXX

#include <unordered_map>
#include <string>
#include "space_battle.hxx"

namespace game {

class BattleFieldStage;

/// Represents an object located in the battle field
class BattleFieldObject {

private:

    /// Forbids the default ctor
    BattleFieldObject() = delete;

    /// Forbids the copy ctor
    BattleFieldObject(const BattleFieldObject&) = delete;

    /// Forbids the move ctor
    BattleFieldObject(BattleFieldObject&&) = delete;

public:

    /// Creates a new instance of BattleFieldObject using
    /// a constant reference to the object describing the
    /// battle field stage (BattleFieldStage).
    BattleFieldObject (const BattleFieldStage& bfs);

    /// Returns value of a property with the given name
    Vector get_property(const std::string& name) const;

    /// Returns the value of a property with the given name
    void set_property(const std::string& name, const Vector &v);

    /// Associates a property (the property's name) with the
    /// object
    void new_property(const std::string& name);

private:

    /// A constant reference to the object holding information
    /// about a battle field stage
    const BattleFieldStage& bfs_;

    /// A list of a BattleFieldObject properties
    std::unordered_map<std::string, Vector> properties_;

};
}

#endif

