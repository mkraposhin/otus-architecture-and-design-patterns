#ifndef SpaceBattle_HXX
#define SpaceBattle_HXX

#include <array>

namespace game {
    using Vector = std::array<double, 2>;

    inline Vector operator + (const Vector v1, const Vector v2) {
        Vector rv;
        for (Vector::size_type i = 0; i < rv.size(); i++) {
            rv[i] = v1[i] + v2[i];
        }
        return rv;
    }
}

#endif

