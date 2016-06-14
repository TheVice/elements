
#include "GameTime.h"

namespace Library
{

GameTime::GameTime(double aTotalGameTime, double aElapsedGameTime)
	: mTotalGameTime(aTotalGameTime),
	  mElapsedGameTime(aElapsedGameTime)
{
}

double GameTime::GetTotalGameTime() const
{
	return mTotalGameTime;
}

void GameTime::SetTotalGameTime(double aTotalGameTime)
{
	mTotalGameTime = aTotalGameTime;
}

double GameTime::GetElapsedGameTime() const
{
	return mElapsedGameTime;
}

void GameTime::SetElapsedGameTime(double aElapsedGameTime)
{
	mElapsedGameTime = aElapsedGameTime;
}

}
