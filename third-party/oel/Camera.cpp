
#include "Camera.h"
#include "Game.h"
#include "VectorHelper.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Library
{
RTTI_DEFINITIONS(Camera)

Camera::Camera(Game& aGame)
	: GameComponent(aGame),
	  mFieldOfView(sDefaultFieldOfView),
	  mAspectRatio(aGame.GetAspectRatio()),
	  mNearPlaneDistance(sDefaultNearPlaneDistance),
	  mFarPlaneDistance(sDefaultFarPlaneDistance),
	  mPosition(),
	  mDirection(),
	  mUp(),
	  mRight(),
	  mViewMatrix(),
	  mProjectionMatrix()
{
}

Camera::Camera(Game& aGame, float aFieldOfView, float aAspectRatio, float aNearPlaneDistance,
			   float aFarPlaneDistance)
	: GameComponent(aGame),
	  mFieldOfView(aFieldOfView),
	  mAspectRatio(aAspectRatio),
	  mNearPlaneDistance(aNearPlaneDistance),
	  mFarPlaneDistance(aFarPlaneDistance),
	  mPosition(),
	  mDirection(),
	  mUp(),
	  mRight(),
	  mViewMatrix(),
	  mProjectionMatrix()
{
}

Camera::~Camera()
{
}

const glm::vec3& Camera::GetPosition() const
{
	return mPosition;
}

const glm::vec3& Camera::GetDirection() const
{
	return mDirection;
}

const glm::vec3& Camera::GetUp() const
{
	return mUp;
}

const glm::vec3& Camera::GetRight() const
{
	return mRight;
}

float Camera::GetAspectRatio() const
{
	return mAspectRatio;
}

float Camera::GetFieldOfView() const
{
	return mFieldOfView;
}

float Camera::GetNearPlaneDistance() const
{
	return mNearPlaneDistance;
}

float Camera::GetFarPlaneDistance() const
{
	return mFarPlaneDistance;
}

const glm::mat4& Camera::GetViewMatrix() const
{
	return mViewMatrix;
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
	return mProjectionMatrix;
}

glm::mat4 Camera::GetViewProjectionMatrix() const
{
	return mProjectionMatrix * mViewMatrix;
}

void Camera::SetPosition(float aX, float aY, float aZ)
{
	mPosition = glm::vec3(aX, aY, aZ);
}

void Camera::SetPosition(const glm::vec3& aPosition)
{
	mPosition = aPosition;
}

void Camera::Reset()
{
	mPosition = Vector3Helper::sZero;
	mDirection = Vector3Helper::sForward;
	mUp = Vector3Helper::sUp;
	mRight = Vector3Helper::sRight;
	UpdateViewMatrix();
}

void Camera::Initialize()
{
	UpdateProjectionMatrix();
	Reset();
}

void Camera::Update(const GameTime&)
{
	UpdateViewMatrix();
}

void Camera::UpdateViewMatrix()
{
	glm::vec3 target = mPosition + mDirection;
	mViewMatrix = glm::lookAt(mPosition, target, mUp);
}

void Camera::UpdateProjectionMatrix()
{
	mProjectionMatrix = glm::perspective(mFieldOfView, mAspectRatio, mNearPlaneDistance, mFarPlaneDistance);
}

void Camera::ApplyRotation(const glm::mat4& aTransform)
{
	glm::vec4 direction = aTransform * glm::vec4(mDirection, 0.0f);
	mDirection = static_cast<glm::vec3>(glm::normalize(direction));
	//
	glm::vec4 up = aTransform * glm::vec4(mUp, 0.0f);
	mUp = static_cast<glm::vec3>(glm::normalize(up));
	//
	mRight = glm::cross(mDirection, mUp);
	mUp = glm::cross(mRight, mDirection);
}

const float Camera::sDefaultFieldOfView = glm::quarter_pi<float>();
const float Camera::sDefaultNearPlaneDistance = 0.01f;
const float Camera::sDefaultFarPlaneDistance = 10000.0f;

}
