//
// Created by Fibonacci on 10/8/21.
//

#include "TheWarrior.hpp"
#include <CSCI441/SimpleShader.hpp>
#include <stdio.h>

TheWarrior::TheWarrior(ModelShaderLocations shaderLocations, GLfloat WORLD_SIDE_LENGTH) {
    this->shaderLocations = shaderLocations;

    this->WORLD_SIDE_LENGTH = WORLD_SIDE_LENGTH;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, this->footHeight*1.35, 0));
}

void TheWarrior::drawWarrior(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderLocations.shaderProgramHandle);

    this->drawBody(this->currentModelMatrix, viewMatrix, projMatrix);

    this->drawLeg(true, currentModelMatrix, viewMatrix, projMatrix);
    this->drawLeg(false, currentModelMatrix, viewMatrix, projMatrix);

    this->drawArm(true, currentModelMatrix, viewMatrix, projMatrix);
    this->drawArm(false, currentModelMatrix, viewMatrix, projMatrix);

    this->drawHead(currentModelMatrix, viewMatrix, projMatrix);

}

void TheWarrior::drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

    glm::mat4 bodyModelMat = glm::translate(modelMtx, glm::vec3(0, this->bodyY, 0));
    GLfloat segmentHeight = this->bodyHeight/2.0f;

    this->computeAndSendMatUniforms(bodyModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);

    if (this->drawWireframe){
        CSCI441::drawWireCylinder(this->bodyBottomWidth,this->bodyCenterWidth , segmentHeight, 30, 30);
    }else{
        CSCI441::drawSolidCylinder(this->bodyBottomWidth,this->bodyCenterWidth , segmentHeight, 30, 30);
    }

    bodyModelMat = glm::translate(bodyModelMat, glm::vec3(0, segmentHeight, 0));
    this->computeAndSendMatUniforms(bodyModelMat, viewMtx, projMtx);
    if (this->drawWireframe){
        CSCI441::drawWireCylinder(this->bodyCenterWidth,this->bodyTopWidth , segmentHeight, 30, 30);
    }else{
        CSCI441::drawSolidCylinder(this->bodyCenterWidth,this->bodyTopWidth , segmentHeight, 30, 30);
    }


    this->drawNeck(bodyModelMat, viewMtx, projMtx);
}

void TheWarrior::drawNeck(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

    glm::mat4 neckModelMat = glm::translate(modelMtx, glm::vec3(0, this->bodyHeight/2, 0));

    this->computeAndSendMatUniforms(neckModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);
    if (this->drawWireframe) {
        CSCI441::drawWireCylinder(this->bodyTopWidth,this->neckTopWidth , this->neckHeight, 30, 30);
    }else{
        CSCI441::drawSolidCylinder(this->bodyTopWidth,this->neckTopWidth , this->neckHeight, 30, 30);
    }


}

void TheWarrior::drawLeg(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    GLfloat legCenterY = this->bodyY - (this->bodyHeight/2);
    GLfloat legOffset = isLeft ? this->legLeftOffset : -this->legLeftOffset;

    glm::mat4 legModelMat = glm::translate(modelMtx, glm::vec3(legOffset, legCenterY, 0));
    this->computeAndSendMatUniforms(legModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);

    if (this->drawWireframe) {
        CSCI441::drawWireCylinder(this->legWidthBottom, this->legWidthTop, this->legLength, 40, 40);
    }else{
        CSCI441::drawSolidCylinder(this->legWidthBottom, this->legWidthTop, this->legLength, 40, 40);
    }


    this->drawFoot(legModelMat, viewMtx, projMtx);
}

void TheWarrior::drawFoot(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    GLfloat footCenterZ = this->footLength - (this->legWidthTop*1.5);
    glm::mat4 footModelMat = glm::translate(modelMtx, glm::vec3(0, 0, footCenterZ));
    footModelMat = glm::scale(footModelMat, glm::vec3(1, this->footHeight/this->footWidth, this->footLength/this->footWidth));

    this->computeAndSendMatUniforms(footModelMat, viewMtx, projMtx);

    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);
    if (this->drawWireframe) {
        CSCI441::drawWireCube(this->footWidth);
    }else{
        CSCI441::drawSolidCube(this->footWidth);
    }

}

