#version 330

layout(location = 0) in vec3 inVertexPosition;
layout(location = 1) in vec2 inTextureCoord;

out vec2 passTextureCoord;

uniform mat4 projMatrix;
uniform mat4 modelViewMatrix;

void main()
{
    gl_Position = projMatrix * modelViewMatrix * vec4(inVertexPosition, 1.0);

    passTextureCoord = inTextureCoord;
}
