/**
 * @file Timer.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-01
 * 
 */

#ifndef PGR_TIMER_HPP
#define PGR_TIMER_HPP

#include <chrono>

namespace sadekpet {

class Timer
{
private:
    float m_delta;
    float m_speed;
    std::chrono::time_point<std::chrono::steady_clock> m_lastMeasure;
public:
    Timer();
    void Measure();
    void SetTimeSpeed(float speed) { m_speed = speed; }
    float GetDelta() const { return m_speed * m_delta; }
};

}

#endif // PGR_TIMER_HPP