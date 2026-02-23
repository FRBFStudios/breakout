#version 410 core
layout(location = 0) in vec4 vertex;

out vec2 textureCoords;
out vec4 particleColor;

uniform mat4 projectionMatrix;
uniform vec2 offset;
uniform vec4 color;

void main() {
    float scale = 10.0f;
    textureCoords = vertex.zw;
    particleColor = color;
    gl_Position = projectionMatrix * vec4((vertex.xy * scale) + offset, 0.0, 1.0);
}
