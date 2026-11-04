#pragma once
#include "maths.h"
#include "TCollisionComponent.h"
#include "TEdgeManager.h"

// Lane zone of Dragon's Keep and Skulduggery (original object type 1036):
// a ball touching its edge is flung along the lane by the field inside the zone.
class TAccelerator :
	public TCollisionComponent
{
public:
	TAccelerator(TPinballTable* table, int groupIndex);
	void put_scoring(int index, int score) override;
	int get_scoring(int index) override;
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
	               TEdgeSegment* edge) override;
	int FieldEffect(TBall* ball, vector2* vecDst) override;

	TBall* Ball{};
	vector3 BallAcceleration{};
	float ThrowAngleMult;
	float ThrowSpeedMult1;
	float ThrowSpeedMult2;
	field_effect_type Field{};
	int Scores[5]{};
};
