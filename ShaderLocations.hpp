//
// Created by Benjamin Carlson on 10/10/21.
//

#ifndef MP_MODELSHADERLOCATIONS_H
#define MP_MODELSHADERLOCATIONS_H

/// \desc The shader locations to pass to the models
struct ModelShaderLocations{
    GLuint shaderProgramHandle;
    GLint mvpMatUniformLocation;
    GLint modelMatUniformLocation;
    GLint normalMatUniformLocation;
    GLint matColorUniformLocation;
};

struct ShaderUniformLocations {
    /// \desc precomputed MVP matrix location
    GLint mvpMatrix;

    GLint modelMatrix;

    /// \desc material diffuse color location
    GLint materialColor;

    GLint normalMat;

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
