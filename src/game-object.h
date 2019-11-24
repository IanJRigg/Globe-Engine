#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm/glm.hpp>

class Game_Object
{
public:
    /**********************************************************************************************//**
     * \brief Default constructor
     *************************************************************************************************/
    Game_Object() :
        position(0.0f, 0.0f, 0.0f),
        rotation(0.0f, 0.0f, 0.0f),
        scale(1.0f, 1.0f, 1.0f)
    {

    }

    /**********************************************************************************************//**
     * \brief Default destructor
     *************************************************************************************************/
    virtual ~Game_Object() = default;

    /**********************************************************************************************//**
     * \brief Copy Constructor
     *************************************************************************************************/
    Game_Object(Game_Object& other) :
        position(other.position),
        rotation(other.rotation),
        scale(other.scale)
    {

    }

    /**********************************************************************************************//**
     * \brief Move Constructor
     *************************************************************************************************/
    Game_Object(Game_Object&& other) noexcept
    {
        *this = std::move(other);
    }

    /**********************************************************************************************//**
     * \brief Assignment operator
     *************************************************************************************************/
    Game_Object& operator=(Game_Object& other)
    {
        if(this != &other)
        {
            position = other.position;
            rotation = other.rotation;
            scale    = other.scale;
        }

        return *this;
    }

    /**********************************************************************************************//**
     * \brief Move assignment operator
     *************************************************************************************************/
    Game_Object& operator=(Game_Object&& other) noexcept
    {
        if(this != &other)
        {
            position = std::move(other.position);
            rotation = std::move(other.rotation);
            scale    = std::move(other.scale);
        }

        return *this;
    }

public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif
