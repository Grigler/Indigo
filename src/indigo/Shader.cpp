#include "Shader.h"

#include "Application.h"

#include "Resources.h"

#include <fstream>

#define ERR_ID GL_INVALID_VALUE

using namespace Indigo;

void Shader::Init(std::string _name)
{
  programID = glCreateProgram();
  if (programID == 0)
  {
    Application::ErrPrint(std::exception("Failed to create shader program"));
  }
  name = _name;

}
void Shader::Activate()
{
  glUseProgram(programID);
}

bool Shader::LoadShader(GLenum _type, std::string _path)
{
  GLchar *shaderSrc;
  std::ifstream file(_path);
  if (file.is_open())
  {
    file.seekg(0, file.end);
    int len = file.tellg();
    file.seekg(0, file.beg);

    shaderSrc = new char[len + 10];
    memset(shaderSrc, 0, sizeof(GLchar)*(len + 10));
    file.read(shaderSrc, len);

    if (!file.eof())
    {
      file.close();
      delete [] shaderSrc;
      Application::ErrPrint("No eof bit for " + _path);
      return false;
    }
    else
    {
      len = file.gcount();
      shaderSrc[len] = 0;
      file.close();
    }

    GLuint *id = NULL;
    switch (_type)
    {
    case GL_VERTEX_SHADER:   id = &vertID; break;
    case GL_GEOMETRY_SHADER: id = &geomID; break;
    case GL_FRAGMENT_SHADER: id = &fragID; break;
    }

    *id = glCreateShader(_type);
    glShaderSource(*id, 1, &shaderSrc, NULL);
    glCompileShader(*id);

    bool rtn = CheckCompile(*id);
    if (rtn)
    {
      glAttachShader(programID, *id);
    }
    return rtn;
  }
  else
  {
    Application::ErrPrint("Failed to open shader " + _path);
    return false;
  }
}
bool Shader::Link()
{
  glLinkProgram(programID);

  GLint linked;
  glGetProgramiv(programID, GL_LINK_STATUS, &linked);
  if (!linked)
  {
    GLsizei len;
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &len);

    GLchar *log = new GLchar[len + 1];
    glGetProgramInfoLog(programID, len, &len, log);
    fprintf(stderr, "%s\n", log);
    Application::ErrPrint("Failed to link shader - reasons above");
    delete[] log;
    return false;
  }

  LinkUniforms();

  return true;
}

std::shared_ptr<Shader> Shader::CreateShaderResource()
{
  std::shared_ptr<Shader> rtn = std::make_shared<Shader>();
  Resources::PushShader(rtn);
  return rtn;
}

void Shader::SetFloat(std::string _uniformName, float _val)
{
  GLuint id = GetUniformID(_uniformName);
  if (id == ERR_ID) return;
  glUniform1f(id, _val);
}
void Shader::SetVec3(std::string _uniformName, glm::vec3 _val)
{
  GLuint id = GetUniformID(_uniformName);
  if (id == ERR_ID) return;
  glUniform3fv(id, 1, &_val[0]);
}
void Shader::SetVec4(std::string _uniformName, glm::vec4 _val)
{
  GLuint id = GetUniformID(_uniformName);
  if (id == ERR_ID) return;
  glUniform4fv(id, 1, &_val[0]);
}
void Shader::SetMat4(std::string _uniformName, glm::mat4 _val)
{
  GLuint id = GetUniformID(_uniformName);
  if (id == ERR_ID) return;
  glUniformMatrix4fv(id, 1, GL_FALSE, &_val[0][0]);
}
void Shader::SetInt(std::string _uniformName, int _val)
{
  GLuint id = GetUniformID(_uniformName);
  if (id == ERR_ID) return;
  glUniform1i(id, _val);
}

bool Shader::CheckCompile(GLuint _programID)
{
  GLboolean hasCompiler;
  glGetBooleanv(GL_SHADER_COMPILER, &hasCompiler);
  if (hasCompiler)
  {
    GLint compiled = 0;
    glGetShaderiv(_programID, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
      GLsizei len;
      glGetShaderiv(_programID, GL_INFO_LOG_LENGTH, &len);
      GLchar *log = new GLchar[len + 1];
      memset(log, 0, sizeof(GLchar) * (len + 1));
      glGetShaderInfoLog(_programID, len, &len, log);
      fprintf(stderr, "%s\n", log);
      Application::ErrPrint("Failed to compile shader - reasons above");
      delete[] log;
      Application::ErrPrint(std::exception());
      return false;
    }
  }
  return true;
}

GLuint Shader::GetUniformID(std::string _name)
{
  GLuint id = FindUniform(_name);

  //Uniform has not yet been cached
  if (id == ERR_ID)
  {
    id = CacheUniform(_name);
    //Uniform does not exist in shader
    if (id == ERR_ID)
    {
      std::string err = "Attempted to find invalid uniform '" + _name +
       "' in shader '" + name + '\'';
      Application::ErrPrint(err);
    }
  }
 
  return id;
}
GLuint Shader::FindUniform(std::string _name)
{
  for (auto c = uniforms.begin(); c != uniforms.end(); c++)
  {
    if (c->name == _name)
    {
      return c->id;
    }
  }
  return ERR_ID;
}
GLuint Shader::CacheUniform(std::string _name)
{
  GLuint id = glGetUniformLocation(programID, _name.c_str());
  if (id != ERR_ID && id != GL_INVALID_OPERATION && id != 0xFFFFFFFF)
  {
    CachedUniforms c;
    c.name = _name;
    c.id = id;
    uniforms.push_back(c);
  }
  else
  {
    //In case of GL_INVALID_OPERATION
    id = ERR_ID;
  }
  return id;
}