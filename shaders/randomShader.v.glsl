#version 410 core

// uniform inputs
uniform mat4 mvpMatrix;

// attribute inputs
layout(location = 0) in vec3 vPos;
in vec3 vNormal;


// varying outputs
out float displacement;

// pseudorandom noise function from https://stackoverflow.com/questions/12964279/whats-the-origin-of-this-glsl-rand-one-liner
float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main() {
    // get spherical coordinates
    float theta = atan(vPos.y / vPos.x);
    float phi = acos(vPos.z / (sqrt(vPos.x * vPos.x + vPos.y * vPos.y + vPos.z * vPos.z)));

    // calculate displacement and new position
    displacement = rand(vec2(theta, phi));
    vec3 newPos = vPos + vNormal * displacement * 0.5;

    gl_Position = mvpMatrix * vec4(newPos, 1.0);
}