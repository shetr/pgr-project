#version 140

uniform sampler2D textureSampler;

out vec4 fragmentColor;

in vec2 f_uv;

void main()
{
    fragmentColor = texture(textureSampler, f_uv);
}
