#version 410

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
out vec3 color;    // color to apply to this vertex

void main() {
    // transform & output the vertex in clip space
    gl_Position = mvpMatrix * vec4(vPos, 1.0);

    vec3 lightVec = normalize(-lightPos);
    vec3 viewVec = normalize(cameraPos - vPos);
    vec3 normal = normalize(normalMat * vNormal);

    vec3 illumDiffuse = lightColor * materialColor * max(dot(lightVec,normal), 0);

    vec3 reflectVec = -lightVec+2*(dot(normal,lightVec)*normal);

    vec3 illumSpec = materialColor * lightColor * pow(max(dot(viewVec,reflectVec),0),materialShininess);

    vec3 illumAmb = materialColor*lightColor;

    vec3 attenuation = vec3(5,0.1,0.01);
    vec3 dist = vec3(1,length(vPos),pow(length(vPos),2));


    color = (illumDiffuse +illumSpec+illumAmb)/dot(attenuation,dist);

}