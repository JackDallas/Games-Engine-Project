#version 440
layout(location = 0) in vec4 in_VertPos; 
layout(location = 1) in vec3 in_NormalPos;
layout(location = 2) in vec2 in_UVPos;

out vec3 vertWorldPos;
out vec3 vertViewPos;
out vec3 lightViewPos;
out vec3 vertNormViewPos;
out vec2 UV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform vec3 LightPosition;

void main(void) {  
	gl_Position = Projection * View *  Model * in_VertPos; 

	vertWorldPos = (Model * in_VertPos).xyz;

	//vector from the camera to the vert in view space (eye space)
	vertViewPos = (View * Model * in_VertPos).xyz;
	
	//vec from the light to the vert in view space
	lightViewPos = (View * vec4(LightPosition,1)).xyz;

	// vert normal in view space
	vertNormViewPos = mat3(View * Model) * in_NormalPos;

	UV = in_UVPos;
}