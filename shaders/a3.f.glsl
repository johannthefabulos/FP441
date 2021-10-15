#version 410 core

// uniform inputs

// varying inputs
uniform vec3 materialColor;     // interpolated color for this fragment
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform float materialShininess;
in vec3 fragNormal;
in vec3 fragPos;
uniform vec3 cameraPos;
// outputs
out vec4 fragColorOut;                  // color to apply to this fragment

void main() {
    // pass the interpolated color through as output
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 normal = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);

    vec3 illumDiffuse = lightColor * max(dot(lightDir,normal), 0);
    vec3 illumAmbient = ambient * lightColor;

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = 0.5 * spec * lightColor;

    vec3 abcVec = vec3(1, 0, 0.5);
    float d = length(lightDir);
    vec3 dVec = vec3(1, d, pow(d, 2));

    vec3 finalColor = (illumDiffuse + illumAmbient + specular) * materialColor;
    finalColor = finalColor / (dot(abcVec, dVec));
    fragColorOut = vec4(finalColor, 1.0);
}