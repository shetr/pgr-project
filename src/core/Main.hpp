/**
 * @file Main.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_MAIN_HPP
#define PGR_MAIN_HPP

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

struct MainConfig
{
    WindowSize windowSize;
    const char* windowTitle;
    DebugLevel debugLevel;
};

struct MainArgs
{
    int* pargc;
    char** argv;
};

class Main
{
private:
    static Main* s_main;
    Renderer m_renderer;
    MainArgs m_args;
    MainConfig m_config;
    Timer m_timer;
    Unique<Window> m_window;
    Unique<ShaderManager> m_shaderManager;
    Unique<App> m_app;
public:
    static void Create(MainArgs args, MainConfig config, App* app);
    static Main* Get();
    ~Main();

    int Run();

    void SetTimeSpeed(float speed) { m_timer.SetTimeSpeed(speed); }
private:
    Main(MainArgs args, MainConfig config, App* app);
    void Init();
    void Draw();
    void Update();
    void UpdateWorldTransfrom();

    static void DrawCallback();
    static void IdleCallback();
};

}

#endif // PGR_MAIN_HPP
