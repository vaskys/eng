#ifndef SKYBOX_SHADER_H
#define SKYBOX_SHADER_H

#include "config.h"
#include "shader.h"

class SkyboxShader : BaseShader {
public:
    SkyboxShader(string vertex_path,string fragment_path);
    ~SkyboxShader();

    void register_uniforms();

    void send_projection_uniform(glm::mat4 projection);
    void send_view_uniform(glm::mat4 view_i);
    void send_skybox_texture(unsigned int texture_id);

    void use();

private:
    unsigned int projection_uniform;
    unsigned int view_uniform;
    unsigned int skybox_texture;
};

#endif
