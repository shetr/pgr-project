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

/**
 * @brief Stará se o základní opengl příkazy na vykreslování.
 */
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
    void ClearDepth();
    void DepthMask(bool enable);
    void SwapBuffers();

    void SetStencilID(uint8_t id);
    void Draw(ShaderContext& shaderContext);


    void OnWindowResize(const WindowSizeEvent& event);
};

}

#endif // PGR_RENDERER_HPP
