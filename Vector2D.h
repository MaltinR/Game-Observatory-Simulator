#ifndef Vector2D_HEADER
#define Vector2D_HEADER

#include <SDL.h>
#include <stdlib.h>
#include <time.h>

class Vector2D {
public:

	Vector2D();
	Vector2D(float _x, float _y);
	static Vector2D* Add(Vector2D vectA, Vector2D vectB);
	static Vector2D* Minus(Vector2D vectA, Vector2D vectB);
	static Vector2D* Scale(Vector2D vectA, float scale);
	static Vector2D* Divide(Vector2D vectA, float scale);
	static Vector2D* Normalize(Vector2D vectA);
	static Vector2D* Reflect(Vector2D inDir, Vector2D normal);
	static float Magnitude(Vector2D vectA);
	static bool Equal(Vector2D vectA, Vector2D vectB);
	float getX();
	float getY();
private:

	float x, y;
};

#endif