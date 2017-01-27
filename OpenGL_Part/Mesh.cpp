#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures) {
  this->vertices = vertices;
  this->indices = indices;
  this->textures = textures;

  this->setupMesh();
}

void Mesh::setupMesh() {
  glGenVertexArrays(1, &this->VAO);
  glGenBuffers(1, &this->VBO);
  glGenBuffers(1, &this->VEO);

  glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->VEO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint), &this->indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(2);

  glBindVertexArray(0);
}

void Mesh::Draw(Shader shader) {
  GLuint diffuseNo = 1;
  GLuint specularNo = 1;
  for (GLuint i = 0; i < this->textures.size(); ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, this->textures[i].id);
    stringstream ss;
    string number;
    string name = this->textures[i].type;

    if (name == "texture_diffuse")
      ss << diffuseNo++;
    else if (name == "texture_specular")
      ss << specularNo++;
    
    number = ss.str();
    glUniform1i(glGetUniformLocation(shader.programID, ("material." + name + number).c_str()), i);
  }

  //glUniform1f(glGetUniformLocation(shader.ProgramID, "material.shininess"), 32.0f);

  glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);


  for (GLuint i = 0; i < this->textures.size(); ++i) {
    glActiveTexture(GL_TEXTURE0 + i);
    glBindTexture(GL_TEXTURE_2D, 0);
  }
}
