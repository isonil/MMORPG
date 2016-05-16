#ifndef SHADERS_HPP
#define SHADERS_HPP

#define STRINGIFY(x) #x

const char VERTEX_SHADER_LIGHT[] = STRINGIFY(
    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    }
);

const char VERTEX_SHADER_LIGHT_TO_LIGHT_MAP[] = STRINGIFY(
    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    }
);

const char FRAGMENT_SHADER_LIGHT_TO_LIGHT_MAP[] = STRINGIFY(
    unfirom sampler2D previousLightMap;
    uniform sampler2D normalMap;
    uniform sampler2D heightMap;
    uniform sampler2D shadowMap;
    uniform float ambientLight;
    uniform vec2 lightPos;

    void main(void)
    {
        gl_FragColor = texture2D(gl_TexCoord[0].x, gl_TexCoord[0].y);
        gl_FragColor = vec4(1.0, 0.0, 0.0, 0.0);
    }
);

const char FRAGMENT_SHADER_LIGHT[] = STRINGIFY(
    uniform sampler2D normalMap;
    uniform sampler2D heightMap;
    uniform sampler2D shadowMap;
    uniform float ambientLight;
    uniform vec2 lightPos;

    void main(void)
    {
        float height = texture2D(heightMap, vec2(gl_TexCoord[0].x, 1.0-gl_TexCoord[0].y)).r;
        height = (height-0.196)/2.0+0.196; // scale a bit, 255 color difference = 0.5 height
        float distanceFromLight = length(vec3(gl_TexCoord[0].xy, height)-vec3(lightPos, 0.196));

        distanceFromLight *= 100.0;
        float attenuation = 1.0+0.045*distanceFromLight+0.0075*distanceFromLight*distanceFromLight;
        float luminosity = 1.0/attenuation;
        distanceFromLight /= 100.0;

        if(distanceFromLight < 0.9) {
            luminosity = (0.9-distanceFromLight)*(1.0/0.9);
        }
        else luminosity = 0.0;

        if(texture2D(shadowMap, vec2(gl_TexCoord[0].x, 1.0-gl_TexCoord[0].y)).r < 1.0 &&
           abs(height-0.196) < 0.01) {
            //luminosity *= luminosity;
            //luminosity *= luminosity;
            luminosity *= texture2D(shadowMap, vec2(gl_TexCoord[0].x, 1.0-gl_TexCoord[0].y)).r;
        }
        /*
        if(texture2D(heightMap, vec2(gl_TexCoord[0].x, 1.0-gl_TexCoord[0].y)-lightDir2d*distanceFromLight/5.0).r > 0.8 &&
           abs(height-0.196) < 0.01) {
            luminosity *= luminosity;
        }
        */

        //// NORMAL MAPPING ///
        vec3 lightPos_xyz = vec3(lightPos.x, lightPos.y, 0.18);
        vec3 texCoord_xyz = vec3(gl_TexCoord[0].x, gl_TexCoord[0].y, 0.0);
        vec3 lightDir = normalize(lightPos_xyz-texCoord_xyz);
        vec3 normal = texture2D(normalMap, vec2(gl_TexCoord[0].x, 1.0-gl_TexCoord[0].y)).xyz*2.0-1.0;
        float additionalLight = max(0.0, dot(normal, lightDir));

        //// SPECULAR
        vec3 eyeVecNormal = vec3(0.0, 0.0, 1.0);
        vec3 reflectVec = normalize(-reflect(lightDir, normal));
        float specular = pow(max(dot(reflectVec, eyeVecNormal), 0.0), 10.0);
        specular *= 2.0;
        additionalLight *= additionalLight;
        additionalLight += specular;
        if(additionalLight > 1.0) additionalLight = 1.0;

        gl_FragColor = vec4(additionalLight*luminosity+ambientLight, additionalLight*luminosity+ambientLight, additionalLight*luminosity+ambientLight, 1.0);
        if(gl_FragColor.r > 1.0) gl_FragColor.r = 1.0;
        if(gl_FragColor.g > 1.0) gl_FragColor.g = 1.0;
        if(gl_FragColor.b > 1.0) gl_FragColor.b = 1.0;
    }
);

