#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H

#include "camera.h"


class OrbitCamera: public Camera
{
public:
  OrbitCamera(float aspect_ratio,float fov,float z_near,float z_far);
  ~OrbitCamera();

  void update();
  void controls();

  void look_at(glm::vec3 target);

  void set_radius(float f);
  float get_radius();

  void null_v();
private:
  glm::vec3 rotation;
  float v;
  float h;

  float radius;

  glm::vec3 target;

  float lastX;
  float lastY;
};

#endif
