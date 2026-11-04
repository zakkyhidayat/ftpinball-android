#include "pch.h"
#include "TReturnExit.h"

#include "control.h"
#include "loader.h"
#include "TBall.h"
#include "TLine.h"
#include "TPinballTable.h"

TReturnExit::TReturnExit(TPinballTable* table, int groupIndex) : TCollisionComponent(table, groupIndex, false)
{
	// Attribute 1301: {maskBit1, maskBit2, count (2), x1, y1, x2, y2}
	auto data = loader::query_float_attribute(groupIndex, 0, 1301);
	if (!data || data[2] != 2.0f)
		return;
	vector2 start{data[3], data[4]}, end{data[5], data[6]};
	auto first = new TLine(this, &ActiveFlag, 1u << static_cast<int>(data[0]), start, end);
	first->Offset(table->CollisionCompOffset);
	first->place_in_grid();
	EdgeList.push_back(first);
	auto second = new TLine(this, &ActiveFlag, 1u << static_cast<int>(data[1]), end, start);
	second->Offset(table->CollisionCompOffset);
	second->place_in_grid();
	EdgeList.push_back(second);
}

void TReturnExit::Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
                            TEdgeSegment* edge)
{
	ball->not_again(edge);
	ball->Position.X = nextPosition->X;
	ball->Position.Y = nextPosition->Y;
	ball->RayMaxDistance -= coef;
	if (!PinballTable->TiltLockFlag)
	{
		if (SoftHitSoundId)
			loader::play_sound(SoftHitSoundId);
		control::handler(63, this);
	}
}
