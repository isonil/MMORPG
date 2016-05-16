#ifndef LIGHT_TO_LIGHT_DIFFUSE_MAP_HPP
#define LIGHT_TO_LIGHT_DIFFUSE_MAP_HPP

const char VERTEX_SHADER_LIGHT_TO_LIGHT_DIFFUSE_MAP[] = STRINGIFY(
    varying vec2 screenPos;

    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
        screenPos = (gl_Position+1.0)/2.0;
    }
);

const char FRAGMENT_SHADER_LIGHT_TO_LIGHT_DIFFUSE_MAP[] = STRINGIFY(
    uniform sampler2D previousLightDiffuseMap;
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
        height = (height-0.196)/2.0+0.196; // scale a bit, 255 color difference = 0.5 height
        float luminosity = texture2D(lightTexture, gl_TexCoord[0].xy).r;

        if(abs(height-0.196) < 0.01) {
            luminosity *= texture2D(shadowMap, vec2(screenPos.x, screenPos.y)).r;
        }

        vec3 lightPos3D = vec3(lightPos.x, lightPos.y, 0.3);
        vec3 texCoord3D = vec3(screenPos.x, 1.0-screenPos.y, 0.0);
        vec3 lightDir = normalize(lightPos3D-texCoord3D);
        vec3 normal = texture2D(normalMap, vec2(screenPos.x, screenPos.y)).xyz*2.0-1.0;
        float normalFactor = pow(max(0.0, dot(normal, lightDir)), 5.0);
        luminosity *= normalFactor;

        vec3 previousDiffuse = texture2D(previousLightDiffuseMap, screenPos).rgb;
        gl_FragColor = vec4(max(previousDiffuse.r, luminosity*lightCol.r),
                            max(previousDiffuse.g, luminosity*lightCol.g),
                            max(previousDiffuse.b, luminosity*lightCol.b), 1.0);

        /*float previousDiffuse = texture2D(previousLightDiffuseMap, screenPos).r;
        float newDiffuse = max(previousDiffuse, luminosity);
        gl_FragColor = vec4(newDiffuse, newDiffuse, newDiffuse, 1.0);*/
    }
);

#endif
