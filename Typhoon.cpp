#include "Typhoon.h"
#include <chrono>
#include <ctime>
#include <stdlib.h>	

#define TyphoonRadius 75.f

// Constructor

float RandomRange(float a, float b) {

	int randX, randY;
	SDL_GetMouseState(&randX, &randY);

	srand(rand() * randX * randY + rand());
	return ((b - a) * ((float)rand() / RAND_MAX)) + a;
}

void Putpixel(SDL_Surface *Screen, int x, int y, Uint32 pixel) {

	if (x < 0 || y < 0 || x >= 1280 || y >= 720) return;

	int byteperpixel = Screen->format->BytesPerPixel;

	Uint8 *p = (Uint8*)Screen->pixels + y * Screen->pitch + x * byteperpixel;

	// Address to pixel
	*(Uint32 *)p = pixel;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	//Check
	if (x < 0 || y < 0 || x >= 1280 || y >= 720) return 0;

	int bpp = surface->format->BytesPerPixel;
	/* Here p is the address to the pixel we want to retrieve */
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
	case 1:
		return *p;
		break;

	case 2:
		return *(Uint16 *)p;
		break;

	case 3:
		if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
		else
			return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
		return *(Uint32 *)p;
		break;

	default:
		return 0;       /* shouldn't happen, but avoids warnings */
	}
}

void DrawLine(SDL_Surface *Screen, int x0, int y0, int x1, int y1, Uint32 pixel) {

	int i;
	double x = x1 - x0;
	double y = y1 - y0;
	double length = sqrt(x * x + y * y);
	double addx = x / length;
	double addy = y / length;
	x = x0;
	y = y0;

	for (i = 0; i < length; i += 1) {
		Putpixel(Screen, x, y, pixel);
		Putpixel(Screen, x + 1, y, pixel);
		Putpixel(Screen, x + 1, y + 1, pixel);
		Putpixel(Screen, x, y + 1, pixel);
		x += addx;
		y += addy;
	}
}

void DrawCircle(SDL_Surface *Screen, int x0, int y0, int radius)
{
	int x = 0, y = radius;
	int dp = 1 - radius;
	do
	{
		if (dp < 0)
			dp = dp + 2 * (++x) + 3;
		else
			dp = dp + 2 * (++x) - 2 * (--y) + 5;

		Putpixel(Screen, x0 + x, y0 + y, 15);     //For the 8 octants
		Putpixel(Screen, x0 - x, y0 + y, 15);
		Putpixel(Screen, x0 + x, y0 - y, 15);
		Putpixel(Screen, x0 - x, y0 - y, 15);
		Putpixel(Screen, x0 + y, y0 + x, 15);
		Putpixel(Screen, x0 - y, y0 + x, 15);
		Putpixel(Screen, x0 + y, y0 - x, 15);
		Putpixel(Screen, x0 - y, y0 - x, 15);

	} while (x < y);
}

void Typhoon::set_follow(bool follow)
{
	isFollow = follow;
}

void Typhoon::Respawn(int new_name_index, int difficulty)
{
	soundIndex = std::rand() % 2;
	name_index = new_name_index;
	//speed = RandomRange(80, 120);
	speed = RandomRange(60 + difficulty * 5, 80 + difficulty * 5);
	set_level(RandomRange(1 + difficulty, 4 + difficulty));

	lastCalPos = pos;
	curDist = 0;
	deaths = 0;
	injuries = 0;

	Predict(true);
	
	predictDirs[0] = *Vector2D::Normalize(*Vector2D::Add(*Vector2D::Minus(target_pos, pos), (Vector2D(RandomRange(-100.f, 100.f), RandomRange(-100.f, 100.f)))));

	float rand = RandomRange(-0.5f, 0.5f);
	predictDirs[1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(+predictDirs[0].getY(), -predictDirs[0].getX()), rand), predictDirs[0]);
}

