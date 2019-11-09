#include "buffer-controller.h"

#include <iostream>
#include <iomanip>

/**********************************************************************************************//**
 * \brief Default constructor
 *************************************************************************************************/
Buffer_Controller::Buffer_Controller() :
    m_vao(0U),
    m_vbo(0U),
    m_ebo(0U),
    m_vertex_buffer_size(0UL),
    m_vertex_count(0UL),
    m_attribute_count(0UL),
    m_index_count(0UL)
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);
}

/**********************************************************************************************//**
 * \brief Default destructor
 *************************************************************************************************/
Buffer_Controller::~Buffer_Controller()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

/**********************************************************************************************//**
 * \brief Move constructor
 * \param other rvalue reference to another program object
 *************************************************************************************************/
Buffer_Controller::Buffer_Controller(Buffer_Controller&& other) noexcept :
    m_vao(0U),
    m_vbo(0U),
    m_ebo(0U),
    m_vertex_buffer_size(0UL),
    m_vertex_count(0UL),
    m_attribute_count(0UL),
    m_index_count(0UL)
{
    *this = std::move(other);
}

/**********************************************************************************************//**
 * \brief Move assignment operator
 * \param other rvalue reference to another program object
 *************************************************************************************************/
Buffer_Controller& Buffer_Controller::operator=(Buffer_Controller&& other) noexcept
{
    if(this != &other)
    {
        std::swap(m_vao, other.m_vao);
        std::swap(m_vbo, other.m_vbo);
        std::swap(m_ebo, other.m_ebo);
        std::swap(m_vertex_buffer_size, other.m_vertex_buffer_size);
        std::swap(m_vertex_count, other.m_vertex_count);
        std::swap(m_attribute_count, other.m_attribute_count);
        std::swap(m_index_count, other.m_index_count);
    }

    return *this;
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Buffer_Controller::bind() const
{
    glBindVertexArray(m_vao);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Buffer_Controller::draw() const
{
    if(m_index_count == 0)
    {
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
    }
    else
    {
        glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
void Buffer_Controller::load_array_buffer(const std::vector<float>& vertices)
{
    m_vertex_buffer_size = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer_size * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

/**********************************************************************************************//**
 * \brief
 * \param indices
 *************************************************************************************************/
void Buffer_Controller::load_element_array_buffer(const std::vector<uint32_t>& indices)
{
    m_index_count = indices.size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
}

/**********************************************************************************************//**
 * \brief
 * \param index
 * \param size
 * \param offset
 *************************************************************************************************/
void Buffer_Controller::set_array_attribute(const uint32_t index,
                                            const uint32_t size,
                                            const uint32_t offset)
{
    glVertexAttribPointer(index,
                          size,
                          GL_FLOAT,
                          GL_FALSE,
                          8 * sizeof(float),
                          (void*)(offset * sizeof(float))
    );

    glEnableVertexAttribArray(index);

    m_attribute_count += size;
    m_vertex_count = m_vertex_buffer_size / m_attribute_count;
}
