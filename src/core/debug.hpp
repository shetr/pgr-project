/**
 * @file debug.hpp
 * @author sadekpet 
 * @brief 
 */

#ifndef PGR_DEBUG_HPP
#define PGR_DEBUG_HPP

#ifdef PGR_WINDOWS
#define PGR_DEBUG_BREAK __debugbreak()
#elif PGR_LINUX
#include <signal.h>
#define PGR_DEBUG_BREAK raise(SIGTRAP)
#else
#define PGR_DEBUG_BREAK 0
#endif

#endif//PGR_DEBUG_HPP