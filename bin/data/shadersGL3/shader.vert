#version 150

uniform mat4 modelViewProjectionMatrix;

in vec4 position;

void main()
{
	vec4 npos = position;// + vec4(1.0, 0.0, 0.0, 1.0);
	gl_Position = modelViewProjectionMatrix * npos;
}
