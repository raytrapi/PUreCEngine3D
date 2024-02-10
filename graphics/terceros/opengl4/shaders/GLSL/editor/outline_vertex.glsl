#version 420 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float outlining;

void main(){
    gl_Position = projection * view * model * vec4(aPos+normal*outlining, 1.0f);
}

