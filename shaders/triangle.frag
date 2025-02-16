#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform float smileB;
uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main() 
{
    FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture2, vec2(1.0 - TexCoord.x, TexCoord.y)), smileB);
}