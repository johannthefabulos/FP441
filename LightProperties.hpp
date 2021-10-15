//
// Created by Benjamin Carlson on 10/14/21.
//

#ifndef MP_LIGHTPROPERTIES_HPP
#define MP_LIGHTPROPERTIES_HPP

#include <glm/glm.hpp>

class LightProperties{

public:
    LightProperties(GLuint shaderProgram){
        this->shaderProgramHandle = shaderProgram;
    }

    glm::vec3 lightPosition = glm::vec3(1.0f);
    glm::vec3 lightColor = glm::vec3(1.0f);

    GLint lightPosUniformLoc = 0;
    GLint lightColorUniformLoc = 0;

    void sendUniforms(){
        glProgramUniform3fv(shaderProgramHandle, lightPosUniformLoc, 1, &lightPosition[0]);

        glProgramUniform3fv(shaderProgramHandle, lightColorUniformLoc, 1, &lightColor[0]);
    }
private:
    GLuint shaderProgramHandle;
};

#endif //MP_LIGHTPROPERTIES_HPP
