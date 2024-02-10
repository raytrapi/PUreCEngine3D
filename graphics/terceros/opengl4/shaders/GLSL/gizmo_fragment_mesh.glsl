#version 400


in vec3 fragPos;
in vec2 texCoord;
uniform sampler2D textura;

out vec4 fragColor;
void main(){
	 vec4 color=texture(textura, texCoord);//vec4(1.0f, 0.0f, 0.0f, 1.0f);
	 /*if (color.a < 0.001) {
       discard;
    }/**/
    fragColor = color;
    fragColor=vec4(1.0,1.0,1.0,1.0);
    /*if (texCoord.x > position.x && texCoord.x < position.x + size.x &&
        texCoord.y > position.y && texCoord.y < position.y + size.y) {
        fragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    } else {
        fragColor = vec4(0.0f, 0.0f, 0.0f, 0.0f);
    }
    /*vec2 scaledTexCoord = vec2(scale.x, scale.y);
    vec2 offsetTexCoord = vec2(scaledTexCoord.x + fragPos.x, scaledTexCoord.y + fragPos.y);

    // Calculamos la coordenada de textura de recorte y convertimos el ancho y alto de recorte a valores de 0-1
    vec2 cropTexCoord = vec2(crop.x + scaledTexCoord.x * crop.z, crop.y + scaledTexCoord.y * crop.w) / vec2(textureSize(image, 0));

    // Comprobamos si la coordenada de textura está dentro de la región de recorte
    if (cropTexCoord.x < crop.x || cropTexCoord.x > crop.x + crop.z || cropTexCoord.y < crop.y || cropTexCoord.y > crop.y + crop.w) {
        fragColor = vec4(0, 0, 0, 0); // Si la coordenada está fuera de la región de recorte, establecemos el color a transparente
    } else {
        vec4 texColor = texture(image, cropTexCoord); // Si la coordenada está dentro de la región de recorte, obtenemos el color de la textura normalmente
        fragColor = texColor;
    }*/
}
