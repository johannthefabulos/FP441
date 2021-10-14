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
    //modelMtx = glm::translate( modelMtx, glm::vec3( cos(animationAngle), 0, sin(animationAngle) ));
    //modelMtx = glm::translate( modelMtx, glm::vec3( translateX, 0, translateY));
    //modelMtx = glm::rotate( modelMtx, 2*correctionAngle, CSCI441::Y_AXIS );
    //modelMtx = glm::rotate( modelMtx, chairCurrentAngle, CSCI441::Y_AXIS );
    drawLegs(this->currentModelMatrix,viewMatrix, projMatrix );
    drawHead(this->currentModelMatrix,viewMatrix,projMatrix );
    drawBody(this->currentModelMatrix,viewMatrix, projMatrix );
}

void JohnReimann::drawLegs(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {
    glm::vec3 _colorRed = glm::vec3( 1.0f, 0.0f, 0 );
    modelMtx = glm::scale( modelMtx,glm::vec3( .5, 1, 1 ));
    modelMtx = glm::translate( modelMtx, glm::vec3( 1.5f, 0, 0 ));
    this->computeAndSendMatUniforms(modelMtx, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &_colorRed[0]);
    CSCI441::drawSolidCube(1);
    modelMtx = glm::translate( modelMtx, glm::vec3( -1.5f, 0, 0 ));
    modelMtx = glm::translate( modelMtx, glm::vec3( -1.5f, 0, 0 ));
    this->computeAndSendMatUniforms(modelMtx, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &_colorRed[0]);
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
    glm::vec3 _colorGreen = glm::vec3( 0, 1.0f, 0);
    modelMtx = glm::translate( modelMtx, glm::vec3( 0, 0, 0 ));
    modelMtx = glm::scale( modelMtx,glm::vec3( 1, .5, 1 ));
    this->computeAndSendMatUniforms(modelMtx, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &_colorGreen[0]);
    CSCI441::drawSolidCube(1);
}

void JohnReimann::drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) {

    glm::vec3 _colorBlue = glm::vec3( 0, 0, 1.0f );
    modelMtx = glm::translate( modelMtx, glm::vec3( 0, .5, .5 ));
    modelMtx = glm::scale( modelMtx,glm::vec3( 1, 1.5, .5 ));
    this->computeAndSendMatUniforms(modelMtx, viewMtx, projMtx);
    glUniform3fv(this->materialColorUniformLocation, 1, &_colorBlue[0]);
    CSCI441::drawSolidCube(1);
}

glm::vec3 JohnReimann::getCurrentPosition() {
    return this->currentWorldPosition;
}

void JohnReimann::moveHeroForward() {

    if (!this->testCarShouldMove(-this->moveSpeed)){
        return;
    }

    this->updateWheelRotation(true);

    this->currentModelMatrix = glm::translate(this->currentModelMatrix, glm::vec3(0, 0, -moveSpeed));
    this->updateCurrentPosition();
}

void JohnReimann::moveHeroBackward() {

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

void JohnReimann::turnHero(GLfloat theta) {
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

glm::mat4 JohnReimann::getCurrentModelMat() {
    return this->currentModelMatrix;
}
