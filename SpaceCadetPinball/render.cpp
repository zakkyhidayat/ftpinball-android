#include "pch.h"
#include "render.h"
#include "proj.h"
#include "TBall.h"

#include "fullscrn.h"
#include "GroupData.h"
#include "options.h"
#include "pb.h"
#include "TPlunger.h"
#include "score.h"
#include "TPinballTable.h"
#include "winmain.h"

std::vector<render_sprite_type_struct*> render::dirty_list, render::sprite_list, render::ball_list;
zmap_header_type* render::background_zmap;
int render::zmap_offset, render::zmap_offsetY, render::offset_x, render::offset_y;
float render::zscaler, render::zmin, render::zmax;
rectangle_type render::vscreen_rect;
gdrv_bitmap8 *render::vscreen, *render::background_bitmap, *render::ball_bitmap[20];
zmap_header_type* render::zscreen;
SDL_Texture* render::vScreenTex = nullptr;
SDL_Rect render::DestinationRect{};

void render::init(gdrv_bitmap8* bmp, float zMin, float zScaler, int width, int height)
{
	zscaler = zScaler;
	zmin = zMin;
	zmax = 4294967300.0f / zScaler + zMin;
	vscreen = new gdrv_bitmap8(width, height, false);
	zscreen = new zmap_header_type(width, height, width);
	zdrv::fill(zscreen, zscreen->Width, zscreen->Height, 0, 0, 0xFFFF);
	vscreen_rect.YPosition = 0;
	vscreen_rect.XPosition = 0;
	vscreen_rect.Width = width;
	vscreen_rect.Height = height;
	vscreen->YPosition = 0;
	vscreen->XPosition = 0;
	for (auto& ballBmp : ball_bitmap)
		ballBmp = new gdrv_bitmap8(64, 64, false);

	background_bitmap = bmp;
	if (bmp)
		gdrv::copy_bitmap(vscreen, width, height, 0, 0, bmp, 0, 0);
	else
		gdrv::fill_bitmap(vscreen, vscreen->Width, vscreen->Height, 0, 0, 0);

	recreate_screen_texture();
}

void render::uninit()
{
	delete vscreen;
	delete zscreen;
	for (auto sprite : sprite_list)
		remove_sprite(sprite, false);
	for (auto ball : ball_list)
		remove_ball(ball, false);
	for (auto& ballBmp : ball_bitmap)
		delete ballBmp;
	ball_list.clear();
	dirty_list.clear();
	sprite_list.clear();
	SDL_DestroyTexture(vScreenTex);
	vScreenTex = nullptr;
}

void render::recreate_screen_texture()
{
	if (vScreenTex != nullptr)
	{
		SDL_DestroyTexture(vScreenTex);
	}

	UsingSdlHint hint{ SDL_HINT_RENDER_SCALE_QUALITY, options::Options.LinearFiltering ? "linear" : "nearest" };
	vScreenTex = SDL_CreateTexture
	(
		winmain::Renderer,
		SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,
		vscreen_rect.Width, vscreen_rect.Height
	);
	SDL_SetTextureBlendMode(vScreenTex, SDL_BLENDMODE_NONE);
}

void render::update()
{
	unpaint_balls();

	// Clip dirty sprites with vScreen, clear clipping (dirty) rectangles 
	for (auto curSprite : dirty_list)
	{
		bool clearSprite = false;
		switch (curSprite->VisualType)
		{
		case VisualTypes::Sprite:
			if (curSprite->DirtyRectPrev.Width > 0)
				maths::enclosing_box(curSprite->DirtyRectPrev, curSprite->BmpRect, curSprite->DirtyRect);

				if (maths::rectangle_clip(curSprite->DirtyRect, vscreen_rect, &curSprite->DirtyRect))
				clearSprite = true;
			else
				curSprite->DirtyRect.Width = -1;
			break;
		case VisualTypes::None:
			if (maths::rectangle_clip(curSprite->BmpRect, vscreen_rect, &curSprite->DirtyRect))
				clearSprite = !curSprite->Bmp;
			else
				curSprite->DirtyRect.Width = -1;
			break;
		default: break;
		}

		if (clearSprite)
		{
			auto yPos = curSprite->DirtyRect.YPosition;
			auto width = curSprite->DirtyRect.Width;
			auto xPos = curSprite->DirtyRect.XPosition;
			auto height = curSprite->DirtyRect.Height;
			zdrv::fill(zscreen, width, height, xPos, yPos, 0xFFFF);
			if (background_bitmap)
				gdrv::copy_bitmap(vscreen, width, height, xPos, yPos, background_bitmap, xPos, yPos);
			else
				gdrv::fill_bitmap(vscreen, width, height, xPos, yPos, 0);
		}
	}

	// Paint dirty rectangles of dirty sprites
	for (auto sprite : dirty_list)
	{
		if (sprite->DirtyRect.Width > 0 && (sprite->VisualType == VisualTypes::None || sprite->VisualType ==
			VisualTypes::Sprite))
			repaint(sprite);
	}

	paint_balls();

	// In the original, this used to blit dirty sprites and balls
	for (auto sprite : dirty_list)
	{
		sprite->DirtyRectPrev = sprite->DirtyRect;
		if (sprite->UnknownFlag != 0)
			remove_sprite(sprite, true);
	}

	dirty_list.clear();
}

