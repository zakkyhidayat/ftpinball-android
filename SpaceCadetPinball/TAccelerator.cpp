#include "pch.h"
#include "TAccelerator.h"

#include <algorithm>

#include "control.h"
#include "loader.h"
#include "TBall.h"
#include "TPinballTable.h"
#include "TTableLayer.h"

TAccelerator::TAccelerator(TPinballTable* table, int groupIndex) : TCollisionComponent(table, groupIndex, true)
{
	visualStruct visual{};
	circle_type circle{};

	loader::query_visual(groupIndex, 0, &visual);
	ThrowSpeedMult2 = visual.Kicker.ThrowBallMult * 0.01f;
	BallAcceleration = visual.Kicker.ThrowBallAcceleration;
	ThrowAngleMult = visual.Kicker.ThrowBallAngleMult;
	ThrowSpeedMult1 = visual.Kicker.Boost;

	// The zone is the circle around the wall's bounding box
	auto wall = loader::query_float_attribute(groupIndex, 0, 600);
	if (!wall)
		return;
	float minX = 1e9f, minY = 1e9f, maxX = -1e9f, maxY = -1e9f;
	auto grow = [&](float x, float y)
	{
		minX = std::min(minX, x);
		maxX = std::max(maxX, x);
		minY = std::min(minY, y);
		maxY = std::max(maxY, y);
	};
	int type = static_cast<int>(floor(*wall) - 1.0f);
	if (type == 0)
	{
		grow(wall[1] - wall[3], wall[2] - wall[3]);
		grow(wall[1] + wall[3], wall[2] + wall[3]);
	}
	else if (type == 1)
	{
		grow(wall[1], wall[2]);
		grow(wall[3], wall[4]);
	}
	else
	{
		for (int i = 0; i < type; i++)
			grow(wall[1 + 2 * i], wall[2 + 2 * i]);
	}
	float half = std::max((maxX - minX) / 1.8f, (maxY - minY) / 1.8f);
	circle.RadiusSq = half * half;
	circle.Center.X = (minX + maxX) / 2.0f;
	circle.Center.Y = (minY + maxY) / 2.0f;
	Field.Flag2Ptr = &ActiveFlag;
	Field.CollisionComp = this;
	Field.Mask = visual.CollisionGroup;
	TTableLayer::edges_insert_circle(&circle, nullptr, &Field);
}

void TAccelerator::put_scoring(int index, int score)
{
	if (index < 5)
		Scores[index] = score;
}

int TAccelerator::get_scoring(int index)
{
	return index < 5 ? Scores[index] : 0;
}

void TAccelerator::Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
                             TEdgeSegment* edge)
{
	ball->not_again(edge);
	ball->Position.X = nextPosition->X;
	ball->Position.Y = nextPosition->Y;
	ball->RayMaxDistance -= coef;
	if (!PinballTable->TiltLockFlag)
	{
		Ball = ball;
		if (SoftHitSoundId)
			loader::play_sound(SoftHitSoundId);
		control::handler(63, this);
	}
}

int TAccelerator::FieldEffect(TBall* ball, vector2* vecDst)
{
	if (Ball != ball)
		return 0;
	Ball = nullptr;
	TBall::throw_ball(ball, &BallAcceleration, ThrowAngleMult, ThrowSpeedMult1, ThrowSpeedMult2);
	return 0;
}
