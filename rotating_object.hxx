#ifndef RotatingObject_HXX
#define RotatingObject_HXX

namespace game {

class RotatingObject {

public:

    const Vector& direction() const;

    void direction(const Vector&) const;

    double angle_increment() const;

};

}

#endif
