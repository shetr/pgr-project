/**
 * @file Engine.hpp
 * @author sadekpet 
 * @brief 
 */

#ifndef PGR_ENGINE_HPP
#define PGR_ENGINE_HPP

#include <core/types.hpp>
#include "Window.hpp"
#include "Timer.hpp"
#include "render/Renderer.hpp"
#include "manage/ShaderManager.hpp"
#include "manage/TextureManager.hpp"
#include "manage/PrimitivesManager.hpp"
#include "manage/MaterialManager.hpp"
#include "scene/Layers.hpp"


namespace sadekpet {

/**
 * @brief Úroveň debugovacího výstupu.
 */
enum DebugLevel {
  DEBUG_OFF = 0,
  DEBUG_LOW,
  DEBUG_MEDIUM,
  DEBUG_HIGH 
};

/**
 * @brief Způsob běhu hlavního cyklu.
 */
enum class EngineLoop {
    NON_STOP,
    FIXED_GLUT,
    FIXED_CUSTOM
};

/**
 * @brief Počáteční nastevení enginu.
 */
struct EngineConfig
{
    WindowSize windowSize;
    const char* windowTitle;
    DebugLevel debugLevel;
    EngineLoop loopType;
    float fps;
};

/**
 * @brief Argumenty programu (pro glut).
 */
struct EngineArgs
{
    int* pargc;
    char** argv;
};

class App;

/**
 * @brief Jádro celého systému. Inicializuje knihovny, aplikaci, updatuje a vykresluje graf scény.
 */
class Engine
{
private:
    static Engine* s_engine;
    Renderer m_renderer;
    EngineArgs m_args;
    EngineConfig m_config;
    Timer m_timer;
    Unique<Window> m_window;
    Unique<ShaderManager> m_shaderManager;
    Unique<TextureManager> m_textureManager;
    Unique<PrimitivesManager> m_primitivesManager;
    Unique<MaterialManager> m_materialManager;
    Unique<App> m_app;
    float m_updateTime;
public:
    static void Create(EngineArgs args, EngineConfig config, App* app);
    static Engine* Get();
    ~Engine();

    int Run();

    static void SetTimeSpeed(float speed);
    static void Exit();
private:
    Engine(EngineArgs args, EngineConfig config, App* app);
    void Init();
    void Draw();
    void Update();
    void UpdateWorldTransfrom();

    static void DrawCallback();
    static void UpdateCallback();
    static void TimerCallback(int id);

    float UpdateTime();
    static void SetTimerGLUT();
};

}

#endif // PGR_ENGINE_HPP
