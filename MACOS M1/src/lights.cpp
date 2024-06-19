#include "lights.h"
#include "camera.h"
#include "config.h"
#include "depth_map.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "model.h"
#include "engine.h"
#include <algorithm>
#include <complex>

LightNode::LightNode(string n) : Node(n)
{
  diff_farba=glm::vec3(1.0f,1.0f,1.0f);
  sila=1.0f;
  inherit_t=true;
  can_modify=true;

  ambient = 0.2f;
}

LightNode::~LightNode()
{
}

void LightNode::update()
{
  Node::update();
  gin_get_active_scene()->env.add_light(this);

}

void LightNode::draw() {
  if(gin_get_fdraw())
  {
    // Model *model=gin_get_asset_manager()->get_model("gin_cube");
    // gin_get_main_renderer()->draw(model,get_transform().get_global_transform());
  }
}

void LightNode::copy(Node *target)
{
  LightNode*nova=new LightNode(get_name());
  nova->set_transform(get_transform());
  nova->set_color(get_diff_farba());
  nova->set_sila(get_sila());
  target->add_child(nova);

  for(int i=0;i<get_children().size();i++)
  {
    Node *decko=get_children().at(i);
    decko->copy(nova);
  }

}

glm::vec3 LightNode::get_diff_farba()
{
  return diff_farba;
}

float LightNode::get_sila()
{
  return sila;
}


void LightNode::set_sila(float v)
{
  sila=v;
}

void LightNode::set_color(glm::vec3 color)
{
  diff_farba=color;
}


void LightNode::set_ambient(float a) {
  ambient = a;
}

float LightNode::get_ambient() {
  return ambient;
}

SpotLightNode::SpotLightNode(string node) : Node(node) {

  diff_farba=glm::vec3(1.0f,1.0f,1.0f);
  sila=1.0f;
  inherit_t=true;
  can_modify=true;


  direction = glm::vec3(0,0,-1);
  cut_off = 30.0f;

  depth_map = new DepthMap(get_spot_light_shadow_res(),get_spot_light_shadow_res());
 // projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,0.1f,100.0f);
  projection = glm::perspective(18.0f/9.0f,1.0f,0.1f,100.0f);

  draw_shadow = true;

  ambient = 0.2f;
  bias = 0.05f;
}

SpotLightNode::~SpotLightNode() {
  delete depth_map;
}

void SpotLightNode::copy(Node *target) {

  SpotLightNode*nova=new SpotLightNode(get_name());
  nova->set_transform(get_transform());
  nova->set_color(get_diff_farba());
  nova->set_sila(get_sila());
  nova->set_cut_off(get_cut_off());
  nova->set_direction(get_direction());

  target->add_child(nova);

  for(int i=0;i<get_children().size();i++)
  {
    Node *decko=get_children().at(i);
    decko->copy(nova);
  }
}


void SpotLightNode::update()
{
  Node::update();
  gin_get_active_scene()->env.add_spot_light(this);

  projection = glm::perspective(18.0f/9.0f,1.0f,0.1f,10000.0f);
  view = glm::lookAt(get_transform().get_position(),
                     get_transform().get_position() + direction,
                     glm::vec3(0.0f,1.0f,0.0f));
}


glm::mat4 SpotLightNode::get_light_space() {
  return projection * view;
}

void SpotLightNode::draw() {
  if(gin_get_fdraw())
  {
       // Model *model=gin_get_asset_manager()->get_model("gin_cube");
       // gin_get_main_renderer()->draw(model,get_transform().get_global_transform());
  }
}

float SpotLightNode::get_cut_off() {
  return cut_off;
}

glm::vec3 SpotLightNode::get_direction() {
  return direction;
}

void SpotLightNode::set_cut_off(float cut) {
  cut_off = cut;
}

void SpotLightNode::set_direction(glm::vec3 dir) {
  direction = dir;
}


glm::vec3 SpotLightNode::get_diff_farba()
{
  return diff_farba;
}

float SpotLightNode::get_sila()
{
  return sila;
}


void SpotLightNode::set_sila(float v)
{
  sila=v;
}

void SpotLightNode::set_color(glm::vec3 color)
{
  diff_farba=color;
}


DepthMap* SpotLightNode::get_depth_map() {
  return depth_map;
}


void SpotLightNode::set_transform(Transform i ) {
  Node::set_transform(i);
  draw_shadow = true;
}

void SpotLightNode::set_ambient(float a) {
  ambient = a;
}

float SpotLightNode::get_ambient() {
  return ambient;
}


glm::mat4 SpotLightNode::get_projection() {
  return projection;
}

glm::mat4 SpotLightNode::get_view(){
  return view;
}


void SpotLightNode::set_bias(float b) {
  bias = b;
}

float SpotLightNode::get_bias() {
  return bias;
}
