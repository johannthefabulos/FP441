#version 410 core

// uniform inputs
uniform vec3 color;                     // color for all fragments

// varying inputs
in float displacement;

// outputs
out vec4 fragColorOut;                  // color to apply to this fragment

void main() {
    // adjust color based on how much it's been moved
    vec3 newColor = color * displacement;
    fragColorOut = vec4(newColor, 1.0);
}