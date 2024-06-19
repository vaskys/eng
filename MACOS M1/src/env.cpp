#include "env.h"
#include "config.h"
#include "depth_map.h"
#include "engine.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/geometric.hpp"
#include <vector>

Env::Env()
{
  light_nodes.clear();
  spot_light_nodes.clear();

  set_global_light_default();

  gr_decay = 0.96f;
  gr_exposure = 0.2f;
  gr_density = 0.9f;
  gr_weight = 0.2f;
  gr_status = false;


  fog_type = 0;
  fog_status = false;
  fog_color = glm::vec3(0.75f);
  fog_start = 1.0f;
  fog_end = 10.0f;
  fog_density = 1.0f;

  scatter_value = 0.1f;
  volumetric_light_status = true;
  volumetric_light_status = false;

  center = glm::vec3(0.0f);
  volumetric_fog_density = 1.0f;
  volumetric_fog_status = 3;
}

Env::~Env()
{
  light_nodes.clear();
  spot_light_nodes.clear();

}

void Env::set_global_light_default()
{
  global_light_dir=glm::vec3(0,1,1);
  global_light_color=glm::vec3(1,1,1);
  global_light_status=true;
  global_light_ambient = 0.6f;

  cal_gr_decal_model();
}

void Env::add_spot_light(SpotLightNode *node) {
  spot_light_nodes.push_back(node);
}

vector<SpotLightNode*> Env::get_spot_lights() {
  return spot_light_nodes;
}

void Env::remove_spot_light(SpotLightNode *node) {
  spot_light_nodes.erase(remove(spot_light_nodes.begin(),spot_light_nodes.end(),node),spot_light_nodes.end());
}

void Env::add_light(LightNode *node)
{
  light_nodes.push_back(node);
}


vector<LightNode*> Env::get_lights()
{
  return light_nodes;
}

void Env::remove_light(LightNode *node)
{
  light_nodes.erase(remove(light_nodes.begin(),light_nodes.end(),node),light_nodes.end());
}

void Env::clear()
{
  light_nodes.clear();
  spot_light_nodes.clear();
}

void Env::set_global_light_dir(glm::vec3 dir)
{
  global_light_dir=dir;
  cal_gr_decal_model();
  redraw_shadow = true;
}

void Env::set_global_light_color(glm::vec3 color)
{
  global_light_color=color;
}


void Env::set_global_light_status(bool status)
{
  global_light_status=status;
}

glm::vec3 Env::get_global_light_dir()
{
  return global_light_dir;
}

glm::vec3 Env::get_global_light_color()
{
  return global_light_color;
}


bool Env::get_global_light_status()
{
  return global_light_status;
}


glm::vec4 cornersClipSpace[] = {
        glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f), // near bottom left
        glm::vec4(1.0f, -1.0f, -1.0f, 1.0f),  // near bottom right
        glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),  // near top left
        glm::vec4(1.0f, 1.0f, -1.0f, 1.0f),   // near top right
        glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f),  // far bottom left
        glm::vec4(1.0f, -1.0f, 1.0f, 1.0f),   // far bottom right
        glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f),   // far top left
        glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)     // far top right
    };

std::vector<glm::vec4> getFrustumCornersWorldSpace(const glm::mat4& proj, const glm::mat4& view)
{
    glm::mat4 idk = glm::perspective(45.0f, 1.0f,0.1f,50.0f);
    const auto inv = glm::inverse(idk * view);
    
     std::vector<glm::vec4> frustumCorners;
    // for (unsigned int x = 0; x < 2; ++x)
    // {
    //     for (unsigned int y = 0; y < 2; ++y)
    //     {
    //         for (unsigned int z = 0; z < 2; ++z)
    //         {
    //             const glm::vec4 pt = 
    //                 inv * glm::vec4(
    //                     2.0f * x - 1.0f,
    //                     2.0f * y - 1.0f,
    //                     2.0f * z - 1.0f,
    //                     1.0f);
    //             frustumCorners.push_back(pt / pt.w);
    //         }
    //     }
    // }
  //
   for (int i = 0; i < 8; ++i) {
        glm::vec4 cornerWorldSpace = inv * cornersClipSpace[i];
        cornerWorldSpace /= cornerWorldSpace.w; 
        frustumCorners.push_back(cornerWorldSpace);
    }
    
    return frustumCorners;
}



