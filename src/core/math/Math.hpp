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

class Math
{
public:

    template<typename V>
    inline static float Lerp(V v1, V v2, float t) {
        return v1 * (1 - t) + v2 * t;
    }
};

}

#endif // PGR_MATH_HPP