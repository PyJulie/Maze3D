#include "Camera.h"

glm::mat4 Camera::getViewMatrix()
{
  return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
  GLfloat velocity = this->MovementSpeed * deltaTime;
  if (direction == FORWARD)
    this->Position += this->Front * velocity;
  if (direction == BACKWARD)
    this->Position -= this->Front * velocity;
  if (direction == LEFT)
    this->Position -= this->Right * velocity;
  if (direction == RIGHT)
    this->Position += this->Right * velocity;
  if (direction == UP)
    this->Position += this->WorldUp * velocity;
  if (direction == DOWN)
    this->Position -= this->WorldUp * velocity;


}

void Camera::ProcessMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constraintPitch)
{
  xoffset *= this->MouseSensitivity;
  yoffset *= this->MouseSensitivity;

  this->Yaw += xoffset;
  this->Picth += yoffset;

  if (constraintPitch) {
    if (this->Picth > 89.0f)
      this->Picth = 89.0f;
    if (this->Picth < -89.0f)
      this->Picth = -89.0f;
  }

  this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(GLfloat yoffset)
{
  if (this->Zoom >= 1.0f && this->Zoom <= 45.0f)
    this->Zoom -= yoffset;
  if (this->Zoom > 45.0f)
    this->Zoom = 45.0f;
  if (this->Zoom < 1.0f)
    this->Zoom = 1.0f;
}

void Camera::updateCameraVectors()
{
  glm::vec3 front;
  front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Picth));
  front.y = sin(glm::radians(this->Picth));
  front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Picth));
  this->Front = glm::normalize(front);
  this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));
  this->Up = glm::normalize(glm::cross(this->Right, this->Front));
  
}
