#include <client/render/light/DirectionalLight.h>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

DirectionalLight::DirectionalLight(Color color, float ambiantAmount, glm::vec3 direction) : Light(color, ambiantAmount), lightDirection(direction)
{
}

void DirectionalLight::setLightDirection(glm::vec3 direction)
{
	lightDirection = glm::normalize(direction);
	dirty = true;
}
