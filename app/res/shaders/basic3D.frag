#version 140

uniform sampler2D textureSampler;

out vec4 fragmentColor;
out vec4 brightColor;

in vec2 f_uv;

void main()
{
    fragmentColor = texture(textureSampler, f_uv);
    brightColor = vec4(0,0,0,1);
}
