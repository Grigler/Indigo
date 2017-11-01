#include "Shader.h"

#include "Application.h"

#include "Resources.h"

#include <fstream>

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
      return false;
    }
  }
  return true;
}