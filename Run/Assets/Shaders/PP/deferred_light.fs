#version 330 core
out vec4 gl_Color;

in vec2 outTex;

uniform vec2 screenSize;
uniform vec2 pixelSize;

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

uniform vec3 uCameraPos;
uniform mat4 uViewMatrix;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;
uniform sampler2D gLightInfo;
uniform sampler2D ssaoTex;
uniform sampler2D gDepth;

const float ambiant = 0.1F;

float near = 0.1; 
float far  = 1000.0; 
  
float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{
	float depth = texture(gDepth, outTex).r;
	if(depth >= 1.0)
	{
		discard;
	}
	
    vec4 albedo = texture(gAlbedo, outTex);
	vec3 lightInfo = texture(gLightInfo, outTex).rgb;
	vec3 fragPos = texture(gPosition, outTex).rgb;
    vec3 normal = texture(gNormal, outTex).rgb;
	float ambiantOcclusion = texture(ssaoTex, outTex).r;

	/// Directional lights
	vec3 finalColor = vec3(0.0, 0.0, 0.0);

	for(int i = 0; i < uDirLightAmount; i++)
	{
		// Diffuse
		vec3 toLight = normalize(-uDirLights[i].direction);
		float diff = max(dot(normal, toLight), 0.0);
		vec3 diffuse = albedo.rgb * diff * uDirLights[i].color;
		vec3 ambiant = albedo.rgb * uDirLights[i].color * uDirLights[i].minAmbiant * (1.0 - diff) * ambiantOcclusion; 

		// Specular
		vec3 unitToCamera = normalize(uCameraPos - fragPos);
		vec3 reflectDir = reflect(-toLight, normal);
	
		float specAmount = pow(max(dot(unitToCamera, reflectDir), 0.0), lightInfo.r * 255.0);
		vec3 specular = lightInfo.g * specAmount * uDirLights[i].color;
		
		finalColor += ambiant + diffuse + specular;
	}

	gl_Color = vec4(finalColor, 1.0);
} 