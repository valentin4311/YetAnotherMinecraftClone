/*
 * MathUtil.cpp
 *
 *  Created on: 7 sept. 2017
 *      Author: Valentin
 */

#include <math/MathUtil.h>

#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>

#include <core/world/AirChunk.h>

glm::vec3 MathUtil::lerpVec3(const glm::vec3& start, const glm::vec3& end, float amount)
{
	return (end - start) * amount + start;
}

glm::vec3 MathUtil::getForwardVector(const glm::vec3& direction)
{
	glm::vec3 forward;

	forward.x = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y + 270));
	forward.y = sin(glm::radians(direction.x));
	forward.z = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y + 270));

	return forward;
}


glm::vec3 MathUtil::getFlatForwardVector(const glm::vec3& direction)
{
	glm::vec3 forward;

	forward.x = cos(glm::radians(direction.y + 270));
	forward.z = sin(glm::radians(direction.y + 270));

	return forward;
}

glm::vec3 MathUtil::getFlatStrafingVector(const glm::vec3& direction)
{
	glm::vec3 strafe;

	strafe.x = cos(glm::radians(direction.y));
	strafe.z = sin(glm::radians(direction.y));

	return strafe;
}

float MathUtil::lessDecimal(float value, float decimal)
{
	float power = decimal * 10;
	return round(value * power) / power;
}

int MathUtil::getChunkTilePosFromWorld(int pos)
{
	if (pos >= 0)
	{
		return pos % CHUNK_SIZE;
	}
	else
	{
		int i = pos % CHUNK_SIZE;
		return i != 0 ? i + CHUNK_SIZE : 0;
	}
}