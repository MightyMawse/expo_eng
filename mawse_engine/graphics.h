#pragma once
#include <math.h>
#include "typedef.h"
#include <vector>
#include <SDL.h>

#define PI 3.14
#define DEG(x) ((PI / 180.0f) * (x))
#define RENDER_DISTANCE 10
#define WIN_HEIGHT 480
#define WIN_WIDTH 680
#define PARTITION_SIZE 30 // Must be even
#define FOV 45
#define NEAR_CLIP 0.1f
#define WALL_HEIGHT 1.0f

extern SDL_Renderer* pRenderer;

static class Graphics {
public:
	static void Init(void);
	static Vertex CalculatePoint(Vertex v1, float a);
	static float Raycast(Vertex v, float a);
	static void Render(void);
	static Vertex& StepFoward(Vertex v, float f, float a);
	static float GetAlpha(float a);
private:
	static float nx(float a, float x1, float x2);
	static float ny(float a, float y1, float y2);
	static float dx(float y1, float y2, float a);
	static float dy(float x1, float x2, float a);
	static float RayLength(Vertex v1, Vertex v2);
	static int*  GetDir(float a);
	static float SignMatch(float f, float dir);
	static void  DrawColumn(float x, float height);
	static float GetColumnHeight(float l);
	static Vertex& InLineCastPos(int iter, float aPerpendicular);
private:
	static std::vector<Vertex> inlineCastPos;
	static std::vector<float> projectionAngles;
	static std::vector<float> angleOffsets;
};