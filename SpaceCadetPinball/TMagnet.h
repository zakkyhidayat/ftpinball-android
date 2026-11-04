#pragma once
#include "maths.h"
#include "TCollisionComponent.h"
#include "TEdgeManager.h"

// Skulduggery's magnet (original object type 1042): pulls the ball toward its
// centre, holds it for a moment once it arrives, then lets go
class TMagnet :
	public TCollisionComponent
{
public:
	TMagnet(TPinballTable* table, int groupIndex);
	int Message(int code, float value) override;
	void put_scoring(int index, int score) override;
	int get_scoring(int index) override;
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
	               TEdgeSegment* edge) override;
	int FieldEffect(TBall* ball, vector2* vecDst) override;

	static void ReleaseTimer(int timerId, void* caller);

	int Holding{};
	int Timer{};
	float HoldTime;
	float FieldMult;
	circle_type Circle{};
	field_effect_type Field{};
	int Scores[5]{};
};
