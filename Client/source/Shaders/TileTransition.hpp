#ifndef TILE_TRANSITION_HPP
#define TILE_TRANSITION_HPP

const char VERTEX_SHADER_TILE_TRANSITION[] = STRINGIFY(
    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    }
);

const char FRAGMENT_SHADER_TILE_TRANSITION[] = STRINGIFY(
    uniform float texUpLeft = 0.0;
    uniform float texUp = 0.0;
    uniform float texUpRight = 0.0;
    uniform float texRight = 0.0;
    uniform float texDownRight = 0.0;
    uniform float texDown = 0.0;
    uniform float texDownLeft = 0.0;
    uniform float texLeft = 0.0;

    void main(void)
    {
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

        gl_FragColor = vec4(1.0-texDistance, 1.0-texDistance, 1.0-texDistance, 1.0);
    }
);

#endif
