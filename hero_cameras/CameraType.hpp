//
// Created by Benjamin Carlson on 10/13/21.
//

#ifndef MP_CAMERATYPE_HPP
#define MP_CAMERATYPE_HPP

#include <GLFW/glfw3.h>
#include <vector>

/// \desc Type of camera to use with value of corresponding key code
enum CameraType{
    ARCBALL = GLFW_KEY_Z,
    FREE_CAM = GLFW_KEY_X,
    FIRST_PERSON = GLFW_KEY_C,
    SKY_CAM = GLFW_KEY_V
};

/// \desc A list of available camera key codes
const std::vector<int> cameraTypeKeys{ARCBALL, FREE_CAM, FIRST_PERSON, SKY_CAM};

#endif //MP_CAMERATYPE_HPP
