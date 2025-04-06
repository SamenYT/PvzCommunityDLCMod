#include "GameButton.h"
#include "../../LawnApp.h"
#include "../System/Music.h"
#include "ChallengeScreen.h"
#include "../../Resources.h"
#include "../ToolTipWidget.h"
#include "../System/PlayerInfo.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../Sexy.TodLib/TodFoley.h"
#include "../../Sexy.TodLib/TodCommon.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../GameConstants.h"

#include "../Board.h"
#include "../Cutscene.h"
#include "AlmanacDialog.h"
#include "../LawnCommon.h"
#include "NewOptionsDialog.h"
#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Slider.h"
#include "../../SexyAppFramework/Checkbox.h"



ChallengeDefinition gChallengeDefs[NUM_CHALLENGE_MODES] = {
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_1,              0,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  0,  _S("[SURVIVAL_DAY_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_2,              1,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  1,  _S("[SURVIVAL_NIGHT_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_3,              2,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  2,  _S("[SURVIVAL_POOL_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_4,              3,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  3,  _S("[SURVIVAL_FOG_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_5,              4,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    0,  4,  _S("[SURVIVAL_ROOF_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_6,              0,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    3,  0,  _S("[SURVIVAL_MOON_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_NORMAL_STAGE_7,              3,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    3,  1,  _S("[SURVIVAL_FOREST_NORMAL]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_1,                5,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  0,  _S("[SURVIVAL_DAY_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_2,                6,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  1,  _S("[SURVIVAL_NIGHT_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_3,                7,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  2,  _S("[SURVIVAL_POOL_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_4,                8,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  3,  _S("[SURVIVAL_FOG_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_5,                9,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    1,  4,  _S("[SURVIVAL_ROOF_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_6,                1,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    4,  0,  _S("[SURVIVAL_MOON_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_HARD_STAGE_7,				   4,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    4,  1,  _S("[SURVIVAL_FOREST_HARD]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_1,             10,  ChallengePage::CHALLENGE_PAGE_SURVIVAL,    2,  0,  _S("[SURVIVAL_DAY_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_2,             11,  ChallengePage::CHALLENGE_PAGE_SURVIVAL,    2,  1,  _S("[SURVIVAL_NIGHT_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_3,             12,  ChallengePage::CHALLENGE_PAGE_SURVIVAL,    2,  2,  _S("[SURVIVAL_POOL_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_4,             13,  ChallengePage::CHALLENGE_PAGE_SURVIVAL,    2,  3,  _S("[SURVIVAL_FOG_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_5,             14,  ChallengePage::CHALLENGE_PAGE_SURVIVAL,    2,  4,  _S("[SURVIVAL_ROOF_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_6,             2,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,	   5,  0,  _S("[SURVIVAL_MOON_ENDLESS]") },
	{ GameMode::GAMEMODE_SURVIVAL_ENDLESS_STAGE_7,			   5,   ChallengePage::CHALLENGE_PAGE_SURVIVAL,    5,  1,  _S("[SURVIVAL_FOREST_ENDLESS]") },
	{ GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS,               0,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  0,  _S("[WAR_AND_PEAS]") },
	{ GameMode::GAMEMODE_CHALLENGE_WALLNUT_BOWLING,            6,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  1,  _S("[WALL_NUT_BOWLING]") },
	{ GameMode::GAMEMODE_CHALLENGE_SLOT_MACHINE,               2,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  2,  _S("[SLOT_MACHINE]") },
	{ GameMode::GAMEMODE_CHALLENGE_RAINING_SEEDS,              3,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  3,  _S("[ITS_RAINING_SEEDS]") },
	{ GameMode::GAMEMODE_CHALLENGE_BEGHOULED,                  1,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   0,  4,  _S("[BEGHOULED]") },
	{ GameMode::GAMEMODE_CHALLENGE_INVISIGHOUL,                8,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  0,  _S("[INVISIGHOUL]") },
	{ GameMode::GAMEMODE_CHALLENGE_SEEING_STARS,               5,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  1,  _S("[SEEING_STARS]") },
	{ GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM,               7,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  2,  _S("[ZOMBIQUARIUM]") },
	{ GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST,            20,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  3,  _S("[BEGHOULED_TWIST]") },
	{ GameMode::GAMEMODE_CHALLENGE_LITTLE_TROUBLE,             12,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   1,  4,  _S("[LITTLE_TROUBLE]") },
	{ GameMode::GAMEMODE_CHALLENGE_PORTAL_COMBAT,              15,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  0,  _S("[PORTAL_COMBAT]") },
	{ GameMode::GAMEMODE_CHALLENGE_COLUMN,                     4,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  1,  _S("[COLUMN_AS_YOU_SEE_EM]") },
	{ GameMode::GAMEMODE_CHALLENGE_BOBSLED_BONANZA,            17,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  2,  _S("[BOBSLED_BONANZA]") },
	{ GameMode::GAMEMODE_CHALLENGE_SPEED,                      18,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  3,  _S("[ZOMBIES_ON_SPEED]") },
	{ GameMode::GAMEMODE_CHALLENGE_WHACK_A_ZOMBIE,             16,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   2,  4,  _S("[WHACK_A_ZOMBIE]") },
	{ GameMode::GAMEMODE_CHALLENGE_LAST_STAND,                 21,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  0,  _S("[LAST_STAND]") },
	{ GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS_2,             22,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  1,  _S("[WAR_AND_PEAS_2]") },
	{ GameMode::GAMEMODE_CHALLENGE_WALLNUT_BOWLING_2,          23,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  2,  _S("[WALL_NUT_BOWLING_EXTREME]") },
	{ GameMode::GAMEMODE_CHALLENGE_POGO_PARTY,                 14,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  3,  _S("[POGO_PARTY]") },
	{ GameMode::GAMEMODE_CHALLENGE_FINAL_BOSS,                 19,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   3,  4,  _S("[FINAL_BOSS]") },
	{ GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT,      24,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   4,  0,  _S("[ART_CHALLENGE_WALL_NUT]") },
	{ GameMode::GAMEMODE_CHALLENGE_SUNNY_DAY,                  25,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   4,  1,  _S("[SUNNY_DAY]") },
	{ GameMode::GAMEMODE_CHALLENGE_RESODDED,                   26,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   4,  2,  _S("[UNSODDED]") },
	{ GameMode::GAMEMODE_CHALLENGE_BIG_TIME,                   27,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   4,  3,  _S("[BIG_TIME]") },
	{ GameMode::GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER,    28,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   4,  4,  _S("[ART_CHALLENGE_SUNFLOWER]") },
	{ GameMode::GAMEMODE_CHALLENGE_AIR_RAID,                   29,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   5,  0,  _S("[AIR_RAID]") },
	{ GameMode::GAMEMODE_CHALLENGE_ICE,                        30,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   5,  1,  _S("[ICE_LEVEL]") },
	{ GameMode::GAMEMODE_CHALLENGE_ZEN_GARDEN,                 7,   ChallengePage::CHALLENGE_PAGE_LIMBO,       1,  6,  _S("[ZEN_GARDEN]")},
	{ GameMode::GAMEMODE_CHALLENGE_HIGH_GRAVITY,               32,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   5,  3,  _S("[HIGH_GRAVITY]") },
	{ GameMode::GAMEMODE_CHALLENGE_GRAVE_DANGER,               33,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   5,  4,  _S("[GRAVE_DANGER]") },
	{ GameMode::GAMEMODE_CHALLENGE_SHOVEL,                     34,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   6,  0,  _S("[CAN_YOU_DIG_IT]") },
	{ GameMode::GAMEMODE_CHALLENGE_STORMY_NIGHT,               13,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   6,  1,  _S("[DARK_STORMY_NIGHT]") },
	{ GameMode::GAMEMODE_CHALLENGE_BUNGEE_BLITZ,               9,   ChallengePage::CHALLENGE_PAGE_CHALLENGE,   6,  2,  _S("[BUNGEE_BLITZ]") },
	{ GameMode::GAMEMODE_CHALLENGE_SQUIRREL,                   35,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   5,  2,  _S("Squirrel") },
	{ GameMode::GAMEMODE_SCARY_POTTER_1,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  0,  _S("[SCARY_POTTER_1]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_2,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  1,  _S("[SCARY_POTTER_2]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_3,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  2,  _S("[SCARY_POTTER_3]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_4,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  3,  _S("[SCARY_POTTER_4]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_5,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      0,  4,  _S("[SCARY_POTTER_5]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_6,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  0,  _S("[SCARY_POTTER_6]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_7,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  1,  _S("[SCARY_POTTER_7]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_8,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  2,  _S("[SCARY_POTTER_8]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_9,                       10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  3,  _S("[SCARY_POTTER_9]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_ENDLESS,                 10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      1,  4,  _S("[SCARY_POTTER_ENDLESS]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_1,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  0,  _S("[I_ZOMBIE_1]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_2,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  1,  _S("[I_ZOMBIE_2]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_3,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  2,  _S("[I_ZOMBIE_3]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_4,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  3,  _S("[I_ZOMBIE_4]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_5,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      2,  4,  _S("[I_ZOMBIE_5]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_6,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  0,  _S("[I_ZOMBIE_6]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_7,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  1,  _S("[I_ZOMBIE_7]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_8,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  2,  _S("[I_ZOMBIE_8]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_9,                    11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  3,  _S("[I_ZOMBIE_9]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS,              11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      3,  4,  _S("[I_ZOMBIE_ENDLESS]") },
	{ GameMode::GAMEMODE_CHALLENGE_BIG_TROUBLE,				   40,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   6,  3,  _S("[BIG_TROUBLE]") },
	{ GameMode::GAMEMODE_CHALLENGE_SEASTAR,					   39,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   6,  4,  _S("[MINIGAME_SEASTAR]") },
	{ GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS_3,             43,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   7,  0,  _S("[WAR_AND_PEAS_3]") },
	{ GameMode::GAMEMODE_CHALLENGE_BOMBALL,					   42,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   7,  1,  _S("[BOMB_ALL_TOGETHER]") },
	{ GameMode::GAMEMODE_CHALLENGE_WALLNUT_BOWLING_3,          44,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   7,  2,  _S("[WALL_NUT_BOWLING_3]") },
	{ GameMode::GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES,           41,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   7,  3,  _S("[ZOMBIESVSZOMBIES]") },
	{ GameMode::GAMEMODE_CHALLENGE_GLADIANTUAR,				   45,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   7,  4,  _S("[MINIGAME_GLADIANTUAR]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_11,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      4,  0,  _S("[SCARY_POTTER_11]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_12,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      4,  1,  _S("[SCARY_POTTER_12]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_13,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      4,  2,  _S("[SCARY_POTTER_13]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_14,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      4,  3,  _S("[SCARY_POTTER_14]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_15,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      4,  4,  _S("[SCARY_POTTER_15]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_16,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      5,  0,  _S("[SCARY_POTTER_16]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_17,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      5,  1,  _S("[SCARY_POTTER_17]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_18,                      10,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      5,  2,  _S("[SCARY_POTTER_18]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_19,                      47,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      5,  3,  _S("[SCARY_POTTER_19]") },
	{ GameMode::GAMEMODE_SCARY_POTTER_20,					   47,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      5,  4,  _S("[SCARY_POTTER_20]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_11,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      6,  0,  _S("[I_ZOMBIE_11]")},
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_12,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      6,  1,  _S("[I_ZOMBIE_12]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_13,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      6,  2,  _S("[I_ZOMBIE_13]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_14,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      6,  3,  _S("[I_ZOMBIE_14]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_15,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE,      6,  4,  _S("[I_ZOMBIE_15]") },
	/*{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_16,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE2,     3,  0,  _S("[I_ZOMBIE_16]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_17,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE2,     3,  1,  _S("[I_ZOMBIE_17]")},
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_18,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE2,     3,  2,  _S("[I_ZOMBIE_18]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_19,                   11,  ChallengePage::CHALLENGE_PAGE_PUZZLE2,     3,  3,  _S("[I_ZOMBIE_19]") },
	{ GameMode::GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS,	           11,  ChallengePage::CHALLENGE_PAGE_PUZZLE2,     3,  4,  _S("[I_ZOMBIE_ENDLESS]") }, */
	{ GameMode::GAMEMODE_CHALLENGE_GLITCH,				       48,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   8,  0,  _S("[MINIGAME_GLITCH]") },
	{ GameMode::GAMEMODE_CHALLENGE_FLIPPED,				       49,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   8,  1,  _S("[MINIGAME_FLIPPED]") },
	{ GameMode::GAMEMODE_CHALLENGE_GIGA,				       50,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   8,  2,  _S("[MINIGAME_GIGA]") },
	{ GameMode::GAMEMODE_CHALLENGE_DARK,				       51,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   8,  3,  _S("[MINIGAME_DARK]") },
	{ GameMode::GAMEMODE_CHALLENGE_SMASH,				       52,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   8,  4,  _S("[MINIGAME_SMASH]") },
	{ GameMode::GAMEMODE_CHALLENGE_HIGHGROUND,				   53,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   9,  0,  _S("[MINIGAME_HIGHGROUND]") },
	{ GameMode::GAMEMODE_CHALLENGE_PLANTS_VS_PLANTS,	       54,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   9,  1,  _S("[MINIGAME_PLANTS_VS_PLANTS]") },
	{ GameMode::GAMEMODE_CHALLENGE_ECLIPSE,					   55,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   9,  2,  _S("[MINIGAME_ECLIPSE]") },
	{ GameMode::GAMEMODE_CHALLENGE_WOOD,					   56,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   9,  3,  _S("[MINIGAME_WOOD]") },
	{ GameMode::GAMEMODE_CHALLENGE_BORDER,					   57,  ChallengePage::CHALLENGE_PAGE_CHALLENGE,   9,  4,  _S("[MINIGAME_BORDER]") },
	{ GameMode::GAMEMODE_CHALLENGE_TEST,                       6,   ChallengePage::CHALLENGE_PAGE_CHALLENGE3, -2,  0,  _S("[TEST_LEVEL]") },
	{ GameMode::GAMEMODE_UPSELL,                               10,  ChallengePage::CHALLENGE_PAGE_LIMBO,	   3,  6,  _S("Upsell") },
	{ GameMode::GAMEMODE_INTRO,                                20,  ChallengePage::CHALLENGE_PAGE_LIMBO,	   0,  6,  _S("Intro") },
	{ GameMode::GAMEMODE_TREE_OF_WISDOM,                       10,  ChallengePage::CHALLENGE_PAGE_LIMBO,       2,  6,  _S("Tree Of Wisdom") },
	{ GameMode::GAMEMODE_CHALLENGE_SNOWPEA,					   46,  ChallengePage::CHALLENGE_PAGE_CHALLENGE3,  8,  0,  _S("[SNOWPEA_BOSS]") },
	{ GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS_4,             46,  ChallengePage::CHALLENGE_PAGE_CHALLENGE3,  9,  0,  _S("[WAR_AND_PEAS_4]") },
	{ GameMode::GAMEMODE_CHALLENGE_WAR_AND_PEAS_5,			   53,  ChallengePage::CHALLENGE_PAGE_CHALLENGE3,  9,  0,  _S("[MINIGAME_WAR_AND_PEAS_5]") },
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS,					   0,   ChallengePage::CHALLENGE_PAGE_VERSUS	,  0,  0,  _S("[VERSUSMODE_DAY]") },
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS_FOREST,			   5,   ChallengePage::CHALLENGE_PAGE_VERSUS,	   1,  2,  _S("[VERSUSMODE_FOREST]") },
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS_POOL,			       2,   ChallengePage::CHALLENGE_PAGE_VERSUS,	   0,  2,  _S("[VERSUSMODE_POOL]") },
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS_NIGHT,		       1,   ChallengePage::CHALLENGE_PAGE_VERSUS,	   0,  1,  _S("[VERSUSMODE_NIGHT]") },
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS_FOG,			       3,   ChallengePage::CHALLENGE_PAGE_VERSUS,	   0,  3,  _S("[VERSUSMODE_FOG]") },
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS_ROOF,			       4,   ChallengePage::CHALLENGE_PAGE_VERSUS,	   1,  0,  _S("[VERSUSMODE_ROOF]") }, 
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS_MOON,			       6,   ChallengePage::CHALLENGE_PAGE_VERSUS,	   1,  1,  _S("[VERSUSMODE_MOON]") },
	{ GameMode::GAMEMODE_CHALLENGE_VERSUS_OLD,			       0,   ChallengePage::CHALLENGE_PAGE_VERSUS,	   1,  3,  _S("[VERSUSMODE_OLD]") },
};

Rect challengeClipRect = Rect(10, 92, 778, 475);
//0x42DAE0
ChallengeScreen::ChallengeScreen(LawnApp* theApp, ChallengePage thePage)
{
	mLockShakeX = 0;
	mLockShakeY = 0;
	mPageIndex = thePage;
	mApp = theApp;
	mClip = false;
	mCheatEnableChallenges = false;
	mUnlockState = UNLOCK_OFF;
	mUnlockChallengeIndex = -1;
	mUnlockStateCounter = 0;
	mScrollAmount = 0;
	mScrollPosition = 0;
	mMaxScrollPosition = 0;
	mHelp = false;
	
	TodLoadResources("DelayLoad_ChallengeScreen");

	mDiscordButton = MakeNewButton(ChallengeScreen::ChallengeScreen_Discord, this, _S(""), nullptr, Sexy::IMAGE_DISCORD_BUTTON, IMAGE_DISCORD_BUTTON_HOVER, IMAGE_DISCORD_BUTTON_DOWN);
	mDiscordButton->mX = 570;
	mDiscordButton->mY = -1000;

	mYoutubeButton = MakeNewButton(ChallengeScreen::ChallengeScreen_Youtube, this, _S(""), nullptr, Sexy::IMAGE_YOUTUBE_BUTTON, IMAGE_YOUTUBE_BUTTON_HOVER, IMAGE_YOUTUBE_BUTTON_HOVER);
	mYoutubeButton->mX = 381;
	mYoutubeButton->mY = -1000;

	mBackButton = MakeNewButton(ChallengeScreen::ChallengeScreen_Back, this, _S("[BACK_TO_MENU]"), nullptr, Sexy::IMAGE_SEEDCHOOSER_BUTTON2,
		Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW, Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW);
	mBackButton->mTextDownOffsetX = 1;
	mBackButton->mTextDownOffsetY = 1;
	mBackButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
	mBackButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
	int aXadjustment = 0;
	if (mPageIndex == CHALLENGE_PAGE_VERSUS || mPageIndex == CHALLENGE_PAGE_CREDITS) aXadjustment = 650;
	mBackButton->Resize(18 + aXadjustment, 568, 111, 26); //18

	mHelpButton = MakeNewButton(ChallengeScreen::ChallengeScreen_Help, this, _S("[VERSUS_BUTTON]"), nullptr, Sexy::IMAGE_SEEDCHOOSER_BUTTON2,
		Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW, Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW);
	mHelpButton->mTextDownOffsetX = 1;
	mHelpButton->mTextDownOffsetY = 1;
	mHelpButton->mColors[ButtonWidget::COLOR_LABEL] = Color(42, 42, 90);
	mHelpButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(42, 42, 90);
	aXadjustment = -5000;
	if (mPageIndex == CHALLENGE_PAGE_VERSUS) aXadjustment = 650;
	mHelpButton->Resize(-100 + aXadjustment, 568, 111, 26); //18

	mOptionButton = MakeNewButton(
		ChallengeScreen::ChallengeScreen_Help,
		this,
		"",
		nullptr,
		Sexy::IMAGE_MULTIPLAYER_OPTION,
		Sexy::IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT,
		Sexy::IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT
	);
	aXadjustment = -5000;
	if (mPageIndex == CHALLENGE_PAGE_VERSUS) aXadjustment = 0;
	mOptionButton->Resize(23 + aXadjustment, 510, 100, 100);
	mOptionButton->mMouseVisible = false;
	mOptionButton->mClip = false;

	if (thePage == CHALLENGE_PAGE_CHALLENGE)
		mMaxScrollPosition = 160;
	else if (thePage == CHALLENGE_PAGE_PUZZLE)
		mMaxScrollPosition = 160;
	else if (thePage == CHALLENGE_PAGE_SURVIVAL)
		mMaxScrollPosition = 160;
	else if (thePage == CHALLENGE_PAGE_DISCLAIMER)
		mMaxScrollPosition = 120;
	else if (thePage == CHALLENGE_PAGE_CREDITS)
		mMaxScrollPosition = 695;
	else
		mMaxScrollPosition = 0;

	for (int aPageIdx = CHALLENGE_PAGE_SURVIVAL; aPageIdx < MAX_CHALLANGE_PAGES; aPageIdx++)
	{
		ButtonWidget* aPageButton = new ButtonWidget(ChallengeScreen::ChallengeScreen_Page + aPageIdx, this);
		aPageButton->mDoFinger = true;
		mPageButton[aPageIdx] = aPageButton;
		if (aPageIdx == CHALLENGE_PAGE_LIMBO)
			//aPageButton->mLabel = TodStringTranslate(_S("Limbo Page"));
			aPageButton->mLabel = TodStringTranslate(_S("Secret"));
		else if (aPageIdx == CHALLENGE_PAGE_CHALLENGE)
			aPageButton->mLabel = TodStringTranslate(_S("Easy"));
		else if (aPageIdx == CHALLENGE_PAGE_CHALLENGE2)
			aPageButton->mLabel = TodStringTranslate(_S("Normal"));
		else if (aPageIdx == CHALLENGE_PAGE_CHALLENGE3)
			aPageButton->mLabel = TodStringTranslate(_S("Hard"));
		else if (aPageIdx == CHALLENGE_PAGE_CHALLENGE4)
			aPageButton->mLabel = TodStringTranslate(_S("Extreme"));
		else if (aPageIdx == CHALLENGE_PAGE_VERSUS)
			aPageButton->mLabel = TodStringTranslate(_S("Impossible"));
		else if (aPageIdx == CHALLENGE_PAGE_PUZZLE)
			aPageButton->mLabel = TodStringTranslate(_S("Easy"));
		else if (aPageIdx == CHALLENGE_PAGE_PUZZLE2)
			aPageButton->mLabel = TodStringTranslate(_S("Normal"));
		else if (aPageIdx == CHALLENGE_PAGE_PUZZLE3)
			aPageButton->mLabel = TodStringTranslate(_S("Hard"));
		else if (aPageIdx == CHALLENGE_PAGE_SURVIVAL)
		aPageButton->mLabel = TodStringTranslate(_S("Survival Page 1"));
		else if (aPageIdx == CHALLENGE_PAGE_SURVIVAL2)
			aPageButton->mLabel = TodStringTranslate(_S("Survival Page 2"));
		else
			aPageButton->mLabel = TodReplaceNumberString(_S("[PAGE_X]"), _S("{PAGE}"), aPageIdx);
		aPageButton->mButtonImage = Sexy::IMAGE_BLANK;
		aPageButton->mOverImage = Sexy::IMAGE_BLANK;
		aPageButton->mDownImage = Sexy::IMAGE_BLANK;
		aPageButton->SetFont(Sexy::FONT_BRIANNETOD12);
		aPageButton->mColors[ButtonWidget::COLOR_LABEL] = Color(255, 240, 0);
		aPageButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color(220, 220, 0);
		if (mPageIndex == CHALLENGE_PAGE_PUZZLE || mPageIndex == CHALLENGE_PAGE_PUZZLE2) aPageButton->Resize(-640 + 100 * aPageIdx, 540, 100, 75);
		else if (mPageIndex == CHALLENGE_PAGE_SURVIVAL2) aPageButton->Resize(+160 + 100 * aPageIdx, 540, 100, 75);
		else if (ShowPageButtons()) aPageButton->Resize(-50 + 100 * aPageIdx, 540, 100, 75);
		else aPageButton->Resize(+160 + 100 * aPageIdx, 540, 100, 75);
		if ((mPageIndex == CHALLENGE_PAGE_CHALLENGE || mPageIndex == CHALLENGE_PAGE_CHALLENGE2 || mPageIndex == CHALLENGE_PAGE_CHALLENGE3) && (aPageIdx == CHALLENGE_PAGE_SURVIVAL || 
			aPageIdx == CHALLENGE_PAGE_PUZZLE || aPageIdx == CHALLENGE_PAGE_PUZZLE2 ||
			aPageIdx == CHALLENGE_PAGE_PUZZLE3 || aPageIdx == CHALLENGE_PAGE_SURVIVAL2)) aPageButton->mVisible = false;
		else if ((mPageIndex == CHALLENGE_PAGE_PUZZLE || mPageIndex == CHALLENGE_PAGE_PUZZLE2) && (aPageIdx == CHALLENGE_PAGE_SURVIVAL || 
				 aPageIdx == CHALLENGE_PAGE_CHALLENGE || aPageIdx == CHALLENGE_PAGE_CHALLENGE2 ||
				 aPageIdx == CHALLENGE_PAGE_CHALLENGE3 || aPageIdx == CHALLENGE_PAGE_CHALLENGE4 || aPageIdx == CHALLENGE_PAGE_VERSUS || aPageIdx == CHALLENGE_PAGE_LIMBO ||
				 aPageIdx == CHALLENGE_PAGE_SURVIVAL2)) aPageButton->mVisible = false;
		else if ((mPageIndex == CHALLENGE_PAGE_SURVIVAL || mPageIndex == CHALLENGE_PAGE_SURVIVAL2) && (aPageIdx == CHALLENGE_PAGE_CHALLENGE || aPageIdx == CHALLENGE_PAGE_CHALLENGE2 ||
			aPageIdx == CHALLENGE_PAGE_CHALLENGE3 || aPageIdx == CHALLENGE_PAGE_CHALLENGE4 || aPageIdx == CHALLENGE_PAGE_VERSUS || aPageIdx == CHALLENGE_PAGE_LIMBO ||
			aPageIdx == CHALLENGE_PAGE_PUZZLE || aPageIdx == CHALLENGE_PAGE_PUZZLE2 || aPageIdx == CHALLENGE_PAGE_PUZZLE3)) aPageButton->mVisible = false;
		//if (!ShowPageButtons() || aPageIdx == CHALLENGE_PAGE_SURVIVAL || aPageIdx == CHALLENGE_PAGE_PUZZLE || aPageIdx == CHALLENGE_PAGE_PUZZLE2 || aPageIdx == CHALLENGE_PAGE_PUZZLE3)
			//aPageButton->mVisible = false;
		//else if (aPageIdx == CHALLENGE_PAGE_CHALLENGE || aPageIdx == CHALLENGE_PAGE_CHALLENGE2 || aPageIdx == CHALLENGE_PAGE_CHALLENGE3 || aPageIdx == CHALLENGE_PAGE_CHALLENGE ||
			//	 aPageIdx == CHALLENGE_PAGE_CHALLENGE5) aPageButton->mVisible = false;
		aPageButton->mVisible = false;
	}
	

	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aChlDef = GetChallengeDefinition(aChallengeMode);
		ButtonWidget* aChallengeButton = new ButtonWidget(ChallengeScreen::ChallengeScreen_Mode + aChallengeMode, this);
		mChallengeButtons[aChallengeMode] = aChallengeButton;
		aChallengeButton->mDoFinger = true;
		aChallengeButton->mFrameNoDraw = true;
		if (aChlDef.mPage == CHALLENGE_PAGE_CHALLENGE || aChlDef.mPage == CHALLENGE_PAGE_LIMBO || aChlDef.mPage == CHALLENGE_PAGE_PUZZLE || aChlDef.mPage == CHALLENGE_PAGE_CHALLENGE2 ||
			aChlDef.mPage == CHALLENGE_PAGE_CHALLENGE3 || aChlDef.mPage == CHALLENGE_PAGE_CHALLENGE4 || aChlDef.mPage == CHALLENGE_PAGE_PUZZLE2 ||
			aChlDef.mPage == CHALLENGE_PAGE_PUZZLE3) //teleport spaceing
			aChallengeButton->Resize(38 + aChlDef.mCol * 155, 93 + aChlDef.mRow * 119, 104, 115);
		else if (aChlDef.mPage == CHALLENGE_PAGE_VERSUS)
			aChallengeButton->Resize(140 + aChlDef.mCol * 140, 200 + aChlDef.mRow * 119, 104, 115);
		else
			aChallengeButton->Resize(38 + aChlDef.mCol * 155, 125 + aChlDef.mRow * 145, 104, 115);

		if (MoreTrophiesNeeded(aChallengeMode))
		{
			aChallengeButton->mDoFinger = false;
			aChallengeButton->mDisabled = true;
		}
	}

	mToolTip = new ToolTipWidget();
	mToolTip->mCenter = true;
	mToolTip->mVisible = false;
	UpdateButtons();
	
	if (mApp->mGameMode != GAMEMODE_UPSELL || mApp->mGameScene != SCENE_LEVEL_INTRO)
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);

	bool aIsIZombie = false;
	if (mPageIndex == CHALLENGE_PAGE_SURVIVAL && mApp->mPlayerInfo->mHasNewSurvival)
	{
		SetUnlockChallengeIndex(mPageIndex, false);
		mApp->mPlayerInfo->mHasNewSurvival = false;
	}
	else if (mPageIndex == CHALLENGE_PAGE_CHALLENGE && mApp->mPlayerInfo->mHasNewMiniGame)
	{
		SetUnlockChallengeIndex(mPageIndex, false);
		mApp->mPlayerInfo->mHasNewMiniGame = false;
	}
	else if (mPageIndex == CHALLENGE_PAGE_PUZZLE)
	{
		if (mApp->mPlayerInfo->mHasNewScaryPotter)
		{
			SetUnlockChallengeIndex(mPageIndex, false);
			mApp->mPlayerInfo->mHasNewScaryPotter = false;
		}
		else if (mApp->mPlayerInfo->mHasNewIZombie)
		{
			SetUnlockChallengeIndex(mPageIndex, true);
			mApp->mPlayerInfo->mHasNewIZombie = false;
		}
	}
	mSlider = new Sexy::Slider(IMAGE_OPTIONS_SLIDERSLOT4, IMAGE_OPTIONS_SLIDERKNOB3, 0, this);
	mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)));
	mSlider->mHorizontal = false;
	mSlider->Resize(768, 90, 40, 475);
	mSlider->mThumbOffsetX -= 9;
	if (mPageIndex == CHALLENGE_PAGE_VERSUS) mSlider->SetVisible(false);
}

void ChallengeScreen::SliderVal(int theId, double theVal)
{
	switch (theId)
	{
	case 0:
		mScrollPosition = theVal * mMaxScrollPosition;
		break;
	}
}

//0x42E280 & 0x42E2A0
ChallengeScreen::~ChallengeScreen()
{
	delete mBackButton;
	delete mHelpButton;
	delete mOptionButton;
	delete mDiscordButton;
	delete mYoutubeButton;
	for (ButtonWidget* aPageButton : mPageButton) delete aPageButton;
	for (ButtonWidget* aChallengeButton : mChallengeButtons) delete aChallengeButton;
	delete mSlider;
	delete mToolTip;
}

ChallengeDefinition& GetChallengeDefinition(int theChallengeMode)
{
	TOD_ASSERT(theChallengeMode >= 0 && theChallengeMode < NUM_CHALLENGE_MODES);

	ChallengeDefinition& aDef = gChallengeDefs[theChallengeMode];
	//TOD_ASSERT();
	aDef.mChallengeMode == theChallengeMode + GAMEMODE_SURVIVAL_NORMAL_STAGE_1;
	return gChallengeDefs[theChallengeMode];
}

bool ChallengeScreen::IsScaryPotterLevel(GameMode theGameMode)
{
	return (theGameMode >= GAMEMODE_SCARY_POTTER_1 && theGameMode <= GAMEMODE_SCARY_POTTER_ENDLESS);
}

bool ChallengeScreen::IsIZombieLevel(GameMode theGameMode)
{
	return theGameMode >= GAMEMODE_PUZZLE_I_ZOMBIE_1 && theGameMode <= GAMEMODE_PUZZLE_I_ZOMBIE_ENDLESS;
}

//0x42E3C0
void ChallengeScreen::SetUnlockChallengeIndex(ChallengePage thePage, bool theIsIZombie)
{
	mUnlockState = UNLOCK_SHAKING;
	mUnlockStateCounter = 10;
	mUnlockChallengeIndex = 0;
	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aDef = GetChallengeDefinition(aChallengeMode);
		if (aDef.mPage == thePage)
		{
			if (thePage != CHALLENGE_PAGE_PUZZLE || (!theIsIZombie && IsScaryPotterLevel(aDef.mChallengeMode)) || (theIsIZombie && IsIZombieLevel(aDef.mChallengeMode)))
			{
				if (AccomplishmentsNeeded(aChallengeMode) <= 0)
				{
					mUnlockChallengeIndex = aChallengeMode;
				}
			}
		}
	}
}

//0x42E440
int ChallengeScreen::MoreTrophiesNeeded(int theChallengeIndex)
{
	ChallengeDefinition& aDef = GetChallengeDefinition(theChallengeIndex);
	if (mApp->mGameMode == GAMEMODE_UPSELL && mApp->mGameScene == SCENE_LEVEL_INTRO)
	{
		return aDef.mChallengeMode == GAMEMODE_CHALLENGE_FINAL_BOSS ? 1 : 0;
	}
	
	if (mApp->IsTrialStageLocked())
	{
		if (mPageIndex == CHALLENGE_PAGE_PUZZLE && aDef.mChallengeMode >= GAMEMODE_SCARY_POTTER_4)
		{
			return aDef.mChallengeMode == GAMEMODE_SCARY_POTTER_4 ? 1 : 2;
		}
		else if (mPageIndex == CHALLENGE_PAGE_CHALLENGE && aDef.mChallengeMode >= GAMEMODE_CHALLENGE_RAINING_SEEDS)
		{
			return aDef.mChallengeMode == GAMEMODE_CHALLENGE_RAINING_SEEDS ? 1 : 2;
		}
		else if (mPageIndex == CHALLENGE_PAGE_SURVIVAL && aDef.mChallengeMode >= GAMEMODE_SURVIVAL_NORMAL_STAGE_4)
		{
			return aDef.mChallengeMode == GAMEMODE_SURVIVAL_NORMAL_STAGE_4 ? 1 : 2;
		}
	}

	if (aDef.mPage == CHALLENGE_PAGE_PUZZLE)
	{
		if (IsScaryPotterLevel(aDef.mChallengeMode))
		{
			int aLevelsCompleted = 0;
			for (ChallengeDefinition& aSPDef : gChallengeDefs)
			{
				if (IsScaryPotterLevel(aSPDef.mChallengeMode) && mApp->HasBeatenChallenge(aSPDef.mChallengeMode))
				{
					aLevelsCompleted++;
				}
			}

			if (aDef.mChallengeMode < GAMEMODE_SCARY_POTTER_4 || mApp->HasFinishedAdventure() || aLevelsCompleted < 3)
			{
				return ClampInt(aDef.mChallengeMode - GAMEMODE_SCARY_POTTER_1 - aLevelsCompleted, 0, 9);
			}
			else
			{
				return aDef.mChallengeMode == GAMEMODE_SCARY_POTTER_4 ? 1 : 2;
			}
		}
		else if (IsIZombieLevel(aDef.mChallengeMode))
		{
			int aLevelsCompleted = 0;
			for (ChallengeDefinition& aIZDef : gChallengeDefs)
			{
				if (IsIZombieLevel(aIZDef.mChallengeMode) && mApp->HasBeatenChallenge(aIZDef.mChallengeMode))
				{
					aLevelsCompleted++;
				}
			}

			if (aDef.mChallengeMode < GAMEMODE_PUZZLE_I_ZOMBIE_4 || mApp->HasFinishedAdventure() || aLevelsCompleted < 3)
			{
				return ClampInt(aDef.mChallengeMode - GAMEMODE_PUZZLE_I_ZOMBIE_1 - aLevelsCompleted, 0, 9);
			}
			else
			{
				return aDef.mChallengeMode == GAMEMODE_PUZZLE_I_ZOMBIE_4 ? 1 : 2;
			}
		}
	}
	else
	{
		int aIdxInPage = aDef.mRow * 5 + aDef.mCol;
		if (mPageIndex == CHALLENGE_PAGE_SURVIVAL)
		{
			aIdxInPage = aDef.mRow % 3 * 5 + aDef.mCol + floor(aDef.mRow / 3);
		}

		if ((aDef.mPage == CHALLENGE_PAGE_CHALLENGE || aDef.mPage == CHALLENGE_PAGE_SURVIVAL) && !mApp->HasFinishedAdventure())
		{
			return aIdxInPage < 3 ? 0 : aIdxInPage == 3 ? 1 : 2;
		}
		else
		{
			int aNumTrophies = mApp->GetNumTrophies(aDef.mPage);
			if (aDef.mPage == CHALLENGE_PAGE_LIMBO || aDef.mPage == CHALLENGE_PAGE_CHALLENGE2 || aDef.mPage == CHALLENGE_PAGE_CHALLENGE3 || aDef.mPage == CHALLENGE_PAGE_CHALLENGE4 ||
				aDef.mPage == CHALLENGE_PAGE_VERSUS || aDef.mPage == CHALLENGE_PAGE_PUZZLE2 || aDef.mPage == CHALLENGE_PAGE_PUZZLE3 || aDef.mPage == CHALLENGE_PAGE_SURVIVAL2)
			{
				return 0;
			}
			if (mApp->IsSurvivalEndless(aDef.mChallengeMode))
			{
				return 14 - aNumTrophies;
			}
			if (aDef.mPage == CHALLENGE_PAGE_SURVIVAL || aDef.mPage == CHALLENGE_PAGE_CHALLENGE)
			{
				aNumTrophies += 3;
			}
			else
			{
				TOD_ASSERT();
			}

			return aIdxInPage >= aNumTrophies ? aIdxInPage - aNumTrophies + 1 : 0;
		}
	}
}

//0x42E6E0
bool ChallengeScreen::ShowPageButtons()
{
	return mPageIndex != CHALLENGE_PAGE_SURVIVAL && mPageIndex != CHALLENGE_PAGE_PUZZLE;
}

//0x42E710
void ChallengeScreen::UpdateButtons()
{
	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
		mChallengeButtons[aChallengeMode]->mVisible = GetChallengeDefinition(aChallengeMode).mPage == mPageIndex;
	for (int aPage = 0; aPage < MAX_CHALLANGE_PAGES; aPage++)
	{
		ButtonWidget* aPageButton = mPageButton[aPage];
		if (aPage == mPageIndex)
		{
			aPageButton->mColors[ButtonWidget::COLOR_LABEL] = Color(64, 64, 64);
			aPageButton->mDisabled = true;
		}
		else
		{
			aPageButton->mColors[ButtonWidget::COLOR_LABEL] = Color(255, 240, 0);
			aPageButton->mDisabled = false;
		}
	}
}

//0x42E8A0
int ChallengeScreen::AccomplishmentsNeeded(int theChallengeIndex)
{
	int aTrophiesNeeded = MoreTrophiesNeeded(theChallengeIndex);
	GameMode aGameMode = GetChallengeDefinition(theChallengeIndex).mChallengeMode;
	if (mApp->IsSurvivalEndless(aGameMode) && aTrophiesNeeded <= 3 && mApp->GetNumTrophies(CHALLENGE_PAGE_SURVIVAL) < 12 &&
		mApp->HasFinishedAdventure() && !mApp->IsTrialStageLocked()) aTrophiesNeeded = 1;
	return mCheatEnableChallenges ? 0 : aTrophiesNeeded;
}

//0x42E920
void ChallengeScreen::DrawButton(Graphics* g, int theChallengeIndex)
{
	if (mPageIndex == CHALLENGE_PAGE_CREDITS)
	{
		mYoutubeButton->mY = 2100 - mScrollPosition * 10;
		mDiscordButton->mY = 6580 - mScrollPosition * 10;
	}
	ButtonWidget* aChallengeButton = mChallengeButtons[theChallengeIndex];
	if (aChallengeButton->mVisible)
	{
		ChallengeDefinition& aDef = GetChallengeDefinition(theChallengeIndex);

		int offsetY = aDef.mPage == CHALLENGE_PAGE_SURVIVAL ? 125 : 93;
		aChallengeButton->mY = offsetY + aDef.mRow * ((aDef.mPage == CHALLENGE_PAGE_SURVIVAL || aDef.mPage == CHALLENGE_PAGE_VERSUS) ? 145 : 119) - mScrollPosition * 10;

		if (aDef.mPage == CHALLENGE_PAGE_VERSUS) aChallengeButton->mY += 20;

		int aPosX = aChallengeButton->mX;
		int aPosY = aChallengeButton->mY ;

		if (aChallengeButton->mY + 1 >= cSeedClipRect.mY + cSeedClipRect.mHeight || aChallengeButton->mY + 121 <= cSeedClipRect.mY || mApp->mWidgetManager->mLastMouseY >= cSeedClipRect.mY + cSeedClipRect.mHeight || mApp->mWidgetManager->mLastMouseY <= cSeedClipRect.mY)
		{
			aChallengeButton->mY = 600;
		}

		if (!aChallengeButton->mIsDown)
			aChallengeButton->mIsOver = aChallengeButton->Contains(mApp->mWidgetManager->mLastMouseX, mApp->mWidgetManager->mLastMouseY);
		

		if (aChallengeButton->mIsDown)
		{
			aPosX++;
			aPosY++;
		}

		if (AccomplishmentsNeeded(theChallengeIndex) <= 1)
		{
			// ============================================================================================
			// ▲ 绘制按钮上的小游戏图标
			// ============================================================================================
			if (aChallengeButton->mDisabled)
			{
				g->SetColor(Color(92, 92, 92));
				g->SetColorizeImages(true);
			}
			if (theChallengeIndex == mUnlockChallengeIndex)
			{
				if (mUnlockState == UNLOCK_SHAKING)
				{
					g->SetColor(Color(92, 92, 92));
				}
				else if (mUnlockState == UNLOCK_FADING)
				{
					int aColor = TodAnimateCurve(50, 25, mUnlockStateCounter, 92, 255, CURVE_LINEAR);
					g->SetColor(Color(aColor, aColor, aColor));
				}
				g->SetColorizeImages(true);
			}

			g->SetClipRect(challengeClipRect);
			if (aDef.mChallengeMode == GAMEMODE_SURVIVAL_NORMAL_STAGE_6 || aDef.mChallengeMode == GAMEMODE_SURVIVAL_HARD_STAGE_6 || aDef.mChallengeMode == GAMEMODE_SURVIVAL_ENDLESS_STAGE_6)
			{
				g->DrawImageCel(Sexy::IMAGE_NEW_SURVIVAL_THUMBNAIL, aPosX + 13, aPosY + 4, aDef.mChallengeIconIndex);
			}
			else if (aDef.mChallengeMode == GAMEMODE_SURVIVAL_NORMAL_STAGE_7 || aDef.mChallengeMode == GAMEMODE_SURVIVAL_HARD_STAGE_7 || aDef.mChallengeMode == GAMEMODE_SURVIVAL_ENDLESS_STAGE_7)
			{
				g->DrawImageCel(Sexy::IMAGE_NEW_SURVIVAL_THUMBNAIL, aPosX + 13, aPosY + 4, aDef.mChallengeIconIndex);
			}
			else if (mPageIndex == CHALLENGE_PAGE_SURVIVAL)
			{
				g->DrawImageCel(Sexy::IMAGE_SURVIVAL_THUMBNAILS, aPosX + 13, aPosY + 4, aDef.mChallengeIconIndex);
			}
			else if (mPageIndex == CHALLENGE_PAGE_VERSUS)
			{
				g->DrawImageCel(Sexy::IMAGE_MINIGAME_3, aPosX + 3, aPosY + 4, aDef.mChallengeIconIndex);
			}
			else// if (mPageIndex == CHALLENGE_PAGE_CHALLENGE2)
			{
				g->DrawImageCel(Sexy::IMAGE_MINIGAME_2, aPosX + 13, aPosY + 4, aDef.mChallengeIconIndex);
				//g->DrawImageCel(Sexy::IMAGE_CHALLENGE_THUMBNAILS, aPosX + 13, aPosY + 4, aDef.mChallengeIconIndex);
			}

			// ============================================================================================
			// ▲ 绘制小游戏按钮边框
			// ============================================================================================
			bool aHighLight = aChallengeButton->mIsOver && theChallengeIndex != mUnlockChallengeIndex;
			g->SetColorizeImages(false);
			if (mPageIndex == CHALLENGE_PAGE_VERSUS) g->DrawImage(aHighLight ? Sexy::IMAGE_VERSUS_WINDOW_HIGHLIGHT : Sexy::IMAGE_VERSUS_WINDOW, aPosX - 6, aPosY - 2);
			else g->DrawImage(aHighLight ? Sexy::IMAGE_CHALLENGE_WINDOW_HIGHLIGHT : Sexy::IMAGE_CHALLENGE_WINDOW, aPosX - 6, aPosY - 2);

			// ============================================================================================
			// ▲ 绘制小游戏的名称
			// ============================================================================================
			Color aTextColor = aHighLight ? Color(250, 40, 40) : Color(42, 42, 90);
			if (mPageIndex == CHALLENGE_PAGE_VERSUS) aTextColor = aHighLight ? Color(255, 128, 0) : Color(255, 255, 90);
			SexyString aName = TodStringTranslate(aDef.mChallengeName);
			if (aChallengeButton->mDisabled || (theChallengeIndex == mUnlockChallengeIndex && mUnlockState == UNLOCK_SHAKING))
			{
				aName = _S("?");
			}

			g->SetClipRect(challengeClipRect);
			int aNameLen = aName.size();

			if (TodDrawStringWrappedHelper(g, aName, Rect(aPosX + 6, aPosY + 76, 94, 28), Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER, false) < 28)
			{
				TodDrawString(g, aName, aPosX + 52, aPosY + 96, Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER);
			}
			else
			{
				TodDrawStringWrapped(g, aName, Rect(aPosX + 6, aPosY + 76, 94, 28), Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER_VERTICAL_MIDDLE);
			}
			/*
			if (aNameLen < 13)
			{
				TodDrawString(g, aName, aPosX + 52, aPosY + 96 , Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER);
			}
			else
			{
				// 先尝试在名称字符串的后半段取空格以将字符串分隔为两行，若后半段中无空格则在整个字符串中寻找空格
				int aHalfPos = ((mPageIndex == CHALLENGE_PAGE_SURVIVAL || aDef.mPage == CHALLENGE_PAGE_COOP_SURVIVAL) && !aChallengeButton->mDisabled) ? 7 : (aNameLen / 2 - 1);
				const SexyChar* aSpacedChar = _S(aName.c_str() + aHalfPos, _S(' '));
				while(aSpacedChar[0]!=' ')
				{
					aHalfPos++;
					aSpacedChar = _S(aName.c_str() + aHalfPos, _S(' '));
					if(aSpacedChar[0]=='\0')
					{
						aHalfPos--;
						aSpacedChar = _S(aName.c_str() + aHalfPos, _S(' '));
						break;
					}
				}
				aHalfPos--;
				aSpacedChar = _S(aName.c_str() + aHalfPos, _S(' '));


				if (aSpacedChar == nullptr)
				{
					aSpacedChar = _S(aName.c_str(), _S(' '));
				}

				// 分别计算取得两行文本的长度
				int aLine1Len = aNameLen;
				int aLine2Len = 0;
				if (aSpacedChar != nullptr)
				{
					aLine1Len = aSpacedChar - aName.c_str();
					aLine2Len = aNameLen - aLine1Len - 1;
				}

				// 分别绘制两行文本字符串
				auto topStr=aName.substr(0, aLine1Len+1);
				auto botStr=aName.substr(aLine1Len + 1, aLine2Len);
				if (botStr.empty())
				{
					TodDrawString(g, aName, aPosX + 52, aPosY + 96 , Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER);
				}
				else
				{
					TodDrawString(g, topStr, aPosX + 52, aPosY + 88 , Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER);
					if (aLine2Len > 0)
					{
						TodDrawString(g, botStr, aPosX + 52, aPosY + 102 , Sexy::FONT_BRIANNETOD12, aTextColor, DS_ALIGN_CENTER);
					}
				}
			}*/

			// ============================================================================================
			// ▲ 绘制关卡锁定或关卡完成的贴图以及关卡最高记录的文本等
			// ============================================================================================
			int aRecord = mApp->mPlayerInfo->mChallengeRecords[theChallengeIndex];
			if (theChallengeIndex == mUnlockChallengeIndex)
			{
				Image* aLockImage = Sexy::IMAGE_LOCK;
				if (mUnlockState == UNLOCK_FADING)
				{
					aLockImage = Sexy::IMAGE_LOCK_OPEN;
					g->SetColor(Color(255, 255, 255, TodAnimateCurve(25, 0, mUnlockStateCounter, 255, 0, CURVE_LINEAR)));
					g->SetColorizeImages(true);
				}
				TodDrawImageScaledF(g, aLockImage, aPosX + 24 + mLockShakeX, aPosY + 9 + mLockShakeY, 0.7f, 0.7f);
				g->SetColorizeImages(false);
			}
			else if (aRecord > 0 && mPageIndex != CHALLENGE_PAGE_VERSUS)
			{
				if (mApp->HasBeatenChallengeHardmode(aDef.mChallengeMode))
				{
					g->DrawImage(Sexy::IMAGE_MINIGAME_DIAMOND_TROPHY, aPosX - 6, aPosY - 2);
				}
				else if (mApp->HasBeatenChallenge(aDef.mChallengeMode))
				{
					g->DrawImage(Sexy::IMAGE_MINIGAME_TROPHY, aPosX - 6, aPosY - 2);
				}
				else if (mApp->IsEndlessScaryPotter(aDef.mChallengeMode) || mApp->IsEndlessIZombie(aDef.mChallengeMode))
				{
					SexyString aAchievement = TodReplaceNumberString(_S("[LONGEST_STREAK]"), _S("{STREAK}"), aRecord);
					Rect aRect(aPosX, aPosY + 15, 96, 200);
					TodDrawStringWrapped(g, aAchievement, aRect, Sexy::FONT_CONTINUUMBOLD14OUTLINE, Color::White, DS_ALIGN_CENTER);
					TodDrawStringWrapped(g, aAchievement, aRect, Sexy::FONT_CONTINUUMBOLD14, Color(255, 0, 0), DS_ALIGN_CENTER);
				}
				else if (mApp->IsSurvivalEndless(aDef.mChallengeMode))
				{
					SexyString aAchievement = mApp->Pluralize(aRecord, _S("[ONE_FLAG]"), _S("[COUNT_FLAGS]"));
					TodDrawString(g, aAchievement, aPosX + 48, aPosY + 48, Sexy::FONT_CONTINUUMBOLD14OUTLINE, Color::White, DS_ALIGN_CENTER);
					TodDrawString(g, aAchievement, aPosX + 48, aPosY + 48, Sexy::FONT_CONTINUUMBOLD14, Color(255, 0, 0), DS_ALIGN_CENTER);
				}
			}
			else if (aChallengeButton->mDisabled)
			{
				TodDrawImageScaledF(g, Sexy::IMAGE_LOCK, aPosX + 24, aPosY + 9, 0.7f, 0.7f);
			}
			g->ClearClipRect();
		}
		else
		{ 
			g->SetClipRect(challengeClipRect);
			g->DrawImage(Sexy::IMAGE_CHALLENGE_BLANK, aPosX, aPosY);
			g->ClearClipRect();
		}
	}

	g->ClearClipRect();
}

//0x42F160
void ChallengeScreen::Draw(Graphics* g)
{
	g->SetLinearBlend(true);
	if (mPageIndex == CHALLENGE_PAGE_VERSUS)
	{
		g->DrawImage(Sexy::IMAGE_VERSUS_BACKGROUND, 0, 0);
	}
	else
		g->DrawImage(Sexy::IMAGE_CHALLENGE_BACKGROUND, 0, 0);

	SexyString aTitleString = 
		mPageIndex == CHALLENGE_PAGE_SURVIVAL || mPageIndex == CHALLENGE_PAGE_SURVIVAL2 ? _S("[PICK_AREA]") :
		mPageIndex == CHALLENGE_PAGE_PUZZLE || mPageIndex ==  CHALLENGE_PAGE_PUZZLE2 || mPageIndex == CHALLENGE_PAGE_PUZZLE3 ? _S("[SCARY_POTTER]") : mPageIndex == CHALLENGE_PAGE_VERSUS ? _S("") : _S("[PICK_CHALLENGE]");
	TodDrawString(g, aTitleString, 400, 58, Sexy::FONT_HOUSEOFTERROR28, Color(220, 220, 220), DS_ALIGN_CENTER);

	if (mPageIndex == CHALLENGE_PAGE_CREDITS)
	{
		g->DrawImage(Sexy::IMAGE_CREDITSBACKGROUND, 0, 0 - mScrollPosition*10);
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);
	}
	if (mPageIndex == CHALLENGE_PAGE_DISCLAIMER)
	{
		g->DrawImage(Sexy::IMAGE_DISCLAIMERBACKGROUND, 0, 0 - mScrollPosition*10);
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);
	}
	if (mPageIndex == CHALLENGE_PAGE_VERSUS)
	{
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_VERSUS_LOBBY);
	}

	int aTrophiesGot = (!mApp->mPlayerInfo->mHardmodeIsOff ? mApp->GetNumTrophiesHardmode(mPageIndex) : mApp->GetNumTrophies(mPageIndex));
	int aTrophiesTotal = mPageIndex == CHALLENGE_PAGE_SURVIVAL ? 14 : mPageIndex == CHALLENGE_PAGE_CHALLENGE ? 50 : mPageIndex == CHALLENGE_PAGE_PUZZLE ? 33 : 0;
	
	if (aTrophiesTotal > 0)
	{
		SexyString aTrophyString = StrFormat(_S("%d/%d"), aTrophiesGot, aTrophiesTotal);
		TodDrawString(g, aTrophyString, 739, 73, Sexy::FONT_DWARVENTODCRAFT12, Color(255, 240, 0), DS_ALIGN_CENTER);
		TodDrawImageScaledF(g, (!mApp->mPlayerInfo->mHardmodeIsOff ? Sexy::IMAGE_DIAMOND_TROPHY : Sexy::IMAGE_TROPHY), 718, 26, 0.5f, 0.5f);
	}

	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
		DrawButton(g, aChallengeMode);

	mToolTip->Draw(g);

	if (mPageIndex == CHALLENGE_PAGE_CHALLENGE3 || mPageIndex == CHALLENGE_PAGE_CHALLENGE4 || mPageIndex == CHALLENGE_PAGE_PUZZLE3 || mPageIndex == CHALLENGE_PAGE_LIMBO) g->DrawImage(Sexy::IMAGE_LOCKED_ZOMBIE, 0, 0);

	if (mHelp) g->DrawImage(Sexy::IMAGE_VERSUS_NOTE, 0, 0);
}

void ChallengeScreen::MouseWheel(int theDelta)
{
	mScrollAmount -= mBaseScrollSpeed * theDelta;
	mScrollAmount -= mScrollAmount * mScrollAccel;
}


//0x42F510
void ChallengeScreen::Update()
{
	Widget::Update();
	UpdateToolTip();

	float aScrollSpeed = mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel;

	if (mPageIndex == CHALLENGE_PAGE_SURVIVAL || mPageIndex == CHALLENGE_PAGE_PUZZLE || mPageIndex == CHALLENGE_PAGE_CHALLENGE)
	{
		//float aScrollSpeed = mBaseScrollSpeed + abs(mScrollAmount) * mScrollAccel;
		mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * aScrollSpeed, 0, 160);
		mScrollAmount *= (1.0f - mScrollAccel);
	}
	else if (mPageIndex == CHALLENGE_PAGE_CREDITS)
	{
		mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * aScrollSpeed, 0, 695); //amount of scroll
		mScrollAmount *= (1.0f - mScrollAccel);
	}
	else if (mPageIndex == CHALLENGE_PAGE_DISCLAIMER)
	{
		mScrollPosition = ClampFloat(mScrollPosition += mScrollAmount * aScrollSpeed, 0, 120); //amount of scroll
		mScrollAmount *= (1.0f - mScrollAccel);
	}
	mSlider->SetValue(max(0.0, min(mMaxScrollPosition, mScrollPosition)) / mMaxScrollPosition);
	/*for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aChlDef = GetChallengeDefinition(aChallengeMode);
		ButtonWidget* aChallengeButton = mChallengeButtons[aChallengeMode];

		if (aChlDef.mPage == CHALLENGE_PAGE_CHALLENGE || aChlDef.mPage == CHALLENGE_PAGE_LIMBO || aChlDef.mPage == CHALLENGE_PAGE_PUZZLE)
			aChallengeButton->Resize(38 + aChlDef.mCol * 155, 93 - mScrollPosition + aChlDef.mRow * 119, 104, 115);
		else
			aChallengeButton->Resize(38 + aChlDef.mCol * 155, 125 - mScrollPosition + aChlDef.mRow * 145, 104, 115);
	}*/

	if (mUnlockStateCounter > 0) mUnlockStateCounter--;
	if (mUnlockState == UNLOCK_SHAKING)
	{
		if (mUnlockStateCounter == 0)
		{
			mApp->PlayFoley(FOLEY_PAPER);
			mUnlockState = UNLOCK_FADING;
			mUnlockStateCounter = 50;
			mLockShakeX = 0;
			mLockShakeY = 0;
		}
		else
		{
			mLockShakeX = RandRangeFloat(-2, 2);
			mLockShakeY = RandRangeFloat(-2, 2);
		}
	}
	else if (mUnlockState == UNLOCK_FADING && mUnlockStateCounter == 0)
	{
		mUnlockState = UNLOCK_OFF;
		mUnlockStateCounter = 0;
		mUnlockChallengeIndex = -1;
	}

	MarkDirty();
}

//0x42F640
void ChallengeScreen::AddedToManager(WidgetManager* theWidgetManager)
{
	Widget::AddedToManager(theWidgetManager);
	AddWidget(mBackButton);
	AddWidget(mYoutubeButton);
	AddWidget(mDiscordButton);
	AddWidget(mHelpButton);
	AddWidget(mOptionButton);
	AddWidget(mSlider);
	for (ButtonWidget* aButton : mPageButton) AddWidget(aButton);
	for (ButtonWidget* aButton : mChallengeButtons) AddWidget(aButton);
}

//0x42F6B0
void ChallengeScreen::RemovedFromManager(WidgetManager* theWidgetManager)
{
	Widget::RemovedFromManager(theWidgetManager);
	RemoveWidget(mBackButton);
	RemoveWidget(mYoutubeButton);
	RemoveWidget(mDiscordButton);
	RemoveWidget(mHelpButton);
	RemoveWidget(mOptionButton);
	RemoveWidget(mSlider);
	for (ButtonWidget* aButton : mPageButton) RemoveWidget(aButton);
	for (ButtonWidget* aButton : mChallengeButtons) RemoveWidget(aButton);
}

//0x42F720
void ChallengeScreen::ButtonPress(int theId)
{
	mApp->PlaySample(Sexy::SOUND_BUTTONCLICK);
}

//0x42F740
void ChallengeScreen::ButtonDepress(int theId)
{
	if (theId == ChallengeScreen::ChallengeScreen_Back)
	{
		mApp->KillChallengeScreen();
		mApp->DoBackToMain();
	}
	else if (theId == ChallengeScreen::ChallengeScreen_Help)
	{
		mHelp = !mHelp;
	}
	else if (theId == ChallengeScreen::ChallengeScreen_Discord)
	{
		ShellExecute(NULL, "open", "https://discord.gg/rTz2QHD9aR", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (theId == ChallengeScreen::ChallengeScreen_Youtube)
	{
		ShellExecute(NULL, "open", "https://www.youtube.com/@SamenPvz", NULL, NULL, SW_SHOWNORMAL);
	}

	int aChallengeMode = theId - ChallengeScreen::ChallengeScreen_Mode;
	if (aChallengeMode >= 0 && aChallengeMode < NUM_CHALLENGE_MODES)
	{
		mApp->KillChallengeScreen();
		mApp->PreNewGame((GameMode)(aChallengeMode + 1), true);
	}

	int aPageIndex = theId - ChallengeScreen::ChallengeScreen_Page;
	if (aPageIndex >= 0 && aPageIndex < MAX_CHALLANGE_PAGES)
	{
		mPageIndex = (ChallengePage)aPageIndex;
		UpdateButtons();
	}
}

//0x42F7E0
void ChallengeScreen::UpdateToolTip()
{
	if (!mApp->mWidgetManager->mMouseIn || !mApp->mActive)
	{
		mToolTip->mVisible = false;
		return;
	}

	for (int aChallengeMode = 0; aChallengeMode < NUM_CHALLENGE_MODES; aChallengeMode++)
	{
		ChallengeDefinition& aDef = GetChallengeDefinition(aChallengeMode);
		ButtonWidget* aChallengeButton = mChallengeButtons[aChallengeMode];

		if (aChallengeButton->mVisible && aChallengeButton->mDisabled &&
			aChallengeButton->Contains(mApp->mWidgetManager->mLastMouseX, mApp->mWidgetManager->mLastMouseY) &&
			AccomplishmentsNeeded(aChallengeMode) <= 1)
		{
			mToolTip->mX = aChallengeButton->mWidth / 2 + aChallengeButton->mX;
			mToolTip->mY = aChallengeButton->mY;
			if (MoreTrophiesNeeded(aChallengeMode) > 0)
			{
				SexyString aLabel;
				if (mPageIndex == CHALLENGE_PAGE_PUZZLE)
				{
					if (IsScaryPotterLevel(aDef.mChallengeMode))
					{
						if (!mApp->HasFinishedAdventure() && aDef.mChallengeMode == GAMEMODE_SCARY_POTTER_4)
						{
							aLabel = _S("[FINISH_ADVENTURE_TOOLTIP]");
						}
						else
						{
							aLabel = _S("[ONE_MORE_SCARY_POTTER_TOOLTIP]");
						}
					}
					else if (IsIZombieLevel(aDef.mChallengeMode))
					{
						if (!mApp->HasFinishedAdventure() && aDef.mChallengeMode == GAMEMODE_PUZZLE_I_ZOMBIE_4)
						{
							aLabel = _S("[FINISH_ADVENTURE_TOOLTIP]");
						}
						else
						{
							aLabel = _S("[ONE_MORE_IZOMBIE_TOOLTIP]");
						}
					}
				}
				else if (!mApp->HasFinishedAdventure() || mApp->IsTrialStageLocked())
				{
					aLabel = _S("[FINISH_ADVENTURE_TOOLTIP]");
				}
				else if (mApp->IsSurvivalEndless(aDef.mChallengeMode))
				{
					aLabel = _S("[10_SURVIVAL_TOOLTIP]");
				}
				else if (mPageIndex == CHALLENGE_PAGE_SURVIVAL)
				{
					aLabel = _S("[ONE_MORE_SURVIVAL_TOOLTIP]");
				}
				else if (mPageIndex == CHALLENGE_PAGE_CHALLENGE)
				{
					aLabel = _S("[ONE_MORE_CHALLENGE_TOOLTIP]");
				}
				else continue;

				mToolTip->SetLabel(aLabel);
				mToolTip->mVisible = true;
				return;
			} // end if (MoreTrophiesNeeded(aChallengeMode) > 0)
		} // end 需要显示标签的条件判断
	}

	mToolTip->mVisible = false;
}