const char VERTEX_SHADER_WATER[] = STRINGIFY(
    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    }
);

const char FRAGMENT_SHADER_WATER[] = STRINGIFY(
    uniform sampler2D waterColorMapTexture;
    uniform sampler2D waterNormalMapTexture;
    uniform sampler2D waterNoiseTexture;
    uniform sampler2D skyTexture;
    uniform float time;
    uniform float tileX;
    uniform float tileY;
    uniform float x;
    uniform float y;
    uniform vec2 tileCornerRealPos;
    uniform float tileSize;

    // texture splatting
    uniform float texUpLeft = 0.0;
    uniform float texUp = 0.0;
    uniform float texUpRight = 0.0;
    uniform float texRight = 0.0;
    uniform float texDownRight = 0.0;
    uniform float texDown = 0.0;
    uniform float texDownLeft = 0.0;
    uniform float texLeft = 0.0;
    uniform sampler2D textureSplattingTexture;
    //

    void main(void)
    {
        vec2 texCoord = gl_TexCoord[0].xy/5.0;
        texCoord.x += 1.0/5.0 * tileX;
        texCoord.y += 1.0/5.0 * tileY;

        vec2 screenPos = vec2(x+gl_TexCoord[0].x/(1024.0/(256.0/6.0)), y+gl_TexCoord[0].y/(768.0/(256.0/6.0)));

        vec2 realPos = tileCornerRealPos+gl_TexCoord[0].xy*tileSize;

        vec4 noiseTexCol = texture2D(waterNoiseTexture, vec2(mod(realPos.x/1024.0 + time/20.0, 1.0), mod(realPos.y/768.0 + time/20.0, 1.0)));
        float reducedOffset = noiseTexCol.r/25.0;

        float specular = 0.0;
        float distance = length(vec2(0.7, 0.5)-vec2(screenPos.x, screenPos.y/(1024.0/768.0)));
        float distance2 = distance;
        if(distance > 0.1) distance = 0.1;
        if(distance < 0.099) {
            vec3 lightPos_xyz = vec3(0.7, 0.5, 0.3);
            vec3 texCoord_xyz = vec3(screenPos, 0.0);
            vec3 lightDir = normalize(lightPos_xyz-texCoord_xyz);
            vec3 normal = texture2D(waterNormalMapTexture, vec2(mod(texCoord.x+time/40.0+reducedOffset, 1.0), mod(texCoord.y+time/40.0+reducedOffset, 1.0))).rgb*2.0-1.0;
            vec3 eyeVecNormal = vec3(0.0, 0.0, 1.0);
            vec3 reflectVec = normalize(-reflect(lightDir, normal));
            specular = pow(max(dot(reflectVec, eyeVecNormal), 0.0), 10.0);
            specular *= (0.1-distance)*(1.0/0.3)*3.0;
        }

        // SUN //vec4 newCol = vec4(texture2D(waterColorMapTexture, vec2(mod(texCoord.x+time/40.0+reducedOffset, 1.0), mod(texCoord.y+time/40.0+reducedOffset, 1.0))).rgb+vec3(specular,specular/1.5,-specular/2.0),1.0);
        // MOON
        vec4 newCol = vec4(texture2D(waterColorMapTexture, vec2(mod(texCoord.x+time/40.0+reducedOffset, 1.0), mod(texCoord.y+time/40.0+reducedOffset, 1.0))).rgb+vec3(specular/1.2,specular/1.2,specular),1.0);

        if(newCol.r > 1.0) newCol.r = 1.0;
        if(newCol.g > 1.0) newCol.g = 1.0;
        if(newCol.b < 0.0) newCol.b = 0.0;

        if(distance2 > 0.12) distance2 = 0.12;
        float sunDiffuse = (0.12-distance2)*(1.0/0.12);
        sunDiffuse *= sunDiffuse;
        //vec4 sunCol = vec4(1.0, 0.9, 0.4, sunDiffuse); SUN
        vec4 sunCol = vec4(0.8, 0.8, 1.0, sunDiffuse); //MOON

        float height = noiseTexCol.r / 20.0;

        vec2 skyPos = vec2(mod(realPos.x/1500.0+time/140.0, 1.0), mod(realPos.y/1500.0, 1.0));
        vec4 skyCol = texture2D(skyTexture, vec2(mod(skyPos.x+reducedOffset, 1.0), mod(skyPos.y+reducedOffset, 1.0)));
        gl_FragColor = vec4(newCol.r*0.75+skyCol.r*0.25, newCol.g*0.75+skyCol.g*0.25, newCol.b*0.75+skyCol.b*0.25, 1.0);
        gl_FragColor = vec4(gl_FragColor.rgb + height, 1.0);
        gl_FragColor = vec4(sunCol.rgb * sunCol.a + gl_FragColor.rgb * (1.0-sunCol.a), 1.0);
        if(gl_FragColor.r > 1.0) gl_FragColor.r = 1.0;
        if(gl_FragColor.g > 1.0) gl_FragColor.g = 1.0;
        if(gl_FragColor.b > 1.0) gl_FragColor.b = 1.0;
        if(gl_FragColor.b < 0.0) gl_FragColor.b = 0.0;

        float texDistance = 1.0;
        bool diagonal = false;
        if(texUpLeft > 0.5 && texUp > 0.5 && texLeft > 0.5) {
            diagonal = true;
            if(gl_TexCoord[0].x > 1.0-gl_TexCoord[0].y) {
                texDistance = gl_TexCoord[0].y-(1.0-gl_TexCoord[0].x);
            }
            else texDistance = 0.0;
        }
        if(texUpRight > 0.5 && texUp > 0.5 && texRight > 0.5) {
            diagonal = true;
            if(gl_TexCoord[0].x < gl_TexCoord[0].y) {
                texDistance = gl_TexCoord[0].y - gl_TexCoord[0].x;
            }
            else texDistance = 0.0;
        }
        if(texDownRight > 0.5 && texDown > 0.5 && texRight > 0.5) {
            diagonal = true;
            if(gl_TexCoord[0].x < 1.0-gl_TexCoord[0].y) {
                texDistance = 1.0-gl_TexCoord[0].x-gl_TexCoord[0].y;
            }
            else texDistance = 0.0;
        }
        if(texDownLeft > 0.5 && texDown > 0.5 && texLeft > 0.5) {
            diagonal = true;
            if(gl_TexCoord[0].x > gl_TexCoord[0].y) {
                texDistance = gl_TexCoord[0].x - gl_TexCoord[0].y;
            }
            else texDistance = 0.0;
        }

        if(!diagonal) {
            if(texUpLeft > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].x-0.0)+abs(gl_TexCoord[0].y-0.0));
            if(texUp > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].y-0.0));
            if(texUpRight > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].x-1.0)+abs(gl_TexCoord[0].y-0.0));
            if(texRight > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].x-1.0));
            if(texDownRight > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].x-1.0)+abs(gl_TexCoord[0].y-1.0));
            if(texDown > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].y-1.0));
            if(texDownLeft > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].x-0.0)+abs(gl_TexCoord[0].y-1.0));
            if(texLeft > 0.5) texDistance = min(texDistance, abs(gl_TexCoord[0].x-0.0));
        }

        if(texDistance < 1.0) {
            gl_FragColor.rgb = texDistance*gl_FragColor.rgb + (1.0-texDistance)*texture2D(textureSplattingTexture, gl_TexCoord[0].xy).rgb;
        }
    }
);

const char VERTEX_SHADER_POST_PROCESS[] = STRINGIFY(
    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    }
);

const char FRAGMENT_SHADER_POST_PROCESS[] = STRINGIFY(
    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    }
);

#endif
