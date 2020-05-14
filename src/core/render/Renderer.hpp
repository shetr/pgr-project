/**
 * @file Renderer.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_RENDERER_HPP
#define PGR_RENDERER_HPP

#include <core/Window.hpp>
#include <core/manage/ShaderManager.hpp>

namespace sadekpet {

class Renderer
{
    using WindowSizeHandler = ScopedEventHandler<WindowSizeEvent, Renderer>;
private:
    Unique<WindowSizeHandler> m_windowSizeHandler;
public:
    Renderer();
    ~Renderer();

    void SetClearColor(glm::vec4 color);

    void Init();
    void Clear();
    void SwapBuffers();

    void Draw(ShaderContext& shaderContext);


    void OnWindowResize(const WindowSizeEvent& event);
};

}

#endif // PGR_RENDERER_HPP
