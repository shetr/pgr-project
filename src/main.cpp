
#include <core/Engine.hpp>
#include <app/App.hpp>

using namespace sadekpet;


int main(int argc, char** argv) {
    int  res;
    App* app = new App();
    Engine::Create(
        EngineArgs({&argc, argv}), 
        EngineConfig({WindowSize({512, 512}), "PGR project", DebugLevel::DEBUG_HIGH, EngineLoop::FIXED_GLUT, 60}),
        app);
    {
        Unique<Engine> engine = Unique<Engine>(Engine::Get());
        res = engine->Run();
    }
    return res;
}