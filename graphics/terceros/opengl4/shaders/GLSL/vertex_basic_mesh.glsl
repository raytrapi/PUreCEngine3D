#version 420
layout(location = 0) in vec3 _posicion;
layout(location = 1) in vec3 _normal;
layout(location = 2) in vec4 _color;
layout(location = 3) in vec2 _textura;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;




//out vec2 coordenadaTextura;
out vec3 normal;
out vec3 fragPos;
out vec4 color;
out vec2 coordenadas_textura;

void main() {
   vec4 model_position = model * vec4(_posicion, 1.0);
   fragPos = vec3(model_position);
   mat4 matrizTransformada=projection * view ;
   gl_Position = matrizTransformada  * model_position;
   mat3 normalMatriz=transpose(inverse(mat3(model)));
   normal = normalize(normalMatriz*_normal);//vec3(model * vec4(_normal, 1.0));
   //normal = normalMatriz*_normal;//vec3(model * vec4(_normal, 1.0));
   color = _color;
   coordenadas_textura = _textura;
   
}

/*#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec4 Color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Color = aColor;
    TexCoord = aTexCoord;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}*/