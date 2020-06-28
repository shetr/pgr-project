#version 140

uniform samplerCube textureSampler;

out vec4 fragmentColor;
out vec4 brightColor;

in vec3 f_direction;

void main()
{
    fragmentColor = vec4(texture(textureSampler, f_direction).xyz,1);
    brightColor = vec4(0,0,0,1);;
}
