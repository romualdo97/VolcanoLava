#version 150

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

// VARIYNG FROM VERTEX SHADER
in vec2 texCoordVarying;
in float noiseVarying;

// FRAGMENT SHADER OUTPUT
out vec4 outputColor;
 
void main()
{
	// compose the colour using the texture coordinates
	// and modulate it with the noise like ambient occlusion
	vec3 color = vec3( texCoordVarying * ( 1. - 1. * noiseVarying ), 0.0 );
	//color = vec3(  1. - 3. * noise  );
    vec3 texel = texture(tex0, texCoordVarying).xyz;
    //float rampFactor = texture(tex1, vec2(noiseVarying*1024*0.75, 0.5)).x;
	color = vec3(1.0 - 1.5 * noiseVarying) * texel/* * (mouse.x)*/;
	//color = mix(vec3(0.0, 0.0, 0.0), texel,  rampFactor*1.5);

    outputColor = vec4(color*vec3(1.5, 1.0, 1.0), 1.0);
    //outputColor = vec4(rampFactor);
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