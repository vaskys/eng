#include "skybox.h"
#include "SDL_opengl.h"
#include "SDL_surface.h"
#include "config.h"
#include "skybox_shader.h"
#include <string>
#include "stb_image.h"


/*
0 - right
1- left
2 - top
3 - bottom
4- front
5 - back
*/

float skyboxVertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
    1.0f,  1.0f, -1.0f,
    1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f, -1.0f,
    1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
    1.0f, -1.0f,  1.0f
};


Skybox::Skybox() {
    skybox_shader = new SkyboxShader("shaders/skybox_vertex.glsl","shaders/skybox_fragment.glsl");

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

}


Skybox::~Skybox() {
    debug_print("skybox dest");

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
    glDeleteTextures(1, &cubemap_id);

    delete skybox_shader;


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1,&VBO);
}

bool Skybox::load_cubemap(string path, string format) {
    clear();

    glGenTextures(1, &cubemap_id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    int width, height, nrChannels;
    for(int i=0; i < 6; i++) {
        string comp_path = path + "/" + to_string(i) + format;
        debug_print(comp_path);

        unsigned char *data = stbi_load(comp_path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            debug_print("ERROR SKYBOX ");
            stbi_image_free(data);
        }

    }


    return true;
}

unsigned int Skybox::get_id() {
        return cubemap_id;
}

void Skybox::clear() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);
    glDeleteTextures(1, &cubemap_id);
}


SkyboxShader* Skybox::get_shader() {
    return skybox_shader;
}


unsigned int Skybox::get_VAO() {
    return VAO;
}

unsigned int Skybox::get_VBO() {
    return VBO;
}

