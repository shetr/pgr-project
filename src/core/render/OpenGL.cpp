#include "OpenGL.hpp"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <ostream>

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

#if defined(_WIN32)
#include <windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "Dbghelp")
#elif defined(__linux__)
#include <execinfo.h>
#endif

namespace pgr {

namespace gldebug {

const char * sourceToString(GLenum src) {
  switch(src) {
    case GL_DEBUG_SOURCE_API: return "API";
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
    case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
    case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
    case GL_DEBUG_SOURCE_APPLICATION: return "Application";
    case GL_DEBUG_SOURCE_OTHER: return "Other";
    default: return "<unknown>";
  }
}

const char * typeToString(GLenum type) {
  switch(type) {
    case GL_DEBUG_TYPE_ERROR: return "Error";
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behavior";
    case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
    case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
    case GL_DEBUG_TYPE_OTHER: return "Other";
    default: return "<unknown>";
  }
}

const char * severityToString(GLenum severity) {
  switch(severity) {
    case GL_DEBUG_SEVERITY_LOW: return "Low";
    case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
    case GL_DEBUG_SEVERITY_HIGH: return "High";
    default: return "<unknown>";
  }
}

void printBacktrace(std::ostream * os) {
  if(os == 0)
    os = &std::cout;

  const int SIZE = 100;
  const int NAME_SIZE = 256;
#if defined(_WIN32)
  HANDLE process = GetCurrentProcess();
  SymSetOptions(SYMOPT_LOAD_LINES);
  SymInitialize(process, NULL, TRUE);

  void * stack[SIZE];
  unsigned short frames = CaptureStackBackTrace(0, SIZE, stack, NULL);
  SYMBOL_INFO * symbol = (SYMBOL_INFO * )calloc(sizeof(SYMBOL_INFO) + NAME_SIZE * sizeof(char), 1);
  symbol->MaxNameLen = NAME_SIZE;
  symbol->SizeOfStruct = sizeof(SYMBOL_INFO);

  for(unsigned short i = 0; i < frames; i++ ) {
    SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
    IMAGEHLP_LINE64 line;
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
    DWORD  dwDisplacement;
    if(!strstr(symbol->Name, __FUNCTION__) && !strstr(symbol->Name,"pgr::debugCallback") && SymGetLineFromAddr64(process, (DWORD64)(stack[i]), &dwDisplacement, &line)) {
      *os << symbol->Name << "():" << line.LineNumber << std::endl;
    }
    if(strcmp(symbol->Name, "main") == 0)
      break;
  }

  free(symbol);
#elif defined(__linux__)
  int j;
  void *buffer[SIZE];
  char **strings;

  int nptrs = backtrace(buffer, SIZE);
  strings = backtrace_symbols(buffer, nptrs);
  if(strings == NULL) {
    *os << "error in backtrace_symbols" << std::endl;
    return;
  }
  for (j = 0; j < nptrs; j++)
    *os << strings[j] << std::endl;
  free(strings);
#else
  *os << "backtrace not supported on this platform" << std::endl;
#endif
}

} // end namespace gldebug

static void APIENTRY debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei, const GLchar* message, void* userParam) {
  std::ostream * os = reinterpret_cast<std::ostream*>(userParam);
  if(os == 0)
    os = &std::cerr;
  *os << "---- OGL DEBUG ----" << std::endl;
  *os << "message <" << id << ">: '" << gldebug::sourceToString(source) << "' reported '" << gldebug::typeToString(type)
      << "' with '" << gldebug::severityToString(severity) << "' severity: " << std::endl << message << std::endl;
  *os << "---- BACKTRACE ----" << std::endl;
  gldebug::printBacktrace(os);
  *os << "---- ---- ---- ----" << std::endl;
}

