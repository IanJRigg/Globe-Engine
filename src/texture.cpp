#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

/**********************************************************************************************//**
 * \brief Default cosntructor
 *************************************************************************************************/
Texture::Texture() :
    m_id(0UL),
    m_target(GL_INVALID_ENUM)
{
    glGenTextures(1, &m_id);
}

/**********************************************************************************************//**
 * \brief Default destructor
 *************************************************************************************************/
Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

/**********************************************************************************************//**
 * \brief Move constructor
 * \param other rvalue reference to another texture object
 *************************************************************************************************/
Texture::Texture(Texture&& other) noexcept
{
    *this = std::move(other);
}

/**********************************************************************************************//**
 * \brief Assignment move operator
 * \param other rvalue reference to another texture object
 *************************************************************************************************/
Texture& Texture::operator=(Texture&& other) noexcept
{
    if(this != &other)
    {
        std::swap(m_id, other.m_id);
        std::swap(m_target, other.m_target);
    }

    return *this;
}

/**********************************************************************************************//**
 * \brief
 * \param path
 *************************************************************************************************/
void Texture::load_jpg(const std::string& path)
{
    this->load(path, GL_TEXTURE_2D, GL_RGB);
}

/**********************************************************************************************//**
 * \brief
 * \param path
 *************************************************************************************************/
void Texture::load_png(const std::string& path)
{
    this->load(path, GL_TEXTURE_2D, GL_RGBA);
}

/**********************************************************************************************//**
 * \brief
 * \param path
 *************************************************************************************************/
void Texture::load_cube_map_png(const std::string& path)
{
    this->load(path, GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_RGBA);
    this->load(path, GL_TEXTURE_CUBE_MAP_NGEATIVE_X, GL_RGBA);
    this->load(path, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, GL_RGBA);
    this->load(path, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_RGBA);
    this->load(path, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, GL_RGBA);
    this->load(path, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, GL_RGBA);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::bind_with_2D_texture_as_target() const
{
    m_target = GL_TEXTURE_2D;
    glBindTexture(m_target, m_id);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::bind_with_cube_map_as_target() const
{
    m_target = GL_TEXTURE_CUBE_MAP;
    glBindTexture(m_target, m_id);
}

/**********************************************************************************************//**
 * \brief
 * \param texture_unit
 *************************************************************************************************/
void Texture::set_active_texture(const uint32_t texture_unit)
{
    glActiveTexture(texture_unit);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_s_axis_to_repeat()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_s_axis_to_mirrored_repeat()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_s_axis_to_clamp_to_edge()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_s_axis_to_clamp_to_border()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_t_axis_to_repeat()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_t_axis_to_mirrored_repeat()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_t_axis_to_clamp_to_edge()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_t_axis_to_clamp_to_border()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_r_axis_to_repeat()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_REPEAT);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_r_axis_to_mirrored_repeat()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_MIRRORED_REPEAT);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_r_axis_to_clamp_to_edge()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_r_axis_to_clamp_to_border()
{
    glTexParameteri(m_target, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_minifying_filter_to_nearest()
{
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_minifying_filter_to_linear()
{
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_magnifying_filter_to_nearest()
{
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_magnifying_filter_to_linear()
{
    glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_mipmapping_to_nearest_mipmap_nearest()
{
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_mipmapping_to_linear_mipmap_nearest()
{
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_mipmapping_to_nearest_mipmap_linear()
{
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Texture::set_mipmapping_to_linear_mipmap_linear()
{
    glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
}

/**********************************************************************************************//**
 * \brief
 * \param path
 * \param format
 *************************************************************************************************/
void Texture::load(const std::string& path, const GLenum target, const GLenum format)
{
    // Load image, create
    int width = 0L;
    int height = 0L;
    int nrChannels = 0L;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if(data != nullptr)
    {
        glTexImage2D(
            target,             // texture target
            0,                    // mipmap level
            format,               // destination format
            width,                // width
            height,               // height
            0,                    // always zero (legacy code)
            format,               // source format
            GL_UNSIGNED_BYTE,     // source data type
            data                  // source
        );
        glGenerateMipmap(m_target);
        stbi_image_free(data);
    }
    else
    {
        // Throw exception?
    }
}