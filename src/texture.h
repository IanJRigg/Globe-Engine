#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <glad/glad.h>
#include <string>
#include <vector>

class Texture
{
public:
    Texture();
    virtual ~Texture();

    Texture(Texture& other) = delete;
    Texture(Texture&& other) noexcept;

    Texture& operator=(Texture& other) = delete;
    Texture& operator=(Texture&& other) noexcept;

    void load_jpg(const std::string& path);
    void load_png(const std::string& path);

    void load_cube_map_png(const std::vector<std::string>& paths);

    void bind_with_2D_texture_as_target();
    void bind_with_cube_map_as_target();

    void set_active_texture(const uint32_t texture_unit);

    // S Axis Texture Wrapping
    void set_s_axis_to_repeat();
    void set_s_axis_to_mirrored_repeat();
    void set_s_axis_to_clamp_to_edge();
    void set_s_axis_to_clamp_to_border();

    // T Axis Texture Wrapping
    void set_t_axis_to_repeat();
    void set_t_axis_to_mirrored_repeat();
    void set_t_axis_to_clamp_to_edge();
    void set_t_axis_to_clamp_to_border();

    // R Axis Texture Wrapping
    void set_r_axis_to_repeat();
    void set_r_axis_to_mirrored_repeat();
    void set_r_axis_to_clamp_to_edge();
    void set_r_axis_to_clamp_to_border();

    // Texture Filtering
    void set_minifying_filter_to_nearest();
    void set_minifying_filter_to_linear();
    void set_magnifying_filter_to_nearest();
    void set_magnifying_filter_to_linear();

    // Mipmapping Configuration
    void set_mipmapping_to_nearest_mipmap_nearest();
    void set_mipmapping_to_linear_mipmap_nearest();
    void set_mipmapping_to_nearest_mipmap_linear();
    void set_mipmapping_to_linear_mipmap_linear();

private:
    void load(const std::string& path, const GLenum target, const GLenum format);

private:
    GLuint m_id;
    GLenum m_target;
};

#endif
