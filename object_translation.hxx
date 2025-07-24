#ifndef ObjectTranslation_HXX
#define ObjectTranslation_HXX

#include "translating_object.hxx"

namespace game {

class ObjectTranslation {

private:

    ObjectTranslation() = delete;

    ObjectTranslation(const ObjectTranslation&) = delete;

    ObjectTranslation(ObjectTranslation&&) = delete;

public:

    ObjectTranslation(TranslatingObject& obj) : obj_(obj){};

    void Execute() {
        obj_.position(obj_.position() +
            obj_.displacement());
    }

private:

    ///
    TranslatingObject& obj_;

};

}

#endif
