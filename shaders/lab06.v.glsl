#version 410 core

// uniform inputs
uniform mat4 mvpMatrix;

// attribute inputs
layout(location = 0) in vec3 vPos;
// TODO #A
in vec2 texCoord;

// varying outputs
// TODO #B
out vec2 toFrag;

void main() {
    gl_Position = mvpMatrix * vec4(vPos, 1.0);

    // TODO #C
    toFrag = texCoord;
}