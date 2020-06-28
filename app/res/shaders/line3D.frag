#version 140

uniform vec3 color;

out vec4 fragmentColor;
out vec4 brightColor;

void main()
{
    fragmentColor = vec4(color,1);
    brightColor = vec4(0,0,0,1);;
}
