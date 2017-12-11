#ifndef __IND_TEXTURE__
#define __IND_TEXTURE__

#include <memory>
#include <string>

namespace Indigo
{
  class TextureResource;
  class GameObject;

  class Texture
  {
    friend class MeshRenderer;
  public:

    //Directly assigns this texture a TextureResource - mostly internal usage
    void Assign(std::weak_ptr<TextureResource> _t);
    //Loads from resource pool if previously loaded - or loads and pools
    void Load(std::string _path);
    //Binds texture for drawing
    void Bind();

  private:
    std::weak_ptr<GameObject> goParent;

    std::shared_ptr<TextureResource> textureResource;

  };
}

#endif