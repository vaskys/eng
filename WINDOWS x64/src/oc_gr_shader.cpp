#include "oc_gr_shader.h"
#include "shader.h"

OcGRShader::OcGRShader(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}

OcGRShader::~OcGRShader() {
  BaseShader::~BaseShader();
}


void OcGRShader::register_uniforms() {
  color_uniform = glGetUniformLocation(id, "color");
  view_uniform = glGetUniformLocation(id,"view");
  model_uniform = glGetUniformLocation(id,"model");
  projection_uniform = glGetUniformLocation(id, "projection");

}

void OcGRShader::send_color_uniform(glm::vec3 color) {
  glUniform3f(color_uniform,color.x,color.y,color.z);
}


void OcGRShader::send_projection_uniform(glm::mat4 projection)
{
  glUniformMatrix4fv(projection_uniform,1,GL_FALSE,glm::value_ptr(projection));
}
void OcGRShader::send_view_uniform(glm::mat4 view_i)
{
  glUniformMatrix4fv(view_uniform,1,GL_FALSE,glm::value_ptr(view_i));
}

void OcGRShader::send_model_uniform(glm::mat4 model)
{
  glUniformMatrix4fv(model_uniform,1,GL_FALSE,glm::value_ptr(model));
}

void OcGRShader::use() {
  glUseProgram(id);
}



/////////////////////////////////////////////////
OcGRShaderAnimated::OcGRShaderAnimated(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path) {
  register_uniforms();
}

OcGRShaderAnimated::~OcGRShaderAnimated() {
  BaseShader::~BaseShader();
}


void OcGRShaderAnimated::register_uniforms() {
  color_uniform = glGetUniformLocation(id, "color");
  view_uniform = glGetUniformLocation(id,"view");
  model_uniform = glGetUniformLocation(id,"model");
  projection_uniform = glGetUniformLocation(id, "projection");

  for(int i=0;i<100;i++)
  {
    string u_id="finalBonesMatrices["+to_string(i)+"]";
    bones_transform_uniform[i]=glGetUniformLocation(id,u_id.c_str());
  }

}

void OcGRShaderAnimated::send_color_uniform(glm::vec3 color) {
  glUniform3f(color_uniform,color.x,color.y,color.z);
}


void OcGRShaderAnimated::send_projection_uniform(glm::mat4 projection)
{
  glUniformMatrix4fv(projection_uniform,1,GL_FALSE,glm::value_ptr(projection));
}
void OcGRShaderAnimated::send_view_uniform(glm::mat4 view_i)
{
  glUniformMatrix4fv(view_uniform,1,GL_FALSE,glm::value_ptr(view_i));
}

void OcGRShaderAnimated::send_model_uniform(glm::mat4 model)
{
  glUniformMatrix4fv(model_uniform,1,GL_FALSE,glm::value_ptr(model));
}

void OcGRShaderAnimated::use() {
  glUseProgram(id);
}


void OcGRShaderAnimated::send_bone_transform(glm::mat4 bone_transform,int id)
{
  glUniformMatrix4fv(bones_transform_uniform[id],1,GL_FALSE,glm::value_ptr(bone_transform));
}
