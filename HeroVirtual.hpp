//
// Created by Fibonacci on 10/12/21.
//

#ifndef MP_HEROVIRTUAL_HPP
#define MP_HEROVIRTUAL_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class HeroVirtual{

public:
    virtual glm::vec3 getCurrentPosition() = 0;
    virtual void turnHero(GLfloat theta) = 0;

    virtual void startMoving() = 0;
    virtual void moveHeroForward() = 0;
    virtual void moveHeroBackward() = 0;
    virtual void stopMoving() = 0;

    virtual glm::vec3 getFirstPersonCamPosition() = 0;

    virtual glm::mat4 getCurrentModelMat() = 0;

    virtual void leftClickAction() = 0;
};

#endif //MP_HEROVIRTUAL_HPP
