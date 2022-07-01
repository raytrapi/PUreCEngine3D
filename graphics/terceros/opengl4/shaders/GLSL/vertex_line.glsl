#version 400
layout(location = 0) in vec3 pos;
layout(location = 1) in vec4 _color;
//layout(location = 1) in vec3 _normal;
//layout(location = 3) in vec2 _textura;
uniform mat4 MVP;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//out vec3 normal;
//out vec3 fragPos;
out vec4 color;
//out vec2 coordenadas_textura;


void main() {
	gl_Position = projection * view * (model * vec4(pos.x, pos.y, pos.z, 1.0));
   color = _color;
   //color = vec4(1.0, 1.0, 1.0, 1.0);
}
