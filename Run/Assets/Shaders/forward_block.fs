#version 330 core

out vec4 gl_Color;

in vec3 outFragPos;
in vec3 outColor;
in vec3 outNormal;
in vec3 outRawNormal;
in vec2 outAtlasPos;

in vec3 toCamera;

// Directional Lights
struct DirLight
{
    vec3 direction;
    vec3 color;
	float minAmbiant;
};

#define NB_DIR_LIGHTS 4
uniform DirLight uDirLights[NB_DIR_LIGHTS];
uniform int uDirLightAmount;

uniform sampler2D albedoMap;
uniform sampler2D specularMap;
uniform vec2 uAtlasCellSize;

vec2 getCoordinateFromNormal()
{
	if(outRawNormal.y != 0)
	{
		return vec2(outFragPos.x, outFragPos.z);
	}
	else if(outRawNormal.x != 0)
	{
		return vec2(outFragPos.z, outFragPos.y);
	}
	else
	{
		return vec2(outFragPos.x, outFragPos.y);
	}
}

void main()
{
	// Get texture coords
	vec2 coords = getCoordinateFromNormal();
	float uPos = coords.x - floor(coords.x);
	float vPos = coords.y - floor(coords.y);
	vec2 texCoords = vec2(uPos * uAtlasCellSize.x + outAtlasPos.x, vPos * uAtlasCellSize.y + outAtlasPos.y);
	vec4 texColor = texture(albedoMap, texCoords);

	/// Lightning
	vec3 finalColor = vec3(0.0, 0.0, 0.0);

	vec3 specularTex = texture(specularMap, texCoords).rgb;

	for(int i = 0; i < uDirLightAmount; i++)
	{
		// Diffuse
		float diff = max(dot(outNormal, uDirLights[i].direction), 0.0);
		vec3 diffuse = texColor.rgb * diff * uDirLights[i].color;
		vec3 ambiant = texColor.rgb * uDirLights[i].color * uDirLights[i].minAmbiant * (1.0 - diff); 

		// Specular
		vec3 unitToCamera = normalize(toCamera);
		vec3 reflectDir = reflect(-uDirLights[i].direction, outNormal);
	
		float specAmount = pow(max(dot(unitToCamera, reflectDir), 0.0), specularTex.r * 255.0);
		vec3 specular = specularTex.g * specAmount * uDirLights[i].color;
		
		finalColor += ambiant + diffuse + specular;
	}
	
    gl_Color = vec4(finalColor, texColor.a);
} 
