#ifndef TranslatingObjectAdapter_HXX
#define TranslatingObjectAdapter_HXX

#include "battle_field_object.hxx"
#include "translating_object.hxx"

namespace game {


/// This is an mediator between a translated object and
/// a class performing translation
class TranslatingObjectAdapter : public TranslatingObject {

private:

    /// A reference to the translated object
    BattleFieldObject& bfo_;

    /// A constant reference to the translated object
    const BattleFieldObject& cbfo_;

public:

    /// Creates a new instance of the mediator using a
    /// reference to the given translated object
    TranslatingObjectAdapter(BattleFieldObject& bfo)
    : bfo_(bfo), cbfo_(bfo) {
    }

    /// Returns the current position of the object
    /// associated with the mediator
    Vector position() const override final {
        return cbfo_.get_property("position");
    }

    /// Sets a new position for the object
    /// associated with the mediator
    void position(const Vector& v) override final {
        bfo_.set_property("position", v);
    }

    /// Returns the next displacement of the object
    /// associated with the mediator
    Vector displacement() const override final {
        return cbfo_.get_property("displacement");
    }

    /// Sets a new displacement for the object
    /// associated with the mediator
    void displacement(const Vector& v) {
        bfo_.set_property("displacement", v);
    }
};

}

#endif
