/**
 * @file OpenGL.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_OPENGL_HPP
#define PGR_OPENGL_HPP

#define USE_GLLOADGEN 1

#if USE_GLLOADGEN
#include "gl_core_4_4.h"
#else
#include <GL/glew.h>
#endif
#include <GL/freeglut.h>
#include <IL/il.h>

#include <string>
#include <math.h>

#include <glm/glm.hpp>                  // vec3 normalize cross
#include <glm/gtc/type_ptr.hpp>         // value_ptr
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale

#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

#ifndef M_PI
/// define Pi for compatibility issues (MSVC vs GCC)
#define M_PI 3.14159f
#endif

#ifndef DEGTORAD
/// degrees-to-radians conversion macro
#define DEGTORAD(a) ((a) * M_PI / 180.0)
#endif
#ifndef RADTODEG
/// radians-to-degrees conversion macro
#define RADTODEG(a) ((a) * 180.0 / M_PI)
#endif

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

/**
 * @brief Typ opengl erroru.
 */
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

/**
 * @brief Funkce týkající se čistě opengl, primárně errory.
 */
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

namespace pgr {

/// defines verbosity of the debug system, DEBUG_OFF turns the system off
enum DebugLevel {
  DEBUG_OFF = 0, ///< turn of the debug callbacks
  DEBUG_LOW, ///< enables messages with hight severity
  DEBUG_MEDIUM, ///< enables messages with hight and medium severities,
  DEBUG_HIGH ///< enables messages with all severities
};

/** required opengl version - major number
 *
 * Use this constant as a first argument of glutInitContextVersion and pgr::initialize.
 */
const int OGL_VER_MAJOR = 3;
/** required opengl version - minor number
 *
 * Use this constant as a second argument of glutInitContextVersion and pgr::initialize.
 */
const int OGL_VER_MINOR = 1;

/** intializes gl functions, DevIL and checks opengl version
 *
 * Call this function after successful creation of OpenGL context (for example after glutCreateWindow).
 * \returns true if everything went ok, especially if opengl version is sufficient; false indicates error - you should exit the application
 * \param glVerMajor opengl major version to check (returns false if not available)
 * \param glVerMinor opengl minor version to check (returns false if not available)
 * \param debugLevel if not DEBUG_OFF initialize opengl debug callback (glDebugMessageCallback), works only with debug contexts!
 */
//bool initialize(int glVerMajor, int glVerMinor, DebugLevel debugLevel = DEBUG_MEDIUM);
bool initialize(int glVerMajor, int glVerMinor, DebugLevel debugLevel = DebugLevel::DEBUG_LOW);

/** returns the value of the PGR_FRAMEWORK_ROOT system variable
 *
 * If the variable is not set, the function returns empty string.
 */
std::string frameworkRoot();

/** prints a message and exits the application
 *
 * Use this if you detect an error from which you dont want to recover.
 * The functions shows the errMsg string to the user
 * and terminates the application with an error return code.
 *
 * \return this function does not return
 */
void dieWithError(const std::string & errMsg);

/** prints out pending opengl error
 *
 * If there is nothing to print (no opengl error has occurred), the function prints nothing.
 * You can use where and line arguments to supply addtional information that will be printed out.
 *
 * \see CHECK_GL_ERROR
 */
void checkGLError(const char * where = 0, int line = 0);

/** helper macro involving the checkGLError function
 *
 * The macro uses __FUNCTION__ and __LINE__ as arguments to the checkGLError function.
 * Use it anywhere you like to catch opengl errors.
 */
#define CHECK_GL_ERROR() do { pgr::checkGLError(__FUNCTION__, __LINE__); } while(0)

}

#endif // PGR_OPENGL_HPP