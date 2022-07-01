#version 400
in vec3 normal;
in vec3 fragPos;
in vec3 color;

out vec4 frag_colour;

void main() {
   vec3 lightPos = vec3(0.0, 1.0, 0.0);
   vec3 lightColor = vec3(1.0, 1.0, 1.0);
   vec3 norm = normalize(normal);
   vec3 lightDir = normalize(lightPos - fragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;


   float ambientStrength = 0.8;
   vec3 ambient = ambientStrength * lightColor;

   vec3 result = (ambient + diffuse) * color;//vec3(0.0, 1.0, 0.0);
   //vec3 result = (ambient)*normal;//vec3(0.0, 1.0, 0.0);
   frag_colour = vec4(result, 1.0);
   //frag_colour = vec4(0.0, 1.0, 0.0, 1.0);
}
float drawLine(vec2 p1, vec2 p2, vec2 uv, float a) {
   float r = 0.;
   float one_px = 1. / iResolution.x; //not really one px

   // get dist between points
   float d = distance(p1, p2);

   // get dist between current pixel and p1
   float duv = distance(p1, uv);

   //if point is on line, according to dist, it should match current uv 
   r = 1. - floor(1. - (a * one_px) + distance(mix(p1, p2, clamp(duv / d, 0., 1.)), uv));

   return r;
}

float drawCircle(vec2 p, float d, vec2 uv) {
   return (distance(p, uv) <= d) ? 1. : 0.;
}

void mainImage(out vec4 fragColor, in vec2 fragCoord) {
   vec2 uv = fragCoord.xy / iResolution.xy;
   float t = iTime * 1.5; //Pro Tip™: multipluy time to go faster!

   //in uv space
   vec2 p1 = vec2(0.5 + sin(t) * .2, 0.25 + cos(t + pi) * .1);
   vec2 p2 = vec2(0.5 + sin(t + pi) * .2, 0.25 + cos(t) * .1);
   vec2 p3 = vec2(0.5 + sin(t + pi / 2.) * .2, 0.25 + cos(t - .5 * pi) * .1);
   vec2 p4 = vec2(0.5 + sin(t - pi / 2.) * .2, 0.25 + cos(t + .5 * pi) * .1);
   vec2 p5 = vec2(0.5 + sin(t) * .2, 0.75 + cos(t + pi) * .1);
   vec2 p6 = vec2(0.5 + sin(t + pi) * .2, 0.75 + cos(t) * .1);
   vec2 p7 = vec2(0.5 + sin(t + pi / 2.) * .2, 0.75 + cos(t - .5 * pi) * .1);
   vec2 p8 = vec2(0.5 + sin(t - pi / 2.) * .2, 0.75 + cos(t + .5 * pi) * .1);


   float lines = drawLine(p1, p5, uv, 2.)
      + drawLine(p2, p6, uv, 1.)
      + drawLine(p1, p3, uv, 1.)
      + drawLine(p3, p2, uv, 1.)
      + drawLine(p1, p4, uv, 1.)
      + drawLine(p4, p2, uv, 1.)
      + drawLine(p5, p7, uv, 1.)
      + drawLine(p7, p6, uv, 1.)
      + drawLine(p6, p8, uv, 1.)
      + drawLine(p8, p5, uv, 1.)
      + drawLine(p3, p7, uv, 1.)
      + drawLine(p4, p8, uv, 1.);
   float line = drawLine(p1, p5, uv, 2.);

   float d = 0.003;
   float dots = drawCircle(p1, d, uv)
      + drawCircle(p2, d, uv)
      + drawCircle(p3, d, uv)
      + drawCircle(p4, d, uv)
      + drawCircle(p5, d, uv)
      + drawCircle(p6, d, uv)
      + drawCircle(p7, d, uv)
      + drawCircle(p8, d, uv);

   fragColor = vec4(line, line, line, 1.);//vec4(line, dots, dots, 1.);
}