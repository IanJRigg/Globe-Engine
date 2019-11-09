#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

class Texture_2D
{
public:
    Texture_2D() :
        m_id(0UL)
    {
        glGenTextures(1, &m_id);
    }

    ~Texture_2D()
    {
        glDeleteTextures(1, &m_id);
    }

    Texture_2D(Texture_2D& other) = delete;
    Texture_2D(Texture_2D&& other) noexcept :
        m_id(other.m_id)
    {
        other.m_id = 0UL;
    }

    Texture_2D& operator=(Texture_2D& other) = delete;
    Texture_2D& operator=(Texture_2D&& other) noexcept
    {
        if(this != &other)
        {
            m_id = other.m_id;

            other.m_id = 0UL;
        }

        return *this;
    }

    void load_jpg(const std::string& path)
    {
        this->load(path, GL_RGB);
    }

    void load_png(const std::string& path)
    {
        this->load(path, GL_RGBA);
    }

    void bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_id);
    }

    void set_active_texture(const uint32_t texture_unit)
    {
        glActiveTexture(texture_unit);
    }

    // S Axis Texture Wrapping
    void set_s_axis_to_repeat()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    }

    void set_s_axis_to_mirrored_repeat()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    }

    void set_s_axis_to_clamp_to_edge()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    }

    void set_s_axis_to_clamp_to_border()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    }

    // T Axis Texture Wrapping
    void set_t_axis_to_repeat()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    void set_t_axis_to_mirrored_repeat()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    }

    void set_t_axis_to_clamp_to_edge()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    void set_t_axis_to_clamp_to_border()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    }

    // Texture Filtering
    void set_minifying_filter_to_nearest()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    }

    void set_minifying_filter_to_linear()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }

    void set_magnifying_filter_to_nearest()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    void set_magnifying_filter_to_linear()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    // Mipmapping Configuration
    void set_mipmapping_to_nearest_mipmap_nearest()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    }

    void set_mipmapping_to_linear_mipmap_nearest()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    }

    void set_mipmapping_to_nearest_mipmap_linear()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    }

    void set_mipmapping_to_linear_mipmap_linear()
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    }

private:
    void load(const std::string& path, const GLenum format)
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
                GL_TEXTURE_2D,        // texture target
                0,                    // mipmap level
                format,               // destination format
                width,                // width
                height,               // height
                0,                    // always zero (legacy code)
                format,               // source format
                GL_UNSIGNED_BYTE,     // source data type
                data                  // source
            );
            glGenerateMipmap(GL_TEXTURE_2D);
            stbi_image_free(data);
        }
        else
        {
            // Throw exception?
        }
    }

private:
    GLuint m_id;
};

#endif
