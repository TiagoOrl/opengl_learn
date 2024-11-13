#version 330 core

out vec4 FragColor;

uniform float texVisibility;

in vec2 textCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, textCoord), texture(texture2, textCoord), texVisibility);
};