#ifndef BUFFER_CONTROLLER_H
#define BUFFER_CONTROLLER_H

#include <vector>
#include <cstdint>

#include <glad/glad.h>

class Buffer_Controller
{
public:
    Buffer_Controller();
    virtual ~Buffer_Controller();

    Buffer_Controller(Buffer_Controller& other) = delete;
    Buffer_Controller(Buffer_Controller&& other) noexcept;

    Buffer_Controller& operator=(Buffer_Controller& other) = delete;
    Buffer_Controller& operator=(Buffer_Controller&& other) noexcept;

    void bind() const;
    void draw() const;

    void load_array_buffer(const std::vector<float>& vertices);
    void load_element_array_buffer(const std::vector<uint32_t>& indices);

    void set_array_attribute(const uint32_t index,
                             const uint32_t number_of_components,
                             const uint32_t offset);

private:

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
