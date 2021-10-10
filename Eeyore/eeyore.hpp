#ifndef LAB05_PLANE_HPP
#define LAB05_PLANE_HPP

#include <GL/glew.h>

#include <glm/glm.hpp>

class eeyore {
public:
    /// \desc creates a simple plane that gives the appearance of flight
    /// \param shaderProgramHandle shader program handle that the plane should be drawn using
    /// \param mvpMtxUniformLocation uniform location for the full precomputed MVP matrix
    /// \param normalMtxUniformLocation uniform location for the precomputed Normal matrix
    /// \param materialColorUniformLocation uniform location for the material diffuse color
    car( GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation );

    /// \desc draws the model plane for a given MVP matrix
    /// \param modelMtx existing model matrix to apply to plane
    /// \param viewMtx camera view matrix to apply to plane
    /// \param projMtx camera projection matrix to apply to plane
    /// \note internally uses the provided shader program and sets the necessary uniforms
    /// for the MVP and Normal Matrices as well as the material diffuse color
    void drawCar(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx );



    glm::vec3 direc = glm::vec3(0,.4,0);
    float theta = 0;
    float phi = 0;

    void rotateX(int x);

    void move(int x);

private:
    GLuint _shaderProgramHandle;
    /// \desc stores the uniform locations needed for the plan information
    struct ShaderProgramUniformLocations {
        /// \desc location of the precomputed ModelViewProjection matrix
        GLint mvpMtx;
        GLint normalMtx;
        GLint materialColor;
    } _shaderProgramUniformLocations;


    glm::vec3 _colorSeat;
    glm::vec3 _scaleSeat;
    glm::vec3 _colorBar;
    glm::vec3 _scaleBar;
    glm::vec3 _transBar[4];
    glm::vec3 _transBar1;
    glm::vec3 _transBar2;
    glm::vec3 _transBar3;
    glm::vec3 _transBar4;
    glm::vec3 _colorWheel;
    GLfloat _rotateWheel;

    glm::vec3 _scaleWheel;
    glm::vec3 _transWheel;
    float _angleAni = 0;


    /// \desc draws just the plane's body
    /// \param modelMtx existing model matrix to apply to plane
    /// \param viewMtx camera view matrix to apply to plane
    /// \param projMtx camera projection matrix to apply to plane
    void _drawCarSeat(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const;

    void _computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;

    void _drawBar(int ind, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;

    void _drawWheel(bool leftWheel, glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const;
};


#endif //LAB05_PLANE_HPP
