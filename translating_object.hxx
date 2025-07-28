#ifndef TranslatingObject_HXX
#define TranslatingObject_HXX

namespace game {

/// An interface defining how an object in a battle field
/// can move (translate) along a specified vector
class TranslatingObject {

public:

    /// Creates a new instance of TranslatingObject
    TranslatingObject() = default;

    /// Returns current position of the object
    virtual Vector position() const = 0;

    /// Sets a new position of the object
    virtual void position(const Vector &new_pos) = 0;

    /// Returns a displacement vector by which the
    /// object is translated
    virtual Vector displacement() const = 0;

};

}

#endif
