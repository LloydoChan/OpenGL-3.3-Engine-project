//texture.fp
#version 330 
 
in vec2 UV;
 
layout(location=0) out vec3 color;
 
uniform sampler2D renderedTexture;
 
void main()
{
    color = texture(renderedTexture,UV).rgb;
}