bool initialize(int glVerMajor, int glVerMinor, DebugLevel debugLevel) {
#if USE_GLLOADGEN
  if(ogl_LoadFunctions() == ogl_LOAD_FAILED) {
    std::cerr << "cannot initialize opengl" << std::endl;
    return false;
  }
  if(ogl_IsVersionGEQ(glVerMajor, glVerMinor - 1) == 1) {
    std::cerr << "OpenGL " << glVerMajor << "." << glVerMinor << " or higher not available" << std::endl;
    return false;
  }
#else
  // we have to sate experimental to work in forward comp mode
  glewExperimental = GL_TRUE;
  if(glewInit() != GLEW_OK) {
    std::cerr << "glew init failed (right context not created?)" << std::endl;
    return false;
  }
  GLenum err = glGetError();
  // silently ignore error caused by glewInit() - happens in forward comp.
  //if(err != GL_NONE)
  //  std::cerr << "glErr in glewInit" << std::endl;

  std::stringstream vers;
  vers << "GL_VERSION_" << glVerMajor << "_" << glVerMinor;
  if(!glewIsSupported(vers.str().c_str())) {
    std::cerr << "OpenGL " << glVerMajor << "." << glVerMinor << " or higher not available" << std::endl;
    return false;
  }
#endif

  // enable debug if requested
  bool debugEnabled = false;
  if(debugLevel > 0 && glDebugMessageCallback != NULL) {
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, &std::cerr);
    debugEnabled = true;
    if(glDebugMessageControl) {
      // enable various severity levels according to debugLevel
      const int nSeverities = 3;
      GLenum severities[nSeverities] = { GL_DEBUG_SEVERITY_HIGH, GL_DEBUG_SEVERITY_MEDIUM, GL_DEBUG_SEVERITY_LOW };
      for(int i = 0; i < nSeverities; ++i) {
        glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DONT_CARE, severities[i], 0, NULL, debugLevel > i ? GL_TRUE : GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_WINDOW_SYSTEM, GL_DONT_CARE, severities[i], 0, NULL, debugLevel > i ? GL_TRUE : GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_SHADER_COMPILER, GL_DONT_CARE, severities[i], 0, NULL, debugLevel > i ? GL_TRUE : GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_THIRD_PARTY, GL_DONT_CARE, severities[i], 0, NULL, debugLevel > i ? GL_TRUE : GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_APPLICATION, GL_DONT_CARE, severities[i], 0, NULL, debugLevel > i ? GL_TRUE : GL_FALSE);
        glDebugMessageControl(GL_DEBUG_SOURCE_OTHER, GL_DONT_CARE, severities[i], 0, NULL, debugLevel > i ? GL_TRUE : GL_FALSE);
      }
    }
  }

  // initialize DevIL
  ilInit();

  std::cout << "pgr: initialized, using OpenGL " << glVerMajor << "." << glVerMinor
      << " debug " << (debugEnabled ? "enabled" : "disabled") << std::endl;
  return true;
}

std::string frameworkRoot() {
  char * root = getenv("PGR_FRAMEWORK_ROOT");
  return root ? root : "";
}

void dieWithError(const std::string & errMsg) {
#if defined(_WIN32) || defined(WIN32)
  MessageBoxA(NULL, errMsg.c_str(), "Fatal error", MB_ICONERROR | MB_OK);
#else
  // will we show some nice graphic error messages on X11/Masox?
  std::cerr << "Fatal error: " << errMsg << std::endl;
#endif
  exit(1);
}

void checkGLError(const char *where, int line) {
  GLenum err = glGetError();
  if(err == GL_NONE)
    return;

  std::string errString = "<unknown>";
  switch(err) {
    case GL_INVALID_ENUM:
      errString = "GL_INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      errString = "GL_INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      errString = "GL_INVALID_OPERATION";
      break;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      errString = "GL_INVALID_FRAMEBUFFER_OPERATION";
      break;
    case GL_OUT_OF_MEMORY:
      errString = "GL_OUT_OF_MEMORY";
      break;
    default:;
  }
  if(where == 0 || *where == 0)
    std::cerr << "GL error occurred: " << errString << std::endl;
  else
    std::cerr << "GL error occurred in " << where << ":" << line << ": " << errString << std::endl;
}

} // end namespace pgr