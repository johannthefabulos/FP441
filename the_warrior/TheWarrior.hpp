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

    void drawWarrior(glm::mat4 viewMatrix, glm::mat4 projMatrix);

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);

private:
    ModelShaderLocations* shaderLocations;

    const glm::vec3 skinColor = {1, 1, 1};

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
};


#endif //MP_THEWARRIOR_HPP
