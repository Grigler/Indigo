#version 400

 struct PointLight
{
  vec4 pos;
  
  vec3 diffuseCol;
  vec3 specularCol;
};

in vec4 vertPos;
in vec3 vertNorm;
in vec2 uv;

//Uniforms defining posiiton and direction of eye
uniform vec3 eyeDir;
uniform vec3 eyePos;

uniform sampler2D mainTexture;

//Arbitrary value
#define MAX_POINT_LIGHTS 16;
uniform int numPointLights = 0;
uniform PointLight pointLights[16];

out vec3 outCol;


vec3 CalcPointLight(PointLight _l)
{
  vec3 lightDir = normalize(_l.pos- vertPos).xyz;
  float diffuse = max(dot(vertNorm, lightDir), 0.0f);
  
  return lightDir * diffuse;
}

void main()
{
  //vec4 texColour = texture(mainTexture, uv);
  vec4 texColour = vec4(0.117, 0.643, 0.145, 1.0f);
  
  vec3 accumDiffuse = vec3(0.0f, 0.0f, 0.0f);
  vec3 ambient = vec3(0.2f, 0.2f, 0.2f);
  
  int num = min(numPointLights, 16);
  for(int i = 0; i < num; i++)
  {
    
    vec3 thisLightCol = CalcPointLight(pointLights[i]);
    
    //Additive colour mixing
    accumDiffuse += thisLightCol;   
    
  }
  
  outCol = ( texColour * vec4(accumDiffuse + ambient, 1.0f) ).xyz;
}