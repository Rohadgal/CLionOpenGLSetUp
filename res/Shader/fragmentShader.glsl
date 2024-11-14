#version 460 core

out vec4 FragColor;
in vec3 ourColor;

uniform float xColor;
uniform float yColor;

void main()
{
   FragColor = vec4(xColor * ourColor.x, yColor * ourColor.y, ourColor.z, 1.0f);
}