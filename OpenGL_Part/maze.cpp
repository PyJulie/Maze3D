#include "maze.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include "resource_manager.h"


Maze::Maze(){
}

void Maze::loadMazeFromFile(const char * file){
  this->objects.clear();

  std::ifstream  fstream(file);
  std::string sline;
  GLuint word;
  std::vector<std::vector<GLuint>> data;

  if (fstream) {
    while (std::getline(fstream, sline)) {
      std::istringstream iss(sline);
      std::vector<GLuint> row;
      while (iss >> word)
        row.push_back(word);

      data.push_back(row);
    }
  }
  else {
    std::cout << "ERROR::MAZE::LOADMAZEFROMFILE! " << std::endl;
  }
  
  if (data.size() > 0)
    this->initData(data);
  
}

void Maze::loadPathFromFile(const char * file){
  this->path.clear();

  std::ifstream fstream(file);
  std::string sline;
  //GLuint word;

  if (fstream) {
    while (std::getline(fstream, sline)) {
      std::istringstream iss(sline);
      glm::vec2 pathNode;
      iss >> pathNode.x >> pathNode.y;
      path.push_back(pathNode);
    }
  }
  else {
    std::cout << "ERROR::MAZE::LOADPATHFROMFILE! " << std::endl;
  }

  //if (path.size() > 0) {
  //  for (std::vector<glm::vec2>::iterator iter = path.begin(); iter != path.end(); ++iter) {
  //    std::cout << iter->x << " " << iter->y << std::endl;

  //  }
  //}
}

void Maze::draw(ObjectRenderer *renderer){
  for (std::vector<Object>::iterator iter = objects.begin(); iter != objects.end(); ++iter) {
    iter->draw(renderer);
    //renderer->drawObject(iter->image, iter->position, iter->size, iter->color);
  }
}

/**temp**/
GLboolean checkCollision(Object &one, Object &two);
Object firstNode, secondNode;
Lamp secondLamp;
GLuint pathOrder = 0;
GLboolean isChangeNode = GL_TRUE;
glm::vec3 dtPos;
/*temp*/

void Maze::animation(ObjectRenderer * renderer, GLfloat dt){
  if (isChangeNode == GL_TRUE) {
    if (pathOrder != path.size()-1) {
      isChangeNode = GL_FALSE;
      firstNode = objects[path[pathOrder].x * mazeWidth + path[pathOrder].y];

      objects[path[pathOrder].x * mazeWidth + path[pathOrder].y].color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
      
      firstLamp.position = firstNode.position;
      firstLamp.size = glm::vec3(0.5f, 3.0f, 0.5f);
      firstLamp.color = glm::vec4(1.0f);

      secondNode = objects[path[pathOrder + 1].x * mazeWidth + path[pathOrder + 1].y];
      secondLamp.position = secondNode.position;

      dtPos = secondNode.position - firstNode.position;
      pathOrder++;
    }

  }

  firstLamp.draw(renderer);
 // secondLamp.draw(renderer);

  if (!checkCollision(firstNode, secondNode)) {
    firstNode.position += dtPos * dt * glm::vec3(3.0f, 3.0f, 3.0f);
    firstLamp.position = firstNode.position;
  }
  else {
    isChangeNode = GL_TRUE;
  }

}

void Maze::initData(std::vector<std::vector<GLuint>> data)
{
  GLuint height = data.size();
  GLuint width = data[0].size();
  GLfloat unit_x = 1.0f;
  GLfloat unit_y = 1.0f;
  GLfloat unit_z = 1.0f;

  mazeWidth = width;
  mazeHeight = height;

  for (GLuint y = 0; y != height; ++y) {
    for (GLuint x = 0; x != width; ++x) {
      if (data[y][x] == 1) {
        glm::vec3 position = glm::vec3(x * unit_x, 0.0f * unit_y, y * unit_z);
        glm::vec3 size = glm::vec3(unit_x, unit_y, unit_z);
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
        Object object(ResourceManager::getTexture("wall"), ResourceManager::getTexture("wallShader"), position, size, color);

        objects.push_back(object);
      }
      else if(data[y][x] == 0){
        glm::vec3 position = glm::vec3(x * unit_x, -unit_y / 2, y * unit_z);
        glm::vec3 size = glm::vec3(unit_x, unit_y * 0.1, unit_z);
        glm::vec4 color = glm::vec4(1.0f);
        Object object(ResourceManager::getTexture("road"), ResourceManager::getTexture("road"), position, size, color);

        objects.push_back(object);
      }
      else if(data[y][x] == 5){
        glm::vec3 position = glm::vec3(x * unit_x, -unit_y / 2, y * unit_z);
        glm::vec3 size = glm::vec3(unit_x, unit_y * 0.1, unit_z);
        glm::vec4 color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        Object object(ResourceManager::getTexture("road"), ResourceManager::getTexture("road"), position, size, color);

        objects.push_back(object);

      }
      else if (data[y][x] == 8) {
        glm::vec3 position = glm::vec3(x * unit_x, -unit_y / 2, y * unit_z);
        glm::vec3 size = glm::vec3(unit_x, unit_y * 0.1, unit_z);
        glm::vec4 color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        Object object(ResourceManager::getTexture("road"), ResourceManager::getTexture("road"), position, size, color);

        objects.push_back(object);

      }
    }
  }

  /*temp*/
  //start = objects[0];
  //end = objects[8];

  //start.size = glm::vec3(0.5f, 2.0f, 0.5f);
  //start.color = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
  //end.size = glm::vec3(0.5f, 2.0f, 0.5f);
  //end.color = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);

  //startPos = start.position;
  //endPos = end.position;
  //dtPos = endPos - startPos;
  /*temp*/
}

/*temp*/
//¼ì²âÁ½¸öobjectµÄpositionÊÇ·ñÖØµþ
/*temp*/
GLboolean checkCollision(Object &one, Object &two) {
/*  glm::vec3 onePos = one.position;
  glm::vec3 twoPos = two.position*/;
  glm::vec3 dtPos = two.position - one.position;
  if (abs(dtPos.x) < 0.1 && abs(dtPos.z) < 0.1)
    return GL_TRUE;
  
  return GL_FALSE;
}
