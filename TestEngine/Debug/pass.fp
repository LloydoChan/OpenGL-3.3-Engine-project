#version 330

in vec3 fragColor;
in vec2 textureCoords;

out vec4 col;

uniform sampler2D texturePic;

void main()
{
  vec3 texCol = texture(texturePic,textureCoords).xyz;
  //vec3 texCol = vec3(0.8f,0.8f,0.4f);
  vec3 mixCol = mix(fragColor,texCol,1.0f);
  col = vec4(texCol,1.0f);
}
