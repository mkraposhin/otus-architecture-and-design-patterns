#ifndef TranslatingObjectAdapter_HXX
#define TranslatingObjectAdapter_HXX

#include "battle_field_object.hxx"
#include "translating_object.hxx"

namespace game {

class TranslatingObjectAdapter : public TranslatingObject {

private:

    BattleFieldObject& bfo_;

    const BattleFieldObject& cbfo_;

public:

    TranslatingObjectAdapter(BattleFieldObject& bfo)
    : bfo_(bfo), cbfo_(bfo) {
    }

    Vector position() const override final {
        return cbfo_.get_property("position");
    }

    void position(const Vector& v) override final {
        return bfo_.set_property("position", v);
    }

    Vector displacement() const override final {
        return cbfo_.get_property("displacement");
    }

    void displacement(const Vector& v) {
        return bfo_.set_property("displacement", v);
    }
};

}

#endif
