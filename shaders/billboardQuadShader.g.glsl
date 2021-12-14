// we are using OpenGL 4.1 Core profile
#version 410 core

// ***** GEOMETRY SHADER PARAMETERS *****
layout(points) in;
layout( triangle_strip, max_vertices = 4 ) out;


// ***** GEOMETRY SHADER UNIFORMS *****
uniform mat4 projMatrix;

// ***** GEOMETRY SHADER INPUT *****

// ***** GEOMETRY SHADER OUTPUT *****
out vec2 myVarying;

// ***** GEOMETRY SHADER HELPER FUNCTIONS *****

// ***** GEOMETRY SHADER MAIN FUNCTION *****
void main() {
    gl_Position = projMatrix * (gl_in[0].gl_Position + vec4(-0.5,-0.5,0,1));
    myVarying = vec2(0,0);
    EmitVertex();

    gl_Position = projMatrix * (gl_in[0].gl_Position + vec4(-0.5,0.5,0,1));
    myVarying = vec2(1,0);
    EmitVertex();

    gl_Position = projMatrix * (gl_in[0].gl_Position + vec4(0.5,-0.5,0,1));
    myVarying = vec2(0,1);
    EmitVertex();

    gl_Position = projMatrix * (gl_in[0].gl_Position + vec4(0.5,0.5,0,1));
    myVarying = vec2(1,1);
    EmitVertex();

    EndPrimitive();
}
