#pragma once
#ifndef MESH_H
#define MESH_H

#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "shader.h"

using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::stringstream;

#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/scene.h>


struct Vertex {
  glm::vec3 Position;
  glm::vec3 Normal;
  glm::vec2 TexCoords;
};

struct Texture {
  GLuint id;
  string type;
  aiString path;
};

class Mesh {
public:
  Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
  void Draw(Shader shader);

  vector<Vertex> vertices;
  vector<GLuint> indices;
  vector<Texture> textures;

private:
  GLuint VAO, VBO, VEO;
  void setupMesh();
};



#endif
