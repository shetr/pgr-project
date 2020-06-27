#version 140

uniform sampler2D textureSampler;

out vec4 fragmentColor;

in vec2 f_uv;

void main()
{
    fragmentColor = vec4(vec3(texture(textureSampler, f_uv)), 1);
}
