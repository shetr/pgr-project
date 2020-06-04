/**
 * @file Spline.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-01
 */

#ifndef PGR_SPLINE_HPP
#define PGR_SPLINE_HPP

#include <core/types.hpp>

namespace sadekpet {

/**
 * @brief Uniformní B spline.
 * Aproximuje uzavřenou křivku pro zadané body.
 */
class UniformBSpline
{
private:
    Vector<glm::vec3> m_points;
    Vector<float> m_lengthsApprox;
    float m_lengthApprox;
public:
    UniformBSpline(const Vector<glm::vec3>& points);
    float GetLengthApprox() const { return m_lengthApprox; }
    int GetPointsCount() const { return m_points.size(); }
    glm::vec3 Value(float t) const;
    glm::vec3 Derivative(float t) const;
    Pair<float, Array<glm::vec3, 4>> GetSegment(float t) const;
private:
    int Idx(int i) const;
};

}

#endif // PGR_SPLINE_HPP