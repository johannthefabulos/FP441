//
// Created by Benjamin Carlson on 10/12/21.
//

#ifndef MP_HEROVIRTUAL_HPP
#define MP_HEROVIRTUAL_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class HeroVirtual{

public:
    /// \desc Returns the current position of the hero
    /// \return (x, y, z) position in world space. glm::vec3
    virtual glm::vec3 getCurrentPosition() = 0;

    /// \desc Rotates the hero around (0, 1, 0) by the given value of theta
    /// \param theta The angle of rotation in radians
    virtual void turnHero(GLfloat theta) = 0;

    /// \desc Gives the ability to run certain actions when moving begins
    virtual void startMoving() = 0;
    /// \desc Tells the hero to move itself forward
    virtual void moveHeroForward() = 0;
    /// \desc Tells the hero to move itself backward
    virtual void moveHeroBackward() = 0;
    /// \desc Gives the ability to run certain actions when moving stops
    virtual void stopMoving() = 0;

    /// \desc Retrieve the location of the first person camera position in world coordinates
    /// \return First person camera position (glm::vec3)
    virtual glm::vec3 getFirstPersonCamPosition() = 0;

    /// \desc Certain heroes may move in a specific direction,
    ///     this z modifier tells the first person camera which direction to point
    /// \return Z modifier
    virtual GLint getFirstPersonCamZModifier() = 0;

    /// \desc Return current model matrix
    /// \return Hero's current model matrix (glm::mat4)
    virtual glm::mat4 getCurrentModelMat() = 0;

    /// \desc Gives the ability to run certain actions when GLFW_MOUSE_BUTTON_LEFT is pressed
    virtual void leftClickAction() = 0;
};

#endif //MP_HEROVIRTUAL_HPP
