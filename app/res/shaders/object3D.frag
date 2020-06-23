#version 140

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
    float shinines;
};

struct Light
{
    int lightType;
    vec4 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 spotDir;
    float spotExponent;
    float spotCutoff;
    float attenuationConst;
    float attenuationLin;
};

uniform mat3  N;

uniform sampler2D textureSampler;
uniform sampler2D optTextureSampler;

uniform Material material;
uniform Light dirLight;
uniform Light pointLight;
uniform Light spotLight;

uniform mat3 textureMat;

uniform float fog;
uniform bool useOptTexture;

out vec4 fragmentColor;

in vec3 f_position;
in vec3 f_normal;
in vec2 f_uv;

vec3 computeLight(Light light, vec3 vertPos, vec3 vertNorm, vec3 diffuseColor)
{
    if(light.lightType <= 0 || light.lightType > 3) {
        return vec3(0);
    }
    vec3 dirToCam = normalize(spotLight.position.xyz - vertPos);
    vec3 dirToLight;
    float spotLightEffect = 1;
    float attenuationFactor = 1;
    if(light.lightType == 1) { // DIR light
        dirToLight = -light.spotDir;
    } else { // POINT or SPOT light
        dirToLight = light.position.xyz - vertPos;
        float dist = length(dirToLight);
        dirToLight = normalize(dirToLight);
        attenuationFactor = 1 / (light.attenuationConst + light.attenuationLin * dist);
        if(light.lightType == 3) { // SPOT light
            float cosAlpha = dot(dirToLight, -light.spotDir);
            if(cosAlpha < cos(light.spotCutoff)) {
                return vec3(0);
            } else {
                spotLightEffect = pow(max(cosAlpha,0),light.spotExponent);
            }
        }
    }
    vec3 reflected = reflect(-dirToLight, vertNorm);
    float specularExp = pow(max(dot(dirToCam, reflected),0), material.shinines);
    if(dot(reflected, vertNorm) < 0) {
        specularExp = 0;
    }

    vec3 ambient = vec3(0);
    vec3 diffuse = vec3(0);
    vec3 specular = vec3(0);

    ambient = light.ambient*material.ambient;
    diffuse = max(dot(dirToLight, vertNorm),0)*light.diffuse*diffuseColor;
    specular = specularExp*light.specular*material.specular;
    return spotLightEffect*attenuationFactor*(ambient+diffuse+specular);
}

float getFogFactor()
{
    return exp(-fog* gl_FragCoord.z / gl_FragCoord.w);
}

void main()
{
    vec3 normal = normalize(N*f_normal);

    vec2 uvTrans = (textureMat * vec3(f_uv,1)).xy;
    vec4 texValue;
    if(useOptTexture) {
        vec4 optValue = texture(optTextureSampler, uvTrans);
        texValue = (1-optValue.w)*texture(textureSampler, uvTrans) + optValue.w*vec4(optValue.xyz,1);
    } else {
        texValue = texture(textureSampler, uvTrans);
    }
    vec3 diffuse = texValue.rgb;
    float alpha = texValue.a;

    vec3 l1 = computeLight(dirLight, f_position, normal, diffuse);
    vec3 l2 = computeLight(pointLight, f_position, normal, diffuse);
    vec3 l3 = computeLight(spotLight, f_position, normal, diffuse);
    vec3 lightsColor = clamp(material.emission+material.ambient*diffuse+l1+l2+l3, 0, 1);

    float f = getFogFactor();

    fragmentColor = vec4(f * lightsColor + (1-f) * vec3(0,0,0), alpha);
}
