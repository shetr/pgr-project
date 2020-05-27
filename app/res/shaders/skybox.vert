#version 140

in vec3 direction;

uniform mat4 P;
uniform mat4 V;

out vec3 f_direction;

void main()
{
    gl_Position = P * vec4((V * vec4(direction, 0.0)).xyz, 1);
    f_direction = direction;
}
