#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;

in DATA
{
    vec4 position;
    vec2 uv;
    float tid;
    vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
    float intensity = 1.0 / length(fs_in.position.xy - light_pos);
    vec4 texColor = fs_in.color;
    if(fs_in.tid > 0.0)
    {
        int tid = int(fs_in.tid - 0.5);
        texColor = fs_in.color * texture(textures[tid], fs_in.uv);
    }
    color = texColor;
    //color = texColor * intensity;
    //color = vec4(1*texColor.r,1*texColor.g,1*texColor.b,1*texColor.a);
    //color = vec4(1,0,1,1);
    //color = vec4(texColor.a,texColor.g,texColor.b,texColor.a);
    //color = vec4(0,0,texColor.a,1);
}