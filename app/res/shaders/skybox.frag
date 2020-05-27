#version 140

uniform samplerCube textureSampler;

out vec4 fragmentColor;

in vec3 f_direction;

void main()
{
    fragmentColor = texture(textureSampler, f_direction);
}
