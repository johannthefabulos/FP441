//
// Created by Fibonacci on 10/10/21.
//

#ifndef MP_MODELSHADERLOCATIONS_H
#define MP_MODELSHADERLOCATIONS_H

struct ModelShaderLocations{
    GLuint shaderProgramHandle;
    GLint mvpMatUniformLocation;
    GLint normalMatUniformLocation;
    GLint matColorUniformLocation;
};

struct ShaderUniformLocations {
    /// \desc precomputed MVP matrix location
    GLint mvpMatrix;
    /// \desc material diffuse color location
    GLint materialColor;

    GLint normalMat;

    GLint lightColor;

    GLint lightPos;

    GLint cameraPos;

    GLint materialShininess;

};
/// \desc stores the locations of all of our shader attributes
struct ShaderAttributeLocations {
    /// \desc vertex position location
    GLint vPos;

    GLint vNormal;

};

#endif //MP_MODELSHADERLOCATIONS_H