void render::sprite_modified(render_sprite_type_struct* sprite)
{
	if (sprite->VisualType != VisualTypes::Ball && dirty_list.size() < 999)
		dirty_list.push_back(sprite);
}

render_sprite_type_struct* render::create_sprite(VisualTypes visualType, gdrv_bitmap8* bmp, zmap_header_type* zMap,
                                                 int xPosition, int yPosition, rectangle_type* rect)
{
	auto sprite = new render_sprite_type_struct();
	if (!sprite)
		return nullptr;
	sprite->BmpRect.YPosition = yPosition;
	sprite->BmpRect.XPosition = xPosition;
	sprite->Bmp = bmp;
	sprite->VisualType = visualType;
	sprite->UnknownFlag = 0;
	sprite->SpriteArray = nullptr;
	sprite->DirtyRect = rectangle_type{};
	if (rect)
	{
		sprite->BoundingRect = *rect;
	}
	else
	{
		sprite->BoundingRect.Width = -1;
		sprite->BoundingRect.Height = -1;
		sprite->BoundingRect.XPosition = 0;
		sprite->BoundingRect.YPosition = 0;
	}
	if (bmp)
	{
		sprite->BmpRect.Width = bmp->Width;
		sprite->BmpRect.Height = bmp->Height;
	}
	else
	{
		sprite->BmpRect.Width = 0;
		sprite->BmpRect.Height = 0;
	}
	sprite->ZMap = zMap;
	sprite->ZMapOffestX = 0;
	sprite->ZMapOffestY = 0;
	if (!zMap && visualType != VisualTypes::Ball)
	{
		sprite->ZMap = background_zmap;
		sprite->ZMapOffestY = xPosition - zmap_offset;
		sprite->ZMapOffestX = yPosition - zmap_offsetY;
	}
	sprite->DirtyRectPrev = sprite->BmpRect;
	if (visualType == VisualTypes::Ball)
	{
		ball_list.push_back(sprite);
	}
	else
	{
		sprite_list.push_back(sprite);
		sprite_modified(sprite);
	}
	return sprite;
}


void render::remove_sprite(render_sprite_type_struct* sprite, bool removeFromList)
{
	if (removeFromList)
	{
		auto it = std::find(sprite_list.begin(), sprite_list.end(), sprite);
		if (it != sprite_list.end())
			sprite_list.erase(it);
	}

	delete sprite->SpriteArray;
	delete sprite;
}

void render::remove_ball(render_sprite_type_struct* ball, bool removeFromList)
{
	if (removeFromList)
	{
		auto it = std::find(ball_list.begin(), ball_list.end(), ball);
		if (it != ball_list.end())
			ball_list.erase(it);
	}

	delete ball->SpriteArray;
	delete ball;
}

void render::sprite_set(render_sprite_type_struct* sprite, gdrv_bitmap8* bmp, zmap_header_type* zMap, int xPos,
                        int yPos)
{
	if (sprite)
	{
		sprite->BmpRect.XPosition = xPos;
		sprite->BmpRect.YPosition = yPos;
		sprite->Bmp = bmp;
		if (bmp)
		{
			sprite->BmpRect.Width = bmp->Width;
			sprite->BmpRect.Height = bmp->Height;
		}
		sprite->ZMap = zMap;
		sprite_modified(sprite);
	}
}

void render::sprite_set_bitmap(render_sprite_type_struct* sprite, gdrv_bitmap8* bmp)
{
	if (sprite && sprite->Bmp != bmp)
	{
		sprite->Bmp = bmp;
		if (bmp)
		{
			sprite->BmpRect.Width = bmp->Width;
			sprite->BmpRect.Height = bmp->Height;
		}
		sprite_modified(sprite);
	}
}

void render::set_background_zmap(struct zmap_header_type* zMap, int offsetX, int offsetY)
{
	background_zmap = zMap;
	zmap_offset = offsetX;
	zmap_offsetY = offsetY;
}

