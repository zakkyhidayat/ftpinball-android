#include "pch.h"
#include "TMagnet.h"

#include "control.h"
#include "loader.h"
#include "TBall.h"
#include "TCircle.h"
#include "timer.h"
#include "TPinballTable.h"
#include "TTableLayer.h"

TMagnet::TMagnet(TPinballTable* table, int groupIndex) : TCollisionComponent(table, groupIndex, false)
{
	visualStruct visual{};
	loader::query_visual(groupIndex, 0, &visual);
	HoldTime = 1.0f;
	auto mult = loader::query_float_attribute(groupIndex, 0, 305);
	FieldMult = mult ? *mult : 1.0f;
	auto radiusMult = loader::query_float_attribute(groupIndex, 0, 306);
	if (visual.FloatArrCount < 3)
		return;

	Circle.Center.X = visual.FloatArr[0];
	Circle.Center.Y = visual.FloatArr[1];
	float core = (radiusMult ? *radiusMult : 0.1f) * visual.FloatArr[2];
	if (core == 0.0f)
		core = 0.001f;
	auto tCircle = new TCircle(this, &ActiveFlag, visual.CollisionGroup,
	                           reinterpret_cast<vector3*>(visual.FloatArr), core);
	if (tCircle)
	{
		tCircle->place_in_grid();
		EdgeList.push_back(tCircle);
	}

	Circle.RadiusSq = visual.FloatArr[2] * visual.FloatArr[2];
	Field.Flag2Ptr = &ActiveFlag;
	Field.CollisionComp = this;
	Field.Mask = visual.CollisionGroup;
	circle_type field = Circle;
	TTableLayer::edges_insert_circle(&field, nullptr, &Field);
}

int TMagnet::Message(int code, float value)
{
	if (code == 1024)
	{
		if (Timer)
			timer::kill(Timer);
		Timer = 0;
		Holding = 0;
	}
	return 0;
}

void TMagnet::put_scoring(int index, int score)
{
	if (index < 5)
		Scores[index] = score;
}

int TMagnet::get_scoring(int index)
{
	return index < 5 ? Scores[index] : 0;
}

void TMagnet::Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef,
                        TEdgeSegment* edge)
{
	ball->Position.X = nextPosition->X;
	ball->Position.Y = nextPosition->Y;
	ball->RayMaxDistance -= coef;
	ball->not_again(edge);
	Holding = 1;
	Timer = timer::set(HoldTime, this, ReleaseTimer);
	if (!PinballTable->TiltLockFlag)
	{
		if (SoftHitSoundId)
			loader::play_sound(SoftHitSoundId);
		control::handler(63, this);
	}
}

int TMagnet::FieldEffect(TBall* ball, vector2* vecDst)
{
	if (Holding)
		return 0;
	float dx = Circle.Center.X - ball->Position.X;
	float dy = Circle.Center.Y - ball->Position.Y;
	if (dx * dx + dy * dy > Circle.RadiusSq)
		return 0;
	vecDst->X = FieldMult * dx - ball->Acceleration.X * ball->Speed;
	vecDst->Y = FieldMult * dy - ball->Acceleration.Y * ball->Speed;
	return 1;
}

void TMagnet::ReleaseTimer(int timerId, void* caller)
{
	auto magnet = static_cast<TMagnet*>(caller);
	magnet->Holding = 0;
	magnet->Timer = 0;
}
