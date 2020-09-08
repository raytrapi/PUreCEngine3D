#version 400
out vec4 color;

in vec2 coordenadaTextura;

uniform sampler2D textura;

void main() {
   color = texture(textura, coordenadaTextura);
}