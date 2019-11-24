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

    glm::mat4 look_at() const;

    void set_zoom(const float zoom);
    float zoom() const;

private:

public:
    glm::vec3 position;
    glm::vec3 rotation;

private:
    float m_zoom;
};

#endif
