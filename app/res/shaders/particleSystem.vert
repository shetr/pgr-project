#version 140

in vec2 vertex;
in vec3 position;
in float size;
in float time;

uniform mat4  M; 
uniform mat4  VM; 
uniform mat4  PVM;


//out vec2 f_uv;

void main()
{
    //f_uv = uv;
    gl_Position = PVM * vec4(vec3(size*vertex, 0) + position, 1.0);
    //gl_Position = vec4(vertex, 0, 1);
}
