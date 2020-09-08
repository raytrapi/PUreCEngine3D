#version 400 
layout(location = 0) in vec3 _posicion;
layout(location = 1) in vec2 _coordenadaTextura;

out vec2 coordenadaTextura;

void main() {
   gl_Position = vec4(_posicion, 1.0);
   coordenadaTextura = vec2(_coordenadaTextura.x, _coordenadaTextura.y);   
}