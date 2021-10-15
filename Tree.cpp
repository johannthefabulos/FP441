//
// Created by Connor on 10/13/2021.
//

#include "Tree.hpp"
#include "ShaderLocations.hpp"
#include <CSCI441/SimpleShader.hpp>


Tree::Tree(ModelShaderLocations shaderLocations, float xPos, float yPos, float zPos) {
    this->shaderLocations = shaderLocations;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(xPos, 0, zPos));
    this->currentModelMatrix = glm::scale(this->currentModelMatrix,glm::vec3(yPos,yPos,yPos));

    this-> x = xPos;
    this-> y = yPos;
    this-> z = zPos;
    this->leaveAngle = ((yPos-1)*M_PI/12)-(M_PI/24);

}

void Tree::drawTree(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderLocations.shaderProgramHandle);

    this->drawTrunk(this->currentModelMatrix,viewMatrix,projMatrix);
    this->drawLeaves(this->currentModelMatrix,viewMatrix,projMatrix);
}

void Tree::drawTrunk(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    modelMtx = glm::scale(modelMtx, glm::vec3(y,y,y));
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->trunkColor[0]);
    this->computeAndSendMatUniforms(modelMtx, viewMtx, projMtx);

    CSCI441::drawSolidCylinder(.3,.3,2,1,20);


}
void Tree::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.mvpMatUniformLocation, 1, GL_FALSE, &mvpMtx[0][0] );

    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.modelMatUniformLocation, 1, GL_FALSE, &modelMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( this->shaderLocations.shaderProgramHandle, this->shaderLocations.normalMatUniformLocation, 1, GL_FALSE, &normalMtx[0][0] );
}

void Tree::drawLeaves(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

    if (leaveBool) {

        this->leaveAngle += .005*abs(abs(leaveAngle)-M_PI/23);
        if (leaveAngle > M_PI/24) {
            leaveBool = false;
        }
    }else{
        this->leaveAngle -= .005*abs(abs(leaveAngle)-M_PI/23);
        if (leaveAngle < -1*M_PI/24) {
            leaveBool = true;
        }
    }

    glm::mat4 leaveMatrix = glm::rotate(modelMtx,leaveAngle,glm::vec3(1,0,0));
    leaveMatrix =glm::translate(leaveMatrix,glm::vec3(0,2,0));
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->leafColor[0]);
    this->computeAndSendMatUniforms(leaveMatrix, viewMtx, projMtx);
    CSCI441::drawSolidCone(2,6,10,10);


}




