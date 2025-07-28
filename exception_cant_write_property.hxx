#ifndef ExceptionCantWriteProperty_HXX
#define ExceptionCantWriteProperty_HXX

namespace game {

class ExceptionCantWriteProperty : public std::exception {

    /// Forbids the default ctor
    ExceptionCantWriteProperty() = delete;

public:

    /// Creates new ExceptionCantWriteProperty
    ExceptionCantWriteProperty(const std::string& property_name)
    : property_name_(property_name) {}

private:

    /// Stores the property name that was not found
    const std::string property_name_;

};

}

#endif
