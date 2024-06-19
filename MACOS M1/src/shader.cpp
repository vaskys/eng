#include "shader.h"
#include <fstream>
#include <sstream>

BaseShader::BaseShader(string vertex_path,string fragment_path)
{
  string vertex_code;
  string fragment_code;

  fstream vertex_subor;
  fstream fragment_subor;

  vertex_subor.open(vertex_path);
  fragment_subor.open(fragment_path);

  stringstream vertex_stream;
  stringstream fragment_stream;

  vertex_stream<<vertex_subor.rdbuf();
  fragment_stream<<fragment_subor.rdbuf();

  vertex_code=vertex_stream.str();
  fragment_code=fragment_stream.str();

  vertex_subor.close();
  fragment_subor.close();

  compile(vertex_code,fragment_code);
  register_uniforms();

}

BaseShader::BaseShader(string vertex_kod,string fragment_kod,bool bruh)
{
  compile(vertex_kod,fragment_kod);
  register_uniforms();
}

BaseShader::~BaseShader()
{
  glDeleteShader(id);
  debug_print("Shader delete");
}

void BaseShader::compile(string vertex_code,string fragment_code)
{
  unsigned int vertex;
  unsigned int fragment;

  int status;
  char log[512];

  const char* shader_code_vertex=vertex_code.c_str();
  const char* shader_code_fragemt=fragment_code.c_str();

  vertex=glCreateShader(GL_VERTEX_SHADER);    
  glShaderSource(vertex,1,&shader_code_vertex,NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex,GL_COMPILE_STATUS,&status);
  if(!status)
  {
    glGetShaderInfoLog(vertex,512,NULL,log);
    debug_print("vertex error "+string(log));

  }
  else
  debug_print("vertex gucci");

  fragment=glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment,1,&shader_code_fragemt,NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment,GL_COMPILE_STATUS,&status);
  if(!status)
  {
    glGetShaderInfoLog(fragment,512,NULL,log);
    debug_print("fragmet error "+string(log));
  }
  else
  debug_print("fragment gucci");

  id=glCreateProgram();
  glAttachShader(id,vertex);
  glAttachShader(id,fragment);
  glLinkProgram(id);

  glGetProgramiv(id,GL_LINK_STATUS,&status);
  if(!status)
  {
    glGetProgramInfoLog(this->id,512,NULL,log);
    debug_print("shader link error "+string(log));
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);

}

void BaseShader::use()
{
  glUseProgram(id);
}

unsigned int BaseShader::get_id()
{
  return id;
}


void BaseShader::register_uniforms()
{

}

void BaseShader::send_float_uniform(const string name,float v) 
{
  glUniform1f(glGetUniformLocation(id, name.c_str()), v); 
}

void BaseShader::send_int_uniform(const string name,int v) 
{
  glUniform1i(glGetUniformLocation(id, name.c_str()), v); 
}

void BaseShader::send_vec3_uniform(const string name,glm::vec3 v)
{
  glUniform3f(glGetUniformLocation(id,name.c_str()),v.x,v.y,v.z);
}

void BaseShader::send_mat4_uniform(const string name,glm::mat4 mat)
{
  glUniformMatrix4fv(glGetUniformLocation(id,name.c_str()),1,GL_FALSE,glm::value_ptr(mat));
}

void BaseShader::send_texture_uniforom(const string name, unsigned int texture_id) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(glGetUniformLocation(id, name.c_str()),texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}


DefaultShader::DefaultShader(string vertex_code_i,string fragment_code_i,bool bruh) : BaseShader(vertex_code_i,fragment_code_i,bruh)
{
  //    compile(vertex_code_i,fragment_code_i);
  register_uniforms();

  meshe.clear();
}

DefaultShader::DefaultShader(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path)
{
}

DefaultShader::~DefaultShader()
{
  BaseShader::~BaseShader();
  meshe.clear();
}


void DefaultShader::add_mesh(MESH_T*mesh)
{
  meshe.push_back(mesh);
}

vector<MESH_T*> DefaultShader::get_meshe()
{
  return meshe;
}

void DefaultShader::clear_meshe()
{
  meshe.clear();
}

void DefaultShader::send_projection_uniform(glm::mat4 projection)
{
  glUniformMatrix4fv(projection_uniform,1,GL_FALSE,glm::value_ptr(projection));
}
void DefaultShader::send_view_uniform(glm::mat4 view_i)
{
  glUniformMatrix4fv(view_uniform,1,GL_FALSE,glm::value_ptr(view_i));
}

void DefaultShader::send_model_uniform(glm::mat4 model)
{
  glUniformMatrix4fv(model_uniform,1,GL_FALSE,glm::value_ptr(model));
}

void DefaultShader::send_diffuse_color_uniform(glm::vec3 color)
{
  glUniform3f(diffuse_color_uniform,color.x,color.y,color.z);
}

