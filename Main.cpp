
#include <stdio.h>
#include <stdlib.h>				
#include <math.h>
#include <time.h>
#include <string>
#include <iostream>
#include <vector>
#include <queue>

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "Button.h"

#include "Typhoon.h"
#include "Vector2D.h"

using namespace std;

SDL_Surface *g_pScreen;			// video screen, there's always one of these
SDL_Window  *g_pWindow;			// main window, there's always one of these

//Music and sound effects
Mix_Music* bgm = NULL;
Mix_Chunk* click_sound = NULL;
Mix_Chunk* item01_sound = NULL;
Mix_Chunk* item02_sound = NULL;
Mix_Chunk* item03_sound = NULL;
Mix_Chunk* item04_sound = NULL;
Mix_Chunk* lvlUp_sound = NULL;
Mix_Chunk* wind_sound_1 = NULL;
Mix_Chunk* wind_sound_2 = NULL;


// UI
SDL_Surface *panelSurface;	// panel image
SDL_Surface *helpPanelSurface;	// setting panel image
SDL_Surface *settinglevelSurface;	// setting level image
SDL_Surface *closeButtonSurface; // panel close image
SDL_Surface *closeLargeButtonSurface; // panel close large image 
SDL_Surface *plusSurface; // plus surface
SDL_Surface *minusSurface; // minus surface
SDL_Surface *plusDisableSurface; // plus surface disabled
SDL_Surface *minusDisableSurface; // minus surface disabled
SDL_Surface *mapSurface;	// map background image
SDL_Surface *blackSurface;	// black background image
SDL_Surface *settingButtonSurface;	// setting button image
SDL_Surface *extendButtonSurface;	// extend button image

//Main menu
SDL_Surface *mainBGSurface;	// main background image
SDL_Surface *mainBGSurface_NoLi;	// main background image without Li
SDL_Surface *defaultButtonSurface;	// default button surface
SDL_Surface *defaultButtonSurface_clicked;	// default button surface clicked

//Helping
SDL_Surface *helpButtonSurface;	// help button image
SDL_Surface *popularityRatingSurface_large; //popularity rating
SDL_Surface *hsiSurface_large; //Hang Seng Indexes
SDL_Surface *moneySurface_large; //government fund for the observatory
SDL_Surface *radSurface_large; //development points

//Map layers, decide not to draw
//SDL_Surface *mapLayerSurface_01;	// cloud layer
//SDL_Surface *mapLayerSurface_02;	// pressure layer

//Bar Background
SDL_Surface *topBarBgSurface;	// the background of the resource and time bar
SDL_Surface *newsBarBgSurface;	// the background of the news bar

//Typhoon
SDL_Surface *typhoonSurface_01; // typhoon image
SDL_Surface *typhoonSurface_02; // typhoon image
SDL_Surface *typhoonSurface_03; // typhoon image
SDL_Surface *typhoonSurface_04; // typhoon image
SDL_Surface *typhoonSurface_05; // typhoon image
SDL_Surface *typhoonSurface_06; // typhoon image
SDL_Surface *typhoonSurface_07; // typhoon image
SDL_Surface *typhoonSurface_08; // typhoon image
SDL_Surface *typhoonSurface_09; // typhoon image
SDL_Surface *typhoonSurface_10; // typhoon image
SDL_Surface *typhoonSurface_11; // typhoon image
SDL_Surface *typhoonSurface_12; // typhoon image
SDL_Surface *typhoonSurface_13; // typhoon image
SDL_Surface *typhoonSurface_14; // typhoon image
SDL_Surface *typhoonSurface_15; // typhoon image
SDL_Surface *typhoonSurface_16; // typhoon image
Typhoon *typhoons;//max: 5
Typhoon *artificialTyphoon;

//Items
SDL_Surface *itemSurface_01; //Item 1 (news deceiver): to reduce the impact of news on people¡¦s popularity
SDL_Surface *itemSurface_02; //Item 2: Change the intensity of the typhoon
SDL_Surface *itemSurface_03; //Item 3: Generate an artificial typhoon in random place (may produce the Fujiwara effect)
SDL_Surface *itemSurface_04; //Item 4(Li's Field) : When using when the typhoon approaches Hong Kong, can effectively change the direction of the typhoon
SDL_Surface *itemDisplaySurface_04; //Item 4 display
//SDL_Surface *itemBGSurface = SDL_CreateRGBSurface(0, 200, 200, 32, 0, 0, 0, 0);
//SDL_Surface *itemFillBGSurface_01;
//SDL_Surface *itemFillBGSurface_02;
//SDL_Surface *itemFillBGSurface_03;
//SDL_Surface *itemFillBGSurface_04;
SDL_Surface *itemSurface_01_dark;
SDL_Surface *itemSurface_02_dark;
SDL_Surface *itemSurface_03_dark;
SDL_Surface *itemSurface_04_dark;

SDL_Surface* stationSurface_empty; // station_empty
SDL_Surface* stationSurface_ready; // station_ready

//Resources
SDL_Surface *increaseIconSurface; //indicate resource increase icon
SDL_Surface *neutralIconSurface; //indicate resource neutral icon
SDL_Surface *decreaseIconSurface; //indicate resource decrease icon
SDL_Surface *popularityRatingSurface; //popularity rating
SDL_Surface *hsiSurface; //Hang Seng Indexes
SDL_Surface *moneySurface; //government fund for the observatory
SDL_Surface *moneySurface_grayscale;
SDL_Surface *radSurface; //development points

//Tropical Cyclone Signals
SDL_Surface *signalSurface_01; // Level 1 signal
SDL_Surface *signalSurface_03; // Level 3 signal
SDL_Surface *signalSurface_08; // Level 8 signal
SDL_Surface *signalSurface_09; // Level 9 signal
SDL_Surface *signalSurface_10; // Level 10 signal

//Game Speed
SDL_Surface *playSurface;
SDL_Surface *playingSurface;
SDL_Surface *pauseSurface;
SDL_Surface *pausingSurface;
SDL_Surface *speedSurface_01; // x1
//SDL_Surface *speedSurface_02; // x2
SDL_Surface *speedSurface_04; // x4 
//SDL_Surface *speedSurface_08; // x8
SDL_Surface *speedSurface_16; // x16 
SDL_Surface *speedSurface_32; // x32 
SDL_Surface *speedSurface_01_dark; // x1
SDL_Surface *speedSurface_04_dark; // x4 
SDL_Surface *speedSurface_16_dark; // x16 
SDL_Surface *speedSurface_32_dark; // x32 

//Skill Tree
SDL_Surface *skillPanelSurface; // skill panel background 
SDL_Surface *skillTreeChainSurface_Empty; // empty skill tree chain
SDL_Surface *skillTreeChainSurface_Skilled; // activated skill tree chain
SDL_Surface *skillTreeRootSurface_Empty; // empty skill tree root
SDL_Surface *skillTreeRootSurface_Skilled; // activated skill tree root
SDL_Surface *skillTreeItemSurface_01; // item 1 in skill tree
SDL_Surface *skillTreeItemSurface_02; // item 2 in skill tree
SDL_Surface *skillTreeItemSurface_03; // item 3 in skill tree
SDL_Surface *skillTreeItemSurface_04; // item 4 in skill tree
SDL_Surface *skillTreeSkillSurface_01; // skill 1 in skill tree
SDL_Surface *skillTreeSkillSurface_02; // skill 2 in skill tree
SDL_Surface *skillTreeSkillSurface_03; // skill 3 in skill tree
SDL_Surface *skillTreeSkillSurface_04; // skill 4 in skill tree
SDL_Surface *skillTreeSkillSurface_05; // skill 5 in skill tree
SDL_Surface *skillTreeSettingButtonSurface;	// setting button for skill tree

//font
SDL_Surface* g_pTextSurface = NULL;
TTF_Font* font_15 = NULL;
TTF_Font* font_20 = NULL;
TTF_Font* font_24 = NULL;
TTF_Font* font_30 = NULL;
TTF_Font* font_30_Bold = NULL;
TTF_Font* font_54 = NULL;
TTF_Font* font_48_Bold = NULL;

//Buttons
Button helpCategoryButton_01(20, 25, 200, 50);  //category: gameplay with skill tree
Button helpCategoryButton_02(230, 25, 200, 50); //category: resources
Button helpCategoryButton_04(850, 25, 200, 50); //category: items
Button helpCategoryButton_05(1060, 25, 200, 50); //back button
Button mainHelpButton(0, 0, 70, 70); //main menu help button
Button settingHelpButton(415, 150, 70, 70); //main menu help button
Button mainStartButton(0, 0, 1280, 720);	// main start button
Button settingButton(10, 10, 80, 80);
Button settingPanelCloseButton(808, 150, 60, 60);
Button musicUpButton(800, 305, 30, 30);
Button musicDownButton(450, 305, 30, 30);
Button effectUpButton(800, 405, 30, 30);
Button effectDownButton(450, 405, 30, 30);
Button resignButton(540, 465, 200, 50);
Button gameoverBackButton(540, 465, 200, 50);
Button signalUpButton(1220, 80, 30, 30);
Button signalDownButton(1180, 80, 30, 30);
Button extendButton(1200, 240, 80, 240);
Button itemButton_01(25, 550, 150, 150);
Button itemButton_02(210, 550, 150, 150);
Button itemButton_03(375, 550, 150, 150);
Button itemButton_04(550, 530, 150, 150);
Button pauseButton(1120, 580, 60, 60);
Button playButton(1200, 580, 60, 60);
Button speedButton_01(970, 650, 60, 60);
Button speedButton_04(1050, 650, 60, 60);
Button speedButton_16(1130, 650, 60, 60);
Button speedButton_32(1210, 650, 60, 60);
Button skillTreePanelCloseButton(1235, 12, 30, 30);
Button skillTreePanelSettingButton(10, 8, 36, 36);
Button skillTreeItemButton[4]{ Button {80,160,50,50}, Button {80,310,50,50}, Button {80,460,50,50}, Button {80,610,50,50} }; // item index, level
Button skillTreeSkillButton[5]{ Button {690,140,50,50}, Button {690,265,50,50}, Button {690,390,50,50}, Button {690,515,50,50}, Button {690,640,50,50} }; // skill index, level

// UI values
float temp_width;
float temp_height;
float menu_text_cd;
bool menu_text_show;

//Data, most values will be changed in the function "ResetStat()"
float temp_time;
float frames_per_gameHour = 0;
int musicLevel = 200;  //0-400
int effectLevel = 200; //0-400
Vector2D target_location = Vector2D(396.f, 266.f);
Vector2D station01 = Vector2D(191.f, 291.f);
Vector2D station02 = Vector2D(617.f, 185.f);
int readyStation;
int typhoonAnimCounter;
bool newsStop;
bool newsOutdate;
int news_typhoon_index = -1;
int newsMoveCounter;
int gamemode; // 0 = Menu, 1 = Game, 2 = Setting, 3 = Skill Tree, 4 = Game Over, 5 = Helping page
int help_category;
vector<int> last_gamemode; // 0 = Menu, 1 = Game, 2 = Setting, 3 = Skill Tree, 4 = Game Over, 5 = Helping page
bool typhoon_last_exist[5] = { false };
bool exitMenu;
bool enteredGame;
bool exitGame;
int second; // background calculation
int minute;
int hour; 
int day; // 1/5/2021 is sunday
int date;
int month;
int year;
int curSignal; //the signal which is showing now
int newSignal = 0; //the signal which is showing now
int curGameSpeed;
float sound_dist;
float popularityRating;
float last_popularityRating;
float hsi;
float display_hsi;
float temp_hsi;
float last_hsi;
float money;
float rad;
float injuries; // TODO
float deaths; // TODO
bool isPause;
float item01_cur_cd;
float item02_cur_cd;
float item03_cur_cd;
float item04_cur_cd;
float signal_cur_cd;
float item01_cd;
float item02_cd;
float item03_cd;
float item04_cd;
float signal_cd;
float item01_active;
float item02_active;
float item03_active;
float item04_active;
float item01_activeLength;
float item02_activeLength;
float item03_activeLength;
float item04_activeLength;
int item01_cost;
int item02_cost;
int item03_cost;
int item04_cost;
int curTyphoonCount;

//News: add some secret news for internal, such as some citizen died, so player can react to this news 
vector<string> default_typhoon_name = { // add names here
	"   Yinxing", "  Co-may", "  Nongfa", "  Ragasa", "    Koto", "  Nokaen", "    Yutu", "  Lekima", "   Faxai", "  Hagibis", " Kammuri", "Phanfone", "    Hato", "  Pakhar", "  ChaSiu", "  MilkTea"
}; // sample typhoon names
vector<int> typhoon_name_index;
int news_last_time; //number of gameloop
queue<string> cur_news;
string cur_show_news = "-    No news";
string next_show_news;
double news_x;
double news_y;
//Skill Tree Data
int itemLevel[4] = { 0, 0, 0, 0 }; //  { 0, 0, 0, 0 }
int skillLevel[5] = { 0, 0, 0, 0, 0 };
int upgradeItemMoney[4] = { 500000, 1000000, 1500000, 2000000, };
int upgradeItemRad[4] = { 10, 20, 30, 40 };
int upgradeSkillMoney[4] = { 500000, 1000000, 1500000, 2000000 };
int upgradeSkillRad[4] = { 10, 20, 30, 40 };
int upgradeItemDetails[4][5] = { { 0, 20, 25, 30, 35 },
								{ 0, 15, 20, 25, 30 },
								{ 0, 15, 24, 36, 48 },
								{ 0, 15, 20, 25, 30 } };
int upgradeSkillDetails[5][5] = { { 5, 10, 15, 20, 25 },
									 { 50000, 75000, 100000, 125000, 150000 },
									 { 55, 60, 65, 70, 75 },
									 { 10, 20, 30, 40, 50 },
									 { 0, 10, 20, 30, 40 } };

void ResetStat() {

	// UI values
	temp_width = 0;
	temp_height = 0;
	menu_text_cd = 0;
	menu_text_show = true;

	//Data
	last_gamemode.clear();
	readyStation = -1;
	typhoonAnimCounter = 0;
	newsStop = false;
	newsOutdate = false;
	newsMoveCounter = 0;
	gamemode = 0; // 0 = Menu, 1 = Game, 2 = Setting, 3 = Skill Tree, 4 = Game Over, 5 = Helping page
	exitMenu = false;
	enteredGame = false;
	exitGame = false;
	second = 0; // background calculation
	minute = 0;
	hour = 0; 
	day = 7; // 1/5/2021 is sunday
	date = 1;
	month = 5;
	year = 2022;
	curSignal = 0;
	curGameSpeed = 4;
	popularityRating = 50;
	last_popularityRating = popularityRating;
	hsi = 25000;
	display_hsi = hsi;
	temp_hsi = hsi;
	last_hsi = hsi;
	money = 5000000;
	rad = 50;
	injuries = 0; // TODO
	deaths = 0; // TODO
	isPause = false;
	item01_cur_cd = 30.0f;
	item02_cur_cd = 15.0f;
	item03_cur_cd = 10.0f;
	item04_cur_cd = 40.0f;
	signal_cur_cd = 7.5f;
	item01_cd = 30.0f;
	item02_cd = 15.0f;
	item03_cd = 10.0f;
	item04_cd = 30.0f;
	signal_cd = 2.5f;
	item01_active = 0.0f;
	item02_active = 0.0f;
	item03_active = 0.0f;
	item04_active = 0.0f;
	item01_activeLength = 5.0f;
	item02_activeLength = 5.0f;
	item03_activeLength = 5.0f;
	item04_activeLength = 5.0f;
	item01_cost = 500000;
	item02_cost = 500000;
	item03_cost = 1000000;
	item04_cost = 500000;
	curTyphoonCount = 0;
	news_last_time = 2500; //number of gameloop
	cur_show_news = "-    No news";
	news_x = 150;
	news_y = 0;
	//Skill Tree Data
	for (int i = 0; i < 4; i++) {
		skillTreeItemButton[i].set_x(80);
		itemLevel[i] = 0; //  { 0, 0, 0, 0 }
	}
	for (int i = 0; i < 5; i++) {
		skillTreeSkillButton[i].set_x(690);
		skillLevel[i] = 0; //  { 0, 0, 0, 0, 0 }
	}

	Mix_FadeInMusic(bgm, -1, 1000);

	// TODO: reset typhoons statistics
	//typhoons;
	//artificialTyphoon;

}

