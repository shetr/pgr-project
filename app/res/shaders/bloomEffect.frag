#version 140

uniform sampler2D textureSampler;
uniform int horizontal;
uniform int weights_size;
uniform float weights[20];

out vec4 fragmentColor;

in vec2 f_uv;

void main()
{   
    vec2 tex_offset = 1.0 / textureSize(textureSampler, 0);
    vec3 result = texture(textureSampler, f_uv).rgb * weights[0];
    if(horizontal == 1)
    {
        for(int i = 1; i < weights_size; ++i)
        {
            result += texture(textureSampler, f_uv + vec2(tex_offset.x * i, 0.0)).rgb * weights[i];
            result += texture(textureSampler, f_uv - vec2(tex_offset.x * i, 0.0)).rgb * weights[i];
        }
    }
    else
    {
        for(int i = 1; i < weights_size; ++i)
        {
            result += texture(textureSampler, f_uv + vec2(0.0, tex_offset.y * i)).rgb * weights[i];
            result += texture(textureSampler, f_uv - vec2(0.0, tex_offset.y * i)).rgb * weights[i];
        }
    }
    fragmentColor = vec4(result, 1);
}
