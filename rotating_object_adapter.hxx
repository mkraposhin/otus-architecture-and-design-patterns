#ifndef RotatingObjectAdapter_HXX
#define RotatingObjectAdapter_HXX

namespace game {

class RotatingObjectAdapter : public RotatingObjectI {

public:

    const Vector& direction() const;

    void direction(const Vector&) const;

    double angle_increment() const;

};

}

#endif
