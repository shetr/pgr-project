#version 140

uniform sampler2D textureSampler;
uniform ivec2 textureSizes;

out vec4 fragmentColor;

in vec2 f_uv;
in float f_time;

void main()
{
    float xSize = textureSizes.x;
    float ySize = textureSizes.y;
    float xStep = 1.0 / xSize;
    float yStep = 1.0 / ySize;
    float imgCount = xSize * ySize;
    float time = f_time * imgCount;
    int ti = int(time);
    int yi = ti / textureSizes.x;
    int xi = ti - yi * textureSizes.x;
    int xi2 = xi + 1;
    int yi2 = yi;
    if(xi2 == textureSizes.x) {
        xi2 = 0;
        yi2++;
        if(yi2 == textureSizes.y) {
            xi2--;
            yi2--;
        }
    }
    float xStart = xi * xStep;
    float yStart = yi * yStep;
    float x2Start = xi2 * xStep;
    float y2Start = yi2 * yStep;
    float t = time - ti;
    vec2 uvRel = vec2(f_uv.x / xSize, f_uv.y / ySize);
    vec2 uv1 = uvRel + vec2(xStart, yStart);
    vec2 uv2 = uvRel + vec2(x2Start, y2Start);
    fragmentColor = (1-t)*texture(textureSampler, uv1) + t*texture(textureSampler, uv2);
}
