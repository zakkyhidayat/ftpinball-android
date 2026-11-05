#pragma once
#include "maths.h"
#include "TCollisionComponent.h"

class TSink :
	public TCollisionComponent
{
public:
	TSink(TPinballTable* table, int groupIndex);
	int Message(int code, float value) override;
	void put_scoring(int index, int score) override;
	int get_scoring(int index) override;
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
	               TEdgeSegment* edge) override;

	static void TimerExpired(int timerId, void* caller);

	int Timer;
	TBall* HeldBall = nullptr; // the ball in the sink, so that several balls can be in play
	bool SpawnBall = false; // release a new ball on the next timer (multiball)
	static int Holding;        // balls held in sinks waiting to be kicked out (a locked ball does not count)
	float TimerTime;
	vector2 BallPosition{};
	vector3 BallAcceleration{};
	float ThrowAngleMult;
	float ThrowSpeedMult1;
	float ThrowSpeedMult2;
	int SoundIndex4;
	int SoundIndex3;
	int Scores[3]{};
	int PlayerMessagefieldBackup[4]{};
};
