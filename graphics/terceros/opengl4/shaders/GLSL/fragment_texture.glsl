#version 400
in vec3 normal;
in vec3 fragPos;
in vec3 color;
in vec2 coordenadas_textura;


out vec4 frag_colour;
uniform sampler2D textura;

void main() {

   vec3 lightPos = vec3(0.0, 1.0, 0.0);
   vec3 lightColor = vec3(1.0, 1.0, 1.0);
   vec3 norm = normalize(normal);
   vec3 lightDir = normalize(lightPos - fragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;


   float ambientStrength = 0.8;
   vec3 ambient = ambientStrength * lightColor;
   vec3 micolor = texture(textura, coordenadas_textura).rgb*color;
   /*if (coordenadas_textura) {
      micolor = vec3(0.0, 0, 1.0);// texture(textura, coordenadas_textura);
   }/***/
   vec3 result = (ambient + diffuse) * micolor;//vec3(0.0, 1.0, 0.0);
   //vec3 result = (ambient)*normal;//vec3(0.0, 1.0, 0.0);
   frag_colour = vec4(result, 1.0);
   //frag_colour = vec4(0.0, 1.0, 0.0, 1.0);

   
}
