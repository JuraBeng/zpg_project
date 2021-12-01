#version 330							

layout(location = 0) in vec3 pos;			
layout(location = 1) in vec4 col;
uniform mat4 model;								
uniform mat4 projection;
uniform mat4 view;							

out vec4 vCol;											

void main()												
{														
    gl_Position = ( projection * view * model) * vec4(pos,1.0f);
    vCol = col;
}