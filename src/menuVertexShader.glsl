#version 330 core
layout (location = 0) in vec2 Pos;

uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * model * vec4(Pos, 0.0f, 1.0f);
}