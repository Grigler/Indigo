#ifndef __IND_SHADER__
#define __IND_SHADER__

#include <GL/glew.h>
#include <string>
#include <memory>

#include "resource.h"

namespace Indigo
{
  class Shader
  {
    friend class Resources;
    friend class RenderBuffer;
  public:
    //Must be called before any other shader functions
    void Init(std::string _name);
    //Activates this shader for drawing
    void Activate();
    //Attatches Each shader to shader program after loading
    bool LoadShader(GLenum _type, std::string _path);
    //bool LoadShader(GLenum _type, GLchar *_src);
    //Links after loading all required shaders
    bool Link();

    //Used to create a managed Shader resource
    //avoids creating identical program
    static std::shared_ptr<Shader> CreateShaderResource();

  protected:
    GLuint programID;

    GLuint vertID;
    GLuint geomID;
    GLuint fragID;

    static bool CheckCompile(GLuint _programID);

    virtual void LinkUniforms() {}

    //Used foir resource management
    std::string name;
  };
} 

#endif