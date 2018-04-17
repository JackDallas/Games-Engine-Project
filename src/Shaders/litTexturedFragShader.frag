#version 440
// Interpolated values from the vertex shaders
in vec2 UV;//textcoord
in vec3 vertWorldPos;
in vec3 vertViewPos;
in vec3 lightViewPos;
in vec3 vertNormViewPos;

//uniforms with defaults
uniform vec3 LightColour = {0.8,0.8,0.8};
uniform vec3 EmissiveColour = {0,0,0};
uniform vec3 DiffuseColour = {1.0f,1.0f,1.0f};
uniform vec3 SpecularColour = {1.0f,1.0f,1.0f};
uniform float Shininess = 50.0f;
uniform float Alpha = 1.0f;

uniform	float LightPower = 1.5f;

// Ouput data
out vec4 colour;

// Values that stay constant for the whole mesh.
uniform sampler2D Tex;

void main(){

	vec3 lightDirection = normalize(lightViewPos - vertViewPos);

	vec3 normal = normalize(vertNormViewPos);

	vec3 eyeToPointDir = normalize(-vertViewPos);

	vec3 halfEyeLightPoint = normalize(eyeToPointDir - lightDirection);
    
	vec3 textureColour = texture(Tex,UV).rgb;
	vec3 ambientColour  = vec3(0.1f,0.1f,0.2f) * textureColour;
	
	vec3 diffuse = DiffuseColour * LightColour * max(dot(normal,lightDirection), 0);

	colour = LightPower * vec4(EmissiveColour + textureColour * (ambientColour + diffuse + SpecularColour),Alpha);
}