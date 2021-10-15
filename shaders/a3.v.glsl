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

    vec3 abcVec = vec3(0.2, 0, 1);
    float d = length(lightVec);
    vec3 dVec = vec3(1, d, pow(d, 2));

    //Specular lighting
    vec3 viewVec = normalize(cameraPos - vPos);
    vec3 refectVec = -lightVec + (2 * (dot(lightVec, worldNormal) * worldNormal));
    vec3 illumSpec = materialColor * lightColor * pow(max(dot(refectVec, viewVec), 0), materialShininess);

    vec3 ambientColorVec = lightColor * 0.1;
    vec3 illumAmbient = vec3(0);//ambientColorVec * materialColor;

//    if (materialShininess == 0){
//        illumSpec = vec3(0);
//    }


    color = (illumDiffuse + illumSpec + illumAmbient)/(dot(abcVec, dVec));
}