Typhoon::Typhoon(bool _isDead, Vector2D new_pos, Vector2D hkPos, float _accuracy, SDL_Surface* _map_surface) {

	int randX, randY;
	SDL_GetMouseState(&randX, &randY);

	srand(time(NULL) + randX + randY);
	soundIndex = std::rand() % 2;

	map_surface = _map_surface;
	isDead = _isDead;
	frame = 0;
	level = 1;
	pos = new_pos;
	curDist = 0;
	lastCalPos = pos;
	target_pos = hkPos;
	gameSpeed = 4;
	landing_count = 0;
	//name = "";
	speed = RandomRange(80, 120); 
	accuracy = _accuracy; // 60, 70, 80, 90, 100
	range = (110 - accuracy) / 200.f;

	Predict(true);

	predictDirs[0] = *Vector2D::Normalize(*Vector2D::Add(*Vector2D::Minus(target_pos, new_pos), (Vector2D(RandomRange(-100.f, 100.f), RandomRange(-100.f, 100.f)))));

	float rand = RandomRange(-0.5f, 0.5f);
	predictDirs[1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(+predictDirs[0].getY(), -predictDirs[0].getX()), rand), predictDirs[0]);
}

void Typhoon::render(SDL_Surface *typhoonSurface,
	SDL_Surface *g_pScreen)
{
	if (!isDead) {
		SDL_Rect dest_temp;
		dest_temp.x = (int)pos.getX() - TyphoonRadius;
		dest_temp.y = (int)pos.getY() - TyphoonRadius;

		Uint32 color = 0x00FF0000; // TODO: Different color of predict route SDL_MapRGBA(, 0,0,0,200)
		// typhoon gif
		SDL_BlitSurface(typhoonSurface, NULL, g_pScreen, &dest_temp);

		Vector2D tempPosL = Vector2D(lastCalPos.getX(), lastCalPos.getY());
		//Must do
		DrawLine(g_pScreen, (int)pos.getX(), (int)pos.getY(), (int)(tempPosL.getX() + predictDirsL[0].getX()), (int)(tempPosL.getY() + predictDirsL[0].getY()), color);

		tempPosL = *Vector2D::Add(tempPosL, predictDirsL[0]);
		for (int i = 1; i < 5 && predict_range >= i; i++)
		{
			DrawLine(g_pScreen, (int)tempPosL.getX(), (int)tempPosL.getY(), (int)(tempPosL.getX() + predictDirsL[i].getX()), (int)(tempPosL.getY() + predictDirsL[i].getY()), color);
			tempPosL = *Vector2D::Add(tempPosL, predictDirsL[i]);
		}
		//R
		Vector2D tempPosR = Vector2D(lastCalPos.getX(), lastCalPos.getY());
		//Must do
		DrawLine(g_pScreen, (int)pos.getX(), (int)pos.getY(), (int)(tempPosR.getX() + predictDirsR[0].getX()), (int)(tempPosR.getY() + predictDirsR[0].getY()), color);

		tempPosR = *Vector2D::Add(tempPosR, predictDirsR[0]);
		for (int i = 1; i < 5 && predict_range >= i; i++)
		{
			DrawLine(g_pScreen, (int)tempPosR.getX(), (int)tempPosR.getY(), (int)(tempPosR.getX() + predictDirsR[i].getX()), (int)(tempPosR.getY() + predictDirsR[i].getY()), color);
			tempPosR = *Vector2D::Add(tempPosR, predictDirsR[i]);
		}
	}
}

void Typhoon::render_artificial_typhoon(SDL_Surface *typhoonSurface,
	SDL_Surface *g_pScreen)
{
	if (!isDead) {
		SDL_Rect dest_temp;
		dest_temp.x = (int)pos.getX() - 75;
		dest_temp.y = (int)pos.getY() - 75;

		Uint32 color = Uint32(); // TODO: Different color of predict route SDL_MapRGBA(, 0,0,0,200)
		// typhoon gif
		SDL_BlitSurface(typhoonSurface, NULL, g_pScreen, &dest_temp);
	}
}

void Typhoon::update_predict_range(int level)
{
	predict_range = level;
}

void Typhoon::update_predict_accuracy(int _accuracy)
{
	accuracy = _accuracy;
}

