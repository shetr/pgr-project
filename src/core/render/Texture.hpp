/**
 * @file Texture.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_TEXTURE_HPP
#define PGR_TEXTURE_HPP

#include <core/types.hpp>

namespace sadekpet
{

enum class TextureUnit : uint
{
    _0 = 0x84C0,
    _1 = 0x84C1,
    _2 = 0x84C2,
    _3 = 0x84C3,
    _4 = 0x84C4,
    _5 = 0x84C5,
    _6 = 0x84C6,
    _7 = 0x84C7,
    _8 = 0x84C8,
    _9 = 0x84C9,
    _10 = 0x84CA,
    _11 = 0x84CB,
    _12 = 0x84CC,
    _13 = 0x84CD,
    _14 = 0x84CE,
    _15 = 0x84CF,
    _16 = 0x84D0,
    _17 = 0x84D1,
    _18 = 0x84D2,
    _19 = 0x84D3,
    _20 = 0x84D4,
    _21 = 0x84D5,
    _22 = 0x84D6,
    _23 = 0x84D7,
    _24 = 0x84D8,
    _25 = 0x84D9,
    _26 = 0x84DA,
    _27 = 0x84DB,
    _28 = 0x84DC,
    _29 = 0x84DD,
    _30 = 0x84DE,
    _31 = 0x84DF
};

enum class TextureChanels
{
    R = 0x1903,
    RG = 0x8227,
    RGB = 0x1907,
    RGBA = 0x1908
};

enum class TextureType
{
    _1D = 0x0DE0,
    _2D = 0x0DE1,
    _3D = 0x806F
};

class Texture
{
protected:
    uint8_t* m_data;
    TextureChanels m_chanels;
    uint m_id;
public:
    Texture(uint8_t* data, TextureChanels chanels);

    void Init();
    void Bind() const;
    void Activate(TextureUnit unit) const;

    uint GetID() const { return m_id; }

    static void UnBind(TextureType type);

    virtual TextureType GetType() const = 0;
protected:
    uint GetFormat();
    uint GetInternalFormat();
    uint GetDataType();

    virtual void SetImage() = 0;
};

class Texture1D : public Texture
{
protected:
    int m_width;
public:
    Texture1D(int width, uint8_t* data, TextureChanels chanels)
        : Texture(data, chanels), m_width(width) { }
    inline virtual TextureType GetType() const override { return TextureType::_1D; }
protected:
    void SetImage() override;
};

class Texture2D : public Texture
{
protected:
    int m_width;
    int m_height;
public:
    Texture2D(int width, int height, uint8_t* data, TextureChanels chanels)
        : Texture(data, chanels), m_width(width), m_height(height) { }
    inline virtual TextureType GetType() const override { return TextureType::_2D; }
protected:
    void SetImage() override;
};

class Texture3D : public Texture
{
protected:
    int m_width;
    int m_height;
    int m_depht;
public:
    Texture3D(int width, int height, int depth, uint8_t* data, TextureChanels chanels)
        : Texture(data, chanels), m_width(width), m_height(height), m_depht(depth) { }
    inline virtual TextureType GetType() const override { return TextureType::_3D; }
protected:
    void SetImage() override;
};

class TextureUnits
{
private:
    Vector<Shared<Texture>> m_units;
public:
    TextureUnits(Vector<Shared<Texture>>&& units) : m_units(units) {}
    void Activate() const;
};

}

#endif // PGR_TEXTURE_HPP