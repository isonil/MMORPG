#ifndef WATER_HPP
#define WATER_HPP

const char VERTEX_SHADER_WATER[] = STRINGIFY(
    varying vec4 screenPos;

    void main(void)
    {
        screenPos = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_Position = screenPos;
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
    uniform vec2 tileScreenPos; // tile position on a screen (0.0 to 1.0)
    uniform vec2 tileWorldPos; // tile position in a game world (0.0 to world size)
    uniform float tileSize;

    // texture splatting
    uniform sampler2D textureSplattingTexture;
    uniform sampler2D textureSplattingMask;
    //

    varying vec4 screenPos;

    void main(void)
    {
        /*
            Translate texCoords so 1 unit means 5 tiles length.
            waterCoord - current pixel position in 1 'big' water tile (0.0 to 1.0)
        */
        vec2 waterCoord = gl_TexCoord[0].xy*0.2;
        waterCoord.x += tileX*0.2;
        waterCoord.y += tileY*0.2;

        /*
            Translate screenPos to positive values.
        */
        screenPos.x += 1.0; screenPos.x *= 0.5;
        screenPos.y += 1.0; screenPos.y *= 0.5;
        screenPos.y = 1.0-screenPos.y;

        /*
            worldPos - pixel position in a game world
            noiseOffset - offset given by wave mapping
        */
        vec2 worldPos = tileWorldPos+gl_TexCoord[0].xy*tileSize;
        float noiseOffset = texture2D(waterNoiseTexture, vec2(mod(worldPos.x/1000.0 + time/20.0, 1.0), mod(worldPos.y/1000.0 + time/20.0, 1.0))).r/20.0;

        float specular = 0.0+tileScreenPos.x/10000.0;
        float distance = length(vec2(0.5, 0.0)-vec2(screenPos.x, screenPos.y/4.0)); // /(1024.0/768.0)
        if(distance < 0.149) {
            vec3 lightPos_xyz = vec3(0.5, 0.0, 0.3);
            vec3 texCoord_xyz = vec3(screenPos.xy, 0.0);
            vec3 lightDir = normalize(lightPos_xyz-texCoord_xyz);
            vec3 normal = texture2D(waterNormalMapTexture, vec2(mod(waterCoord.x+time/40.0+noiseOffset, 1.0), mod(waterCoord.y+time/40.0+noiseOffset, 1.0))).rgb*2.0-1.0;
            vec3 eyeVecNormal = vec3(0.0, 0.0, 1.0);
            vec3 reflectVec = normalize(-reflect(lightDir, normal));
            specular = pow(max(dot(reflectVec, eyeVecNormal), 0.0), 10.0);
            specular *= (0.15-distance)*(1.0/0.15);
        }

        vec4 newCol = vec4(texture2D(waterColorMapTexture, vec2(mod(waterCoord.x+time/40.0+noiseOffset, 1.0), mod(waterCoord.y+time/40.0+noiseOffset, 1.0))).rgb+vec3(specular,specular,specular/2.0), 1.0);

        distance = length(vec2(0.5, 0.0)-vec2(screenPos.x, screenPos.y));
        if(distance > 0.7) distance = 0.7;
        float sunDiffuse = (0.7-distance)*(1.0/0.7);
        if(sunDiffuse > 0.8) sunDiffuse = 0.8;
        vec4 sunCol = vec4(1.0, 0.85, 0.35, sunDiffuse);

        vec2 skyPos = vec2(mod(worldPos.x/1500.0+time/140.0, 1.0), mod(worldPos.y/1500.0, 1.0));
        vec4 skyCol = texture2D(skyTexture, vec2(mod(skyPos.x+noiseOffset, 1.0), mod(skyPos.y+noiseOffset, 1.0)));
        gl_FragColor = vec4(newCol.r*0.75+skyCol.r*0.25, newCol.g*0.75+skyCol.g*0.25, newCol.b*0.75+skyCol.b*0.25, 1.0);
        gl_FragColor = vec4(sunCol.rgb * sunCol.a + gl_FragColor.rgb * (1.0-sunCol.a), 1.0);
        if(gl_FragColor.r > 1.0) gl_FragColor.r = 1.0;
        if(gl_FragColor.g > 1.0) gl_FragColor.g = 1.0;
        if(gl_FragColor.b > 1.0) gl_FragColor.b = 1.0;
/*
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
            texDistance = (texDistance*texDistance+texDistance)*0.5;
            gl_FragColor.rgb = texDistance*gl_FragColor.rgb + (1.0-texDistance)*texture2D(textureSplattingTexture, gl_TexCoord[0].xy).rgb;
        }*/

        float mask = texture2D(textureSplattingMask, gl_TexCoord[0].xy).r;
        gl_FragColor.rgb = texture2D(textureSplattingTexture, gl_TexCoord[0].xy).rgb*mask+gl_FragColor.rgb*(1.0-mask);

        //vec3 FINAL = vec3(screenPos.x, screenPos.x, screenPos.x);

        //gl_FragColor.rgb = gl_FragColor.rgb*0.001+FINAL;
        //gl_FragColor.rgb += vec3(noiseOffset*10.0, noiseOffset*10.0, noiseOffset*10.0);
    }
);

#endif
