#include "Spline.hpp"

namespace sadekpet {

UniformBSpline::UniformBSpline(const Vector<glm::vec3>& points) : m_points(points), m_lengthsApprox(points.size()), m_lengthApprox(0)
{
    for(int i = 0; i < GetPointsCount(); i++) {
        glm::vec3& p1 = m_points[Idx(i)];
        glm::vec3& p2 = m_points[Idx(i+1)];
        m_lengthsApprox[i] = glm::distance(p1, p2);
        m_lengthApprox += m_lengthsApprox[i];
    }
}

glm::vec3 UniformBSpline::Value(float t) const
{
    Pair<float, Array<glm::vec3, 4>> pair = GetSegment(t);
    t = pair.first;
    Array<glm::vec3, 4>& p = pair.second;
    glm::vec3 v;
    float t0 = 1;
    float t1 = t;
    float t2 = t*t;
    float t3 = t2*t;
    float c0 = ((-1)*t3 + ( 3)*t2 + (-3)*t1 + ( 1)*t0) / 6.0f;
    float c1 = (( 3)*t3 + (-6)*t2 + ( 0)*t1 + ( 4)*t0) / 6.0f;
    float c2 = ((-3)*t3 + ( 3)*t2 + ( 3)*t1 + ( 1)*t0) / 6.0f;
    float c3 = (( 1)*t3 + ( 0)*t2 + ( 0)*t1 + ( 0)*t0) / 6.0f;
    v = p[0]*c0 + p[1]*c1 + p[2]*c2 + p[3]*c3;
    return v;
}
glm::vec3 UniformBSpline::Derivative(float t) const
{
    Pair<float, Array<glm::vec3, 4>> pair = GetSegment(t);
    t = pair.first;
    Array<glm::vec3, 4>& p = pair.second;
    glm::vec3 v;
    float t0 = 0;
    float t1 = 1;
    float t2 = 2*t;
    float t3 = 3*t*t;
    float c0 = ((-1)*t3 + ( 3)*t2 + (-3)*t1 + ( 1)*t0) / 6.0f;
    float c1 = (( 3)*t3 + (-6)*t2 + ( 0)*t1 + ( 4)*t0) / 6.0f;
    float c2 = ((-3)*t3 + ( 3)*t2 + ( 3)*t1 + ( 1)*t0) / 6.0f;
    float c3 = (( 1)*t3 + ( 0)*t2 + ( 0)*t1 + ( 0)*t0) / 6.0f;
    v = p[0]*c0 + p[1]*c1 + p[2]*c2 + p[3]*c3;
    return v;
}
Pair<float, Array<glm::vec3, 4>> UniformBSpline::GetSegment(float t) const
{
    Pair<float, Array<glm::vec3, 4>> res;
    Array<glm::vec3, 4>& points = res.second;
    int ti = ((int)(t / m_lengthApprox)) * m_lengthApprox;
    t = t - ti;
    float l = 0;
    for(int i = 0; i < GetPointsCount(); i++) {
        float lPrev = l;
        l += m_lengthsApprox[i];
        if(t < l) {
            points[0] = m_points[Idx(i-1)];
            points[1] = m_points[Idx(i)];
            points[2] = m_points[Idx(i+1)];
            points[3] = m_points[Idx(i+2)];
            res.first = (t - lPrev) / m_lengthsApprox[i];
            break;
        }
    }
    return res;
}

int UniformBSpline::Idx(int i) const
{
    i = i % GetPointsCount();
    return i < 0 ? GetPointsCount() + i : i;
}

}