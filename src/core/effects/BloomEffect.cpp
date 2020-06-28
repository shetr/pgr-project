#include "BloomEffect.hpp"

#include <core/manage/ShaderManager.hpp>
#include <core/render/OpenGL.hpp>

#include "BlurEffect.hpp"

#include <iostream>

namespace sadekpet {

BloomEffect::BloomEffect(int width, int height) : PostProcessingEffect()
{
    Vector<float> basic_weights({
        0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216
    });
    Vector<float> test_weights({
        0.029749,0.029712,0.029601,0.029416,0.02916,0.028834,0.02844,0.027982,0.027462,0.026885,0.026254,0.025574,0.02485,0.024085,0.023286,0.022457,0.021604,0.020731,0.019844,0.018947
    });
    Vector<float> test_weights2({
        0.060615,	0.060313,	0.059415,	0.05795,	0.055958,	0.053498,	0.050637,	0.047453,	0.044027,	0.040442
    });
    /*
    int weights_count = 20;
    Vector<float> weights(weights_count);
    for(int i = 0; i < weights_count; i++) {
        //weights[i] = 1.0f / (2 * weights_count - 1);
        float v = (float)i / (float) weights_count;
        float sigma2 = 1;
        sigma2 *= sigma2;
        weights[i] = glm::exp(-v*v/(2.0f*sigma2)) / (2.0f * glm::pi<float>() * sigma2);
        std::cout << weights[i] << std::endl;
    }*/

    m_textureSampler = new Uniform<int>("textureSampler", 0);
    m_horizontal = new Uniform<bool>("horizontal", false);
    m_weights = new UniformArray<float>("weights", test_weights2);

    for(int i = 0; i < 2; i++) {
        pingpongFramebuffers[i] = Unique<Framebuffer>(new Framebuffer());
        pingpongFramebuffers[i]->Bind();
        pingpongTextures[i] = Shared<Texture2D>(new Texture2D(width, height, nullptr, TextureChanels::RGB));
        pingpongTextures[i]->Bind();
        pingpongTextures[i]->Init();
        GL(TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GL(TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
        pingpongFramebuffers[i]->AttachTexture2D(pingpongTextures[i], FramebufferColor::_0);
        pingpongFramebuffers[i]->UnBind();
    }

    m_blur = Unique<PostProcessingEffect>(new BlurEffect());
}

void BloomEffect::Run(Shared<Texture2D>& tex1, Shared<Texture2D>& tex2)
{
    int programID = ShaderManager::BindRenderProgram(TypeIndex(typeid(BloomEffect)));
    m_windowQuad->Bind();
    m_textureSampler->Set(programID);
    m_weights->Set(programID);

    bool horizontal = true, first_iteration = true;
    int count = 5;
    int amount = 2*count;
    for (unsigned int i = 0; i < amount; i++)
    {
        pingpongFramebuffers[horizontal]->Bind();
        m_horizontal->value = horizontal;
        m_horizontal->Set(programID);
        Texture2D::Activate(TextureUnit::_0);
        if(first_iteration) {
            tex2->Bind();
        } else {
            pingpongTextures[!horizontal]->Bind();
        }
        GL(DrawElements(static_cast<uint>(m_windowQuad->GetType()), m_windowQuad->GetCount(), GL_UNSIGNED_INT, 0));

        horizontal = !horizontal;
        if (first_iteration)
            first_iteration = false;
    }
    VertexArray::UnBind();
    GraphicsProgram::UnBind();
    Framebuffer::UnBind();

    m_blur->Run(tex1, pingpongTextures[!horizontal]);
}

void BloomEffect::Resize(int width, int height)
{
    for(int i = 0; i < 2; i++) {
        pingpongTextures[i]->Bind();
        pingpongTextures[i]->Resize(width, height);
    }
}

}