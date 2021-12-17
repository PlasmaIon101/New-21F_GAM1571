#pragma once

const std::vector<fw::VertexFormat> g_SpriteVerts =
{
    { vec2(-0.5f, 0.5f),    0,  0,255,255,  vec2(0.0f,1.0f) }, // top left
    { vec2(-0.5f,-0.5f),    0,255,  0,255,  vec2(0.0f,0.0f) }, // bottom left
    { vec2( 0.5f, 0.5f),    0,255,  0,255,  vec2(1.0f,1.0f) }, // top right
    { vec2( 0.5f,-0.5f),  255,  0,  0,255,  vec2(1.0f,0.0f) }, // bottom right
};
