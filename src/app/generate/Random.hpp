/**
 * @file Random.hpp
 * @author sadekpet
 * @date 2020-04-15
 * @brief 
 * 
 * 
 */

#ifndef PGR_RANDOM_HPP
#define PGR_RANDOM_HPP

#include <core/types.hpp>

namespace sadekpet {

/// Interface for random number generators.
class Random
{
public:
    /**
     * @brief Returns next generated number.
     * @return uint32_t Next generated number.
     */
    virtual uint32_t Next() = 0;
    /**
     * @brief Returns next generated number with maximum value of max.
     * @param max Maximum genareded value.
     * @return uint32_t Next generated number.
     */
    virtual uint32_t Next(uint32_t max) = 0;
    /**
     * @brief Returns next generated number with minimum value of min and maximum value of max.
     * @param min Minimum genareded value.
     * @param max Maximum genareded value.
     * @return uint32_t Next generated number.
     */
    virtual uint32_t Next(uint32_t min, uint32_t max) = 0;
};

/// Linear congruential random number generator.
class LinCongRand : public Random
{
private:
    uint32_t m_previous;
    uint32_t m_multiplier;
    uint32_t m_increment;
public:
    /**
     * @brief Construct a new linear congruential random number generator object
     * @param seed Initial value determining the random sequence.
     * @param multiplier Linear congruential random number generator multiplier parameter.
     * @param increment Linear congruential random number generator increment parameter.
     */
    LinCongRand(uint32_t seed, uint32_t multiplier = 22695477, uint32_t increment = 1)
        : m_previous(seed), m_multiplier(multiplier), m_increment(increment) {}

    /**
     * @brief Returns next generated number.
     * @return uint32_t Next generated number.
     */
    uint32_t Next() override
    {
        m_previous *= m_multiplier;
        m_previous += m_increment;
        return m_previous;
    }
    /**
     * @brief Returns next generated number with maximum value of max.
     * @param max Maximum genareded value.
     * @return uint32_t Next generated number.
     */
    uint32_t Next(uint32_t max) override
    {
        return Next() % (max+1);
    }
    /**
     * @brief Returns next generated number with minimum value of min and maximum value of max.
     * @param min Minimum genareded value.
     * @param max Maximum genareded value.
     * @return uint32_t Next generated number.
     */
    uint32_t Next(uint32_t min, uint32_t max) override
    {
        return Next(max - min) + min;
    }
};

}

#endif // PGR_RANDOM_HPP