/**
 * @file OpenGL.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_OPENGL_HPP
#define PGR_OPENGL_HPP

#include <pgr.h>

#include <core/debug.hpp>
#include <stdint.h>
#include <string>

#ifndef PGR_DEBUG
#define GL(action) gl##action
#else // ifdef PGR_DEBUG
#define GL(action) gl##action;\
    if(sadekpet::OpenGL::Error(__FILE__, __LINE__)) PGR_DEBUG_BREAK;
#endif // PGR_DEBUG

namespace sadekpet {

enum class OpenGLError : uint32_t
{
    NONE = 0,
    CONTEXT_LOST = 0x0507,
    INVALID_ENUM = 0x0500,
    INVALID_VALUE = 0x0501,
    INVALID_OPERATION = 0x0502,
    INVALID_FRAMEBUFFER_OPERATION = 0x0506,
    OUT_OF_MEMORY = 0x0505,
    STACK_OVERFLOW = 0x0503,
    STACK_UNDERFLOW = 0x0504
};

class OpenGL
{
private:
    static const std::string s_errorStrings[9];
public:
    static OpenGLError GetError();
    static const std::string& GetErrorString(OpenGLError err);
    static void ClearError();
    static bool Error(const char* file, int line);
};

}

#endif // PGR_OPENGL_HPP