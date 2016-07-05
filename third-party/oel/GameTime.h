#ifndef _GAME_TIME_H_
#define _GAME_TIME_H_

namespace Library
{
class GameTime
{
public:
	GameTime(double aTotalGameTime, double aElapsedGameTime);

public:
	GameTime() = delete;
	GameTime(const GameTime& aRhs) = delete;
	GameTime& operator = (const GameTime& aRhs) = delete;

public:
	double GetTotalGameTime() const;
	void SetTotalGameTime(double aTotalGameTime);

	double GetElapsedGameTime() const;
	void SetElapsedGameTime(double aElapsedGameTime);

private:
	double mTotalGameTime;
	double mElapsedGameTime;
};
}

#endif
