#version 140

uniform sampler3D textureSampler;
uniform float time;

uniform float fog;

out vec4 fragmentColor;
out vec4 brightColor;

in vec2 f_uv;

float getFogFactor()
{
    return exp(-fog* gl_FragCoord.z / gl_FragCoord.w);
}

void main()
{
    float f = getFogFactor();
    fragmentColor = vec4(f * texture(textureSampler, vec3(f_uv, time)).xyz + (1-f) * vec3(0,0,0), 1);
    brightColor = fragmentColor;
    //fragmentColor = time * vec4(1);
}
