//
// Created by Fibonacci on 10/10/21.
//

#ifndef MP_THEWARRIOR_HPP
#define MP_THEWARRIOR_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../ShaderLocations.hpp"

class TheWarrior {

public:
    TheWarrior(ModelShaderLocations* locations);

private:
    ModelShaderLocations* shaderLocations;
};


#endif //MP_THEWARRIOR_HPP
