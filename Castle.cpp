//
// Created by Connor on 10/14/2021.
//

#include "Castle.hpp"
#include <CSCI441/SimpleShader.hpp>

Castle::Castle(ModelShaderLocations shaderLocations, float xPos, float zPos, float ang) {
    this->shaderLocations = shaderLocations;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(xPos, 2.5, zPos));
    this-> x = xPos;
    this-> ang = ang;
    this-> z = zPos;
}

void Castle::drawCastle(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderLocations.shaderProgramHandle);
    this->drawMain(this->currentModelMatrix,viewMatrix,projMatrix);
}

void Castle::drawMain(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    glm::mat4 castleMtx = glm::rotate(modelMtx,ang,glm::vec3(0,1,0));

    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->trunkColor[0]);
    this->computeAndSendMatUniforms(castleMtx, viewMtx, projMtx);

    CSCI441::drawSolidCube(5);
}

void Castle::drawTop(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

}

void Castle::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.mvpMatUniformLocation, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( this->shaderLocations.shaderProgramHandle, this->shaderLocations.normalMatUniformLocation, 1, GL_FALSE, &normalMtx[0][0] );

}
