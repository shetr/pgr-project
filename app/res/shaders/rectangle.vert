#version 110

in vec2 position;

uniform mat4  M; 
uniform mat4  VM; 
uniform mat4  PVM;

void main()
{
    gl_Position = M * vec4(position, 0.0, 1.0) ;
}
