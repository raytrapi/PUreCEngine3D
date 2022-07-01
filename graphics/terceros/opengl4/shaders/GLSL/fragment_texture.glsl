#version 400
in vec3 normal;
in vec3 fragPos;
in vec4 color;
in vec2 coordenadas_textura;


out vec4 frag_colour;
uniform int con_textura = 0;
uniform int con_luces = 0;
uniform float fuerza_luz_ambiente = 1;
uniform vec4 color_luz_ambiente = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D textura;

void main() {
   vec4 diffuse = vec4(0.0,0.0,0.0,0.0);
   
   if (con_luces==1) {
      vec3 lightPos = vec3(0.0, 1.0, 0.0);
      vec4 lightColor = vec4(1.0, 1.0, 1.0, 1.0);
      vec3 norm = normalize(normal);
      vec3 lightDir = normalize(lightPos - fragPos);
      float diff = max(dot(norm, lightDir), 0.0);
      diffuse = diff * lightColor;
   } 

   vec4 ambient = fuerza_luz_ambiente * color_luz_ambiente;
   vec4 micolor = color;
   
   if (con_textura == 1) {
      micolor *= texture(textura, coordenadas_textura);

   }/*else{
    micolor=vec4(1.0, 1.0, 1.0, 1.0);
   }/**/
   if (micolor.a < 0.001) {
      discard;
   }/**/
   /*if (coordenadas_textura) {
      micolor = vec3(0.0, 0, 1.0);// texture(textura, coordenadas_textura);
   }/***/
   vec4 result = (ambient + diffuse) * micolor;//vec3(0.0, 1.0, 0.0);
   //vec3 result = (ambient)*normal;//vec3(0.0, 1.0, 0.0);
   frag_colour = result;
   //frag_colour = vec4(0.0, 1.0, 0.0, 1.0);


}
