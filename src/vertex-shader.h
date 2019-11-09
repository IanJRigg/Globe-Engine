#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Vertex_Shader
{
public:
    Vertex_Shader() :
        m_id(0UL)
    {
        m_id = glCreateShader(GL_VERTEX_SHADER);
    }

    ~Vertex_Shader()
    {
        glDeleteShader(m_id);
    }

    Vertex_Shader(Vertex_Shader& other) = delete;
    Vertex_Shader(Vertex_Shader&& other) noexcept :
        m_id(0UL)
    {
        *this = std::move(other);
    }

    Vertex_Shader& operator=(Vertex_Shader& other) = delete;
    Vertex_Shader& operator=(Vertex_Shader&& other) noexcept
    {
        if(this != &other)
        {
            std::swap(m_id, other.m_id);
        }

        return *this;
    }

    void compile(const std::string& code)
    {
        const char* code_pointer = code.c_str();

        glShaderSource(m_id, 1, &code_pointer, nullptr);
        glCompileShader(m_id);

        check_for_vertex_shader_errors();
    }

    GLuint id() const
    {
        return m_id;
    }

    void attach_to(const GLuint program_id) const
    {
        glAttachShader(program_id, m_id);
    }

private:
    void check_for_vertex_shader_errors()
    {
        GLint success;

        glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            std::string info(1024UL, 0);
            glGetShaderInfoLog(m_id, info.size(), NULL, info.data());
            std::cerr << "Unable to compile vertex shader: " << info << std::endl;
        }
    }

private:
    GLuint m_id;
};

#endif
