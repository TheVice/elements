#ifndef _GAME_COMPONENT_H_
#define _GAME_COMPONENT_H_

#include "RTTI.h"

namespace Library
{
class Game;
class GameTime;

class GameComponent : public RTTI
{
	RTTI_DECLARATIONS(GameComponent, RTTI)

public:
	GameComponent();
	GameComponent(Game& aGame);
	virtual ~GameComponent();

public:
	GameComponent(const GameComponent& aRhs) = delete;
	GameComponent& operator = (const GameComponent& aRhs) = delete;

public:
	Game* GetGame();
	void SetGame(Game& aGame);
	bool IsEnabled() const;
	void SetEnabled(bool aEnabled);

	virtual void Initialize();
	virtual void Update(const GameTime& aGameTime);

protected:
	Game* mGame;
	bool mEnabled;
};
}

#endif
