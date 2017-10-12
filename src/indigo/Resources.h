#ifndef __IND_RECOURCES__
#define __IND_RECOURCES__

#define STRINGIFY(T) #T

#include <memory>
#include <string>
#include <vector>
#include <map>

#include "resource.h"

namespace Indigo
{
  class Mesh;
  class Texture;

  class Resources
  {
  public:
    //static std::weak_ptr<Mesh> LoadMesh(std::string _path);
    //static std::weak_ptr<Texture> LoadTexture(std::string _path);

    template <class T>
    static std::weak_ptr<T> LoadResource(std::string _path);

  private:
    //static std::vector<std::shared_ptr<Mesh>> meshVec;
    //static std::vector<std::shared_ptr<Texture>> textureVec;

    static std::map < std::string, std::vector<std::shared_ptr<Resource>> > resourceMap;
  };

  std::map<std::string, std::vector<std::shared_ptr<Resource>>> Resources::resourceMap;

  template <class T>
  static std::weak_ptr<T> Resources::LoadResource(std::string _path)
  {
    //Does not allow for pure Resource class use for T
    static_assert(std::is_base_of(Resource, T),
      "Resource must inherit from Resource class with LoadFromFile overload");

    std::vector <std::shared_ptr<Resource>> *mapVec;
    auto iterator = resourceMap.find(STRINGIFY(T));
    if (iterator == resourceMap.end()) //First resource instance, create vector
    {
      mapVec = resourceMap.insert(std::vector<std::shared_ptr<T>>)->second;
    }
    else
    {
      mapVec = (*iterator)->second;
    }
    
    for (auto i = mapVec->begin(); i != mapVec->end(); i++)
    {
      if ((*i)->path == _path)
        return std::weak_ptr<T>((*i));
    }
    std::shared_ptr<T> rtn = std::make_shared<T>();
    rtn->Load(_path);
    mapVec->push_back(rtn);
    return rtn;
  }

}

#endif