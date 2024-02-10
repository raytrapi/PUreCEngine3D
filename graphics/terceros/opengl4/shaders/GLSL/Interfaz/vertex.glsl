#version 420
layout(location = 0) in vec3 _posicion;
layout(location = 1) in vec2 _textura;

uniform mat4 model;




//out vec2 coordenadaTextura;
out vec2 coordenadas_textura;

void main() {
   vec4 model_position = model * vec4(_posicion, 1.0);
   //gl_Position = model_position;
   gl_Position =  vec4(_posicion, 1.0);
   coordenadas_textura = _textura;
}
