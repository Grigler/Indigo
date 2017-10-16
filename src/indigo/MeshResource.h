#ifndef __IND_MESH_RESOURCE__
#define __IND_MESH_RESOURCE__

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Component.h"
#include "resource.h"

namespace Indigo
{
  //TODO - pull apart obj loader for this
  class MeshResource : public Resource
  {
    friend class Resources;
  public:

    std::vector<glm::vec3> *GetVerts() { return &verts; }

  private:
    std::string path;
    void ReadFromFile(std::string _path) { printf("This is just a test"); }

    std::vector<glm::vec3> verts;
  };

}

#endif