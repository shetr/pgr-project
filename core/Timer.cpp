#include "Timer.hpp"

namespace sadekpet {

Timer::Timer() : m_delta(0), m_speed(1) 
{
    m_lastMeasure = std::chrono::steady_clock::now();
}

void Timer::Measure()
{
    using namespace std::chrono;

    time_point<steady_clock> newMeasure = steady_clock::now();
    std::chrono::duration<float> delta = newMeasure - m_lastMeasure;
    m_delta = delta.count();
    m_lastMeasure = newMeasure;
}

}