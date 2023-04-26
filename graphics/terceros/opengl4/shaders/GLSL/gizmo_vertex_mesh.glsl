#version 400

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragPos;
out vec2 texCoord;
void main(){
    
    gl_Position = projection * view * model * vec4(position, 1.0);
	fragPos = vec3(gl_Position);
	texCoord=uv;
}