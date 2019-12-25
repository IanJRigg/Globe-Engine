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
    m_fov(90.0f),
    m_distance_to_near_plane(0.0f),
    m_distance_to_far_plane(0.0f)
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
    m_fov(other.m_fov),
    m_distance_to_near_plane(0.0f),
    m_distance_to_far_plane(0.0f)
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
        m_fov = other.m_fov;
        m_distance_to_near_plane = other.m_distance_to_near_plane;
        m_distance_to_far_plane  = other.m_distance_to_far_plane;
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

        std::swap(m_fov, other.m_fov);
        std::swap(m_distance_to_near_plane, other.m_distance_to_near_plane);
        std::swap(m_distance_to_far_plane,  other.m_distance_to_far_plane);
    }

    return *this;
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
glm::mat4 Camera::view_matrix() const
{
    glm::vec3 direction = glm::normalize(position - ORIGIN);
    glm::vec3 right = glm::normalize(glm::cross(Y_AXIS, direction));
    glm::vec3 up = glm::cross(direction, right);

    return glm::lookAt(position, ORIGIN, up);
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
glm::mat3 Camera::view_matrix_at_origin() const
{
    glm::vec3 direction = glm::normalize(position - ORIGIN);
    glm::vec3 right = glm::normalize(glm::cross(Y_AXIS, direction));
    glm::vec3 up = glm::cross(direction, right);

    return glm::lookAt(glm::vec3(0.0f), ORIGIN, up);
}

/**********************************************************************************************//**
 * \brief
 * \param aspect_ratio
 *************************************************************************************************/
glm::mat4 Camera::projection_matrix(const float aspect_ratio) const
{
    return glm::perspective(
        glm::radians(m_fov),
        aspect_ratio,
        m_distance_to_near_plane,
        m_distance_to_far_plane
    );
}

/**********************************************************************************************//**
 * \brief
 * \param fov
 *************************************************************************************************/
void Camera::set_fov(const float fov)
{
    if(fov >= 0.0f && fov <= 180.0f)
    {
        m_fov = fov;
    }
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
float Camera::fov() const
{
   return m_fov;
}

/**********************************************************************************************//**
 * \brief
 * \param distance
 *************************************************************************************************/
void Camera::set_distance_to_near_plane(const float distance)
{
    m_distance_to_near_plane = distance;
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
float Camera::distance_to_near_plane() const
{
    return m_distance_to_near_plane;
}

/**********************************************************************************************//**
 * \brief
 * \param distance
 *************************************************************************************************/
void Camera::set_distance_to_far_plane(const float distance)
{
    m_distance_to_far_plane = distance;
}

/**********************************************************************************************//**
 * \brief
 *************************************************************************************************/
float Camera::distance_to_far_plane() const
{
    return m_distance_to_far_plane;
}
