#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "vertex-shader.h"
#include "fragment-shader.h"

#include <string>
#include <iostream>
#include <vector>
#include <filesystem>

class Program
{
public:
    Program();
    virtual ~Program();

    Program(Program& other) = delete;
    Program(Program&& other) noexcept;

    Program& operator=(Program& other) = delete;
    Program& operator=(Program&& other) noexcept;

    void load_directory(const std::filesystem::path& path);

    void load_vertex_shader(const std::string& path);
    void load_fragment_shader(const std::string& path);

    void link() const;
    void use() const;

    void set_uniform_integer(const std::string& name, const GLint value) const;
    void set_uniform_unsigned_integer(const std::string& name, const GLuint value) const;
    void set_uniform_float(const std::string& name, const GLfloat value) const;
    void set_uniform_mat4(const std::string& name, const glm::mat4& value) const;

private:
    void check_for_linking_errors() const;

private:
    GLuint m_id;

    std::vector<Vertex_Shader>   m_vertex_shaders;
    std::vector<Fragment_Shader> m_fragment_shaders;
};

#endif
