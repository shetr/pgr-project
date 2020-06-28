#version 140

uniform sampler2D texture1Sampler;
uniform sampler2D texture2Sampler;

out vec4 fragmentColor;

in vec2 f_uv;

void main()
{
    float exposure = 1;
    vec3 sceneColor = texture(texture1Sampler, f_uv).rgb;
    vec3 bloomColor = texture(texture2Sampler, f_uv).rgb;
    //vec3 result = sceneColor + bloomColor;
    vec3 result = vec3(1.0) - exp(-(sceneColor + bloomColor) * exposure);
    fragmentColor = vec4(result, 1);
}
