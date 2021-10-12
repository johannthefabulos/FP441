#ifndef LAB05_PLANE_HPP
#define LAB05_PLANE_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>

class eeyore {
public:
    eeyore(GLuint shaderHandle, GLint mvpMatUniformLoc, GLint normalMatUniformLoc, GLint matColorUniformLoc, GLfloat WORLD_SIDE_LENGTH);

    void drawEeyore(glm::mat4 viewMatrix, glm::mat4 projMatrix);

    glm::vec3 getCurrentPosition();

    void driveForward();
    void driveBackward();
    void turnCar(GLfloat theta);


    glm::mat4 currentModelMatrix = glm::mat4(1.0f);
private:
    GLuint shaderProgramHandle;
    GLint mvpMatrixUniformLocation;
    GLint normalMatrixUniformLocation;
    GLint materialColorUniformLocation;

    GLfloat WORLD_SIDE_LENGTH;

    GLfloat wheelAngle = 0.0f;

    glm::vec3 currentWorldPosition = {0, 0, 0};

    const glm::vec3 wheelColor = {0.0f, 0.0f, 1.0f};
    const glm::vec3 bodyColor = {0.0f, 0.0f, 1.0f};
    const glm::vec3 tailColor = {0, 0, 0};
    const glm::vec3 axelColor = {0.5, 0.5, 0.5};

    const GLfloat wheelInnerRadius = 0.25;
    const GLfloat wheelOuterRadius = 0.5;
    const GLfloat carYPosition = wheelOuterRadius+wheelInnerRadius;

    const GLfloat moveSpeed = 0.1;

    //The left/right translation for the wheels, original state is right wheel
    const glm::vec3 wheelLRTranslation = {1.2, 0, 0};
    //The front/back translation for the wheels, original state is front wheel
    const glm::vec3 wheelFBTranslation = {0, 0, 1.6};

    void drawLeg(bool isFront, bool isRight, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawAxel(bool isFront, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void drawBody(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void computeAndSendMatUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx);

    void updateCurrentPosition();

    void updateWheelRotation(bool isMovingForward);

    bool testCarShouldMove(GLfloat testMoveSpeed);
};


#endif //LAB05_PLANE_HPP
