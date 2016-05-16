#ifndef LIGHT_TO_LIGHT_SPECULAR_MAP_HPP
#define LIGHT_TO_LIGHT_SPECULAR_MAP_HPP

const char VERTEX_SHADER_LIGHT_TO_LIGHT_SPECULAR_MAP[] = STRINGIFY(
    varying vec2 screenPos;

    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
        screenPos = (gl_Position+1.0)/2.0;
    }
);

const char FRAGMENT_SHADER_LIGHT_TO_LIGHT_SPECULAR_MAP[] = STRINGIFY(
    uniform sampler2D previousLightSpecularMap;
    uniform sampler2D normalMap;
    uniform sampler2D heightMap;
    uniform sampler2D shadowMap;
    uniform sampler2D lightTexture;
    uniform float ambientLight;
    uniform vec2 lightPos;
    uniform vec3 lightCol;
    varying vec2 screenPos;

    void main(void)
    {
        float height = texture2D(heightMap, vec2(screenPos.x, screenPos.y)).r;
        float height1 = (height-0.196)/2.0+0.196; // scale a bit, 255 color difference = 0.5 height
        float height2 = (height-0.196)/30.0+0.196; // scale a bit, 255 color difference = 0.5 height

        float luminosity = texture2D(lightTexture, gl_TexCoord[0].xy).r;

        if(abs(height1-0.196) < 0.01) {
            luminosity *= texture2D(shadowMap, vec2(screenPos.x, screenPos.y)).r;
        }

        vec3 lightPos3D = vec3(lightPos.x, lightPos.y, 0.3); //0.3 0.5
        vec3 texCoord3D = vec3(screenPos.x, 1.0-screenPos.y, height2);
        vec3 lightDir = normalize(lightPos3D-texCoord3D);
        vec3 normal = texture2D(normalMap, vec2(screenPos.x, screenPos.y)).xyz*2.0-1.0;

        vec3 eyeVecNormal = vec3(0.0, 0.0, 1.0);
        vec3 reflectVec = normalize(-reflect(lightDir, normal));
        float specular = max(dot(reflectVec, eyeVecNormal), 0.0);
        //specular *= specular;
        specular *= 0.1;
        if(specular > 1.0) specular = 1.0; //NEEDED????

        //vec3 lightColor = vec3(1.0, 1.0, 0.8);
        //vec3 lightColor = vec3(1.0, 1.0, 0.7);
        vec3 previousSpecular = texture2D(previousLightSpecularMap, screenPos).rgb;
        vec3 newSpecular = previousSpecular+lightCol*(specular*luminosity);
        gl_FragColor = vec4(newSpecular, 1.0);
    }
);

#endif
