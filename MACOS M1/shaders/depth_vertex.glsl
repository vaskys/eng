#version 330 core
layout (location = 0) in vec3 pos;

uniform mat4 light_space_matrix;
uniform mat4 model;
uniform mat4 view; 

void main()
{
    gl_Position = light_space_matrix  * model * vec4(pos, 1.0);
}  

