#include "TextureManager.hpp"


#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#include <IL/il.h>

namespace sadekpet {

TextureManager* TextureManager::s_instance = nullptr;
String TextureManager::s_texturesPath = "res/textures/";

TextureManager* TextureManager::Init()
{
    if(s_instance == nullptr) {
        s_instance = new TextureManager();
    }
    return s_instance;
}
TextureManager::~TextureManager()
{
    s_instance = nullptr;
}

bool TextureManager::AddTexture2D(const String& name)
{
    String fileName = s_texturesPath+name;

    ILuint img_id;
    ilGenImages(1, &img_id);
    ilBindImage(img_id);

    ilEnable(IL_ORIGIN_SET);
    ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);

    #ifdef PGR_WINDOWS
        if(ilLoadImage((const wchar_t*)fileName.c_str()) == IL_FALSE) {
    #else
        if(ilLoadImage(fileName.c_str()) == IL_FALSE) {
    #endif
        ilDeleteImages(1, &img_id);
        std::cout << " cannot load image " << fileName << std::endl;
        return false;
    }

    ILint width = ilGetInteger(IL_IMAGE_WIDTH);
    ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
    ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
    unsigned Bpp = ((format == IL_RGBA || format == IL_BGRA) ? 4 : 3);
    char * data = new char[width * height * Bpp];
    ilCopyPixels(0, 0, 0, width, height, 1, Bpp == 4 ? IL_RGBA : IL_RGB, IL_UNSIGNED_BYTE, data);
    ilDeleteImages(1, &img_id);

    Shared<Texture> tex (new Texture2D((int)width, (int)height, (uint8_t*)data, Bpp == 4 ? TextureChanels::RGBA : TextureChanels::RGB));
    tex->Bind();
    tex->Init();
    s_instance->m_textures.insert({name, tex});

    // free our data (they were copied to OpenGL)
    delete [] data;
    return true;
}

bool TextureManager::AddTexture3D(const String& name, const Vector<String>& names2D)
{
    Vector<uint8_t> data;

    int width;
    int height;
    int depth = names2D.size();
    int Bpp;

    for(int i = 0; i < names2D.size(); i++) {
        String fileName = s_texturesPath+names2D[i];
        ILuint img_id;
        ilGenImages(1, &img_id);
        ilBindImage(img_id);

        ilEnable(IL_ORIGIN_SET);
        ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);

        #ifdef PGR_WINDOWS
            if(ilLoadImage((const wchar_t*)fileName.c_str()) == IL_FALSE) {
        #else
            if(ilLoadImage(fileName.c_str()) == IL_FALSE) {
        #endif
            ilDeleteImages(1, &img_id);
            std::cout << " cannot load image " << fileName << std::endl;
            return false;
        }
        ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
        if(i == 0) {
            width = ilGetInteger(IL_IMAGE_WIDTH);
            height = ilGetInteger(IL_IMAGE_HEIGHT);
            Bpp = ((format == IL_RGBA || format == IL_BGRA) ? 4 : 3);
            data.resize(Bpp*width*height*depth);
        }
        ilCopyPixels(0, 0, 0, width, height, 1, Bpp == 4 ? IL_RGBA : IL_RGB, IL_UNSIGNED_BYTE, &data[i*Bpp*width*height]);
        ilDeleteImages(1, &img_id);
    }
    
    Shared<Texture> tex (new Texture3D(width, height, depth, data.data(), Bpp == 4 ? TextureChanels::RGBA : TextureChanels::RGB));
    tex->Bind();
    tex->Init();
    s_instance->m_textures.insert({name, tex});
    return true;
}

bool TextureManager::AddTextureCubeMap(const String& name)
{
    String path = s_texturesPath+name;
    Array<String, 6> fileNames = {
        path+"_px.jpg",
        path+"_nx.jpg",
        path+"_py.jpg",
        path+"_ny.jpg",
        path+"_pz.jpg",
        path+"_nz.jpg"
    };

    Array<uint8_t*, 6> data;
    int width;
    int height;
    int Bpp;

    for(int i = 0; i < data.size(); i++) {
        String fileName = fileNames[i];
        ILuint img_id;
        ilGenImages(1, &img_id);
        ilBindImage(img_id);

        ilEnable(IL_ORIGIN_SET);
        ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);

        #ifdef PGR_WINDOWS
            if(ilLoadImage((const wchar_t*)fileName.c_str()) == IL_FALSE) {
        #else
            if(ilLoadImage(fileName.c_str()) == IL_FALSE) {
        #endif
            ilDeleteImages(1, &img_id);
            std::cout << " cannot load image " << fileName << std::endl;
            return false;
        }
        ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
        if(i == 0) {
            width = ilGetInteger(IL_IMAGE_WIDTH);
            height = ilGetInteger(IL_IMAGE_HEIGHT);
            Bpp = ((format == IL_RGBA || format == IL_BGRA) ? 4 : 3);
        }
        data[i] = new uint8_t[width * height * Bpp];
        ilCopyPixels(0, 0, 0, width, height, 1, Bpp == 4 ? IL_RGBA : IL_RGB, IL_UNSIGNED_BYTE, data[i]);
        ilDeleteImages(1, &img_id);
    }

    Shared<Texture> tex (new TextureCubeMap(width, height, data, Bpp == 4 ? TextureChanels::RGBA : TextureChanels::RGB));
    tex->Bind();
    tex->Init();
    s_instance->m_textures.insert({name, tex});

    for(uint8_t* d : data) {
        delete [] d;
    }

    return true;
}

Shared<Texture> TextureManager::GetTexture(const String& name)
{
    UnordMap<String, Shared<Texture>>::iterator it = s_instance->m_textures.find(name);
    return it->second;
}

void TextureManager::SaveTexture2DRGB(const String& name, int width, int height, uint8_t* data)
{
    SaveTexture2D(name, width, height, data, IL_RGB);
}


void TextureManager::SaveTexture2DRGBA(const String& name, int width, int height, uint8_t* data)
{
    SaveTexture2D(name, width, height, data, IL_RGBA);
}
void TextureManager::SaveTexture2D(const String& name, int width, int height, uint8_t* data, int type)
{
    String location = s_texturesPath + name;
    ILuint img_id;
    ilEnable(IL_ORIGIN_SET);
    ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);
    ilEnable(IL_FILE_OVERWRITE);
    ilGenImages(1, &img_id);
    ilBindImage(img_id);

    ilTexImage(width, height, 1, type == IL_RGB ? 3 : 4, type, IL_UNSIGNED_BYTE, data);
    #ifdef PGR_WINDOWS
        ilSaveImage((const wchar_t*)location.c_str());
    #else
        ilSaveImage(location.c_str());
    #endif
    ilDeleteImages(1, &img_id);
}

TextureManager::TextureManager()
{
}

}