void Typhoon::move(int _gameSpeed, float _accuracy)
{
	SDL_Color rgb;
	landing_count = 0;

	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			Uint32 data = getpixel(map_surface, pos.getX() - 15 + i, pos.getY() - 15 + j);
			SDL_GetRGB(data, map_surface->format, &rgb.r, &rgb.g, &rgb.b);

			//printf("rgb %d %d %d\n", rgb.r, rgb.g, rgb.b);
			if (rgb.b < 100) { // non-sea, touching land
				landing_count++;
			}
		}
	}

	gameSpeed = _gameSpeed * (1 / ((landing_count / (float)450) + 1));

	frame += gameSpeed;
	accuracy = _accuracy; // 60, 70, 80, 90, 100
	range = (110 - accuracy) / 200.f;


	Vector2D moveVect = *Vector2D::Divide(exactDir, 4000.f / gameSpeed);
	pos = *Vector2D::Add(pos, moveVect);
	curDist += Vector2D::Magnitude(moveVect);

	// different landed situation
	if (landing_count > 550) // if none part of typhoon is landed
		LevelDown((landing_count - 550) * (landing_count - 550) * 0.0000001f * gameSpeed / 4);
	else if (landing_count < 300)
		LevelUp((300 - landing_count) * (300 - landing_count) * 0.000000035f * gameSpeed / 4);

	if (level > 12) level = 12;

	if (curDist >= totalDist)
	{
		curDist = 0;

		frame = 0;

		lastCalPos = pos;

		Predict(false);
		/*
		float ran = rand[0];
		rand[0] = rand[1];
		rand[1] = rand[2];
		rand[2] = RandomRange(-0.5f + range, 0.5f - range);
		float exactRand = RandomRange(ran - range, ran + range);
		//printf("A %f %f %f %f exactRand\n", exactRand, ran, -0.5f + range, 0.5f - range);
		//Non-initialize
		predictDirsL[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-exactDir.getY(), +exactDir.getX()), (ran - range)), exactDir);
		predictDirsR[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-exactDir.getY(), +exactDir.getX()), (ran + range)), exactDir);
		//Non-initialize
		exactDir = *Vector2D::Scale(*Vector2D::Normalize(exactDir), speed);
		exactDir = *Vector2D::Add(*Vector2D::Scale(Vector2D(-exactDir.getY(), +exactDir.getX()), (exactRand)), exactDir);

		totalDist = Vector2D::Magnitude(exactDir);

		Vector2D tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsL[0]), speed);
		//predictDirsL[1] = tempVect;
		predictDirsL[1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[0] - range)), tempVect);
		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsR[0]), speed);
		predictDirsR[1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[0] + range)), tempVect);

		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsL[1]), speed);
		predictDirsL[2] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[1] - range)), tempVect);
		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsR[1]), speed);
		predictDirsR[2] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[1] + range)), tempVect);

		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsL[2]), speed);
		predictDirsL[3] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[2] - range)), tempVect);
		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsR[2]), speed);
		predictDirsR[3] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[2] + range)), tempVect);
		*/
	}

	//Outside the Screen
	if (pos.getX() < -75.f || pos.getX() > 1355.f || pos.getY() > 795.f || pos.getY() < -75.f) isDead = true;
}

void Typhoon::Predict(bool isRan)
{
	lastCalPos = pos;
	//float ran = RandomRange(-speed / 2 + range, speed / 2 - range);
	float ran;
	float exactRand;
	Vector2D tempVect;
	if (isRan)
	{
		ran = RandomRange(-0.5f + range, 0.5f - range);
		rand[0] = RandomRange(-0.5f + range, 0.5f - range);
		rand[1] = RandomRange(-0.5f + range, 0.5f - range);
		rand[2] = RandomRange(-0.5f + range, 0.5f - range);
		rand[3] = RandomRange(-0.5f + range, 0.5f - range);
		rand[4] = RandomRange(-0.5f + range, 0.5f - range);
		exactRand = RandomRange(ran - range, ran + range);

		tempVect = *Vector2D::Scale(*Vector2D::Normalize(*Vector2D::Add(*Vector2D::Minus(target_pos, pos), Vector2D(RandomRange(-20.f, 20.f), RandomRange(-20.f, 20.f)))), speed);

		predictDirsL[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (ran - range)), tempVect);
		predictDirsR[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (ran + range)), tempVect);
		exactDir = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (exactRand)), tempVect);
	}
	else
	{
		ran = rand[0];
		rand[0] = rand[1];
		rand[1] = rand[2];
		rand[2] = rand[3];
		rand[3] = rand[4];
		rand[4] = RandomRange(-0.5f + range, 0.5f - range);

		exactRand = RandomRange(ran - range, ran + range);
		//Non-initialize
		predictDirsL[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-exactDir.getY(), +exactDir.getX()), (ran - range)), exactDir);
		predictDirsR[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-exactDir.getY(), +exactDir.getX()), (ran + range)), exactDir);
		//Non-initialize
		exactDir = *Vector2D::Scale(*Vector2D::Normalize(exactDir), speed);
		exactDir = *Vector2D::Add(*Vector2D::Scale(Vector2D(-exactDir.getY(), +exactDir.getX()), (exactRand)), exactDir);
	}

	totalDist = Vector2D::Magnitude(exactDir);

	for (int i = 0; i < 4; i++)
	{
		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsL[i]), speed);
		predictDirsL[i+1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[i] - range)), tempVect);
		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsR[i]), speed);
		predictDirsR[i+1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[i] + range)), tempVect);
	}
}

