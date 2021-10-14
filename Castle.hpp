//
// Created by Connor on 10/14/2021.
//

#ifndef MP_CASTLE_HPP
#define MP_CASTLE_HPP
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ShaderLocations.hpp"
#include "../HeroVirtual.hpp"

class Castle {
public:
    Castle(ModelShaderLocations shaderLocations, float xPos, float zPos, float ang);

    void drawCastle(glm::mat4 viewMatrix, glm::mat4 projMatrix);


private:
    ModelShaderLocations shaderLocations;

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);

    float x;
    float ang;
    float z;

    const glm::vec3 leafColor = {0, .5f, 0};
    const glm::vec3 trunkColor = {0.7f, 0.75f, 0.71f};

    void drawMain(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
    void drawTop(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);


    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //MP_CASTLE_HPP
