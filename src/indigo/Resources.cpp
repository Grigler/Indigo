#include "Resources.h"

#include "Application.h"

#include "MeshResource.h"
#include "TextureResource.h"
#include "Shader.h"

using namespace Indigo;

std::vector<std::shared_ptr<MeshResource>> Resources::meshVec;
std::vector<std::shared_ptr<TextureResource>> Resources::textureVec;
std::vector<std::shared_ptr<Shader>> Resources::shaderVec;

std::weak_ptr<MeshResource> Resources::LoadMesh(std::string _path)
{
  for (auto i = meshVec.begin(); i != meshVec.end(); i++)
  {
    if (_path == (*i)->path)
      return std::weak_ptr<MeshResource>((*i));
  }
  //Load mesh in its private constructor, then push shared_ptr
  std::shared_ptr<MeshResource> rtn = std::make_shared<MeshResource>();
  rtn->ReadFromFile(_path);
  meshVec.push_back(rtn);
  return std::weak_ptr<MeshResource>(rtn);
}
std::weak_ptr<TextureResource> Resources::LoadTexture(std::string _path)
{
  for (auto i = textureVec.begin(); i != textureVec.end(); i++)
  {
    if (_path == (*i)->path)
      return std::weak_ptr<TextureResource>((*i));
  }
  std::shared_ptr<TextureResource> rtn = std::make_shared<TextureResource>();
  rtn->ReadFromFile(_path);
  textureVec.push_back(rtn);
  return std::weak_ptr<TextureResource>(rtn);
}
std::weak_ptr<Shader> Resources::GetShaderProgram(std::string _name)
{
  for (auto i = shaderVec.begin(); i != shaderVec.end(); i++)
  {
    if ((*i)->name == _name)
    {
      return std::weak_ptr<Shader>((*i));
    }
  } 
  Application::ErrPrint("Error: Shaders must be built before loaded");
  return std::weak_ptr<Shader>();
}

void Resources::PushShader(std::shared_ptr<Shader> _shader)
{
  shaderVec.push_back(_shader);
}