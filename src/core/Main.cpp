#include "Main.hpp"

#include "Window.hpp"
#include "Input.hpp"
#include "render/OpenGL.hpp"

#include <iostream>

namespace sadekpet {

Main* Main::s_main = nullptr;

void Main::Create(MainArgs args, MainConfig config, App* app)
{
    if(s_main == nullptr) {
        s_main = new Main(args, config, app);
    }
}
Main* Main::Get()
{
    return s_main;
}

Main::Main(MainArgs args, MainConfig config, App* app)
    : m_args(args), m_config(config), m_app(app)
{
}
Main::~Main()
{
    s_main = nullptr;
}
int Main::Run()
{
    Init();
    glutMainLoop();
    return 0;
}
void Main::Init()
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

    glutDisplayFunc(&Main::DrawCallback);
    glutIdleFunc(&Main::IdleCallback);
}

void Main::Draw()
{
    m_renderer.Clear();
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer& layer = Layers::Get(l);
        for(Pair<uint, VisibleNode*> p : layer.Visible()) {
            m_renderer.Draw(p.second->GetMaterial());
        }
    }
    m_renderer.SwapBuffers();
}

void Main::Update()
{
    m_timer.Measure();
    m_app->Update(m_timer.GetDelta());
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer& layer = Layers::Get(l);
        for(Pair<uint, Node*> p : layer.Roots()) {
            p.second->Update(m_timer.GetDelta());
        }
    }
    UpdateWorldTransfrom();
}

void Main::UpdateWorldTransfrom()
{
    for(size_t l = 0; l < Layers::Count(); l++) {
        Layer& layer = Layers::Get(l);
        for(Pair<uint, Node*> p : layer.Roots()) {
            p.second->UpdateWorldTransform();
        }
    }
}

void Main::DrawCallback()
{
    s_main->Draw();
}
void Main::IdleCallback()
{
    s_main->Update();
    glutPostRedisplay();
}

}
