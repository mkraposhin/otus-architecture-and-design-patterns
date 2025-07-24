#ifndef ObjectMotionI_HXX
#define ObjectMotionI_HXX

namespace game {

/// The interface defines methods to move an object
/// in space
class ObjectMotionI {
private:

    ObjectMotionI() = delete;

    ObjectMotionI(const ObjectMotionI&) = delete;

    ObjectMotionI(ObjectMotionI&&) = delete;

public:

    template <class MovingObject>
    virtual void Move(MovingObject& obj) = 0;
};

}

#endif
