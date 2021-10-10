//
// Created by Fibonacci on 10/10/21.
//

#ifndef MP_THEWARRIOR_HPP
#define MP_THEWARRIOR_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

class TheWarrior {
    TheWarrior(GLuint shaderHandle, GLint mvpMatUniformLoc, GLint normalMatUniformLoc, GLint matColorUniformLoc);

private:
    GLuint shaderProgramHandle;
    GLint mvpMatUniformLo

};


#endif //MP_THEWARRIOR_HPP
