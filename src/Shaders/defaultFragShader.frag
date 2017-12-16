#version 440

in vec3 fragmentColour;

out vec4 colour;

vec4 checker3D(vec3 texc, vec4 color0, vec4 color1)
{
	//Round them all and add them
  if ((int(floor(texc.x) + floor(texc.y) + floor(texc.z)) & 1) == 0)
    return color0;
  else
    return color1;
}

void main(void){ 
	colour = checker3D (
		fragmentColour,
		// 	255-20-147
		vec4(1.0f,0.078431f,0.576470f,1.0f),
		// black
		vec4(0.0f,0.0f,0.0f,1.0f));
}
