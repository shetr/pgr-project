#include "OpenGL.hpp"

#include <iostream>

namespace sadekpet {

const std::string OpenGL::s_errorStrings[9] = {
    "NONE",
    "INVALID_ENUM",
    "INVALID_VALUE",
    "INVALID_OPERATION",
    "STACK_OVERFLOW",
    "STACK_UNDERFLOW",
    "OUT_OF_MEMORY",
    "INVALID_FRAMEBUFFER_OPERATION",
    "CONTEXT_LOST"
};

OpenGLError OpenGL::GetError()
{
    return static_cast<OpenGLError>(glGetError());
}

const std::string& OpenGL::GetErrorString(OpenGLError err)
{
    return s_errorStrings[err == OpenGLError::NONE ? 0 : static_cast<uint32_t>(err) - 0x0500 + 1];
}

void OpenGL::ClearError()
{
    while(OpenGL::GetError() != OpenGLError::NONE);
}

bool OpenGL::Error(const char* file, int line)
{
    OpenGLError err;
    bool res = false;
    while((err = GetError()) != OpenGLError::NONE) {
        res = true;
        std::cerr << "OpenGL error " << file << " " << line << ": " << GetErrorString(err) << std::endl;
    }
    return res;
}

}