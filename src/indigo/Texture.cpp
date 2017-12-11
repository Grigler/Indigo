#include "Texture.h"

#include "Resources.h"
#include "TextureResource.h"

using namespace Indigo;

void Texture::Assign(std::weak_ptr<TextureResource> _t)
{
  textureResource = _t.lock();
}
void Texture::Load(std::string _path)
{
  textureResource = Resources::LoadTexture(_path).lock();
}
void Texture::Bind()
{
  if(textureResource.get() != nullptr) textureResource->Bind();
}