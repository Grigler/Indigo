#ifndef __IND_MESH_RESOURCE__
#define __IND_MESH_RESOURCE__

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Component.h"
#include "resource.h"

namespace Indigo
{

  class MeshResource : public Resource
  {
    friend class Resources;
  public:
    ~MeshResource();
    std::vector<glm::vec3> *GetVerts() { return &verts; }

    void ActivateVAO();
    GLsizei GetVertCount() { return vertCount; }

  private:
    std::string path;
    //Detects correct function for parsing from file extension
    void ReadFromFile(std::string _path);

    //Utility functions for loading meshes in specific formats
    void _LoadOBJ(std::string _path);

    GLsizei vertCount;
    std::vector<glm::vec3> verts;

    GLuint vaoID;

  };

}

#endif