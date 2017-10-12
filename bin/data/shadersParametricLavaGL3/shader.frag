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
uniform sampler2DRect tex0;	// explosion
uniform sampler2DRect tex1; // ramp texture
vec3 uLightDir = vec3(0, 0, 1);

// VARIYNG FROM VERTEX SHADER
in vec2 vTexCoord;
in float vNoise;
in vec3 vNormal;

// FRAGMENT SHADER OUTPUT
out vec4 outputColor;
 
void main()
{
	// compose the colour using the texture coordinates
	// and modulate it with the noise like ambient occlusion
	vec3 color = vec3( vTexCoord * ( 1. - 1. * vNoise ), 0.0 );
    vec3 texel = texture(tex0, vTexCoord).xyz;

#ifdef USE_NOISE
    //float rampFactor = texture(tex1, vec2(vNoise*1024*0.75, 0.5)).x;
	color = vec3(1.0 - 1.5 * vNoise) * texel/* * (mouse.x)*/;
	//color = mix(vec3(0.0, 0.0, 0.0), texel,  rampFactor*1.5);
#else
	color = vec3(dot(vNormal, normalize(uLightDir))) * texel;
#endif

    outputColor = vec4(color*vec3(1.5, 1.0, 1.0), 1.0);
}
/*#version 150

// this is how we receive the texture
uniform sampler2DRect tex0;
in vec2 uv_tex0; // varying

out vec4 outputColor;
 
void main()
{
    outputColor = texture(tex0, uv_tex0);;
}*/