void render::ball_set(render_sprite_type_struct* sprite, gdrv_bitmap8* bmp, float depth, int xPos, int yPos)
{
	if (sprite)
	{
		sprite->Bmp = bmp;
		if (bmp)
		{
			sprite->BmpRect.XPosition = xPos;
			sprite->BmpRect.YPosition = yPos;
			sprite->BmpRect.Width = bmp->Width;
			sprite->BmpRect.Height = bmp->Height;
		}
		if (depth >= zmin)
		{
			float depth2 = (depth - zmin) * zscaler;
			if (depth2 <= zmax)
				sprite->Depth = static_cast<short>(depth2);
			else
				sprite->Depth = -1;
		}
		else
		{
			sprite->Depth = 0;
		}
	}
}

void render::repaint(struct render_sprite_type_struct* sprite)
{
	rectangle_type clipRect{};
	if (!sprite->SpriteArray)
		return;
	for (auto refSprite : *sprite->SpriteArray)
	{
		if (!refSprite->UnknownFlag && refSprite->Bmp)
		{
			if (maths::rectangle_clip(refSprite->BmpRect, sprite->DirtyRect, &clipRect))
				zdrv::paint(
					clipRect.Width,
					clipRect.Height,
					vscreen,
					clipRect.XPosition,
					clipRect.YPosition,
					zscreen,
					clipRect.XPosition,
					clipRect.YPosition,
					refSprite->Bmp,
					clipRect.XPosition - refSprite->BmpRect.XPosition,
					clipRect.YPosition - refSprite->BmpRect.YPosition,
					refSprite->ZMap,
					clipRect.XPosition + refSprite->ZMapOffestY - refSprite->BmpRect.XPosition,
					clipRect.YPosition + refSprite->ZMapOffestX - refSprite->BmpRect.YPosition);
		}
	}
}


void render::paint_balls()
{
	// Sort ball sprites by depth
	for (auto i = 0u; i < ball_list.size(); i++)
	{
		for (auto j = i; j < ball_list.size() / 2; ++j)
		{
			auto ballA = ball_list[j];
			auto ballB = ball_list[i];
			if (ballB->Depth > ballA->Depth)
			{
				ball_list[i] = ballA;
				ball_list[j] = ballB;
			}
		}
	}

	// For balls that clip vScreen: save original vScreen contents and paint ball bitmap.
	for (auto index = 0u; index < ball_list.size(); ++index)
	{
		auto ball = ball_list[index];
		auto dirty = &ball->DirtyRect;
		if (ball->Bmp && maths::rectangle_clip(ball->BmpRect, vscreen_rect, &ball->DirtyRect))
		{
			int xPos = dirty->XPosition;
			int yPos = dirty->YPosition;
			gdrv::copy_bitmap(ball_bitmap[index], dirty->Width, dirty->Height, 0, 0, vscreen, xPos, yPos);
			zdrv::paint_flat(
				dirty->Width,
				dirty->Height,
				vscreen,
				xPos,
				yPos,
				zscreen,
				xPos,
				yPos,
				ball->Bmp,
				xPos - ball->BmpRect.XPosition,
				yPos - ball->BmpRect.YPosition,
				ball->Depth);
		}
		else
		{
			dirty->Width = -1;
		}
	}
}

void render::unpaint_balls()
{
	// Restore portions of vScreen saved during previous paint_balls call.
	for (int index = static_cast<int>(ball_list.size()) - 1; index >= 0; index--)
	{
		auto curBall = ball_list[index];
		if (curBall->DirtyRect.Width > 0)
			gdrv::copy_bitmap(
				vscreen,
				curBall->DirtyRect.Width,
				curBall->DirtyRect.Height,
				curBall->DirtyRect.XPosition,
				curBall->DirtyRect.YPosition,
				ball_bitmap[index],
				0,
				0);

		curBall->DirtyRectPrev = curBall->DirtyRect;
	}
}

void render::shift(int offsetX, int offsetY)
{
	offset_x += offsetX;
	offset_y += offsetY;
}