int InitImages()
{
	helpButtonSurface = SDL_LoadBMP("help_sign.bmp");

	mapSurface = SDL_LoadBMP("Map.bmp");
	blackSurface = SDL_LoadBMP("BlackBG.bmp");
	mainBGSurface = SDL_LoadBMP("Main_Back.bmp");
	mainBGSurface_NoLi = SDL_LoadBMP("Main_BackNoLi.bmp");
	settingButtonSurface = SDL_LoadBMP("Setting_Normal.bmp");
	extendButtonSurface = SDL_LoadBMP("Extend_Normal.bmp");
	defaultButtonSurface = SDL_LoadBMP("UI_Button01_Normal.bmp");
	defaultButtonSurface_clicked = SDL_LoadBMP("UI_Button01_Click.bmp");

	panelSurface = SDL_LoadBMP("Panel.bmp");
	helpPanelSurface = SDL_LoadBMP("HelpPanel.bmp");
	settinglevelSurface = SDL_LoadBMP("ScrollBar.bmp");
	closeButtonSurface = SDL_LoadBMP("PanelClose.bmp");
	closeLargeButtonSurface = SDL_LoadBMP("PanelCloseLarge.bmp");
	//mapLayerSurface_01 = SDL_LoadBMP("Layer_Cloud.bmp");
	//mapLayerSurface_02 = SDL_LoadBMP("Layer_Pressure.bmp");

	topBarBgSurface = SDL_LoadBMP("Bar_Top.bmp");
	newsBarBgSurface = SDL_LoadBMP("Bar_News.bmp");

	typhoonSurface_01 = SDL_LoadBMP("sprite_typhoon00.bmp");
	typhoonSurface_02 = SDL_LoadBMP("sprite_typhoon01.bmp");
	typhoonSurface_03 = SDL_LoadBMP("sprite_typhoon02.bmp");
	typhoonSurface_04 = SDL_LoadBMP("sprite_typhoon03.bmp");
	typhoonSurface_05 = SDL_LoadBMP("sprite_typhoon04.bmp");
	typhoonSurface_06 = SDL_LoadBMP("sprite_typhoon05.bmp");
	typhoonSurface_07 = SDL_LoadBMP("sprite_typhoon06.bmp");
	typhoonSurface_08 = SDL_LoadBMP("sprite_typhoon07.bmp");
	typhoonSurface_09 = SDL_LoadBMP("sprite_typhoon08.bmp");
	typhoonSurface_10 = SDL_LoadBMP("sprite_typhoon09.bmp");
	typhoonSurface_11 = SDL_LoadBMP("sprite_typhoon10.bmp");
	typhoonSurface_12 = SDL_LoadBMP("sprite_typhoon11.bmp");
	typhoonSurface_13 = SDL_LoadBMP("sprite_typhoon12.bmp");
	typhoonSurface_14 = SDL_LoadBMP("sprite_typhoon13.bmp");
	typhoonSurface_15 = SDL_LoadBMP("sprite_typhoon14.bmp");
	typhoonSurface_16 = SDL_LoadBMP("sprite_typhoon15.bmp");

	stationSurface_empty = SDL_LoadBMP("Station_Empty.bmp");
	stationSurface_ready = SDL_LoadBMP("Station_Ready.bmp");

	itemSurface_01 = SDL_LoadBMP("Item01.bmp");
	itemSurface_02 = SDL_LoadBMP("Item02.bmp");
	itemSurface_03 = SDL_LoadBMP("Item03.bmp");
	itemSurface_04 = SDL_LoadBMP("Item04.bmp");
	itemDisplaySurface_04 = SDL_LoadBMP("Li's.bmp");
	itemSurface_01_dark = SDL_LoadBMP("Item01_BW.bmp");
	itemSurface_02_dark = SDL_LoadBMP("Item02_BW.bmp");
	itemSurface_03_dark = SDL_LoadBMP("Item03_BW.bmp");
	itemSurface_04_dark = SDL_LoadBMP("Item04_BW.bmp");

	increaseIconSurface = SDL_LoadBMP("Positive.bmp");
	neutralIconSurface = SDL_LoadBMP("Neutral.bmp");
	decreaseIconSurface = SDL_LoadBMP("Negative.bmp");
	popularityRatingSurface = SDL_LoadBMP("Res_Citizen.bmp");
	hsiSurface = SDL_LoadBMP("Res_HSI.bmp");
	moneySurface = SDL_LoadBMP("Res_Money.bmp");
	moneySurface_grayscale = SDL_LoadBMP("Res_Money_BW.bmp");
	radSurface = SDL_LoadBMP("Res_RAD.bmp");
	popularityRatingSurface_large = SDL_LoadBMP("Res_Citizen_80.bmp");
	hsiSurface_large = SDL_LoadBMP("Res_HSI_80.bmp");
	moneySurface_large = SDL_LoadBMP("Res_Money_80.bmp");
	radSurface_large = SDL_LoadBMP("Res_RAD_80.bmp");

	signalSurface_01 = SDL_LoadBMP("Signal01.bmp");
	signalSurface_03 = SDL_LoadBMP("Signal03.bmp");
	signalSurface_08 = SDL_LoadBMP("Signal08.bmp");
	signalSurface_09 = SDL_LoadBMP("Signal09.bmp");
	signalSurface_10 = SDL_LoadBMP("Signal10.bmp");
	plusSurface = SDL_LoadBMP("SignalUp.bmp");
	minusSurface = SDL_LoadBMP("SignalDown.bmp");
	plusDisableSurface = SDL_LoadBMP("SignalUp_BW.bmp");
	minusDisableSurface = SDL_LoadBMP("SignalDown_BW.bmp");

	playSurface = SDL_LoadBMP("Play_Normal.bmp");
	pauseSurface = SDL_LoadBMP("Pause_Normal.bmp");
	playingSurface = SDL_LoadBMP("Play_Click.bmp");
	pausingSurface = SDL_LoadBMP("Pause_Click.bmp");

	speedSurface_01 = SDL_LoadBMP("Speed01.bmp");
	//speedSurface_02 = SDL_LoadBMP("Speed02.bmp");
	speedSurface_04 = SDL_LoadBMP("Speed04.bmp");
	//speedSurface_08 = SDL_LoadBMP("Speed08.bmp");
	speedSurface_16 = SDL_LoadBMP("Speed16.bmp");
	speedSurface_32 = SDL_LoadBMP("Speed32.bmp");
	speedSurface_01_dark = SDL_LoadBMP("Speed01_Dark.bmp");
	speedSurface_04_dark = SDL_LoadBMP("Speed04_Dark.bmp");
	speedSurface_16_dark = SDL_LoadBMP("Speed16_Dark.bmp");
	speedSurface_32_dark = SDL_LoadBMP("Speed32_Dark.bmp");

	skillPanelSurface = SDL_LoadBMP("WindowPanel.bmp");
	skillTreeChainSurface_Empty = SDL_LoadBMP("SkillTreeChain_Empty.bmp");
	skillTreeChainSurface_Skilled = SDL_LoadBMP("SkillTreeChain_Skilled.bmp");
	skillTreeRootSurface_Empty = SDL_LoadBMP("SkillTreeRoot_Empty.bmp");
	skillTreeRootSurface_Skilled = SDL_LoadBMP("SkillTreeRoot_Skilled.bmp");
	skillTreeItemSurface_01 = SDL_LoadBMP("Item01_Small.bmp");
	skillTreeItemSurface_02 = SDL_LoadBMP("Item02_Small.bmp");
	skillTreeItemSurface_03 = SDL_LoadBMP("Item03_Small.bmp");
	skillTreeItemSurface_04 = SDL_LoadBMP("Item04_Small.bmp");
	skillTreeSkillSurface_01 = SDL_LoadBMP("Skill01.bmp");
	skillTreeSkillSurface_02 = SDL_LoadBMP("Skill02.bmp");
	skillTreeSkillSurface_03 = SDL_LoadBMP("Skill03.bmp");
	skillTreeSkillSurface_04 = SDL_LoadBMP("Skill04.bmp");
	skillTreeSkillSurface_05 = SDL_LoadBMP("Skill05.bmp");
	skillTreeSettingButtonSurface = SDL_LoadBMP("Setting_Dark.bmp");

	typhoonSurface_01 = SDL_LoadBMP("sprite_typhoon00.bmp");
	typhoonSurface_02 = SDL_LoadBMP("sprite_typhoon01.bmp");
	typhoonSurface_03 = SDL_LoadBMP("sprite_typhoon02.bmp");
	typhoonSurface_04 = SDL_LoadBMP("sprite_typhoon03.bmp");
	typhoonSurface_05 = SDL_LoadBMP("sprite_typhoon04.bmp");
	typhoonSurface_06 = SDL_LoadBMP("sprite_typhoon05.bmp");
	typhoonSurface_07 = SDL_LoadBMP("sprite_typhoon06.bmp");
	typhoonSurface_08 = SDL_LoadBMP("sprite_typhoon07.bmp");
	typhoonSurface_09 = SDL_LoadBMP("sprite_typhoon08.bmp");
	typhoonSurface_10 = SDL_LoadBMP("sprite_typhoon09.bmp");
	typhoonSurface_11 = SDL_LoadBMP("sprite_typhoon10.bmp");
	typhoonSurface_12 = SDL_LoadBMP("sprite_typhoon11.bmp");
	typhoonSurface_13 = SDL_LoadBMP("sprite_typhoon12.bmp");
	typhoonSurface_14 = SDL_LoadBMP("sprite_typhoon13.bmp");
	typhoonSurface_15 = SDL_LoadBMP("sprite_typhoon14.bmp");
	typhoonSurface_16 = SDL_LoadBMP("sprite_typhoon15.bmp");

	SDL_SetColorKey(typhoonSurface_01, SDL_TRUE, SDL_MapRGB(typhoonSurface_01->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_02, SDL_TRUE, SDL_MapRGB(typhoonSurface_02->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_03, SDL_TRUE, SDL_MapRGB(typhoonSurface_03->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_04, SDL_TRUE, SDL_MapRGB(typhoonSurface_04->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_05, SDL_TRUE, SDL_MapRGB(typhoonSurface_05->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_06, SDL_TRUE, SDL_MapRGB(typhoonSurface_06->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_07, SDL_TRUE, SDL_MapRGB(typhoonSurface_07->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_08, SDL_TRUE, SDL_MapRGB(typhoonSurface_08->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_09, SDL_TRUE, SDL_MapRGB(typhoonSurface_09->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_10, SDL_TRUE, SDL_MapRGB(typhoonSurface_10->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_11, SDL_TRUE, SDL_MapRGB(typhoonSurface_11->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_12, SDL_TRUE, SDL_MapRGB(typhoonSurface_12->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_13, SDL_TRUE, SDL_MapRGB(typhoonSurface_13->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_14, SDL_TRUE, SDL_MapRGB(typhoonSurface_14->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_15, SDL_TRUE, SDL_MapRGB(typhoonSurface_15->format, 255, 255, 255));
	SDL_SetColorKey(typhoonSurface_16, SDL_TRUE, SDL_MapRGB(typhoonSurface_16->format, 255, 255, 255));

	return 0;
}

void LoadSound() {
	//Load music
	// code for the sound here==================
	bgm = Mix_LoadMUS("Sound\\BGM_Loyalty_Freak_Music_-_04_-_Cant_Stop_My_Feet_.wav");
	if (bgm == NULL) {
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else {
		Mix_VolumeMusic(32 * musicLevel / 400.f/ (gamemode + 1) / (gamemode + 1) / (gamemode + 1));
	}

	// code for the sound here==================
	//Load sound effects
	click_sound = Mix_LoadWAV("Sound\\Click_mixkit-game-ball-tap-2073.wav");
	if (click_sound == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(click_sound, 128 * effectLevel / 400.f);
	item01_sound = Mix_LoadWAV("Sound\\News_mixkit-digital-signal-interference-2548.wav");
	if (item01_sound == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(item01_sound, 128 * effectLevel / 400.f);
	item02_sound = Mix_LoadWAV("Sound\\Pulse_mixkit-synthetic-sci-fi-wobble-278.wav");
	if (item02_sound == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(item02_sound, 128 * effectLevel / 400.f);
	item03_sound = Mix_LoadWAV("Sound\\ArtTyphoon_mixkit-storm-wind-2411.wav");
	if (item03_sound == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(item03_sound, 128 * effectLevel / 400.f);
	item04_sound = Mix_LoadWAV("Sound\\LisField_mixkit-electricity-buzz-910.wav");
	if (item04_sound == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(item04_sound, 128 * effectLevel / 400.f);
	wind_sound_1 = Mix_LoadWAV("Sound\\WindStay1_mixkit-desertic-wind-1161.wav");
	if (wind_sound_1 == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(wind_sound_1, 128 * effectLevel / 400.f);
	wind_sound_2 = Mix_LoadWAV("Sound\\WindStay2_mixkit-coastal-outdoor-wind-1160.wav");
	if (wind_sound_2 == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(wind_sound_2, 128 * effectLevel / 400.f);
	lvlUp_sound = Mix_LoadWAV("Sound\\LvUp_mixkit-unlock-game-notification-253.wav");
	if (lvlUp_sound == NULL) {
		printf("Failed to load sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_VolumeChunk(lvlUp_sound, 128 * effectLevel / 400.f);

}

void UpdateSignal(bool upgrade) {

	if (upgrade) {
		switch (curSignal) {
		//case 0: newSignal = 8; break;
		case 0: newSignal = 1;  next_show_news = "-    [ News ]  StandBy!!!   A tropical Cyclone may be moving to Hong Kong"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break; //CHANGE: Trying only no 8, coz the typhoon is so fast in game
		case 1: newSignal = 3;  next_show_news = "-    [ News ]  Warning!!!   A tropical Cyclone is approaching Hong Kong"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break;
		case 3: newSignal = 8;  next_show_news = "-    [ News ]  Because of the typhoon, school and works were suspended"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break;
		case 8: newSignal = 9;  next_show_news = "-    [ News ]  The intensity of the typhoon is still increasing"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break;
		case 9: newSignal = 10;  next_show_news = "-    [ News ]  The typhoon makes huge damage to Hong Kong"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break;
		default: break;
		}
	}
	else {
		switch (curSignal) {
		case 1: newSignal = 0; next_show_news = "-    No News"; newsMoveCounter = news_last_time - 1; newsOutdate = true;  break;
		case 3: newSignal = 1;  next_show_news = "-    [ News ]  A tropical Cyclone has left far away from Hong Kong"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break;
		case 8: newSignal = 3;  next_show_news = "-    [ News ]  School and works resume"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break;
		//case 8: newSignal = 0; break;
		case 9: newSignal = 8;  next_show_news = "-    [ News ]  The typhoon starts weakening"; newsMoveCounter = news_last_time - 1; if (next_show_news != cur_show_news) newsOutdate = true; break;
		case 10: newSignal = 9;  next_show_news = "-    [ News ]  The typhoon starts weakening"; newsMoveCounter = news_last_time - 1; newsOutdate = true; break;
		default: break;
		}
	}
	signal_cur_cd = signal_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100;
}

string GenerateDate() {
	if (second >= 60) { // 60 seconds = 1 minute
		// rewards per minute
		rad += upgradeSkillDetails[0][skillLevel[0]] * (second / 60) / 14400.0;
		if (rad > 999.9f) rad = 999;
		money += upgradeSkillDetails[1][skillLevel[1]] * (second / 60) / 1440.0;
		if (money > 9999999) money = 9999999;
		if (((minute < 30 && minute + second / 60 >= 30) || minute + second / 60 >= 60)) last_hsi = display_hsi;// do every 30 mins
		minute += second / 60;
		second = second % 60;
		if (minute >= 60) { // 60 minutes = 1 
			frames_per_gameHour = temp_time / (minute / 60);
			temp_time = 0;
			last_popularityRating = popularityRating; // do every 60 mins
			hour += minute / 60;
			minute = minute % 60;
			if (hour >= 24) { // 24 hours = 1 day
				date++;
				day = day % 7 + 1;
				hour = 0;
				switch (month) { // different month has different max days
				case 2:
					if (date > 28) {
						month++;
						date = 1;
					}
					break;
				case 4: case 6:	case 9:	case 11:
					if (date > 30) {
						month++;
						date = 1;
					}
					break;
				default:
					if (date > 31) {
						month++;
						date = 1;
					}
					break;
				}
				// rewards per day
				if (month == 4 && date == 1) // rad per month will be 5 more since april
					for (int i = 0; i < 5; i++)
						upgradeSkillDetails[0][i] += 5;

				//Change: here to spawn typhoon
				//Check whether spawn in every day
				#pragma region spawn typhoon

				//
				if (rand() % 100 > 50 + abs(month - 8) * 5 + curTyphoonCount * 5) {
					for (int i = 0; i < 5; i++)
					{
						if (typhoons[i].get_exist()) continue;

						typhoons[i].set_exist(true);
						typhoons[i].set_pos(Vector2D(rand() % 440 + 400, rand() % 180 + 540));
						//typhoons[i].set_level(rand() % 5 + 2);//Do it inside the respawn function
						if (typhoon_name_index.empty()) {
							for (int i = 0; i < default_typhoon_name.size(); i++)
								typhoon_name_index.push_back(i);
						}
						typhoon_last_exist[i] = true;
						int rand_name_index = rand() % typhoon_name_index.size();
						typhoons[i].Respawn(typhoon_name_index[rand_name_index], (int)((month - 3) * 1.5));
						typhoon_name_index.erase(typhoon_name_index.begin() + rand_name_index);

						curTyphoonCount++;
						break;
					}
				}
				#pragma endregion
			}
		}
	}

	string dayString;
	switch (day) {
	case 1: dayString = "Monday"; break;
	case 2: dayString = "Tuesday"; break;
	case 3: dayString = "Wednesday"; break;
	case 4: dayString = "Thursday"; break;
	case 5: dayString = "Friday"; break;
	case 6: dayString = "Saturday"; break;
	case 7: dayString = "Sunday"; break;
	}

	string dateString = date < 10 ? "0" + to_string(date) : to_string(date);

	string monthString;
	switch (month) {
	case 1: monthString = "January"; break;
	case 2: monthString = "February"; break;
	case 3: monthString = "March"; break;
	case 4: monthString = "April"; break;
	case 5: monthString = "May"; break;
	case 6: monthString = "June"; break;
	case 7: monthString = "July"; break;
	case 8: monthString = "August"; break;
	case 9: monthString = "September"; break;
	case 10: monthString = "October"; break;
	case 11: monthString = "November"; break;
	case 12: monthString = "December"; break;
	}

	return dateString + " " + monthString + " " + to_string(year) + ", " + dayString;
}

//	DrawIMG() - Takes the SDL_Surface to blit at (x, y)
void DrawIMG(SDL_Surface *img, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	SDL_BlitSurface(img, NULL, g_pScreen, &dest);
}

// Draw text
void DrawTTF(string str, int x, int y, SDL_Color color, TTF_Font *font)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	g_pTextSurface = TTF_RenderText_Solid(font, str.c_str(), color);
	SDL_BlitSurface(g_pTextSurface, NULL, g_pScreen, &dest);

	//destroy text surface
	SDL_FreeSurface(g_pTextSurface);
	g_pTextSurface = NULL;
}

// override for drawing cd ing item
void DrawItemIMG(SDL_Surface *img, int x, int y, float percentageRate)
{
	SDL_Rect clip[1];
	clip[0].h = 150.f * percentageRate;
	clip[0].w = 150.f;
	clip[0].x = 0;
	clip[0].y = 150.f - clip[0].h;
	SDL_Rect dest;
	dest.x = x;
	dest.y = y + clip[0].y;

	SDL_BlitSurface(img, clip, g_pScreen, &dest);
}

void DrawGameMenu(float width, float height, bool showText, bool exit) {
	// draw background animation
	SDL_Rect src_temp;
	src_temp.x = 0;
	src_temp.y = 0;
	src_temp.w = 1280;
	src_temp.h = 720;
	if (!exit) {
		if (width < 1285) {
			src_temp.w = width;
			SDL_BlitSurface(mainBGSurface_NoLi, &src_temp, g_pScreen, NULL);
			DrawIMG(blackSurface, -width, 0);
			DrawIMG(blackSurface, 0, height);
			DrawIMG(blackSurface, 0, -height);
		}
		else if (height > 0) {
			src_temp.y = height;
			src_temp.h = 720 - height;
			SDL_Rect dest;
			dest.x = 0;
			dest.y = src_temp.y;
			SDL_BlitSurface(mainBGSurface, &src_temp, g_pScreen, &dest);
		}
		else { //end animation
			SDL_BlitSurface(mainBGSurface, NULL, g_pScreen, NULL);
			DrawTTF("Observatory", 50, 95, SDL_Color{ 220,220,220 }, font_54);
			DrawTTF("Simulator", 100, 180, SDL_Color{ 220,220,220 }, font_54);
			DrawTTF("Made By", 820, 180, SDL_Color{ 220,220,220 }, font_24);
			DrawTTF("Artist: Lam King Hoi", 900, 210, SDL_Color{ 220,220,220 }, font_24);
			DrawTTF("Programmer: Ho Tsun Him", 900, 240, SDL_Color{ 220,220,220 }, font_24);
			mainHelpButton.show(helpButtonSurface, g_pScreen);
			if (showText)
				DrawTTF("START", 535, 440, SDL_Color{ 255,165,0 }, font_54);
		}
	}
	else {
		SDL_BlitSurface(mainBGSurface, NULL, g_pScreen, NULL);
		DrawTTF("Observatory", 50, 95, SDL_Color{ 220,220,220 }, font_54);
		DrawTTF("Simulator", 100, 180, SDL_Color{ 220,220,220 }, font_54);
		DrawTTF("Made By", 820, 180, SDL_Color{ 220,220,220 }, font_24);
		DrawTTF("Artist: Lam King Hoi", 900, 210, SDL_Color{ 220,220,220 }, font_24);
		DrawTTF("Programmer: Ho Tsun Him", 900, 240, SDL_Color{ 220,220,220 }, font_24);
		if (showText)
			DrawTTF("START", 535, 440, SDL_Color{ 255,165,0 }, font_54);
		src_temp.w = width;
		SDL_BlitSurface(blackSurface, &src_temp, g_pScreen, NULL);
		if (width >= 900) {
			gamemode = 1;
		}
		DrawIMG(blackSurface, 1280 - width, 0);
		DrawIMG(blackSurface, 0, height - 720);
		DrawIMG(blackSurface, 0, 720 - height);

		Mix_VolumeMusic(32 * musicLevel / 400.f/ (gamemode + 1) / (gamemode + 1) / (gamemode + 1));
		//Mix_FadeOutMusic(1000);
	}
}

void DrawEnterGame(float width, float height) {
	// draw background animation
	SDL_Rect src_temp;
	src_temp.x = 1280 - width;
	src_temp.y = 0;
	src_temp.w = width;
	src_temp.h = 720;
	SDL_BlitSurface(blackSurface, &src_temp, g_pScreen, NULL);
	src_temp.x = 0;
	src_temp.y = 0;
	src_temp.w = 1280;
	src_temp.h = height;
	SDL_BlitSurface(blackSurface, &src_temp, g_pScreen, NULL);
}

void DrawUpdatingSignal(int oldSignal, int newSignal, int x, int y, float percentageRate) {
	SDL_Surface *oldSignalSurface = NULL;	
	switch (oldSignal) {
		case 1: oldSignalSurface = signalSurface_01; break;
		case 3: oldSignalSurface = signalSurface_03; break;
		case 8: oldSignalSurface = signalSurface_08; break;
		case 9: oldSignalSurface = signalSurface_09; break;
		case 10: oldSignalSurface = signalSurface_10; break;
		//default: printf("No Signal\n");
	}
	SDL_Surface *newSignalSurface = NULL;
	switch (newSignal) {
		case 1: newSignalSurface = signalSurface_01; break;
		case 3: newSignalSurface = signalSurface_03; break;
		case 8: newSignalSurface = signalSurface_08; break;
		case 9: newSignalSurface = signalSurface_09; break;
		case 10: newSignalSurface = signalSurface_10; break;
		//default: printf("No Signal\n");
	}
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	// draw background animation
	SDL_Rect src_temp;
	src_temp.x = 0;
	src_temp.w = 80;

	src_temp.y = 0;
	src_temp.h = 80 - 80 * percentageRate;
	SDL_BlitSurface(oldSignalSurface, &src_temp, g_pScreen, &dest);

	src_temp.y = 80 - 80 * percentageRate;
	src_temp.h = 80 * percentageRate;
	dest.y = y + src_temp.y;
	SDL_BlitSurface(newSignalSurface, &src_temp, g_pScreen, &dest);
}

void DrawBarImg(SDL_Surface *img, int x, int y, float percentageRate) {

	SDL_Rect clip[1];
	clip[0].h = 30.f;
	clip[0].w = 300.f * percentageRate;
	clip[0].x = 0;
	clip[0].y = 0;
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;

	//
	//  SDL_BlitSurface() to blit the image onto the screen surface
	//  Syntax: 
	//	int SDL_BlitSurface(SDL_Surface *src, SDL_Rect *srcrect, 
	//						SDL_Surface *dst, SDL_Rect *dstrect);
	//	where
	//		src is the surface to blit 
	//		dst is the surface to blit to 
	//		srcrect specifies what part of the source surface to blit 
	//		dstrect specifies where to blit it
	//
	//	If you type in NULL as the second parameter (srcrect), 
	//	then the entire source image is blitted.
	//
	//	The x and y of dstrect specify where to blit the SDL_Surface src. 
	//	With dstrect the width and the height are ignored.
	//
	//	SDL_Rect is a structure that contains 4 16-bit integers: 
	//		x, y, w (width) and h (height)
	//
	SDL_BlitSurface(img, clip, g_pScreen, &dest);
}

void DrawSetting() {
	// draw background animation
	DrawIMG(panelSurface, 415, 150);
	settingHelpButton.show(helpButtonSurface, g_pScreen);
	settingPanelCloseButton.show(closeLargeButtonSurface, g_pScreen);
	DrawTTF("Settings", 490, 180, SDL_Color{ 0,0,0 }, font_54);
	if (musicLevel <= 0)
		musicDownButton.show(minusDisableSurface, g_pScreen);
	else musicDownButton.show(minusSurface, g_pScreen);
	if (musicLevel >= 400)
		musicUpButton.show(plusDisableSurface, g_pScreen);
	else musicUpButton.show(plusSurface, g_pScreen);
	if (effectLevel <= 0)
		effectDownButton.show(minusDisableSurface, g_pScreen);
	else effectDownButton.show(minusSurface, g_pScreen);
	if (effectLevel >= 400)
		effectUpButton.show(plusDisableSurface, g_pScreen);
	else effectUpButton.show(plusSurface, g_pScreen);
	resignButton.show(defaultButtonSurface, g_pScreen);
	DrawTTF("Resign", 580, 470, SDL_Color{ 0,0,0 }, font_30);
	DrawBarImg(settinglevelSurface, 490, 305, musicLevel / 400.0f);
	DrawBarImg(settinglevelSurface, 490, 405, effectLevel / 400.0f);
	DrawTTF("Music", 602, 260, SDL_Color{ 0,0,0 }, font_24);
	DrawTTF("Effect", 587, 360, SDL_Color{ 0,0,0 }, font_24);
}

void DrawGameOver() {
	// draw background animation
	DrawIMG(panelSurface, 415, 150);
	DrawTTF("Game Over", 475, 180, SDL_Color{ 0,0,0 }, font_54);
	DrawTTF("Final Statistics", 525, 255, SDL_Color{ 0,0,0 }, font_24);
	int temp_x = 0;
	if (popularityRating < 1) {
		temp_x = 490;
		DrawTTF("Status: Resign - low popularity", temp_x, 300, SDL_Color{ 0,0,0 }, font_15); // resign
	}
	else if (display_hsi < 15000) {
		temp_x = 495;
		DrawTTF("Status: Being sacked - low HSI", temp_x, 300, SDL_Color{ 0,0,0 }, font_15); // being sacked
	}
	else if (month > 11) {
		temp_x = 455;
		DrawTTF("Status: Completed half year service", temp_x, 300, SDL_Color{ 0,0,0 }, font_15); // finish 1 year
	}
	else {
		temp_x = 485;
		DrawTTF("Status: Resign - personal reason", temp_x, 300, SDL_Color{ 0,0,0 }, font_15); // resign, give up
	}
	DrawTTF("Total Deaths: " + to_string((int)deaths), temp_x, 330, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Total Injuries: " + to_string((int)injuries), temp_x, 360, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Final Hang Seng Index: " + to_string(display_hsi).substr(0, 8), temp_x, 390, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Final Popularity Rating: " + to_string((int)popularityRating).append("%"), temp_x, 420, SDL_Color{ 0,0,0 }, font_15);
	gameoverBackButton.show(defaultButtonSurface, g_pScreen);
	DrawTTF("Back To Menu", 547, 470, SDL_Color{ 0,0,0 }, font_24);
}

void DrawCloseGame(float width, float height) { // close the game from gameover 

	if (width >= 900) {
		// reset every stat
		ResetStat();
		gamemode = 0;
	}
	SDL_Rect src_temp;
	src_temp.x = 0;
	src_temp.y = 0;
	src_temp.w = width;
	src_temp.h = 720;
	SDL_BlitSurface(blackSurface, &src_temp, g_pScreen, NULL);
	DrawIMG(blackSurface, 1280 - width, 0);
	DrawIMG(blackSurface, 0, height - 720);
	DrawIMG(blackSurface, 0, 720 - height);
}

void DrawSkillTreeChainAndRoot(int x[3], int y, int level) {

	if (level < 1)
		; // DrawIMG(skillTreeRootSurface_Empty, x[0], y);
	else DrawIMG(skillTreeRootSurface_Skilled, x[0], y);
	if (level < 2)
		DrawIMG(skillTreeChainSurface_Empty, x[0], y);
	else DrawIMG(skillTreeChainSurface_Skilled, x[0], y);
	if (level < 3)
		DrawIMG(skillTreeChainSurface_Empty, x[1], y);
	else DrawIMG(skillTreeChainSurface_Skilled, x[1], y);
	if (level < 4)
		DrawIMG(skillTreeChainSurface_Empty, x[2], y);
	else DrawIMG(skillTreeChainSurface_Skilled, x[2], y);
	return;
}

void DrawSkillTree()
{
	// draw background
	SDL_Rect src_temp;
	src_temp.x = 0;
	src_temp.y = 0;
	src_temp.w = 1280;
	src_temp.h = 720;
	SDL_BlitSurface(skillPanelSurface, &src_temp, g_pScreen, NULL);

	// Draw each object
	skillTreePanelCloseButton.show(closeButtonSurface, g_pScreen);
	skillTreePanelSettingButton.show(skillTreeSettingButtonSurface, g_pScreen);
	for (int i = 0; i < 4; i++) {
		if (itemLevel[i] < 4)
			skillTreeItemButton[i].show(skillTreeRootSurface_Empty, g_pScreen);
	}
	for (int i = 0; i < 5; i++) {
		if (skillLevel[i] < 4)
			skillTreeSkillButton[i].show(skillTreeRootSurface_Empty, g_pScreen);
	}

	//DrawIMG(closeButtonSurface, 1235, 12); 
	//DrawIMG(skillTreeSettingButtonSurface, 10, 8);
	DrawTTF((hour < 10 ? "0" + to_string(hour) : to_string(hour)) + ":" + (minute < 10 ? "0" + to_string(minute) : to_string(minute)), 130, 6, SDL_Color{ 0,0,0 }, font_30);
	DrawTTF(GenerateDate(), 240, 12, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(popularityRatingSurface, 595, 10);
	if (popularityRating > last_popularityRating)
		DrawIMG(increaseIconSurface, 630, 15);
	else if (popularityRating < last_popularityRating)
		DrawIMG(decreaseIconSurface, 630, 15);
	else
		DrawIMG(neutralIconSurface, 630, 15);
	DrawTTF(to_string((int)popularityRating).append("%"), 655, 12, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(hsiSurface, 725, 10);
	if (display_hsi > last_hsi)
		DrawIMG(increaseIconSurface, 760, 15);
	else if (display_hsi < last_hsi)
		DrawIMG(decreaseIconSurface, 760, 15);
	else
		DrawIMG(neutralIconSurface, 760, 15);
	DrawTTF(to_string(display_hsi).substr(0, 8), 785, 12, SDL_Color{ 0,0,0 }, font_20); //5 digits + "." + 2 decimal place = 8 digits
	DrawIMG(moneySurface, 895, 10);
	DrawTTF("$" + to_string((int)money), 930, 12, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 1055, 10);
	DrawTTF(to_string(rad).substr(0, to_string(rad).find('.') + 2), 1085, 12, SDL_Color{ 0,0,0 }, font_20);

	DrawIMG(skillTreeItemSurface_01, 60, 80);
	DrawTTF("News Deceiver", 155, 80, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + (itemLevel[0] < 1 ? "Undeveloped" : to_string(upgradeItemDetails[0][itemLevel[0]]) + " hours"), 155, 115, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (itemLevel[0] != 4 ? to_string(upgradeItemDetails[0][itemLevel[0] + 1]) + " hours" : " / "), 155, 135, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 440, 85);
	DrawTTF((itemLevel[0] != 4 ? "$" + to_string(upgradeItemMoney[itemLevel[0]]) : " / "), 475, 85, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 440, 125);
	DrawTTF((itemLevel[0] != 4 ? to_string(upgradeItemRad[itemLevel[0]]) : " / "), 475, 125, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 80, 230, 380 }, 160, itemLevel[0]);

	DrawIMG(skillTreeItemSurface_02, 70, 230);
	DrawTTF("Typhoon Intensity Attenuator", 155, 230, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + (itemLevel[1] < 1 ? "Undeveloped" : "Level " + to_string(itemLevel[1])), 155, 265, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (itemLevel[1] != 4 ? "Level " + to_string(itemLevel[1] + 1) : " / "), 155, 285, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 440, 235);
	DrawTTF((itemLevel[1] != 4 ? "$" + to_string(upgradeItemMoney[itemLevel[1]]) : " / "), 475, 235, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 440, 275);
	DrawTTF((itemLevel[1] != 4 ? to_string(upgradeItemRad[itemLevel[1]]) : " / "), 475, 275, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 80, 230, 380 }, 310, itemLevel[1]);

	DrawIMG(skillTreeItemSurface_03, 60, 380);
	DrawTTF("Artificial Typhoon Generator", 155, 380, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + (itemLevel[2] < 1 ? "Undeveloped" : to_string(upgradeItemDetails[2][itemLevel[2]]) + " hours"), 155, 415, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (itemLevel[2] != 4 ? to_string(upgradeItemDetails[2][itemLevel[2] + 1]) + " hours" : " / "), 155, 435, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 440, 385);
	DrawTTF((itemLevel[2] != 4 ? "$" + to_string(upgradeItemMoney[itemLevel[2]]) : " / "), 475, 385, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 440, 425);
	DrawTTF((itemLevel[2] != 4 ? to_string(upgradeItemRad[itemLevel[2]]) : " / "), 475, 425, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 80, 230, 380 }, 460, itemLevel[2]);

	DrawIMG(skillTreeItemSurface_04, 60, 530);
	DrawTTF("Li's Field", 155, 530, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + (itemLevel[3] < 1 ? "Undeveloped" : to_string(upgradeItemDetails[3][itemLevel[3]]) + " hours"), 155, 565, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (itemLevel[3] != 4 ? to_string(upgradeItemDetails[3][itemLevel[3] + 1]) + " hours" : " / "), 155, 585, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 440, 535);
	DrawTTF((itemLevel[3] != 4 ? "$" + to_string(upgradeItemMoney[itemLevel[3]]) : " / "), 475, 535, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 440, 575);
	DrawTTF((itemLevel[3] != 4 ? to_string(upgradeItemRad[itemLevel[3]]) : " / "), 475, 575, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 80, 230, 380 }, 610, itemLevel[3]);

	DrawIMG(skillTreeSkillSurface_01, 680, 75);
	DrawTTF("R&D Investment Upgrade", 750, 70, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + to_string(upgradeSkillDetails[0][skillLevel[0]] / 10.0f).substr(0, 3) + "/day", 750, 100, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (skillLevel[0] != 4 ? to_string(upgradeSkillDetails[0][skillLevel[0] + 1] / 10.0f).substr(0, 3) + "/day" : " / "), 750, 120, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 1050, 75);
	DrawTTF((skillLevel[0] != 4 ? "$" + to_string(upgradeSkillMoney[skillLevel[0]]) : " / "), 1085, 75, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 1050, 115);
	DrawTTF((skillLevel[0] != 4 ? to_string(upgradeSkillRad[skillLevel[0]]) : " / "), 1085, 115, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 690, 840, 990 }, 140, skillLevel[0]);

	DrawIMG(skillTreeSkillSurface_02, 680, 200);
	DrawTTF("Income Increment", 750, 195, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + to_string(upgradeSkillDetails[1][skillLevel[1]]) + "/day", 750, 225, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (skillLevel[1] != 4 ? to_string(upgradeSkillDetails[1][skillLevel[1] + 1]) + "/day" : " / "), 750, 245, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 1050, 200);
	DrawTTF((skillLevel[1] != 4 ? "$" + to_string(upgradeSkillMoney[skillLevel[1]]) : " / "), 1085, 200, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 1050, 240);
	DrawTTF((skillLevel[1] != 4 ? to_string(upgradeSkillRad[skillLevel[1]]) : " / "), 1085, 240, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 690, 840, 990 }, 265, skillLevel[1]);

	DrawIMG(skillTreeSkillSurface_03, 680, 325);
	DrawTTF("Prediction Accuracy Upgrade", 750, 320, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + to_string(upgradeSkillDetails[2][skillLevel[2]]) + "%", 750, 350, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (skillLevel[2] != 4 ? to_string(upgradeSkillDetails[2][skillLevel[2] + 1]) + "%" : " / "), 750, 370, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 1050, 325);
	DrawTTF((skillLevel[2] != 4 ? "$" + to_string(upgradeSkillMoney[skillLevel[2]]) : " / "), 1085, 325, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 1050, 365);
	DrawTTF((skillLevel[2] != 4 ? to_string(upgradeSkillRad[skillLevel[2]]) : " / "), 1085, 365, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 690, 840, 990 }, 390, skillLevel[2]);

	DrawIMG(skillTreeSkillSurface_04, 680, 450);
	DrawTTF("Prediction Time Upgrade", 750, 445, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: " + to_string(upgradeSkillDetails[3][skillLevel[3]]) + " hours", 750, 475, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: " + (skillLevel[3] != 4 ? to_string(upgradeSkillDetails[3][skillLevel[3] + 1]) + " hours" : " / "), 750, 495, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 1050, 450);
	DrawTTF((skillLevel[3] != 4 ? "$" + to_string(upgradeSkillMoney[skillLevel[3]]) : " / "), 1085, 450, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 1050, 490);
	DrawTTF((skillLevel[3] != 4 ? to_string(upgradeSkillRad[skillLevel[3]]) : " / "), 1085, 490, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 690, 840, 990 }, 515, skillLevel[3]);

	DrawIMG(skillTreeSkillSurface_05, 680, 575);
	DrawTTF("Cooldown Reduction", 750, 570, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Current Level: -" + to_string(upgradeSkillDetails[4][skillLevel[4]]) + "%", 750, 600, SDL_Color{ 0,0,0 }, font_15);
	DrawTTF("Next Level: -" + (skillLevel[4] != 4 ? to_string(upgradeSkillDetails[4][skillLevel[4] + 1]) + "%" : " / "), 750, 620, SDL_Color{ 0,0,0 }, font_15);
	DrawIMG(moneySurface, 1050, 575);
	DrawTTF((skillLevel[4] != 4 ? "$" + to_string(upgradeSkillMoney[skillLevel[4]]) : " / "), 1085, 575, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 1050, 615);
	DrawTTF((skillLevel[4] != 4 ? to_string(upgradeSkillRad[skillLevel[4]]) : " / "), 1085, 615, SDL_Color{ 0,0,0 }, font_20);
	DrawSkillTreeChainAndRoot(new int[3]{ 690, 840, 990 }, 640, skillLevel[4]);
}

void DrawHelpPage() {
	DrawIMG(helpPanelSurface, 0, 0);
	if (help_category == 0)
		helpCategoryButton_01.show(defaultButtonSurface_clicked, g_pScreen);
	else helpCategoryButton_01.show(defaultButtonSurface, g_pScreen);
	DrawTTF("Gameplay", 52, 30 + (help_category == 0 ? 5 : 0), SDL_Color{ 0,0,0 }, font_24);
	if (help_category == 1)
		helpCategoryButton_02.show(defaultButtonSurface_clicked, g_pScreen);
	else helpCategoryButton_02.show(defaultButtonSurface, g_pScreen);
	DrawTTF("Resources", 255, 30 + (help_category == 1 ? 5 : 0), SDL_Color{ 0,0,0 }, font_24);
	DrawTTF("HOW TO PLAY", 445, 20, SDL_Color{ 0,0,0 }, font_48_Bold);
	if (help_category == 3)
		helpCategoryButton_04.show(defaultButtonSurface_clicked, g_pScreen);
	else helpCategoryButton_04.show(defaultButtonSurface, g_pScreen);
	DrawTTF("Items/Skills", 862, 30 + (help_category == 3 ? 5 : 0), SDL_Color{ 0,0,0 }, font_24);
	helpCategoryButton_05.show(defaultButtonSurface, g_pScreen);
	DrawTTF("Back", 1125, 30, SDL_Color{ 0,0,0 }, font_24);

	//help_category = 1;
	if (help_category == 0) {
		SDL_Surface *typhoonSurface_toBeDrawn = typhoonSurface_01;
		switch (typhoonAnimCounter % 480 / 30) {
		case 0: typhoonSurface_toBeDrawn = typhoonSurface_01; break;
		case 1: typhoonSurface_toBeDrawn = typhoonSurface_02; break;
		case 2: typhoonSurface_toBeDrawn = typhoonSurface_03; break;
		case 3: typhoonSurface_toBeDrawn = typhoonSurface_04; break;
		case 4: typhoonSurface_toBeDrawn = typhoonSurface_05; break;
		case 5: typhoonSurface_toBeDrawn = typhoonSurface_06; break;
		case 6: typhoonSurface_toBeDrawn = typhoonSurface_07; break;
		case 7: typhoonSurface_toBeDrawn = typhoonSurface_08; break;
		case 8: typhoonSurface_toBeDrawn = typhoonSurface_09; break;
		case 9: typhoonSurface_toBeDrawn = typhoonSurface_10; break;
		case 10: typhoonSurface_toBeDrawn = typhoonSurface_11; break;
		case 11: typhoonSurface_toBeDrawn = typhoonSurface_12; break;
		case 12: typhoonSurface_toBeDrawn = typhoonSurface_13; break;
		case 13: typhoonSurface_toBeDrawn = typhoonSurface_14; break;
		case 14: typhoonSurface_toBeDrawn = typhoonSurface_15; break;
		case 15: typhoonSurface_toBeDrawn = typhoonSurface_16; break;
		default: printf("Error on typhoon surface"); break;
		}
		DrawTTF("Game", 580, 120, SDL_Color{ 0,0,0 }, font_30_Bold);
		// gameplay		
		DrawIMG(typhoonSurface_toBeDrawn, 1040, 280);
		DrawTTF("- This game is a simulator of observatory", 100, 175, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- Act as the director of the Hong Kong Observatory ( half year terms of service )", 117, 200, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- There are multiple data that you need to take care:", 100, 240, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- popularity ratings, hang seng index, funds, R&D points, and news", 117, 265, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- data will influence each other  ( e.g.  bad news => popularity ratings    )", 117, 290, SDL_Color{ 0,0,0 }, font_20);
		DrawIMG(decreaseIconSurface, 960, 292);
		DrawTTF("- Losing Condition:", 100, 330, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- Popularity ratings is less than 0% / Hang Seng Index is less than 20000", 117, 355, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- Finish the half year terms of service ( 1 May 2022 - 30 November 2022 ):", 100, 395, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- become one of the Honorary Director of the Hong Kong observatory", 117, 420, SDL_Color{ 0,0,0 }, font_20);

		// skill tree
		DrawTTF("Skill Tree", 500, 475, SDL_Color{ 0,0,0 }, font_30_Bold);
		DrawTTF("- The skill tree shows all upgrading progress of items and skills", 100, 530, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- You can develop and upgrade items and skills by consuming funds and r&d points", 100, 570, SDL_Color{ 0,0,0 }, font_20);
		DrawTTF("- Different items and skills can provide different benefits to your gameplay", 100, 610, SDL_Color{ 0,0,0 }, font_20);
		DrawIMG(skillTreeRootSurface_Empty, 365, 650);
		DrawSkillTreeChainAndRoot(new int[3]{ 365, 515, 665 }, 650, typhoonAnimCounter % 800 / 160 );

	}
	else if (help_category == 1) {
		// Resources
		// Resources 1: popularity ratings
		// Resources 2: hsi
		// Resources 3: money 
		// Resources 4: R&D investment points

		DrawTTF("Resources", 530, 120, SDL_Color{ 0,0,0 }, font_30_Bold);
		DrawIMG(popularityRatingSurface_large, 130, 190);
		DrawTTF("Popularity Ratings", 230, 180, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Shows the supportiveness of the observatory", 230, 220, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Will be affected by the Appropriateness of hoisted tropical cyclone warning signal", 230, 240, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Increase slowly on normal days", 242, 260, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Decrease when any typhoon is approaching Hong Kong, and depends on the intensity of the typhoon", 242, 280, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(hsiSurface_large, 130, 335);
		DrawTTF("Hang Seng Index ( HSI )", 230, 320, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Shows the changes of the stock-market", 230, 360, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Will be updated at 9:15 a.m. - 12:00 noon and 1:00 p.m. - 4:30 p.m. on every Monday to Friday", 230, 380, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Increase when no tropical cyclone warning signal is hoisting", 242, 400, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Decrease when hoisting any tropical cyclone warning signal, and depends on the level of the signal", 242, 420, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(moneySurface_large, 130, 475);
		DrawTTF("Funds", 230, 460, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Shows the amount of funds that the government gives to the observatory", 230, 500, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Increase over time, can gain more by upgrading skill", 230, 520, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Require when using any items and developing any items and skills", 230, 540, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(radSurface_large, 130, 595);
		DrawTTF("Research and development investment points ( R&D )", 230, 580, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- use to make Research and development investment in the observatory", 230, 620, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Increase over time, can gain more by upgrading skill", 230, 640, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Require when developing any items and skills", 230, 660, SDL_Color{ 0,0,0 }, font_15);
	}
	else if (help_category == 3) {
		// Items & Skills
		//Item 1 (news deceiver): Reduce the impact of news on people's popularity
		//Item 2: Reduce the intensity of the typhoon
		//Item 3: Generate an artificial typhoon in random place (may produce the Fujiwara effect)
		//Item 4 (Li's Field) : When using when the typhoon approaches Hong Kong, can effectively change the direction of the typhoon

		DrawTTF("Items", 290, 120, SDL_Color{ 0,0,0 }, font_30_Bold);
		DrawIMG(skillTreeItemSurface_01, 60, 190);
		DrawTTF("New's Deceiver", 150, 190, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Reduce the impact of news on people's popularity", 150, 230, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Block all news about deaths and injuries", 150, 250, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeItemSurface_02, 60, 315);
		DrawTTF("Typhoon Intensity Attenuator", 150, 315, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Reduce the intensity of all current typhoons", 150, 355, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeItemSurface_03, 60, 440);
		DrawTTF("Artificial Typhoon Creator", 150, 440, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Generate an artificial typhoon in one of the", 150, 480, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("two generating station when it is ready", 162, 500, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("- Can Produce the Fujiwhara effect", 150, 520, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeItemSurface_04, 60, 565);
		DrawTTF("Li's Field", 150, 565, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Can effectively change the direction of typhoons", 150, 605, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("when they approaches Hong Kong", 162, 625, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeSkillSurface_01, 680, 185);

		DrawTTF("Skills", 885, 120, SDL_Color{ 0,0,0 }, font_30_Bold);
		DrawTTF("R&D Investment Upgrade", 760, 190, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Increase R&D investment points getting per day", 760, 230, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeSkillSurface_02, 680, 295);
		DrawTTF("Income Increment", 760, 295, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Increase money income per day", 760, 335, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeSkillSurface_03, 680, 400);
		DrawTTF("Prediction Accuracy Upgrade", 760, 400, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Increase the prediction accuracy of typhoons", 760, 440, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeSkillSurface_04, 680, 505);
		DrawTTF("Prediction Range Upgrade", 760, 505, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Increase the prediction range of typhoons", 760, 545, SDL_Color{ 0,0,0 }, font_15);
		DrawIMG(skillTreeSkillSurface_05, 680, 610);
		DrawTTF("Cooldown Reduction", 760, 605, SDL_Color{ 0,0,0 }, font_24);
		DrawTTF("- Reduce the cooldown of all items and hoisting", 760, 645, SDL_Color{ 0,0,0 }, font_15);
		DrawTTF("tropical cyclone warning signal", 772, 665, SDL_Color{ 0,0,0 }, font_15);
	}
	else printf("help category error");
}

void DrawMainGameplay()
{

	// draw background
	SDL_Rect src_temp;
	src_temp.x = 0;
	src_temp.y = 0;
	src_temp.w = 1280;
	src_temp.h = 720;
	SDL_BlitSurface(mapSurface, &src_temp, g_pScreen, NULL);


	SDL_Surface *typhoonSurface_toBeDrawn = typhoonSurface_01;
	switch (typhoonAnimCounter % 480 / 30) {
	case 0: typhoonSurface_toBeDrawn = typhoonSurface_01; break;
	case 1: typhoonSurface_toBeDrawn = typhoonSurface_02; break;
	case 2: typhoonSurface_toBeDrawn = typhoonSurface_03; break;
	case 3: typhoonSurface_toBeDrawn = typhoonSurface_04; break;
	case 4: typhoonSurface_toBeDrawn = typhoonSurface_05; break;
	case 5: typhoonSurface_toBeDrawn = typhoonSurface_06; break;
	case 6: typhoonSurface_toBeDrawn = typhoonSurface_07; break;
	case 7: typhoonSurface_toBeDrawn = typhoonSurface_08; break;
	case 8: typhoonSurface_toBeDrawn = typhoonSurface_09; break;
	case 9: typhoonSurface_toBeDrawn = typhoonSurface_10; break;
	case 10: typhoonSurface_toBeDrawn = typhoonSurface_11; break;
	case 11: typhoonSurface_toBeDrawn = typhoonSurface_12; break;
	case 12: typhoonSurface_toBeDrawn = typhoonSurface_13; break;
	case 13: typhoonSurface_toBeDrawn = typhoonSurface_14; break;
	case 14: typhoonSurface_toBeDrawn = typhoonSurface_15; break;
	case 15: typhoonSurface_toBeDrawn = typhoonSurface_16; break;
	default: printf("Error on typhoon surface"); break;
	}

	// Draw Station
	if(readyStation != 0)
		DrawIMG(stationSurface_empty, station01.getX() - 16, station01.getY() - 16);
	else
		DrawIMG(stationSurface_ready, station01.getX() - 16, station01.getY() - 16);

	if (readyStation != 1)
		DrawIMG(stationSurface_empty, station02.getX() - 16, station02.getY() - 16);
	else
		DrawIMG(stationSurface_ready, station02.getX() - 16, station02.getY() - 16);

	// Draw Typhoon
	for (int i = 0; i < 5; i++) {
		if (typhoons[i].get_exist()) {

			if (typhoons[i].soundIndex == 0) {
				if (!Mix_Playing(i * 2))
					Mix_PlayChannel(i * 2, wind_sound_1, -1);
			}
			else {
				if (!Mix_Playing(i * 2 + 1))
					Mix_PlayChannel(i * 2 + 1, wind_sound_2, -1);
			}
			
			// 128 = default sound volume(1x voice), effectLevel / 400.f = customize volume size(percentage)
			sound_dist = 400 - Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos()));
			if (sound_dist < 0) sound_dist = 0;
			//cout << sound_dist <<endl;
			sound_dist *= typhoons[i].get_level() / 6.f;
			if (typhoons[i].soundIndex == 0)
				Mix_Volume(i * 2, 128 * effectLevel / 400.f * sound_dist / 400.f);
			else
				Mix_Volume(i * 2 + 1, 128 * effectLevel / 400.f * sound_dist / 400.f);
			typhoons[i].render(typhoonSurface_toBeDrawn, g_pScreen);

			DrawTTF(default_typhoon_name[typhoons[i].get_name_index()], typhoons[i].get_pos().getX() - 70, typhoons[i].get_pos().getY() + 20, 
				SDL_Color{Uint8(typhoons[i].get_level() > 6 ? 255 : 255 - 255 * (6 - typhoons[i].get_level()) / 6), Uint8(typhoons[i].get_level() <= 6 ? 255 : 255 * (12 - typhoons[i].get_level()) / 6),0 }, font_24);
		}
		else {
			if (typhoon_last_exist[i]) {
				typhoon_last_exist[i] = false;
				if (typhoons[i].soundIndex == 0)
					Mix_FadeOutChannel(i * 2, 500 + 500.f / curGameSpeed);
				else
					Mix_FadeOutChannel(i * 2 + 1, 500 + 500.f / curGameSpeed);
			}
		}
	}

	// Draw each object
	settingButton.show(settingButtonSurface, g_pScreen);
	if (curSignal != 10 && curSignal == newSignal)
	//if (curSignal != 8 && curSignal == newSignal)
		signalUpButton.show(plusSurface, g_pScreen);
	else
		DrawIMG(plusDisableSurface, 1220, 80);
	if (curSignal != 0 && curSignal == newSignal)
		signalDownButton.show(minusSurface, g_pScreen);
	else
		DrawIMG(minusDisableSurface, 1180, 80);
	extendButton.show(extendButtonSurface, g_pScreen);

	if (item01_cur_cd > 0.0f || itemLevel[0] == 0) {
		DrawIMG(itemSurface_01_dark, 25, 550);
		DrawItemIMG(itemSurface_01, 25, 550, (item01_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100 - item01_cur_cd) / (item01_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100));
	}
	else
		itemButton_01.show(itemSurface_01, g_pScreen);
	if (item01_cur_cd > 0.0f || money - item01_cost < 0) {
		DrawIMG(moneySurface_grayscale, 40, 680);
		DrawTTF(to_string(item01_cost), 75, 680, SDL_Color{ 128,128,128 }, font_20);
	}
	else {
		DrawIMG(moneySurface, 40, 680);
		DrawTTF(to_string(item01_cost), 75, 680, SDL_Color{ 200,100,0 }, font_20);
	}

	if (item02_cur_cd > 0.0f || itemLevel[1] == 0) {
		DrawIMG(itemSurface_02_dark, 210, 550);
		DrawItemIMG(itemSurface_02, 210, 550, (item02_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100 - item02_cur_cd) / (item02_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100));
	}
	else
		itemButton_02.show(itemSurface_02, g_pScreen);
	if (item02_cur_cd > 0.0f || money - item02_cost < 0) {
		DrawIMG(moneySurface_grayscale, 215, 680);
		DrawTTF(to_string(item02_cost), 250, 680, SDL_Color{ 128,128,128 }, font_20);
	}
	else {
		DrawIMG(moneySurface, 215, 680);
		DrawTTF(to_string(item02_cost), 250, 680, SDL_Color{ 200,100,0 }, font_20);
	}

	if (item03_cur_cd > 0.0f || itemLevel[2] == 0) {
		DrawIMG(itemSurface_03_dark, 375, 550);
		DrawItemIMG(itemSurface_03, 375, 550, (item03_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100 - item03_cur_cd) / (item03_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100));
	}
	else
	{
		itemButton_03.show(itemSurface_03, g_pScreen);
		if (readyStation == -1)
		{
			readyStation = rand() % 2;
		}
	}

	if (item03_cur_cd > 0.0f || money - item03_cost < 0) {
		DrawIMG(moneySurface_grayscale, 390, 680);
		DrawTTF(to_string(item03_cost), 425, 680, SDL_Color{ 128,128,128 }, font_20);
	}
	else {
		DrawIMG(moneySurface, 390, 680);
		DrawTTF(to_string(item03_cost), 425, 680, SDL_Color{ 200,100,0 }, font_20);
	}

	if (item04_cur_cd > 0.0f || itemLevel[3] == 0) {
		DrawIMG(itemSurface_04_dark, 550, 530);
		DrawItemIMG(itemSurface_04, 550, 530, (item04_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100 - item04_cur_cd) / (item04_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100));
	}
	else
		itemButton_04.show(itemSurface_04, g_pScreen);
	if (item04_cur_cd > 0.0f || money - item04_cost < 0) {
		DrawIMG(moneySurface_grayscale, 565, 680);
		DrawTTF(to_string(item04_cost), 600, 680, SDL_Color{ 128,128,128 }, font_20);
	}
	else {
		DrawIMG(moneySurface, 565, 680);
		DrawTTF(to_string(item04_cost), 600, 680, SDL_Color{ 200,100,0 }, font_20);
	}

	//TODO May change
	if (item03_active > 0.0f)
		artificialTyphoon[0].render_artificial_typhoon(typhoonSurface_toBeDrawn, g_pScreen);
	if (item04_active > 0.0f)
		DrawIMG(itemDisplaySurface_04, target_location.getX() - 100, target_location.getY() - 100);
	if (isPause) {
		playButton.show(playSurface, g_pScreen);
		DrawIMG(pausingSurface, 1120, 580);
	}
	else {
		DrawIMG(playingSurface, 1200, 580);
		pauseButton.show(pauseSurface, g_pScreen);
	}
	if (curGameSpeed != 4)
		speedButton_01.show(speedSurface_01, g_pScreen);
	else
		DrawIMG(speedSurface_01_dark, 970, 650);
	if (curGameSpeed != 8)
		speedButton_04.show(speedSurface_04, g_pScreen);
	else
		DrawIMG(speedSurface_04_dark, 1050, 650);
	if (curGameSpeed != 16)
		speedButton_16.show(speedSurface_16, g_pScreen);
	else
		DrawIMG(speedSurface_16_dark, 1130, 650);
	if (curGameSpeed != 64)
		speedButton_32.show(speedSurface_32, g_pScreen);
	else
		DrawIMG(speedSurface_32_dark, 1210, 650);

	DrawIMG(newsBarBgSurface, 110, 50);
	DrawTTF(cur_show_news, news_x, news_y, SDL_Color{ 255,165,0 }, font_20);
	DrawIMG(topBarBgSurface, 110, 0);
	DrawTTF((hour < 10 ? "0" + to_string(hour) : to_string(hour)) + ":" + (minute < 10 ? "0" + to_string(minute) : to_string(minute)), 130, 6, SDL_Color{ 0,0,0 }, font_30);
	DrawTTF(GenerateDate(), 240, 12, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(popularityRatingSurface, 595, 10);
	if (popularityRating > last_popularityRating)
		DrawIMG(increaseIconSurface, 630, 15);
	else if (popularityRating < last_popularityRating)
		DrawIMG(decreaseIconSurface, 630, 15);
	else
		DrawIMG(neutralIconSurface, 630, 15);
	DrawTTF(to_string((int)popularityRating).append("%"), 655, 12, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(hsiSurface, 725, 10);
	if (display_hsi > last_hsi)
		DrawIMG(increaseIconSurface, 760, 15);
	else if (display_hsi < last_hsi)
		DrawIMG(decreaseIconSurface, 760, 15);
	else
		DrawIMG(neutralIconSurface, 760, 15);
	DrawTTF(to_string(display_hsi).substr(0, 8), 785, 12, SDL_Color{ 0,0,0 }, font_20); //5 digits + "." + 2 decimal place = 8 digits
	DrawIMG(moneySurface, 895, 10);
	DrawTTF("$" + to_string((int)money), 930, 12, SDL_Color{ 0,0,0 }, font_20);
	DrawIMG(radSurface, 1055, 10);
	DrawTTF(to_string(rad).substr(0, to_string(rad).find('.') + 2), 1085, 12, SDL_Color{ 0,0,0 }, font_20);
	if (curSignal == newSignal) {
		switch (curSignal) {
		case 1: DrawIMG(signalSurface_01, 1175, 0); break;
		case 3: DrawIMG(signalSurface_03, 1175, 0); break;
		case 8: DrawIMG(signalSurface_08, 1175, 0); break;
		case 9: DrawIMG(signalSurface_09, 1175, 0); break;
		case 10: DrawIMG(signalSurface_10, 1175, 0); break;
			//default: printf("No Signal\n");
		}
	}
	else DrawUpdatingSignal(curSignal, newSignal, 1175, 0, (signal_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100 - signal_cur_cd) / signal_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100);

}

void HandleButtonEvents(SDL_Event e)
{
	if (gamemode == 0) {
		// handle button events in main menu
		mainHelpButton.handle_events(e);
		mainStartButton.handle_events(e);
	}
	else if (gamemode == 1) {
		settingButton.handle_events(e);
		signalUpButton.handle_events(e);
		signalDownButton.handle_events(e);
		extendButton.handle_events(e);
		itemButton_01.handle_events(e);
		itemButton_02.handle_events(e);
		itemButton_03.handle_events(e);
		itemButton_04.handle_events(e);
		pauseButton.handle_events(e);
		playButton.handle_events(e);
		speedButton_01.handle_events(e);
		speedButton_04.handle_events(e);
		speedButton_16.handle_events(e);
		speedButton_32.handle_events(e);
	}
	else if (gamemode == 2) {
		// handle button events in setting panel
		settingHelpButton.handle_events(e);
		settingPanelCloseButton.handle_events(e);
		musicUpButton.handle_events(e);
		musicDownButton.handle_events(e);
		effectUpButton.handle_events(e);
		effectDownButton.handle_events(e);
		resignButton.handle_events(e);
	}
	else if (gamemode == 3) {
		skillTreePanelCloseButton.handle_events(e);
		skillTreePanelSettingButton.handle_events(e);
		for (int i = 0; i < 4; i++) {
			if (itemLevel[i] < 4)
				skillTreeItemButton[i].handle_events(e);
		}
		for (int i = 0; i < 5; i++) {
			if (skillLevel[i] < 4)
				skillTreeSkillButton[i].handle_events(e);
		}
	}
	else if (gamemode == 4) {
		gameoverBackButton.handle_events(e);
	}
	else if (gamemode == 5) {
		helpCategoryButton_01.handle_events(e);
		helpCategoryButton_02.handle_events(e);
		helpCategoryButton_04.handle_events(e);
		helpCategoryButton_05.handle_events(e);
	}
	else printf("No Such Gamemode");
}

void HandleButtonAction()
{
	if (gamemode == 0) {
		// handle button events in main menu		
		if (mainHelpButton.getButtonPressed() && temp_height <= 0) { //Button Down
			mainHelpButton.setButtonPressed(false);
			gamemode = 5; 
			help_category = 0;
			last_gamemode.push_back(0);
			Mix_PlayChannel(10, click_sound, 0);
			printf("open helping page\n");
		}
		else if (mainStartButton.getButtonPressed() && temp_height <= 0) { //Button Down
			mainStartButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			exitMenu = true;
			temp_width = 0;
			temp_height = 0;
			printf("start game\n");

			curSignal = 0;
			newSignal = 0;
			for (int i = 0; i < 5; i++) {
				typhoons[i].set_exist(false);
			}
		}
	}
	else if (gamemode == 1) {
		if (settingButton.getButtonPressed()) { //Button Down
			settingButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			for (int i = 0; i < 5; i++) {
				if (typhoons[i].soundIndex == 0)
					Mix_FadeOutChannel(i * 2, 500 + 500.f / curGameSpeed);
				else
					Mix_FadeOutChannel(i * 2 + 1, 500 + 500.f / curGameSpeed);
			}
			gamemode = 2;
			last_gamemode.push_back(1);
			printf("Setting in gameplay\n");
		}
		else if (signalUpButton.getButtonPressed() && curSignal == newSignal) { //Button Down
			UpdateSignal(true);
			signalUpButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			printf("Signal Up\n");
		}
		else if (signalDownButton.getButtonPressed() && curSignal == newSignal) { //Button Down
			UpdateSignal(false);
			signalDownButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			printf("Signal Down\n");
		}
		else if (extendButton.getButtonPressed()) { //Button Down
			gamemode = 3;
			for (int i = 0; i < 5; i++) {
				if (typhoons[i].soundIndex == 0)
					Mix_FadeOutChannel(i * 2, 500 + 500.f / curGameSpeed);
				else
					Mix_FadeOutChannel(i * 2 + 1, 500 + 500.f / curGameSpeed);
			}
			extendButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			printf("Open skill tree panel\n");
		}
		else if (itemButton_01.getButtonPressed() && item01_cur_cd <= 0.0f && item01_cost <= money) { //Button Down
			money -= item01_cost;
			//the higher level, the longer durantion
			item01_active = upgradeItemDetails[0][itemLevel[0]] * frames_per_gameHour * 0.001f;
			//cout << item01_active << endl;
			item01_cur_cd = item01_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100;
			itemButton_01.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			Mix_PlayChannel(11, item01_sound, 0);
			printf("Use item 1\n");
		}
		else if (itemButton_02.getButtonPressed() && item02_cur_cd <= 0.0f && item02_cost <= money) { //Button Down
			money -= item02_cost;
			for (int i = 0; i < 5; i++)
			{
				if (!typhoons[i].get_exist()) continue;
				typhoons[i].LevelDown(rand() % itemLevel[1] + itemLevel[1]);
			}
			item02_cur_cd = item02_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100;
			itemButton_02.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			Mix_PlayChannel(12, item02_sound, 0);
			printf("Use item 2\n");
		}
		else if (itemButton_03.getButtonPressed() && item03_cur_cd <= 0.0f && item03_cost <= money) { //Button Down
			money -= item03_cost;

			//Find the best typhoon which fulfilled the conditions
			int best = -1;
			float closest = FLT_MAX;
			for (int i = 0; i < 5; i++)
			{
				if (!typhoons[i].get_exist()) continue;
				//Later change it to the station pos
				float dist;
				//Should not have the -1
				if (readyStation == 0)
				{
					dist = Vector2D::Magnitude(*Vector2D::Minus(station01, typhoons[i].get_pos()));
				}
				else
				{
					dist = Vector2D::Magnitude(*Vector2D::Minus(station02, typhoons[i].get_pos()));
				}
				if (dist < closest)
				{
					closest = dist;
					best = i;
				}
			}
			if (best != -1)
			{
				//Place the artificial typhoon
				//When it can be called, should != -1
				if (readyStation != -1)
				{
					artificialTyphoon[0].set_exist(true);
					artificialTyphoon[0].set_follow(true);
					if (readyStation == 0)
					{
						artificialTyphoon[0].set_pos(station01);
					}
					else
					{
						artificialTyphoon[0].set_pos(station02);
					}

					readyStation = -1;
					item03_active = upgradeItemDetails[2][itemLevel[2]] * frames_per_gameHour * 0.001f;
					item03_cur_cd = item03_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100;
				}
			}
			itemButton_03.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			Mix_PlayChannel(13, item03_sound, 0);
			printf("Use item 3\n");
		}
		else if (itemButton_04.getButtonPressed() && item04_cur_cd <= 0.0f && item04_cost <= money) { //Button Down
			money -= item04_cost;
			item04_active = upgradeItemDetails[3][itemLevel[3]] * frames_per_gameHour * 0.001f;
			item04_cur_cd = item04_cd * (100 - upgradeSkillDetails[4][skillLevel[4]]) / 100;
			itemButton_04.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			Mix_PlayChannel(14, item04_sound, 0);
			printf("Use item 4\n");
		}
		else if (pauseButton.getButtonPressed()) { //Button Down
			pauseButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			isPause = true;
			printf("Pause Game\n");
		}
		else if (playButton.getButtonPressed()) { //Button Down
			playButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			isPause = false;
			printf("Continue Play Game\n");
		}
		else if (speedButton_01.getButtonPressed()) { //Button Down
			speedButton_01.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			curGameSpeed = 4;
			printf("speed up to 1x\n");
		}
		else if (speedButton_04.getButtonPressed()) { //Button Down
			speedButton_04.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			curGameSpeed = 8;
			printf("speed up to 4x\n");
		}
		else if (speedButton_16.getButtonPressed()) { //Button Down
			speedButton_16.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			curGameSpeed = 16;
			printf("speed up to 16x\n");
		}
		else if (speedButton_32.getButtonPressed()) { //Button Down
			speedButton_32.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			curGameSpeed = 64;
			printf("speed up to 32x\n");
		}
	}
	else if (gamemode == 2) {
		// handle button actions in setting panel
		if (settingHelpButton.getButtonPressed()) { //Button Down
			settingHelpButton.setButtonPressed(false);
			gamemode = 5;
			help_category = 0;
			last_gamemode.push_back(2);
			Mix_PlayChannel(10, click_sound, 0);
			printf("Open help\n");
		}
		else if (settingPanelCloseButton.getButtonPressed()) { //Button Down
			gamemode = last_gamemode.back();
			last_gamemode.pop_back();
			settingPanelCloseButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			printf("Close setting panel\n");
		}
		else if (musicUpButton.getButtonPressed() && musicLevel < 400) { //Button Down
			musicLevel++;
			int temp_music_level = (int)(64 * musicLevel / 400.f / 2 / 2);
			Mix_VolumeMusic(temp_music_level);
			printf("Music Up, %d\n", musicLevel);
		}
		else if (musicDownButton.getButtonPressed() && musicLevel > 0) { //Button Down
			musicLevel--;
			int temp_music_level = (int)(64 * musicLevel / 400.f / 2 / 2);
			if (temp_music_level == 0 && musicLevel != 0) temp_music_level = 1;
			Mix_VolumeMusic(temp_music_level);
			printf("Music Down, %d\n", musicLevel);
		}
		else if (effectUpButton.getButtonPressed() && effectLevel < 400) { //Button Down
			effectLevel++;
			Mix_VolumeChunk(click_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item01_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item02_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item03_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item04_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(lvlUp_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(wind_sound_1, 128 * effectLevel / 400.f * sound_dist / 400.f / 20);
			Mix_VolumeChunk(wind_sound_2, 128 * effectLevel / 400.f * sound_dist / 400.f / 20);
			printf("Effect Up, %d\n", effectLevel);
		}
		else if (effectDownButton.getButtonPressed() && effectLevel > 0) { //Button Down
			effectLevel--;
			Mix_VolumeChunk(click_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item01_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item02_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item03_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(item04_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(lvlUp_sound, 128 * effectLevel / 400.f);
			Mix_VolumeChunk(wind_sound_1, 128 * effectLevel / 400.f * sound_dist / 400.f / 20);
			Mix_VolumeChunk(wind_sound_2, 128 * effectLevel / 400.f * sound_dist / 400.f / 20);
			printf("Effect Down, %d\n", effectLevel);
		}
		else if (resignButton.getButtonPressed()) { //Button Down
			gamemode = 4;
			resignButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			printf("Resign, Gameover\n");
		}
	}
	else if (gamemode == 3) {
		if (skillTreePanelCloseButton.getButtonPressed()) { //Button Down
			gamemode = 1;
			skillTreePanelCloseButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			printf("Close skill tree panel\n");
		}
		else if (skillTreePanelSettingButton.getButtonPressed()) { //Button Down
			skillTreePanelSettingButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			gamemode = 2;
			last_gamemode.push_back(3);
			printf("Setting in skill tree\n");
		}
		for (int i = 0; i < 4; i++) {
			if (skillTreeItemButton[i].getButtonPressed()) {
				skillTreeItemButton[i].setButtonPressed(false);
				Mix_PlayChannel(10, click_sound, 0);
				if (upgradeItemMoney[itemLevel[i]] > money || upgradeItemRad[itemLevel[i]] > rad)
					return;
				money -= upgradeItemMoney[itemLevel[i]];
				rad -= upgradeItemRad[itemLevel[i]];
				itemLevel[i]++;
				if (itemLevel[i] < 4)
					skillTreeItemButton[i].set_x(skillTreeItemButton[i].get_x() + 150);
				Mix_PlayChannel(15, lvlUp_sound, 0);
				printf("Level up\n");
				return;
			}
		}
		for (int i = 0; i < 5; i++) {
			if (skillTreeSkillButton[i].getButtonPressed()) {
				skillTreeSkillButton[i].setButtonPressed(false);
				Mix_PlayChannel(10, click_sound, 0);
				if (upgradeSkillMoney[skillLevel[i]] > money || upgradeSkillRad[skillLevel[i]] > rad)
					return;
				money -= upgradeSkillMoney[skillLevel[i]];
				rad -= upgradeSkillRad[skillLevel[i]];
				skillLevel[i]++;
				if (i == 3)
				{
					//Update to typhoon
					for (int j = 0; j < 5; j++)
					{
						typhoons[j].update_predict_range(skillLevel[i]);
						typhoons[j].update_predict_accuracy(upgradeSkillDetails[2][skillLevel[2]]);
					}
				}
				if (skillLevel[i] < 4)
					skillTreeSkillButton[i].set_x(skillTreeSkillButton[i].get_x() + 150);
				Mix_PlayChannel(15, lvlUp_sound, 0);
				printf("Level up\n");
				return;
			}
		}
	}
	else if (gamemode == 4) {// gameover scene
		if (gameoverBackButton.getButtonPressed()) { //Button Down
			gameoverBackButton.setButtonPressed(false);
			Mix_PlayChannel(10, click_sound, 0);
			exitGame = true;
			printf("Back game menu\n");
		}
	}
	else if (gamemode == 5) {// 
		if (helpCategoryButton_01.getButtonPressed() && help_category != 0) { //Button Down
			Mix_PlayChannel(10, click_sound, 0);
			helpCategoryButton_01.setButtonPressed(false);
			help_category = 0;
			printf("Help category 1\n");
		}
		else if (helpCategoryButton_02.getButtonPressed() && help_category != 1) { //Button Down
			Mix_PlayChannel(10, click_sound, 0);
			helpCategoryButton_02.setButtonPressed(false);
			help_category = 1;
			printf("Help category 2\n");
		}
		else if (helpCategoryButton_04.getButtonPressed() && help_category != 3) { //Button Down
			Mix_PlayChannel(10, click_sound, 0);
			helpCategoryButton_04.setButtonPressed(false);
			help_category = 3;
			printf("Help category 4\n");
		}
		else if (helpCategoryButton_05.getButtonPressed()) { //Button Down
			Mix_PlayChannel(10, click_sound, 0);
			helpCategoryButton_05.setButtonPressed(false);
			gamemode = last_gamemode.back(); 
			last_gamemode.pop_back();
			if (!last_gamemode.empty()) {
				printf("gm%d\n", last_gamemode.back());
				if (last_gamemode.back() == 1)
					DrawMainGameplay();
				else if (last_gamemode.back() == 3)
					DrawSkillTree();
				else printf("last game mode error");
				DrawSetting();
			} 
			else mainStartButton.setButtonPressed(false);
			printf("Help category 5\n");
		}

	}
	else printf("No such gamemode");
}

int main(int argc, char *argv[])
{
	srand(time(NULL));
	const Uint8* keys;		// for keyboard key state

	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		printf("Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	// Create the window and try to setup the primary screen surface
	g_pWindow = SDL_CreateWindow("Observatory Simulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		1280, 720, SDL_WINDOW_SHOWN);
	if (g_pWindow == NULL)
	{
		fprintf(stderr, "Error: Can't open window!  %s\n", SDL_GetError());
		exit(1);
	}

	g_pScreen = SDL_GetWindowSurface(g_pWindow);
	if (g_pScreen == NULL)
	{
		printf("Fail to get the main window surface : %s\n", SDL_GetError());
		exit(1);
	}

	//initialize SDL_ttf
	TTF_Init();

	font_15 = TTF_OpenFont("Chava-Regular.ttf", 15);
	if (!font_15) {
		printf("No Font");
		return 0;
	}
	font_20 = TTF_OpenFont("Chava-Regular.ttf", 20);
	if (!font_20) {
		printf("No Font");
		return 0;
	}
	font_24 = TTF_OpenFont("Chava-Regular.ttf", 24);
	if (!font_24) {
		printf("No Font");
		return 0;
	}
	font_30 = TTF_OpenFont("Chava-Regular.ttf", 30);
	if (!font_30) {
		printf("No Font");
		return 0;
	}
	font_30_Bold = TTF_OpenFont("Chava-Regular.ttf", 30);
	if (!font_30_Bold) {
		printf("No Font");
		return 0;
	}
	TTF_SetFontStyle(font_30_Bold, TTF_STYLE_BOLD);
	font_54 = TTF_OpenFont("Chava-Regular.ttf", 54);
	if (!font_54) {
		printf("No Font");
		return 0;
	}
	font_48_Bold = TTF_OpenFont("Chava-Regular.ttf", 48);
	if (!font_48_Bold) {
		printf("No Font");
		return 0;
	}
	TTF_SetFontStyle(font_48_Bold, TTF_STYLE_BOLD);
	//TTF_SetFontOutline(font_54, 1);
	//TTF_SetFontStyle(font_54, TTF_STYLE_BOLD);
	//TTF_STYLE_NORMAL
	//TTF_STYLE_BOLD
	//TTF_STYLE_ITALIC
	//TTF_STYLE_UNDERLINE
	//TTF_STYLE_STRIKETHROUGH

	//Initialize SDL_mixer
	// code for the sound here==================
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}

	InitImages();		// Load all images
	Mix_AllocateChannels(16);
	LoadSound();
	ResetStat(); // initialize all variables

	typhoons = (Typhoon*)malloc(sizeof(Typhoon) * 5);
	for (int i = 0; i < 5; i++) {
		// start with a slanted x,y pattern
		typhoons[i] = Typhoon(true, Vector2D(500, 500), target_location, upgradeSkillDetails[2][skillLevel[2]], mapSurface);
		typhoons[i].update_predict_range(skillLevel[3]);
		//typhoons[i].
	}
	artificialTyphoon = (Typhoon*)malloc(sizeof(Typhoon));
	artificialTyphoon[0] = Typhoon(true, Vector2D(0, 0), target_location, 100, mapSurface);
	int done = 0;

	while (done == 0)
	{
		SDL_Event event;

		while (SDL_PollEvent(&event))		// Poll for the event
		{
			if (event.type == SDL_QUIT) { done = 1; }

			// item 
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_ESCAPE) { done = 1; }
			}
			HandleButtonEvents(event);
		}

		curTyphoonCount = 0;
		for (int i = 0; i < 5; i++)
		{
			if (typhoons[i].get_exist()) curTyphoonCount++;
		}

		HandleButtonAction();

		// item 0
		// Try get the keyboard state
		keys = SDL_GetKeyboardState(NULL);

		// SDL_GetKeyboardState() returns a pointer to an array of type Uint8. 
		// Each element of the array has information about a specific key 
		// (whether it is held down or not). 
		//
		// The reason why we don't check for the keys in the event loop is 
		// because in the event loop events are generated when a key has 
		// been pressed down, not if it is being held down. 
		//
		// We check if the left, right, up or down keys are pressed. 
		// And if so then we move the box one unit left, right, up or down. 
		// Since many keys can be pressed down at *once* so we don't 
		// use "else if" here.

		if (gamemode == 0) {
			if (temp_width < 1285) {
				temp_width += 4 + exitMenu;
				temp_height += (4 + exitMenu) * 9.f / 16;
			}
			else if (temp_height > 0) temp_height -= 2;
			else {
				menu_text_cd++;
				if (menu_text_cd > 200) {
					menu_text_cd = 0;
					menu_text_show = !menu_text_show;
				}
			}
			DrawGameMenu(temp_width, temp_height, menu_text_show, exitMenu);
		}

		// Gameplay
		else if (gamemode == 1) {
			if (enteredGame) {
				//if (GetDistanceToTarget
				typhoonAnimCounter++;
				// News movement
				if (newsStop) newsMoveCounter += curGameSpeed;
				if (!newsStop) {
					if (news_y < 60) {
						news_y += 0.1f * curGameSpeed; //speed
					}
					else {
						newsStop = true;
					}
				}
				else {
					if (news_typhoon_index != -1 && !typhoons[news_typhoon_index].get_exist() && cur_show_news != "-    No news") {
						next_show_news = "-    No news";
						newsOutdate = true;
						news_typhoon_index = -1;
					}
					if (newsMoveCounter > news_last_time && newsOutdate) {
						if (news_y > -10) {
							news_y -= 0.1f * curGameSpeed; //speed
						}
						else { // disappear news
							newsStop = false;
							cur_show_news = next_show_news;
							next_show_news = "error news";
							newsMoveCounter = 0;
							newsOutdate = false;
						}
					}
				}
				if (!isPause) {
					//The signal and HSI
					switch (curSignal)
					{
					case 0:
						hsi += (rand() % 100 - 20) * curGameSpeed / 3000.f;
						break;
					case 1:
						hsi += (rand() % 100 - 60) * curGameSpeed / 3000.f;
						break;
					case 3:
						hsi += (-rand() % 100) * curGameSpeed / 3000.f;
						break;
					case 8:
						hsi += (-rand() % 175 - 50) * curGameSpeed / 3000.f;
						break;
					case 9:
						hsi += (-rand() % 175 - 100) * curGameSpeed / 3000.f;
						break;
					case 10:
						hsi += (-rand() % 250 - 100) * curGameSpeed / 3000.f;
						break;
					}
					// Trading Hours
					if ((((hour == 9) && (minute >= 15)) || ((hour > 9) && (hour < 12)) || ((hour >= 13) && (hour < 16)) || ((hour == 16) && (minute <= 30)))) {
						if (curSignal)
							if (curSignal == 1) {
								temp_hsi += ((rand() % 100 - 60) > 0 ? 1 : -1) * abs(hsi - temp_hsi); // 30% increase, 60% decrease
								hsi = temp_hsi;
							}
							else if (curSignal == 3) {
								temp_hsi += ((rand() % 100 - 80) > 0 ? 1 : -1) * abs(hsi - temp_hsi); // 20% increase, 80% decrease
								hsi = temp_hsi;
							}
							else
								temp_hsi = hsi;
						else {
							temp_hsi += ((rand() % 100 - 48) > 0 ? 1 : -1) * abs(hsi - temp_hsi); // 55% increase, 45% decrease
							hsi = temp_hsi;
						}
					}
					if (curSignal < 8 && day <= 5)
						display_hsi = temp_hsi;

					//Hurt
					//Distance and strength

					bool damaged = false;
					int wrong_count = 0;

					//Change: immunity when curSignal == 8
					if (curSignal == 0)
					{
						//Normal typhoon
						for (int i = 0; i < 5; i++)
						{
							if (typhoons[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos()));

								if (dist < 400 && (rand() % 100 - dist - curSignal * 2.5f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										popularityRating -= ((400 - dist + 400) / 400.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									}
									//TODO add news
									string temp_name = default_typhoon_name[typhoons[i].get_name_index()].substr(default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '), default_typhoon_name[typhoons[i].get_name_index()].length() - default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '));
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Typhoon \"" + temp_name + "\" has made " + to_string(typhoons[i].get_deaths()) + " deaths and " + to_string(typhoons[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (typhoons[i].get_deaths() != 0 || typhoons[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((200 - dist + 200) / 200.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 50000.f;
									float temp_injuries = ((200 - dist + 200) / 200.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									if (temp_deaths < 0) temp_deaths = 0;
									if (temp_injuries < 0) temp_injuries = 0;
									typhoons[i].set_deaths(temp_deaths);
									typhoons[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
								//cout << dist << endl;
							}
						}
						//Art typhoon
						for (int i = 0; i < 1; i++)
						{
							if (artificialTyphoon[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, artificialTyphoon[i].get_pos()));
								if (dist < 400 && (rand() % 100 - dist - curSignal * 2.5f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										//Fixed level(depends on level of the item)
										popularityRating -= ((400 - dist + 400) / 400.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									}
									//TODO add news									
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Artificial Typhoon has made " + to_string(artificialTyphoon[i].get_deaths()) + " deaths and " + to_string(artificialTyphoon[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (artificialTyphoon[i].get_deaths() != 0 || artificialTyphoon[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((200 - dist + 200) / 200.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 50000.f;
									float temp_injuries = ((200 - dist + 200) / 200.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									artificialTyphoon[i].set_deaths(temp_deaths);
									artificialTyphoon[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
							}
						}
					}
					else if (curSignal == 1)
					{
						//Normal typhoon
						for (int i = 0; i < 5; i++)
						{
							if (typhoons[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos()));

								if (dist < 300 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										popularityRating -= ((300 - dist + 300) / 300.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									}
									//TODO add news
									string temp_name = default_typhoon_name[typhoons[i].get_name_index()].substr(default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '), default_typhoon_name[typhoons[i].get_name_index()].length() - default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '));
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Typhoon \"" + temp_name + "\" has made " + to_string(typhoons[i].get_deaths()) + " deaths and " + to_string(typhoons[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (typhoons[i].get_deaths() != 0 || typhoons[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((150 - dist + 150) / 150.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 50000.f;
									float temp_injuries = ((150 - dist + 150) / 150.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									if (temp_deaths < 0) temp_deaths = 0;
									if (temp_injuries < 0) temp_injuries = 0;
									typhoons[i].set_deaths(temp_deaths);
									typhoons[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
								else if (dist > 600) {
									wrong_count++;
								}
							}
						}
						//Art typhoon
						for (int i = 0; i < 1; i++)
						{
							if (artificialTyphoon[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, artificialTyphoon[i].get_pos()));
								if (dist < 300 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										//Fixed level(depends on level of the item)
										popularityRating -= ((300 - dist + 300) / 300.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									}
									//TODO add news									
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Artificial Typhoon has made " + to_string(artificialTyphoon[i].get_deaths()) + " deaths and " + to_string(artificialTyphoon[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (artificialTyphoon[i].get_deaths() != 0 || artificialTyphoon[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((150 - dist + 150) / 150.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 50000.f;
									float temp_injuries = ((150 - dist + 150) / 150.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									if (temp_deaths < 0) temp_deaths = 0;
									if (temp_injuries < 0) temp_injuries = 0;
									artificialTyphoon[i].set_deaths(temp_deaths);
									artificialTyphoon[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
							}
						}
					}
					else if (curSignal == 3)
					{
						//Normal typhoon
						for (int i = 0; i < 5; i++)
						{
							if (typhoons[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos()));

								if (dist < 250 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										popularityRating -= ((250 - dist + 250) / 250.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									}
									//TODO add news
									string temp_name = default_typhoon_name[typhoons[i].get_name_index()].substr(default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '), default_typhoon_name[typhoons[i].get_name_index()].length() - default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '));
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Typhoon \"" + temp_name + "\" has made " + to_string(typhoons[i].get_deaths()) + " deaths and " + to_string(typhoons[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (typhoons[i].get_deaths() != 0 || typhoons[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((125 - dist + 125) / 125.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 50000.f;
									float temp_injuries = ((125 - dist + 125) / 125.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									typhoons[i].set_deaths(temp_deaths);
									typhoons[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
								else if (dist > 400) {
									wrong_count++;
								}
							}
						}
						//Art typhoon
						for (int i = 0; i < 1; i++)
						{
							if (artificialTyphoon[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, artificialTyphoon[i].get_pos()));
								if (dist < 250 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										//Fixed level(depends on level of the item)
										popularityRating -= ((250 - dist + 250) / 250.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									}
									//TODO add news									
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Artificial Typhoon has made " + to_string(artificialTyphoon[i].get_deaths()) + " deaths and " + to_string(artificialTyphoon[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (artificialTyphoon[i].get_deaths() != 0 || artificialTyphoon[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((125 - dist + 125) / 125.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 50000.f;
									float temp_injuries = ((125 - dist + 125) / 125.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									artificialTyphoon[i].set_deaths(temp_deaths);
									artificialTyphoon[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
							}
						}
					}
					else if (curSignal == 8)
					{
						//Normal typhoon
						for (int i = 0; i < 5; i++)
						{
							if (typhoons[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos()));

								if (dist < 200 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										popularityRating -= ((200 - dist + 200) / 200.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									}
									//TODO add news
									string temp_name = default_typhoon_name[typhoons[i].get_name_index()].substr(default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '), default_typhoon_name[typhoons[i].get_name_index()].length() - default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '));
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Typhoon \"" + temp_name + "\" has made " + to_string(typhoons[i].get_deaths()) + " deaths and " + to_string(typhoons[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (typhoons[i].get_deaths() != 0 || typhoons[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((100 - dist + 100) / 100.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 50000.f;
									float temp_injuries = ((100 - dist + 100) / 100.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									typhoons[i].set_deaths(temp_deaths);
									typhoons[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
								else if (dist > 250) {
									wrong_count++;
								}
							}
						}
						//Art typhoon
						for (int i = 0; i < 1; i++)
						{
							if (artificialTyphoon[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, artificialTyphoon[i].get_pos()));
								if (dist < 200 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										//Fixed level(depends on level of the item)
										popularityRating -= ((200 - dist + 200) / 200.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									}
									//TODO add news									
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Artificial Typhoon has made " + to_string(artificialTyphoon[i].get_deaths()) + " deaths and " + to_string(artificialTyphoon[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (artificialTyphoon[i].get_deaths() != 0 || artificialTyphoon[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((100 - dist + 100) / 100.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 50000.f;
									float temp_injuries = ((100 - dist + 100) / 100.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									artificialTyphoon[i].set_deaths(temp_deaths);
									artificialTyphoon[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
							}
						}
					}
					else if (curSignal == 9)
					{
						//Normal typhoon
						for (int i = 0; i < 5; i++)
						{
							if (typhoons[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos()));

								if (dist < 150 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										popularityRating -= ((150 - dist + 150) / 150.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									}
									//TODO add news
									string temp_name = default_typhoon_name[typhoons[i].get_name_index()].substr(default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '), default_typhoon_name[typhoons[i].get_name_index()].length() - default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '));
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Typhoon \"" + temp_name + "\" has made " + to_string(typhoons[i].get_deaths()) + " deaths and " + to_string(typhoons[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (typhoons[i].get_deaths() != 0 || typhoons[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((75 - dist + 75) / 75.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 50000.f;
									float temp_injuries = ((75 - dist + 75) / 75.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									typhoons[i].set_deaths(temp_deaths);
									typhoons[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
								else if (dist > 175) {
									wrong_count++;
								}
							}
						}
						//Art typhoon
						for (int i = 0; i < 1; i++)
						{
							if (artificialTyphoon[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, artificialTyphoon[i].get_pos()));
								if (dist < 150 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										//Fixed level(depends on level of the item)
										popularityRating -= ((150 - dist + 150) / 150.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									}
									//TODO add news									
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Artificial Typhoon has made " + to_string(artificialTyphoon[i].get_deaths()) + " deaths and " + to_string(artificialTyphoon[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (artificialTyphoon[i].get_deaths() != 0 || artificialTyphoon[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((75 - dist + 75) / 75.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 50000.f;
									float temp_injuries = ((75 - dist + 75) / 75.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									artificialTyphoon[i].set_deaths(temp_deaths);
									artificialTyphoon[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
							}
						}
					}
					else if (curSignal == 10)
					{
						//Normal typhoon
						for (int i = 0; i < 5; i++)
						{
							if (typhoons[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos()));

								if (dist < 100 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										popularityRating -= ((100 - dist + 100) / 100.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									}
									//TODO add news
									string temp_name = default_typhoon_name[typhoons[i].get_name_index()].substr(default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '), default_typhoon_name[typhoons[i].get_name_index()].length() - default_typhoon_name[typhoons[i].get_name_index()].find_first_not_of(' '));
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Typhoon \"" + temp_name + "\" has made " + to_string(typhoons[i].get_deaths()) + " deaths and " + to_string(typhoons[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (typhoons[i].get_deaths() != 0 || typhoons[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((50 - dist + 50) / 50.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 50000.f;
									float temp_injuries = ((50 - dist + 50) / 50.f) * (rand() % 100 / 100.f) * typhoons[i].get_level() * curGameSpeed / 4000.f;
									typhoons[i].set_deaths(temp_deaths);
									typhoons[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
								else if (dist > 100) {
									wrong_count++;
								}
							}
						}
						//Art typhoon
						for (int i = 0; i < 1; i++)
						{
							if (artificialTyphoon[i].get_exist())
							{
								float dist = Vector2D::Magnitude(*Vector2D::Minus(target_location, artificialTyphoon[i].get_pos()));
								if (dist < 100 && (rand() % 100 - dist - curSignal * 10.f) > 0)
								{
									if (item01_active <= 0.0f)
									{
										damaged = true;
										//Fixed level(depends on level of the item)
										popularityRating -= ((100 - dist + 100) / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									}
									//TODO add news									
									string temp_next_show_news = (string)(item01_active > 0.0f ? "-    [ Internal Information ]  " : "-    [ News ]  ") + "The Artificial Typhoon has made " + to_string(artificialTyphoon[i].get_deaths()) + " deaths and " + to_string(artificialTyphoon[i].get_injuries()) + " injuries";
									if (cur_show_news != temp_next_show_news && (artificialTyphoon[i].get_deaths() != 0 || artificialTyphoon[i].get_injuries() != 0)) {
										news_typhoon_index = i;
										next_show_news = temp_next_show_news;
										newsOutdate = true;
									}
									float temp_deaths = ((50 - dist + 50) / 50.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 50000.f;
									float temp_injuries = ((50 - dist + 50) / 50.f) * (rand() % 100 / 100.f) * (8 - itemLevel[2]) * curGameSpeed / 4000.f;
									artificialTyphoon[i].set_deaths(temp_deaths);
									artificialTyphoon[i].set_injuries(temp_injuries);
									deaths += temp_deaths;
									injuries += temp_injuries;
								}
							}
						}
					}

					if (wrong_count == curTyphoonCount && curSignal != 0) {
						popularityRating -= curGameSpeed / 20000.f * curSignal;
					}
					else if (!damaged) popularityRating += curGameSpeed / 10000.f;

					if (item01_cur_cd > 0.0f && itemLevel[0] != 0)
						item01_cur_cd -= 0.001f * curGameSpeed;
					if (item02_cur_cd > 0.0f && itemLevel[1] != 0)
						item02_cur_cd -= 0.001f * curGameSpeed;
					if (item03_cur_cd > 0.0f && itemLevel[2] != 0)
						item03_cur_cd -= 0.001f * curGameSpeed;
					if (item04_cur_cd > 0.0f && itemLevel[3] != 0)
						item04_cur_cd -= 0.001f * curGameSpeed;
					if (signal_cur_cd > 0.0f)
						signal_cur_cd -= 0.001f * curGameSpeed;
					else curSignal = newSignal;
					if (item01_active > 0.0f) {
						item01_active -= 0.001f * curGameSpeed;
					}
					else if(Mix_Playing(11))
					{
						Mix_FadeOutChannel(11, 1000);
					}
					if (item03_active > 0.0f) {
						item03_active -= 0.001f * curGameSpeed;
					}
					else
					{
						artificialTyphoon[0].set_exist(false);
						if (Mix_Playing(13))
						{
							Mix_FadeOutChannel(13, 1000);
						}
					}

					if (item04_active > 0.0f) {
						item04_active -= 0.001f * curGameSpeed;

						for (int i = 0; i < 5; i++)
						{
							if (!typhoons[i].get_exist()) continue;
							if (Vector2D::Magnitude(*Vector2D::Minus(target_location, typhoons[i].get_pos())) < 175)
							{
								//Do reflection
								//Move to 175
								Vector2D tempVect = *Vector2D::Normalize(*Vector2D::Minus(typhoons[i].get_pos(), target_location));

								typhoons[i].set_pos(*Vector2D::Add(*Vector2D::Scale(tempVect, 175), target_location));
								typhoons[i].ChangeDir(*Vector2D::Reflect(typhoons[i].get_dir(), tempVect));

								//Down level
								int level = typhoons[i].get_level() - 4;
								if (level < 0) level = 0;
								{
									typhoons[i].set_level(level);
								}
							}
						}

					}
					else if (Mix_Playing(14))
					{
						Mix_FadeOutChannel(14, 1000);
					}

					second += curGameSpeed * 10;
					temp_time += curGameSpeed;

					//cout << frames_per_gameHour << "         " << hour << ":" << minute << " is " << item01_active << ", " << item03_active << ", " << item04_active << endl;

					//Toward the closest non-art typhoon
					if (artificialTyphoon[0].get_exist())
					{
						if (artificialTyphoon[0].get_follow())
						{
							int best = -1;
							float closest = FLT_MAX;
							for (int i = 0; i < 5; i++)
							{
								if (!typhoons[i].get_exist()) continue;
								//Later change it to the station pos
								float dist = Vector2D::Magnitude(*Vector2D::Minus(artificialTyphoon[0].get_pos(), typhoons[i].get_pos()));
								printf("%f \n", dist);
								if (dist < closest)
								{
									closest = dist;
									best = i;
								}
							}
							if (best != -1)
							{
								//move the artificial typhoon
								Vector2D tempDir = *Vector2D::Minus(typhoons[best].get_pos(), artificialTyphoon[0].get_pos());
									float dist = Vector2D::Magnitude(tempDir);
									if (dist* (float)curGameSpeed > (1 + itemLevel[1])) dist = (1 + itemLevel[1]) / (float)curGameSpeed;
								artificialTyphoon[0].save_dir(*Vector2D::Scale(*Vector2D::Normalize(tempDir), dist));
								artificialTyphoon[0].set_pos(*Vector2D::Add(*Vector2D::Scale(artificialTyphoon[0].get_dir(), curGameSpeed), artificialTyphoon[0].get_pos()));
							}
							//Check collision
							{
								bool caused = false;
								Vector2D tempVect;
								for (int i = 0; i < 5; i++) {
									if (typhoons[i].get_exist() && Vector2D::Magnitude(*Vector2D::Minus(typhoons[i].get_pos(), artificialTyphoon[0].get_pos())) < 150)
									{
										caused = true;
										tempVect = *Vector2D::Normalize(*Vector2D::Minus(typhoons[i].get_pos(), artificialTyphoon[0].get_pos()));

										typhoons[i].set_pos(*Vector2D::Add(*Vector2D::Scale(tempVect, 150), artificialTyphoon[0].get_pos()));
										//typhoons[i].ChangeDir(*Vector2D::Reflect(typhoons[i].get_dir(), tempVect));
										typhoons[i].ChangeDir(tempVect);
									}
								}
								if (caused)
								{
									cout << "Caused \n";
									//ArtTyp die
									artificialTyphoon[0].ChangeDir(*Vector2D::Reflect(artificialTyphoon[0].get_dir(), tempVect));
									artificialTyphoon[0].set_follow(false);
									artificialTyphoon[0].set_exist(false);

									readyStation = -1;
								}
							}
						}
						//Act like a normal typhoon
						else
						{
							artificialTyphoon[0].move(curGameSpeed, upgradeSkillDetails[2][skillLevel[2]]);
						}
					}


					for (int i = 0; i < 5; i++) {
						if (typhoons[i].get_exist()) {
							typhoons[i].move(curGameSpeed, upgradeSkillDetails[2][skillLevel[2]]);
						}
					}

					// Game over checking
					if (display_hsi < 15000 || popularityRating < 1 || month >= 12) {
						gamemode = 4;
						for (int i = 0; i < 5; i++) {
							if (typhoons[i].soundIndex == 0)
								Mix_FadeOutChannel(i * 2, 500 + 500.f / curGameSpeed);
							else
								Mix_FadeOutChannel(i * 2 + 1, 500 + 500.f / curGameSpeed);
						}
					}
				}
				DrawMainGameplay();
			}
			else {
				if (temp_width > 0) {
					temp_width -= 5;
					temp_height -= 5 * 9.f / 16;
				}
				else enteredGame = true;
				DrawMainGameplay();
				DrawEnterGame(temp_width, temp_height); // right to left
				DrawIMG(blackSurface, 1280 - temp_width, 0); // left to right
				DrawIMG(blackSurface, 0, 720 - temp_height);
			}
		}
		else if (gamemode == 2) DrawSetting();
		else if (gamemode == 3) DrawSkillTree();
		else if (gamemode == 4) {
			DrawGameOver();
			if (exitGame) {
				temp_width += 4 + exitMenu;
				temp_height += (4 + exitMenu) * 9.f / 16;
				DrawCloseGame(temp_width, temp_height);
			}
		}
		else if (gamemode == 5) {
			typhoonAnimCounter++;
			DrawHelpPage();
		}
		else printf("No Such GameMode");//Debug

		// update the Window
		SDL_UpdateWindowSurface(g_pWindow);
	}

#pragma region Dellocate
	//Deallocate surface
	SDL_FreeSurface(helpButtonSurface);
	helpButtonSurface = NULL;
	SDL_FreeSurface(mapSurface);
	mapSurface = NULL;
	SDL_FreeSurface(blackSurface);
	blackSurface = NULL;
	SDL_FreeSurface(helpPanelSurface);
	helpPanelSurface = NULL;
	SDL_FreeSurface(panelSurface);
	panelSurface = NULL;
	SDL_FreeSurface(settinglevelSurface);
	settinglevelSurface = NULL;
	SDL_FreeSurface(mainBGSurface);
	mainBGSurface = NULL;
	SDL_FreeSurface(mainBGSurface_NoLi);
	mainBGSurface_NoLi = NULL;
	SDL_FreeSurface(settingButtonSurface);
	settingButtonSurface = NULL;
	SDL_FreeSurface(extendButtonSurface);
	extendButtonSurface = NULL;
	SDL_FreeSurface(defaultButtonSurface);
	defaultButtonSurface = NULL;
	SDL_FreeSurface(defaultButtonSurface_clicked);
	defaultButtonSurface_clicked = NULL;
	//SDL_FreeSurface(mapLayerSurface_01);
	//mapLayerSurface_01 = NULL;
	//SDL_FreeSurface(mapLayerSurface_02);
	//mapLayerSurface_02 = NULL;
	SDL_FreeSurface(stationSurface_empty);
	stationSurface_empty = NULL;
	SDL_FreeSurface(stationSurface_ready);
	stationSurface_ready = NULL;
	SDL_FreeSurface(topBarBgSurface);
	topBarBgSurface = NULL;
	SDL_FreeSurface(newsBarBgSurface);
	newsBarBgSurface = NULL;
	SDL_FreeSurface(itemSurface_01);
	itemSurface_01 = NULL;
	SDL_FreeSurface(itemSurface_02);
	itemSurface_02 = NULL;
	SDL_FreeSurface(itemSurface_03);
	itemSurface_03 = NULL;
	SDL_FreeSurface(itemSurface_04);
	itemSurface_04 = NULL;
	SDL_FreeSurface(itemDisplaySurface_04);
	itemDisplaySurface_04 = NULL;
	SDL_FreeSurface(itemSurface_01_dark);
	itemSurface_01_dark = NULL;
	SDL_FreeSurface(itemSurface_02_dark);
	itemSurface_02_dark = NULL;
	SDL_FreeSurface(itemSurface_03_dark);
	itemSurface_03_dark = NULL;
	SDL_FreeSurface(itemSurface_04_dark);
	itemSurface_04_dark = NULL;
	SDL_FreeSurface(increaseIconSurface);
	increaseIconSurface = NULL;
	SDL_FreeSurface(neutralIconSurface);
	neutralIconSurface = NULL;
	SDL_FreeSurface(decreaseIconSurface);
	decreaseIconSurface = NULL;
	SDL_FreeSurface(popularityRatingSurface);
	popularityRatingSurface = NULL;
	SDL_FreeSurface(hsiSurface);
	hsiSurface = NULL;
	SDL_FreeSurface(moneySurface);
	moneySurface = NULL;
	SDL_FreeSurface(moneySurface_grayscale);
	moneySurface_grayscale = NULL;
	SDL_FreeSurface(radSurface);
	radSurface = NULL;
	SDL_FreeSurface(popularityRatingSurface_large);
	popularityRatingSurface_large = NULL;
	SDL_FreeSurface(hsiSurface_large);
	hsiSurface_large = NULL;
	SDL_FreeSurface(moneySurface_large);
	moneySurface_large = NULL;
	SDL_FreeSurface(radSurface_large);
	radSurface_large = NULL;
	SDL_FreeSurface(signalSurface_01);
	signalSurface_01 = NULL;
	SDL_FreeSurface(signalSurface_03);
	signalSurface_03 = NULL;
	SDL_FreeSurface(signalSurface_08);
	signalSurface_08 = NULL;
	SDL_FreeSurface(signalSurface_09);
	signalSurface_09 = NULL;
	SDL_FreeSurface(signalSurface_10);
	signalSurface_10 = NULL;
	SDL_FreeSurface(plusSurface);
	plusSurface = NULL;
	SDL_FreeSurface(minusSurface);
	minusSurface = NULL;
	SDL_FreeSurface(plusDisableSurface);
	plusDisableSurface = NULL;
	SDL_FreeSurface(minusDisableSurface);
	minusDisableSurface = NULL;
	SDL_FreeSurface(playSurface);
	playSurface = NULL;
	SDL_FreeSurface(pauseSurface);
	pauseSurface = NULL;
	SDL_FreeSurface(playingSurface);
	playingSurface = NULL;
	SDL_FreeSurface(pausingSurface);
	pausingSurface = NULL;
	SDL_FreeSurface(speedSurface_01);
	speedSurface_01 = NULL;
	//SDL_FreeSurface(speedSurface_02);
	//speedSurface_02 = NULL;
	SDL_FreeSurface(speedSurface_04);
	speedSurface_04 = NULL;
	//SDL_FreeSurface(speedSurface_08);
	//speedSurface_08 = NULL;
	SDL_FreeSurface(speedSurface_16);
	speedSurface_16 = NULL;
	SDL_FreeSurface(speedSurface_32);
	speedSurface_32 = NULL;
	SDL_FreeSurface(speedSurface_01_dark);
	speedSurface_01_dark = NULL;
	SDL_FreeSurface(speedSurface_04_dark);
	speedSurface_04_dark = NULL;
	SDL_FreeSurface(speedSurface_16_dark);
	speedSurface_16_dark = NULL;
	SDL_FreeSurface(speedSurface_32_dark);
	speedSurface_32_dark = NULL;
	SDL_FreeSurface(skillPanelSurface);
	skillPanelSurface = NULL;
	SDL_FreeSurface(skillTreeChainSurface_Empty);
	skillTreeChainSurface_Empty = NULL;
	SDL_FreeSurface(skillTreeChainSurface_Skilled);
	skillTreeChainSurface_Skilled = NULL;
	SDL_FreeSurface(skillTreeRootSurface_Empty);
	skillTreeRootSurface_Empty = NULL;
	SDL_FreeSurface(skillTreeRootSurface_Skilled);
	skillTreeRootSurface_Skilled = NULL;
	SDL_FreeSurface(skillTreeItemSurface_01);
	skillTreeItemSurface_01 = NULL;
	SDL_FreeSurface(skillTreeItemSurface_02);
	skillTreeItemSurface_02 = NULL;
	SDL_FreeSurface(skillTreeItemSurface_03);
	skillTreeItemSurface_03 = NULL;
	SDL_FreeSurface(skillTreeItemSurface_04);
	skillTreeItemSurface_04 = NULL;
	SDL_FreeSurface(skillTreeSkillSurface_01);
	skillTreeSkillSurface_01 = NULL;
	SDL_FreeSurface(skillTreeSkillSurface_02);
	skillTreeSkillSurface_02 = NULL;
	SDL_FreeSurface(skillTreeSkillSurface_03);
	skillTreeSkillSurface_03 = NULL;
	SDL_FreeSurface(skillTreeSkillSurface_04);
	skillTreeSkillSurface_04 = NULL;
	SDL_FreeSurface(skillTreeSkillSurface_05);
	skillTreeSkillSurface_05 = NULL;
	SDL_FreeSurface(closeButtonSurface);
	closeButtonSurface = NULL;
	SDL_FreeSurface(closeLargeButtonSurface);
	closeLargeButtonSurface = NULL;
	SDL_FreeSurface(skillTreeSettingButtonSurface);
	skillTreeSettingButtonSurface = NULL;
	SDL_FreeSurface(typhoonSurface_01);
	typhoonSurface_01 = NULL;
	SDL_FreeSurface(typhoonSurface_02);
	typhoonSurface_02 = NULL;
	SDL_FreeSurface(typhoonSurface_03);
	typhoonSurface_03 = NULL;
	SDL_FreeSurface(typhoonSurface_04);
	typhoonSurface_04 = NULL;
	SDL_FreeSurface(typhoonSurface_05);
	typhoonSurface_05 = NULL;
	SDL_FreeSurface(typhoonSurface_06);
	typhoonSurface_06 = NULL;
	SDL_FreeSurface(typhoonSurface_07);
	typhoonSurface_07 = NULL;
	SDL_FreeSurface(typhoonSurface_08);
	typhoonSurface_08 = NULL;
	SDL_FreeSurface(typhoonSurface_09);
	typhoonSurface_09 = NULL;
	SDL_FreeSurface(typhoonSurface_10);
	typhoonSurface_10 = NULL;
	SDL_FreeSurface(typhoonSurface_11);
	typhoonSurface_11 = NULL;
	SDL_FreeSurface(typhoonSurface_12);
	typhoonSurface_12 = NULL;
	SDL_FreeSurface(typhoonSurface_13);
	typhoonSurface_13 = NULL;
	SDL_FreeSurface(typhoonSurface_14);
	typhoonSurface_14 = NULL;
	SDL_FreeSurface(typhoonSurface_15);
	typhoonSurface_15 = NULL;
	SDL_FreeSurface(typhoonSurface_16);
	typhoonSurface_16 = NULL;

#pragma endregion Dellocate

	//code for the sound here==================
	//Free the sound effects
	Mix_FreeChunk(click_sound);
	click_sound = NULL;
	Mix_FreeChunk(item01_sound);
	item01_sound = NULL;
	Mix_FreeChunk(item02_sound);
	item02_sound = NULL;
	Mix_FreeChunk(item03_sound);
	item03_sound = NULL;
	Mix_FreeChunk(item04_sound);
	item04_sound = NULL;
	Mix_FreeChunk(wind_sound_1);
	wind_sound_1 = NULL;
	Mix_FreeChunk(wind_sound_2);
	wind_sound_2 = NULL;
	Mix_FreeChunk(lvlUp_sound);
	lvlUp_sound = NULL;

	//code for the sound here==================
	//Free the music
	Mix_FreeMusic(bgm);
	bgm = NULL;

	//close the font
	TTF_CloseFont(font_15);
	TTF_CloseFont(font_20);
	TTF_CloseFont(font_24);
	TTF_CloseFont(font_30);
	TTF_CloseFont(font_54);

	//quit SDL_ttf
	TTF_Quit();

	//Destroy window
	SDL_DestroyWindow(g_pWindow);
	g_pWindow = NULL;

	//code for the sound here==================
	Mix_Quit();

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}


#pragma