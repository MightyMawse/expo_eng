#include "graphics.h"
#include "globals.h"
#include "utils.h"

#include <iostream>
#include <cmath>
#include <algorithm>

std::vector<Vertex> Graphics::inlineCastPos;
std::vector<float> Graphics::projectionAngles;
std::vector<float> Graphics::angleOffsets;

SDL_Renderer* pRenderer = nullptr;
std::vector<SDL_Rect> wallRects;

void Graphics::Init(void) {
	pRenderer = SDL_CreateRenderer(pMainWin, -1, SDL_RENDERER_ACCELERATED);
	std::cout << SDL_GetError() << std::endl;
	return;
}

void DrawBackground() {
	// Draw sky and ground
	SDL_SetRenderDrawColor(pRenderer, 173, 250, 255, SDL_ALPHA_OPAQUE);

	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = WIN_WIDTH;
	rect.h = WIN_HEIGHT / 2;

	SDL_RenderFillRect(pRenderer, &rect);
	SDL_RenderDrawRect(pRenderer, &rect);

	SDL_SetRenderDrawColor(pRenderer, 120, 120, 120, SDL_ALPHA_OPAQUE);

	SDL_Rect rect2;
	rect2.x = 0;
	rect2.y = WIN_HEIGHT / 2;
	rect2.w = WIN_WIDTH;
	rect2.h = WIN_HEIGHT / 2;

	SDL_RenderFillRect(pRenderer, &rect2);
	SDL_RenderDrawRect(pRenderer, &rect2);
}

//--------------------------------------------------
// GetAlpha()
// purpose: Get the angle offset
//--------------------------------------------------
float Graphics::GetAlpha(float a) {
	if (a <= 90)
		return 0;
	else if (a > 90 && a <= 180)
		return 90;
	else if (a > 180 && a <= 270)
		return 180;
	else if (a > 270 && a <= 360)
		return 270;
}

//--------------------------------------------------
// GetDir()
// purpose: Get dirs
//--------------------------------------------------
int* Graphics::GetDir(float a) {
	float alpha = GetAlpha(a);
	int dir[2] = { 0, 0 };
	float y_dir = Utils::Round_2DP(cos(DEG((a))));

	if (y_dir > 0)
		dir[1] = 1;
	else if (y_dir < 0)
		dir[1] = -1;
	else
		dir[1] = 0;

	float x_dir = Utils::Round_2DP(sin(DEG(a)));

	if (x_dir > 0)
		dir[0] = 1;
	else if (x_dir < 0)
		dir[0] = -1;
	else
		dir[0] = 0;

	return dir;
}

//--------------------------------------------------
// SignMatch()
// purpose: Match dx or dy with its dir sign
//--------------------------------------------------
float Graphics::SignMatch(float f, float dir) {
	if (dir > 0) {
		if (f < 0)
			return (f * -1); // invert it
	}
	else if (dir < 0) {
		if (f > 0)
			return (f * -1);
	}
	else if (dir == 0)
		return 0;
	return f;
}

//--------------------------------------------------
// CalculatePoint()
// purpose: Return collision point of next cell
//--------------------------------------------------
Vertex Graphics::CalculatePoint(Vertex v1, float a) {
	Vertex p2 = Vertex(0, 0);

	a = std::fmod(a, 360.0f);

	int* dir = Graphics::GetDir(a);
	float x_dir = dir[0];
	float y_dir = dir[1];

	float fl_x = floor(v1.m_x);
	float fl_y = floor(v1.m_y);

	float x2 = x_dir > 0 ? fl_x + 1 : (std::fmod(v1.m_x, 1.0) == 0.0 ? fl_x - 1 : fl_x);
	float y2 = y_dir > 0 ? fl_y + 1 : (std::fmod(v1.m_y, 1.0) == 0.0 ? fl_y - 1 : fl_y);

	float n_x = nx(a, v1.m_x, x2);
	float n_y = ny(a, v1.m_y, y2);

	if (n_x < n_y) {
		p2.m_x = x2;

		float d_y = dy(v1.m_x, x2, a);
		float y = v1.m_y + SignMatch(d_y, y_dir);
		p2.m_y = y;
	}
	else if (n_y < n_x) {
		p2.m_y = y2;

		float d_x = dx(v1.m_y, y2, a) * x_dir;
		float x = v1.m_x + SignMatch(d_x, x_dir);
		p2.m_x = x;
	}

	return p2;
}

