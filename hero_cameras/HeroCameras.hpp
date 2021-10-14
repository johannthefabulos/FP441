//
// Created by Fibonacci on 10/13/21.
//

#ifndef MP_HEROCAMERAS_HPP
#define MP_HEROCAMERAS_HPP

#include <CSCI441/Camera.hpp>
#include <CSCI441/ArcballCam.hpp>
#include <CSCI441/FreeCam.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../HeroVirtual.hpp"
#include "CameraType.hpp"

class HeroCameras {

public:
    HeroCameras(GLint cameraPosUniformLoc);

    ~HeroCameras();

    void changeCamera(int possibleKeyCode);

    void setHero(HeroVirtual* currentHero);

    void update(GLboolean *keysPressed);

    void recalculateViewMatrix();

    CSCI441::Camera* getCamera();

    CameraType getCurrentMainCameraType();

    glm::mat4 getViewMatrix();

private:
    CSCI441::Camera* currentCameraPointer = nullptr;
    CSCI441::ArcballCam* arcballCam = nullptr;
    CSCI441::FreeCam* freeCam = nullptr;

    glm::mat4 currentViewMatrix = glm::mat4 (1.0f);
    const glm::vec2 freeCameraSpeed = glm::vec2(0.1f, 0.01f);
    const GLfloat skyCamHeight = 20;
    CameraType mainCameraType = ARCBALL;
    CameraType pipCameraType = SKY_CAM;
    HeroVirtual* currentHero = nullptr;

    GLint cameraPositionUniformLoc;
};


#endif //MP_HEROCAMERAS_HPP
