#include "program.h"

/**********************************************************************************************//**
 * \brief Default cosntructor
 *************************************************************************************************/
Program::Program() :
    m_id(0UL),
    m_vertex_shaders(),
    m_fragment_shaders()
{
    // Link the shaders
    m_id = glCreateProgram();
}

/**********************************************************************************************//**
 * \brief Default destructor
 *************************************************************************************************/
Program::~Program()
{
    glDeleteProgram(m_id);
}

/**********************************************************************************************//**
 * \brief Move constructor
 * \param other rvalue reference to another program object
 *************************************************************************************************/
Program::Program(Program&& other) noexcept :
    m_id(std::move(other.m_id)),
    m_vertex_shaders(std::move(other.m_vertex_shaders)),
    m_fragment_shaders(std::move(other.m_fragment_shaders))
{
    other.m_id = 0UL;
}

/**********************************************************************************************//**
 * \brief Assignment move operator
 * \param other rvalue reference to another program object
 *************************************************************************************************/
Program& Program::operator=(Program&& other) noexcept
{
    if(this != &other)
    {
        m_id = other.m_id;

        m_vertex_shaders = std::move(other.m_vertex_shaders);
        m_fragment_shaders = std::move(other.m_fragment_shaders);
    }

    return *this;
}

/**********************************************************************************************//**
 * \brief Load the vertex shader at path into a vertex shader object
 * \param path Path to a vertex shader file
 *************************************************************************************************/
void Program::load_vertex_shader(const std::string& path)
{
    std::string code;
    std::ifstream file_stream;

    file_stream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        file_stream.open(path);
        std::stringstream sstream;

        // read file's buffer contents into streams
        sstream << file_stream.rdbuf();

        // close file handlers
        file_stream.close();

        // convert stream into string
        code = sstream.str();

        Vertex_Shader shader;
        shader.compile(code);

        m_vertex_shaders.push_back(std::move(shader));
    }
    catch(const std::ifstream::failure& ex)
    {

    }
}

/**********************************************************************************************//**
 * \brief
 * \param path
 *************************************************************************************************/
void Program::load_fragment_shader(const std::string& path)
{
    std::string code;
    std::ifstream file_stream;

    file_stream.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        file_stream.open(path);
        std::stringstream sstream;

        // read file's buffer contents into streams
        sstream << file_stream.rdbuf();

        // close file handlers
        file_stream.close();

        // convert stream into string
        code = sstream.str();

        Fragment_Shader shader;
        shader.compile(code);

        m_fragment_shaders.push_back(std::move(shader));
    }
    catch(const std::ifstream::failure& ex)
    {

    }
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Program::link() const
{
    for(const auto& vertex_shader : m_vertex_shaders)
    {
        vertex_shader.attach_to(m_id);
    }

    for(const auto& fragment_shader : m_fragment_shaders)
    {
        fragment_shader.attach_to(m_id);
    }

    glLinkProgram(m_id);

    check_for_linking_errors();
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Program::use() const
{
    glUseProgram(m_id);
}

/**********************************************************************************************//**
 * \brief
 * \param name
 * \param value
 *************************************************************************************************/
void Program::set_uniform_integer(const std::string& name, const GLint value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

/**********************************************************************************************//**
 * \brief
 * \param name
 * \param value
 *************************************************************************************************/
void Program::set_uniform_unsigned_integer(const std::string& name, const GLuint value) const
{
    glUniform1ui(glGetUniformLocation(m_id, name.c_str()), value);
}


/**********************************************************************************************//**
 * \brief
 * \param name
 * \param value
 *************************************************************************************************/
void Program::set_uniform_float(const std::string& name, const GLfloat value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

/**********************************************************************************************//**
 * \brief
 * \param name
 * \param value
 *************************************************************************************************/
void Program::set_uniform_mat4(const std::string& name, const glm::mat4& value) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(m_id, name.c_str()), // Uniform location
        1,                                        // Number of matrices
        GL_FALSE,                                 // Transpose? Yes or no
        glm::value_ptr(value)                     // The matrix/matrices
    );
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
void Program::check_for_linking_errors() const
{
    GLint success;

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        std::string info(1024UL, 0);
        glGetProgramInfoLog(m_id, info.size(), NULL, info.data());
        std::cerr << "Unable to link program: " << info << std::endl;
    }
}