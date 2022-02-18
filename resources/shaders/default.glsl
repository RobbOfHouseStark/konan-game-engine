#shader vertex
#version 330 core

layout(location=0) in vec3 v_position;
layout(location=1) in vec2 v_uv;
layout(location=2) in vec3 v_normal;

uniform mat4 v_MVP;

out vec2 f_uv;
out float f_cosTheta;

void main() {
    gl_Position = v_MVP * vec4(v_position, 1.f);
    f_uv = v_uv;

    f_cosTheta = clamp(dot(v_normal, vec3(.5f, 1.f, .3f)), .2f, 1);
}

#shader fragment
#version 330 core

in vec2 f_uv;
in float f_cosTheta;

layout(location=0) out vec3 color;

uniform sampler2D f_texture;

void main() {
    vec3 materialColor = texture(f_texture, f_uv).rgb;
    color = materialColor * vec3(1.f, 1.f, 1.f) * f_cosTheta;
}
