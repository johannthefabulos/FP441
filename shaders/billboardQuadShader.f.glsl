// we are using OpenGL 4.1 Core profile
#version 410 core

// ***** FRAGMENT SHADER UNIFORMS *****
uniform sampler2D image;
uniform int goldEaten;

// ***** FRAGMENT SHADER INPUT *****
in vec2 myVarying;

// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;


// ***** FRAGMENT SHADER HELPER FUNCTIONS *****


// ***** FRAGMENT SHADER MAIN FUNCTION *****
void main() {
    vec4 tempVar = texture(image,myVarying);

    if (goldEaten < 1) {
        fragColorOut = tempVar * vec4(0, 0, 1, 1); // blue
    } else if (goldEaten < 2) {
        fragColorOut = tempVar * vec4(0.69, 0.553, 0.341, 1); // bronze
    } else if (goldEaten < 3) {
        fragColorOut = tempVar * vec4(0.753, 0.753, 0.753, 1); // silver
    } else {
        fragColorOut = tempVar * vec4(1, 0.843, 0, 1); // gold
    }
}
