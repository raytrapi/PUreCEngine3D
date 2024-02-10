#version 420

in vec2 coordenadas_textura;


uniform sampler2D textura; 

out vec4 frag_colour;

void main() {
    vec4 color=texture(textura, coordenadas_textura);
    if (color.a < 0.001) {
      discard;
    }
    frag_colour = color;
    //return;
    //micolor = texture(albedo_texture, coordenadas_textura);


}
