//
// Created by Connor on 10/14/2021.
//

#include "Castle.hpp"
#include <CSCI441/SimpleShader.hpp>

Castle::Castle(ModelShaderLocations shaderLocations, float xPos, float zPos, float ang) {
    this->shaderLocations = shaderLocations;


    this-> x = xPos;
    this-> ang = ang;
    this-> z = zPos;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(xPos, 2.5, zPos));
    this->currentModelMatrix = glm::rotate(this->currentModelMatrix,-ang,glm::vec3(0,1,0));
}

void Castle::drawCastle(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderLocations.shaderProgramHandle);
    this->drawMain(this->currentModelMatrix,viewMatrix,projMatrix);
    this->drawTop(true,true,this->currentModelMatrix,viewMatrix,projMatrix);
    this->drawTop(true,false,this->currentModelMatrix,viewMatrix,projMatrix);
    this->drawTop(false,true,this->currentModelMatrix,viewMatrix,projMatrix);
    this->drawTop(false,false,this->currentModelMatrix,viewMatrix,projMatrix);
}

void Castle::drawMain(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->trunkColor[0]);
    this->computeAndSendMatUniforms(modelMtx, viewMtx, projMtx);
    CSCI441::drawSolidCube(5);

    glm::mat4 doorMat = glm::rotate(modelMtx,0.0f,glm::vec3(0,0,1));
    doorMat = glm::rotate(doorMat,float(M_PI/2),glm::vec3(0,1,0));
    doorMat = glm::translate(doorMat,glm::vec3(0,0,-3));

    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->leafColor[0]);
    this->computeAndSendMatUniforms(doorMat, viewMtx, projMtx);
    CSCI441::drawSolidPartialDisk(0,1,10,10,0,180);

    glm::mat4 doorWay = glm::translate(modelMtx,glm::vec3(-2,-1,0));
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->leafColor[0]);
    this->computeAndSendMatUniforms(doorWay, viewMtx, projMtx);
    CSCI441::drawSolidCube(2);

}

void Castle::drawTop(bool isLeft, bool isTop, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    int positionModifierX = 1, positionModifierZ = 1;
    if(isLeft){
        positionModifierX = -1;
    }
    if(isTop){
        positionModifierZ = -1;
    }
    glm::mat4 drawTop = glm::translate(modelMtx,glm::vec3(positionModifierX*2,3,positionModifierZ*2));
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->trunkColor[0]);
    this->computeAndSendMatUniforms(drawTop, viewMtx, projMtx);
    CSCI441::drawSolidCube(1);
}

void Castle::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.mvpMatUniformLocation, 1, GL_FALSE, &mvpMtx[0][0] );

    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.modelMatUniformLocation, 1, GL_FALSE, &modelMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( this->shaderLocations.shaderProgramHandle, this->shaderLocations.normalMatUniformLocation, 1, GL_FALSE, &normalMtx[0][0] );

}
