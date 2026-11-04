#include "pch.h"
#include "TDrain.h"


#include "control.h"
#include "loader.h"
#include "TBall.h"
#include "timer.h"
#include "TPinballTable.h"
#include "TSink.h"

TDrain::TDrain(TPinballTable* table, int groupIndex) : TCollisionComponent(table, groupIndex, true)
{
	Timer = 0;
	TimerTime = *loader::query_float_attribute(groupIndex, 0, 407);
}

int TDrain::Message(int code, float value)
{
	if (code == 1024)
	{
		if (Timer)
		{
			timer::kill(Timer);
			Timer = 0;
		}
		PinballTable->BallInSink = 0;
	}
	return 0;
}

void TDrain::Collision(TBall* ball, vector2* nextPosition, vector2* direction, float coef, TEdgeSegment* edge)
{
	ball->Message(1024, 0.0);
	if (loader::Lenient)
	{
		// Multiball: while other balls are still in play (or held in a sink) only this ball is lost
		if (TSink::Holding > 0)
		{
			control::handler(2000, this);
			return;
		}
		for (auto other : PinballTable->BallList)
			if (other != ball && other->ActiveFlag)
			{
				control::handler(2000, this);
				return;
			}
	}
	PinballTable->BallInSink = 1;
	Timer = timer::set(TimerTime, this, TimerCallback);
	control::handler(63, this);
}

void TDrain::TimerCallback(int timerId, void* caller)
{
	auto drain = static_cast<TDrain*>(caller);
	control::handler(60, drain);
}
