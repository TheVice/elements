#ifndef _CLEAR_DEPTH_H_
#define _CLEAR_DEPTH_H_

#include <DrawableGameComponent.h>
#include <Game.h>

namespace Library
{
class ClearDepth : public DrawableGameComponent
{
	RTTI_DECLARATIONS(ClearDepth, DrawableGameComponent)

public:
	ClearDepth(Game& aGame);
	~ClearDepth();

public:
	ClearDepth() = delete;
	ClearDepth(const ClearDepth& aRhs) = delete;
	ClearDepth& operator = (const ClearDepth& aRhs) = delete;

public:
	virtual bool Initialize() override;
	virtual void Draw() override;
};
}

#endif
