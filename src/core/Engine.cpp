#include "Engine.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "render/OpenGL.hpp"

#include <iostream>

namespace sadekpet {

Engine* Engine::s_engine = nullptr;

void Engine::Create(EngineArgs args, EngineConfig config, App* app)
{
    if(s_engine == nullptr) {
		s_engine = new Engine(args, config, app);
    }
}
Engine* Engine::Get()
{
    return s_engine;
}

Engine::Engine(EngineArgs args, EngineConfig config, App* app)
    : m_args(args), m_config(config), m_app(app)
{
}
Engine::~Engine()
{
	s_engine = nullptr;
}
int Engine::Run()
{
    Init();
    glutMainLoop();
    return 0;
}
void Engine::Init()
{
    m_timer.Measure();

    glutInit(m_args.pargc, m_args.argv);
    glutInitContextVersion(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);

    Window::Init(m_config.windowSize, m_config.windowTitle);
    m_window = Unique<Window>(Window::Get());
    Input::Init();
    m_shaderManager = Unique<ShaderManager>(ShaderManager::Init());

    bool pgrRes;
    #ifdef PGR_DEBUG
        pgrRes = pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR, static_cast<pgr::DebugLevel>(m_config.debugLevel));
    #else
        pgrRes = pgr::initialize(pgr::OGL_VER_MAJOR, pgr::OGL_VER_MINOR);
    #endif

    if(!pgrRes)
        pgr::dieWithError("pgr init failed, required OpenGL not supported?");

    m_renderer.Init();

    m_app->Init();

    UpdateWorldTransfrom();

    glutDisplayFunc(&Engine::DrawCallback);
    glutIdleFunc(&Engine::IdleCallback);
}

void Engine::Draw()
{
    m_renderer.Clear();
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer& layer = Layers::Get(l);
        Layers::SetCurrent(&layer);
        for(Pair<uint, VisibleNode*> p : layer.Visible()) {
            m_renderer.Draw(p.second->GetMaterial());
        }
    }
    Layers::SetCurrent(nullptr);
    m_renderer.SwapBuffers();
}

void Engine::Update()
{
    m_timer.Measure();
    m_app->Update(m_timer.GetDelta());
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer& layer = Layers::Get(l);
        Layers::SetCurrent(&layer);
        for(Pair<uint, Node*> p : layer.Roots()) {
            p.second->Update(m_timer.GetDelta());
        }
    }
    UpdateWorldTransfrom();
}

void Engine::UpdateWorldTransfrom()
{
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer& layer = Layers::Get(l);
        Layers::SetCurrent(&layer);
        for(Pair<uint, Node*> p : layer.Roots()) {
            p.second->UpdateWorldTransform();
        }
    }
    Layers::SetCurrent(nullptr);
}

void Engine::DrawCallback()
{
	s_engine->Draw();
}
void Engine::IdleCallback()
{
	s_engine->Update();
    glutPostRedisplay();
}

}
