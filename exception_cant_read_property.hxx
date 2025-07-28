#ifndef ExceptionCantReadProperty_HXX
#define ExceptionCantReadProperty_HXX

namespace game {

class ExceptionCantReadProperty : public std::exception {

    /// Forbids the default ctor
    ExceptionCantReadProperty() = delete;

public:

    /// Creates new ExceptionCantReadProperty
    ExceptionCantReadProperty(const std::string& property_name)
    : property_name_(property_name) {}

private:

    /// Stores the property name that was not found
    const std::string property_name_;

};

}

#endif
