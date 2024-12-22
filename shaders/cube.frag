#version 330 core
out vec4 FragColor;


#define NR_POINT_LIGHTS 4

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct Light {
    vec3 position;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct Spotlight {
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    vec3 diffuse;
    vec3 specular;
};


struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
  
uniform vec3 viewPos;

uniform Light lights[NR_POINT_LIGHTS];
uniform Light light;
uniform DirLight dirLight;
uniform Spotlight spotlight;
uniform Material material;

vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir); 
vec3 calculatePointLight(Light light, vec3 normal, vec3 FragPos, Material material, vec2 texCoords, vec3 viewDir);
vec3 calculateSpotlight(Spotlight spotlight, vec3 normal, vec3 fragPos, Material material, vec2 texCoords, vec3 viewDir);


void main()
{    
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    //direct lighting
    vec3 dirLightResult = calculateDirLight(dirLight, norm, viewDir);

    //point light
    vec3 lightVal = calculatePointLight(light, norm, FragPos, material, TexCoords, viewDir);

    //spotlight
    vec3 spotlightVal = calculateSpotlight(spotlight, norm, FragPos, material, TexCoords, viewDir);
    
            
    vec3 result = lightVal + spotlightVal + dirLightResult;
    FragColor = vec4(result, 1.0);

}


vec3 calculateDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    return (ambient + diffuse + specular);
}


vec3 calculatePointLight(Light light, vec3 norm, vec3 fragPos, Material material, vec2 texCoords, vec3 viewDir) 
{
    //attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
        light.quadratic * (distance * distance));

    
    // diffuse 
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 diffuse = light.diffuse * max(dot(norm, lightDir), 0.0) * vec3(texture(material.diffuse, texCoords));
    
    // specular
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

    specular *= attenuation;
    diffuse *= attenuation;

    return specular + diffuse;
}


vec3 calculateSpotlight(Spotlight spotlight, vec3 norm, vec3 fragPos, Material material, vec2 texCoords, vec3 viewDir)
{
    vec3 cameraDir = normalize(spotlight.position - fragPos);
    float theta = dot(cameraDir, normalize(-spotlight.direction));

    // diffuse 
    vec3 spotDiffuse = spotlight.diffuse * max(dot(norm, cameraDir), 0.0) * texture(material.diffuse, texCoords).rgb;  
    
    // specular
    vec3 spotReflectDir = reflect(-cameraDir, norm);  
    float spotSpec = pow(max(dot(viewDir, spotReflectDir), 0.0), material.shininess);
    vec3 spotSpecular = spotlight.specular * spotSpec * texture(material.specular, texCoords).rgb;  
    
    // attenuation
    float spotDistance    = length(spotlight.position - fragPos);
    float spotAttenuation = 1.0 / (light.constant + light.linear * spotDistance + light.quadratic * (spotDistance * spotDistance));    

    float epsilon = (spotlight.cutoff - spotlight.outerCutoff);
    float spotIntensity = clamp((theta - spotlight.outerCutoff) / epsilon, 0.0f, 1.0f);

    spotDiffuse *= spotIntensity;
    spotSpecular *= spotIntensity;

    spotDiffuse *= spotAttenuation;
    spotSpecular *= spotAttenuation;   
        
    return spotDiffuse + spotSpecular;
}