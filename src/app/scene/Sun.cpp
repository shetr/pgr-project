#include "Sun.hpp"


namespace sadekpet {

Sun::Sun(float size, float density) 
    : SpaceBody(size, density), m_shaderContext("spherePrecise", "perlinSun"), m_time(0), m_changeSpeed(0.05)
{ 
}

void Sun::Update(float deltaTime) {
    m_time += deltaTime * m_changeSpeed;
    if(m_time > 1) m_time -= 1;
    float t = m_time <= 0.5 ? 2*m_time : 2*(1 - m_time);
    m_shaderContext.GetSunUniforms().time->value = t;
}

}