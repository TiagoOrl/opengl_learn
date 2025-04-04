#version 330 core
out vec4 FragColor;

uniform vec3 diffuse;

void main()
{
    FragColor = vec4(diffuse, 1.0); // set all 4 vector values to 1.0
}