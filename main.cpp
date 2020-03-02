
#include <core/Main.hpp>

using namespace sadekpet;

int main(int argc, char** argv) {
    int  res;
    App* app = new App();
    Main::Create({&argc, argv}, {.windowSize = {512, 512}, .windowTitle = "TestName", .debugLevel = DebugLevel::DEBUG_HIGH}, app);
    {
        Unique<Main> main = Unique<Main>(Main::Get());
        res = main->Run();
    }
    return res;
}