#version 440 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 offset;

uniform vec2 _offset;

void main()
{
	gl_Position = vec4(position + _offset, 0.0, 1.0);
}