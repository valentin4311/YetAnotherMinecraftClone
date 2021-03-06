#version 330 core
in vec3 aPos;
in vec3 aColor;
in vec3 aNormal;
in vec2 aAtlasPos;

out vec3 outFragPos;
out vec3 outFragPosView;
out vec3 outColor;
out vec3 outNormal;
out vec3 outRawNormal;
out vec2 outAtlasPos;

uniform mat4 uModel;
uniform mat4 uViewMat;
uniform mat4 uViewProj;

void main()
{
	// Set vertex pos
	vec4 worldPosition = uModel * vec4(aPos, 1.0);
	outFragPos = worldPosition.xyz;
	outFragPosView = (uViewMat * worldPosition).xyz;
	gl_Position = uViewProj * worldPosition;

	outNormal = normalize(mat3(uViewMat * uModel) * normalize(aNormal));
	outRawNormal = aNormal;
    outColor = aColor;
	outAtlasPos = aAtlasPos;
}