#version 410 core

// uniform inputs
uniform mat4 mvpMatrix;                 // the precomputed Model-View-Projection Matrix
uniform mat4 modelMatrix;

uniform mat3 normalMat;
// attribute inputs
layout(location = 0) in vec3 vPos;      // the position of this specific vertex in object space

in vec3 vNormal;

out vec3 fragNormal;
out vec3 fragPos;

void main() {
    // transform & output the vertex in clip space
    gl_Position = mvpMatrix * vec4(vPos, 1.0);

    fragNormal = normalize(normalMat * vNormal);
    fragPos = vec3(modelMatrix * vec4(vPos, 1));
}