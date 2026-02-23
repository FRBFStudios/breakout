#version 410 core

in vec2 textureCoords;
in vec4 particleColor;
out vec4 fragColor;

uniform sampler2D particleTexture;

void main() {
    fragColor = (texture(particleTexture, textureCoords) * particleColor);
}
