#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "GameComponent.h"
#include <glm/glm.hpp>

namespace Library
{
class GameTime;

class Camera : public GameComponent
{
	RTTI_DECLARATIONS(Camera, GameComponent)

public:
	Camera(Game& aGame);
	Camera(Game& aGame, float aFieldOfView, float aAspectRatio, float aNearPlaneDistance,
		   float aFarPlaneDistance);
	virtual ~Camera();

public:
	Camera(const Camera& aRhs) = delete;
	Camera& operator = (const Camera& aRhs) = delete;

public:
	const glm::vec3& GetPosition() const;
	const glm::vec3& GetDirection() const;
	const glm::vec3& GetUp() const;
	const glm::vec3& GetRight() const;

	float GetAspectRatio() const;
	float GetFieldOfView() const;
	float GetNearPlaneDistance() const;
	float GetFarPlaneDistance() const;

	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;
	glm::mat4 GetViewProjectionMatrix() const;

	virtual void SetPosition(float aX, float aY, float aZ);
	virtual void SetPosition(const glm::vec3& aPosition);

	virtual void Reset();
	virtual void Initialize() override;
	virtual void Update(const GameTime& aGameTime) override;
	virtual void UpdateViewMatrix();
	virtual void UpdateProjectionMatrix();
	virtual void ApplyRotation(const glm::mat4& aTransform);

	static const float sDefaultFieldOfView;
	static const float sDefaultNearPlaneDistance;
	static const float sDefaultFarPlaneDistance;

protected:
	float mFieldOfView;
	float mAspectRatio;
	float mNearPlaneDistance;
	float mFarPlaneDistance;

	glm::vec3 mPosition;
	glm::vec3 mDirection;
	glm::vec3 mUp;
	glm::vec3 mRight;

	glm::mat4 mViewMatrix;
	glm::mat4 mProjectionMatrix;
};
}

#endif
