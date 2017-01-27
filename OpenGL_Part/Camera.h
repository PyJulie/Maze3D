#ifndef CAMERA_H
#define CAMERA_H

#include <vector>;
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
  FORWARD,
  BACKWARD,
  LEFT,
  RIGHT,
  UP,
  DOWN
};

const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 3.0f;
const GLfloat SENSITIVITY = 0.15f;
const GLfloat ZOOM = 45.0f;

class Camera {
public:
  Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
    GLfloat yaw = YAW, GLfloat pitch = PITCH): Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), 
    MouseSensitivity(SENSITIVITY), Zoom(ZOOM){
   
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Picth = pitch;
    this->updateCameraVectors();
  }

  glm::mat4 getViewMatrix();
  void ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime);
  void ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constraintPitch = true);
  void ProcessMouseScroll(GLfloat yoffset);


  glm::vec3 Position;
  glm::vec3 WorldUp;
  glm::vec3 Front;

  glm::vec3 Up; //view坐标系 的上方向
  glm::vec3 Right; // view坐标系的 右方向
  
  //Eular Angles
  GLfloat Picth;
  GLfloat Yaw;

  //Camera options
  GLfloat MovementSpeed;
  GLfloat MouseSensitivity;
  GLfloat Zoom;
private:
  void updateCameraVectors();
};

#endif // !CAMERA_H