void DefaultShader::send_diffuse_texutre_uniform(unsigned int texture_id)

{
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(diffuse_texture_uniform,texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}


void DefaultShader::send_specular_color_uniform(glm::vec3 specular_color) {
  glUniform3f(specular_color_uniform,specular_color.x,specular_color.y,specular_color.z);
}

void DefaultShader::send_specular_color_power_uniform(float s) {
  glUniform1f(specular_color_power_uniform,s);
}

void DefaultShader::send_camera_pos_uniform(glm::vec3 pos)
{
  glUniform3f(camera_pos_uniform,pos.x,pos.y,pos.z);
}

void DefaultShader::send_bone_transform(glm::mat4 bone_transform,int id)
{
  glUniformMatrix4fv(bones_transform_uniform[id],1,GL_FALSE,glm::value_ptr(bone_transform));
}
////////////////////////////////////////////////////////////////////////
void DefaultShader::send_spot_light_color(glm::vec3 color, int i) {
  glUniform3f(spot_lights_color_uniform[i],color.x,color.y,color.z);
}

void DefaultShader::send_spot_light_pos(glm::vec3 pos, int i)
{
  glUniform3f(spot_lights_pos_uniform[i],pos.x,pos.y,pos.z);
}

void DefaultShader::send_spot_light_sila(float sila,int i)
{
  glUniform1f(spot_lights_sila_uniform[i],sila);
}

void DefaultShader::send_spot_lights_pocet(unsigned int i)
{
  glUniform1i(spot_lights_pocet_aktiv_uniform,i);    
}

void DefaultShader::send_spot_lights_dir(glm::vec3 pos, int i)
{
  glUniform3f(spot_lights_dir_uniform[i],pos.x,pos.y,pos.z);
}

void DefaultShader::send_spot_lights_cut_off(float cut,int i)
{
  glUniform1f(spot_lights_cutoff_uniform[i],glm::cos(glm::radians(cut)));
}

void DefaultShader::send_spot_lights_ambient(float a,int i)
{
  glUniform1f(spot_lights_ambient_uniform[i],a);
}


void DefaultShader::send_spot_lights_shadow_map(unsigned int texture_id, int i) {
  glActiveTexture(GL_TEXTURE0+texture_id);
  glUniform1i(spot_lights_shadow_map_uniform[i],texture_id);
  glBindTexture(GL_TEXTURE_2D, texture_id);
}

void DefaultShader::send_spot_lights_light_space_matrix(glm::mat4 m,int i) {
  glUniformMatrix4fv(spot_lights_light_space_matrix_uniform[i],1,GL_FALSE,glm::value_ptr(m));
}

void DefaultShader::send_spot_lights_bias(float a,int i)
{
  glUniform1f(spot_lights_bias_uniform[i],a);
}

////////////////////////////////////////////////////////////////////
void DefaultShader::send_light_color(glm::vec3 color, int i)
{
  glUniform3f(lights_color_uniform[i],color.x,color.y,color.z);
}
void DefaultShader::send_light_pos(glm::vec3 pos, int i)
{
  glUniform3f(lights_pos_uniform[i],pos.x,pos.y,pos.z);
}

void DefaultShader::send_light_sila(float sila,int i)
{
  glUniform1f(lights_sila_uniform[i],sila);
}

void DefaultShader::send_light_ambient(float a,int i)
{
  glUniform1f(lights_ambient_uniform[i],a);
}

void DefaultShader::send_lights_pocet(unsigned int i)
{
  glUniform1i(lights_pocet_aktiv_uniform,i);    
}

void DefaultShader::send_global_light_color(glm::vec3 color)
{
  glUniform3f(light_global_color_uniform,color.x,color.y,color.z);
}

void DefaultShader::send_global_light_dir(glm::vec3 dir)
{
  glUniform3f(light_global_dir_uniform,dir.x,dir.y,dir.z);
}

void DefaultShader::send_global_light_status(bool status)
{
  glUniform1i(light_global_status_uniform,status);
}

void DefaultShader::send_global_light_space_matrix_uniform(glm::mat4 m) {
  glUniformMatrix4fv(light_space_matrix_uniform, 1, GL_FALSE, glm::value_ptr(m));
}

void DefaultShader::send_global_light_ambient(float a) {
  glUniform1f(light_global_ambient_uniform,a);
}

void DefaultShader::send_global_depth_map(unsigned int mapa) {

  glActiveTexture(GL_TEXTURE0+mapa);
  glUniform1i(global_light_depth_map_uniform,mapa);
  glBindTexture(GL_TEXTURE_2D, mapa);

}

void DefaultShader::send_fog_type(int v) {
  glUniform1i(fog_type_uniform,v);
}

void DefaultShader::send_fog_status(bool v) {
  glUniform1i(fog_status_uniform,v);
}

void DefaultShader::send_fog_start(float v) {
  glUniform1f(fog_start_uniform,v);
}

void DefaultShader::send_fog_end(float v) {
  glUniform1f(fog_end_uniform,v);
}

void DefaultShader::send_fog_color(glm::vec3 color) {
  glUniform3f(fog_color_uniform,color.x,color.y,color.z);
}

void DefaultShader::send_fog_density(float v) {
  glUniform1f(fog_density_uniform,v);
}

void DefaultShader::register_uniforms()
{
  projection_uniform=glGetUniformLocation(id,"projection");
  view_uniform=glGetUniformLocation(id,"view");
  camera_pos_uniform=glGetUniformLocation(id,"cam_pos");
  model_uniform=glGetUniformLocation(id,"model");
  diffuse_color_uniform=glGetUniformLocation(id,"diffuse_color");
  diffuse_texture_uniform=glGetUniformLocation(id,"texture_diffuse");

  specular_color_uniform = glGetUniformLocation(id, "specular_color");
  specular_color_power_uniform = glGetUniformLocation(id, "specular_power");

  for(int i=0;i<100;i++)
  {
    string u_id="finalBonesMatrices["+to_string(i)+"]";
    bones_transform_uniform[i]=glGetUniformLocation(id,u_id.c_str());
  }

  for(int i=0;i<4;i++)
  {
    string id_pos="svetla["+to_string(i) + "].pos";
    string id_color="svetla["+to_string(i) + "].color";
    string id_sila="svetla["+to_string(i) + "].sila";
    string id_ambient="svetla["+to_string(i) + "].ambient";

    lights_pos_uniform[i]=glGetUniformLocation(id,id_pos.c_str());
    lights_color_uniform[i]=glGetUniformLocation(id,id_color.c_str());
    lights_sila_uniform[i]=glGetUniformLocation(id,id_sila.c_str());
    lights_ambient_uniform[i]=glGetUniformLocation(id,id_ambient.c_str());


    string id_ambient_spot="spot_lights["+to_string(i) + "].ambient";
    string id_pos_spot="spot_lights["+to_string(i) + "].pos";
    string id_color_spot="spot_lights["+to_string(i) + "].color";
    string id_sila_spot="spot_lights["+to_string(i) + "].sila";
    string id_cut_spot="spot_lights["+to_string(i) + "].cut_off";
    string id_dir_spot="spot_lights["+to_string(i) + "].direction";
    string id_shadow_map_spot="shadow_s["+to_string(i) + "]";
    string id_light_space_matrix_spot="spot_lights["+to_string(i) + "].light_space";
    string id_light_bias_spot="spot_lights["+to_string(i) + "].bias";

    spot_lights_pos_uniform[i] =  glGetUniformLocation(id, id_pos_spot.c_str());
    spot_lights_color_uniform[i] =  glGetUniformLocation(id, id_color_spot.c_str());
    spot_lights_sila_uniform[i] =  glGetUniformLocation(id, id_sila_spot.c_str());
    spot_lights_cutoff_uniform[i] =  glGetUniformLocation(id, id_cut_spot.c_str());
    spot_lights_dir_uniform[i] =  glGetUniformLocation(id, id_dir_spot.c_str());
    spot_lights_shadow_map_uniform[i] =  glGetUniformLocation(id, id_shadow_map_spot.c_str());
    spot_lights_light_space_matrix_uniform[i] =  glGetUniformLocation(id, id_light_space_matrix_spot.c_str());
    spot_lights_ambient_uniform[i] =  glGetUniformLocation(id, id_ambient_spot.c_str());
    spot_lights_bias_uniform[i] = glGetUniformLocation(id, id_light_bias_spot.c_str());
  }
  lights_pocet_aktiv_uniform=glGetUniformLocation(id,"active_svetla");
  spot_lights_pocet_aktiv_uniform=glGetUniformLocation(id,"active_spot_lights");

  light_global_ambient_uniform=glGetUniformLocation(id,"global_light_ambient");
  light_global_dir_uniform=glGetUniformLocation(id,"global_light_dir");
  light_global_color_uniform=glGetUniformLocation(id,"global_light_color");
  light_global_status_uniform=glGetUniformLocation(id,"global_light_status");
  light_space_matrix_uniform = glGetUniformLocation(id, "light_space_matrix");
  global_light_depth_map_uniform = glGetUniformLocation(id,"global_light_shadow");


  fog_type_uniform = glGetUniformLocation(id, "fog_type");
  fog_status_uniform = glGetUniformLocation(id,"fog_status");
  fog_color_uniform = glGetUniformLocation(id,"fog_color");
  fog_start_uniform = glGetUniformLocation(id,"fog_start");
  fog_end_uniform = glGetUniformLocation(id,"fog_end");
  fog_density_uniform = glGetUniformLocation(id, "fog_density");
}


