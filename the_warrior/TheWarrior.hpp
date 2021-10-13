//
// Created by Fibonacci on 10/10/21.
//

#ifndef MP_THEWARRIOR_HPP
#define MP_THEWARRIOR_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../ShaderLocations.hpp"

class TheWarrior {

public:
    TheWarrior(ModelShaderLocations shaderLocations, GLfloat WORLD_SIDE_LENGTH);

    void drawWarrior(glm::mat4 viewMatrix, glm::mat4 projMatrix);

    glm::vec3 getCurrentPosition();

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);
private:
    ModelShaderLocations shaderLocations;

    GLfloat WORLD_SIDE_LENGTH;

    glm::vec3 currentWorldPosition = {0, 0, 0};

    const glm::vec3 bodyColor = {1.0, 223.0f/255.0f, 196.0f/255.0f};
    const glm::vec3 shieldColor = {0.06f, 0.42f, 0.99f};
    const glm::vec3 swordColor = {0.82, 0.82, 0.82};

    const bool drawWireframe = false;

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

    const GLfloat headRadius = 1;

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawNeck(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawLeg(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawFoot(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawArm(bool isLeft, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawShield(glm::mat4 armEndModelMtx, GLfloat armRotation, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawSword(glm::mat4 armEndModelMtx, GLfloat armRotation, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //MP_THEWARRIOR_HPP
