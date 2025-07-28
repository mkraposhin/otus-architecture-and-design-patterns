#ifndef RotatingObjectAdapter_HXX
#define RotatingObjectAdapter_HXX

#include <cmath>
#include "rotating_object.hxx"

namespace game {

/// A mediator class responsible for retrieving parameters
/// of rotation of an object in a battle field
class RotatingObjectAdapter : public RotatingObject {

    /// A reference to the rotated object
    BattleFieldObject& bfo_;

    /// A constant reference to the rotated object
    const BattleFieldObject& cbfo_;


public:

    /// Creates a new instance of the mediator using a
    /// reference to the given translated object
    RotatingObjectAdapter(BattleFieldObject& bfo)
    : bfo_(bfo), cbfo_(bfo) {
    }

    /// Returns the current orientation (in local coordinates)
    /// of the object
    virtual const Vector orientation() const override final {
        double c_angle = angle();
        double c_angle_rad = std::acos(-1.0) * c_angle / 180.0;
        return Vector{std::cos(c_angle_rad), std::sin(c_angle_rad)};
    }

    /// Returns the current orientation angle of the object
    virtual double angle() const override final {
        return cbfo_.get_property("angle")[0];
    }

    /// Sets a new orientation angle of the object
    virtual void angle(double a) override final {
        bfo_.set_property("angle", Vector{a,0.0});
    }

    /// Returns the current angle increment of the object
    virtual double angle_increment() const override final {
        return cbfo_.get_property("angle_increment")[0];
    }

    /// Returns the current angle increment of the object
    void angle_increment(double a_incr) {
        bfo_.set_property("angle_increment", Vector{a_incr,0.0});
    }
};

}

#endif
