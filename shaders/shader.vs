#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec3 outPos;
out vec2 TexCoord;

uniform float xOffset = 0;

void main()
{

   gl_Position = vec4((-aPos)+xOffset, 1.0);
   ourColor = aColor;
   TexCoord = aTexCoord;
   //outPos=(-aPos)+xOffset+0.5;
}