void render::build_occlude_list()
{
	std::vector<render_sprite_type_struct*>* spriteArr = nullptr;
	for (auto mainSprite : sprite_list)
	{
		if (mainSprite->SpriteArray)
		{
			delete mainSprite->SpriteArray;
			mainSprite->SpriteArray = nullptr;
		}

		if (!mainSprite->UnknownFlag && mainSprite->BoundingRect.Width != -1)
		{
			if (!spriteArr)
				spriteArr = new std::vector<render_sprite_type_struct*>();

			for (auto refSprite : sprite_list)
			{
				if (!refSprite->UnknownFlag
					&& refSprite->BoundingRect.Width != -1
					&& maths::rectangle_clip(mainSprite->BoundingRect, refSprite->BoundingRect, nullptr)
					&& spriteArr)
				{
					spriteArr->push_back(refSprite);
				}
			}

			if (mainSprite->Bmp && spriteArr->size() < 2)
				spriteArr->clear();
			if (!spriteArr->empty())
			{
				mainSprite->SpriteArray = spriteArr;
				spriteArr = nullptr;
			}
		}
	}

	delete spriteArr;
}

void render::BlitVScreen()
{
	int pitch = 0;
	ColorRgba* lockedPixels;
	SDL_LockTexture
	(
		vScreenTex,
		nullptr,
		reinterpret_cast<void**>(&lockedPixels),
		&pitch
	);
	assertm(static_cast<unsigned>(pitch) == vscreen->Width * sizeof(ColorRgba), "Padding on vScreen texture");

	std::memcpy(lockedPixels, vscreen->BmpBufPtr1, vscreen->Width * vscreen->Height * sizeof(ColorRgba));

	SDL_UnlockTexture(vScreenTex);
}

bool render::PlungerWindow = false;
bool render::BallInPlunger = false;

// Fixed, square, magnified view of the shooter lane with ball and plunger (it does not follow the ball), drawn on top of the table
static bool PlungerAnchorSet = false;
static float PlungerAnchorX = 0, PlungerAnchorY = 0;


static float LaneBallX = 0, LaneBallY = 0;
static bool LaneBallKnown = false;

// While the ball waits in the lane its own (sloped) position is the anchor; afterwards the last one stays
static void UpdateLaneBall()
{
	if (!render::BallInPlunger || !pb::MainTable || pb::MainTable->BallList.empty())
		return;
	int xy[2]{};
	proj::xform_to_2d(&pb::MainTable->BallList[0]->Position, xy);
	LaneBallX = static_cast<float>(xy[0]);
	LaneBallY = static_cast<float>(xy[1]);
	LaneBallKnown = true;
}

void render::DrawPlungerWindow()
{
	auto& dest = DestinationRect;

	// The lane is fixed: project the plunger position onto the virtual screen once per opening
	if (!PlungerAnchorSet)
	{
		PlungerAnchorX = vscreen->Width * 0.9f;
		PlungerAnchorY = vscreen->Height * 0.9f;
		if (pb::MainTable && !pb::MainTable->BallList.empty())
		{
			vector3 plunger{};
			plunger.X = pb::MainTable->PlungerPositionX;
			plunger.Y = pb::MainTable->PlungerPositionY;
			plunger.Z = pb::MainTable->BallList[0]->Position.Z;
			int xy[2]{};
			proj::xform_to_2d(&plunger, xy);
			PlungerAnchorX = static_cast<float>(xy[0]);
			PlungerAnchorY = static_cast<float>(xy[1]);
		}
		PlungerAnchorSet = true;
	}
	UpdateLaneBall();
	if (LaneBallKnown)
	{
		PlungerAnchorX = LaneBallX;
		PlungerAnchorY = LaneBallY;
	}

	// Square (1:1) window centered on the table
	SDL_Rect win;
	// Only the board (left part of the virtual screen) is visible, the sidebar sits off screen
	int boardWidth = pb::MainTable ? std::min(static_cast<int>(pb::MainTable->Width), vscreen->Width) : vscreen->Width;
	float boardDestW = static_cast<float>(dest.w) * boardWidth / vscreen->Width;
	win.w = win.h = static_cast<int>(boardDestW * 0.40f);
	win.x = dest.x + static_cast<int>(boardDestW / 2) - win.w / 2;
	win.y = dest.y + dest.h / 2 - win.h / 2;

	// Source: the lower right of the table, with the lane, ball and plunger at the right-bottom of the view
	const float magnification = 2.0f;
	float scaleX = static_cast<float>(dest.w) / vscreen->Width;
	float scaleY = static_cast<float>(dest.h) / vscreen->Height;
	SDL_Rect src;
	src.w = static_cast<int>(win.w / (scaleX * magnification));
	src.h = static_cast<int>(win.h / (scaleY * magnification));
	// Ball centered horizontally; past the right edge of the board there is only the off screen sidebar, so
	// the source is cut there and the window is filled with black on that side
	src.x = std::max(0, static_cast<int>(PlungerAnchorX - src.w * 0.5f));
	src.y = std::max(0, std::min(static_cast<int>(PlungerAnchorY - src.h * 0.40f), vscreen->Height - src.h));

	Uint8 oldR, oldG, oldB, oldA;
	SDL_GetRenderDrawColor(winmain::Renderer, &oldR, &oldG, &oldB, &oldA);
	SDL_SetRenderDrawColor(winmain::Renderer, 0, 0, 0, 255);
	SDL_RenderFillRect(winmain::Renderer, &win);
	SDL_Rect copyDst = win;
	if (src.x + src.w > boardWidth)
	{
		int cut = src.x + src.w - boardWidth;
		copyDst.w = win.w - static_cast<int>(cut * win.w / static_cast<float>(src.w));
		src.w -= cut;
	}
	SDL_RenderCopy(winmain::Renderer, vScreenTex, &src, &copyDst);
	SDL_SetRenderDrawColor(winmain::Renderer, 255, 183, 77, 255);
	for (int i = 0; i < 3; i++)
	{
		SDL_Rect border{ win.x - i, win.y - i, win.w + 2 * i, win.h + 2 * i };
		SDL_RenderDrawRect(winmain::Renderer, &border);
	}
	SDL_SetRenderDrawColor(winmain::Renderer, oldR, oldG, oldB, oldA);
}

