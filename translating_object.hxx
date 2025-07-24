#ifndef TranslatingObject_HXX
#define TranslatingObject_HXX

namespace game {

class TranslatingObject {

public:

    ///
    TranslatingObject() = default;

    virtual Vector position() const = 0;

    virtual void position(const Vector &new_pos) = 0;

    virtual Vector displacement() const = 0;

};

}

#endif
