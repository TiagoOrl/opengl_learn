#version 330 core

out vec4 FragColor;
uniform vec4 sharedColor;
uniform float shValue;
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor.x, shValue, ourColor.z, 1.0f);
};