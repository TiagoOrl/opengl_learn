#version 330 core

out vec4 FragColor;

uniform vec4 sharedColor;
uniform float shValue;

in vec3 ourColor;
in vec2 textCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, textCoord) * vec4(ourColor, 1.0f);
};