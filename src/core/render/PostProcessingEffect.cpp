#include "PostProcessingEffect.hpp"

namespace sadekpet {

glm::vec2 PostProcessingEffect::s_QuadVertices[4] = {
    glm::vec2( 1.0f,-1.0f),
    glm::vec2( 1.0f, 1.0f), 
    glm::vec2(-1.0f, 1.0f),
    glm::vec2(-1.0f,-1.0f)
};
glm::vec2 PostProcessingEffect::s_QuadUvs[4] = {
    glm::vec2( 1.0f, 0.0f),
    glm::vec2( 1.0f, 1.0f), 
    glm::vec2( 0.0f, 1.0f),
    glm::vec2( 0.0f, 0.0f)
};
int PostProcessingEffect::s_QuadIndices[6] = {
    0, 1, 2, 0, 2, 3
};

PostProcessingEffect::PostProcessingEffect()
{
    m_windowQuad = Shared<Mesh2D>(new Mesh2D(4, 6, s_QuadVertices, s_QuadUvs, s_QuadIndices));
}

}