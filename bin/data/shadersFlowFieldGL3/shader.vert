#version 150


// UNIFORMS
// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewProjectionMatrix;
uniform float mouseX;
uniform float time;

// VERTEX ATTRIBUTES
in vec4 position;
in vec3 normal;
in vec2 texcoord;

// VARYING
// this is something we're creating for this shader
out vec2 vTexCoord;

void main()
{
    vTexCoord = texcoord; // pass the texture coordinates to fragment shader

	gl_Position = modelViewProjectionMatrix * position; // send the vertices to the fragment shader
}