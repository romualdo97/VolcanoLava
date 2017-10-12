#version 150

 // ashima's webgl-noise: https://github.com/ashima/webgl-noise/blob/master/src/classicnoise3D.glsl
vec3 mod289(vec3 x)
{
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}
vec4 mod289(vec4 x)
{
    return x - floor(x * (1.0 / 289.0)) * 289.0;
}
vec4 permute(vec4 x)
{
    return mod289(((x*34.0)+1.0)*x);
}
vec4 taylorInvSqrt(vec4 r)
{
    return 1.79284291400159 - 0.85373472095314 * r;
}
vec3 fade(vec3 t) {
    return t*t*t*(t*(t*6.0-15.0)+10.0);
}
// Classic Perlin noise, periodic variant
float pnoise(vec3 P, vec3 rep)
{
    vec3 Pi0 = mod(floor(P), rep); // Integer part, modulo period
    vec3 Pi1 = mod(Pi0 + vec3(1.0), rep); // Integer part + 1, mod period
    Pi0 = mod289(Pi0);
    Pi1 = mod289(Pi1);
    vec3 Pf0 = fract(P); // Fractional part for interpolation
    vec3 Pf1 = Pf0 - vec3(1.0); // Fractional part - 1.0
    vec4 ix = vec4(Pi0.x, Pi1.x, Pi0.x, Pi1.x);
    vec4 iy = vec4(Pi0.yy, Pi1.yy);
    vec4 iz0 = Pi0.zzzz;
    vec4 iz1 = Pi1.zzzz;
    vec4 ixy = permute(permute(ix) + iy);
    vec4 ixy0 = permute(ixy + iz0);
    vec4 ixy1 = permute(ixy + iz1);
    vec4 gx0 = ixy0 * (1.0 / 7.0);
	// el amor que siento por ti es tan hermoso como este proyecto
    vec4 gy0 = fract(floor(gx0) * (1.0 / 7.0)) - 0.5;
    gx0 = fract(gx0);
    vec4 gz0 = vec4(0.5) - abs(gx0) - abs(gy0);
    vec4 sz0 = step(gz0, vec4(0.0));
    gx0 -= sz0 * (step(0.0, gx0) - 0.5);
    gy0 -= sz0 * (step(0.0, gy0) - 0.5);
    vec4 gx1 = ixy1 * (1.0 / 7.0);
    vec4 gy1 = fract(floor(gx1) * (1.0 / 7.0)) - 0.5;
    gx1 = fract(gx1);
    vec4 gz1 = vec4(0.5) - abs(gx1) - abs(gy1);
    vec4 sz1 = step(gz1, vec4(0.0));
    gx1 -= sz1 * (step(0.0, gx1) - 0.5);
    gy1 -= sz1 * (step(0.0, gy1) - 0.5);
    vec3 g000 = vec3(gx0.x,gy0.x,gz0.x);
    vec3 g100 = vec3(gx0.y,gy0.y,gz0.y);
    vec3 g010 = vec3(gx0.z,gy0.z,gz0.z);
    vec3 g110 = vec3(gx0.w,gy0.w,gz0.w);
    vec3 g001 = vec3(gx1.x,gy1.x,gz1.x);
    vec3 g101 = vec3(gx1.y,gy1.y,gz1.y);
    vec3 g011 = vec3(gx1.z,gy1.z,gz1.z);
    vec3 g111 = vec3(gx1.w,gy1.w,gz1.w);
    vec4 norm0 = taylorInvSqrt(vec4(dot(g000, g000), dot(g010, g010), dot(g100, g100), dot(g110, g110)));
    g000 *= norm0.x;
    g010 *= norm0.y;
    g100 *= norm0.z;
    g110 *= norm0.w;
    vec4 norm1 = taylorInvSqrt(vec4(dot(g001, g001), dot(g011, g011), dot(g101, g101), dot(g111, g111)));
    g001 *= norm1.x;
    g011 *= norm1.y;
    g101 *= norm1.z;
    g111 *= norm1.w;
    float n000 = dot(g000, Pf0);
    float n100 = dot(g100, vec3(Pf1.x, Pf0.yz));
    float n010 = dot(g010, vec3(Pf0.x, Pf1.y, Pf0.z));
    float n110 = dot(g110, vec3(Pf1.xy, Pf0.z));
    float n001 = dot(g001, vec3(Pf0.xy, Pf1.z));
    float n101 = dot(g101, vec3(Pf1.x, Pf0.y, Pf1.z));
    float n011 = dot(g011, vec3(Pf0.x, Pf1.yz));
    float n111 = dot(g111, Pf1);
    vec3 fade_xyz = fade(Pf0);
    vec4 n_z = mix(vec4(n000, n100, n010, n110), vec4(n001, n101, n011, n111), fade_xyz.z);
    vec2 n_yz = mix(n_z.xy, n_z.zw, fade_xyz.y);
    float n_xyz = mix(n_yz.x, n_yz.y, fade_xyz.x); 
    return 2.2 * n_xyz;
}

