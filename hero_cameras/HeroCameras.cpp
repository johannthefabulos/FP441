//
// Created by Fibonacci on 10/13/21.
//

#include "HeroCameras.hpp"

#include <algorithm>
#include <iostream>
#include <glm/gtc/matrix_access.hpp>

HeroCameras::HeroCameras(GLint cameraPosUniformLoc) {
    arcballCam = new CSCI441::ArcballCam();
    arcballCam->setLookAtPoint(glm::vec3(0.0f, 2.1f, 0.0f) );
    arcballCam->setTheta(3.52f );
    arcballCam->setPhi(1.9f );
    arcballCam->setRadius( 15.0f );
    arcballCam->recomputeOrientation();

    freeCam = new CSCI441::FreeCam();
    freeCam->setPosition( glm::vec3(10.0f, 10.0f, 10.0f) );
    freeCam->setTheta( 5.52f );
    freeCam->setPhi( 0.9f );
    freeCam->recomputeOrientation();

    this->currentCameraPointer = arcballCam;
    this->cameraPositionUniformLoc = cameraPosUniformLoc;
}

HeroCameras::~HeroCameras() {
    if (arcballCam != nullptr){
        delete arcballCam;
    }
    if (freeCam != nullptr){
        delete freeCam;
    }
}

void HeroCameras::changeCamera(int possibleKeyCode) {

    //Only used with SKY_CAM perspective, but initialized here for C++ errors
    glm::vec3 skyCamPos, heroForwardVec, pos;
    if (possibleKeyCode == SKY_CAM || possibleKeyCode == FIRST_PERSON){
        glm::mat4 heroInvMat = glm::inverse(this->currentHero->getCurrentModelMat());
        heroForwardVec = glm::transpose(heroInvMat) * glm::vec4(0, 0, this->currentHero->getFirstPersonCamZModifer(), 1);
        heroForwardVec = glm::normalize(heroForwardVec);
        pos = this->currentHero->getFirstPersonCamPosition();
    }
    //Since this is used in SKY_CAM and FIRST_PERSON, I will just declare it here

     switch (possibleKeyCode) {
        case ARCBALL:
            this->currentCameraPointer = this->arcballCam;
            this->mainCameraType = ARCBALL;
            this->currentViewMatrix = glm::mat4(1.0f);
            break;
        case FREE_CAM:
            this->currentCameraPointer = this->freeCam;
            this->mainCameraType = FREE_CAM;
            this->currentViewMatrix = glm::mat4(1.0f);
            break;
        case SKY_CAM:
            //Compute sky cam view matrix
            this->pipCameraType = SKY_CAM;
            skyCamPos = this->currentHero->getCurrentPosition();
            skyCamPos.y = skyCamHeight;

            this->currentViewMatrix = glm::lookAt(skyCamPos, this->currentHero->getCurrentPosition(), -heroForwardVec);
            break;
        case FIRST_PERSON:
            //Compute first person view matrix
            this->pipCameraType = FIRST_PERSON;
            //Take direction vector and apply it to camera position (when rotating) and eye location (also for rotation)
            this->currentViewMatrix = glm::lookAt(pos - glm::vec3(heroForwardVec.x*2.5, 0, heroForwardVec.z*2.5), pos - (heroForwardVec*4.0f), glm::vec3(0, 1, 0));
            break;
        default:
            break;
    }
}



void HeroCameras::setHero(HeroVirtual *currentHero) {
    this->currentHero = currentHero;
}

void HeroCameras::update(GLboolean *keysPressed) {
    //Only free cam should move camera by key presses
    if (this->mainCameraType == ARCBALL){
        this->currentCameraPointer->setLookAtPoint(this->currentHero->getCurrentPosition());
        this->currentCameraPointer->recomputeOrientation();
        glUniform3fv(this->cameraPositionUniformLoc, 1, &this->currentCameraPointer->getPosition()[0]);
        return;
    }
    if (this->mainCameraType != FREE_CAM){
        return;
    }
    if (keysPressed == nullptr){
        return;
    }

    if(keysPressed[GLFW_KEY_SPACE] ) {
        // go backward if shift held down
        if(keysPressed[GLFW_KEY_LEFT_SHIFT] || keysPressed[GLFW_KEY_RIGHT_SHIFT] ) {
            this->currentCameraPointer->moveBackward(this->freeCameraSpeed.x);
        }
            // go forward
        else {
            this->currentCameraPointer->moveForward(this->freeCameraSpeed.x);
        }
    }
    // turn right
    if(keysPressed[GLFW_KEY_D] ) {
        this->currentCameraPointer->rotate(this->freeCameraSpeed.y, 0.0f);
    }
    // turn left
    if(keysPressed[GLFW_KEY_A] ) {
        this->currentCameraPointer->rotate(-this->freeCameraSpeed.y, 0.0f);
    }
    // pitch up
    if(keysPressed[GLFW_KEY_W] ) {
        this->currentCameraPointer->rotate(0.0f, this->freeCameraSpeed.y);
    }
    // pitch down
    if(keysPressed[GLFW_KEY_S] ) {
        this->currentCameraPointer->rotate(0.0f, -this->freeCameraSpeed.y);
    }
}


CSCI441::Camera *HeroCameras::getCamera() {
    return this->currentCameraPointer;
}

CameraType HeroCameras::getCurrentMainCameraType() {
    return this->mainCameraType;
}

glm::mat4 HeroCameras::getViewMatrix() {
    return this->currentViewMatrix;
}

void HeroCameras::recalculateViewMatrix() {
    if (this->currentHero == nullptr || this->currentViewMatrix == glm::mat4(1.0f)){
        return;
    }
    this->changeCamera(this->pipCameraType);
}
