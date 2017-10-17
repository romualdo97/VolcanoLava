#version 150

// UNIFORMS
uniform sampler2D tex0;	// explosion
uniform sampler2D tex1; // ramp texture
uniform float time;
uniform float mouseX;

// VARIYNG FROM VERTEX SHADER
in vec2 vTexCoord; // uv coords

// FRAGMENT SHADER OUTPUT
out vec4 outputColor;

vec2 unpackFlowVector(sampler2D flowField)
{
    vec2 flowVector = texture(flowField, vTexCoord).xy - vec2(0.5);
    return flowVector;
}
 
void main()
{
    vec2 flowDir = unpackFlowVector(tex1);

	vec4 color = vec4( 1.0 );
    vec4 texel = texture(tex0, vTexCoord + flowDir); // texture2D is deprecated since version 1.30

    outputColor = texel;
}
