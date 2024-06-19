#ifndef LIGHTS_H
#define LIGHTS_H

#include "camera.h"
#include "config.h"
#include "Node.h"
#include "depth_map.h"

class LightNode: public Node
{
public:
  LightNode(string Node);
  virtual ~LightNode();

  void copy(Node *target);
  void update();

  glm::vec3 get_diff_farba();
  float get_sila();
  float get_ambient();


  void set_sila(float v);
  void set_color(glm::vec3 color);
  void set_ambient(float a);

  void draw();

private:
  glm::vec3 diff_farba;
  float sila;
  float ambient;
};


class SpotLightNode: public Node {
public:
  SpotLightNode(string Node);
  virtual ~SpotLightNode();

  void copy(Node *target);
  void update();

  glm::vec3 get_direction();
  float get_cut_off();

  void set_direction(glm::vec3 dir);
  void set_cut_off(float cut);

  glm::vec3 get_diff_farba();
  float get_sila();
  float get_ambient();

  void set_sila(float v);
  void set_color(glm::vec3 color);
  void set_ambient(float a);

  void draw();
  DepthMap *get_depth_map();
  glm::mat4 get_light_space();

  bool draw_shadow;
  void set_transform(Transform transform_i);


  glm::mat4 get_projection();
  glm::mat4 get_view();


  float get_bias();
  void set_bias(float v);

private:
  glm::vec3 direction;
  float cut_off;

  glm::vec3 diff_farba;
  float sila;
  float ambient;

  DepthMap *depth_map;

  glm::mat4 projection;
  glm::mat4 view;

  float bias;

};


#endif
