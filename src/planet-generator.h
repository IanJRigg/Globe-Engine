#ifndef PLANET_GENERATOR_H
#define PLANET_GENERATOR_H

#include <cstdint>
#include <vector>

void generate_cube_with_subdivisions(std::vector<float>& vertices,
                                     std::vector<uint32_t>& indices,
                                     const uint32_t number_of_subdivisions);

#endif
