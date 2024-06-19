#include "volumetric_shader.h"
#include "shader.h"

VolumetricShader::VolumetricShader(string vertex_path,string fragment_path) : BaseShader(vertex_path, fragment_path) {
  register_uniforms();
}

VolumetricShader::~VolumetricShader() {

}

void VolumetricShader::send_projection_inv(glm::mat4 projection) {
  glm::mat4 p = glm::inverse(projection);
  glUniformMatrix4fv(projection_inv_uniform,1,GL_FALSE,glm::value_ptr(p));
}

void VolumetricShader::send_view_inv(glm::mat4 view) {
  glm::mat4 v = glm::inverse(view);
  glUniformMatrix4fv(view_inv_uniform,1,GL_FALSE,glm::value_ptr(v));
}

void VolumetricShader::send_camera_pos(glm::vec3 pos)
{
  glUniform3f(camera_pos_uniform,pos.x,pos.y,pos.z);
}

// void VolumetricShader::send_color_texture(unsigned int color_texture) {
//
//   glActiveTexture(GL_TEXTURE0+color_texture);
//   glUniform1i(color_texture_uniform,color_texture);
//   glBindTexture(GL_TEXTURE_2D, color_texture);
// }

void VolumetricShader::send_depth_texture(unsigned int depth_texture) {
  glActiveTexture(GL_TEXTURE0+depth_texture);
  glUniform1i(depth_texture_uniform,depth_texture);
  glBindTexture(GL_TEXTURE_2D, depth_texture);
}


void VolumetricShader::send_spot_light_color(glm::vec3 color, int i) {
  glUniform3f(spot_lights_color_uniform[i],color.x,color.y,color.z);
}

void VolumetricShader::send_spot_light_pos(glm::vec3 pos, int i)
{
  glUniform3f(spot_lights_pos_uniform[i],pos.x,pos.y,pos.z);
}

void VolumetricShader::send_spot_light_sila(float sila,int i)
{
  glUniform1f(spot_lights_sila_uniform[i],sila);
}

void VolumetricShader::send_spot_lights_pocet(unsigned int i)
{
  glUniform1i(spot_lights_pocet_aktiv_uniform,i);    
}

void VolumetricShader::send_spot_lights_dir(glm::vec3 pos, int i)
{
  glUniform3f(spot_lights_dir_uniform[i],pos.x,pos.y,pos.z);
}

void VolumetricShader::send_spot_lights_cut_off(float cut,int i)
{
  glUniform1f(spot_lights_cutoff_uniform[i],glm::cos(glm::radians(cut)));
}

void VolumetricShader::send_spot_lights_shadow_map(unsigned int texture_id, int i) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(spot_lights_shadow_map_uniform[i],texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}

void VolumetricShader::send_spot_lights_view(glm::mat4 v,int i) {
  glUniformMatrix4fv(spot_lights_view_uniform[i],1,GL_FALSE,glm::value_ptr(v));
}

void VolumetricShader::send_spot_lights_projection(glm::mat4 p,int i) {
  glUniformMatrix4fv(spot_lights_projection_uniform[i],1,GL_FALSE,glm::value_ptr(p));
}


void VolumetricShader::send_global_light_color(glm::vec3 color)
{
  glUniform3f(light_global_color_uniform,color.x,color.y,color.z);
}

void VolumetricShader::send_global_light_dir(glm::vec3 dir)
{
  glUniform3f(light_global_dir_uniform,dir.x,dir.y,dir.z);
}

void VolumetricShader::send_global_light_status(bool status)
{
  glUniform1i(light_global_status_uniform,status);
}

void VolumetricShader::send_global_light_projection(glm::mat4 m) {
  glUniformMatrix4fv(light_global_projection_uniform, 1, GL_FALSE, glm::value_ptr(m));
}

void VolumetricShader::send_global_light_view(glm::mat4 m) {
  glUniformMatrix4fv(light_global_view_uniform, 1, GL_FALSE, glm::value_ptr(m));
}

void VolumetricShader::send_global_depth_map(unsigned int mapa) {
  glActiveTexture(GL_TEXTURE0+mapa);
  glUniform1i(global_light_depth_map_uniform, mapa);
  glBindTexture(GL_TEXTURE_2D, mapa);
}


void VolumetricShader::send_scatter_value(float v) {
  glUniform1f(scatter_value_uniform,v);
}

void VolumetricShader::send_time(float t) {
  glUniform1f(time_uniform,t);
}

void VolumetricShader::send_volumetric_fog_denstiy(float i) {
  glUniform1f(volumetric_fog_density_uniform,i);
}

void VolumetricShader::register_uniforms() {
  projection_inv_uniform = glGetUniformLocation(id,"cam_projection_inv");
  view_inv_uniform = glGetUniformLocation(id,"cam_view_inv");
  camera_pos_uniform=glGetUniformLocation(id,"cam_pos");
  scatter_value_uniform = glGetUniformLocation(id,"scatter_value");
  volumetric_fog_density_uniform = glGetUniformLocation(id,"volumetric_fog_density");

  //color_texture_uniform = glGetUniformLocation(id,"color_texture");
  depth_texture_uniform = glGetUniformLocation(id,"depth_texture");
  time_uniform = glGetUniformLocation(id, "time");

  for(int i=0; i < 4;i++) {
    string id_pos_spot="spot_lights["+to_string(i) + "].pos";
    string id_color_spot="spot_lights["+to_string(i) + "].color";
    string id_sila_spot="spot_lights["+to_string(i) + "].sila";
    string id_cut_spot="spot_lights["+to_string(i) + "].cut_off";
    string id_dir_spot="spot_lights["+to_string(i) + "].direction";
    string id_shadow_map_spot="shadow_s["+to_string(i) + "]";
    string id_view_spot="spot_lights["+to_string(i) + "].view";
    string id_projection_spot="spot_lights["+to_string(i) + "].projection";

    spot_lights_pos_uniform[i] =  glGetUniformLocation(id, id_pos_spot.c_str());
    spot_lights_color_uniform[i] =  glGetUniformLocation(id, id_color_spot.c_str());
    spot_lights_sila_uniform[i] =  glGetUniformLocation(id, id_sila_spot.c_str());
    spot_lights_cutoff_uniform[i] =  glGetUniformLocation(id, id_cut_spot.c_str());
    spot_lights_dir_uniform[i] =  glGetUniformLocation(id, id_dir_spot.c_str());
    spot_lights_shadow_map_uniform[i] =  glGetUniformLocation(id, id_shadow_map_spot.c_str());
    spot_lights_view_uniform[i] =  glGetUniformLocation(id, id_view_spot.c_str());
    spot_lights_projection_uniform[i] =  glGetUniformLocation(id, id_projection_spot.c_str());
  }

  spot_lights_pocet_aktiv_uniform=glGetUniformLocation(id,"active_spot_lights");

  light_global_dir_uniform=glGetUniformLocation(id,"global_light_dir");
  light_global_color_uniform=glGetUniformLocation(id,"global_light_color");
  light_global_status_uniform=glGetUniformLocation(id,"global_light_status");
  light_global_view_uniform = glGetUniformLocation(id, "global_light_view");
  light_global_projection_uniform = glGetUniformLocation(id, "global_light_projection");
  global_light_depth_map_uniform = glGetUniformLocation(id,"global_light_shadow_map");


  volumetric_fog_status = glGetUniformLocation(id, "volumetric_fog_status");
}

void VolumetricShader::use() {
  glUseProgram(id);
}


void VolumetricShader::send_volumetric_fog_status(int i) {
  glUniform1i(volumetric_fog_status,i);
}
