#include "eeyore.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>

#ifndef M_PI
#define M_PI 3.14159265
#endif

eeyore::eeyore(ModelShaderLocations shaderLocations, GLfloat WORLD_SIDE_LENGTH) {
    this->shaderLocations = shaderLocations;


    this->WORLD_SIDE_LENGTH = WORLD_SIDE_LENGTH;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(10, this->eeyoreYPosition, -10));
}

void eeyore::drawEeyore(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderLocations.shaderProgramHandle);
    //Front wheels
    this->drawLeg(true, true, this->currentModelMatrix, viewMatrix, projMatrix);
    this->drawLeg(true, false, this->currentModelMatrix, viewMatrix, projMatrix);
    //Back wheels
    this->drawLeg(false, true, this->currentModelMatrix, viewMatrix, projMatrix);
    this->drawLeg(false, false, this->currentModelMatrix, viewMatrix, projMatrix);

    this->drawHead( this->currentModelMatrix, viewMatrix, projMatrix);
    this->drawEye(true,this->currentModelMatrix, viewMatrix, projMatrix);
    this->drawEye(false,this->currentModelMatrix, viewMatrix, projMatrix);
    this->drawEar(true,this->currentModelMatrix, viewMatrix, projMatrix);
    this->drawEar(false,this->currentModelMatrix, viewMatrix, projMatrix);
    this->drawBody(this->currentModelMatrix, viewMatrix, projMatrix);
}

void eeyore::drawLeg(bool isFront, bool isRight, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    glm::mat4 wheelModelMat = modelMtx;

    wheelModelMat = glm::scale(wheelModelMat,glm::vec3(1,5,1));

    if (isFront){
        wheelModelMat = glm::translate(wheelModelMat, this->bodyWid);
    }else{
        wheelModelMat = glm::translate(wheelModelMat, -this->bodyWid);
    }
    if (isRight){
        wheelModelMat = glm::translate(wheelModelMat, this->bodyLen);
        wheelModelMat = glm::rotate(wheelModelMat, wheelAngle, glm::vec3(0.5,0,0));
    }else{
        wheelModelMat = glm::translate(wheelModelMat, -this->bodyLen);
        wheelModelMat = glm::rotate(wheelModelMat, -wheelAngle, glm::vec3(0.5,0,0));
    }


//    wheelModelMat = glm::rotate(wheelModelMat, glm::half_pi<GLfloat>(), glm::vec3(0, 1, 0));



    this->computeAndSendMatUniforms(wheelModelMat, viewMtx, projMtx);

    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->wheelColor[0]);

    //Testing values
    CSCI441::drawSolidCube(this->legInWid);

}

void eeyore::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.mvpMatUniformLocation, 1, GL_FALSE, &mvpMtx[0][0] );

    glProgramUniformMatrix4fv(this->shaderLocations.shaderProgramHandle, this->shaderLocations.modelMatUniformLocation, 1, GL_FALSE, &modelMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( this->shaderLocations.shaderProgramHandle, this->shaderLocations.normalMatUniformLocation, 1, GL_FALSE, &normalMtx[0][0] );
}

void eeyore::drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    glm::mat4 axelModelMat = modelMtx;
    //GLfloat axelWidth = this->wheelLRTranslation.x;
    if (headBool) {
        this->headBob += .001;
        if (headBob > .2) {
            headBool = false;
        }
    }else{
        this->headBob -= .001;
        if (headBob < 0) {
            headBool = true;
        }
    }
    axelModelMat = glm::scale(axelModelMat, glm::vec3(1, 1, 1.5));


    axelModelMat = glm::translate(axelModelMat, glm::vec3(0, 2+headBob, -1.5));



    this->computeAndSendMatUniforms(axelModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);
    CSCI441::drawSolidCube(1);

    glm::mat4 noseModelMat = modelMtx;
    noseModelMat = glm::scale(noseModelMat, glm::vec3(1, 1, .5));
    noseModelMat = glm::translate(noseModelMat, glm::vec3(0, 2+headBob, -6.5));
    this->computeAndSendMatUniforms(noseModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->noseColor[0]);
    CSCI441::drawSolidCube(1);



}
void eeyore::drawEye(bool left,glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx){
    glm::mat4 eyeModelMat = modelMtx;
    glm::mat4 pupilModelMat = modelMtx;
    if(left){
        eyeModelMat = glm::translate(eyeModelMat, glm::vec3(.5, 2+headBob, -2));
        pupilModelMat = glm::translate(pupilModelMat, glm::vec3(.65, 2+headBob, -2));
    }
    else{
        eyeModelMat = glm::translate(eyeModelMat, glm::vec3(-.5, 2+headBob, -2));
        pupilModelMat = glm::translate(pupilModelMat, glm::vec3(-.65, 2+headBob, -2));
    }

    this->computeAndSendMatUniforms(eyeModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->eyeColor[0]);
    CSCI441::drawSolidCube(.3);
    this->computeAndSendMatUniforms(pupilModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->tailColor[0]);
    CSCI441::drawSolidCube(.1);

}

