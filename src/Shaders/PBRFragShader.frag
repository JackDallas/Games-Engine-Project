#version 440
// Interpolated values from the vertex shaders

in vec2 in_UV;//textcoord
in vec3 in_vertWorldPos;
in vec3 in_vertViewPos;
in vec3 in_lightViewPos;
in vec3 in_vertNormViewPos;

//uniforms with defaults
uniform vec3 in_LightColour = {0.8,0.8,0.8};
uniform vec3 in_EmissiveColour = {0,0,0};
uniform vec3 in_DiffuseColour = {1.0f,1.0f,1.0f};
uniform vec3 in_SpecularColour = {1.0f,1.0f,1.0f};
uniform float in_Shininess = 50.0f;
uniform float in_Alpha = 1.0f;

uniform	float in_LightPower = 1.5f;

// Ouput data
out vec4 out_colour;

// Values that stay constant for the whole mesh.
uniform sampler2D in_Tex;
uniform sampler2D in_Roughness;

//uniform sampler2D in_albedoTex;
//uniform sampler2D in_normalTex;
//uniform sampler2D in_aoTex;
//uniform sampler2D in_metallicTex;
//uniform sampler2D in_emissiveTex;

#define PI 3.14159265359

//http://graphicrants.blogspot.co.uk/2013/08/specular-brdf-reference.html

float FresnelReflectance(float LightDotHalf, vec3 specColour) {
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

void main() {
	//Let's do our querying first
	vec3 textureColour = texture(in_Tex,in_UV).rgb;

//#if Normal_Map
//normal = //texture query
//#endif
//#if Roughness_Map
    vec3 roughnessPoint = texture2D(in_Roughness, in_UV).rgb;
    float roughness = roughnessPoint.r;
//#endif

	vec3 normal = normalize(in_vertNormViewPos);//normal
	vec3 lightDirection = normalize(in_lightViewPos - in_vertViewPos);//light direction
	vec3 viewDirection = normalize(-in_vertViewPos);
	vec3 halfDirection = normalize(viewDirection + lightDirection);

	float NormalDotHalf = max(0.0f, dot(normal, halfDirection));
	float NormalDotLight = max(0.0f, dot(normal, lightDirection));
	float NormalDotView = max(0.0f, dot(normal, viewDirection));
	float LightDotHalf = max(0.0f, dot(lightDirection, halfDirection));
	float ViewDotHalf = max(0.0f, dot(viewDirection, halfDirection));


	vec3 SpecularDist = in_SpecularColour * NDF(NormalDotHalf,roughness);
	float GeometryShadowing = GeometryFunction(NormalDotHalf, NormalDotView, NormalDotLight, ViewDotHalf);
	vec3 Fresnel = in_SpecularColour * FresnelReflectance(LightDotHalf,in_SpecularColour); 

	vec3 BDRF = (SpecularDist * GeometryShadowing * Fresnel) / (4 * NormalDotLight * NormalDotView);

	vec3 LightModel = (in_DiffuseColour + BDRF);

	LightModel += NormalDotHalf;

	out_colour = vec4(0.0f,0.0f,0.0f,1.0f);

	//out_colour = in_LightPower * vec4(in_EmissiveColour + textureColour * (ambientColour + diffuse + in_SpecularColour),in_Alpha);
}