//
// Created by Fibonacci on 10/8/21.
//

#include "TheWarrior.hpp"
#include <CSCI441/SimpleShader.hpp>
#include <stdio.h>

TheWarrior::TheWarrior(ModelShaderLocations shaderLocations, GLfloat WORLD_SIDE_LENGTH) {
    this->shaderLocations = shaderLocations;

    this->WORLD_SIDE_LENGTH = WORLD_SIDE_LENGTH;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, 0));
}

void TheWarrior::drawWarrior(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderLocations.shaderProgramHandle);

    this->drawBody(this->currentModelMatrix, viewMatrix, projMatrix);

    this->drawLeg(true, currentModelMatrix, viewMatrix, projMatrix);
    this->drawLeg(false, currentModelMatrix, viewMatrix, projMatrix);
}

void TheWarrior::drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

    glm::mat4 bodyModelMat = glm::translate(modelMtx, glm::vec3(0, this->bodyY, 0));
    this->computeAndSendMatUniforms(bodyModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);

    CSCI441::drawSolidCylinder(this->bodyWidth, this->bodyWidth, this->bodyHeight, 40, 40);
}

void TheWarrior::drawLeg(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    GLfloat legCenterY = this->bodyY - (this->bodyHeight/4);
    GLfloat legOffset = isLeft ? this->legLeftOffset : -this->legLeftOffset;
    GLfloat legRotation = isLeft ? this->legInitialRotation : -this->legInitialRotation;

    glm::mat4 legModelMat = glm::translate(modelMtx, glm::vec3(legOffset, legCenterY, 0));
    legModelMat = glm::rotate(legModelMat, legRotation, glm::vec3(0, 0, 1));
    this->computeAndSendMatUniforms(legModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);

    CSCI441::drawSolidCylinder(this->legWidth, this->legWidth, this->legLength, 40, 40);
}

void TheWarrior::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.mvpMatUniformLocation, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( this->shaderLocations.shaderProgramHandle, this->shaderLocations.normalMatUniformLocation, 1, GL_FALSE, &normalMtx[0][0] );
}

glm::vec3 TheWarrior::getCurrentPosition() {
    return this->currentWorldPosition;
}
