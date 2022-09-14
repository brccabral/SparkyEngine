#version 330 core

layout (location = 0) out vec4 color;
uniform vec3 block_color = vec3(1.0f, 1.0f, 1.0f);

uniform vec3 player_pos;
uniform float light_on;
uniform float selected;
uniform sampler2D tex_id;

vec3 light = vec3(2.0f, 48.0f, 2.0f);

in DATA
{
    vec3 position;
    vec3 normal;
    vec2 tc;
} fs_in;

void main()
{
    vec3 to_light = player_pos - fs_in.position;
    float intensity = dot(normalize(to_light), normalize(fs_in.normal));
    intensity = min(10.0f / length(to_light) * max(intensity, 0.0f), 2.0f);
    vec3 col = vec3(texture(tex_id, fs_in.tc));
    if (light_on == 1.0f) col *= intensity;
    color = vec4(col + 0.05f, 1.0f);
    if (selected == 1.0f) color += 0.3f;
}