#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Vector2D.h"

class Typhoon {
public:
	Typhoon();
	Typhoon(bool isDead, Vector2D new_pos, Vector2D hkPos, float _accuracy, SDL_Surface* _map_surface);
	void move(int gameSpeed, float _accuracy);
	void render(SDL_Surface *typhoonSurface, SDL_Surface *g_pScreen);
	void render_artificial_typhoon(SDL_Surface *typhoonSurface, SDL_Surface *g_pScreen);

	void update_predict_range(int level);
	void update_predict_accuracy(int _accuracy);

	bool get_exist();
	int get_level();
	int get_deaths();
	int get_injuries();
	Vector2D get_pos();
	Vector2D get_dir();
	bool get_follow();
	int get_name_index();

	void Respawn(int new_name_index, int difficulty);

	void set_exist(bool exist_t);
	void set_level(int new_level);
	void set_pos(Vector2D new_pos);
	void set_follow(bool follow);
	void set_name_index(int new_name_index);
	void set_deaths(float addDeaths);
	void set_injuries(float addInjuries);

	int GetDistanceToTarget(); // return distance with target location(hk)

	bool LevelDown(float value);
	void LevelUp(float value);
	void Frame();
	void Predict(bool isRan);

	void save_dir(Vector2D dir);

	void ChangeDir(Vector2D vect);

	int soundIndex;

private:
	SDL_Surface* map_surface;
	Vector2D pos;
	Vector2D lastCalPos;
	Vector2D target_pos;
	bool isDead;
	int frame;
	float level;
	int nextLevel;
	float totalDist;
	float curDist;
	float speed;
	float gameSpeed;
	float range;
	float accuracy;
	int name_index;
	int landing_count;
	int predict_range;
	bool isFollow;
	float deaths;
	float injuries;
	Vector2D predictDirs[5]; //0 = next frame
	Vector2D predictDirsL[5]; //0 = next frame
	Vector2D predictDirsR[5]; //0 = next frame

	float rand[5];
	Vector2D exactDir;
};
