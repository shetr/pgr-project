#version 140

in vec2 vertex;
in vec2 uv;
in vec3 pos;
in float size;
in float rot;
in float time;

uniform mat4  V; 
uniform mat4  P;

out vec2 f_uv;
out float f_time;

void main()
{
    f_uv = uv;
    f_time = time;

    float sinRot = sin(rot);
    float cosRot = cos(rot);
    vec2 vert = vertex * size;
    vert = vec2(cosRot * vert.x - sinRot * vert.y, sinRot * vert.x + cosRot * vert.y);
    vec4 position = V * vec4(pos, 1) + vec4(vert, 0, 0);
    gl_Position = P * position;
}
