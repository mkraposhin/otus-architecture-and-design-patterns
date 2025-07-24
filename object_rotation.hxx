#ifndef ObjectRotation_HXX
#define ObjectRotation_HXX

namespace game {

class ObjectRotation {

private:

    ObjectRotation() = delete;

    ObjectRotation(const ObjectRotation&) = delete;

    ObjectRotation(ObjectRotation&&) = delete;

public:

    template <class MovingObject>
    void ObjectRotation(MovingObject& obj);

    void Execute() {
        obj.direction(obj.direction() +
            obj.angle_increment());
    }

};

}

#endif
