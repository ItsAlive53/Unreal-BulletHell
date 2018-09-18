

#include "BHPlayerState.h"

ABHPlayerState::ABHPlayerState() {
	Score = 0;
}

void ABHPlayerState::IncrementScore() {
	Score++;
}

int ABHPlayerState::GetScore() {
	return Score;
}
