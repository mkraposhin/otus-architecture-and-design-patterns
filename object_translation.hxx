#ifndef ObjectTranslation_HXX
#define ObjectTranslation_HXX

#include "translating_object.hxx"
#include "exception_property_not_found.hxx"
#include "exception_cant_read_property.hxx"
#include "exception_cant_write_property.hxx"

namespace game {

/// The class implements translation of an object
/// by the vector given as a property of the object
class ObjectTranslation {

private:

    /// Forbids default ctor
    ObjectTranslation() = delete;

    /// Forbids copy ctor
    ObjectTranslation(const ObjectTranslation&) = delete;

    /// Forbids move ctor
    ObjectTranslation(ObjectTranslation&&) = delete;

public:

    /// Constructs a new instance of ObjectTranslation from
    /// from the reference to a translated object
    ObjectTranslation(TranslatingObject& obj) : obj_(obj){};

    /// Translates the referenced object by the given
    /// displacement vector
    void Execute() {
        // try to read the properties
        Vector new_pos;
        try {
            new_pos = obj_.position() + obj_.displacement();
        } catch (const ExceptionPropertyNotFound &e) {
            throw ExceptionCantReadProperty {"position or displacement"};
        }

        // try to set properties
        try {
            obj_.position(new_pos);
        } catch (const ExceptionPropertyNotFound &e) {
            throw ExceptionCantWriteProperty {"position"};
        }
    }

private:

    /// A reference to the object being translated
    TranslatingObject& obj_;

};

}

#endif
