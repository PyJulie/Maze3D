#pragma once
#ifndef  MODEL_H
#define  MODEL_H

#pragma once
// Std. Includes
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// GL Includes

#include <GL/glew.h> // Contains all the necessery OpenGL includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SOIL.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

GLuint TextureFromFile(const char* path, string directory);

class Model {
public:
  Model(const GLchar *path);
  Model();
  void Draw(Shader shader);
private:
  string directory;
  vector<Mesh> meshes;
  vector<Texture> textures_loaded;

  void loadModel(string path);
  void processNode(aiNode *node, const aiScene *scene);
  Mesh processMesh(aiMesh *mesh, const aiScene* scene);
  vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, string typeName);

  
};


#endif // ! MODEL_H
