#version 140

uniform sampler3D textureSampler;
uniform float time;

uniform float fog;

out vec4 fragmentColor;

in vec2 f_uv;

float getFogFactor()
{
    return exp(-fog* gl_FragCoord.z / gl_FragCoord.w);
}

void main()
{
    float f = getFogFactor();
    fragmentColor = f * texture(textureSampler, vec3(f_uv, time)) + (1-f) * vec4(0,0,0,1);
    //fragmentColor = time * vec4(1);
}
