#include "planet-generator.h"
#include <glm/glm.hpp>

static const uint32_t FRONT_FACE_START_INDEX  = 0UL;
static const uint32_t BACK_FACE_START_INDEX   = 1UL;
static const uint32_t LEFT_FACE_START_INDEX   = 2UL;
static const uint32_t RIGHT_FACE_START_INDEX  = 3UL;
static const uint32_t TOP_FACE_START_INDEX    = 4UL;
static const uint32_t BOTTOM_FACE_START_INDEX = 5UL;

#include <iostream>

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
static void generate_front_face(std::vector<float>& vertices,
                                std::vector<uint32_t>& indices,
                                const uint32_t vertices_per_side)
{
    float step = 1.0 / (vertices_per_side - 1UL);
    uint32_t n = (vertices_per_side * vertices_per_side * 3) * FRONT_FACE_START_INDEX;

    glm::vec3 temp;

    for(uint32_t i = 0; i < vertices_per_side; i++)
    {
        for(uint32_t j = 0; j < vertices_per_side; j++)
        {
            temp.x = j * step - 0.5f; // X
            temp.y = i * step - 0.5f; // Y
            temp.z = 0.5f;            // Z

            temp = glm::normalize(temp);

            vertices.at(n + 0UL) = temp.x;
            vertices.at(n + 1UL) = temp.y;
            vertices.at(n + 2UL) = temp.z;

            n += 3UL;
        }
    }

    n = ((vertices_per_side - 1UL)  * (vertices_per_side - 1UL) * 6UL) * FRONT_FACE_START_INDEX;
    uint32_t offset = vertices_per_side * vertices_per_side * FRONT_FACE_START_INDEX;

    for(uint32_t i = 0; i < vertices_per_side - 1; ++i)
    {
        for(uint32_t j = 0; j < vertices_per_side - 1; ++j)
        {
            indices.at(n + 0UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 1UL) = offset + (i * vertices_per_side) + j + 1UL; // Y
            indices.at(n + 2UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Z

            indices.at(n + 3UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 4UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Y
            indices.at(n + 5UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 0UL); // Z

            n += 6UL;
        }
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
static void generate_back_face(std::vector<float>& vertices,
                               std::vector<uint32_t>& indices,
                               const uint32_t vertices_per_side)
{
    float step = 1.0 / (vertices_per_side - 1UL);
    uint32_t n = (vertices_per_side * vertices_per_side * 3) * BACK_FACE_START_INDEX;

    glm::vec3 temp;

    for(uint32_t i = 0; i < vertices_per_side; i++)
    {
        for(uint32_t j = 0; j < vertices_per_side; j++)
        {
            temp.x = 1.0f - (j * step) - 0.5f; // X
            temp.y = i * step - 0.5f; // Y
            temp.z = -0.5f;            // Z

            temp = glm::normalize(temp);

            vertices.at(n + 0UL) = temp.x;
            vertices.at(n + 1UL) = temp.y;
            vertices.at(n + 2UL) = temp.z;

            n+= 3UL;
        }
    }

    n = ((vertices_per_side - 1UL)  * (vertices_per_side - 1UL) * 6UL) * BACK_FACE_START_INDEX;
    uint32_t offset = vertices_per_side * vertices_per_side * BACK_FACE_START_INDEX;

    for(uint32_t i = 0; i < vertices_per_side - 1; ++i)
    {
        for(uint32_t j = 0; j < vertices_per_side - 1; ++j)
        {
            indices.at(n + 0UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 1UL) = offset + (i * vertices_per_side) + j + 1UL; // Y
            indices.at(n + 2UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Z

            indices.at(n + 3UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 4UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Y
            indices.at(n + 5UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 0UL); // Z

            n += 6UL;
        }
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
static void generate_left_face(std::vector<float>& vertices,
                               std::vector<uint32_t>& indices,
                               const uint32_t vertices_per_side)
{
    float step = 1.0 / (vertices_per_side - 1UL);
    uint32_t n = (vertices_per_side * vertices_per_side * 3) * LEFT_FACE_START_INDEX;

    glm::vec3 temp;

    for(uint32_t i = 0; i < vertices_per_side; i++)
    {
        for(uint32_t j = 0; j < vertices_per_side; j++)
        {
            temp.x = -0.5f;           // X
            temp.y = i * step - 0.5f; // Y
            temp.z = j * step - 0.5f; // Z

            temp = glm::normalize(temp);

            vertices.at(n + 0UL) = temp.x;
            vertices.at(n + 1UL) = temp.y;
            vertices.at(n + 2UL) = temp.z;

            n += 3UL;
        }
    }

    n = ((vertices_per_side - 1UL)  * (vertices_per_side - 1UL) * 6UL) * LEFT_FACE_START_INDEX;
    uint32_t offset = vertices_per_side * vertices_per_side * LEFT_FACE_START_INDEX;

    for(uint32_t i = 0; i < vertices_per_side - 1; ++i)
    {
        for(uint32_t j = 0; j < vertices_per_side - 1; ++j)
        {
            indices.at(n + 0UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 1UL) = offset + (i * vertices_per_side) + j + 1UL; // Y
            indices.at(n + 2UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Z

            indices.at(n + 3UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 4UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Y
            indices.at(n + 5UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 0UL); // Z

            n += 6UL;
        }
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
static void generate_right_face(std::vector<float>& vertices,
                                std::vector<uint32_t>& indices,
                                const uint32_t vertices_per_side)
{
    float step = 1.0 / (vertices_per_side - 1UL);
    uint32_t n = (vertices_per_side * vertices_per_side * 3) * RIGHT_FACE_START_INDEX;

    glm::vec3 temp;

    for(uint32_t i = 0; i < vertices_per_side; i++)
    {
        for(uint32_t j = 0; j < vertices_per_side; j++)
        {
            temp.x = 0.5f;            // X
            temp.y = i * step - 0.5f; // Y
            temp.z = 1.0f - (j * step) - 0.5f; // Z

            temp = glm::normalize(temp);

            vertices.at(n + 0UL) = temp.x;
            vertices.at(n + 1UL) = temp.y;
            vertices.at(n + 2UL) = temp.z;

            n += 3UL;
        }
    }

    n = ((vertices_per_side - 1UL)  * (vertices_per_side - 1UL) * 6UL) * RIGHT_FACE_START_INDEX;
    uint32_t offset = vertices_per_side * vertices_per_side * RIGHT_FACE_START_INDEX;

    for(uint32_t i = 0; i < vertices_per_side - 1; ++i)
    {
        for(uint32_t j = 0; j < vertices_per_side - 1; ++j)
        {
            indices.at(n + 0UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 1UL) = offset + (i * vertices_per_side) + j + 1UL; // Y
            indices.at(n + 2UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Z

            indices.at(n + 3UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 4UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Y
            indices.at(n + 5UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 0UL); // Z

            n += 6UL;
        }
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
static void generate_top_face(std::vector<float>& vertices,
                              std::vector<uint32_t>& indices,
                              const uint32_t vertices_per_side)
{
    float step = 1.0 / (vertices_per_side - 1UL);
    uint32_t n = (vertices_per_side * vertices_per_side * 3) * TOP_FACE_START_INDEX;

    glm::vec3 temp;

    for(uint32_t i = 0; i < vertices_per_side; i++)
    {
        for(uint32_t j = 0; j < vertices_per_side; j++)
        {
            temp.x = 1.0f - (j * step) - 0.5f; // X
            temp.y = 0.5f;            // Y
            temp.z = i * step - 0.5f; // Z

            temp = glm::normalize(temp);

            vertices.at(n + 0UL) = temp.x;
            vertices.at(n + 1UL) = temp.y;
            vertices.at(n + 2UL) = temp.z;

            n += 3UL;
        }
    }

    n = ((vertices_per_side - 1UL)  * (vertices_per_side - 1UL) * 6UL) * TOP_FACE_START_INDEX;
    uint32_t offset = vertices_per_side * vertices_per_side * TOP_FACE_START_INDEX;

    for(uint32_t i = 0; i < vertices_per_side - 1; ++i)
    {
        for(uint32_t j = 0; j < vertices_per_side - 1; ++j)
        {
            indices.at(n + 0UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 1UL) = offset + (i * vertices_per_side) + j + 1UL; // Y
            indices.at(n + 2UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Z

            indices.at(n + 3UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 4UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Y
            indices.at(n + 5UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 0UL); // Z

            n += 6UL;
        }
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
static void generate_bottom_face(std::vector<float>& vertices,
                                 std::vector<uint32_t>& indices,
                                 const uint32_t vertices_per_side)
{
    float step = 1.0 / (vertices_per_side - 1UL);
    uint32_t n = (vertices_per_side * vertices_per_side * 3) * BOTTOM_FACE_START_INDEX;

    glm::vec3 temp;

    for(uint32_t i = 0; i < vertices_per_side; i++)
    {
        for(uint32_t j = 0; j < vertices_per_side; j++)
        {
            temp.x = j * step - 0.5f; // X
            temp.y = -0.5f;           // Y
            temp.z = i * step - 0.5f; // Z

            temp = glm::normalize(temp);

            vertices.at(n + 0UL) = temp.x;
            vertices.at(n + 1UL) = temp.y;
            vertices.at(n + 2UL) = temp.z;

            n += 3UL;
        }
    }

    n = ((vertices_per_side - 1UL)  * (vertices_per_side - 1UL) * 6UL) * BOTTOM_FACE_START_INDEX;
    uint32_t offset = vertices_per_side * vertices_per_side * BOTTOM_FACE_START_INDEX;

    for(uint32_t i = 0; i < vertices_per_side - 1; ++i)
    {
        for(uint32_t j = 0; j < vertices_per_side - 1; ++j)
        {
            indices.at(n + 0UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 1UL) = offset + (i * vertices_per_side) + j + 1UL; // Y
            indices.at(n + 2UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Z

            indices.at(n + 3UL) = offset + (i * vertices_per_side) + j;       // X
            indices.at(n + 4UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 1UL); // Y
            indices.at(n + 5UL) = offset + (i * vertices_per_side) + j + (vertices_per_side + 0UL); // Z

            n += 6UL;
        }
    }
}

/**********************************************************************************************//**
 * \brief
 * \param vertices
 *************************************************************************************************/
void generate_cube_with_subdivisions(std::vector<float>& vertices,
                                     std::vector<uint32_t>& indices,
                                     const uint32_t number_of_subdivisions)
{
    const uint32_t vertices_per_side = number_of_subdivisions + 2;

    vertices.resize(((vertices_per_side * vertices_per_side * 3) * 6), 0.0f);
    indices.resize((((vertices_per_side - 1) * (vertices_per_side - 1) * 6) * 6), 0UL);

    generate_front_face(vertices, indices, vertices_per_side);
    generate_back_face(vertices, indices, vertices_per_side);
    generate_left_face(vertices, indices, vertices_per_side);
    generate_right_face(vertices, indices, vertices_per_side);
    generate_top_face(vertices, indices, vertices_per_side);
    generate_bottom_face(vertices, indices, vertices_per_side);
}






// /**********************************************************************************************//**
//  * \brief
//  * \param vertices
//  *************************************************************************************************/
// void generate_subdivided_tetrahedron(std::vector<float>& vertices,
//                                      std::vector<uint32_t>& indices,
//                                      const uint32_t level)
// {
//     // const float root_two_over_three = sqrt(2.0) / 3.0;
//     // const float one_third = -(1.0 / 3.0);
//     // const float root_six_over_three = sqrt(6.0) / 3.0;

//     // vertices.reserve(pow(4.0, level + 1));
// }

// /**********************************************************************************************//**
//  * \brief
//  * \param vertices
//  *************************************************************************************************/
// void subdivide(std::vector<float>& vertices, std::vector<uint32_t>& indices, const uint32_t level)
// {
//     if(level > 0)
//     {
//         subdivide(vertices, indices, level - 1);
//     }
//     else
//     {

//     }
// }