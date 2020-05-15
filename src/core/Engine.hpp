/**
 * @file Engine.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_ENGINE_HPP
#define PGR_ENGINE_HPP

#include <core/types.hpp>
#include "Window.hpp"
#include "Timer.hpp"
#include "render/Renderer.hpp"
#include "manage/ShaderManager.hpp"
#include "manage/TextureManager.hpp"
#include "scene/Layers.hpp"


namespace sadekpet {

enum DebugLevel {
  DEBUG_OFF = 0,
  DEBUG_LOW,
  DEBUG_MEDIUM,
  DEBUG_HIGH 
};

enum class EngineLoop {
    NON_STOP,
    FIXED_GLUT,
    FIXED_CUSTOM
};

struct EngineConfig
{
    WindowSize windowSize;
    const char* windowTitle;
    DebugLevel debugLevel;
    EngineLoop loopType;
    float fps;
};

struct EngineArgs
{
    int* pargc;
    char** argv;
};

class App;

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
