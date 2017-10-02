#include "Mesh.h"

#include "Transform.h"

using namespace Indigo;

MeshPool *MeshPool::instance = nullptr;

Mesh* MeshPool::CheckMesh(std::string _path)
{
  for (std::list<MeshPoolInstace*>::iterator inst = instance->pool.begin();
    inst != instance->pool.end(); inst++)
  {
    if (_path == (*inst)->_path)
    {
      return (*inst)->m;
    }
  }

  MeshPoolInstace *newInst = new MeshPoolInstace;
  newInst->m = new Mesh(_path);
  newInst->_path = _path;
  
  return newInst->m;
}
//TODO - loading object data
Mesh::Mesh(std::string _path)
{
  //Load object from _path and parse data into lists
}