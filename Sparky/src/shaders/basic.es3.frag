precision highp float;

uniform highp vec4 colour;
uniform highp vec2 light_pos;

verying highp vec4 vs_position;
verying highp vec2 vs_uv;
verying highp float vs_tid;
verying highp vec4 vs_color;

uniform sampler2D textures_0;
uniform sampler2D textures_1;
uniform sampler2D textures_2;
uniform sampler2D textures_3;
uniform sampler2D textures_4;
uniform sampler2D textures_5;
uniform sampler2D textures_6;
uniform sampler2D textures_7;

void main()
{
    float intensity = 1.0 / length(vs_position.xy - light_pos);
    vec4 texColor = vs_color;
    if(fs_in.tid > 0.0)
    {
        int tid = int(fs_in.tid - 0.5);
        if (tid == 0)
            texColor = vs_color * texture(textures_0, vs_uv);
        else if (tid == 1)
            texColor = vs_color * texture(textures_1, vs_uv);
        else if (tid == 2)
            texColor = vs_color * texture(textures_2, vs_uv);
        else if (tid == 3)
            texColor = vs_color * texture(textures_3, vs_uv);
        else if (tid == 4)
            texColor = vs_color * texture(textures_4, vs_uv);
        else if (tid == 5)
            texColor = vs_color * texture(textures_5, vs_uv);
        else if (tid == 6)
            texColor = vs_color * texture(textures_6, vs_uv);
        else if (tid == 7)
            texColor = vs_color * texture(textures_7, vs_uv);
    }
    color = texColor * intensity;
}