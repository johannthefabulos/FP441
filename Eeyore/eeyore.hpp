#ifndef EEYORE_HPP
#define EEYORE_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>
#include "../ShaderLocations.hpp"
#include "../HeroVirtual.hpp"

class eeyore : public virtual HeroVirtual {
public:
    eeyore(ModelShaderLocations shaderLocations, GLfloat WORLD_SIDE_LENGTH);

    void drawEeyore(glm::mat4 viewMatrix, glm::mat4 projMatrix);

    glm::vec3 getCurrentPosition() override;
    glm::mat4 getCurrentModelMat() override;

    void moveHeroForward() override;
    void moveHeroBackward() override;
    void turnHero(GLfloat theta) override;
    void leftClickAction() override;

    void startMoving() override{};

    void stopMoving() override{};

private:
    ModelShaderLocations shaderLocations;
    GLint mvpMatrixUniformLocation;
    GLint normalMatrixUniformLocation;
    GLint materialColorUniformLocation;

    glm::mat4 currentModelMatrix = glm::mat4(1.0f);

    GLfloat WORLD_SIDE_LENGTH;

    GLfloat wheelAngle = 0.0f;
    GLfloat headBob = 0;


    glm::vec3 currentWorldPosition = {0, 0, 0};

    const glm::vec3 wheelColor = {0.0f, 0.0f, 1.0f};
    const glm::vec3 bodyColor = {0.0f, 0.0f, 1.0f};
    const glm::vec3 tailColor = {0, 0, 0};
    const glm::vec3 noseColor = {0.98, 0.81, 0.69};
    bool direction = true;
    const GLfloat wheelInnerRadius = 0.25;
    const GLfloat wheelOuterRadius = 0.5;
    const GLfloat carYPosition = wheelOuterRadius+wheelInnerRadius;

    const GLfloat moveSpeed = 0.1;

    //The left/right translation for the wheels, original state is right wheel
    const glm::vec3 wheelLRTranslation = {1.2, 0, 0};
    //The front/back translation for the wheels, original state is front wheel
    const glm::vec3 wheelFBTranslation = {0, 0, 1.6};

    void drawLeg(bool isFront, bool isRight, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawHead(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void updateCurrentPosition();

    void updateWheelRotation(bool isMovingForward);

    bool testCarShouldMove(GLfloat testMoveSpeed);
};


#endif //LAB05_PLANE_HPP
