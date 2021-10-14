//
// Created by Fibonacci on 10/8/21.
//

#ifndef A3_CAR_HPP
#define A3_CAR_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "../HeroVirtual.hpp"

class Car : public virtual HeroVirtual{

public:
    Car(GLuint shaderHandle, GLint mvpMatUniformLoc, GLint normalMatUniformLoc, GLint matColorUniformLoc, GLfloat WORLD_SIDE_LENGTH);

    void drawCar(glm::mat4 viewMatrix, glm::mat4 projMatrix);

    void moveHeroForward() override;

    glm::vec3 getCurrentPosition() override;

    void moveHeroBackward() override;

    void turnHero(GLfloat theta) override;

    glm::mat4 getCurrentModelMat() override;

    void leftClickAction() override{};

    void startMoving() override{};

    void stopMoving() override{};

    GLint getFirstPersonCamZModifer() override { return 1;};

    glm::vec3 getFirstPersonCamPosition() override{
        return this->getCurrentPosition();
    };
private:
    GLuint shaderProgramHandle;
    GLint mvpMatrixUniformLocation;
    GLint normalMatrixUniformLocation;
    GLint materialColorUniformLocation;

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);

    GLfloat WORLD_SIDE_LENGTH;

    GLfloat wheelAngle = 0.0f;

    glm::vec3 currentWorldPosition = {0, 0, 0};

    const glm::vec3 wheelColor = {0.1, 0.1, 0.1};
    const glm::vec3 bodyColor = {0.9, 0.05, 0.05};
    const glm::vec3 teapotColor = {0.1, 0.8, 0.4};
    const glm::vec3 axelColor = {0.5, 0.5, 0.5};

    const GLfloat wheelInnerRadius = 0.25;
    const GLfloat wheelOuterRadius = 0.5;
    const GLfloat carYPosition = wheelOuterRadius+wheelInnerRadius;

    const GLfloat moveSpeed = 0.1;

    //The left/right translation for the wheels, original state is right wheel
    const glm::vec3 wheelLRTranslation = {1.5, 0, 0};
    //The front/back translation for the wheels, original state is front wheel
    const glm::vec3 wheelFBTranslation = {0, 0, 2.25};

    void drawWheel(bool isFront, bool isRight, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawAxel(bool isFront, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void updateCurrentPosition();

    void updateWheelRotation(bool isMovingForward);

    bool testCarShouldMove(GLfloat testMoveSpeed);
};


#endif //A3_CAR_HPP
