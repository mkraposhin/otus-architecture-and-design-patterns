#ifndef RotatingObject_HXX
#define RotatingObject_HXX

namespace game {

/// An interface defining how an object in a battle field
/// can rotate
class RotatingObject {

public:

    /// Returns the current orientation (in local coordinates)
    /// of the object
    virtual const Vector orientation() const = 0;

    /// Returns the current orientation angle of the object
    virtual double angle() const = 0;

    /// Sets a new orientation angle of the object
    virtual void angle(double a) = 0;

    /// Returns the current angle increment of the object
    virtual double angle_increment() const = 0;

};

}

#endif
