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

#include "Framebuffer.hpp"
#include "Renderbuffer.hpp"
#include "Texture.hpp"
#include "ShaderContext.hpp"
#include "Primitives.hpp"
#include "PostProcessingEffect.hpp"

namespace sadekpet {

/**
 * @brief Stará se o základní opengl příkazy na vykreslování.
 */
class Renderer
{
    using WindowSizeHandler = ScopedEventHandler<WindowSizeEvent, Renderer>;
private:
    Unique<WindowSizeHandler> m_windowSizeHandler;
    Unique<Framebuffer> m_offFramebuffer;
    Shared<Texture2D> m_offTexture;
    Shared<Texture2D> m_offBrightTexture;
    Shared<Renderbuffer> m_offRenderbuffer;
    Unique<PostProcessingEffect> m_effect;
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

    void StartScene();
    void EndScene();

    void OnWindowResize(const WindowSizeEvent& event);
};

}

#endif // PGR_RENDERER_HPP
