#version 440
layout(location = 0) in vec4 in_VertPos; 


void main(void) {  
	gl_Position = Projection * View *  Model * in_VertPos; 
}