#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

uniform vec4 u_Colors;

out vec4 colors;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
    colors = u_Colors;
}