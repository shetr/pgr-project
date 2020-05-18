#version 140

in vec3 position;
in vec2 uv;
in vec3 normal;

uniform mat4  M; 
uniform mat4  VM; 
uniform mat4  PVM;

out vec3 f_position;
out vec3 f_normal;
out vec2 f_uv;

void main()
{
    f_normal = normal;
    f_uv = uv;
    gl_Position = PVM * vec4(position, 1.0);
    f_position = vec3(M*vec4(position, 1.0));
}
