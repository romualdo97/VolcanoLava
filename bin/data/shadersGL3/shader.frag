#version 150

// this is how we receive the texture
uniform sampler2DRect tex0;
/*	sampler2dRect data type vs sampler2D
 the real advantage is, that when you work in
 screen-space for post-processing effects it gets
 much easier for the programmer to work with non-normalized
 texture coordinates. Especially with deferred rendering many
 shaders work in screen-space.
 		https://www.opengl.org/discussion_boards/showthread.php/168643-Is-sampler2DRect-really-necessary*/

in vec2 texCoordVarying;

out vec4 outputColor;
 
void main()
{
    outputColor = texture(tex0, texCoordVarying);
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