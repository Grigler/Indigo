#version 400

 struct PointLight
{
  vec4 pos;
  vec3 colour;
  float attenuation;
};

in vec4 vertPos;
in vec3 vertNorm;
in vec2 uv;

//Uniforms defining posiiton and direction of eye
uniform vec3 eyePos;

uniform sampler2D mainTexture;

//Arbitrary value
#define MAX_POINT_LIGHTS 16;
uniform int numPointLights = 1;
uniform PointLight pointLights[16];

out vec3 outCol;


vec3 CalcPointLight(PointLight _l)
{
  //Calculating diffuse
  vec3 toLight = (_l.pos - vertPos).xyz;
  vec3 lightDir = normalize(toLight);
  float diffuseScale = max(dot(vertNorm, lightDir), 0.0f);
  
  vec3 diffCol = _l.colour * diffuseScale;
  
  //Calculating Specular
  float specStrength = 0.5f;
  
  vec3 viewDir = normalize(eyePos - vertPos.xyz);
  vec3 halfVec = normalize(lightDir + viewDir);
  
  float specScale = pow(max(dot(vertNorm, halfVec), 0.0f), 32.0f);
  vec3 specCol = specStrength * specScale * _l.colour;
  
  float dist = length(toLight);
  //Linear attenuation
  float att = (1.0f / dist) * _l.attenuation;
  
  return (specCol + diffCol) * att;
  
}

void main()
{
  vec4 texColour = texture(mainTexture, uv);
  //vec4 texColour = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  
  vec3 accumLight = vec3(0.0f, 0.0f, 0.0f);
  vec3 ambient = vec3(0.1f, 0.1f, 0.1f);
  
  int num = min(numPointLights, 16);
  for(int i = 0; i < num; i++)
  {
    
    vec3 thisLightCol = CalcPointLight(pointLights[i]);
    
    //Additive colour mixing
    accumLight += thisLightCol;   
    
  }
  
  outCol = ( texColour * vec4(accumLight + ambient, 1.0f) ).xyz;
}