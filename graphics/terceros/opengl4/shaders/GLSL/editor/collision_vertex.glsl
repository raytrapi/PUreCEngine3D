#version 420
layout(location = 0) in vec3 _posicion;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec4 _color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;





out vec3 normal;
out vec3 fragPos;
out vec4 color;

void main() {
   vec4 model_position = model * vec4(_posicion, 1.0);
   fragPos = vec3(model_position);
   mat4 matrizTransformada=projection * view ;
   gl_Position = matrizTransformada*model_position;
   mat3 normalMatriz=transpose(inverse(mat3(model)));
   normal = normalize(normalMatriz*_normal);//vec3(model * vec4(_normal, 1.0));
   color = _color;
}