void eeyore::drawEar(bool left,glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx){
    glm::mat4 ear = modelMtx;

    if(left){
        ear = glm::translate(ear, glm::vec3(.3, 3+headBob, -2));
    }
    else{
        ear = glm::translate(ear, glm::vec3(-.3, 3+headBob, -2));
    }
    ear = glm::scale(ear, glm::vec3(.5,3,.8));
    this->computeAndSendMatUniforms(ear, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);
    CSCI441::drawSolidCube(.5);


}


void eeyore::drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

    GLfloat bodyWidth = (this->bodyWid.x * 2) + (this->legInWid);
    GLfloat bodyLength = (this->bodyLen.z * 2) + (this->legInWid);
    GLfloat bodyWidthScale = bodyWidth/this->legInWid;
    GLfloat bodyLengthScale = bodyLength/this->legInWid;



    glm::mat4 flatBodyModelMat = glm::scale(modelMtx, glm::vec3(bodyWidthScale, bodyWidthScale/2, bodyLengthScale));
    flatBodyModelMat = glm::translate(flatBodyModelMat,glm::vec3(0,.2,0));
    this->computeAndSendMatUniforms(flatBodyModelMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->bodyColor[0]);
    CSCI441::drawSolidCube(this->legInWid);

    glm::mat4 tailMat = glm::scale(modelMtx, glm::vec3(.5, bodyWidthScale/3, .5));
    tailMat = glm::translate(tailMat,glm::vec3(0,.3,3.5));
    this->computeAndSendMatUniforms(tailMat, viewMtx, projMtx);
    glUniform3fv(this->shaderLocations.matColorUniformLocation, 1, &this->tailColor[0]);
    CSCI441::drawSolidCube(this->legInWid);
}

glm::vec3 eeyore::getCurrentPosition() {
    return this->currentWorldPosition;
}

void eeyore::moveHeroForward() {

    if (!this->testEeyoreShouldMove(-this->moveSpeed)){
        return;
    }

    this->updateLegRotation(true);

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, -moveSpeed));
    this->updateCurrentPosition();
}

void eeyore::moveHeroBackward() {

    if (!this->testEeyoreShouldMove(this->moveSpeed)){
        return;
    }

    this->updateLegRotation(false);

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, moveSpeed));
    this->updateCurrentPosition();
}

void eeyore::updateCurrentPosition() {
    this->currentWorldPosition = this->currentModelMatrix * glm::vec4(0, 0, 0, 1);
}

void eeyore::turnHero(GLfloat theta) {
    this->currentModelMatrix = glm::rotate(this->currentModelMatrix, theta, glm::vec3(0, 1, 0));
}

bool eeyore::testEeyoreShouldMove(GLfloat testMoveSpeed) {
    glm::mat4 testModelMat = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, testMoveSpeed));
    glm::vec3 testWorldPos = testModelMat * glm::vec4(0, 0, 0, 1);

    // Since the group extends from (-WORLD_SIDE_LENGTH, -WORLD_SIDE_LENGTH) to (WORLD_SIDE_LENGTH, WORLD_SIDE_LENGTH)
    //      we can use the absolute value
    GLfloat absXPos = ceil(glm::abs(testWorldPos.x) + this->bodyLen.z+2);
    GLfloat absZPos = ceil(glm::abs(testWorldPos.z) + this->bodyLen.z+2);
    GLfloat distanceFromCenter = sqrt(pow(absXPos,2)+pow(absZPos,2));
    if (distanceFromCenter > WORLD_SIDE_LENGTH-5.5){
        return false;
    }
    return true;
}

void eeyore::updateLegRotation(bool isMovingForward) {
    GLfloat wheelAngleDelta = glm::pi<GLfloat>() /256.0f;
//    if (isMovingForward){
//        wheelAngleDelta *= -1;
//    }

    if (direction) {
        this->wheelAngle += wheelAngleDelta;
        if (wheelAngle > M_PI / 4) {
            direction = false;
        }
    }else{
        this->wheelAngle -= wheelAngleDelta;
        if (wheelAngle < -M_PI / 4) {
            direction = true;
        }
    }

}

glm::mat4 eeyore::getCurrentModelMat() {
    return this->currentModelMatrix;
}

void eeyore::leftClickAction() {
    eyeColor = glm::vec3(1,0,0);
    eyeFlag +=1;
    if(eyeFlag>= 2){
        eyeColor = glm::vec3(1,1,1);
        eyeFlag = 0;
    }
}
