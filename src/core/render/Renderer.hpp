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
    Shared<Renderbuffer> m_offRenderbuffer;
    Shared<Mesh2D> m_windowQuad;
    static glm::vec2 s_QuadVertices[4];
    static glm::vec2 s_QuadUvs[4];
    static int s_QuadIndices[6];
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
