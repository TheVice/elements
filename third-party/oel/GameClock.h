#ifndef _GAME_CLOCK_H_
#define _GAME_CLOCK_H_

#ifdef WIN32
#include <windows.h>
#else
#include <ctime>
#endif

namespace Library
{
class GameTime;
class GameClock
{
public:
	GameClock();

public:
	GameClock(const GameClock& aRhs) = delete;
	GameClock& operator = (const GameClock& aRhs) = delete;

#ifndef WIN32
public:
	const timespec StartTime() const;
	const timespec CurrentTime() const;
	const timespec LastTime() const;

	void Reset();
	static timespec GetResolution();
	static void GetTime(timespec& aTime);
	void UpdateGameTime(GameTime& aGameTime);

private:
	timespec mStartTime;
	timespec mCurrentTime;
	timespec mLastTime;
	timespec mResolution;
	static const clockid_t sClockId;
	static const long sNsInSecond;
#else
public:
	const LARGE_INTEGER StartTime() const;
	const LARGE_INTEGER CurrentTime() const;
	const LARGE_INTEGER LastTime() const;

	void Reset();
	static double GetFrequency();
	static void GetTime(LARGE_INTEGER& aTime);
	void UpdateGameTime(GameTime& aGameTime);

private:
	LARGE_INTEGER mStartTime;
	LARGE_INTEGER mCurrentTime;
	LARGE_INTEGER mLastTime;
	double mFrequency;
#endif
};
}

#endif
