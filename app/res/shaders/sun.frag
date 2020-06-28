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
    fragmentColor = vec4(f * (texture(textureSampler, vec3(f_uv, time)).xyz + vec3(0.2)) + (1-f) * vec3(0,0,0), 1);
    float brightness = dot(fragmentColor.rgb, vec3(0.2126, 0.7152, 0.0722));
    if(brightness > 0.0) {
        brightColor = fragmentColor;
        fragmentColor = vec4(0.0*fragmentColor.rgb,1);
    } else {
        brightColor = vec4(0,0,0,1);
    }
}
