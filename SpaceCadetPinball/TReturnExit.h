#pragma once
#include "TCollisionComponent.h"

// Skulduggery's return exit (original object type 1035): two sided trigger line
class TReturnExit :
	public TCollisionComponent
{
public:
	TReturnExit(TPinballTable* table, int groupIndex);
	void Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
	               TEdgeSegment* edge) override;
};
