#include "include/raylib.h"
#include <iostream>
#include <cmath>

#define NUMBER_OF_RAY 150


typedef struct segment
{
	Vector2 firstPoint;
	Vector2 secondPoint;

} segment;

typedef struct ray
{
	Vector2 firstPoint;
	Vector2 secondPoint;

} ray;

static inline bool lineLine(ray &r, segment &s, Vector2 &intersecPoint)
{
	float x1 = r.firstPoint.x;
	float y1 = r.firstPoint.y;
	float x2 = r.secondPoint.x;
	float y2 = r.secondPoint.y;
	float x3 = s.firstPoint.x;
	float y3 = s.firstPoint.y;
	float x4 = s.secondPoint.x;
	float y4 = s.secondPoint.y;

	// calculate the direction of the lines
	float uA = ((x4-x3)*(y1-y3) - (y4-y3)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));
	float uB = ((x2-x1)*(y1-y3) - (y2-y1)*(x1-x3)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1));

	// if uA and uB are between 0-1, lines are colliding
	if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1)
	{
		// optionally, draw a circle where the lines meet
		intersecPoint.x = x1 + (uA * (x2-x1));
		intersecPoint.y = y1 + (uA * (y2-y1));
		return true;
	}
	return false;
}

static inline Vector2 closestVec(Vector2 ori, Vector2 v2, Vector2 intersec)
{
	int cmp1 = 0;
	int cmp2 = 0;

	cmp1 = std::abs(ori.x - v2.x) + std::abs(ori.y - v2.y);
	cmp2 = std::abs(ori.x - intersec.x) + std::abs(ori.y - intersec.y);

	return ((cmp1 >= cmp2) ? intersec : v2);
}

int main()
{
	int w = 1080;
	int h = 720;
	Vector2 intersecPoint;
	bool inter = false;

	segment seg[5];
	seg[0].firstPoint.x = 70.0f;
	seg[0].firstPoint.y = 70.0f;
	seg[0].secondPoint.x = 130.0f;
	seg[0].secondPoint.y = 600.0f;

	seg[1].firstPoint.x = 70.0f;
	seg[1].firstPoint.y = 70.0f;
	seg[1].secondPoint.x = 230.0f;
	seg[1].secondPoint.y = 450.0f;

	seg[2].firstPoint.x = 270.0f;
	seg[2].firstPoint.y = 400.0f;
	seg[2].secondPoint.x = 50.0f;
	seg[2].secondPoint.y = 350.0f;

	seg[3].firstPoint.x = 650.0f;
	seg[3].firstPoint.y = 70.0f;
	seg[3].secondPoint.x = 950.0f;
	seg[3].secondPoint.y = 300.0f;

	seg[4].firstPoint.x = 600.0f;
	seg[4].firstPoint.y = 600.0f;
	seg[4].secondPoint.x = 880.0f;
	seg[4].secondPoint.y = 500.0f;

	ray r[NUMBER_OF_RAY];

	InitWindow(w, h, "Raycasting 2D Line");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		inter = false;
		r[0].firstPoint = GetMousePosition();
		r[0].secondPoint.x = r[0].firstPoint.x + std::cos((2 * PI)) * (w * 2);
		r[0].secondPoint.y = r[0].firstPoint.y + std::sin((2 * PI)) * (w * 2);
		for (unsigned int j = 0; j < 5; j++)
		{
			if ((inter = lineLine(r[0], seg[j], intersecPoint)))
			{
				if (inter)
					r[0].secondPoint = closestVec(r[0].firstPoint, r[0].secondPoint, intersecPoint);
				else
					r[0].secondPoint = intersecPoint;
			}
		}
		inter = false;
		for (int i = 1; i < NUMBER_OF_RAY; i++)
		{
			r[i].firstPoint = GetMousePosition();
			r[i].secondPoint.x = r[i].firstPoint.x + std::cos(((2 * PI) / NUMBER_OF_RAY) * i) * (w * 2);
			r[i].secondPoint.y = r[i].firstPoint.y + std::sin(((2 * PI) / NUMBER_OF_RAY) * i) * (w * 2);
			for (unsigned int j = 0; j < 5; j++)
			{
				if ((inter = lineLine(r[i], seg[j], intersecPoint)))
				{
					if (inter)
						r[i].secondPoint = closestVec(r[i].firstPoint, r[i].secondPoint, intersecPoint);
					else
						r[i].secondPoint = intersecPoint;
				}
			}
			inter = false;
		}
		// r.firstPoint = GetMousePosition();
		// r.secondPoint = {0, 100};

		// tmps = lineLineIntersection(seg[0].firstPoint, seg[0].secondPoint, mousePos, {0, 100});
		// inter = lineLine(r, seg[0], intersecPoint);

		BeginDrawing();

			ClearBackground(BLACK);

			for (unsigned int i = 0; i < 5; i++)
				DrawLine(seg[i].firstPoint.x, seg[i].firstPoint.y, seg[i].secondPoint.x, seg[i].secondPoint.y, RAYWHITE);
			for (unsigned int i = 0; i < NUMBER_OF_RAY; i++)
				DrawLine(r[i].firstPoint.x, r[i].firstPoint.y, r[i].secondPoint.x, r[i].secondPoint.y, Fade(RAYWHITE, 0.8f));
			// if (inter)
				// DrawLine(r.firstPoint.x, r.firstPoint.y, intersecPoint.x, intersecPoint.y, RAYWHITE);


		EndDrawing();
	}
}