#version 440

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    sampler2D diffuseTex;
    sampler2D specularTex;
};

struct PointLight
{
    vec3 position;
    float intensity;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

//Uniforms
uniform Material material;
uniform PointLight pointLight[2];
uniform vec3 cameraPos;

//Functions
vec3 calculateAmbient(Material material)
{
    return material.ambient;
}

vec3 calculateDiffuse(Material material, vec3 vs_position, vec3 vs_normal, PointLight pointLight)
{
    vec3 posToLightDirVec = normalize(pointLight.position - vs_position);
    float diffuse = clamp(dot(posToLightDirVec, normalize(vs_normal)), 0, 1);
    vec3 diffuseFinal = material.diffuse *  diffuse * pointLight.intensity;

    return diffuseFinal;
}

vec3 calculateSpecular(Material material, vec3 vs_position, vec3 vs_normal, PointLight pointLight, vec3 cameraPos)
{
    vec3 lightToPosDirVec = normalize(vs_position - pointLight.position);
    vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
    vec3 posToViewDirVec = normalize(cameraPos - vs_position);
    float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
    //vec3 specularFinal = material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb;
    vec3 specularFinal = material.specular * specularConstant;

    return specularFinal;
}

void main()
{
    //fs_color = texture(texture0, vs_texcoord) * texture(texture1, vs_texcoord) * vec4(vs_color, 1.f);

        vec3 ambientFinal;
        vec3 diffuseFinal;
        vec3 specularFinal;
   
        for (int i = 0; i < 1; i++)
        {
            //Ambient light
            ambientFinal += calculateAmbient(material);

            //Diffuse light
            diffuseFinal += calculateDiffuse(material, vs_position, vs_normal, pointLight[i]);


            //Specular light
            specularFinal += calculateSpecular(material, vs_position, vs_normal, pointLight[i], cameraPos);

            //Attenuation

            float distance = length(pointLight[i].position - vs_position);
            //constanat linear quadratic
            float attenuation = pointLight[i].constant / (1.f + pointLight[i].linear * distance + pointLight[i].quadratic * (distance * distance));


            //Final Light
            ambientFinal *= attenuation;
            diffuseFinal *= attenuation;
            specularFinal *= attenuation;
        }
       

   /* fs_color = (texture(material.diffuseTex, vs_texcoord) 
        * vec4(vs_color, 1.f));*/
    //(vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f))) + texture2D(material.specularTex, vs_texcoord);

    vec4 diff = texture2D(material.diffuseTex, vs_texcoord) * (vec4(ambientFinal, 1.f) + vec4(diffuseFinal, 1.f) + vec4(specularFinal, 1.f));

   vec4 emi = texture2D(material.specularTex, vs_texcoord);

    vec4 totalColor = (diff + emi);

    fs_color = totalColor;
}