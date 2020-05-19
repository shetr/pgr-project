#version 140

uniform mat3  N;

uniform sampler2D textureSampler;
uniform vec3 lightPos = vec3(0,0,0);

out vec4 fragmentColor;

in vec3 f_position;
in vec3 f_normal;
in vec2 f_uv;

void main()
{
    vec3 normal = normalize(N*f_normal);
    vec3 lightDir = normalize(-f_position);
    fragmentColor = clamp(dot(normal, lightDir), 0, 1) * texture(textureSampler, f_uv);
}
