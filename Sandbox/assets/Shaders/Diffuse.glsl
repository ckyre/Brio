#type vertex
#version 330 core

layout (location = 0) in vec3 a_VertexPosition;
layout (location = 1) in vec2 a_UV;
layout (location = 2) in vec3 a_Normal;

out vec3 VertexPosition;
out vec2 UV;
out vec3 Normal;

layout (std140) uniform SceneData
{
    mat4 u_ViewProjection;
    vec3 u_LightPosition;
    vec3 u_ViewPosition;
};

uniform mat4 u_Transform;

void main()
{
    VertexPosition = vec3(u_Transform * vec4(a_VertexPosition, 1.0));
    UV = a_UV;
    Normal = a_Normal;

    gl_Position = u_ViewProjection * vec4(VertexPosition, 1.0);
}

////////////////////////////////////////////////
////// Pixel shader ////////////////////////////
////////////////////////////////////////////////

#type pixel
#version 330 core

layout (std140) uniform SceneData
{
    mat4 u_ViewProjection;
    vec3 u_LightPosition;
    vec3 u_ViewPosition;
};

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

out vec4 PixelColor;

in vec3 VertexPosition;
in vec2 UV;
in vec3 Normal;

uniform Material material;
uniform DirectionalLight dirLight;
uniform PointLight pointLight;
uniform SpotLight spotLight;

vec3 ApplyDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 ApplyPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 ApplySpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);  
    vec3 viewDir = normalize(u_ViewPosition - VertexPosition);

    // Directional light
    vec3 result = ApplyDirLight(dirLight, norm, viewDir);

    // Point light
    PointLight l = pointLight;
    l.position = u_LightPosition;
    result += ApplyPointLight(l, norm, VertexPosition, viewDir);

    // Spot light
    result += ApplySpotLight(spotLight, norm, VertexPosition, viewDir);

    PixelColor = vec4(result, 1.0);
} 

vec3 ApplyDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // combine
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

    return (ambient + diffuse + specular);
}

vec3 ApplyPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

    // combine
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 ApplySpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);

    // diffuse
    float diff = max(dot(normal, lightDir), 0.0);

    // specular
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // combine
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, UV));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, UV));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, UV));

    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}