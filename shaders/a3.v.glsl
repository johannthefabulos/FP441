#version 410 core

// uniform inputs
uniform mat4 mvpMatrix;                 // the precomputed Model-View-Projection Matrix

uniform mat3 normalMat;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 cameraPos;

uniform vec3 materialColor;             // the material color for our vertex (& whole object)
uniform float materialShininess;
// attribute inputs
layout(location = 0) in vec3 vPos;      // the position of this specific vertex in object space

in vec3 vNormal;

// varying outputs
layout(location = 0) out vec3 color;    // color to apply to this vertex

void main() {
    // transform & output the vertex in clip space
    gl_Position = mvpMatrix * vec4(vPos, 1.0);

    vec3 lightVec = normalize(-lightPos);

    vec3 worldNormal = normalize(normalMat * vNormal);

    vec3 illumDiffuse = lightColor * materialColor * max(dot(lightVec,worldNormal), 0);

    //Specular lighting
    vec3 reflectVec = reflect(lightVec, worldNormal);
    vec3 viewVec = normalize(cameraPos - vPos);
    float spec = pow(max(dot(viewVec, reflectVec), 0.0), materialShininess);
    vec3 illumSpec = lightColor * materialColor * spec;
    if (materialShininess == 0){
        illumSpec = vec3(0);
    }

    color = illumDiffuse + illumSpec;
}