#include "Engine.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "render/OpenGL.hpp"
#include <app/App.hpp>

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
    m_updateTime = UpdateTime();
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
    m_textureManager = Unique<TextureManager>(TextureManager::Init());
    m_primitivesManager = Unique<PrimitivesManager>(PrimitivesManager::Init());
    m_materialManager = Unique<MaterialManager>(MaterialManager::Init());


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
    if(m_config.loopType == EngineLoop::FIXED_GLUT) {
        SetTimerGLUT();
    } else {
        glutIdleFunc(&Engine::UpdateCallback);
    }
}


void Engine::SetTimeSpeed(float speed) 
{ 
    s_engine->m_timer.SetTimeSpeed(speed);
}
void Engine::Exit()
{
    glutLeaveMainLoop();
}

void Engine::Draw()
{
    m_renderer.StartScene();
    UpdateWorldTransfrom();
    m_renderer.Clear();
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer* layer = Layers::Get(l);
        Layers::SetCurrent(layer);
        if(layer->DoClearDepth()) {
            m_renderer.ClearDepth();
        }
        if(!layer->DoWriteDepth()) {
            m_renderer.DepthMask(false);
        }
        for(Pair<uint, VisibleNode*> p : layer->Visible()) {
            VisibleNode* node = p.second;
            if(node->IsVisible()) {
                node->UpdateShaderContext();
                m_renderer.SetStencilID(node->GetStencilID());
                m_renderer.Draw(node->GetShaderContext());
            }
        }
        if(!layer->DoWriteDepth()) {
            m_renderer.DepthMask(true);
        }
    }
    Input::StencilUpdate(m_timer.GetDelta());
    Layers::SetCurrent(nullptr);
    m_renderer.EndScene();
    m_renderer.SwapBuffers();
}

void Engine::Update()
{
    m_timer.Measure();
    //std::cout << "fps: " << (1/ m_timer.GetDelta()) << std::endl;
    UpdateWorldTransfrom();
    m_app->Update(m_timer.GetDelta());
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer* layer = Layers::Get(l);
        Layers::SetCurrent(layer);
        for(Pair<uint, Node*> p : layer->Roots()) {
            p.second->Update(m_timer.GetDelta() * p.second->GetTimeSpeed());
        }
    }
}

void Engine::UpdateWorldTransfrom()
{
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer* layer = Layers::Get(l);
        Layers::SetCurrent(layer);
        for(Pair<uint, Node*> p : layer->Roots()) {
            p.second->UpdateWorldTransform();
        }
    }
    Layers::SetCurrent(nullptr);
}

void Engine::DrawCallback()
{
	s_engine->Draw();
}
void Engine::UpdateCallback()
{
	s_engine->Update();
    glutPostRedisplay();
}

void Engine::TimerCallback(int id)
{
    SetTimerGLUT();
	s_engine->Update();
    glutPostRedisplay();
}

float Engine::UpdateTime()
{
    return 1.0f / m_config.fps;
}
void Engine::SetTimerGLUT()
{
    glutTimerFunc(1000.0f*s_engine->m_updateTime, &Engine::TimerCallback, 0);
}

}
