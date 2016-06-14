
#include "VectorHelper.h"
#include <glm/gtc/constants.hpp>
#include <sstream>

namespace Library
{
const glm::vec2 Vector2Helper::sZero = glm::zero<glm::vec2>();
const glm::vec2 Vector2Helper::sOne = glm::one<glm::vec2>();

std::string Vector2Helper::ToString(const glm::vec2& aVector)
{
	std::stringstream stream;
	stream << "{" << aVector.x << ", " << aVector.y << "}";
	return stream.str();
}

const glm::vec3 Vector3Helper::sZero = glm::zero<glm::vec3>();
const glm::vec3 Vector3Helper::sOne = glm::one<glm::vec3>();
const glm::vec3 Vector3Helper::sForward = { 0.0f, 0.0f, -1.0f };
const glm::vec3 Vector3Helper::sBackward = { 0.0f, 0.0f, 1.0f };
const glm::vec3 Vector3Helper::sUp = { 0.0f, 1.0f, 0.0f };
const glm::vec3 Vector3Helper::sDown = { 0.0f, -1.0f, 0.0f };
const glm::vec3 Vector3Helper::sRight = { 1.0f, 0.0f, 0.0f };
const glm::vec3 Vector3Helper::sLeft = { -1.0f, 0.0f, 0.0f };

std::string Vector3Helper::ToString(const glm::vec3& aVector)
{
	std::stringstream stream;
	stream << "{" << aVector.x << ", " << aVector.y << ", " << aVector.z << "}";
	return stream.str();
}

const glm::vec4 Vector4Helper::sZero = glm::zero<glm::vec4>();
const glm::vec4 Vector4Helper::sOne = glm::one<glm::vec4>();

std::string Vector4Helper::ToString(const glm::vec4& aVector)
{
	std::stringstream stream;
	stream << "{" << aVector.x << ", " << aVector.y << ", " << aVector.z << ", " << aVector.w << "}";
	return stream.str();
}

}
