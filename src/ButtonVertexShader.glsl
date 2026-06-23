#version 330 core
layout (location = 0) in vec3 Pos;

uniform mat4 projection;
uniform mat4 model;

void main() {
    gl_Position = projection * model * vec4(Pos, 1.0);
}