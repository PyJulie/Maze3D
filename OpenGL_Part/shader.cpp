#include "shader.h"

void Shader::compile(const GLchar * vertexSource, const GLchar * fragmentSource, const GLchar * geometrySource)
{
  GLuint vertexShader, fragmentShader, geometryShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSource, NULL);
  glCompileShader(vertexShader);
  checkCompileErrors(vertexShader, "VERTEX");

  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
  glCompileShader(fragmentShader);
  checkCompileErrors(fragmentShader, "FRAGMENT");

  if (geometrySource != nullptr) {
    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &geometrySource, NULL);
    glCompileShader(geometryShader);
    checkCompileErrors(geometryShader, "GEOMETRY");
  }

  //shader program;
  this->programID = glCreateProgram();
  glAttachShader(this->programID, vertexShader);
  glAttachShader(this->programID, fragmentShader);
  if (geometrySource != nullptr)
    glAttachShader(this->programID, geometryShader);

  glLinkProgram(this->programID);
  checkCompileErrors(this->programID, "PROGRAM");

  //delete
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  if (geometrySource != nullptr)
    glDeleteShader(geometryShader);

}

Shader & Shader::use()
{
  glUseProgram(this->programID);
  return *this; 
}

void Shader::setFloat(const GLchar * name, GLfloat value, GLboolean useShader)
{
  if (useShader)
    this->use();

  glUniform1f(glGetUniformLocation(this->programID, name), value);
}

void Shader::setInteger(const GLchar * name, GLint value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform1i(glGetUniformLocation(this->programID, name), value);
}

void Shader::setVector2f(const GLchar* name, GLfloat x, GLfloat y, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform2f(glGetUniformLocation(this->programID, name), x, y);
}

void Shader::setVector2f(const GLchar* name, const glm::vec2& value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform2f(glGetUniformLocation(this->programID, name), value.x, value.y);
}

void Shader::setVector3f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform3f(glGetUniformLocation(this->programID, name), x, y, z);
}

void Shader::setVector3f(const GLchar* name, const glm::vec3& value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform3f(glGetUniformLocation(this->programID, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const GLchar* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform4f(glGetUniformLocation(this->programID, name), x, y, z, w);
}

void Shader::setVector4f(const GLchar* name, const glm::vec4& value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniform4f(glGetUniformLocation(this->programID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4f(const GLchar* name, const glm::mat4& value, GLboolean useShader)
{
  if (useShader)
    this->use();
  glUniformMatrix4fv(glGetUniformLocation(this->programID, name), 1, GL_FALSE, glm::value_ptr(value));
}



void Shader::checkCompileErrors(GLuint object, std::string type)
{
  GLint success;
  GLchar infoLog[1024];
  if (type == "PROGRAM") {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER : Link-time \n type: " << type << "\n infolog: " << infoLog << std::endl;
    }
  } else {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      std::cout << "ERROR::SHADER : compile-time \n type: " << type << "\n infolog: " << infoLog << std::endl;
    }
  }
}


