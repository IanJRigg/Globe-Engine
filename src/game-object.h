#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>

#include "program.h"

class Game_Object
{
public:
    Game_Object();
    virtual ~Game_Object();

    Game_Object(Game_Object& other) = delete;
    Game_Object(Game_Object&& other) noexcept;

    Game_Object& operator=(Game_Object& other) = delete;
    Game_Object& operator=(Game_Object&& other) noexcept;

private:

private:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    Program program;

    std::vector<std::unique_ptr<Game_Object>> children;
};

#endif
