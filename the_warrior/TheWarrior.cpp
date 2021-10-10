//
// Created by Fibonacci on 10/10/21.
//

#include "TheWarrior.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <CSCI441/SimpleShader.hpp>

TheWarrior::TheWarrior(ModelShaderLocations* locations) {
    this->shaderLocations = locations;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(5, 5, 5));
}

void TheWarrior::drawWarrior(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderLocations->shaderProgramHandle);
    this->drawBody(currentModelMatrix, viewMatrix, projMatrix);

}

void TheWarrior::drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

    glm::mat4 bodyModelMat = modelMtx;

    this->computeAndSendMatUniforms(bodyModelMat, viewMtx, projMtx);

    glUniform3fv(this->shaderLocations->matColorUniformLocation, 1, &this->skinColor[0]);

    CSCI441::drawSolidCylinder(5, 5, 10,20, 30);

}

void TheWarrior::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv(this->shaderLocations->shaderProgramHandle, this->shaderLocations->mvpMatUniformLocation, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( this->shaderLocations->shaderProgramHandle, this->shaderLocations->normalMatUniformLocation, 1, GL_FALSE, &normalMtx[0][0] );
}



