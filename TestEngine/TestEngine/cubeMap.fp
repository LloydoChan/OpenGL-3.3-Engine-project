#version 330
varying vec3 ray;

uniform samplerCube CubeMapTex;

out vec4 FragColor;

void main()
{
  FragColor = texture(CubeMapTex,ray);
}