void TheWarrior::drawArm(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    GLfloat armCenterY = this->bodyY + this->bodyHeight - this->neckHeight;
    GLfloat armOffset = isLeft ? this->armLeftOffset : -this->armLeftOffset;
    GLfloat armRotation = isLeft ? -this->armInitialRotation : this->armInitialRotation;

    glm::mat4 armModelMat = glm::translate(modelMtx, glm::vec3(armOffset, armCenterY, 0));

    //Used when drawing shield + sword
    glm::mat4 armEndModelMat = glm::translate(armModelMat, glm::vec3(this->armLength, 0, 0));

    armModelMat = glm::rotate(armModelMat, armRotation, glm::vec3(0, 0, 1));

    this->computeAndSendMatUniforms(armModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);

    CSCI441::drawSolidCylinder(this->armStartWidth, this->armEndWidth, this->armLength, 40, 40);
    if (isLeft){
        this->drawShield(armEndModelMat, armRotation, viewMtx, projMtx);
    }



}

void TheWarrior::drawShield(glm::mat4 armEndModelMtx, GLfloat armRotation, glm::mat4 viewMtx, glm::mat4 projMtx) {



    glm::mat4 shieldSemiCircleMat = glm::translate(armEndModelMtx, glm::vec3(0, -this->shieldRectHeight, 0));

    glm::mat4 shieldRectMat = glm::translate(armEndModelMtx, glm::vec3(0,
                                                                       this->armEndWidth - (this->shieldRectHeight/1.5),
                                                                       0));
    shieldRectMat = glm::scale(shieldRectMat, glm::vec3(1,
                                                        this->shieldRectHeight/this->shieldRectWidth,
                                                        (this->shieldDepth+0.05)/this->shieldRectWidth));

    this->computeAndSendMatUniforms(glm::translate(shieldSemiCircleMat, glm::vec3(0, 0, this->shieldDepth/2)), viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->shieldColor[0]);
    CSCI441::drawSolidPartialDisk(0, this->shieldRectWidth/2, 20, 20, 180, 180);

    this->computeAndSendMatUniforms(glm::translate(shieldSemiCircleMat, glm::vec3(0, 0, -this->shieldDepth/2)), viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->shieldColor[0]);
    CSCI441::drawSolidPartialDisk(0, this->shieldRectWidth/2, 20, 20, 180, 180);

    shieldSemiCircleMat = glm::translate(shieldSemiCircleMat, glm::vec3(0, 0, -this->shieldDepth/2));

    shieldSemiCircleMat = glm::rotate(shieldSemiCircleMat, glm::half_pi<GLfloat>(), glm::vec3(1, 0, 0));
    this->computeAndSendMatUniforms(shieldSemiCircleMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->shieldColor[0]);


    CSCI441::drawSolidCylinder(this->shieldRectWidth/2, this->shieldRectWidth/2, this->shieldDepth, 20, 20);

    this->computeAndSendMatUniforms(shieldRectMat, viewMtx, projMtx);
    CSCI441::drawSolidCube(this->shieldRectWidth);

}


void TheWarrior::drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    GLfloat headCenterY = this->bodyY + this->bodyHeight + (neckHeight*2) + (this->headRadius/2);

    glm::mat4 headModelMat = glm::translate(modelMtx, glm::vec3(0, headCenterY, 0));
    this->computeAndSendMatUniforms(headModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);

    if (this->drawWireframe) {
        CSCI441::drawWireSphere(this->headRadius, 30, 30);
    }else{
        CSCI441::drawSolidSphere(this->headRadius, 30, 30);
    }

}

void TheWarrior::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
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