void Env::cal_global_light_matrix() {
  auto corners = getFrustumCornersWorldSpace(gin_get_active_camera()->get_projection_matrix(), gin_get_active_camera()->get_view_matrix());
  glm::vec3 center = glm::vec3(0, 0, 0);
  for (const auto& v : corners)
  {
      center += glm::vec3(v);
  }
  center /= corners.size();
      
 const auto lightView = glm::lookAt(
    center + global_light_dir,
    center,
    glm::vec3(0.0f, 1.0f, 0.0f)
);
      float minX = std::numeric_limits<float>::max();
  float maxX = std::numeric_limits<float>::lowest();
  float minY = std::numeric_limits<float>::max();
  float maxY = std::numeric_limits<float>::lowest();
  float minZ = std::numeric_limits<float>::max();
  float maxZ = std::numeric_limits<float>::lowest();
  for (const auto& v : corners)
  {
      const auto trf = lightView * v;
      minX = std::min(minX, trf.x);
      maxX = std::max(maxX, trf.x);
      minY = std::min(minY, trf.y);
      maxY = std::max(maxY, trf.y);
      minZ = std::min(minZ, trf.z);
      maxZ = std::max(maxZ, trf.z);
  }
  constexpr float zMult = 2.0f;
  if (minZ < 0)
  {
      minZ *= zMult;
  }
  else
  {
      minZ /= zMult;
  }
  if (maxZ < 0)
  {
      maxZ /= zMult;
  }
  else
  {
      maxZ *= zMult;
  }
     
  const glm::mat4 lightProjection = glm::ortho(minX, maxX, minY, maxY, minZ, maxZ);
  global_light_view = lightView;
  global_light_projection = lightProjection;

  global_light_space_matrix = lightProjection * lightView;


 //  global_light_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f,0.1f,100.0f);
 //  glm::vec3 c_pos = gin_get_active_camera()->get_position();
 //  global_light_view = glm::lookAt(global_light_dir,
 //                                  glm::vec3(0.0f)
 //                                  ,glm::vec3(0.0f,1.0f,0.0f));
 //
 //  global_light_space_matrix = global_light_projection * global_light_view;
}


glm::mat4 Env::get_global_light_space_matrix() {
  return global_light_space_matrix;
}


glm::mat4 Env::get_global_light_view() {
  return global_light_view;
}

glm::mat4 Env::get_global_light_projection() {
   return global_light_projection;
}

float Env::get_gr_decay() {
  return gr_decay;
}


float Env::get_gr_weight() {
  return gr_weight;
}

float Env::get_gr_density() {
  return gr_density;
}

float Env::get_gr_exposure() {
  return gr_exposure;
}

void Env::set_gr_decay(float v) {
  gr_decay = v;
}

void Env::set_gr_exposure(float v) {
  gr_exposure = v;
}

void Env::set_gr_weight(float v) {
  gr_weight = v;
}

void Env::set_gr_density(float v) {
  gr_density = v;
}

void Env::cal_gr_sun_pos() {
  glm::mat4 m = glm::mat4(1.0f);
  m = glm::translate(m, glm::vec3(0,1,50) + glm::normalize(global_light_dir));

  m = glm::mat4(glm::mat3(gin_get_active_camera()->get_view_matrix()))* m;
  glm::vec3 c = glm::project(glm::vec3(0.0f),m,gin_get_active_camera()->get_projection_matrix(),glm::vec4(0.0f,0.0f,gin_get_screen_w(),gin_get_screen_h()));
  c.x = c.x / gin_get_screen_w();
  c.y = c.y / gin_get_screen_h();

  gr_sun_pos = glm::vec2(c.x,c.y);
}

glm::vec2 Env::get_gr_sun_pos() {
  cal_gr_sun_pos();
  return gr_sun_pos;
}


void Env::set_gr_status(bool s) {
  gr_status = s;
}

bool Env::get_gr_status() {
  return gr_status;
}

void Env::cal_gr_decal_model() {

  gr_decal_model = glm::mat4(1.0f);
  gr_decal_model = glm::translate(gr_decal_model,glm::vec3(0,1,50) + glm::normalize(global_light_dir));
  gr_decal_model = glm::scale(gr_decal_model,glm::vec3(10.0f));
}

glm::mat4 Env::get_gr_decal_model() {
  return gr_decal_model;
}


void Env::set_global_light_ambient(float a) {
  global_light_ambient = a;
}

float Env::get_global_light_ambient() {
  return global_light_ambient;
}


void Env::set_fog_type(int v) {
  fog_type = v;
}

void Env::set_fog_status(bool v) {
  fog_status = v;
}

void Env::set_fog_color(glm::vec3 color) {
  fog_color = color;
}

void Env::set_fog_end(float v) {
  fog_end = v;
}

void Env::set_fog_start(float v) {
  fog_start = v;
}

void Env::set_fog_density(float v) {
  fog_density = v;
}


int Env::get_fog_type() {
  return fog_type;
}

bool Env::get_fog_status() {
  return fog_status;
}

float Env::get_fog_start() {
  return fog_start;
}

float Env::get_fog_end() {
  return fog_end;
}

glm::vec3 Env::get_fog_color() {
  return fog_color;
}

float Env::get_fog_density() {
  return fog_density;
}



bool Env::get_volumetric_light_status() {
  return volumetric_light_status;
}

void Env::set_volumetric_light_status(bool i) {
  volumetric_light_status = i;
}

void Env::set_volumetric_fog_status(int i) {
  volumetric_fog_status = i;
}

int Env::get_volumetric_fog_status() {
  return volumetric_fog_status;
}
