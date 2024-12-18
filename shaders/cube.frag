

#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
in vec2 TexCoords;
  

uniform vec3 viewPos;


struct Light {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light light;  


struct Spotlight {
    vec3 position;
    vec3 direction;
    float cutoff;

    vec3 diffuse;
    vec3 specular;
};

uniform Spotlight spotlight;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
  
uniform Material material;

void main()
{    
    vec3 spotResult;
    vec3 cameraDir = normalize(spotlight.position - FragPos);
    float theta = dot(cameraDir, normalize(-spotlight.direction));

    //attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + 
        light.quadratic * (distance * distance));

    // ambient
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

    specular *= attenuation;
    diffuse *= attenuation;

    //spotlight
    if (theta > spotlight.cutoff) {

        // diffuse 
        vec3 norm = normalize(Normal);
        float diff = max(dot(norm, cameraDir), 0.0);
        vec3 spotDiffuse = spotlight.diffuse * diff * texture(material.diffuse, TexCoords).rgb;  
        
        // specular
        vec3 viewDir = normalize(viewPos - FragPos);
        vec3 reflectDir = reflect(-cameraDir, norm);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = spotlight.specular * spec * texture(material.specular, TexCoords).rgb;  
        
        // attenuation
        float spotDistance    = length(spotlight.position - FragPos);
        float spotAttenuation = 1.0 / (light.constant + light.linear * spotDistance + light.quadratic * (spotDistance * spotDistance));    

        spotDiffuse *= spotAttenuation;
        specular *= spotAttenuation;   
            
        spotResult = spotDiffuse + specular;
        // FragColor = vec4(result, 1.0);
    } 
            
    vec3 result = ambient + specular + diffuse + spotResult;
    FragColor = vec4(result, 1.0);

}