bool Typhoon::LevelDown(float value)
{
	level -= value;
	//sprite.color = new Color(1, 1, 1, 0.2f * level);
	//transform.localScale = new Vector3((0.5f + 0.5f * level), (0.5f + 0.5f * level), 1f);
	isDead = level < 1;

	return isDead;
}

void Typhoon::LevelUp(float value)
{
	level += value;
	if (level > 13) level = 13;
	//sprite.color = new Color(1, 1, 1, 0.2f * level);
	//transform.localScale = new Vector3((0.5f + 0.5f * level), (0.5f + 0.5f * level), 1f);
}

int Typhoon::GetDistanceToTarget() {
	return (int)sqrt((target_pos.getX() - pos.getX()) * (target_pos.getX() - pos.getX()) + (target_pos.getY() - pos.getY()) * (target_pos.getY() - pos.getY()));
}


bool Typhoon::get_exist() {
	return !isDead;
}
Vector2D Typhoon::get_pos() {
	return pos;
}
int Typhoon::get_level() {
	return (int)level;
}

bool Typhoon::get_follow()
{
	return isFollow;
}

Vector2D Typhoon::get_dir()
{
	return exactDir;
}

int Typhoon::get_name_index()
{
	return name_index;
}
int Typhoon::get_deaths()
{
	return (int)deaths;
}
int Typhoon::get_injuries()
{
	return (int)injuries;
}

void Typhoon::set_exist(bool exist_t) {
	isDead = !exist_t;
}
void Typhoon::set_pos(Vector2D new_pos) {
	pos = new_pos;

	lastCalPos = pos;
	curDist = 0;
}
void Typhoon::set_level(int new_level) {
	level = new_level;
}
void Typhoon::set_name_index(int new_name_index) {
	name_index = new_name_index;
}
void Typhoon::set_deaths(float addDeaths)
{
	deaths += addDeaths;
}
void Typhoon::set_injuries(float addInjuries)
{
	injuries += addInjuries;
}

//For artTyp only
void Typhoon::save_dir(Vector2D dir)
{
	exactDir = dir;
}

void Typhoon::ChangeDir(Vector2D vect)
{
	frame = 0;
	curDist = 0;
	lastCalPos = pos;

	float ran = RandomRange(-0.5f + range, 0.5f - range);
	rand[0] = RandomRange(-0.5f + range, 0.5f - range);
	rand[1] = RandomRange(-0.5f + range, 0.5f - range);
	rand[2] = RandomRange(-0.5f + range, 0.5f - range);
	rand[3] = RandomRange(-0.5f + range, 0.5f - range);
	rand[4] = RandomRange(-0.5f + range, 0.5f - range);
	float exactRand = RandomRange(ran - range, ran + range);

	Vector2D tempVect = *Vector2D::Scale(*Vector2D::Normalize(vect), speed);

	predictDirsL[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (ran - range)), tempVect);
	predictDirsR[0] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (ran + range)), tempVect);
	exactDir = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (exactRand)), tempVect);

	for (int i = 0; i < 4; i++)
	{
		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsL[i]), speed);
		predictDirsL[i+1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[i] - range)), tempVect);
		tempVect = *Vector2D::Scale(*Vector2D::Normalize(predictDirsR[i]), speed);
		predictDirsR[i+1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(-tempVect.getY(), +tempVect.getX()), (rand[i] + range)), tempVect);
	}

	predictDirs[0] = tempVect;

	float rand = RandomRange(-0.5f, 0.5f);
	predictDirs[1] = *Vector2D::Add(*Vector2D::Scale(Vector2D(+predictDirs[0].getY(), -predictDirs[0].getX()), rand), predictDirs[0]);
}