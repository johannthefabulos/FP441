//
// Created by Fibonacci on 10/10/21.
//

#ifndef MP_THEWARRIOR_HPP
#define MP_THEWARRIOR_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ShaderLocations.hpp"

class TheWarrior {

public:
    TheWarrior(ModelShaderLocations shaderLocations, GLfloat WORLD_SIDE_LENGTH);

    void drawWarrior(glm::mat4 viewMatrix, glm::mat4 projMatrix);

    glm::vec3 getCurrentPosition();

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);
private:
    ModelShaderLocations shaderLocations;

    GLfloat WORLD_SIDE_LENGTH;

    glm::vec3 currentWorldPosition = {0, 0, 0};

    const glm::vec3 bodyColor = {1.0, 223.0f/255.0f, 196.0f/255.0f};
    const GLfloat bodyWidth = 0.6;
    const GLfloat bodyHeight = 5;

    const GLfloat bodyY = 1.5;

    const GLfloat legInitialRotation = glm::two_pi<GLfloat>()/12.0f;
    const GLfloat legLeftOffset = 1;
    const GLfloat legLength = 2;
    const GLfloat legWidth = 0.2;

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawLeg(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
};


#endif //MP_THEWARRIOR_HPP
