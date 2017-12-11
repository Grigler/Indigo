#include "MeshResource.h"

#include "Application.h"

#include "tiny_obj_loader.h"

#include <fstream>
#include <sstream>

using namespace Indigo;

//Removing this means that there is an assumed zero need
//for any of the data to be buffered
MeshResource::~MeshResource()
{
  //If no other VAOs reference the VBOs used by this
  //then the memory is automatically handled
  glDeleteVertexArrays(1, &vaoID);
}

void MeshResource::ActivateVAO()
{
  glBindVertexArray(vaoID);
}

void MeshResource::ReadFromFile(std::string _path)
{
  std::string extension;
  size_t i = _path.rfind('.', _path.length());
  if (i != std::string::npos)
  {
    extension = _path.substr(i + 1, _path.length() - i);
  }

  if (extension == "obj")
  {
    path = _path;
    _LoadOBJ(_path);
  }
  else
  {
    Application::ErrPrint("Extension: " + extension + " not supported");
  }
}

void MeshResource::_LoadOBJ(std::string _path)
{
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapesVec;
  std::vector<tinyobj::material_t> matVec;
  std::string err;
  
  bool r = tinyobj::LoadObj(&attrib, &shapesVec, &matVec, &err, _path.c_str(), NULL, true);
  if (!err.empty())
  {
    Application::ErrPrint(err);
    Application::ErrPrint(std::exception());
  }
  if (!r)
  {
    Application::ErrPrint("Failed to load model at path - " + _path);
    Application::ErrPrint(std::exception());
  }

  std::vector<glm::vec3> vertData;
  std::vector<glm::vec3> normData;
  std::vector<glm::vec2> uvData;

  //Accumulating all vertex, normal and UV data in 3-vectors

  //Loading information in location 1-position 2-normals 3-uv
  for (size_t s = 0; s < shapesVec.size(); s++)
  {
    size_t indexOffset = 0;
    //Each face in this object
    for (int f = 0; f < shapesVec.at(s).mesh.num_face_vertices.size(); f++)
    {
      int fv = shapesVec.at(s).mesh.num_face_vertices.at(f);
      for (size_t v = 0; v < fv; v++)
      {
        tinyobj::index_t i = shapesVec.at(s).mesh.indices.at(indexOffset + v);
        glm::vec3 vert;
        vert.x = attrib.vertices.at(3 * i.vertex_index + 0);
        vert.y = attrib.vertices.at(3 * i.vertex_index + 1);
        vert.z = attrib.vertices.at(3 * i.vertex_index + 2);
        vertData.push_back(vert);

        if (attrib.normals.size() > 0)
        {
          vert.x = attrib.normals.at(3 * i.normal_index + 0);
          vert.y = attrib.normals.at(3 * i.normal_index + 1);
          vert.z = attrib.normals.at(3 * i.normal_index + 2);
          normData.push_back(vert);
        }
        
        if (attrib.texcoords.size() > 0)
        {
          vert.x = attrib.texcoords.at(2 * i.texcoord_index + 0);
          vert.y = attrib.texcoords.at(2 * i.texcoord_index + 1);
          uvData.push_back(vert);
        }
      }
      indexOffset += fv;
    }
  }

  //Storing vertData into verts member-variable to build an AABB from later
  verts = vertData;
  vertCount = vertData.size();

  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  //Creating VBOs, buffering data and setting attrib location pointers
  GLuint vertVBO;
  glGenBuffers(1, &vertVBO);
  glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
  glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(GLfloat) * 3, &vertData[0], GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(0);
  
  if (attrib.normals.size() > 0)
  {
    GLuint normVBO;
    glGenBuffers(1, &normVBO);
    glBindBuffer(GL_ARRAY_BUFFER, normVBO);
    glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(GLfloat) * 3, &normData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
  }

  if (attrib.texcoords.size() > 0)
  {
    GLuint uvVBO;
    glGenBuffers(1, &uvVBO);
    glBindBuffer(GL_ARRAY_BUFFER, uvVBO);
    glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(GLfloat) * 2, &uvData[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);
  }
  
  //Unbinding VAO for clean state
  glBindVertexArray(0);

}