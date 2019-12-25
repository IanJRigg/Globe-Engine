#include "raycaster.h"

#include "camera.h"
#include "window.h"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

static const glm::vec3 ALL_ZERO_VEC3(0.0f, 0.0f, 0.0f);
#define ORIGIN ALL_ZERO_VEC3

static const float FORWARD_Z        = -1.0f;
static const float HOMOGENOUS_W     =  1.0f;
static const float NON_HOMOGENOUS_W =  0.0f;

/**********************************************************************************************//**
 * \brief
 * \param a
 * \param b
 * \param c
 * \param solution
 * \return
 *************************************************************************************************/
bool intersection_exists(const float a, const float b, const float c, float& first_intersection)
{
    float discriminant = (b * b) - (4 * a * c); // b^2 - 4AC

    if (discriminant > 0)
    {
        float q = (b > 0)
            ? (-0.5 * (b + sqrt(discriminant)))
            : (-0.5 * (b - sqrt(discriminant)));

        float first  = q / a;
        float second = c / q;

        // Return the smaller solution, as it will be closer to the sphere
        first_intersection = (first < second) ? first : second;

        return true;
    }
    else
    {
        // Either there are no intersections, or there is one point tangent to the sphere
        return false;
    }
}

/**********************************************************************************************//**
 * \brief
 * \param ray A normalized ray
 * \param ray_origin
 *************************************************************************************************/
glm::vec3 instersection_of_ray_with_sphere(const glm::vec3& ray, const glm::vec3& ray_origin)
{
    float first_intersection = 0.0f;

    // Setup the quadratic variables, A,mB, and C
    float a = 1.0f; // optimization: the dot product of a normalized vector with itself is 1.0f
    float b = 2 * glm::dot(ray, ray_origin);
    float c = glm::dot(ray_origin, ray_origin) - 1.0f; // Sphere is unit sphere, hence 1.0f

    if(intersection_exists(a, b, c, first_intersection))
    {
        // O + dt
        return ray_origin + ray * first_intersection;
    }
    else
    {
        return ALL_ZERO_VEC3;
    }
}

/**********************************************************************************************//**
 * \brief
 * \param window
 * \param camera
 *************************************************************************************************/
glm::vec3 screen_position_to_ray(const Window& window, const Camera& camera)
{
    // Instructions for writing ths found here: http://antongerdelan.net/opengl/raycasting.html


    // Normalize Device Coordinates: Convert positions from [0, width or height] to [-1, 1]
    float normalized_x = (2.0f * window.mouse_x_position()) / (window.width()) - 1.0f;
    float normalized_y = 1.0f - (2.0f * window.mouse_y_position()) / (window.height());

    // Generate Homogenous Clip Coordinates
    glm::vec4 ray_clip_coordinates(normalized_x, normalized_y, FORWARD_Z, HOMOGENOUS_W);

    // Generate Camera Coordinates
    glm::mat4 projection = camera.projection_matrix(window.aspect_ratio());
    glm::vec4 ray_camera_coordinates = glm::inverse(projection) * ray_clip_coordinates;

    ray_camera_coordinates = glm::vec4(
        ray_camera_coordinates.x,
        ray_camera_coordinates.y,
        FORWARD_Z,
        NON_HOMOGENOUS_W
    );

    // Convert to World Coordinates
    glm::vec3 world_coordinates(glm::inverse(camera.view_matrix()) * ray_camera_coordinates);

    return glm::normalize(glm::vec3(world_coordinates));
}
