#ifndef MESH_H
#define MESH_H

#include <vector>
#include <cstdint>

#include <glad/glad.h>

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();

    Mesh(Mesh& other) = delete;
    Mesh(Mesh&& other) noexcept;

    Mesh& operator=(Mesh& other) = delete;
    Mesh& operator=(Mesh&& other) noexcept;

    void bind() const;
    void unbind() const;

    void draw() const;

    void load_vertex_buffer(const std::vector<float>& vertices);
    void load_vertex_buffer(const float* vertices, const uint32_t length);

    void load_index_buffer(const std::vector<uint32_t>& indices);

    void set_vertex_buffer_attribute(const uint32_t index,
                                     const uint32_t number_of_components,
                                     const uint32_t offset);

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    uint32_t m_vertex_buffer_size;
    uint32_t m_vertex_count;
    uint32_t m_attribute_count;
    uint32_t m_index_count;
};

#endif
