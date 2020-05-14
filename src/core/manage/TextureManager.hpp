
#ifndef PGR_TEXTURE_MANAGER_HPP
#define PGR_TEXTURE_MANAGER_HPP

#include <core/render/Texture.hpp>

namespace sadekpet {

class TextureManager
{
private:
    static TextureManager* s_instance;
    static String s_texturesPath;
    UnordMap<String, TextureUnitStorage> m_textures;
public:
    static TextureManager* Init();
    ~TextureManager();
    static bool AddTexture(const String& name);
    static TextureUnitStorage GetTexture(const String& name);

private:
    TextureManager();
};

}

#endif // PGR_TEXTURE_MANAGER_HPP