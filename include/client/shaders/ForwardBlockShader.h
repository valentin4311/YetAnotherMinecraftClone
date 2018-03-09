#ifndef CLIENT_SHADERS_FORWARDBLOCKSHADER_H_
#define CLIENT_SHADERS_FORWARDBLOCKSHADER_H_

#include <client/shaders/Shader.h>
#include <client/render/light/LightCache.h>
#include <client/render/light/DirectionalLightLocationArray.h>
#include <string>

class ForwardBlockShader : public Shader
{
private:
	int uniformModelLocation;
	int uniformViewProjLocation;
	int uniformNormalLocation;
	int uniformAtlasCellSizeLocation;
	int uniformAlbedoTexture;
	int uniformSpecularTexture;
	DirectionalLightLocationArray dirLightLocationArray;
	int uniformCameraPosLocation;

	float cellW;
	float cellH;

public:
	ForwardBlockShader(std::string name) : Shader(name), uniformModelLocation(0), uniformViewProjLocation(0), uniformNormalLocation(0), uniformAtlasCellSizeLocation(0), uniformAlbedoTexture(0), uniformSpecularTexture(0), dirLightLocationArray(this, MAX_DIR_LIGHT), uniformCameraPosLocation(0), cellW(1.0F), cellH(1.0F) {}

	virtual void use() override;
	virtual void stop() override;
	void setAtlasCellSize(float cellW, float cellH);
	virtual void onDraw(glm::mat4& modelMatrix, glm::mat3& normalMatrix) override;

private:
	virtual void bindAttributesAndUniforms() override;
};

#endif
