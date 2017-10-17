#version 150

// CONSTANTS
#define DEBUG_MODE

// UNIFORMS
uniform sampler2D tex0;	// explosion
uniform sampler2D tex1; // fire texture
uniform sampler2D tex2; // fire texture
uniform float time;
uniform float halfCycle;
uniform float mouseX;

//Flow map offsets used to scroll the wave maps
uniform float flowMapOffset0;
uniform float flowMapOffset1;

// VARIYNG FROM VERTEX SHADER
in vec2 vTexCoord; // uv coords

// FRAGMENT SHADER OUTPUT
out vec4 outputColor;

vec2 unpackFlowVector(vec2 flowVecData)
{
    vec2 flowVector = flowVecData * 2.0 - 1.0;
    return flowVector;
}
 
void main()
{
	vec4 color = vec4( 1.0, 0.0, 0.0, 1.0 );

	vec4 flowMapTexel = texture(tex0, vTexCoord);
    vec2 flowDir = unpackFlowVector(flowMapTexel.xy);
	
    vec4 texelA = texture(tex1, vTexCoord + flowDir * flowMapOffset0); // texture2D is deprecated since version 1.30
    vec4 texelB = texture(tex2, vTexCoord + flowDir * flowMapOffset1);

    float mixFactor = (abs(halfCycle - flowMapOffset0) / halfCycle);
    color = mix(texelA, texelB, mixFactor);
#ifdef DEBUG_MODE
	outputColor = mix(color, flowMapTexel, 0.4);
#else
    outputColor = color;
#endif
}
