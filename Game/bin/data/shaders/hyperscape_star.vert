#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;
// layout(location = 2) is vec3 vertexNormal;
layout(location = 3) in vec4 vertexColor;

out vec2 UV;
out vec4 vcolor;

uniform mat4 k_worldViewProj;
uniform vec2 k_parallax;

void main()
{
	float parallaxAmount = -8.0;
	gl_Position = k_worldViewProj * vec4( vertexPosition + vec3( k_parallax * parallaxAmount, 0.0 ), 1.0 );
	UV = vertexUV;
	vcolor = vertexColor;
}
