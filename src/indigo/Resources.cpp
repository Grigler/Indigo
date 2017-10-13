#include "Resources.h"

#include "MeshResource.h"
#include "TextureResource.h"

using namespace Indigo;

//std::vector<std::shared_ptr<Mesh>> Resources::meshVec;
//std::vector<std::shared_ptr<Texture>> Resources::textureVec;

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
}