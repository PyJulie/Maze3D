#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <gl/glew.h>

#include "shader.h"
#include "texture2d.h"

class ResourceManager {
public:
  static std::map<std::string, Shader> map_Shaders;
  static std::map<std::string, Texture2D> map_Textures;
  static Shader loadShader(const std::string name, GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderfile = nullptr);
  static Shader getShader(const std::string name);
  static Texture2D loadTexture(const std::string name, const GLchar *file, GLboolean alpha = false);
  static Texture2D getTexture(const std::string name);
  static void clear();
private:
  ResourceManager(){}//虚函数，不要对象，只用静态方法
  static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile);
  static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif 
