

#ifndef PGR_PARTIAL_LERP_HPP
#define PGR_PARTIAL_LERP_HPP

#include <core/types.hpp>
#include <stdexcept>

#include "Math.hpp"

namespace sadekpet {

template<typename ValueType>
struct PartialLerpPoint
{
    float position;
    ValueType value;
};

template<typename ValueType>
class PartialLerp
{
private:
    Vector<PartialLerpPoint<ValueType>> m_points;
public:
    PartialLerp() {}
    PartialLerp(const Vector<PartialLerpPoint<ValueType>>& points) : m_points(points) {}
    void AddPoint(const PartialLerpPoint<ValueType>& point) {
        m_points.push_back(point);
    }
    ValueType Value(float pos) const {
        if(m_points.empty()) {
            throw std::runtime_error("PartialLerp should have at least one point.");
        }
        for(int i = 0; i < m_points.size() - 1; i++) {
            float min = m_points[i].position;
            float max = m_points[i+1].position;
            if(min <= pos && pos < max) {
                float length = max - min;
                float t = (pos - min) / length;
                return Math::Lerp(m_points[i].value, m_points[i+1].value, t);
            }
        }
        return m_points[0].value;
    } 
};

}

#endif // PGR_PARTIAL_LERP_HPP