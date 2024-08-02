#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

// variables for update the position of the figure
uniform float xOffset;
uniform float yOffset;

void main()
{
    // update the position
    gl_Position = vec4(aPos.x + xOffset, aPos.y + yOffset, aPos.z, 1.0);
    ourColor = aColor;
}