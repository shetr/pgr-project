#version 110

in vec3 position;
in vec2 uv;
in vec3 normal;

uniform mat4  M; 
uniform mat4  VM; 
uniform mat4  PVM;

void main()
{
    gl_Position = PVM * vec4(position, 1.0) ;
}
