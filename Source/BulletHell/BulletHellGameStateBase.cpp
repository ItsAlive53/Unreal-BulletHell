

#include "BulletHellGameStateBase.h"
#include "BulletHellGameModeBase.h"

ABulletHellGameStateBase::ABulletHellGameStateBase() {
	Score = 0;
}

void ABulletHellGameStateBase::IncrementScore() {
	Score++;
}

int ABulletHellGameStateBase::GetScore() {
	return Score;
}

