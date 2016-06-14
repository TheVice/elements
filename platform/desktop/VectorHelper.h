#ifndef _VECTOR_HELPER_H_
#define _VECTOR_HELPER_H_

#include <glm/glm.hpp>
#include <string>

namespace Library
{
class Vector2Helper
{
public:
	static const glm::vec2 sZero;
	static const glm::vec2 sOne;

	static std::string ToString(const glm::vec2& aVector);

public:
	Vector2Helper() = delete;
	Vector2Helper(const Vector2Helper& aRhs) = delete;
	Vector2Helper& operator = (const Vector2Helper& aRhs) = delete;
};

class Vector3Helper
{
public:
	static const glm::vec3 sZero;
	static const glm::vec3 sOne;
	static const glm::vec3 sForward;
	static const glm::vec3 sBackward;
	static const glm::vec3 sUp;
	static const glm::vec3 sDown;
	static const glm::vec3 sRight;
	static const glm::vec3 sLeft;

	static std::string ToString(const glm::vec3& aVector);

public:
	Vector3Helper() = delete;
	Vector3Helper(const Vector3Helper& aRhs) = delete;
	Vector3Helper& operator = (const Vector3Helper& aRhs) = delete;
};

class Vector4Helper
{
public:
	static const glm::vec4 sZero;
	static const glm::vec4 sOne;

	static std::string ToString(const glm::vec4& aVector);

public:
	Vector4Helper() = delete;
	Vector4Helper(const Vector4Helper& aRhs) = delete;
	Vector4Helper& operator = (const Vector4Helper& aRhs) = delete;
};
}

#endif
