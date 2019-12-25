#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <glm/glm.hpp>

// Forward declarations
class Window;
class Camera;

glm::vec3 instersection_of_ray_with_sphere(const glm::vec3& ray, const glm::vec3& ray_origin);
glm::vec3 screen_position_to_ray(const Window& window, const Camera& camera);

#endif
