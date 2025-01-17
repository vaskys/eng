#include "config.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool debugovanie=true;

int global_light_shadow_res = 4096;
int spot_light_shadow_res = 2048;


int get_global_light_shadow_res() {
  return global_light_shadow_res;
}
int get_spot_light_shadow_res() {
  return spot_light_shadow_res;
}

void debug_print(string msg)
{
    if(debugovanie)
        cout<<msg<<endl;
}

void print_wd()
{
    char buff[FILENAME_MAX]; 
    GetCurrentDir( buff, FILENAME_MAX );
    string current_working_dir(buff);
    debug_print(current_working_dir);
}

glm::mat4 AssimpToGLM(const aiMatrix4x4& from)
{
    glm::mat4 to;
    to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
    to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
    to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
    to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
    return to;
}

glm::vec3 AssimpVec3ToGLM(const aiVector3D &vec)
{
    return glm::vec3(vec.x, vec.y, vec.z);
}

glm::quat AssimpQuatToGLM(const aiQuaternion &quat)
{
    return glm::quat(quat.w,quat.x,quat.y,quat.z);
}
