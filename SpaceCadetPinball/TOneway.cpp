#include "pch.h"
#include "TOneway.h"


#include "control.h"
#include "loader.h"
#include "TBall.h"
#include "TLine.h"
#include "TPinballTable.h"

TOneway::TOneway(TPinballTable* table, int groupIndex) : TCollisionComponent(table, groupIndex, false)
{
	visualStruct visual{};

	loader::query_visual(groupIndex, 0, &visual);
	if (visual.FloatArrCount == 2)
	{
		AddLines(visual.FloatArr, visual.CollisionGroup);
		return;
	}

	// Full Tilt: several gates in one component, as {2, x1, y1, x2, y2, ...} records in attribute 604
	auto list = loader::query_float_attribute(groupIndex, 0, 604);
	while (list && *list == 2.0f)
	{
		AddLines(list + 1, visual.CollisionGroup);
		list += 6;
	}
}

void TOneway::AddLines(const float* points, unsigned int collisionGroup)
{
	vector2 linePt2{points[0], points[1]};
	vector2 linePt1{points[2], points[3]};

	auto line = new TLine(this, &ActiveFlag, collisionGroup, linePt2, linePt1);
	line->Offset(PinballTable->CollisionCompOffset);
	line->place_in_grid();
	EdgeList.push_back(line);

	line = new TLine(this, &ActiveFlag, collisionGroup, linePt1, linePt2);
	Line = line;
	line->Offset(-PinballTable->CollisionCompOffset * 0.8f);
	line->place_in_grid();
	EdgeList.push_back(line);
}

bool TOneway::IsBackLine(TEdgeSegment* edge) const
{
	// Back lines are the second of each pair
	for (size_t i = 1; i < EdgeList.size(); i += 2)
		if (EdgeList[i] == edge)
			return true;
	return false;
}

void TOneway::Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef, TEdgeSegment* edge)
{
	if (IsBackLine(edge))
	{
		ball->not_again(edge);
		ball->Position.X = nextPosition->X;
		ball->Position.Y = nextPosition->Y;
		ball->RayMaxDistance -= coef;
		if (!PinballTable->TiltLockFlag)
		{
			if (HardHitSoundId)
				loader::play_sound(HardHitSoundId);
			control::handler(63, this);
		}
	}
	else if (PinballTable->TiltLockFlag)
	{
		maths::basic_collision(ball, nextPosition, direction, Elasticity, Smoothness, 1000000000.0, 0.0);
	}
	else if (maths::basic_collision(
		ball,
		nextPosition,
		direction,
		Elasticity,
		Smoothness,
		Threshold,
		Boost) > 0.2f)
	{
		if (SoftHitSoundId)
			loader::play_sound(SoftHitSoundId);
	}
}

int TOneway::Message(int code, float value)
{
	// Full Tilt diverters: the original switches a gate on (62) or off (63); the Dragon's Keep diverters come in pairs,
	// one on and one off (original 0x423d50)
	switch (code)
	{
	case 62:
		ActiveFlag = 1;
		break;
	case 63:
		ActiveFlag = 0;
		break;
	default:
		break;
	}
	return 0;
}

void TOneway::put_scoring(int index, int score)
{
	if (index < 6)
		Scores[index] = score;
}

int TOneway::get_scoring(int index)
{
	return index < 6 ? Scores[index] : 0;
}
