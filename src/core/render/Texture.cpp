#include "Texture.hpp"

#include "OpenGL.hpp"

#include "Uniforms.hpp"

namespace sadekpet
{

Texture::Texture(uint8_t* data, TextureChanels chanels) : m_data(data), m_chanels(chanels)
{
    GL(GenTextures(1, &m_id));
}

void Texture::Bind() const
{
    GL(BindTexture(static_cast<uint>(GetType()), m_id));
}

void Texture::Activate(TextureUnit unit)
{
    GL(ActiveTexture(static_cast<uint>(unit)));
}

void Texture::UnBind(TextureType type)
{
    GL(BindTexture(static_cast<uint>(type), 0));
}


void Texture::Init()
{
    GL(TexParameteri(static_cast<uint>(GetType()), GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GL(TexParameteri(static_cast<uint>(GetType()), GL_TEXTURE_MAG_FILTER, GL_LINEAR));

    SetImage();
}

uint Texture::GetFormat()
{
    return static_cast<uint>(m_chanels);
}
uint Texture::GetInternalFormat()
{
    switch (m_chanels)
    {
    case TextureChanels::R:
        return GL_R8;
    case TextureChanels::RG:
        return GL_RG8;
    case TextureChanels::RGB:
        return GL_RGB8;
    case TextureChanels::RGBA:
        return GL_RGBA8;
    default:
        return 0;
    }
}
uint Texture::GetDataType()
{
    return GL_UNSIGNED_BYTE;
}

void Texture1D::SetImage()
{
    GL(TexImage1D(
        static_cast<uint>(GetType()), 
        0, 
        GetInternalFormat(),
        m_width,
        0,
        GetFormat(),
        GetDataType(),
        m_data));
}


void Texture2D::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
    SetImage();
}

void Texture2D::SetImage()
{
    GL(TexImage2D(
        static_cast<uint>(GetType()), 
        0, 
        GetInternalFormat(),
        m_width,
        m_height,
        0,
        GetFormat(),
        GetDataType(),
        m_data));
}

void Texture3D::SetImage()
{
    GL(TexImage3D(
        static_cast<uint>(GetType()), 
        0, 
        GetInternalFormat(),
        m_width,
        m_height,
        m_depht,
        0,
        GetFormat(),
        GetDataType(),
        m_data));
}

void TextureCubeMap::SetImage()
{
    GL(TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL(TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GL(TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
    for(int i = 0; i < 6; i++) {
        uint8_t* data = m_data[i];
        GL(TexImage2D(
        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
        0, 
        GetInternalFormat(),
        m_width,
        m_height,
        0,
        GetFormat(),
        GetDataType(),
        data));
    }
}

void TextureUnits::Activate() const
{
    for(uint i = 0; i < (uint)m_units.size(); i++) {
        const Shared<Texture>& tex = m_units[i];
        uint unitNum = static_cast<uint>(TextureUnit::_0) + i;
        TextureUnit unit = static_cast<TextureUnit>(unitNum);
        tex->Activate(unit);
        tex->Bind();
    }
}

}