#ifndef __IND_SHADER__
#define __IND_SHADER__

#include <glm/glm.hpp>
#include <GL/glew.h>

#include <string>
#include <memory>
#include <vector>

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

    //Helper functions for setting uniform values by name
    void SetVec3(std::string _uniformName, glm::vec3 _val);
    void SetVec4(std::string _uniformName, glm::vec4 _val);
    void SetMat4(std::string _uniformName, glm::mat4 _val);
    void SetInt(std::string _uniformName, int _val);


  protected:
    GLuint programID;

    GLuint vertID;
    GLuint geomID;
    GLuint fragID;

    static bool CheckCompile(GLuint _programID);

    virtual void LinkUniforms() {}

    //Used for resource management
    std::string name;

  private:
    struct CachedUniforms
    {
      GLuint id;
      std::string name;
    };
    std::vector<CachedUniforms> uniforms;
    //Returns the id of the given uniform name
    GLuint GetUniformID(std::string _name);
    //Attempts to find uniform location from CachedUniforms
    GLuint FindUniform(std::string _name);
    //Attempts to find uniform location from shader and caches
    GLuint CacheUniform(std::string _name);

  };
} 

#endif