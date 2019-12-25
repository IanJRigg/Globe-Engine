#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    virtual ~Camera();

    Camera(const Camera& other);
    Camera(Camera&& other) noexcept;

    Camera& operator=(const Camera& other);
    Camera& operator=(Camera&& other) noexcept;

    glm::mat4 view_matrix() const;
    glm::mat3 view_matrix_at_origin() const;
    glm::mat4 projection_matrix(const float aspect_ratio) const;

    void set_fov(const float zoom);
    float fov() const;

    void set_distance_to_near_plane(const float distance);
    float distance_to_near_plane() const;

    void set_distance_to_far_plane(const float distance);
    float distance_to_far_plane() const;

private:

public:
    glm::vec3 position;
    glm::vec3 rotation;

private:
    float m_fov;
    float m_distance_to_near_plane;
    float m_distance_to_far_plane;
};

#endif
