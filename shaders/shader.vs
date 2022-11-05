#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 ourColor;
out vec3 outPos;

uniform float xOffset = 0;

void main()
{

   gl_Position = vec4((-aPos)+xOffset, 1.0);
   ourColor = aColor;
   outPos=(-aPos)+xOffset+0.5;
}
