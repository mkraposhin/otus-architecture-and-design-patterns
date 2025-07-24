#ifndef ExceptionPropertyNotFound_HXX
#define ExceptionPropertyNotFound_HXX

namespace game {

class ExceptionPropertyNotFound : public std::exception{

    /// Forbids the default ctor
    ExceptionPropertyNotFound() = delete;

public:

    /// Creates new ExceptionPropertyNotFound
    ExceptionPropertyNotFound(const std::string& property_name)
    : property_name_(property_name) {}

private:

    /// Stores the property name that was not found
    const std::string property_name_;

};

}

#endif
