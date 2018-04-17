#version 440
layout(location = 0) in vec3 in_VertPos;
layout(location = 1) in vec3 in_NormalPos;
layout(location = 2) in vec2 in_UVPos;

out vec3 in_vertWorldPos;
out vec3 in_vertViewPos;
out vec3 in_lightViewPos;
out vec3 in_vertNormViewPos;
out vec2 in_UV;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 LightPosition;

void main(void) {
	//Work out the position in screen space
	gl_Position = Projection * View * Model * vec4(1,in_VertPos);

	//position of our light in world space
	/*in_vertWorldPos = (Model * in_VertPos).xyz;

	//vector from the camera to the vert in view space (eye space)
	in_vertViewPos = (View * Model * in_VertPos).xyz;
	
	//vec from the light to the vert in view space
	in_lightViewPos = (View * vec4(LightPosition,1)).xyz;

	// vert normal in view space
	in_vertNormViewPos = mat3(View * Model) * in_NormalPos;*/

	in_UV = in_UVPos;
}