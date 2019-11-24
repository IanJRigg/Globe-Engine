#include "camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const glm::vec3 ORIGIN(0.0f, 0.0f, 0.0f);
static const glm::vec3 Y_AXIS(0.0f, 1.0f, 0.0f);

/**********************************************************************************************//**
 * \brief Default constructor
 *************************************************************************************************/
Camera::Camera() :
    position(0.0f, 0.0f, 0.0f),
    rotation(0.0f, 0.0f, 0.0f),
    m_zoom(45.0f)
{

}

/**********************************************************************************************//**
 * \brief Default destructor
 *************************************************************************************************/
Camera::~Camera()
{

}

/**********************************************************************************************//**
 * \brief Copy Constructor
 *************************************************************************************************/
Camera::Camera(const Camera& other) :
    position(other.position),
    rotation(other.rotation),
    m_zoom(other.m_zoom)
{

}

/**********************************************************************************************//**
 * \brief Move Constructor
 *************************************************************************************************/
Camera::Camera(Camera&& other) noexcept
{
    *this = std::move(other);
}

/**********************************************************************************************//**
 * \brief Assignment Operator
 *************************************************************************************************/
Camera& Camera::operator=(const Camera& other)
{
    if(this != &other)
    {
        position = other.position;
        rotation = other.rotation;
        m_zoom = other.m_zoom;
    }

    return *this;
}

/**********************************************************************************************//**
 * \brief Move Assignment Operator
 *************************************************************************************************/
Camera& Camera::operator=(Camera&& other) noexcept
{
    if(this != &other)
    {
        position = std::move(other.position);
        rotation = std::move(other.rotation);

        std::swap(m_zoom, other.m_zoom);
    }

    return *this;
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
glm::mat4 Camera::look_at() const
{
    glm::vec3 direction = glm::normalize(position - ORIGIN);
    glm::vec3 right = glm::normalize(glm::cross(Y_AXIS, direction));
    glm::vec3 up = glm::cross(direction, right);

    return glm::lookAt(
        position,
        glm::vec3(0.0f, 0.0f, 0.0f), // position + front
        up
    );
}

/**********************************************************************************************//**
 * \brief
 * \param zoom
 *************************************************************************************************/
void Camera::set_zoom(const float zoom)
{

}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
float Camera::zoom() const
{

}
