#version 410 core

// uniform inputs

// varying inputs
uniform vec3 materialColor;     // interpolated color for this fragment

uniform float materialShininess;
in vec3 fragNormal;
in vec3 fragPos;
uniform vec3 cameraPos;

struct LightSource{
    vec3 lightColor;
    vec3 lightPos;
};

uniform LightSource pointLight;
uniform LightSource spotLight;
uniform LightSource directLight;

// outputs
out vec4 fragColorOut;                  // color to apply to this fragment

void applyIllumination(in vec3 lightDirection, in bool doAttenuate, out vec3 illColor){
    float ambientStrength = 0.1;

    vec3 normal = normalize(fragNormal);

    vec3 illumDiffuse = max(dot(lightDirection,normal), 0) * vec3(1.0);
    vec3 illumAmbient = vec3(ambientStrength);

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect(-lightDirection, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), materialShininess);
    vec3 specular = 0.5 * spec * vec3(1.0);

    vec3 finalColor = (illumDiffuse + illumAmbient + specular);
    if (doAttenuate){
        vec3 abcVec = vec3(1, 0, 0.5);
        float d = length(lightDirection);
        vec3 dVec = vec3(1, d, pow(d, 2));
        illColor = finalColor / (dot(abcVec, dVec));
        return;
    }
    illColor = finalColor;
}

void main() {
    // pass the interpolated color through as output
    vec3 pointIlluminationVal;
    vec3 pointLightDir = normalize(pointLight.lightPos - fragPos);
    applyIllumination(pointLightDir, true, pointIlluminationVal);

    vec3 directionalIllumVal;
    applyIllumination(normalize(directLight.lightPos), false, directionalIllumVal);

    vec3 spotLightIllumVal = vec3(0);
    float alpha = 0.784;
    if (dot(normalize(spotLight.lightPos - fragPos), fragNormal) > alpha){
        spotLightIllumVal = pointIlluminationVal;
    }
    pointIlluminationVal = pointIlluminationVal * pointLight.lightColor;
    directionalIllumVal = directionalIllumVal * directLight.lightColor;
    spotLightIllumVal = spotLightIllumVal * spotLight.lightColor;

    //Directional Light
    vec3 finalColor = (pointIlluminationVal + directionalIllumVal + spotLightIllumVal) * materialColor;
    fragColorOut = vec4(finalColor, 1.0);
}