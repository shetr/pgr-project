#include "App.hpp"

#include <iostream>

#include <core/Engine.hpp>
#include <core/Window.hpp>
#include <core/manage/ShaderManager.hpp>
#include <core/manage/TextureManager.hpp>
#include <core/manage/PrimitivesManager.hpp>
#include <core/manage/MaterialManager.hpp>
#include <core/scene/Layers.hpp>
#include <core/scene/Camera.hpp>

#include <app/scene/CameraController.hpp>
#include <app/scene/PlanetarySystem.hpp>
#include <app/scene/Planet.hpp>
#include <app/generate/MeshGen.hpp>
#include <app/scene/ShaderContexts.hpp>
#include <app/testing/Rectangle.hpp>
#include <app/testing/Sphere.hpp>
#include <app/testing/Testing.hpp>
#include <app/scene/Dummy.hpp>
#include <app/scene/Rocket.hpp>
#include <app/scene/PickPlanetController.hpp>
#include <app/scene/Skybox.hpp>
#include <app/scene/GlobalSceneState.hpp>
#include <app/scene/Ufo.hpp>
#include <app/scene/Config.hpp>

namespace sadekpet {

App::App()
{}
App::~App()
{}

void App::Init()
{
    m_mouseEnterHandler = std::make_unique<MouseEnterHandler>(this, &App::OnMouseEnter, Input::Get());
    m_keyEventHandler = std::make_unique<KeyEventHandler>(this, &App::OnKeyPressed, Input::Get());
    m_specialKeyEventHandler = std::make_unique<SpecialKeyEventHandler>(this, &App::OnSpecialKeyPressed, Input::Get());
    ShaderManager::AddRenderProgram(TypeIndex(typeid(RectangleShaderContext)), "rectangle");
    ShaderManager::AddRenderProgram(TypeIndex(typeid(Object3DShaderContext)), "object3D");
    ShaderManager::AddRenderProgram(TypeIndex(typeid(Basic3DShaderContext)), "basic3D");
    ShaderManager::AddRenderProgram(TypeIndex(typeid(Line3DShaderContext)), "line3D");
    ShaderManager::AddRenderProgram(TypeIndex(typeid(SkyboxShaderContext)), "skybox");
    ShaderManager::AddRenderProgram(TypeIndex(typeid(SunShaderContext)), "sun");
    #ifdef PGR_DEBUG
        std::cout << "shaders loaded" << std::endl;
    #endif
    TextureManager::AddTexture2D("perlinSun0.png");
    TextureManager::AddTexture2D("planet1.png");
    TextureManager::AddTexture2D("planet2.png");
    TextureManager::AddTexture2D("planet3.png");
    TextureManager::AddTexture2D("planet4.png");
    TextureManager::AddTexture2D("planet5.png");
    TextureManager::AddTexture2D("planet5_2.png");
    TextureManager::AddTexture2D("planet6.png");
    TextureManager::AddTexture2D("planet6_2.png");
    TextureManager::AddTexture2D("planet7.png");
    TextureManager::AddTexture2D("moon1.png");
    TextureManager::AddTexture2D("moon2.png");
    TextureManager::AddTexture2D("moon3.png");
    TextureManager::AddTexture2D("moon4.png");
    TextureManager::AddTexture2D("moon5.png");
    TextureManager::AddTexture2D("red.png");
    TextureManager::AddTexture2D("ufo.jpg");
    TextureManager::AddTextureCubeMap("space");
    TextureManager::AddTexture3D("perlinSun", {
        "perlinSun0.png", "perlinSun1.png", "perlinSun2.png", "perlinSun3.png", "perlinSun4.png",
        "perlinSun5.png", "perlinSun6.png", "perlinSun7.png", "perlinSun8.png", "perlinSun9.png"
    });
    #ifdef PGR_DEBUG
        std::cout << "textures loaded" << std::endl;
    #endif
    PrimitivesManager::LoadModel("ufo");
    PrimitivesManager::LoadModel("rocket");
    #ifdef PGR_DEBUG
        std::cout << "models loaded" << std::endl;
    #endif
    PrimitivesManager::AddPrimitives("sphere", MeshGen::HardCodedSphere30());
    PrimitivesManager::AddPrimitives("spherePrecise", MeshGen::BasicSphere(200));
    PrimitivesManager::AddPrimitives("cube", MeshGen::BasicCube());
    MaterialManager::LoadMaterial("ufo");
    #ifdef PGR_DEBUG
        std::cout << "assets loaded" << std::endl;
    #endif

    //g_GenTextures();

    GlobalSceneState::pointLight.lightType = LightType::POINT;
    GlobalSceneState::pointLight.position = glm::vec4(0,0,0,1);
    GlobalSceneState::pointLight.specular = glm::vec3(0.05,0.05,0.05);
    GlobalSceneState::pointLight.attenuationConst = 1;
    GlobalSceneState::pointLight.attenuationLin = 0;

    GlobalSceneState::dirLight.specular = glm::vec3(0.4,0.4,0.4);

    GlobalSceneState::spotLight.specular = glm::vec3(0.2,0.2,0.2);
    GlobalSceneState::spotLight.spotCutoff = M_PI / 8;
    GlobalSceneState::spotLight.spotExponent = 30;

    Layer* skyLayer = Layers::Get(Layers::Add("skybox"));
    Layer* layer = Layers::Get(Layers::Add("3D"));

    m_cameraControll = Shared<CameraControll>(new NumericCamControll());
    Camera* camera1 = new PerspectiveCamera(M_PI_2, 0.1f, 1000.0f);
    StaticCamera* statCamera1 = new StaticCamera(camera1);
    statCamera1->AddLayer(skyLayer);
    statCamera1->AddLayer(layer);
    statCamera1->GetTransform().pos = glm::vec3(20.2782, 19.681, 35.4639);
    statCamera1->SideRotation() = 0.599464;
    statCamera1->UpRotation() = -0.61803;

    Camera* camera2 = new PerspectiveCamera(M_PI_2, 0.1f, 1000.0f);
    StaticCamera* statCamera2 = new StaticCamera(camera2);
    statCamera2->AddLayer(skyLayer);
    statCamera2->AddLayer(layer);
    statCamera2->GetTransform().pos = glm::vec3(0, 72.5054, 0);
    statCamera2->SideRotation() = 0;
    statCamera2->UpRotation() = -1.56932;
    
    Camera* camera3 = new PerspectiveCamera(M_PI_2, 0.1f, 1000.0f);
    MovableCamera* movCamera = new MovableCamera(camera3);
    movCamera->AddLayer(skyLayer);
    movCamera->AddLayer(layer);
    movCamera->GetTransform().pos = glm::vec3(20.2782, 19.681, 35.4639);
    movCamera->SideRotation() = 0.599464;
    movCamera->UpRotation() = -0.61803;
    movCamera->MoveSpeed() = 10;
    layer->Add(camera1);
    layer->Add(camera2);
    layer->Add(camera3);
    layer->Add(statCamera1);
    layer->Add(statCamera2);
    layer->Add(movCamera);
    statCamera1->Activate();

    Skybox* skybox = new Skybox("space");
    skyLayer->Add(skybox);

    m_planetarySystemTimeGroup = Shared<TimeGroup>(new TimeGroup());

    Vector<glm::vec3> ufoSplinePoints = {
        glm::vec3(-60,-15, 60),
        glm::vec3(  0,-10, 20),
        glm::vec3( 60,-10, 60),
        glm::vec3( 20, -5,  0),
        glm::vec3( 60, -5,-60),
        glm::vec3(  0,-10,-20),
        glm::vec3(-60,-10,-60),
        glm::vec3(-20,-15,  0)
    };
    Ufo* ufo = new Ufo(ufoSplinePoints, 20, layer, skyLayer, m_planetarySystemTimeGroup);
    layer->Add(ufo);

    m_cameraControll->AddController(statCamera1);
    m_cameraControll->AddController(statCamera2);
    m_cameraControll->AddController(ufo->GetCam());
    m_cameraControll->AddController(movCamera);

    Sun* sun = new Sun(5, 1);
    m_planetarySystem = new PlanetarySystem(sun, movCamera, m_planetarySystemTimeGroup, 100);
    Planet* planet1 = new Planet(0.4, 1, "planet1.png", 2);
    Planet* planet2 = new Planet(0.6, 1, "planet2.png", 1);
    Planet* planet3 = new Planet(0.8, 1, "planet3.png", 0.6);
    Planet* planet4 = new Planet(1.1, 1, "planet4.png", 0.3);
    Planet* planet5 = new Planet(2.0, 1, "planet5.png", "planet5_2.png", 0.2);
    Planet* planet6 = new Planet(1.5, 1, "planet6.png", "planet6_2.png", 0.15);
    Planet* planet7 = new Planet(1.3, 1, "planet7.png", 0.1);
    Orbit* orbit1 = new Orbit(planet1, 20, 0.7, 0.56);
    Orbit* orbit2 = new Orbit(planet2, 25, 0.5);
    Orbit* orbit3 = new Orbit(planet3, 30, 0.3, 1.5);
    Orbit* orbit4 = new Orbit(planet4, 36, 0.2, 3);
    Orbit* orbit5 = new Orbit(planet5, 48, 0.1, 3*M_PI/2);
    Orbit* orbit6 = new Orbit(planet6, 58, 0.08, 3*M_PI/4);
    Orbit* orbit7 = new Orbit(planet7, 70, 0.03, M_PI);
    m_planetarySystem->AddOrbitToSun(orbit1);
    m_planetarySystem->AddOrbitToSun(orbit2);
    m_planetarySystem->AddOrbitToSun(orbit3);
    m_planetarySystem->AddOrbitToSun(orbit4);
    m_planetarySystem->AddOrbitToSun(orbit5);
    m_planetarySystem->AddOrbitToSun(orbit6);
    m_planetarySystem->AddOrbitToSun(orbit7);

    OrbitingObject* moon1 = new OrbitingObject(0.2, 1, "moon1.png", 0.1);
    OrbitingObject* moon2 = new OrbitingObject(0.1, 1, "moon2.png", 0.1);
    OrbitingObject* moon3 = new OrbitingObject(0.3, 1, "moon3.png", 0.1);
    OrbitingObject* moon4 = new OrbitingObject(0.4, 1, "moon4.png", 0.1);
    OrbitingObject* moon5 = new OrbitingObject(0.2, 1, "moon5.png", 0.1);
    Orbit* mOrbit1 = new Orbit(moon1, 2.5, 0.6, 1.56);
    Orbit* mOrbit2 = new Orbit(moon2, 2, 0.6, 0.56);
    Orbit* mOrbit3 = new Orbit(moon3, 3, 0.4, 2.56);
    Orbit* mOrbit4 = new Orbit(moon4, 6, 0.6, 0.36);
    Orbit* mOrbit5 = new Orbit(moon5, 1.5, 1.2, 1.76);
    planet3->ConnectChild(mOrbit1);
    planet4->ConnectChild(mOrbit2);
    planet4->ConnectChild(mOrbit3);
    planet5->ConnectChild(mOrbit4);
    moon4->ConnectChild(mOrbit5);
    m_planetarySystem->AddOrbit(mOrbit1);
    m_planetarySystem->AddOrbit(mOrbit2);
    m_planetarySystem->AddOrbit(mOrbit3);
    m_planetarySystem->AddOrbit(mOrbit4);
    m_planetarySystem->AddOrbit(mOrbit5);

    layer->Add(sun);
    layer->Add(planet1);
    layer->Add(planet2);
    layer->Add(planet3);
    layer->Add(planet4);
    layer->Add(planet5);
    layer->Add(planet6);
    layer->Add(planet7);

    layer->Add(orbit1);
    layer->Add(orbit2);
    layer->Add(orbit3);
    layer->Add(orbit4);
    layer->Add(orbit5);
    layer->Add(orbit6);
    layer->Add(orbit7);

    layer->Add(moon1);
    layer->Add(moon2);
    layer->Add(moon3);
    layer->Add(moon4);
    layer->Add(moon5);

    layer->Add(mOrbit1);
    layer->Add(mOrbit2);
    layer->Add(mOrbit3);
    layer->Add(mOrbit4);
    layer->Add(mOrbit5);

    layer->Add(m_planetarySystem);

    UnordMap<String, Orbit*> planetNames = {
        {"planet1", orbit1},
        {"planet2", orbit2},
        {"planet3", orbit3},
        {"planet4", orbit4},
        {"planet5", orbit5},
        {"planet6", orbit6},
        {"planet7", orbit7},
    };
    m_config = Unique<Config>(new Config(planetNames));
    m_config->Load();


    m_pickPlanetController = Unique<PickPlanetController>(new PickPlanetController({movCamera}, m_cameraControll));
    m_pickPlanetController->AddOrbit(orbit1);
    m_pickPlanetController->AddOrbit(orbit2);
    m_pickPlanetController->AddOrbit(orbit3);
    m_pickPlanetController->AddOrbit(orbit4);
    m_pickPlanetController->AddOrbit(orbit5);
    m_pickPlanetController->AddOrbit(orbit6);
    m_pickPlanetController->AddOrbit(orbit7);

}
void App::Update(float deltaTime)
{
    float inc = 0;
    if(Input::IsSpecialKeyPressed(SpecialKey::DOWN)) {
        inc = -1;
    } else if(Input::IsSpecialKeyPressed(SpecialKey::UP)) {
        inc = 1;
    }
    m_planetarySystemTimeGroup->Speed() += deltaTime * inc;
    if(m_planetarySystemTimeGroup->Speed() < 0) m_planetarySystemTimeGroup->Speed() = 0;

    CameraController* cam = m_cameraControll->GetActive();
    GlobalSceneState::spotLight.position = glm::vec4(cam->GetWorldPos(), 1);
    m_pickPlanetController->Update(deltaTime);
}

void App::OnMouseEnter(const MouseEnterEvent& event)
{
    MousePos pos = Input::GetMousePos();
}

void App::OnKeyPressed(const KeyEvent& event)
{
    if(event.key == 'o') {
        Engine::Exit();
    } else if(event.key == 'n' && event.pressed) {
        m_planetarySystemTimeGroup->Speed() = 0;
    } else if(event.key == 'm' && event.pressed) {
        m_planetarySystemTimeGroup->Speed() = 1;
    } else if(event.key == 'f' && event.pressed) {
        m_useFog = !m_useFog;
        if(m_useFog) {
            GlobalSceneState::fog = 0.025;
        } else {
            GlobalSceneState::fog = 0.001;
        }
    } else if(event.key == 'r' && event.pressed) {
        m_config->Load();
    }
}

void App::OnSpecialKeyPressed(const SpecialKeyEvent& event)
{
    if(event.key == SpecialKey::F2) {
        Engine::Exit();
    }
}

}
