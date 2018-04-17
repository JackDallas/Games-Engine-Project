#version 440
layout(location = 0) in vec3 in_VertPos; 

out vec3 fragmentColour;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(void) {  
	gl_Position = Projection * View *  Model* vec4(in_VertPos, 1); 

	fragmentColour = in_VertPos;
}