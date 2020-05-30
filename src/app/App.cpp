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
	std::cout << "shaders" << std::endl;
    TextureManager::AddTexture2D("perlinSun0.png");
    TextureManager::AddTexture2D("planet1.png");
    TextureManager::AddTexture2D("planet2.png");
    TextureManager::AddTexture2D("planet3.png");
    TextureManager::AddTexture2D("planet5.png");
    TextureManager::AddTexture2D("planet6.png");
    TextureManager::AddTexture2D("red.png");
    TextureManager::AddTexture2D("ufo.jpg");
    TextureManager::AddTextureCubeMap("space");
    TextureManager::AddTexture3D("perlinSun", {"perlinSun0.png", "perlinSun1.png", "perlinSun2.png", "perlinSun3.png"});
	std::cout << "textures" << std::endl;
    PrimitivesManager::LoadModel("ufo");
    PrimitivesManager::LoadModel("rocket");
	std::cout << "load models" << std::endl;
    PrimitivesManager::AddPrimitives("sphere", MeshGen::HardCodedSphere30());
    PrimitivesManager::AddPrimitives("spherePrecise", MeshGen::BasicSphere(200));
    PrimitivesManager::AddPrimitives("cube", MeshGen::BasicCube());
    MaterialManager::LoadMaterial("ufo");
    #ifdef PGR_DEBUG
        std::cout << "assets loaded" << std::endl;
    #endif

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
    Camera* camera1 = new PerspectiveCamera(M_PI_2, 0.1f, 200.0f);
    StaticCamera* statCamera1 = new StaticCamera(camera1);
    statCamera1->AddLayer(skyLayer);
    statCamera1->AddLayer(layer);
    statCamera1->GetTransform().pos = glm::vec3(20.2782, 19.681, 35.4639);
    statCamera1->SideRotation() = 0.599464;
    statCamera1->UpRotation() = -0.61803;

    Camera* camera2 = new PerspectiveCamera(M_PI_2, 0.1f, 200.0f);
    StaticCamera* statCamera2 = new StaticCamera(camera2);
    statCamera2->AddLayer(skyLayer);
    statCamera2->AddLayer(layer);
    statCamera2->GetTransform().pos = glm::vec3(0, 47.1616, 0);
    statCamera2->SideRotation() = 0;
    statCamera2->UpRotation() = -1.56932;
    
    Camera* camera3 = new PerspectiveCamera(M_PI_2, 0.1f, 200.0f);
    MovableCamera* movCamera = new MovableCamera(camera3);
    movCamera->AddLayer(skyLayer);
    movCamera->AddLayer(layer);
    movCamera->GetTransform().pos = glm::vec3(20.2782, 19.681, 35.4639);
    movCamera->SideRotation() = 0.599464;
    movCamera->UpRotation() = -0.61803;
    movCamera->MoveSpeed() = 10;
    m_cameraControll->AddController(statCamera1);
    m_cameraControll->AddController(statCamera2);
    m_cameraControll->AddController(movCamera);
    layer->Add(camera1);
    layer->Add(camera2);
    layer->Add(camera3);
    layer->Add(statCamera1);
    layer->Add(statCamera2);
    layer->Add(movCamera);
    statCamera1->Activate();


    Skybox* skybox = new Skybox("space");
    skyLayer->Add(skybox);

    Dummy* ufo = new Dummy("ufo", "ufo.jpg", MaterialManager::GetMaterial("ufo"));
    ufo->GetTransform().pos = glm::vec3(5,-10, 5);
    ufo->GetTransform().scale /= 100;
    ufo->GetTransform().rotAxis = glm::vec3(1,0,0);
    ufo->GetTransform().rotAngle = M_PI/2;
    layer->Add(ufo);

    m_planetarySystemTimeGroup = Shared<TimeGroup>(new TimeGroup());

    Sun* sun = new Sun(5, 1);
    m_planetarySystem = new PlanetarySystem(sun, movCamera, m_planetarySystemTimeGroup, 100);
    Planet* planet1 = new Planet(0.4, 1, "planet1.png", 3);
    Planet* planet2 = new Planet(0.6, 1, "planet2.png", 2);
    Planet* planet3 = new Planet(0.8, 1, "planet3.png", 1);
    Planet* planet5 = new Planet(2.0, 1, "planet5.png", 0.5);
    Planet* planet6 = new Planet(1.5, 1, "planet6.png", 0.3);
    Orbit* orbit1 = new Orbit(planet1, 20, 0.7, 0.56);
    Orbit* orbit2 = new Orbit(planet2, 25, 0.5);
    Orbit* orbit3 = new Orbit(planet3, 30, 0.3, 1.5);
    Orbit* orbit5 = new Orbit(planet5, 40, 0.1, 3*M_PI/2);
    Orbit* orbit6 = new Orbit(planet6, 45, 0.08, 3*M_PI/4);
    m_planetarySystem->AddOrbitToSun(orbit1);
    m_planetarySystem->AddOrbitToSun(orbit2);
    m_planetarySystem->AddOrbitToSun(orbit3);
    m_planetarySystem->AddOrbitToSun(orbit5);
    m_planetarySystem->AddOrbitToSun(orbit6);

    layer->Add(sun);
    layer->Add(planet1);
    layer->Add(planet2);
    layer->Add(planet3);
    layer->Add(planet5);
    layer->Add(planet6);
    layer->Add(orbit1);
    layer->Add(orbit2);
    layer->Add(orbit3);
    layer->Add(orbit5);
    layer->Add(orbit6);
    layer->Add(m_planetarySystem);


    m_pickPlanetController = Unique<PickPlanetController>(new PickPlanetController({movCamera}, m_cameraControll));
    m_pickPlanetController->AddOrbit(orbit1);
    m_pickPlanetController->AddOrbit(orbit2);
    m_pickPlanetController->AddOrbit(orbit3);
    m_pickPlanetController->AddOrbit(orbit5);
    m_pickPlanetController->AddOrbit(orbit6);

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

    CameraController* cam = m_cameraControll->GetActive();
    GlobalSceneState::spotLight.position = glm::vec4(cam->GetWorldPos(), 1);
    m_pickPlanetController->Update(deltaTime);
}

void App::OnMouseEnter(const MouseEnterEvent& event)
{
    MousePos pos = Input::GetMousePos();
    //std::cout << "Mouse in window: " << event.entered << ", pos:" << pos.x << "," << pos.y << std::endl;
}

void App::OnKeyPressed(const KeyEvent& event)
{
    if(event.key == 'o') {
        Engine::Exit();
    } else if(event.key == 'n' && event.pressed) {
        m_planetarySystemTimeGroup->Speed() = 0;
    } else if(event.key == 'm' && event.pressed) {
        m_planetarySystemTimeGroup->Speed() = 1;
    }
}

void App::OnSpecialKeyPressed(const SpecialKeyEvent& event)
{
    if(event.key == SpecialKey::F2) {
        Engine::Exit();
    }
}

}