void render::PresentVScreen()
{
	static bool fitted = false;
	if (!fitted && pb::MainTable)
	{
		fitted = true;
		fullscrn::window_size_changed(); // centers tables narrower than Space Cadet
	}
	PresentVScreenTable();
	if (PlungerWindow)
		DrawPlungerWindow();
	else
		PlungerAnchorSet = false;
}

void render::PresentVScreenTable()
{
	BlitVScreen();

	if (offset_x == 0 && offset_y == 0)
	{
		SDL_RenderCopy(winmain::Renderer, vScreenTex, nullptr, &DestinationRect);
	}
	else
	{
		auto tableWidthCoef = static_cast<float>(pb::MainTable->Width) / vscreen->Width;
		auto srcSeparationX = static_cast<int>(round(vscreen->Width * tableWidthCoef));
		auto srcBoardRect = SDL_Rect
		{
			0, 0,
			srcSeparationX, vscreen->Height
		};
		auto srcSidebarRect = SDL_Rect
		{
			srcSeparationX, 0,
			vscreen->Width - srcSeparationX, vscreen->Height
		};

#if SDL_VERSION_ATLEAST(2, 0, 10)
		// SDL_RenderCopyF was added in 2.0.10
		auto dstSeparationX = DestinationRect.w * tableWidthCoef;
		auto dstBoardRect = SDL_FRect
		{
			DestinationRect.x + offset_x * fullscrn::ScaleX,
			DestinationRect.y + offset_y * fullscrn::ScaleY,
			dstSeparationX, static_cast<float>(DestinationRect.h)
		};
		auto dstSidebarRect = SDL_FRect
		{
			DestinationRect.x + dstSeparationX, static_cast<float>(DestinationRect.y),
			DestinationRect.w - dstSeparationX, static_cast<float>(DestinationRect.h)
		};

		SDL_RenderCopyF(winmain::Renderer, vScreenTex, &srcBoardRect, &dstBoardRect);
		SDL_RenderCopyF(winmain::Renderer, vScreenTex, &srcSidebarRect, &dstSidebarRect);
#else
		// SDL_RenderCopy cannot express sub pixel offset.
		// Vscreen shift is required for that.
		auto dstSeparationX = static_cast<int>(DestinationRect.w * tableWidthCoef);
		auto scaledOffX = static_cast<int>(round(offset_x * fullscrn::ScaleX));
		if (offset_x != 0 && scaledOffX == 0)
			scaledOffX = Sign(offset_x);
		auto scaledOffY = static_cast<int>(round(offset_y * fullscrn::ScaleY));
		if (offset_y != 0 && scaledOffX == 0)
			scaledOffY = Sign(offset_y);

		auto dstBoardRect = SDL_Rect
		{
			DestinationRect.x + scaledOffX, DestinationRect.y + scaledOffY,
			dstSeparationX, DestinationRect.h
		};
		auto dstSidebarRect = SDL_Rect
		{
			DestinationRect.x + dstSeparationX, DestinationRect.y,
			DestinationRect.w - dstSeparationX, DestinationRect.h
		};

		SDL_RenderCopy(winmain::Renderer, vScreenTex, &srcBoardRect, &dstBoardRect);
		SDL_RenderCopy(winmain::Renderer, vScreenTex, &srcSidebarRect, &dstSidebarRect);
#endif
	}
}