//--------------------------------------------------
// nx()
// purpose: return the length that needs to be travelled
// in a direction to reach next x integer
//--------------------------------------------------
float Graphics::nx(float a, float x1, float x2) {
	float n_x = 0;
	if (a <= 90) {
		n_x = (x2 - x1) / sin(DEG(a));
	}
	else if (a > 90 && a <= 180) {
		n_x = (x2 - x1) / cos(DEG((a - 90)));
	}
	else if (a > 180 && a <= 270) {
		n_x = (x2 - x1) / sin(DEG((a - 180)));
	}
	else if (a > 270 && a <= 360) {
		n_x = (x2 - x1) / cos(DEG((a - 270)));
	}

	return abs(n_x);
}

//--------------------------------------------------
// ny()
// purpose: return the length that needs to be travelled
// in a direction to reach next x integer
//--------------------------------------------------
float Graphics::ny(float a, float y1, float y2) {
	float n_y = 0;
	if (a <= 90) {
		n_y = (y2 - y1) / cos(DEG(a));
	}
	else if (a > 90 && a <= 180) {
		n_y = (y2 - y1) / sin(DEG((a - 90)));
	}
	else if (a > 180 && a <= 270) {
		n_y = (y2 - y1) / cos(DEG((a - 180)));
	}
	else if (a > 270 && a <= 360) {
		n_y = (y2 - y1) / sin(DEG((a - 270)));
	}

	return abs(n_y);
}

//--------------------------------------------------
// dx()
// purpose: return the x difference in positions
//--------------------------------------------------
float Graphics::dx(float y1, float y2, float a) {
	float d_x = 0;
	float alpha = GetAlpha(a);
	if (alpha == 0 || alpha == 180) {
		d_x = (y2 - y1) * tan(DEG((a - alpha)));
	}
	else {
		d_x = (y2 - y1) / tan(DEG((a - alpha)));
	}
	return d_x;
}

//--------------------------------------------------
// dy()
// purpose: return the y difference in positions
//--------------------------------------------------
float Graphics::dy(float x1, float x2, float a) {
	float d_y = 0;
	float alpha = GetAlpha(a);
	if (alpha == 0 || alpha == 180) {
		d_y = (x2 - x1) / tan(DEG((a - alpha)));
	}
	else {
		d_y = (x2 - x1) * tan(DEG((a - alpha)));
	}
	return d_y;
}

//--------------------------------------------------
// RayLength()
// purpose: return ray length
//--------------------------------------------------
float Graphics::RayLength(Vertex v1, Vertex v2) {
	float a = pow((v2.m_x - v1.m_x), 2);
	float b = pow((v2.m_y - v1.m_y), 2);
	float c = sqrt(a + b);
	return c;
}

//--------------------------------------------------
// Raycast()
// purpose: return ray length if collision with wall
//--------------------------------------------------
float Graphics::Raycast(Vertex v, float a) {
	bool collision = false;
	Vertex v_last = v;

	while (!collision) {
		float heading = std::fmod(a, 360.0f);

		v_last = CalculatePoint(v_last, heading);
		collision = pWorld->IsWall(v_last);

		if (RayLength(v, v_last) > RENDER_DISTANCE)
			return -1;
	}

	return RayLength(v, v_last);
}

