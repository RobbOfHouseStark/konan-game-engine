#shader vertex
#version 330 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec2 a_uv;
layout(location=2) in vec3 a_normal;

uniform mat4 v_MVP;

out vec2 f_uv;

void main() {
    gl_Position = v_MVP * vec4(a_position, 1.0);
    f_uv = a_uv;
}

    #shader fragment
    #version 330 core

in vec2 f_uv;

layout(location=0) out vec4 o_color;

uniform sampler2D u_texture;

void main() {
    o_color = vec4(texture(u_texture, f_uv).rgb, 1.0);
}