#ifndef __IND_MESH__
#define __IND_MESH__

#include <list>
#include <vector>
#include <string>

#include "GL/glew.h"

namespace Indigo
{
  class Mesh;
  class Transform;

  struct MeshPoolInstace
  {
    Mesh *m;
    std::string _path;
  };

  class MeshPool
  {
    friend class RenderManager;
  public:
    static Mesh* CheckMesh(std::string _path);
  private:
    static MeshPool *instance;

    std::list<MeshPoolInstace*> pool;
  };

  class Mesh
  {
    friend class MeshRednerer;
  public:
    Mesh(std::string _path);
  private:
    std::vector<GLfloat> vertsCoords;
    //Extra data goes here

  };

} //End of namespace

#endif