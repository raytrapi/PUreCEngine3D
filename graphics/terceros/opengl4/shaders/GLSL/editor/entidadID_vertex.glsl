#version 420 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in float id;

uniform mat4 view;
uniform mat4 projection;
uniform mat4 model;
//out vec3 fragPos;
out float _id;

void main(){
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    //fragPos=gl_Position;
    _id=id;
}  

