#version 150

// CONSTANTS
//#define USE_NOISE

// UNIFORMS
/*	'sampler2dRect' data-type vs 'sampler2D'
 the real advantage is, that when you work in
 screen-space for post-processing effects it gets
 much easier for the programmer to work with non-normalized
 texture coordinates. Especially with deferred rendering many
 shaders work in screen-space.
 		https://www.opengl.org/discussion_boards/showthread.php/168643-Is-sampler2DRect-really-necessary*/

uniform sampler2D tex0;	// explosion
uniform sampler2D tex1; // ramp texture
uniform float time;
uniform float mouseX;
vec3 uLightDir = vec3(0, 0, 1);

// VARIYNG FROM VERTEX SHADER
in vec2 vTexCoord;
in float vNoise;

in float vNoise2;
in vec3 vNormal;

// FRAGMENT SHADER OUTPUT
out vec4 outputColor;
 
void main()
{
	// compose the colour using the texture coordinates
	// and modulate it with the noise like ambient occlusion
	vec3 color = vec3( vTexCoord * ( 1. - 1. * vNoise ), 0.0 );

    //vec3 texel = texture2D(tex0, vTexCoord).xyz;
    vec3 texel = texture(tex0, vTexCoord + vec2(vNoise2)).xyz;
    //texel = texture2D(tex0, vec2(vNoise2, vTexCoord.y)).xyz;

#ifdef USE_NOISE
    //float rampFactor = texture(tex1, vec2(vNoise*1024*0.75, 0.5)).x;
	color = vec3(1.0 - 1.5 * vNoise) * texel/* * (mouse.x)*/;
	//color = mix(vec3(0.0, 0.0, 0.0), texel,  rampFactor*1.5);
#else
	color = vec3(dot(vNormal, normalize(uLightDir))) * texel;
#endif

    outputColor = mix(vec4(color*vec3(1.0, 0.6, 0.6), 1.0), 
    				  vec4(color*vec3(1.8, 1.0, 1.0), 1.0), 
    				  max(0.0, min(mouseX, 1.0)));
    outputColor= texel;
}
