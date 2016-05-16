#ifndef POST_PROCESS_HPP
#define POST_PROCESS_HPP

const char VERTEX_SHADER_POST_PROCESS[] = STRINGIFY(
    void main(void)
    {
        gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
        gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
    }
);

const char FRAGMENT_SHADER_POST_PROCESS[] = STRINGIFY(
    uniform sampler2D scene;
    uniform sampler2D height;
    uniform vec3 color;
    uniform vec2 directionalBlur;
    uniform float time;
    uniform float useSSAO;

vec4 Bloom()
{
    vec4 final;
	float quantity = 1.0;
	for(int i=-3; i<=3; ++i) {
		for(int j=-3; j<=3; ++j) {
			vec4 color = texture2D(scene, gl_TexCoord[0].xy+vec2(i, j)*0.004);
			float intensity;
			if(i == 0 && j == 0) final += color;
			else if((color.r+color.g+color.b)/3.0 > 0.6) {
			    final += color;
			    quantity += 1.0;
			}
		}
	}
	final /= quantity;
	final.a = 1.0;
	if(final.r > 1.0) final.r = 1.0;
	if(final.g > 1.0) final.g = 1.0;
	if(final.b > 1.0) final.b = 1.0;
	return final;
}
vec4 Bloom2()
{
    vec4 sum = vec4(0);
   vec4 bloomColor;
   bloomColor.a=1.0;
   vec2 texCoord = gl_TexCoord[0].xy;

   int j;
   int i;

   for( i= -4 ;i < 4; i++)
   {
        for (j = -3; j < 3; j++)
        {
            sum += texture2D(scene, texCoord + vec2(j, i)*0.004) * 0.25;
        }
   }
       if (texture2D(scene, texCoord).r < 0.3)
    {
       bloomColor = sum*sum*0.012 + texture2D(scene, texCoord);
    }
    else
    {
        if (texture2D(scene, texCoord).r < 0.5)
        {
            bloomColor = sum*sum*0.009 + texture2D(scene, texCoord);
        }
        else
        {
            bloomColor = sum*sum*0.0075 + texture2D(scene, texCoord);
        }
    }
	return bloomColor;
}
    void main(void)
    {
        //vec3 current = texture2D(scene, gl_TexCoord[0].xy).rgb;
        //vec3 final = current*color;
        directionalBlur /= 16.0;
        vec2 currentPos = gl_TexCoord[0].xy;
        vec3 pix = vec3(0.0, 0.0, 0.0);
        for(int i=0; i<16; ++i) {
            pix += texture2D(scene, currentPos);
            currentPos += directionalBlur;
        }
        pix /= 16.0;
        gl_FragColor = vec4(pix*color, 1.0);

        if(useSSAO > 0.5f) {
            vec3 A = texture2D(height, gl_TexCoord[0].xy);
            float mul = 1.0;
            for(int i=-15; i<=15; ++i) {
                for(int j=-15; j<=15; ++j) {
                    if(i == 0 && j == 0) continue;
                    vec3 B = texture2D(height, gl_TexCoord[0].xy-vec2(1.0/1024.0, 1.0/768.0)*vec2(i, j)).rgb;
                    if(B.r > A.r) mul -= (B.r-A.r)*0.003;//sqrt(i*i+j*j);
                }
            }
            if(mul < 0.0) mul = 0.0;
            gl_FragColor *= mul;
            gl_FragColor.a = 1.0;
        }
    }
);

#endif
