#include "skybox_shader.h"
#include "skybox.h"


SkyboxShader::SkyboxShader(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path) {
    register_uniforms();
}

SkyboxShader::~SkyboxShader() {
    BaseShader::~BaseShader();
}


void SkyboxShader::register_uniforms() {
    projection_uniform=glGetUniformLocation(id,"projection");
    view_uniform=glGetUniformLocation(id,"view");
    skybox_texture = glGetUniformLocation(id,"skybox");
}

void SkyboxShader::use() {
    glUseProgram(id);
}



void SkyboxShader::send_projection_uniform(glm::mat4 projection)
{
    glUniformMatrix4fv(projection_uniform,1,GL_FALSE,glm::value_ptr(projection));
}
void SkyboxShader::send_view_uniform(glm::mat4 view_i)
{
    glUniformMatrix4fv(view_uniform,1,GL_FALSE,glm::value_ptr(view_i));
}

void SkyboxShader::send_skybox_texture(unsigned int texture_id) {
    glActiveTexture(GL_TEXTURE0+texture_id);
    glUniform1i(skybox_texture,texture_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture_id);

}

