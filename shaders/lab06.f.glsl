#version 410 core

// uniform inputs
// TODO #E
uniform sampler2D textureMap;

// varying inputs
// TODO #D
in vec2 toFrag;

// fragment outputs
out vec4 fragColorOut;

void main() {
    // TODO #F
    vec4 tempVar = texture(textureMap, toFrag);

    // TODO #G
    fragColorOut = tempVar;
}