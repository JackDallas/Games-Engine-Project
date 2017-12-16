#version 440
layout(location = 0) in vec3 in_VertPos; 
//layout(location = 1) in vec2 in_TexPos;
layout(location = 2) in vec2 in_UVPos;

out vec2 UV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(void) {
	gl_Position = Projection * Model * View * vec4(in_VertPos, 1); 

	UV = in_UVPos;
}