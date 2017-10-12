#include "Resources.h"

#include "Mesh.h"
#include "Texture.h"

using namespace Indigo;

//std::vector<std::shared_ptr<Mesh>> Resources::meshVec;
//std::vector<std::shared_ptr<Texture>> Resources::textureVec;

std::weak_ptr<Mesh> Resources::LoadMesh(std::string _path)
{
  for (auto i = meshVec.begin(); i != meshVec.end(); i++)
  {
    if (_path == (*i)->path)
      return std::weak_ptr<Mesh>((*i));
  }
  //Load mesh in its private constructor, then push shared_ptr
  std::shared_ptr<Mesh> rtn = std::make_shared<Mesh>();
  rtn->ReadFromFile(_path);
  meshVec.push_back(rtn);
}
std::weak_ptr<Texture> Resources::LoadTexture(std::string _path)
{
  for (auto i = textureVec.begin(); i != textureVec.end(); i++)
  {
    if (_path == (*i)->path)
      return std::weak_ptr<Texture>((*i));
  }
  std::shared_ptr<Texture> rtn = std::make_shared<Texture>();
  rtn->ReadFromFile(_path);
  textureVec.push_back(rtn);
}