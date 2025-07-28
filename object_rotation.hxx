#ifndef ObjectRotation_HXX
#define ObjectRotation_HXX

#include "rotating_object.hxx"
#include "exception_property_not_found.hxx"
#include "exception_cant_read_property.hxx"
#include "exception_cant_write_property.hxx"

namespace game {

/// The class describes rotation of an object in a battle field
class ObjectRotation {

private:

    /// Forbids the default ctor
    ObjectRotation() = delete;

    /// Forbids the copy ctor
    ObjectRotation(const ObjectRotation&) = delete;

    /// Forbids the move ctor
    ObjectRotation(ObjectRotation&&) = delete;

public:

    /// Constructs a new instance of ObjectRotation from
    /// from the reference to a translated object
    ObjectRotation(RotatingObject& obj) : obj_(obj){};

    /// Rotates the referenced object by the given
    /// angle increment
    void Execute() {
        double new_angle;
        try {
            new_angle = obj_.angle() + obj_.angle_increment();
        } catch (const ExceptionPropertyNotFound &e) {
            throw ExceptionCantReadProperty {"angle or angle_increment"};
        }

        // try to set properties
        try {
            obj_.angle(new_angle);
        } catch (const ExceptionPropertyNotFound &e) {
            throw ExceptionCantWriteProperty {"angle"};
        }
    } 

private:

    /// A reference to the object being translated
    RotatingObject& obj_;

};

}

#endif
