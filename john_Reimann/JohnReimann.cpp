#include "JohnReimann.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>

#ifndef M_PI
#define M_PI 3.14159265
#endif

JohnReimann::JohnReimann(GLuint shaderHandle, GLint mvpMatUniformLoc, GLint normalMatUniformLoc, GLint matColorUniformLoc, GLfloat WORLD_SIDE_LENGTH) {
    this->shaderProgramHandle = shaderHandle;
    this->mvpMatrixUniformLocation = mvpMatUniformLoc;
    this->normalMatrixUniformLocation = normalMatUniformLoc;
    this->materialColorUniformLocation = matColorUniformLoc;

    this->WORLD_SIDE_LENGTH = WORLD_SIDE_LENGTH;

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, this->carYPosition, 0));
}

void JohnReimann::drawJohn_Reimann(glm::mat4 viewMatrix, glm::mat4 projMatrix) {
    glUseProgram(this->shaderProgramHandle);
    //Front wheels
    this->drawLegs(this->currentModelMatrix, viewMatrix, projMatrix);
    //this->drawLeg(this->currentModelMatrix, viewMatrix, projMatrix);
    //Back wheels

    //this->drawHead( this->currentModelMatrix, viewMatrix, projMatrix);
//    this->drawAxel(false, this->currentModelMatrix, viewMatrix, projMatrix);

    //this->drawBody(this->currentModelMatrix, viewMatrix, projMatrix);
}

void JohnReimann::drawLegs(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    modelMtx = glm::translate(modelMtx,glm::vec3(1,5,1));


//    wheelModelMat = glm::rotate(wheelModelMat, glm::half_pi<GLfloat>(), glm::vec3(0, 1, 0));

    //wheelModelMat = glm::rotate(wheelModelMat, wheelAngle, glm::vec3(0, 0, 1));

    this->computeAndSendMatUniforms(modelMtx, viewMtx, projMtx);

    //glUniform3fv(this->materialColorUniformLocation, 1, &this->wheelColor[0]);

    //Testing values
    CSCI441::drawSolidCube(1);

}

void JohnReimann::computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv(this->shaderProgramHandle, this->mvpMatrixUniformLocation, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( this->shaderProgramHandle, this->normalMatrixUniformLocation, 1, GL_FALSE, &normalMtx[0][0] );
}

void JohnReimann::drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    glm::mat4 axelModelMat = modelMtx;
    //GLfloat axelWidth = this->wheelLRTranslation.x;
//    axelModelMat = glm::scale(axelModelMat, glm::vec3(axelWidth, axelWidth, axelWidth));


    axelModelMat = glm::translate(axelModelMat, glm::vec3(0, 2, -2));

//    axelModelMat = glm::rotate(axelModelMat, glm::half_pi<GLfloat>(), glm::vec3(0, 0, 1));
//
//    axelModelMat = glm::rotate(axelModelMat, wheelAngle, glm::vec3(0, 1, 0));

    this->computeAndSendMatUniforms(axelModelMat, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &this->bodyColor[0]);
    CSCI441::drawSolidCube(1);
    glm::mat4 noseModelMat = modelMtx;
    noseModelMat = glm::translate(noseModelMat, glm::vec3(0, 2, -3));
    this->computeAndSendMatUniforms(noseModelMat, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &this->bodyColor[0]);
    CSCI441::drawSolidCube(1);

}

void JohnReimann::drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

//    glm::mat4 teapotModelMat = glm::scale(modelMtx, glm::vec3(0.4, 0.4, 0.4));
//    teapotModelMat = glm::translate(teapotModelMat, glm::vec3(0, 0, -this->wheelFBTranslation.z));
//    teapotModelMat = glm::rotate(teapotModelMat, -glm::half_pi<GLfloat>(), glm::vec3(1, 0, 0));
//    teapotModelMat = glm::rotate(teapotModelMat, glm::half_pi<GLfloat>(), glm::vec3(0, 0, 1));
//    this->computeAndSendMatUniforms(teapotModelMat, viewMtx, projMtx);
//
//    glUniform3fv(this->materialColorUniformLocation, 1, &this->teapotColor[0]);
//    CSCI441::drawSolidTeapot();

    GLfloat bodyWidth = (this->wheelLRTranslation.x * 2) + (this->wheelInnerRadius);
    GLfloat bodyLength = (this->wheelFBTranslation.z * 2) + (this->wheelInnerRadius);
    GLfloat bodyWidthScale = bodyWidth/this->wheelInnerRadius;
    GLfloat bodyLengthScale = bodyLength/this->wheelInnerRadius;



    glm::mat4 flatBodyModelMat = glm::scale(modelMtx, glm::vec3(bodyWidthScale, bodyWidthScale/2, bodyLengthScale));
    flatBodyModelMat = glm::translate(flatBodyModelMat,glm::vec3(0,.2,0));
    this->computeAndSendMatUniforms(flatBodyModelMat, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &this->bodyColor[0]);
    CSCI441::drawSolidCube(this->wheelInnerRadius);

    glm::mat4 tailMat = glm::scale(modelMtx, glm::vec3(.5, bodyWidthScale/3, .5));
    tailMat = glm::translate(tailMat,glm::vec3(0,.3,3.5));
    this->computeAndSendMatUniforms(tailMat, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &this->tailColor[0]);
    CSCI441::drawSolidCube(this->wheelInnerRadius);
}

glm::vec3 JohnReimann::getCurrentPosition() {
    return this->currentWorldPosition;
}

void JohnReimann::driveForward() {

    if (!this->testCarShouldMove(-this->moveSpeed)){
        return;
    }

    this->updateWheelRotation(true);

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, -moveSpeed));
    this->updateCurrentPosition();
}

void JohnReimann::driveBackward() {

    if (!this->testCarShouldMove(this->moveSpeed)){
        return;
    }

    this->updateWheelRotation(false);

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, moveSpeed));
    this->updateCurrentPosition();
}

void JohnReimann::updateCurrentPosition() {
    this->currentWorldPosition = this->currentModelMatrix * glm::vec4(0, 0, 0, 1);
}

void JohnReimann::turnCar(GLfloat theta) {
    this->currentModelMatrix = glm::rotate(this->currentModelMatrix, theta, glm::vec3(0, 1, 0));
}

bool JohnReimann::testCarShouldMove(GLfloat testMoveSpeed) {
    glm::mat4 testModelMat = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, testMoveSpeed));
    glm::vec3 testWorldPos = testModelMat * glm::vec4(0, 0, 0, 1);

    // Since the group extends from (-WORLD_SIDE_LENGTH, -WORLD_SIDE_LENGTH) to (WORLD_SIDE_LENGTH, WORLD_SIDE_LENGTH)
    //      we can use the absolute value
    GLfloat absXPos = glm::abs(testWorldPos.x) + this->wheelFBTranslation.z;
    GLfloat absZPos = glm::abs(testWorldPos.z) + this->wheelFBTranslation.z;
    if (absXPos >= WORLD_SIDE_LENGTH || absZPos >= WORLD_SIDE_LENGTH){
        return false;
    }
    return true;
}

void JohnReimann::updateWheelRotation(bool isMovingForward) {
    GLfloat wheelAngleDelta = glm::pi<GLfloat>() /128.0f;
    if (isMovingForward){
        wheelAngleDelta *= -1;
    }
    this->wheelAngle += wheelAngleDelta;
    if (this->wheelAngle < 0){
        this->wheelAngle += glm::two_pi<GLfloat>();
    }
    if (this->wheelAngle > glm::two_pi<GLfloat>()){
        this->wheelAngle -= glm::two_pi<GLfloat>();
    }
}
