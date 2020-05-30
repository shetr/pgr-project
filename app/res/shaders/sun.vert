#version 140

#define M_PI 3.1415926535897932384626433832795

in vec3 position;
in vec2 uv;
in vec3 normal;

uniform mat4  M; 
uniform mat4  VM; 
uniform mat4  PVM;

uniform float time;


out vec2 f_uv;

void main()
{
    float freq = 0.1;
    float amp = 0.05;
    float d = amp*sin(2*M_PI*(uv.y)/freq);
    f_uv = uv;
    gl_Position = PVM * vec4(position, 1.0);
}
