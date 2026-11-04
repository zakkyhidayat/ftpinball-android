#include "pch.h"
#include "TBall.h"


#include "fullscrn.h"
#include "winmain.h"
#include "gdrv.h"
#include "partman.h"
#include "pinball.h"
#include "GroupData.h"
#include "loader.h"
#include "maths.h"
#include "pb.h"
#include "proj.h"
#include "render.h"
#include "TPinballTable.h"

TBall::TBall(TPinballTable* table) : TPinballComponent(table, -1, false)
{
	visualStruct visual{};
	char ballGroupName[10]{"ball"};

	TimeNow = 0.0;
	RayMaxDistance = 0.0;
	ActiveFlag = 1;
	CollisionComp = nullptr;
	EdgeCollisionCount = 0;
	TimeDelta = 0.0;
	FieldFlag = 1;
	CollisionFlag = 0;
	Speed = 0.0;
	Acceleration.Y = 0.0;
	Acceleration.X = 0.0;
	InvAcceleration.Y = 1000000000.0;
	InvAcceleration.X = 1000000000.0;
	Position.X = 0.0;
	Position.Y = 0.0;

	ListBitmap = new std::vector<gdrv_bitmap8*>();

	/*Full tilt: ball is ballN, where N[0,2] resolution*/
	if (pb::FullTiltMode)
		ballGroupName[4] = '0' + fullscrn::GetResolution();
	auto groupIndex = loader::query_handle(ballGroupName);

	Offset = *loader::query_float_attribute(groupIndex, 0, 500);

	auto visualCount = loader::query_visual_states(groupIndex);
	for (auto index = 0; index < visualCount; ++index)
	{
		loader::query_visual(groupIndex, index, &visual);
		if (ListBitmap)
			ListBitmap->push_back(visual.Bitmap);
		auto visVec = reinterpret_cast<vector3*>(loader::query_float_attribute(groupIndex, index, 501));
		auto zDepth = proj::z_distance(visVec);
		VisualZArray[index] = zDepth;
	}
	// Dragon's Keep only has a smiley face for a ball in its own data. The steel ball of the other Full Tilt
	// tables (Space Cadet's data is stored next to it by the app) is scaled to the sizes Dragon's Keep uses.
	if (pb::FullTiltMode && winmain::DatFileName == "DRAGON.DAT")
	{
		auto steelDat = partman::load_records(pinball::make_path_name("BALL_SOURCE.DAT").c_str(), true);
		if (steelDat)
		{
			std::vector<gdrv_bitmap8*> steel;
			auto steelPalette = reinterpret_cast<ColorRgba*>(steelDat->field_labeled("background", FieldTypes::Palette));
			ColorRgba palette[256]{};
			if (steelPalette)
			{
				// same rules as gdrv::display_palette: colors 10..245 come from the data, 255 is white
				for (int i = 10; i < 246; ++i)
				{
					palette[i] = steelPalette[i];
					palette[i].rgba.Alpha = 0xFF;
				}
				palette[255].Color = 0xffFFFFFF;
			}
			int steelGroup = steelDat->record_labeled("ball2");
			for (int i = steelGroup + 1; steelGroup >= 0 && i < static_cast<int>(steelDat->Groups.size()); ++i)
			{
				auto src = steelDat->Groups[i]->GetBitmap(2);
				if (!src || (!steel.empty() && src->Width < steel.back()->Width))
					break;
				// the second data file was not given its palette on load: colors come from its own palette
				if (steelPalette)
				{
					auto dst = src->BmpBufPtr1;
					for (int y = src->Height - 1; y >= 0; y--)
					{
						auto idx = reinterpret_cast<uint8_t*>(src->IndexedBmpPtr) + src->IndexedStride * y;
						for (int x = 0; x < src->Width; x++)
							*dst++ = palette[*idx++];
					}
				}
				steel.push_back(src);
			}
			if (steel.size() >= 2 && ListBitmap->size() >= 2)
			{
				for (size_t i = 0; i < ListBitmap->size(); ++i)
				{
					auto target = ListBitmap->at(i);
					auto src = steel[i * (steel.size() - 1) / (ListBitmap->size() - 1)];
					auto scaled = new gdrv_bitmap8(target->Width, target->Height, false);
					scaled->XPosition = target->XPosition;
					scaled->YPosition = target->YPosition;
					scaled->Resolution = target->Resolution;
					for (int y = 0; y < scaled->Height; ++y)
						for (int x = 0; x < scaled->Width; ++x)
							scaled->BmpBufPtr1[y * scaled->Stride + x] =
								src->BmpBufPtr1[(y * src->Height / scaled->Height) * src->Stride + x * src->Width / scaled->Width];
					(*ListBitmap)[i] = scaled;
				}
			}
		}
	}
	RenderSprite = render::create_sprite(VisualTypes::Ball, nullptr, nullptr, 0, 0, nullptr);
	PinballTable->CollisionCompOffset = Offset;
	Position.Z = Offset;
}

void TBall::Repaint()
{
	int pos2D[2];

	if (CollisionFlag)
	{
		Position.Z =
			CollisionOffset.X * Position.X +
			CollisionOffset.Y * Position.Y +
			Offset + CollisionOffset.Z;
	}

	proj::xform_to_2d(&Position, pos2D);
	auto zDepth = proj::z_distance(&Position);

	auto zArrPtr = VisualZArray;
	auto index = 0u;
	for (; index < ListBitmap->size() - 1; ++index, zArrPtr++)
	{
		if (*zArrPtr <= zDepth) break;
	}

	auto bmp = ListBitmap->at(index);
	render::ball_set(
		RenderSprite,
		bmp,
		zDepth,
		pos2D[0] - bmp->Width / 2,
		pos2D[1] - bmp->Height / 2);
}

void TBall::not_again(TEdgeSegment* edge)
{
	if (EdgeCollisionCount < 5)
	{
		Collisions[EdgeCollisionCount] = edge;
		++EdgeCollisionCount;
	}
}

bool TBall::already_hit(TEdgeSegment* edge)
{
	for (int i = 0; i < EdgeCollisionCount; i++)
	{
		if (Collisions[i] == edge)
			return true;
	}

	return false;
}

int TBall::Message(int code, float value)
{
	if (code == 1024)
	{
		render::ball_set(RenderSprite, nullptr, 0.0, 0, 0);
		Position.X = 0.0;
		CollisionComp = nullptr;
		Position.Y = 0.0;
		ActiveFlag = 0;
		CollisionFlag = 0;
		FieldFlag = 1;
		Acceleration.Y = 0.0;
		Position.Z = Offset;
		Acceleration.X = 0.0;
		Speed = 0.0;
		RayMaxDistance = 0.0;
	}
	return 0;
}

void TBall::throw_ball(TBall* ball, vector3* acceleration, float angleMult, float speedMult1, float speedMult2)
{
	ball->CollisionComp = nullptr;
	ball->Acceleration = *acceleration;
	float rnd = RandFloat();
	float angle = (1.0f - (rnd + rnd)) * angleMult;
	maths::RotateVector(ball->Acceleration, angle);
	rnd = RandFloat();
	ball->Speed = (1.0f - (rnd + rnd)) * (speedMult1 * speedMult2) + speedMult1;
}
