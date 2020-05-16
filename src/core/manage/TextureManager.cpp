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
    ilGenImages(1, &img_id); // generate one image ID (name)
    ilBindImage(img_id); // bind that generated id

    // set origin to LOWER LEFT corner (the orientation which OpenGL uses)
    ilEnable(IL_ORIGIN_SET);
    ilSetInteger(IL_ORIGIN_MODE, IL_ORIGIN_LOWER_LEFT);

    // this will load image data to the currently bound image
    if(ilLoadImage(fileName.c_str()) == IL_FALSE) {
        ilDeleteImages(1, &img_id);
        std::cout << " cannot load image " << fileName << std::endl;
        return false;
    }

    // if the image was correctly loaded, we can obtain some informatins about our image
    ILint width = ilGetInteger(IL_IMAGE_WIDTH);
    ILint height = ilGetInteger(IL_IMAGE_HEIGHT);
    ILenum format = ilGetInteger(IL_IMAGE_FORMAT);
    // there are many possible image formats and data types
    // we will convert all image types to RGB or RGBA format, with one byte per channel
    unsigned Bpp = ((format == IL_RGBA || format == IL_BGRA) ? 4 : 3);
    char * data = new char[width * height * Bpp];
    // this will convert image to RGB or RGBA, one byte per channel and store data to our array
    ilCopyPixels(0, 0, 0, width, height, 1, Bpp == 4 ? IL_RGBA : IL_RGB, IL_UNSIGNED_BYTE, data);
    // image data has been copied, we dont need the DevIL object anymore
    ilDeleteImages(1, &img_id);

    // bogus ATI drivers may require this call to work with mipmaps
    //glEnable(GL_TEXTURE_2D);

    Shared<Texture> tex (new Texture2D((int)width, (int)height, (uint8_t*)data, Bpp == 4 ? TextureChanels::RGBA : TextureChanels::RGB));
    tex->Bind();
    tex->Init();
    s_instance->m_textures.insert({name, tex});

    // free our data (they were copied to OpenGL)
    delete [] data;
    return true;
}

Shared<Texture> TextureManager::GetTexture(const String& name)
{
    UnordMap<String, Shared<Texture>>::iterator it = s_instance->m_textures.find(name);
    return it->second;
}

TextureManager::TextureManager()
{
}

}