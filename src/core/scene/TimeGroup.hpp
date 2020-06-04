/**
 * @file TimeGroup.hpp
 * @author sadekpet 
 * @brief 
 * @date 2020-05-18
 * 
 */

#ifndef PGR_TIME_GROUP_HPP
#define PGR_TIME_GROUP_HPP

namespace sadekpet {

/**
 * @brief Slouží ke sdílení stejné rychlosti času mezi více objekty.
 */
class TimeGroup
{
private:
    float m_speed;
public:
    TimeGroup(float speed = 1) : m_speed(speed) {}
    float& Speed() { return m_speed; }
};

}

#endif // PGR_TIME_GROUP_HPP