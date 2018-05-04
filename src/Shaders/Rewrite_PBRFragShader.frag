#version 440

//Inputs from Frag
in vec2 UV;//textcoord
in vec3 vertWorldPos;
in vec3 vertViewPos;
in vec3 lightViewPos;
in vec3 vertNormViewPos;

//uniforms with defaults
uniform vec3 LightColour = {0.8,0.8,0.8};
uniform vec3 EmissiveColour = {0,0,0};
uniform vec3 DiffuseColour = {1.0f,1.0f,1.0f}; //Kd
//uniform vec3 SpecularColour = {1.0f,1.0f,1.0f};
uniform float Shininess = 50.0f;
uniform float Alpha = 1.0f;

uniform	float LightPower = 1.5f;

uniform sampler2D Tex;
uniform sampler2D Roughness;
uniform sampler2D Spec;

//Output Colour
out vec4 colour;

#define PI 3.14159265359

//http://graphicrants.blogspot.co.uk/2013/08/specular-brdf-reference.html

vec3 FresnelReflectance(float LightDotHalf, vec3 specColour) {
	//Schlick
	return specColour + (1.0f - specColour) * pow(1.0f - LightDotHalf, 5.0f); 
}
//What fraction of the microsurface is visible between l and v
//Cook-Torrance
float GeometryFunction(float NormalDotHalf, float NormalDotView, float NormalDotLight, float ViewDotHalf) {
	return min(1,
		min(((2 * NormalDotHalf * NormalDotView) / ViewDotHalf),
			((2 * NormalDotHalf * NormalDotLight) / ViewDotHalf)));
}

// α = roughness2
//DGGX(m) = α2 / π((n⋅m)2(α2−1)+1)2
float NDF(float NormalDotHalf, float roughness){//GGX Trowbridge-Reitz
	float roughnessSqr = roughness * roughness; 
	return roughnessSqr / (PI * pow((pow(NormalDotHalf,2.0f) * (roughnessSqr - 1.0f) + 1.0f),2.0f));
}


void main(void){ 
	//Let's do our querying first
	vec3 textureColour = texture(Tex,UV).rgb;
	//Query the roughness
    float roughness = texture2D(Roughness, UV).r;
    float reflectance = 0.2; //TODO query I think gloss

	vec3 SpecularColour = texture(Spec,UV).rgb; 

	vec4 AmbientColour  = vec4(vec3(0.1f,0.1f,0.2f) * textureColour,1.0f);


    vec3 normal = normalize(vertNormViewPos);//normal
	vec3 lightDirection = normalize(lightViewPos - vertViewPos);//light direction
	vec3 viewDirection = normalize(-vertViewPos);
	vec3 halfDirection = normalize(viewDirection + lightDirection);


	float NormalDotHalf = max(0.0f, dot(normal, halfDirection));
	float NormalDotLight = max(0.0f, -dot(normal, lightDirection));//BROKE
	float NormalDotView = max(0.0f, dot(normal, viewDirection));
	float LightDotHalf = max(0.0f, dot(lightDirection, halfDirection));
	float ViewDotHalf = max(0.0f, dot(viewDirection, halfDirection));
	
	float SpecularDist = NDF(NormalDotHalf,roughness);
	float GeometryShadowing = GeometryFunction(NormalDotHalf, NormalDotView, NormalDotLight, ViewDotHalf);
	vec3 Fresnel = FresnelReflectance(LightDotHalf,SpecularColour); 

	vec3 BRDF = (SpecularDist * GeometryShadowing * Fresnel) / (4.0f * NormalDotLight * NormalDotView);

	//vec3 diffuse = vec3(reflectance / PI) * NormalDotLight;
	
	colour = vec4((BRDF + textureColour) * LightPower,1);
}