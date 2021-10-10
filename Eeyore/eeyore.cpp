#include "eeyore.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <CSCI441/objects.hpp>
#include <CSCI441/OpenGLUtils.hpp>

#ifndef M_PI
#define M_PI 3.14159265
#endif

eeyore::eeyore( GLuint shaderProgramHandle, GLint mvpMtxUniformLocation, GLint normalMtxUniformLocation, GLint materialColorUniformLocation ) {

    _shaderProgramHandle                            = shaderProgramHandle;
    _shaderProgramUniformLocations.mvpMtx           = mvpMtxUniformLocation;
    _shaderProgramUniformLocations.normalMtx        = normalMtxUniformLocation;
    _shaderProgramUniformLocations.materialColor    = materialColorUniformLocation;


    _colorSeat = glm::vec3(0.0f, 0.0f, 1.0f );
    _scaleSeat = glm::vec3(2.0f, 1.0f, 3.0f );
    _colorBar = glm::vec3(1.0f, 0.0f, 0.0f );
    _scaleBar = glm::vec3(0.3f, 2.0f, 0.3f );
    _transBar1 = glm::vec3(.17,-.25,.27);
    _transBar2 = glm::vec3(-.17,-.25,.27);
    _transBar3 = glm::vec3(.17,-.25,-.27);
    _transBar4 = glm::vec3(-.17,-.25,-.27);
    _transBar[0] = _transBar1;
    _transBar[1] = _transBar2;
    _transBar[2] = _transBar3;
    _transBar[3] = _transBar4;
    _colorWheel = glm::vec3(0.0f, 1.0f, 0.0f );
    _scaleWheel = glm::vec3(1.0f, 1.0f, 1.0f );
    _transWheel = glm::vec3(0,-.25,0);
    _rotateWheel = M_PI / 2.0f;

}

void eeyore::drawCar(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) {
    glUseProgram( _shaderProgramHandle );

    modelMtx = glm::rotate( modelMtx, theta, CSCI441::Y_AXIS );
//    modelMtx = glm::rotate( modelMtx, _rotatePlaneAngle, CSCI441::Z_AXIS );
  //  _drawCarSeat(modelMtx, viewMtx, projMtx);        // the body of our plane
    _drawBar(0,modelMtx, viewMtx, projMtx);
    _drawBar(1,modelMtx, viewMtx, projMtx);
    _drawBar(2,modelMtx, viewMtx, projMtx);
    _drawBar(3,modelMtx, viewMtx, projMtx);
    //_drawWheel(false,modelMtx,viewMtx,projMtx);
    //_drawWheel(true,modelMtx,viewMtx,projMtx);
}

void eeyore::rotateX(int x){
    theta+= .02*x;
    _angleAni += .02;
}
void eeyore::move(int x){

    direc = direc + glm::vec3(sin(theta)*.01*x,0, cos(theta)*.01*x);
    _angleAni += (x/abs(x))*.02;
}

void eeyore::_drawCarSeat( glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {
    modelMtx = glm::scale(modelMtx, _scaleSeat );

    _computeAndSendMatrixUniforms(modelMtx, viewMtx, projMtx);

    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &_colorSeat[0]);

    CSCI441::drawSolidCube( .2 );
}
void eeyore::_drawBar(int ind,glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {

    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transBar[ind] );
    modelMtx1 = glm::scale(modelMtx1, _scaleBar );

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &_colorBar[0]);

    CSCI441::drawSolidCube( .2);
}
void eeyore::_drawWheel(bool leftWheel,glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx ) const {

    glm::mat4 modelMtx1 = glm::translate( modelMtx, _transWheel );
    modelMtx1 = glm::scale(modelMtx1, _scaleWheel );
    if(leftWheel){
        modelMtx1 = glm::rotate(modelMtx1,-1*_rotateWheel,CSCI441::Z_AXIS);
        modelMtx1 = glm::rotate(modelMtx1,_angleAni,CSCI441::Y_AXIS);
    }else{
        modelMtx1 = glm::rotate(modelMtx1,_rotateWheel,CSCI441::Z_AXIS);
        modelMtx1 = glm::rotate(modelMtx1,-1*_angleAni,CSCI441::Y_AXIS);
    }

    _computeAndSendMatrixUniforms(modelMtx1, viewMtx, projMtx);

    glUniform3fv(_shaderProgramUniformLocations.materialColor, 1, &_colorWheel[0]);

    CSCI441::drawSolidCylinder( 0,.15,.1,100,10);
}


void eeyore::_computeAndSendMatrixUniforms(glm::mat4 modelMtx, glm::mat4 viewMtx, glm::mat4 projMtx) const {
    // precompute the Model-View-Projection matrix on the CPU
    glm::mat4 mvpMtx = projMtx * viewMtx * modelMtx;
    // then send it to the shader on the GPU to apply to every vertex
    glProgramUniformMatrix4fv( _shaderProgramHandle, _shaderProgramUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );

    glm::mat3 normalMtx = glm::mat3( glm::transpose( glm::inverse( modelMtx )));
    glProgramUniformMatrix3fv( _shaderProgramHandle, _shaderProgramUniformLocations.normalMtx, 1, GL_FALSE, &normalMtx[0][0] );
}
