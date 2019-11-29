#include "mesh.h"

#include <iostream>
#include <iomanip>

/**********************************************************************************************//**
 * \brief Default constructor
 *************************************************************************************************/
Mesh::Mesh() :
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
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

/**********************************************************************************************//**
 * \brief Move constructor
 * \param other rvalue reference to another program object
 *************************************************************************************************/
Mesh::Mesh(Mesh&& other) noexcept :
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
Mesh& Mesh::operator=(Mesh&& other) noexcept
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
void Mesh::bind() const
{
    glBindVertexArray(m_vao);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Mesh::unbind() const
{
    glBindVertexArray(0);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Mesh::draw() const
{
    if(m_index_count == 0)
    {
        //glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glDrawArrays(GL_TRIANGLES, 0, m_vertex_count);
    }
    else
    {
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
void Mesh::load_vertex_buffer(const std::vector<float>& vertices)
{
    m_vertex_buffer_size = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer_size * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
void Mesh::load_vertex_buffer(const float* vertices, const uint32_t length)
{
    m_vertex_buffer_size = length;

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertex_buffer_size * sizeof(float), vertices, GL_STATIC_DRAW);
}

/**********************************************************************************************//**
 * \brief
 * \param indices
 *************************************************************************************************/
void Mesh::load_index_buffer(const std::vector<uint32_t>& indices)
{
    m_index_count = indices.size();

    // TODO: The stride needs to be updated for every element

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_index_count * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
}

/**********************************************************************************************//**
 * \brief
 * \param index
 * \param size
 * \param offset
 *************************************************************************************************/
void Mesh::set_vertex_buffer_attribute(const uint32_t index,
                                       const uint32_t size,
                                       const uint32_t offset)
{
    m_attribute_count += size;
    m_vertex_count = m_vertex_buffer_size / m_attribute_count;

    glVertexAttribPointer(index,
                          size,
                          GL_FLOAT,
                          GL_FALSE,
                          m_attribute_count * sizeof(float),
                          (void*)(offset * sizeof(float))
    );

    glEnableVertexAttribArray(index);
}
