#version 110

varying out vec4 fragmentColor;

uniform vec3 color;

void main()
{
    fragmentColor = vec4(color, 1);
}
