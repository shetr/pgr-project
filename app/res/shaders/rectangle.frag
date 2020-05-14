#version 140

out vec4 fragmentColor;

in vec2 f_uv;

void main()
{
    fragmentColor = vec4(f_uv,1, 1);
}
