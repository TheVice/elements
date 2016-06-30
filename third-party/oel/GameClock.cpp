
#include "GameClock.h"
#include "GameTime.h"
#ifdef WIN32
#include <stdexcept>
#else
#include <cstring>
#include <algorithm>
#include <iostream>
#endif

namespace Library
{
#ifndef WIN32
GameClock::GameClock()
	: mStartTime(),
	  mCurrentTime(),
	  mLastTime(),
	  mResolution(GetResolution())
{
	Reset();
}

const timespec GameClock::StartTime() const
{
	return mStartTime;
}

const timespec GameClock::CurrentTime() const
{
	return mCurrentTime;
}

const timespec GameClock::LastTime() const
{
	return mLastTime;
}

void GameClock::Reset()
{
	GetTime(mStartTime);
	mCurrentTime = mStartTime;
	mLastTime = mCurrentTime;
}

timespec GameClock::GetResolution()
{
	timespec resolution;
	memset(&resolution, 0, sizeof(resolution));
	clock_getres(sClockId, &resolution);
	return resolution;
}

void GameClock::GetTime(timespec& aTime)
{
	memset(&aTime, 0, sizeof(aTime));
	clock_gettime(sClockId, &aTime);
}

#define timespec2ns(A) (A.tv_sec * sNsInSecond + A.tv_nsec)

void GameClock::UpdateGameTime(GameTime& aGameTime)
{
	GetTime(mCurrentTime);
	//
	long delta = (timespec2ns(mCurrentTime) - timespec2ns(mStartTime));
	aGameTime.SetTotalGameTime(static_cast<double>(delta) / sNsInSecond);
	//
	delta = (timespec2ns(mCurrentTime) - timespec2ns(mLastTime));
	aGameTime.SetElapsedGameTime(static_cast<double>(delta) / sNsInSecond);
	//
	mLastTime = mCurrentTime;
}

const clockid_t GameClock::sClockId = CLOCK_MONOTONIC;
const long GameClock::sNsInSecond = 1000000000;
#else
GameClock::GameClock()
	: mStartTime(),
	  mCurrentTime(),
	  mLastTime(),
	  mFrequency(GetFrequency())
{
	Reset();
}

const LARGE_INTEGER GameClock::StartTime() const
{
	return mStartTime;
}

const LARGE_INTEGER GameClock::CurrentTime() const
{
	return mCurrentTime;
}

const LARGE_INTEGER GameClock::LastTime() const
{
	return mLastTime;
}

void GameClock::Reset()
{
	GetTime(mStartTime);
	mCurrentTime = mStartTime;
	mLastTime = mCurrentTime;
}

double GameClock::GetFrequency()
{
	LARGE_INTEGER frequency;

	if (QueryPerformanceFrequency(&frequency) == false)
	{
		throw std::runtime_error("QueryPerformanceFrequency() failed");
	}

	return static_cast<double>(frequency.QuadPart);
}

void GameClock::GetTime(LARGE_INTEGER& aTime)
{
	QueryPerformanceCounter(&aTime);
}

void GameClock::UpdateGameTime(GameTime& aGameTime)
{
	GetTime(mCurrentTime);
	aGameTime.SetTotalGameTime((mCurrentTime.QuadPart - mStartTime.QuadPart) / mFrequency);
	aGameTime.SetElapsedGameTime((mCurrentTime.QuadPart - mLastTime.QuadPart) / mFrequency);
	mLastTime = mCurrentTime;
}
#endif
}
