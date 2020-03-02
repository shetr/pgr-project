/**
 * @file Engine.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_ENGINE_HPP
#define PGR_ENGINE_HPP

#include <core/types.hpp>
#include <app/App.hpp>
#include "Window.hpp"
#include "Timer.hpp"
#include "render/Renderer.hpp"
#include "manage/ShaderManager.hpp"
#include "scene/Layers.hpp"


namespace sadekpet {

enum DebugLevel {
  DEBUG_OFF = 0,
  DEBUG_LOW,
  DEBUG_MEDIUM,
  DEBUG_HIGH 
};

struct EngineConfig
{
    WindowSize windowSize;
    const char* windowTitle;
    DebugLevel debugLevel;
};

struct EngineArgs
{
    int* pargc;
    char** argv;
};

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
    Unique<App> m_app;
public:
    static void Create(EngineArgs args, EngineConfig config, App* app);
    static Engine* Get();
    ~Engine();

    int Run();

    void SetTimeSpeed(float speed) { m_timer.SetTimeSpeed(speed); }
private:
    Engine(EngineArgs args, EngineConfig config, App* app);
    void Init();
    void Draw();
    void Update();
    void UpdateWorldTransfrom();

    static void DrawCallback();
    static void IdleCallback();
};

}

#endif // PGR_ENGINE_HPP
