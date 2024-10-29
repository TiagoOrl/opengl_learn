#version 330 core

out vec4 FragColor;
uniform vec4 sharedColor;

void main()
{
    FragColor = sharedColor;
};