
#version 330 core

layout (location = 0) out vec4 color;

in vec4 v_color;
in vec2 v_textureCoords;
in float v_textureIndex;

uniform sampler2D u_textures[16];

void main()
{
    switch(int(v_textureIndex))
    {
        case 0: color = texture(u_textures[0], v_textureCoords) * v_color; break;
        case 1: color = texture(u_textures[1], v_textureCoords) * v_color; break;
        case 2: color = texture(u_textures[2], v_textureCoords) * v_color; break;
        case 3: color = texture(u_textures[3], v_textureCoords) * v_color; break;
        case 4: color = texture(u_textures[4], v_textureCoords) * v_color; break;
        case 5: color = texture(u_textures[5], v_textureCoords) * v_color; break;
        case 6: color = texture(u_textures[6], v_textureCoords) * v_color; break;
        case 7: color = texture(u_textures[7], v_textureCoords) * v_color; break;
        case 8: color = texture(u_textures[8], v_textureCoords) * v_color; break;
        case 9: color = texture(u_textures[9], v_textureCoords) * v_color; break;
        case 10: color = texture(u_textures[10], v_textureCoords) * v_color; break;
        case 11: color = texture(u_textures[11], v_textureCoords) * v_color; break;
        case 12: color = texture(u_textures[12], v_textureCoords) * v_color; break;
        case 13: color = texture(u_textures[13], v_textureCoords) * v_color; break;
        case 14: color = texture(u_textures[14], v_textureCoords) * v_color; break;
        case 15: color = texture(u_textures[15], v_textureCoords) * v_color; break;
    }
}