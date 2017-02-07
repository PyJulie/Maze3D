#include "resource_manager.h"
#include <fstream>
#include <iostream>
#include <sstream>

#include <SOIL.h>

std::map<std::string, Shader> ResourceManager::map_Shaders;
std::map<std::string, Texture2D> ResourceManager::map_Textures;

Shader ResourceManager::loadShader(const std::string name, GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderfile)
{
  map_Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderfile);
  return map_Shaders[name];
}

Shader ResourceManager::getShader(const std::string name)
{
  return map_Shaders[name];
}

Texture2D ResourceManager::loadTexture(const std::string name, const GLchar * file, GLboolean alpha)
{
  map_Textures[name] = loadTextureFromFile(file, alpha);
  return map_Textures[name];
}

Texture2D ResourceManager::getTexture(const std::string name)
{
  return map_Textures[name];
}

void ResourceManager::clear() {
  for (std::map<std::string, Shader>::iterator iter = map_Shaders.begin(); iter != map_Shaders.end(); ++iter)
    glDeleteProgram(iter->second.programID);

  for (std::map<std::string, Texture2D>::iterator iter = map_Textures.begin(); iter != map_Textures.end(); ++iter)
    glDeleteTextures(1, &iter->second.ID);

}

Shader ResourceManager::loadShaderFromFile(const GLchar * vShaderFile, const GLchar * fShaderFile, const GLchar * gShaderFile)
{
  std::string vertexCode;
  std::string fragmentCode;
  std::string geometryCode;
  try {
    std::stringstream vShaderStream, fShaderStream;
    std::ifstream vertexShaderFile(vShaderFile);
    std::ifstream fragmentShaderFile(fShaderFile);
    
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();
    
    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();

    vertexShaderFile.close();
    fragmentShaderFile.close();

    if (gShaderFile != nullptr) {
      std::stringstream gShaderStream;
      std::ifstream geometryShaderFile(gShaderFile);

      gShaderStream << geometryShaderFile.rdbuf();
      geometryCode = gShaderStream.str();

      geometryShaderFile.close();
    }
  }
  catch (std::exception e) {
    std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
  }

  const GLchar *vShaderCode = vertexCode.c_str();
  const GLchar *fShaderCode = fragmentCode.c_str();
  const GLchar *gShaderCode = geometryCode.c_str();

  Shader shader;
  shader.compile(vShaderCode, fShaderCode, gShaderFile == nullptr ? nullptr : gShaderCode);
  return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const GLchar * file, GLboolean alpha){
  Texture2D texture;
  if (alpha) {
    texture.image_format = GL_RGBA;
    texture.internal_format = GL_RGBA;
  }

  int width, height;
  unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.image_format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);
  texture.generate(width, height, image);
  SOIL_free_image_data(image);

  return texture;
}
