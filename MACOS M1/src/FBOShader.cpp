#include "FBOShader.h"

FBOShader::FBOShader(string vertex_path,string fragment_path) : BaseShader(vertex_path,fragment_path)
{
    register_uniforms();
}

void FBOShader::register_uniforms()
{
    texture_uniform = glGetUniformLocation(id,"color_texture");
}

void FBOShader::send_texture_uniform(int texture_id) {
    glActiveTexture(GL_TEXTURE0+texture_id);
    glUniform1i(texture_uniform,texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}


