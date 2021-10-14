//
// Created by Fibonacci on 10/10/21.
//

#ifndef MP_THEWARRIOR_HPP
#define MP_THEWARRIOR_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ShaderLocations.hpp"
#include "../HeroVirtual.hpp"

class TheWarrior : public virtual HeroVirtual{

public:
    TheWarrior(ModelShaderLocations shaderLocations, GLfloat WORLD_SIDE_LENGTH);

    void drawWarrior(glm::mat4 viewMatrix, glm::mat4 projMatrix);

    void startMoving() override;
    void moveHeroForward() override;
    void moveHeroBackward() override;
    void stopMoving() override;

    glm::vec3 getFirstPersonCamPosition() override;

    void turnHero(GLfloat theta) override;
    glm::vec3 getCurrentPosition() override;

    glm::mat4 getCurrentModelMat() override;

    void leftClickAction() override;
private:
    ModelShaderLocations shaderLocations;

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);

    GLfloat WORLD_SIDE_LENGTH;

    glm::vec3 currentWorldPosition = {0, 0, 0};

    const glm::vec3 bodyColor = {1.0, 223.0f/255.0f, 196.0f/255.0f};
    const glm::vec3 shieldColor = {0.06f, 0.42f, 0.99f};
    const glm::vec3 swordColor = {0.82, 0.82, 0.82};
    const glm::vec3 outerEyeColor = {1.0f, 1.0f, 1.0f};
    const glm::vec3 innerEyeColor = {0.12f, 0.55f, 0.84f};

    GLfloat currentTime = 0;
    GLfloat movementTime = 0;
    const GLfloat initalCooldownTime = 2;
    GLfloat currentMoveCooldownTime = initalCooldownTime;
    const GLfloat timeDelta = glm::pi<GLfloat>()/256.0f;
    const GLfloat movementSpeed = 0.1;

    bool isMoving = false;
    bool isCoolingDown = false;

    GLfloat swordRotationAngle = 0.0f;

    //Body Constants
    const GLfloat bodyTopWidth = 0.6;
    const GLfloat bodyCenterWidth = 1.05;
    const GLfloat bodyBottomWidth = 0.85;
    const GLfloat bodyHeight = 3.5;

    const GLfloat neckTopWidth = 0.2;
    const GLfloat neckHeight = 0.3;

    const GLfloat bodyY = 1.5;

    //Leg Constants
    const GLfloat legLeftOffset = 0.45;
    const GLfloat legLength = 2;
    const GLfloat legWidthTop = 0.4;
    const GLfloat legWidthBottom = 0.2;

    //Foot Constants
    const GLfloat footLength = 0.8;
    const GLfloat footWidth = 0.4;
    const GLfloat footHeight = 0.3;

    //Arm constants
    const GLfloat armInitialRotation = glm::two_pi<GLfloat>()/3.0f;
    const GLfloat armLeftOffset = 0.3;
    const GLfloat armLength = 2;
    const GLfloat armStartWidth = 0.2;
    const GLfloat armEndWidth = 0.1;

    // Shield constants
    const GLfloat shieldRectWidth = 1.5;
    const GLfloat shieldRectHeight = 1;
    const GLfloat shieldDepth = 0.2;

    //Sword constants
    const GLfloat swordCenterSideLength = 0.3;
    const GLfloat swordCenterHeight = 2.5;

    const GLfloat swordHiltLength = swordCenterSideLength * 2;
    const GLfloat swordHiltWidth = swordCenterSideLength * 3;
    const GLfloat swordHiltHeight = 0.5;
    const GLfloat swordConeHeight = 0.4;

    //Head constants
    const GLfloat headRadius = 1;
    const GLfloat eyeLeftOffset = 0.3;
    const GLfloat outerEyeHeight = 0.3;
    const GLfloat outerEyeWidth = 0.25;
    const GLfloat innerEyeRadius = 0.1;

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawNeck(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawLeg(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawFoot(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawArm(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawShield(glm::mat4 armEndModelMtx, GLfloat armRotation, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawSword(glm::mat4 armEndModelMtx, GLfloat armRotation, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawEyes(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void updateCurrentPosition();

    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;

    bool testWarriorShouldMove(GLfloat testMoveSpeed);
};


#endif //MP_THEWARRIOR_HPP