// =====================================================================
// HERE START MY CODE!!

// CONSTANTS
//#define USE_NOISE

// UNIFORMS
// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewProjectionMatrix;
uniform float mouseX;
uniform float time;
// wave 1
float uAmplitude = 3.0;
float uSpeed = 0.8;
vec2 uDirection = vec2(-1.0, 0.0);
float uFreq = 1.0 / 3.0;

// VERTEX ATTRIBUTES
in vec4 position;
in vec3 normal;
in vec2 texcoord;

// VARYING
// this is something we're creating for this shader
out vec2 vTexCoord;
out float vNoise;
out vec3 vNormal;

// noise perturbation approach
float turbulence( vec3 p ) 
{
	float w = 100.0;
	float t = -.5;
	for (float f = 1.0 ; f <= 10.0 ; f++ )
	{
		float power = pow( 2.0, f );
		t += abs( pnoise( vec3( power * p ), vec3( 10.0, 10.0, 10.0 ) ) / power );
	}
	return t;
}

// Effective Water Simulation from Physical Models by Marck Finch and Cyan World approach
// https://developer.nvidia.com/gpugems/GPUGems/gpugems_ch01.html
float wave(vec2 direction, float amplitude, float speed, float w)
{
    // Equation 1:
    return amplitude * sin((dot(direction, position.xy) * w) + time * speed);
}

float dWdx(vec2 direction, float amplitude, float speed, float w)
{
    // Equation 4b:
    // Partial derivative in the 'x' direction of P(x, y, H(x, y, t)) is binormal vector
    return amplitude * direction.x * w * cos((dot(direction, position.xy) * w) + time * speed);
}

float dWdy(vec2 direction, float amplitude, float speed, float w)
{
    // Equation 5b:
    // Partial derivative in the 'y' direction of P(x, y, H(x, y, t)) is tangent vector
    return amplitude * direction.y * w * cos((dot(direction, position.xy) * w) + time * speed);
}

void main()
{
    // pass the texture coordinates to fragment shader
    vTexCoord = vec2( texcoord.x + uDirection.x * time * 4.5, texcoord.y);

    //noiseVarying = 10.0 *  -.10 * turbulence( .5 * normal + time * .1 ); // <= use for spheres
	vNoise = 10.0 *  -.10 * turbulence( vec3(.5 * texcoord.xy + time*.04, 0.0) ); // <= use for planes

    // displacement
    float displacement = 0.0;
#ifdef USE_NOISE
    // get a 3d noise using the position, low frequency
    float b = 5.0 * pnoise( 0.05 * position.xyz, vec3( 100.0 ) );
    // compose both noises
    displacement = (- 10. * vNoise + b) * 1.5;
#else
    float W1 = wave(uDirection, uAmplitude, uSpeed, uFreq);
    float H = W1;
    float dHdx = dWdx(uDirection, uAmplitude, uSpeed, uFreq);
    float dHdy = dWdy(uDirection, uAmplitude, uSpeed, uFreq);
    vec3 N_x_y = normalize(vec3(-dHdx, -dHdy, 1)); // N(x, y); surface normal at any given point
    vNormal = N_x_y;
    displacement = H;
#endif


    vec3 nPos = position.xyz + normal * displacement;

    // send the vertices to the fragment shader
	gl_Position = modelViewProjectionMatrix * vec4(nPos, 1.0);
}