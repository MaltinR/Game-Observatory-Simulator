#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float _x, float _y)
{
	x = _x;
	y = _y;
}

Vector2D* Vector2D::Add(Vector2D vectA, Vector2D vectB)
{
	return new Vector2D(vectA.x + vectB.x, vectA.y + vectB.y);
}

Vector2D* Vector2D::Minus(Vector2D vectA, Vector2D vectB)
{
	return new Vector2D(vectA.x - vectB.x, vectA.y - vectB.y);
}

Vector2D* Vector2D::Scale(Vector2D vectA, float scale)
{
	return new Vector2D(vectA.x * scale, vectA.y * scale);
}

Vector2D* Vector2D::Divide(Vector2D vectA, float scale)
{
	return new Vector2D(vectA.x / scale, vectA.y / scale);
}

Vector2D* Vector2D::Normalize(Vector2D vectA)
{
	return Divide(vectA, Magnitude(vectA));
}

Vector2D* Vector2D::Reflect(Vector2D inDir, Vector2D normal)
{
	float factor = -2 * (normal.x * inDir.x + normal.y * inDir.y);
	return new Vector2D(factor * normal.x + inDir.x, factor * normal.y + inDir.y);
}

float Vector2D::Magnitude(Vector2D vectA)
{
	return sqrt(vectA.x * vectA.x + vectA.y * vectA.y);
}

bool Vector2D::Equal(Vector2D vectA, Vector2D vectB)
{
	return vectA.x == vectB.x && vectA.y == vectB.y;
}

float Vector2D::getX()
{
	return x;
}

float Vector2D::getY()
{
	return y;
}