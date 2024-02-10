#version 420
in vec3 normal;
in vec3 fragPos;

in vec4 color;
in vec2 coordenadas_textura;


struct Light {
    vec3 position;              // Posición de la luz en el espacio
    vec3 color;                 // Color de la luz
    float constantAttenuation;  // Atenuación constante de la luz
    float linearAttenuation;    // Atenuación lineal de la luz
    float quadraticAttenuation; // Atenuación cuadrática de la luz

    // Para sombras:
    int castsShadows;           // Indica si la luz emite sombras
    mat4 shadowMatrix;          // Matriz de proyección para sombras
    //sampler2D shadowMap;        // Textura de mapa de sombras
};

layout (std140, binding = 1) uniform LightBlock {
    Light lights[10];
};
uniform int ligths_numbers=0;

out vec4 frag_colour;
uniform int con_textura = 0;
uniform int con_luces = 1;
uniform int shininess=32;
uniform vec3 viewPos=vec3(0.0,0.0,0);


uniform vec3 colorLuzAmbiente;
uniform float intensidadLuz;

/*uniform vec3 posicionLuz;
uniform vec3 colorLuz;
uniform float watiosLuz;/**/

//uniform sampler2D textura;
uniform sampler2D shadowMap;//[60];


float ShadowCalculation(vec4 fragPosLightSpace, Light light){
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    //vec3 _normal = normalize(normal);
    vec3 lightDir = normalize(light.position - fragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}  


void main() {
   vec3 totalDiffuse = vec3(0.0);
   vec3 totalSpecular=vec3(0.0);
   float specularStrength = 1.0; //Luz especular
   


   for (int i = 0; i < ligths_numbers; i++) {
        // Calcula la dirección y distancia de la luz
        vec3 lightDirection = normalize(lights[i].position - fragPos);
        float lightDistance = length(lights[i].position - fragPos);

        // Calcula el factor de atenuación de la luz
        float attenuation = 1.0 / (lights[i].constantAttenuation +
                                   lights[i].linearAttenuation * lightDistance +
                                   lights[i].quadraticAttenuation * lightDistance * lightDistance);

        // Calcula la intensidad de la luz
        vec3 diffuse = lights[i].color * max(dot(normal, lightDirection), 0.0);


        vec3 viewDir = normalize(viewPos - fragPos);
        vec3 reflectDir = reflect(-lights[i].position, normal); 
        vec3 specular = lights[i].color * pow(max(dot(reflectDir, viewDir), 0.0), shininess);

        // Aplica el factor de atenuación a la intensidad de la luz
        //diffuse *= attenuation;
        //specular *= attenuation;

        totalDiffuse += diffuse;
        //totalSpecular += specular;
    }



   /*//if (con_luces==1) {
      //vec3 norm = normalize(normal);
      vec3 lightDir = normalize(posicionLuz - fragPos);
      float diff = max(dot(normal, lightDir), 0.0);
      
	  float distance = length(posicionLuz - fragPos);
	  //float attenuation = 1.0 / (u_lightAttenuation.x + u_lightAttenuation.y * distance + u_lightAttenuation.z * distance * distance);
	  vec3 colorDistancia=colorLuz*max(0.0,1.0-(distance/watiosLuz));
	  diffuse = diff * colorDistancia;
	  // Luz hacia camara
	  vec3 viewDir = normalize(viewPos - fragPos);
      vec3 reflectDir = reflect(-posicionLuz, normal); 
	  float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
      specular = specularStrength * spec* colorDistancia; 
	  //specular=vec3(0,0,0);
   //} /**/
   
   

   vec3 ambient = intensidadLuz * colorLuzAmbiente;
   vec4 micolor = color;
   
   if (con_textura == 1) {
      //micolor *= texture(textura, coordenadas_textura);

   }/*else{
    micolor=vec4(1.0, 1.0, 1.0, 1.0);
   }/**/
   if (micolor.a < 0.001) {
      discard;
   }/**/
   /*if (coordenadas_textura) {
      micolor = vec3(0.0, 0, 1.0);// texture(textura, coordenadas_textura);
   }/***/

   //float shadow=0;
   //float shadow = ShadowCalculation(lights[0].shadowMatrix* vec4(fragPos, 1.0));
   float shadow = ShadowCalculation( lights[0].shadowMatrix* vec4(fragPos, 1.0), lights[0]);



   vec4 result = vec4((ambient + (1.0-shadow)*(totalDiffuse + totalSpecular)),1.0) * micolor;//vec3(0.0, 1.0, 0.0);
   //vec3 result = (ambient)*normal;//vec3(0.0, 1.0, 0.0);
   //result=vec4(ambient,1.0)+micolor*vec4(diffuse,1.0);
   //result=vec4((ambient+specular+diffuse)*micolor.xyz,1.0);
   //result=vec4((ambient*micolor.xyz)+ specular*micolor.xyz +diffuse*micolor.xyz , micolor.w);
   frag_colour = result;
   //frag_colour = vec4(0.0, 1.0, 0.0, 1.0);
//frag_colour=vec4(shadow, 0,0,1.0);

}
