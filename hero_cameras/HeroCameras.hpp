//
// Created by Benjamin Carlson on 10/13/21.
//

#ifndef MP_HEROCAMERAS_HPP
#define MP_HEROCAMERAS_HPP

#include <CSCI441/Camera.hpp>
#include <CSCI441/ArcballCam.hpp>
#include <CSCI441/FreeCam.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../HeroVirtual.hpp"
#include "CameraType.hpp"

/// \desc Object managing camera movement, computation, and key changes
class HeroCameras {

public:
    HeroCameras(GLint cameraPosUniformLoc);

    ~HeroCameras();

    /// \desc Attempt to change the camera type based on the given keycode.
    /// \desc Ignores call if invalid key code.
    /// \param possibleKeyCode The keycode to attempt
    void changeCamera(int possibleKeyCode);

    /// \desc Sets the hero to allow for movement/view matrix calculations based on hero location
    /// \param currentHero Currently selected hero
    void setHero(HeroVirtual* currentHero);

    /// \desc Attempt to update the camera location
    /// \example ARCBALL camera ignores key presses and just follows current hero
    /// \example FREE_CAM camera moves based on key presses
    /// \param keysPressed An array of booleans indicating which keys are pressed (Key code as index)
    void update(GLboolean *keysPressed);

    /// \desc Recalculate the internal view matrix
    void recalculateViewMatrix();

    /// \desc Return the currently selected primary camera
    /// \return Camera objects
    CSCI441::Camera* getPrimaryCamera();

    /// \desc Return the type of the current primary camera
    /// \return The type of the primary camera
    CameraType getPrimaryCameraType();

    /// \desc Return the view matrix of the PIP camera (glm::mat4(1.0f) if no PIP camera selected)
    /// \return View matrix
    glm::mat4 getViewMatrix();

private:
    GLint cameraPositionUniformLoc;

    CSCI441::Camera* currentPrimaryCamera = nullptr;
    CSCI441::ArcballCam* arcballCam = nullptr;
    CSCI441::FreeCam* freeCam = nullptr;
    HeroVirtual* currentHero = nullptr;

    const glm::vec2 freeCameraSpeed = glm::vec2(0.1f, 0.01f);
    const GLfloat skyCamHeight = 20;

    glm::mat4 currentViewMatrix = glm::mat4 (1.0f);

    CameraType mainCameraType = ARCBALL;
    CameraType pipCameraType = SKY_CAM;
};


#endif //MP_HEROCAMERAS_HPP