//--------------------------------------------------
// GetColumnHeight()
// purpose: Get column height
//--------------------------------------------------
float Graphics::GetColumnHeight(float l) {
	//float lengthOverRD = l / RENDER_DISTANCE;
	//float inverse = 1 - lengthOverRD;
	//float height = inverse * WIN_HEIGHT;
	float height = (WIN_HEIGHT * WALL_HEIGHT) / l;
	return height;
}

//--------------------------------------------------
// DrawColumn()
// purpose: Draw column given x and height
//--------------------------------------------------
void Graphics::DrawColumn(float x, float height) {

	float grayScale = ((height / WIN_HEIGHT) * 0.8) * 255;

	SDL_SetRenderDrawColor(pRenderer, grayScale, grayScale, grayScale, SDL_ALPHA_OPAQUE);

	float y_screenSpace[2] = { (height / 2), -height / 2 };
	float width = ((float)WIN_WIDTH / (float)(PARTITION_SIZE - 1)) + 1;

	SDL_Rect rect;
	rect.x = x - (width / 2);
	rect.y = ((float)WIN_HEIGHT - height) / 2;
	rect.w = width;
	rect.h = height;

	SDL_RenderFillRect(pRenderer, &rect);
	SDL_RenderDrawRect(pRenderer, &rect);
}


//--------------------------------------------------
// Render()
// purpose: Raycast across the screen
//--------------------------------------------------
void Graphics::Render(void) {
	// Get angle offsets
	projectionAngles.clear();

	float paritionAngle = (float)FOV / (float)PARTITION_SIZE;
	int halfPartition = PARTITION_SIZE / 2;

	for (int j = 0; j < 2; j++) { 
		for (int c = 0; c < halfPartition; c++) {
			if (j == 0) {
				float offset = (paritionAngle * -(halfPartition - c));
				projectionAngles.push_back(pPlayer->a + offset);
				angleOffsets.push_back(offset);
			}
			else {
				float offset = (paritionAngle * (c + 1));
				projectionAngles.push_back(pPlayer->a + offset);
				angleOffsets.push_back(offset);
			}
		}
	}

	// Ray cast across FOV
	SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(pRenderer);

	//DrawBackground();

	float columnWidth = (float)WIN_WIDTH / (float)(PARTITION_SIZE - 1);

	for (int n = 0; n < projectionAngles.size(); n++) {
		float a = projectionAngles[n];
		float aLocal = angleOffsets[n];

		float distance = Raycast(pPlayer->GetPosition(), a);

		if (distance != -1) {
			float range = Utils::GetRayRange(distance, aLocal);
			float columnHeight = Graphics::GetColumnHeight(range);
			float x = (columnWidth * n);

			Graphics::DrawColumn(x, columnHeight);
		}
	}

	SDL_RenderPresent(pRenderer);

	return;
}

//--------------------------------------------------
// StepForward()
// purpose: Get position f units ahead of point
//--------------------------------------------------
Vertex& Graphics::StepFoward(Vertex v, float f, float a) {
	Vertex next = Vertex(0, 0);

	float x, y;
	if (a <= 90) {
		x = f * Utils::Round_2DP(sin(DEG(a)));
		y = f * Utils::Round_2DP(cos(DEG(a)));
	}
	else if (a > 90 && a <= 180) {
		x = f * Utils::Round_2DP(cos(DEG(a - 90)));
		y = -f * Utils::Round_2DP(sin(DEG(a - 90)));
	}
	else if (a > 180 && a <= 270) {
		x = -f * Utils::Round_2DP(sin(DEG(a - 180)));
		y = -f * Utils::Round_2DP(cos(DEG(a - 180)));
	}
	else if (a > 270 && a <= 360) {
		x = -f * Utils::Round_2DP(cos(DEG(a - 270)));
		y = f * Utils::Round_2DP(sin(DEG(a - 270)));
	}

	next = Vertex(v.m_x + x, v.m_y + y);
	return next;
}