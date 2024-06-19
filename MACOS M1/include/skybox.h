#ifndef SKYBOX
#define SKYBOX

#include "config.h"
#include "skybox_shader.h"

class Skybox {
public:
    Skybox();
    ~Skybox();

    bool load_cubemap(string path,string format);
    unsigned get_id();

    SkyboxShader* get_shader();

    SkyboxShader *skybox_shader;


    unsigned int get_VAO();
    unsigned int get_VBO();

private:
    unsigned int cubemap_id;

    unsigned int VAO;
    unsigned int VBO;

    void clear();
};

#endif 
