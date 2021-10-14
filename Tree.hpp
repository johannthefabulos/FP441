//
// Created by Connor on 10/13/2021.
//

#ifndef MP_TREE_HPP
#define MP_TREE_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ShaderLocations.hpp"
#include "../HeroVirtual.hpp"


class Tree {
public:
    Tree(ModelShaderLocations shaderLocations, float xPos, float yPos, float zPos);

    void drawTree(glm::mat4 viewMatrix, glm::mat4 projMatrix);


private:
    ModelShaderLocations shaderLocations;

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);

    float x;
    float y;
    float z;

    const glm::vec3 leafColor = {0, .5f, 0};
    const glm::vec3 trunkColor = {0.43f, 0.21f, 0.1f};

    void drawTrunk(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);
    void drawLeaves(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);


    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //MP_TREE_HPP
