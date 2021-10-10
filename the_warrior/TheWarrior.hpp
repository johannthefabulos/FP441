//
// Created by Fibonacci on 10/10/21.
//

#ifndef MP_THEWARRIOR_HPP
#define MP_THEWARRIOR_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../ShaderLocations.h"

class TheWarrior {
    TheWarrior(ShaderLocations* locations);

private:
    ShaderLocations* shaderLocations;
};


#endif //MP_THEWARRIOR_HPP
