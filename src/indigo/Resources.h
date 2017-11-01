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
  class MeshResource;
  class TextureResource;
  class Shader;

  class Resources
  {
    friend class Shader;
  public:
    virtual ~Resources() {}
    static std::weak_ptr<MeshResource> LoadMesh(std::string _path);
    static std::weak_ptr<TextureResource> LoadTexture(std::string _path);
    static std::weak_ptr<Shader> GetShaderProgram(std::string _name);

  private:
    static std::vector<std::shared_ptr<MeshResource>> meshVec;
    static std::vector<std::shared_ptr<TextureResource>> textureVec;

    //Used in Shader::CreateShaderResource for management
    static void PushShader(std::shared_ptr<Shader> _shader);
    static std::vector<std::shared_ptr<Shader>> shaderVec;
  };

}

#endif