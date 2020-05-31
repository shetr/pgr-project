
#ifndef PGR_TEXTURE_MANAGER_HPP
#define PGR_TEXTURE_MANAGER_HPP

#include <core/render/Texture.hpp>

namespace sadekpet {

class TextureManager
{
private:
    static TextureManager* s_instance;
    static String s_texturesPath;
    UnordMap<String, Shared<Texture>> m_textures;
public:
    static TextureManager* Init();
    ~TextureManager();
    static bool AddTexture2D(const String& name);
    static bool AddTexture3D(const String& name, const Vector<String>& names2D);
    static bool AddTextureCubeMap(const String& name);
    static Shared<Texture> GetTexture(const String& name);
    static void SaveTexture2DRGB(const String& name, int width, int height, uint8_t* data);
    static void SaveTexture2DRGBA(const String& name, int width, int height, uint8_t* data);
    static void SaveTexture2D(const String& name, int width, int height, uint8_t* data, int type);

private:
    TextureManager();
};

}

#endif // PGR_TEXTURE_MANAGER_HPP