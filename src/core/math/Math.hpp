/**
 * @file Math.hpp
 * @author sadekpet
 * @date 2020-04-16
 * @brief 
 * 
 */

#ifndef PGR_MATH_HPP
#define PGR_MATH_HPP

namespace sadekpet {

/**
 * @brief Jednoduché často používané matematické funkce.
 */
class Math
{
public:

    static int FloorToOrigin(float v) {
        int r = static_cast<int>(v);
        return r < 0 ? r + 1 : r;
    }

    template<typename V>
    inline static V Lerp(V v1, V v2, float t) {
        return v1 * (1 - t) + v2 * t;
    }
};

}

#endif // PGR_MATH_HPP