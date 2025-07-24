#ifndef BattleFieldStage_HXX
#define BattleFieldStage_HXX

#include "space_battle.hxx"

namespace game {

/// Describes the geometry of a battle field
class BattleFieldStage {

private:

    /// Forbid default ctor
    BattleFieldStage() = delete;

public:

    /// Gives constant access to the dimensions of the stage
    const Vector& dimensions();

    /// Gives the origin vector of the stage
    const Vector& origin();

    /// Creates a new instance of BattleFieldStage
    BattleFieldStage(const Vector& dimensions, const Vector& origin);

private:

    /// The dimensions of the stage
    Vector dimensions_;

    /// The origin coordinates of the stage
    Vector origin_;

};

}

#endif

