#include "Resources.h"
#include "SexyAppFramework/ResourceManager.h"

using namespace Sexy;

#pragma warning(disable:4311 4312)

static bool gNeedRecalcVariableToIdMap = false;

bool Sexy::ExtractResourcesByName(ResourceManager *theManager, const char *theName)
{
	if (strcmp(theName,"DelayLoad_Almanac")==0) return ExtractDelayLoad_AlmanacResources(theManager);
	if (strcmp(theName,"DelayLoad_AwardScreen")==0) return ExtractDelayLoad_AwardScreenResources(theManager);
	if (strcmp(theName,"DelayLoad_Background1")==0) return ExtractDelayLoad_Background1Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background2")==0) return ExtractDelayLoad_Background2Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background3")==0) return ExtractDelayLoad_Background3Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background4")==0) return ExtractDelayLoad_Background4Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background5")==0) return ExtractDelayLoad_Background5Resources(theManager);
	if (strcmp(theName,"DelayLoad_Background6")==0) return ExtractDelayLoad_Background6Resources(theManager);
	if (strcmp(theName,"DelayLoad_BackgroundUnsodded")==0) return ExtractDelayLoad_BackgroundUnsoddedResources(theManager);
	if (strcmp(theName,"DelayLoad_ChallengeScreen")==0) return ExtractDelayLoad_ChallengeScreenResources(theManager);
	if (strcmp(theName,"DelayLoad_Credits")==0) return ExtractDelayLoad_CreditsResources(theManager);
	if (strcmp(theName,"DelayLoad_GreenHouseGarden")==0) return ExtractDelayLoad_GreenHouseGardenResources(theManager);
	if (strcmp(theName,"DelayLoad_GreenHouseOverlay")==0) return ExtractDelayLoad_GreenHouseOverlayResources(theManager);
	if (strcmp(theName,"DelayLoad_MushroomGarden")==0) return ExtractDelayLoad_MushroomGardenResources(theManager);
	if (strcmp(theName,"DelayLoad_Store")==0) return ExtractDelayLoad_StoreResources(theManager);
	if (strcmp(theName,"DelayLoad_TreeOfWisdom")==0) return ExtractDelayLoad_TreeOfWisdomResources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieFinalNote")==0) return ExtractDelayLoad_ZombieFinalNoteResources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote")==0) return ExtractDelayLoad_ZombieNoteResources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote1")==0) return ExtractDelayLoad_ZombieNote1Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote2")==0) return ExtractDelayLoad_ZombieNote2Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote3")==0) return ExtractDelayLoad_ZombieNote3Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote4")==0) return ExtractDelayLoad_ZombieNote4Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote5")==0) return ExtractDelayLoad_ZombieNote5Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNote6")==0) return ExtractDelayLoad_ZombieNote6Resources(theManager);
	if (strcmp(theName,"DelayLoad_ZombieNoteHelp")==0) return ExtractDelayLoad_ZombieNoteHelpResources(theManager);
	if (strcmp(theName,"DelayLoad_Zombiquarium")==0) return ExtractDelayLoad_ZombiquariumResources(theManager);
	if (strcmp(theName,"Init")==0) return ExtractInitResources(theManager);
	if (strcmp(theName,"LoaderBar")==0) return ExtractLoaderBarResources(theManager);
	if (strcmp(theName,"LoadingFonts")==0) return ExtractLoadingFontsResources(theManager);
	if (strcmp(theName,"LoadingImages")==0) return ExtractLoadingImagesResources(theManager);
	if (strcmp(theName,"LoadingSounds")==0) return ExtractLoadingSoundsResources(theManager);
	return false;
}

Sexy::ResourceId Sexy::GetIdByStringId(const char *theStringId)
{
	typedef std::map<std::string,int> MyMap;
	static MyMap aMap;
	if(aMap.empty())
	{
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[GetStringIdById(i)] = i;
	}

	MyMap::iterator anItr = aMap.find(theStringId);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

// DelayLoad_Almanac Resources
Image* Sexy::IMAGE_ALMANAC_CLOSEBUTTON;
Image* Sexy::IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_ALMANAC_GROUNDDAY;
Image* Sexy::IMAGE_ALMANAC_GROUNDICE;
Image* Sexy::IMAGE_ALMANAC_GROUNDFOREST;
Image* Sexy::IMAGE_ALMANAC_GROUNDNIGHT;
Image* Sexy::IMAGE_ALMANAC_GROUNDNIGHTPOOL;
Image* Sexy::IMAGE_ALMANAC_GROUNDPOOL;
Image* Sexy::IMAGE_ALMANAC_GROUNDROOF;
Image* Sexy::IMAGE_ALMANAC_INDEXBACK;
Image* Sexy::IMAGE_ALMANAC_INDEXBUTTON;
Image* Sexy::IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_ALMANAC_PLANTBACK;
Image* Sexy::IMAGE_ALMANAC_PLANTCARD;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEBACK;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEBLANK;
Image* Sexy::IMAGE_ALMANAC_ZOMBIECARD;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW;
Image* Sexy::IMAGE_ALMANAC_ZOMBIEWINDOW2;

bool Sexy::ExtractDelayLoad_AlmanacResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ALMANAC_CLOSEBUTTON = aMgr.GetImageThrow("IMAGE_ALMANAC_CLOSEBUTTON");
		IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT");
		IMAGE_ALMANAC_GROUNDDAY = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDDAY");
		IMAGE_ALMANAC_GROUNDICE = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDICE");
		IMAGE_ALMANAC_GROUNDFOREST = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDFOREST");
		IMAGE_ALMANAC_GROUNDNIGHT = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDNIGHT");
		IMAGE_ALMANAC_GROUNDNIGHTPOOL = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDNIGHTPOOL");
		IMAGE_ALMANAC_GROUNDPOOL = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDPOOL");
		IMAGE_ALMANAC_GROUNDROOF = aMgr.GetImageThrow("IMAGE_ALMANAC_GROUNDROOF");
		IMAGE_ALMANAC_INDEXBACK = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBACK");
		IMAGE_ALMANAC_INDEXBUTTON = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBUTTON");
		IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT");
		IMAGE_ALMANAC_PLANTBACK = aMgr.GetImageThrow("IMAGE_ALMANAC_PLANTBACK");
		IMAGE_ALMANAC_PLANTCARD = aMgr.GetImageThrow("IMAGE_ALMANAC_PLANTCARD");
		IMAGE_ALMANAC_ZOMBIEBACK = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEBACK");
		IMAGE_ALMANAC_ZOMBIEBLANK = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEBLANK");
		IMAGE_ALMANAC_ZOMBIECARD = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIECARD");
		IMAGE_ALMANAC_ZOMBIEWINDOW = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEWINDOW");
		IMAGE_ALMANAC_ZOMBIEWINDOW2 = aMgr.GetImageThrow("IMAGE_ALMANAC_ZOMBIEWINDOW2");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_AwardScreen Resources
Image* Sexy::IMAGE_AWARDSCREEN_BACK;

bool Sexy::ExtractDelayLoad_AwardScreenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_AWARDSCREEN_BACK = aMgr.GetImageThrow("IMAGE_AWARDSCREEN_BACK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background1 Resources
Image* Sexy::IMAGE_BACKGROUND1;
Image* Sexy::IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND1_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background1Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND1 = aMgr.GetImageThrow("IMAGE_BACKGROUND1");
		IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND1_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND1_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background2 Resources
Image* Sexy::IMAGE_BACKGROUND2;
Image* Sexy::IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND2_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background2Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND2 = aMgr.GetImageThrow("IMAGE_BACKGROUND2");
		IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND2_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND2_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background3 Resources
Image* Sexy::IMAGE_BACKGROUND3;
Image* Sexy::IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND3_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background3Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND3 = aMgr.GetImageThrow("IMAGE_BACKGROUND3");
		IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND3_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND3_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background4 Resources
Image* Sexy::IMAGE_BACKGROUND4;
Image* Sexy::IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY;
Image* Sexy::IMAGE_BACKGROUND4_GAMEOVER_MASK;
Image* Sexy::IMAGE_FOG;
Image* Sexy::IMAGE_FOG_SOFTWARE;

bool Sexy::ExtractDelayLoad_Background4Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND4 = aMgr.GetImageThrow("IMAGE_BACKGROUND4");
		IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY");
		IMAGE_BACKGROUND4_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND4_GAMEOVER_MASK");
		IMAGE_FOG = aMgr.GetImageThrow("IMAGE_FOG");
		IMAGE_FOG_SOFTWARE = aMgr.GetImageThrow("IMAGE_FOG_SOFTWARE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background5 Resources
Image* Sexy::IMAGE_BACKGROUND5;
Image* Sexy::IMAGE_BACKGROUND5_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background5Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND5 = aMgr.GetImageThrow("IMAGE_BACKGROUND5");
		IMAGE_BACKGROUND5_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND5_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Background6 Resources
Image* Sexy::IMAGE_BACKGROUND6BOSS;
Image* Sexy::IMAGE_BACKGROUND6_GAMEOVER_MASK;

bool Sexy::ExtractDelayLoad_Background6Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND6BOSS = aMgr.GetImageThrow("IMAGE_BACKGROUND6BOSS");
		IMAGE_BACKGROUND6_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND6_GAMEOVER_MASK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_BackgroundUnsodded Resources
Image* Sexy::IMAGE_BACKGROUND1UNSODDED;
Image* Sexy::IMAGE_SOD1ROW;
Image* Sexy::IMAGE_SOD3ROW;

bool Sexy::ExtractDelayLoad_BackgroundUnsoddedResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND1UNSODDED = aMgr.GetImageThrow("IMAGE_BACKGROUND1UNSODDED");
		IMAGE_SOD1ROW = aMgr.GetImageThrow("IMAGE_SOD1ROW");
		IMAGE_SOD3ROW = aMgr.GetImageThrow("IMAGE_SOD3ROW");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ChallengeScreen Resources
Image* Sexy::IMAGE_CHALLENGE_BACKGROUND;
Image* Sexy::IMAGE_CHALLENGE_BLANK;
Image* Sexy::IMAGE_CHALLENGE_THUMBNAILS;
Image* Sexy::IMAGE_CHALLENGE_WINDOW;
Image* Sexy::IMAGE_CHALLENGE_WINDOW_HIGHLIGHT;
Image* Sexy::IMAGE_LOCK;
Image* Sexy::IMAGE_LOCK_OPEN;
Image* Sexy::IMAGE_SURVIVAL_THUMBNAILS;

bool Sexy::ExtractDelayLoad_ChallengeScreenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_CHALLENGE_BACKGROUND = aMgr.GetImageThrow("IMAGE_CHALLENGE_BACKGROUND");
		IMAGE_CHALLENGE_BLANK = aMgr.GetImageThrow("IMAGE_CHALLENGE_BLANK");
		IMAGE_CHALLENGE_THUMBNAILS = aMgr.GetImageThrow("IMAGE_CHALLENGE_THUMBNAILS");
		IMAGE_CHALLENGE_WINDOW = aMgr.GetImageThrow("IMAGE_CHALLENGE_WINDOW");
		IMAGE_CHALLENGE_WINDOW_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_CHALLENGE_WINDOW_HIGHLIGHT");
		IMAGE_LOCK = aMgr.GetImageThrow("IMAGE_LOCK");
		IMAGE_LOCK_OPEN = aMgr.GetImageThrow("IMAGE_LOCK_OPEN");
		IMAGE_SURVIVAL_THUMBNAILS = aMgr.GetImageThrow("IMAGE_SURVIVAL_THUMBNAILS");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Credits Resources
Font* Sexy::FONT_BRIANNETOD32;
Font* Sexy::FONT_BRIANNETOD32BLACK;
Image* Sexy::IMAGE_CREDITS_PLAYBUTTON;
Image* Sexy::IMAGE_CREDITS_ZOMBIENOTE;
Image* Sexy::IMAGE_REANIM_CREDITS_DISCOLIGHTS;
Image* Sexy::IMAGE_REANIM_CREDITS_FOGMACHINE;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING1;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING2;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING3;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING4;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_SING5;
Image* Sexy::IMAGE_REANIM_SUNFLOWER_HEAD_WINK;

bool Sexy::ExtractDelayLoad_CreditsResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_BRIANNETOD32 = aMgr.GetFontThrow("FONT_BRIANNETOD32");
		FONT_BRIANNETOD32BLACK = aMgr.GetFontThrow("FONT_BRIANNETOD32BLACK");
		IMAGE_CREDITS_PLAYBUTTON = aMgr.GetImageThrow("IMAGE_CREDITS_PLAYBUTTON");
		IMAGE_CREDITS_ZOMBIENOTE = aMgr.GetImageThrow("IMAGE_CREDITS_ZOMBIENOTE");
		IMAGE_REANIM_CREDITS_DISCOLIGHTS = aMgr.GetImageThrow("IMAGE_REANIM_CREDITS_DISCOLIGHTS");
		IMAGE_REANIM_CREDITS_FOGMACHINE = aMgr.GetImageThrow("IMAGE_REANIM_CREDITS_FOGMACHINE");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING1 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING1");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING2 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING2");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING3 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING3");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING4 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING4");
		IMAGE_REANIM_SUNFLOWER_HEAD_SING5 = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_SING5");
		IMAGE_REANIM_SUNFLOWER_HEAD_WINK = aMgr.GetImageThrow("IMAGE_REANIM_SUNFLOWER_HEAD_WINK");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_GreenHouseGarden Resources
Image* Sexy::IMAGE_BACKGROUND_GREENHOUSE;

bool Sexy::ExtractDelayLoad_GreenHouseGardenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND_GREENHOUSE = aMgr.GetImageThrow("IMAGE_BACKGROUND_GREENHOUSE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_GreenHouseOverlay Resources
Image* Sexy::IMAGE_BACKGROUND_GREENHOUSE_OVERLAY;

bool Sexy::ExtractDelayLoad_GreenHouseOverlayResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND_GREENHOUSE_OVERLAY = aMgr.GetImageThrow("IMAGE_BACKGROUND_GREENHOUSE_OVERLAY");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_MushroomGarden Resources
Image* Sexy::IMAGE_BACKGROUND_MUSHROOMGARDEN;

bool Sexy::ExtractDelayLoad_MushroomGardenResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BACKGROUND_MUSHROOMGARDEN = aMgr.GetImageThrow("IMAGE_BACKGROUND_MUSHROOMGARDEN");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Store Resources
Image* Sexy::IMAGE_STORE_AQUARIUMGARDENICON;
Image* Sexy::IMAGE_STORE_BACKGROUND;
Image* Sexy::IMAGE_STORE_BACKGROUNDNIGHT;
Image* Sexy::IMAGE_STORE_CAR;
Image* Sexy::IMAGE_STORE_CARCLOSED;
Image* Sexy::IMAGE_STORE_CARCLOSED_NIGHT;
Image* Sexy::IMAGE_STORE_CAR_NIGHT;
Image* Sexy::IMAGE_STORE_FIRSTAIDWALLNUTICON;
Image* Sexy::IMAGE_STORE_HATCHBACKOPEN;
Image* Sexy::IMAGE_STORE_MAINMENUBUTTON;
Image* Sexy::IMAGE_STORE_MAINMENUBUTTONDOWN;
Image* Sexy::IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_STORE_MUSHROOMGARDENICON;
Image* Sexy::IMAGE_STORE_NEXTBUTTON;
Image* Sexy::IMAGE_STORE_NEXTBUTTONDISABLED;
Image* Sexy::IMAGE_STORE_NEXTBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_STORE_PACKETUPGRADE;
Image* Sexy::IMAGE_STORE_PREVBUTTON;
Image* Sexy::IMAGE_STORE_PREVBUTTONDISABLED;
Image* Sexy::IMAGE_STORE_PREVBUTTONHIGHLIGHT;
Image* Sexy::IMAGE_STORE_PRICETAG;
Image* Sexy::IMAGE_STORE_PVZICON;
Image* Sexy::IMAGE_STORE_SIGN;
Image* Sexy::IMAGE_STORE_TREEOFWISDOMICON;

bool Sexy::ExtractDelayLoad_StoreResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_STORE_AQUARIUMGARDENICON = aMgr.GetImageThrow("IMAGE_STORE_AQUARIUMGARDENICON");
		IMAGE_STORE_BACKGROUND = aMgr.GetImageThrow("IMAGE_STORE_BACKGROUND");
		IMAGE_STORE_BACKGROUNDNIGHT = aMgr.GetImageThrow("IMAGE_STORE_BACKGROUNDNIGHT");
		IMAGE_STORE_CAR = aMgr.GetImageThrow("IMAGE_STORE_CAR");
		IMAGE_STORE_CARCLOSED = aMgr.GetImageThrow("IMAGE_STORE_CARCLOSED");
		IMAGE_STORE_CARCLOSED_NIGHT = aMgr.GetImageThrow("IMAGE_STORE_CARCLOSED_NIGHT");
		IMAGE_STORE_CAR_NIGHT = aMgr.GetImageThrow("IMAGE_STORE_CAR_NIGHT");
		IMAGE_STORE_FIRSTAIDWALLNUTICON = aMgr.GetImageThrow("IMAGE_STORE_FIRSTAIDWALLNUTICON");
		IMAGE_STORE_HATCHBACKOPEN = aMgr.GetImageThrow("IMAGE_STORE_HATCHBACKOPEN");
		IMAGE_STORE_MAINMENUBUTTON = aMgr.GetImageThrow("IMAGE_STORE_MAINMENUBUTTON");
		IMAGE_STORE_MAINMENUBUTTONDOWN = aMgr.GetImageThrow("IMAGE_STORE_MAINMENUBUTTONDOWN");
		IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT");
		IMAGE_STORE_MUSHROOMGARDENICON = aMgr.GetImageThrow("IMAGE_STORE_MUSHROOMGARDENICON");
		IMAGE_STORE_NEXTBUTTON = aMgr.GetImageThrow("IMAGE_STORE_NEXTBUTTON");
		IMAGE_STORE_NEXTBUTTONDISABLED = aMgr.GetImageThrow("IMAGE_STORE_NEXTBUTTONDISABLED");
		IMAGE_STORE_NEXTBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_STORE_NEXTBUTTONHIGHLIGHT");
		IMAGE_STORE_PACKETUPGRADE = aMgr.GetImageThrow("IMAGE_STORE_PACKETUPGRADE");
		IMAGE_STORE_PREVBUTTON = aMgr.GetImageThrow("IMAGE_STORE_PREVBUTTON");
		IMAGE_STORE_PREVBUTTONDISABLED = aMgr.GetImageThrow("IMAGE_STORE_PREVBUTTONDISABLED");
		IMAGE_STORE_PREVBUTTONHIGHLIGHT = aMgr.GetImageThrow("IMAGE_STORE_PREVBUTTONHIGHLIGHT");
		IMAGE_STORE_PRICETAG = aMgr.GetImageThrow("IMAGE_STORE_PRICETAG");
		IMAGE_STORE_PVZICON = aMgr.GetImageThrow("IMAGE_STORE_PVZICON");
		IMAGE_STORE_SIGN = aMgr.GetImageThrow("IMAGE_STORE_SIGN");
		IMAGE_STORE_TREEOFWISDOMICON = aMgr.GetImageThrow("IMAGE_STORE_TREEOFWISDOMICON");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_TreeOfWisdom Resources

bool Sexy::ExtractDelayLoad_TreeOfWisdomResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieFinalNote Resources
Image* Sexy::IMAGE_ZOMBIE_FINAL_NOTE;

bool Sexy::ExtractDelayLoad_ZombieFinalNoteResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_FINAL_NOTE = aMgr.GetImageThrow("IMAGE_ZOMBIE_FINAL_NOTE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE;

bool Sexy::ExtractDelayLoad_ZombieNoteResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote1 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE1;

bool Sexy::ExtractDelayLoad_ZombieNote1Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE1 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE1");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote2 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE2;

bool Sexy::ExtractDelayLoad_ZombieNote2Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE2 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE2");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote3 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE3;

bool Sexy::ExtractDelayLoad_ZombieNote3Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE3 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE3");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote4 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE4;

bool Sexy::ExtractDelayLoad_ZombieNote4Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE4 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE4");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote5 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE5;

bool Sexy::ExtractDelayLoad_ZombieNote5Resources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE5 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE5");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNote6 Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE6;

bool Sexy::ExtractDelayLoad_ZombieNote6Resources(ResourceManager* theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager& aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE6 = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE6");
	}
	catch (ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_ZombieNoteHelp Resources
Image* Sexy::IMAGE_ZOMBIE_NOTE_HELP;

bool Sexy::ExtractDelayLoad_ZombieNoteHelpResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ZOMBIE_NOTE_HELP = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE_HELP");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// DelayLoad_Zombiquarium Resources
Image* Sexy::IMAGE_AQUARIUM1;
Image* Sexy::IMAGE_WAVECENTER;
Image* Sexy::IMAGE_WAVESIDE;

bool Sexy::ExtractDelayLoad_ZombiquariumResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_AQUARIUM1 = aMgr.GetImageThrow("IMAGE_AQUARIUM1");
		IMAGE_WAVECENTER = aMgr.GetImageThrow("IMAGE_WAVECENTER");
		IMAGE_WAVESIDE = aMgr.GetImageThrow("IMAGE_WAVESIDE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// Init Resources
Image* Sexy::IMAGE_BLANK;
Image* Sexy::IMAGE_PARTNER_LOGO;
Image* Sexy::IMAGE_POPCAP_LOGO;
Image* Sexy::IMAGE_NEW_LOGO;

bool Sexy::ExtractInitResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_BLANK = aMgr.GetImageThrow("IMAGE_BLANK");
		IMAGE_PARTNER_LOGO = aMgr.GetImageThrow("IMAGE_PARTNER_LOGO");
		IMAGE_POPCAP_LOGO = aMgr.GetImageThrow("IMAGE_POPCAP_LOGO");
		IMAGE_NEW_LOGO = aMgr.GetImageThrow("IMAGE_NEW_LOGO");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoaderBar Resources
Font* Sexy::FONT_BRIANNETOD16;
Image* Sexy::IMAGE_LOADBAR_DIRT;
Image* Sexy::IMAGE_LOADBAR_GRASS;
Image* Sexy::IMAGE_PVZ_LOGO;
Image* Sexy::IMAGE_REANIM_SODROLLCAP;
Image* Sexy::IMAGE_TITLESCREEN;
int Sexy::SOUND_BUTTONCLICK;
int Sexy::SOUND_LOADINGBAR_FLOWER;
int Sexy::SOUND_LOADINGBAR_ZOMBIE;

bool Sexy::ExtractLoaderBarResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_BRIANNETOD16 = aMgr.GetFontThrow("FONT_BRIANNETOD16");
		IMAGE_LOADBAR_DIRT = aMgr.GetImageThrow("IMAGE_LOADBAR_DIRT");
		IMAGE_LOADBAR_GRASS = aMgr.GetImageThrow("IMAGE_LOADBAR_GRASS");
		IMAGE_PVZ_LOGO = aMgr.GetImageThrow("IMAGE_PVZ_LOGO");
		IMAGE_REANIM_SODROLLCAP = aMgr.GetImageThrow("IMAGE_REANIM_SODROLLCAP");
		IMAGE_TITLESCREEN = aMgr.GetImageThrow("IMAGE_TITLESCREEN");
		SOUND_BUTTONCLICK = aMgr.GetSoundThrow("SOUND_BUTTONCLICK");
		SOUND_LOADINGBAR_FLOWER = aMgr.GetSoundThrow("SOUND_LOADINGBAR_FLOWER");
		SOUND_LOADINGBAR_ZOMBIE = aMgr.GetSoundThrow("SOUND_LOADINGBAR_ZOMBIE");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoadingFonts Resources
Font* Sexy::FONT_BRIANNETOD12;
//Font* Sexy::FONT_BRIANNETOD9;
Font* Sexy::FONT_PIX118BOLD;
Font* Sexy::FONT_CONTINUUMBOLD14;
Font* Sexy::FONT_CONTINUUMBOLD14OUTLINE;
Font* Sexy::FONT_DWARVENTODCRAFT12;
Font* Sexy::FONT_DWARVENTODCRAFT15;
Font* Sexy::FONT_DWARVENTODCRAFT18;
Font* Sexy::FONT_DWARVENTODCRAFT18BRIGHTGREENINSET;
Font* Sexy::FONT_DWARVENTODCRAFT18GREENINSET;
Font* Sexy::FONT_DWARVENTODCRAFT18YELLOW;
Font* Sexy::FONT_DWARVENTODCRAFT24;
Font* Sexy::FONT_DWARVENTODCRAFT36BRIGHTGREENINSET;
Font* Sexy::FONT_DWARVENTODCRAFT36GREENINSET;
Font* Sexy::FONT_HOUSEOFTERROR16;
Font* Sexy::FONT_HOUSEOFTERROR20;
Font* Sexy::FONT_HOUSEOFTERROR28;
Image* Sexy::FONT_IMAGE_HOUSEOFTERROR28;
Font* Sexy::FONT_LUCKFIXHOUSEOFTERROR15;
Font* Sexy::FONT_PICO129;
Font* Sexy::FONT_TINYBOLD;

bool Sexy::ExtractLoadingFontsResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		FONT_BRIANNETOD12 = aMgr.GetFontThrow("FONT_BRIANNETOD12");
		//FONT_BRIANNETOD9 = aMgr.GetFontThrow("FONT_BRIANNETOD9");
		FONT_PIX118BOLD = aMgr.GetFontThrow("FONT_PIX118BOLD");
		FONT_CONTINUUMBOLD14 = aMgr.GetFontThrow("FONT_CONTINUUMBOLD14");
		FONT_CONTINUUMBOLD14OUTLINE = aMgr.GetFontThrow("FONT_CONTINUUMBOLD14OUTLINE");
		FONT_DWARVENTODCRAFT12 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT12");
		FONT_DWARVENTODCRAFT15 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT15");
		FONT_DWARVENTODCRAFT18 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18");
		FONT_DWARVENTODCRAFT18BRIGHTGREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18BRIGHTGREENINSET");
		FONT_DWARVENTODCRAFT18GREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18GREENINSET");
		FONT_DWARVENTODCRAFT18YELLOW = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT18YELLOW");
		FONT_DWARVENTODCRAFT24 = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT24");
		FONT_DWARVENTODCRAFT36BRIGHTGREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT36BRIGHTGREENINSET");
		FONT_DWARVENTODCRAFT36GREENINSET = aMgr.GetFontThrow("FONT_DWARVENTODCRAFT36GREENINSET");
		FONT_HOUSEOFTERROR16 = aMgr.GetFontThrow("FONT_HOUSEOFTERROR16");
		FONT_HOUSEOFTERROR20 = aMgr.GetFontThrow("FONT_HOUSEOFTERROR20");
		FONT_HOUSEOFTERROR28 = aMgr.GetFontThrow("FONT_HOUSEOFTERROR28");
		FONT_IMAGE_HOUSEOFTERROR28 = aMgr.GetImageThrow("FONT_IMAGE_HOUSEOFTERROR28");
		FONT_LUCKFIXHOUSEOFTERROR15 = aMgr.GetFontThrow("FONT_LUCKFIXHOUSEOFTERROR15");
		FONT_PICO129 = aMgr.GetFontThrow("FONT_PICO129");
		FONT_TINYBOLD = aMgr.GetFontThrow("FONT_TINYBOLD");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoadingImages Resources
Image* Sexy::IMAGE_ALMANAC;
Image* Sexy::IMAGE_ALMANAC_IMITATER;
Image* Sexy::IMAGE_ALMANAC_PLANTBACK_2;
Image* Sexy::IMAGE_ALMANAC_SHIRT;
Image* Sexy::IMAGE_ALMANAC_GOLDEN_LOCK;
Image* Sexy::IMAGE_AWARDPICKUPGLOW;
Image* Sexy::IMAGE_BACKGROUND_FOREST;
Image* Sexy::IMAGE_BACKGROUND_GLADIANTUAR;
Image* Sexy::IMAGE_BACKGROUND_HIGHGROUND;
Image* Sexy::IMAGE_BACKGROUND_ICE;
Image* Sexy::IMAGE_BACKGROUND_PP;
Image* Sexy::IMAGE_BEGHOULED_TWIST_OVERLAY;
Image* Sexy::IMAGE_BEJEWEL_SELECTORSHADOW;
Image* Sexy::IMAGE_BOMBALL;
Image* Sexy::IMAGE_BRAIN;
Image* Sexy::IMAGE_BRAINBANK;
Image* Sexy::IMAGE_BRAINBANK_SMALL;
Image* Sexy::IMAGE_BUG_SPRAY;
Image* Sexy::IMAGE_BUNGEECORD;
Image* Sexy::IMAGE_BUNGEETARGET;
Image* Sexy::IMAGE_BUTTON_DOWN_LEFT;
Image* Sexy::IMAGE_BUTTON_DOWN_MIDDLE;
Image* Sexy::IMAGE_BUTTON_DOWN_RIGHT;
Image* Sexy::IMAGE_BUTTON_LEFT;
Image* Sexy::IMAGE_BUTTON_MIDDLE;
Image* Sexy::IMAGE_BUTTON_RIGHT;
Image* Sexy::IMAGE_CARKEYS;
Image* Sexy::IMAGE_CHOCOLATE;
Image* Sexy::IMAGE_COBCANNON_POPCORN;
Image* Sexy::IMAGE_COBCANNON_TARGET;
Image* Sexy::IMAGE_COINBANK;
Image* Sexy::IMAGE_CONVEYORBELT;
Image* Sexy::IMAGE_CONVEYORBELT_BACKDROP;
Image* Sexy::IMAGE_CRATER;
Image* Sexy::IMAGE_CRATER_FADING;
Image* Sexy::IMAGE_BACKGROUND_BLOODMOON;
Image* Sexy::IMAGE_CRATER_ROOF_CENTER;
Image* Sexy::IMAGE_CRATER_ROOF_LEFT;
Image* Sexy::IMAGE_CRATER_WATER_DAY;
Image* Sexy::IMAGE_CRATER_WATER_NIGHT;
Image* Sexy::IMAGE_CROSS;
Image* Sexy::IMAGE_C_FLAG1;
Image* Sexy::IMAGE_C_FLAG2;
Image* Sexy::IMAGE_DA_FLAG1;
Image* Sexy::IMAGE_DA_FLAG2;
Image* Sexy::IMAGE_DIALOG_BIGBOTTOMLEFT;
Image* Sexy::IMAGE_DIALOG_BIGBOTTOMMIDDLE;
Image* Sexy::IMAGE_DIALOG_BIGBOTTOMRIGHT;
Image* Sexy::IMAGE_DIALOG_BOTTOMLEFT;
Image* Sexy::IMAGE_DIALOG_BOTTOMMIDDLE;
Image* Sexy::IMAGE_DIALOG_BOTTOMRIGHT;
Image* Sexy::IMAGE_DIALOG_CENTERLEFT;
Image* Sexy::IMAGE_DIALOG_CENTERMIDDLE;
Image* Sexy::IMAGE_DIALOG_CENTERRIGHT;
Image* Sexy::IMAGE_DIALOG_HEADER;
Image* Sexy::IMAGE_DIALOG_TOPLEFT;
Image* Sexy::IMAGE_DIALOG_TOPMIDDLE;
Image* Sexy::IMAGE_DIALOG_TOPRIGHT;
Image* Sexy::IMAGE_DIRTBIG;
Image* Sexy::IMAGE_DIRTSMALL;
Image* Sexy::IMAGE_DOOMSHROOM_EXPLOSION_BASE;
Image* Sexy::IMAGE_DUST_PUFFS;
Image* Sexy::IMAGE_D_FLAG1;
Image* Sexy::IMAGE_D_FLAG2;
Image* Sexy::IMAGE_EDITBOX;
Image* Sexy::IMAGE_ELECTRIC;
Image* Sexy::IMAGE_E_FLAG1;
Image* Sexy::IMAGE_E_FLAG2;
Image* Sexy::IMAGE_FERTILIZER;
Image* Sexy::IMAGE_FF1;
Image* Sexy::IMAGE_FF2;
Image* Sexy::IMAGE_FLAGMETER;
Image* Sexy::IMAGE_FLAGMETERLEVELPROGRESS;
Image* Sexy::IMAGE_FLAGMETERPARTS;
Image* Sexy::IMAGE_FLAGMETERPARTS_HARDMODE;
Image* Sexy::IMAGE_F_FLAG1;
Image* Sexy::IMAGE_F_FLAG2;
Image* Sexy::IMAGE_HW_FLAG1;
Image* Sexy::IMAGE_HW_FLAG2;
Image* Sexy::IMAGE_ICE;
Image* Sexy::IMAGE_ICETRAP;
Image* Sexy::IMAGE_ICETRAP2;
Image* Sexy::IMAGE_ICETRAP_PARTICLES;
Image* Sexy::IMAGE_ICE_CAP;
Image* Sexy::IMAGE_ICE_SPARKLES;
Image* Sexy::IMAGE_ICON_POOLCLEANER;
Image* Sexy::IMAGE_ICON_RAKE;
Image* Sexy::IMAGE_ICON_ROOFCLEANER;
Image* Sexy::IMAGE_IMITATERCLOUDS;
Image* Sexy::IMAGE_IMITATERPUFFS;
Image* Sexy::IMAGE_IMITATERSEED;
Image* Sexy::IMAGE_IMITATERSEEDDISABLED;
Image* Sexy::IMAGE_IP_FLAG1;
Image* Sexy::IMAGE_IP_FLAG2;
Image* Sexy::IMAGE_KF_FLAG1;
Image* Sexy::IMAGE_KF_FLAG2;
Image* Sexy::IMAGE_LOCKED_ZOMBIE;
Image* Sexy::IMAGE_L_BUTTON1;
Image* Sexy::IMAGE_L_BUTTON2;
Image* Sexy::IMAGE_MA_FLAG1;
Image* Sexy::IMAGE_MA_FLAG2;
Image* Sexy::IMAGE_MELONPULT_PARTICLES;
Image* Sexy::IMAGE_MINIGAME_2;
Image* Sexy::IMAGE_MINIGAME_TROPHY;
Image* Sexy::IMAGE_MONEYBAG;
Image* Sexy::IMAGE_MONEYBAG_HI_RES;
Image* Sexy::IMAGE_M_FLAG1;
Image* Sexy::IMAGE_M_FLAG2;
Image* Sexy::IMAGE_NEW_SURVIVAL_THUMBNAIL;
Image* Sexy::IMAGE_NIGHT_GRAVE_GRAPHIC;
Image* Sexy::IMAGE_OAK_ARROW;
Image* Sexy::IMAGE_OPTIONS_BACKTOGAMEBUTTON0;
Image* Sexy::IMAGE_OPTIONS_BACKTOGAMEBUTTON2;
Image* Sexy::IMAGE_OPTIONS_CHECKBOX0;
Image* Sexy::IMAGE_OPTIONS_CHECKBOX1;
Image* Sexy::IMAGE_OPTIONS_MENUBACK;
Image* Sexy::IMAGE_OPTIONS_SLIDERKNOB2;
Image* Sexy::IMAGE_OPTIONS_SLIDERSLOT;
Image* Sexy::IMAGE_P1_1;
Image* Sexy::IMAGE_P1_2;
Image* Sexy::IMAGE_P1_3;
Image* Sexy::IMAGE_P2_1;
Image* Sexy::IMAGE_P2_2;
Image* Sexy::IMAGE_P2_3;
Image* Sexy::IMAGE_PACKET_PLANTS;
Image* Sexy::IMAGE_PEA_PARTICLES;
Image* Sexy::IMAGE_PEA_SHADOWS;
Image* Sexy::IMAGE_PEA_SPLATS;
Image* Sexy::IMAGE_PHONOGRAPH;
Image* Sexy::IMAGE_PINATA;
Image* Sexy::IMAGE_PLANTSHADOW;
Image* Sexy::IMAGE_PLANTSHADOW2;
Image* Sexy::IMAGE_PLANTSPEECHBUBBLE;
Image* Sexy::IMAGE_POOL;
Image* Sexy::IMAGE_POOLSPARKLY;
Image* Sexy::IMAGE_POOL_BASE;
Image* Sexy::IMAGE_POOL_BASE_NIGHT;
Image* Sexy::IMAGE_POOL_CAUSTIC_EFFECT;
Image* Sexy::IMAGE_POOL_NIGHT;
Image* Sexy::IMAGE_POOL_SHADING;
Image* Sexy::IMAGE_POOL_SHADING_NIGHT;
Image* Sexy::IMAGE_POTATOMINE_PARTICLES;
Image* Sexy::IMAGE_PRESENT;
Image* Sexy::IMAGE_PRESENTOPEN;
Image* Sexy::IMAGE_PROJECTILECACTUS;
Image* Sexy::IMAGE_PROJECTILEICEQUEEN;
Image* Sexy::IMAGE_PROJECTILEPEA;
Image* Sexy::IMAGE_PROJECTILESNOWPEA;
Image* Sexy::IMAGE_PROJECTILE_SEASTAR;
Image* Sexy::IMAGE_PROJECTILE_STAR;
Image* Sexy::IMAGE_PR_FLAG1;
Image* Sexy::IMAGE_PR_FLAG2;
Image* Sexy::IMAGE_PUDDLE;
Image* Sexy::IMAGE_PUFFSHROOM_PUFF1;
Image* Sexy::IMAGE_RAIN;
Image* Sexy::IMAGE_MINIGAME_DIAMOND_TROPHY;
Image* Sexy::IMAGE_REANIM_CABBAGEPULT_CABBAGE;
Image* Sexy::IMAGE_REANIM_COBCANNON_COB;
Image* Sexy::IMAGE_REANIM_COINGLOW;
Image* Sexy::IMAGE_REANIM_COIN_GOLD_DOLLAR;
Image* Sexy::IMAGE_REANIM_COIN_SILVER_DOLLAR;
Image* Sexy::IMAGE_REANIM_CORNPULT_BUTTER;
Image* Sexy::IMAGE_REANIM_CORNPULT_BUTTER_SPLAT;
Image* Sexy::IMAGE_REANIM_CORNPULT_KERNAL;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH1;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH4;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH5;
Image* Sexy::IMAGE_REANIM_CRAZYDAVE_MOUTH6;
Image* Sexy::IMAGE_REANIM_DIAMOND;
Image* Sexy::IMAGE_REANIM_FIRESHROOM_BODY2;
Image* Sexy::IMAGE_REANIM_FIRESHROOM_CRACKED1;
Image* Sexy::IMAGE_REANIM_FIRESHROOM_CRACKED2;
Image* Sexy::IMAGE_REANIM_GARLIC_BODY2;
Image* Sexy::IMAGE_REANIM_GARLIC_BODY3;
Image* Sexy::IMAGE_REANIM_MELONPULT_MELON;
Image* Sexy::IMAGE_REANIM_POT_TOP_DARK;
Image* Sexy::IMAGE_REANIM_PUMPKIN_DAMAGE1;
Image* Sexy::IMAGE_REANIM_PUMPKIN_DAMAGE3;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_BG;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3;
Image* Sexy::IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS;
Image* Sexy::IMAGE_REANIM_STINKY_TURN3;
Image* Sexy::IMAGE_REANIM_TALLNUT_CRACKED1;
Image* Sexy::IMAGE_REANIM_TALLNUT_CRACKED2;
Image* Sexy::IMAGE_REANIM_DUMMY_CRACKED1;
Image* Sexy::IMAGE_REANIM_DUMMY_CRACKED2;
Image* Sexy::IMAGE_REANIM_TREE_BG;
Image* Sexy::IMAGE_REANIM_WALLNUT_BODY;
Image* Sexy::IMAGE_REANIM_WALLNUT_CRACKED1;
Image* Sexy::IMAGE_REANIM_WALLNUT_CRACKED2;
Image* Sexy::IMAGE_REANIM_WINTERMELON_PROJECTILE;
Image* Sexy::IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CONE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CONE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_CONE3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DANCER_INNERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FLAG1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FLAG3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_AXE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET_RED;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_HAND_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER_REDEYE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ICE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ICE3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE;
Image* Sexy::IMAGE_REANIM_ZOMBIE_IMP_ARM2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_JACKBOX_BOX;
Image* Sexy::IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_5;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_MUSTACHE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_MUSTACHE3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_HEAD_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET1_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET2_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_BUCKET3_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER1_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER2_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER3_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER4_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER5_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER6_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER7_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER8_GIGA;
Image* Sexy::IMAGE_REANIM_ZOMBIE_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_PAPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_PAPER_PAPER3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FISHER_HAT;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCARE_HEAD;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCARE_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCREENDOOR1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCREENDOOR2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SCREENDOOR3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_TRASHCAN1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_TRASHCAN2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_TRASHCAN3;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD;
Image* Sexy::IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_VAMPIRE_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_FISHERMAN_OUTERARM_UPPER;
Image* Sexy::IMAGE_REANIM_ZOMBIE_LEAFBLOWER_OUTERARM_UPPER;
Image* Sexy::IMAGE_REANIM_ZOMBIE_AXE_OUTERARM_UPPER;
Image* Sexy::IMAGE_REANIM_ZOMBIE_AXE_HAT;
Image* Sexy::IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND;
Image* Sexy::IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2;
Image* Sexy::IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT;
Image* Sexy::IMAGE_ROCKSMALL;
Image* Sexy::IMAGE_R_BUTTON1;
Image* Sexy::IMAGE_R_BUTTON2;
Image* Sexy::IMAGE_R_FLAG1;
Image* Sexy::IMAGE_R_FLAG2;
Image* Sexy::IMAGE_SCARY_POT;
Image* Sexy::IMAGE_SEEDBANK;
Image* Sexy::IMAGE_SEEDBANK_SMALL;
Image* Sexy::IMAGE_SEEDCHOOSER_BACKGROUND;
Image* Sexy::IMAGE_SEEDCHOOSER_BACKGROUND_ZOMBIES;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON2;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON_DISABLED;
Image* Sexy::IMAGE_SEEDCHOOSER_BUTTON_GLOW;
Image* Sexy::IMAGE_SEEDCHOOSER_IMITATERADDON;
Image* Sexy::IMAGE_SEEDPACKETFLASH;
Image* Sexy::IMAGE_SEEDPACKETSILHOUETTE;
Image* Sexy::IMAGE_SEEDPACKET_LARGER;
Image* Sexy::IMAGE_SEEDS;
Image* Sexy::IMAGE_SELECTORSCREEN_ALMANAC;
Image* Sexy::IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT;
Image* Sexy::IMAGE_SELECTORSCREEN_HELP1;
Image* Sexy::IMAGE_SELECTORSCREEN_HELP2;
Image* Sexy::IMAGE_SELECTORSCREEN_LEVELNUMBERS;
Image* Sexy::IMAGE_SELECTORSCREEN_OPTIONS1;
Image* Sexy::IMAGE_SELECTORSCREEN_OPTIONS2;
Image* Sexy::IMAGE_SELECTORSCREEN_QUIT1;
Image* Sexy::IMAGE_SELECTORSCREEN_QUIT2;
Image* Sexy::IMAGE_SELECTORSCREEN_STORE;
Image* Sexy::IMAGE_SELECTORSCREEN_STOREHIGHLIGHT;
Image* Sexy::IMAGE_SELECTORSCREEN_ZENGARDEN;
Image* Sexy::IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT;
Image* Sexy::IMAGE_SHOVEL;
Image* Sexy::IMAGE_SHOVELBANK;
Image* Sexy::IMAGE_SHOVEL_HI_RES;
Image* Sexy::IMAGE_SH_FLAG1;
Image* Sexy::IMAGE_SH_FLAG2;
Image* Sexy::IMAGE_SLOTMACHINE_OVERLAY;
Image* Sexy::IMAGE_SNOWFLAKES;
Image* Sexy::IMAGE_SNOWPEA_PARTICLES;
Image* Sexy::IMAGE_SNOWPEA_PUFF;
Image* Sexy::IMAGE_SNOWPEA_SPLATS;
Image* Sexy::IMAGE_SPOTLIGHT;
Image* Sexy::IMAGE_SPOTLIGHT2;
Image* Sexy::IMAGE_STAR_PARTICLES;
Image* Sexy::IMAGE_STAR_SPLATS;
Image* Sexy::IMAGE_STONE2;
Image* Sexy::IMAGE_STONE3;
Image* Sexy::IMAGE_STONE4;
Image* Sexy::IMAGE_STONE5;
Image* Sexy::IMAGE_STORE_SPEECHBUBBLE;
Image* Sexy::IMAGE_STORE_SPEECHBUBBLE2;
Image* Sexy::IMAGE_SUNBANK;
Image* Sexy::IMAGE_SUNFLOWER_TROPHY;
Image* Sexy::IMAGE_DIAMOND_SUNFLOWER_TROPHY;
Image* Sexy::IMAGE_S_FLAG1;
Image* Sexy::IMAGE_S_FLAG2;
Image* Sexy::IMAGE_TACO;
Image* Sexy::IMAGE_TARGET;
Image* Sexy::IMAGE_TARGET_1;
Image* Sexy::IMAGE_TARGET_2;
Image* Sexy::IMAGE_TARGET_3;
Image* Sexy::IMAGE_TOMBSTONES;
Image* Sexy::IMAGE_TOMBSTONE_MOUNDS;
Image* Sexy::IMAGE_TREEFOOD;
Image* Sexy::IMAGE_TROPHY;
Image* Sexy::IMAGE_DIAMOND_TROPHY;
Image* Sexy::IMAGE_TROPHY_HI_RES;
Image* Sexy::IMAGE_DIAMOND_TROPHY_HI_RES;
Image* Sexy::IMAGE_VASE_CHUNKS;
Image* Sexy::IMAGE_VERSUS_BUTTON;
Image* Sexy::IMAGE_VERSUS_BUTTON_HIGHLIGHTED;
Image* Sexy::IMAGE_WALLNUTPARTICLESLARGE;
Image* Sexy::IMAGE_WALLNUTPARTICLESSMALL;
Image* Sexy::IMAGE_WALLNUT_BOWLINGSTRIPE;
Image* Sexy::IMAGE_FLOWER_STRIPE;
Image* Sexy::IMAGE_WATERDROP;
Image* Sexy::IMAGE_WATERINGCAN;
Image* Sexy::IMAGE_WATERINGCANGOLD;
Image* Sexy::IMAGE_WATERPARTICLE;
Image* Sexy::IMAGE_WHITEPIXEL;
Image* Sexy::IMAGE_WHITEWATER;
Image* Sexy::IMAGE_WHITEWATER_SHADOW;
Image* Sexy::IMAGE_WINTERMELON_PARTICLES;
Image* Sexy::IMAGE_YY_FLAG1;
Image* Sexy::IMAGE_YY_FLAG2;
Image* Sexy::IMAGE_ZAMBONISMOKE;
Image* Sexy::IMAGE_ZENSHOPBUTTON;
Image* Sexy::IMAGE_ZENSHOPBUTTON_HIGHLIGHT;
Image* Sexy::IMAGE_ZEN_GARDENGLOVE;
Image* Sexy::IMAGE_ZEN_GOLDTOOLRETICLE;
Image* Sexy::IMAGE_ZEN_MONEYSIGN;
Image* Sexy::IMAGE_ZEN_NEED_ICONS;
Image* Sexy::IMAGE_ZEN_NEXTGARDEN;
Image* Sexy::IMAGE_ZEN_WHEELBARROW;
Image* Sexy::IMAGE_ZOMBIEBACKUPDANCERARM;
Image* Sexy::IMAGE_ZOMBIEBACKUPDANCERHEAD;
Image* Sexy::IMAGE_ZOMBIEBALLOONHEAD;
Image* Sexy::IMAGE_ZOMBIEBOBSLEDHEAD;
Image* Sexy::IMAGE_ZOMBIEDANCERARM;
Image* Sexy::IMAGE_ZOMBIEDANCERHEAD;
Image* Sexy::IMAGE_ZOMBIEDIGGERARM;
Image* Sexy::IMAGE_ZOMBIEDIGGERHEAD;
Image* Sexy::IMAGE_ZOMBIEDOLPHINRIDERHEAD;
Image* Sexy::IMAGE_ZOMBIEFOOTBALLHEAD;
Image* Sexy::IMAGE_ZOMBIEFUTUREGLASSES;
Image* Sexy::IMAGE_ZOMBIEIMPHEAD;
Image* Sexy::IMAGE_ZOMBIEJACKBOXARM;
Image* Sexy::IMAGE_ZOMBIELADDERARM;
Image* Sexy::IMAGE_ZOMBIELADDERHEAD;
Image* Sexy::IMAGE_ZOMBIEPAPERARM;
Image* Sexy::IMAGE_ZOMBIEPOGO;
Image* Sexy::IMAGE_ZOMBIEPOGOARM;
Image* Sexy::IMAGE_ZOMBIEPOLEVAULTERARM;
Image* Sexy::IMAGE_ZOMBIEPOLEVAULTERHEAD;
Image* Sexy::IMAGE_ZOMBIESCARECROWARM;
Image* Sexy::IMAGE_ZOMBIEFISHERARM;
Image* Sexy::IMAGE_ZOMBIEHUNTERARM;
Image* Sexy::IMAGE_ZOMBIELEAFBLOWERARM;
Image* Sexy::IMAGE_ZOMBIEAXEARM;
Image* Sexy::IMAGE_ZOMBIEBIGFOOTARM;
Image* Sexy::IMAGE_ZOMBIEVAMPIREARM;
Image* Sexy::IMAGE_ZOMBIEVAMPIREHEAD;
Image* Sexy::IMAGE_ZOMBIEFISHERHEAD;
Image* Sexy::IMAGE_ZOMBIELEAFBLOWERHEAD;
Image* Sexy::IMAGE_ZOMBIEAXEHEAD;
Image* Sexy::IMAGE_ZOMBIEBIGFOOTHEAD;
Image* Sexy::IMAGE_ZOMBIEYETIHEAD;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED1;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED2;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED3;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED4;
Image* Sexy::IMAGE_ZOMBIE_BOBSLED_INSIDE;
Image* Sexy::IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES;
Image* Sexy::IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES;
Image* Sexy::IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES;
Image* Sexy::IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES;
Image* Sexy::IMAGE_ZOMBIE_NOTE_SMALL;
Image* Sexy::IMAGE_ZOMBIE_PACK;
Image* Sexy::IMAGE_ZOMBIE_SEAWEED;
Image* Sexy::IMAGE_ZOMBOSS_PARTICLES;
Image* Sexy::IMAGE_Z_FLAG1;
Image* Sexy::IMAGE_Z_FLAG2;
Image* Sexy::IMAGE_CREDITSBACKGROUND;
Image* Sexy::IMAGE_DISCLAIMERBACKGROUND;
Image* Sexy::IMAGE_CREDITS_BTN1;
Image* Sexy::IMAGE_CREDITS_BTN2;
Image* Sexy::IMAGE_CROW1;
Image* Sexy::IMAGE_CROW2;
Image* Sexy::IMAGE_VIOLET_PADDLE;
Image* Sexy::IMAGE_FOREST_OBJECTS;
Image* Sexy::IMAGE_LOG1;
Image* Sexy::IMAGE_LOG2;
Image* Sexy::IMAGE_LOG3;
Image* Sexy::IMAGE_GEM_RED;
Image* Sexy::IMAGE_GEM_GREEN;
Image* Sexy::IMAGE_GEM_WHITE;
Image* Sexy::IMAGE_GEM_PURPLE;
Image* Sexy::IMAGE_GEM_YELLOW;
Image* Sexy::IMAGE_GEM_ORANGE;
Image* Sexy::IMAGE_DISCLAIMER_BTN1;
Image* Sexy::IMAGE_DISCLAIMER_BTN2;
Image* Sexy::IMAGE_FLASHLIGHT_LIGHT;
Image* Sexy::IMAGE_FOREST_NIGHT_MAP;
Image* Sexy::IMAGE_FOREST_NIGHT_ITEMS;
Image* Sexy::IMAGE_VINENUT_2;
Image* Sexy::IMAGE_VINENUT_3;
Image* Sexy::IMAGE_VINENUT_2_BODY;
Image* Sexy::IMAGE_VINENUT_3_BODY;
Image* Sexy::IMAGE_NET;
Image* Sexy::IMAGE_GAME;
Image* Sexy::IMAGE_GAME2;
Image* Sexy::IMAGE_WOOD;
Image* Sexy::IMAGE_HUNTER_HAT;
Image* Sexy::IMAGE_VERSUS_NOTE;
Image* Sexy::IMAGE_BACKGROUND7_GAMEOVER_MASK;
Image* Sexy::IMAGE_BACKGROUNDPP_GAMEOVER_MASK;
Image* Sexy::IMAGE_BACKGROUND_GLADIANTUAR_GAMEOVER_MASK;
Image* Sexy::IMAGE_WOODS_NOTE;
Image* Sexy::IMAGE_SHOVEL_ROTATED;
Image* Sexy::IMAGE_ICON_WOODCHIPPER;
Image* Sexy::IMAGE_ICON_NEW;
Image* Sexy::IMAGE_PLAYER1_MOUSE;
Image* Sexy::IMAGE_PLAYER2_MOUSE;
Image* Sexy::IMAGE_PLAYER1_KEYBOARD;
Image* Sexy::IMAGE_PLAYER2_KEYBOARD;
Image* Sexy::IMAGE_OPTIONS_SLIDERKNOB3;
Image* Sexy::IMAGE_OPTIONS_SLIDERSLOT4;
Image* Sexy::IMAGE_DISCORD_BUTTON;
Image* Sexy::IMAGE_DISCORD_BUTTON_HOVER;
Image* Sexy::IMAGE_DISCORD_BUTTON_DOWN;
Image* Sexy::IMAGE_GIGA_HEAD;
Image* Sexy::IMAGE_GIGA_POLE_HEAD;
Image* Sexy::IMAGE_GIGA_PROGRESS_FLAG;
Image* Sexy::IMAGE_BOWLING_STRIPE_POOL;
Image* Sexy::IMAGE_BOWLING_STRIPE_ROOF;
Image* Sexy::IMAGE_BOWLING_STRIPE_ROOF_VERSUS;
Image* Sexy::IMAGE_PLANT_TROPHY;
Image* Sexy::IMAGE_PLANT_TROPHY_HIGH_RES;
Image* Sexy::IMAGE_ZOMBIE_TROPHY;
Image* Sexy::IMAGE_ZOMBIE_TROPHY_HIGH_RES;
Image* Sexy::IMAGE_VERSUS_BACKGROUND;
Image* Sexy::IMAGE_VERSUS_WINDOW;
Image* Sexy::IMAGE_VERSUS_WINDOW_HIGHLIGHT;
Image* Sexy::IMAGE_MINIGAME_3;
Image* Sexy::IMAGE_MULTIPLAYER_OPTION;
Image* Sexy::IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT;
Image* Sexy::IMAGE_GRAVESTONE_ROOF1;
Image* Sexy::IMAGE_GRAVESTONE_ROOF2;
Image* Sexy::IMAGE_GRAVESTONE_ROOF3;
Image* Sexy::IMAGE_GRAVESTONE_ROOF4;
Image* Sexy::IMAGE_GRAVESTONE_ROOF5;
Image* Sexy::IMAGE_GRAVESTONE_ROOF6;
Image* Sexy::IMAGE_GRAVESTONE_NIGHT_DIRT;
Image* Sexy::IMAGE_MAP_FLIPPED;
Image* Sexy::IMAGE_ZOMBIEPOLE;
Image* Sexy::IMAGE_STICK;
Image* Sexy::IMAGE_GAME_OVER_FLIPPED;
Image* Sexy::IMAGE_REANIM_BUSH_PARTICLE1;
Image* Sexy::IMAGE_REANIM_BUSH_PARTICLE2;
Image* Sexy::IMAGE_REANIM_BUSH_PARTICLE3;
Image* Sexy::IMAGE_REANIM_BUSH_PARTICLE4;
Image* Sexy::IMAGE_ZOMBIE_BUSHES;
Image* Sexy::IMAGE_YOUTUBE_BUTTON;
Image* Sexy::IMAGE_YOUTUBE_BUTTON_HOVER;
Image* Sexy::IMAGE_STONEBUTTON_RIGHT;
Image* Sexy::IMAGE_STONEBUTTON_RIGHT_HOVER;
Image* Sexy::IMAGE_STONEBUTTON_LEFT;
Image* Sexy::IMAGE_STONEBUTTON_LEFT_HOVER;
Image* Sexy::IMAGE_RHYTHM_NUMBERGRID;

bool Sexy::ExtractLoadingImagesResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		IMAGE_ALMANAC = aMgr.GetImageThrow("IMAGE_ALMANAC");
		IMAGE_ALMANAC_IMITATER = aMgr.GetImageThrow("IMAGE_ALMANAC_IMITATER");
		IMAGE_ALMANAC_PLANTBACK_2 = aMgr.GetImageThrow("IMAGE_ALMANAC_PLANTBACK_2");
		IMAGE_ALMANAC_SHIRT = aMgr.GetImageThrow("IMAGE_ALMANAC_SHIRT");
		IMAGE_ALMANAC_GOLDEN_LOCK = aMgr.GetImageThrow("IMAGE_ALMANAC_GOLDEN_LOCK");
		IMAGE_AWARDPICKUPGLOW = aMgr.GetImageThrow("IMAGE_AWARDPICKUPGLOW");
		IMAGE_BACKGROUND_FOREST = aMgr.GetImageThrow("IMAGE_BACKGROUND_FOREST");
		IMAGE_BACKGROUND_GLADIANTUAR = aMgr.GetImageThrow("IMAGE_BACKGROUND_GLADIANTUAR");
		IMAGE_BACKGROUND_HIGHGROUND = aMgr.GetImageThrow("IMAGE_BACKGROUND_HIGHGROUND");
		IMAGE_BACKGROUND_ICE = aMgr.GetImageThrow("IMAGE_BACKGROUND_ICE");
		IMAGE_BACKGROUND_PP = aMgr.GetImageThrow("IMAGE_BACKGROUND_PP");
		IMAGE_BEGHOULED_TWIST_OVERLAY = aMgr.GetImageThrow("IMAGE_BEGHOULED_TWIST_OVERLAY");
		IMAGE_BEJEWEL_SELECTORSHADOW = aMgr.GetImageThrow("IMAGE_BEJEWEL_SELECTORSHADOW");
		IMAGE_BOMBALL = aMgr.GetImageThrow("IMAGE_BOMBALL");
		IMAGE_BRAIN = aMgr.GetImageThrow("IMAGE_BRAIN");
		IMAGE_BRAINBANK = aMgr.GetImageThrow("IMAGE_BRAINBANK");
		IMAGE_BRAINBANK_SMALL = aMgr.GetImageThrow("IMAGE_BRAINBANK_SMALL");
		IMAGE_BUG_SPRAY = aMgr.GetImageThrow("IMAGE_BUG_SPRAY");
		IMAGE_BUNGEECORD = aMgr.GetImageThrow("IMAGE_BUNGEECORD");
		IMAGE_BUNGEETARGET = aMgr.GetImageThrow("IMAGE_BUNGEETARGET");
		IMAGE_BUTTON_DOWN_LEFT = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN_LEFT");
		IMAGE_BUTTON_DOWN_MIDDLE = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN_MIDDLE");
		IMAGE_BUTTON_DOWN_RIGHT = aMgr.GetImageThrow("IMAGE_BUTTON_DOWN_RIGHT");
		IMAGE_BUTTON_LEFT = aMgr.GetImageThrow("IMAGE_BUTTON_LEFT");
		IMAGE_BUTTON_MIDDLE = aMgr.GetImageThrow("IMAGE_BUTTON_MIDDLE");
		IMAGE_BUTTON_RIGHT = aMgr.GetImageThrow("IMAGE_BUTTON_RIGHT");
		IMAGE_CARKEYS = aMgr.GetImageThrow("IMAGE_CARKEYS");
		IMAGE_CHOCOLATE = aMgr.GetImageThrow("IMAGE_CHOCOLATE");
		IMAGE_COBCANNON_POPCORN = aMgr.GetImageThrow("IMAGE_COBCANNON_POPCORN");
		IMAGE_COBCANNON_TARGET = aMgr.GetImageThrow("IMAGE_COBCANNON_TARGET");
		IMAGE_COINBANK = aMgr.GetImageThrow("IMAGE_COINBANK");
		IMAGE_CONVEYORBELT = aMgr.GetImageThrow("IMAGE_CONVEYORBELT");
		IMAGE_CONVEYORBELT_BACKDROP = aMgr.GetImageThrow("IMAGE_CONVEYORBELT_BACKDROP");
		IMAGE_CRATER = aMgr.GetImageThrow("IMAGE_CRATER");
		IMAGE_CRATER_FADING = aMgr.GetImageThrow("IMAGE_CRATER_FADING");
		IMAGE_BACKGROUND_BLOODMOON = aMgr.GetImageThrow("IMAGE_BACKGROUND_BLOODMOON");
		IMAGE_CRATER_ROOF_CENTER = aMgr.GetImageThrow("IMAGE_CRATER_ROOF_CENTER");
		IMAGE_CRATER_ROOF_LEFT = aMgr.GetImageThrow("IMAGE_CRATER_ROOF_LEFT");
		IMAGE_CRATER_WATER_DAY = aMgr.GetImageThrow("IMAGE_CRATER_WATER_DAY");
		IMAGE_CRATER_WATER_NIGHT = aMgr.GetImageThrow("IMAGE_CRATER_WATER_NIGHT");
		IMAGE_CROSS = aMgr.GetImageThrow("IMAGE_CROSS");
		IMAGE_C_FLAG1 = aMgr.GetImageThrow("IMAGE_C_FLAG1");
		IMAGE_C_FLAG2 = aMgr.GetImageThrow("IMAGE_C_FLAG2");
		IMAGE_DA_FLAG1 = aMgr.GetImageThrow("IMAGE_DA_FLAG1");
		IMAGE_DA_FLAG2 = aMgr.GetImageThrow("IMAGE_DA_FLAG2");
		IMAGE_DIALOG_BIGBOTTOMLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_BIGBOTTOMLEFT");
		IMAGE_DIALOG_BIGBOTTOMMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_BIGBOTTOMMIDDLE");
		IMAGE_DIALOG_BIGBOTTOMRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_BIGBOTTOMRIGHT");
		IMAGE_DIALOG_BOTTOMLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_BOTTOMLEFT");
		IMAGE_DIALOG_BOTTOMMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_BOTTOMMIDDLE");
		IMAGE_DIALOG_BOTTOMRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_BOTTOMRIGHT");
		IMAGE_DIALOG_CENTERLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_CENTERLEFT");
		IMAGE_DIALOG_CENTERMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_CENTERMIDDLE");
		IMAGE_DIALOG_CENTERRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_CENTERRIGHT");
		IMAGE_DIALOG_HEADER = aMgr.GetImageThrow("IMAGE_DIALOG_HEADER");
		IMAGE_DIALOG_TOPLEFT = aMgr.GetImageThrow("IMAGE_DIALOG_TOPLEFT");
		IMAGE_DIALOG_TOPMIDDLE = aMgr.GetImageThrow("IMAGE_DIALOG_TOPMIDDLE");
		IMAGE_DIALOG_TOPRIGHT = aMgr.GetImageThrow("IMAGE_DIALOG_TOPRIGHT");
		IMAGE_DIRTBIG = aMgr.GetImageThrow("IMAGE_DIRTBIG");
		IMAGE_DIRTSMALL = aMgr.GetImageThrow("IMAGE_DIRTSMALL");
		IMAGE_DOOMSHROOM_EXPLOSION_BASE = aMgr.GetImageThrow("IMAGE_DOOMSHROOM_EXPLOSION_BASE");
		IMAGE_DUST_PUFFS = aMgr.GetImageThrow("IMAGE_DUST_PUFFS");
		IMAGE_D_FLAG1 = aMgr.GetImageThrow("IMAGE_D_FLAG1");
		IMAGE_D_FLAG2 = aMgr.GetImageThrow("IMAGE_D_FLAG2");
		IMAGE_EDITBOX = aMgr.GetImageThrow("IMAGE_EDITBOX");
		IMAGE_ELECTRIC = aMgr.GetImageThrow("IMAGE_ELECTRIC");
		IMAGE_E_FLAG1 = aMgr.GetImageThrow("IMAGE_E_FLAG1");
		IMAGE_E_FLAG2 = aMgr.GetImageThrow("IMAGE_E_FLAG2");
		IMAGE_FERTILIZER = aMgr.GetImageThrow("IMAGE_FERTILIZER");
		IMAGE_FF1 = aMgr.GetImageThrow("IMAGE_FF1");
		IMAGE_FF2 = aMgr.GetImageThrow("IMAGE_FF2");
		IMAGE_FLAGMETER = aMgr.GetImageThrow("IMAGE_FLAGMETER");
		IMAGE_FLAGMETERLEVELPROGRESS = aMgr.GetImageThrow("IMAGE_FLAGMETERLEVELPROGRESS");
		IMAGE_FLAGMETERPARTS = aMgr.GetImageThrow("IMAGE_FLAGMETERPARTS");
		IMAGE_FLAGMETERPARTS_HARDMODE = aMgr.GetImageThrow("IMAGE_FLAGMETERPARTS_HARDMODE");
		IMAGE_F_FLAG1 = aMgr.GetImageThrow("IMAGE_F_FLAG1");
		IMAGE_F_FLAG2 = aMgr.GetImageThrow("IMAGE_F_FLAG2");
		IMAGE_HW_FLAG1 = aMgr.GetImageThrow("IMAGE_HW_FLAG1");
		IMAGE_HW_FLAG2 = aMgr.GetImageThrow("IMAGE_HW_FLAG2");
		IMAGE_ICE = aMgr.GetImageThrow("IMAGE_ICE");
		IMAGE_ICETRAP = aMgr.GetImageThrow("IMAGE_ICETRAP");
		IMAGE_ICETRAP2 = aMgr.GetImageThrow("IMAGE_ICETRAP2");
		IMAGE_ICETRAP_PARTICLES = aMgr.GetImageThrow("IMAGE_ICETRAP_PARTICLES");
		IMAGE_ICE_CAP = aMgr.GetImageThrow("IMAGE_ICE_CAP");
		IMAGE_ICE_SPARKLES = aMgr.GetImageThrow("IMAGE_ICE_SPARKLES");
		IMAGE_ICON_POOLCLEANER = aMgr.GetImageThrow("IMAGE_ICON_POOLCLEANER");
		IMAGE_ICON_RAKE = aMgr.GetImageThrow("IMAGE_ICON_RAKE");
		IMAGE_ICON_ROOFCLEANER = aMgr.GetImageThrow("IMAGE_ICON_ROOFCLEANER");
		IMAGE_IMITATERCLOUDS = aMgr.GetImageThrow("IMAGE_IMITATERCLOUDS");
		IMAGE_IMITATERPUFFS = aMgr.GetImageThrow("IMAGE_IMITATERPUFFS");
		IMAGE_IMITATERSEED = aMgr.GetImageThrow("IMAGE_IMITATERSEED");
		IMAGE_IMITATERSEEDDISABLED = aMgr.GetImageThrow("IMAGE_IMITATERSEEDDISABLED");
		IMAGE_IP_FLAG1 = aMgr.GetImageThrow("IMAGE_IP_FLAG1");
		IMAGE_IP_FLAG2 = aMgr.GetImageThrow("IMAGE_IP_FLAG2");
		IMAGE_KF_FLAG1 = aMgr.GetImageThrow("IMAGE_KF_FLAG1");
		IMAGE_KF_FLAG2 = aMgr.GetImageThrow("IMAGE_KF_FLAG2");
		IMAGE_LOCKED_ZOMBIE = aMgr.GetImageThrow("IMAGE_LOCKED_ZOMBIE");
		IMAGE_L_BUTTON1 = aMgr.GetImageThrow("IMAGE_L_BUTTON1");
		IMAGE_L_BUTTON2 = aMgr.GetImageThrow("IMAGE_L_BUTTON2");
		IMAGE_MA_FLAG1 = aMgr.GetImageThrow("IMAGE_MA_FLAG1");
		IMAGE_MA_FLAG2 = aMgr.GetImageThrow("IMAGE_MA_FLAG2");
		IMAGE_MELONPULT_PARTICLES = aMgr.GetImageThrow("IMAGE_MELONPULT_PARTICLES");
		IMAGE_MINIGAME_2 = aMgr.GetImageThrow("IMAGE_MINIGAME_2");
		IMAGE_MINIGAME_TROPHY = aMgr.GetImageThrow("IMAGE_MINIGAME_TROPHY");
		IMAGE_MONEYBAG = aMgr.GetImageThrow("IMAGE_MONEYBAG");
		IMAGE_MONEYBAG_HI_RES = aMgr.GetImageThrow("IMAGE_MONEYBAG_HI_RES");
		IMAGE_M_FLAG1 = aMgr.GetImageThrow("IMAGE_M_FLAG1");
		IMAGE_M_FLAG2 = aMgr.GetImageThrow("IMAGE_M_FLAG2");
		IMAGE_NEW_SURVIVAL_THUMBNAIL = aMgr.GetImageThrow("IMAGE_NEW_SURVIVAL_THUMBNAIL");
		IMAGE_NIGHT_GRAVE_GRAPHIC = aMgr.GetImageThrow("IMAGE_NIGHT_GRAVE_GRAPHIC");
		IMAGE_OAK_ARROW = aMgr.GetImageThrow("IMAGE_OAK_ARROW");
		IMAGE_OPTIONS_BACKTOGAMEBUTTON0 = aMgr.GetImageThrow("IMAGE_OPTIONS_BACKTOGAMEBUTTON0");
		IMAGE_OPTIONS_BACKTOGAMEBUTTON2 = aMgr.GetImageThrow("IMAGE_OPTIONS_BACKTOGAMEBUTTON2");
		IMAGE_OPTIONS_CHECKBOX0 = aMgr.GetImageThrow("IMAGE_OPTIONS_CHECKBOX0");
		IMAGE_OPTIONS_CHECKBOX1 = aMgr.GetImageThrow("IMAGE_OPTIONS_CHECKBOX1");
		IMAGE_OPTIONS_MENUBACK = aMgr.GetImageThrow("IMAGE_OPTIONS_MENUBACK");
		IMAGE_OPTIONS_SLIDERKNOB2 = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERKNOB2");
		IMAGE_OPTIONS_SLIDERSLOT = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERSLOT");
		IMAGE_P1_1 = aMgr.GetImageThrow("IMAGE_P1_1");
		IMAGE_P1_2 = aMgr.GetImageThrow("IMAGE_P1_2");
		IMAGE_P1_3 = aMgr.GetImageThrow("IMAGE_P1_3");
		IMAGE_P2_1 = aMgr.GetImageThrow("IMAGE_P2_1");
		IMAGE_P2_2 = aMgr.GetImageThrow("IMAGE_P2_2");
		IMAGE_P2_3 = aMgr.GetImageThrow("IMAGE_P2_3");
		IMAGE_PACKET_PLANTS = aMgr.GetImageThrow("IMAGE_PACKET_PLANTS");
		IMAGE_PEA_PARTICLES = aMgr.GetImageThrow("IMAGE_PEA_PARTICLES");
		IMAGE_PEA_SHADOWS = aMgr.GetImageThrow("IMAGE_PEA_SHADOWS");
		IMAGE_PEA_SPLATS = aMgr.GetImageThrow("IMAGE_PEA_SPLATS");
		IMAGE_PHONOGRAPH = aMgr.GetImageThrow("IMAGE_PHONOGRAPH");
		IMAGE_PINATA = aMgr.GetImageThrow("IMAGE_PINATA");
		IMAGE_PLANTSHADOW = aMgr.GetImageThrow("IMAGE_PLANTSHADOW");
		IMAGE_PLANTSHADOW2 = aMgr.GetImageThrow("IMAGE_PLANTSHADOW2");
		IMAGE_PLANTSPEECHBUBBLE = aMgr.GetImageThrow("IMAGE_PLANTSPEECHBUBBLE");
		IMAGE_POOL = aMgr.GetImageThrow("IMAGE_POOL");
		IMAGE_POOLSPARKLY = aMgr.GetImageThrow("IMAGE_POOLSPARKLY");
		IMAGE_POOL_BASE = aMgr.GetImageThrow("IMAGE_POOL_BASE");
		IMAGE_POOL_BASE_NIGHT = aMgr.GetImageThrow("IMAGE_POOL_BASE_NIGHT");
		IMAGE_POOL_CAUSTIC_EFFECT = aMgr.GetImageThrow("IMAGE_POOL_CAUSTIC_EFFECT");
		IMAGE_POOL_NIGHT = aMgr.GetImageThrow("IMAGE_POOL_NIGHT");
		IMAGE_POOL_SHADING = aMgr.GetImageThrow("IMAGE_POOL_SHADING");
		IMAGE_POOL_SHADING_NIGHT = aMgr.GetImageThrow("IMAGE_POOL_SHADING_NIGHT");
		IMAGE_POTATOMINE_PARTICLES = aMgr.GetImageThrow("IMAGE_POTATOMINE_PARTICLES");
		IMAGE_PRESENT = aMgr.GetImageThrow("IMAGE_PRESENT");
		IMAGE_PRESENTOPEN = aMgr.GetImageThrow("IMAGE_PRESENTOPEN");
		IMAGE_PROJECTILECACTUS = aMgr.GetImageThrow("IMAGE_PROJECTILECACTUS");
		IMAGE_PROJECTILEICEQUEEN = aMgr.GetImageThrow("IMAGE_PROJECTILEICEQUEEN");
		IMAGE_PROJECTILEPEA = aMgr.GetImageThrow("IMAGE_PROJECTILEPEA");
		IMAGE_PROJECTILESNOWPEA = aMgr.GetImageThrow("IMAGE_PROJECTILESNOWPEA");
		IMAGE_PROJECTILE_SEASTAR = aMgr.GetImageThrow("IMAGE_PROJECTILE_SEASTAR");
		IMAGE_PROJECTILE_STAR = aMgr.GetImageThrow("IMAGE_PROJECTILE_STAR");
		IMAGE_PR_FLAG1 = aMgr.GetImageThrow("IMAGE_PR_FLAG1");
		IMAGE_PR_FLAG2 = aMgr.GetImageThrow("IMAGE_PR_FLAG2");
		IMAGE_PUDDLE = aMgr.GetImageThrow("IMAGE_PUDDLE");
		IMAGE_PUFFSHROOM_PUFF1 = aMgr.GetImageThrow("IMAGE_PUFFSHROOM_PUFF1");
		IMAGE_RAIN = aMgr.GetImageThrow("IMAGE_RAIN");
		IMAGE_MINIGAME_DIAMOND_TROPHY = aMgr.GetImageThrow("IMAGE_MINIGAME_DIAMOND_TROPHY");
		IMAGE_REANIM_CABBAGEPULT_CABBAGE = aMgr.GetImageThrow("IMAGE_REANIM_CABBAGEPULT_CABBAGE");
		IMAGE_REANIM_COBCANNON_COB = aMgr.GetImageThrow("IMAGE_REANIM_COBCANNON_COB");
		IMAGE_REANIM_COINGLOW = aMgr.GetImageThrow("IMAGE_REANIM_COINGLOW");
		IMAGE_REANIM_COIN_GOLD_DOLLAR = aMgr.GetImageThrow("IMAGE_REANIM_COIN_GOLD_DOLLAR");
		IMAGE_REANIM_COIN_SILVER_DOLLAR = aMgr.GetImageThrow("IMAGE_REANIM_COIN_SILVER_DOLLAR");
		IMAGE_REANIM_CORNPULT_BUTTER = aMgr.GetImageThrow("IMAGE_REANIM_CORNPULT_BUTTER");
		IMAGE_REANIM_CORNPULT_BUTTER_SPLAT = aMgr.GetImageThrow("IMAGE_REANIM_CORNPULT_BUTTER_SPLAT");
		IMAGE_REANIM_CORNPULT_KERNAL = aMgr.GetImageThrow("IMAGE_REANIM_CORNPULT_KERNAL");
		IMAGE_REANIM_CRAZYDAVE_MOUTH1 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH1");
		IMAGE_REANIM_CRAZYDAVE_MOUTH4 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH4");
		IMAGE_REANIM_CRAZYDAVE_MOUTH5 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH5");
		IMAGE_REANIM_CRAZYDAVE_MOUTH6 = aMgr.GetImageThrow("IMAGE_REANIM_CRAZYDAVE_MOUTH6");
		IMAGE_REANIM_DIAMOND = aMgr.GetImageThrow("IMAGE_REANIM_DIAMOND");
		IMAGE_REANIM_FIRESHROOM_BODY2 = aMgr.GetImageThrow("IMAGE_REANIM_FIRESHROOM_BODY2");
		IMAGE_REANIM_FIRESHROOM_CRACKED1 = aMgr.GetImageThrow("IMAGE_REANIM_FIRESHROOM_CRACKED1");
		IMAGE_REANIM_FIRESHROOM_CRACKED2 = aMgr.GetImageThrow("IMAGE_REANIM_FIRESHROOM_CRACKED2");
		IMAGE_REANIM_GARLIC_BODY2 = aMgr.GetImageThrow("IMAGE_REANIM_GARLIC_BODY2");
		IMAGE_REANIM_GARLIC_BODY3 = aMgr.GetImageThrow("IMAGE_REANIM_GARLIC_BODY3");
		IMAGE_REANIM_MELONPULT_MELON = aMgr.GetImageThrow("IMAGE_REANIM_MELONPULT_MELON");
		IMAGE_REANIM_POT_TOP_DARK = aMgr.GetImageThrow("IMAGE_REANIM_POT_TOP_DARK");
		IMAGE_REANIM_PUMPKIN_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_PUMPKIN_DAMAGE1");
		IMAGE_REANIM_PUMPKIN_DAMAGE3 = aMgr.GetImageThrow("IMAGE_REANIM_PUMPKIN_DAMAGE3");
		IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW");
		IMAGE_REANIM_SELECTORSCREEN_BG = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_BG");
		IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW");
		IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON");
		IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT");
		IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS");
		IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3 = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3");
		IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS = aMgr.GetImageThrow("IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS");
		IMAGE_REANIM_STINKY_TURN3 = aMgr.GetImageThrow("IMAGE_REANIM_STINKY_TURN3");
		IMAGE_REANIM_TALLNUT_CRACKED1 = aMgr.GetImageThrow("IMAGE_REANIM_TALLNUT_CRACKED1");
		IMAGE_REANIM_TALLNUT_CRACKED2 = aMgr.GetImageThrow("IMAGE_REANIM_TALLNUT_CRACKED2");
		IMAGE_REANIM_DUMMY_CRACKED1 = aMgr.GetImageThrow("IMAGE_REANIM_DUMMY_CRACKED1");
		IMAGE_REANIM_DUMMY_CRACKED2 = aMgr.GetImageThrow("IMAGE_REANIM_DUMMY_CRACKED2");
		IMAGE_REANIM_TREE_BG = aMgr.GetImageThrow("IMAGE_REANIM_TREE_BG");
		IMAGE_REANIM_WALLNUT_BODY = aMgr.GetImageThrow("IMAGE_REANIM_WALLNUT_BODY");
		IMAGE_REANIM_WALLNUT_CRACKED1 = aMgr.GetImageThrow("IMAGE_REANIM_WALLNUT_CRACKED1");
		IMAGE_REANIM_WALLNUT_CRACKED2 = aMgr.GetImageThrow("IMAGE_REANIM_WALLNUT_CRACKED2");
		IMAGE_REANIM_WINTERMELON_PROJECTILE = aMgr.GetImageThrow("IMAGE_REANIM_WINTERMELON_PROJECTILE");
		IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE = aMgr.GetImageThrow("IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE");
		IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE");
		IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL");
		IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_BUCKET1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET1");
		IMAGE_REANIM_ZOMBIE_BUCKET2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET2");
		IMAGE_REANIM_ZOMBIE_BUCKET3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET3");
		IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED");
		IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL");
		IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL");
		IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE");
		IMAGE_REANIM_ZOMBIE_CONE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CONE1");
		IMAGE_REANIM_ZOMBIE_CONE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CONE2");
		IMAGE_REANIM_ZOMBIE_CONE3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_CONE3");
		IMAGE_REANIM_ZOMBIE_DANCER_INNERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DANCER_INNERARM_HAND");
		IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT");
		IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2");
		IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3");
		IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE");
		IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_FLAG1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FLAG1");
		IMAGE_REANIM_ZOMBIE_FLAG3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FLAG3");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND");
		IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2");
		IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE");
		IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HAND");
		IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET1");
		IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET2");
		IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET3");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_AXE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_AXE2");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_2");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_3");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2_REDEYE");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD_REDEYE");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET1");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET2");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET3");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET_RED = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET_RED");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_HAND_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_HAND_REDEYE");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2_REDEYE");
		IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER_REDEYE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER_REDEYE");
		IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3");
		IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4");
		IMAGE_REANIM_ZOMBIE_ICE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ICE2");
		IMAGE_REANIM_ZOMBIE_ICE3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ICE3");
		IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE");
		IMAGE_REANIM_ZOMBIE_IMP_ARM2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_IMP_ARM2");
		IMAGE_REANIM_ZOMBIE_JACKBOX_BOX = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_JACKBOX_BOX");
		IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2");
		IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_LADDER_1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_1");
		IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_LADDER_5 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_5");
		IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_MUSTACHE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_MUSTACHE2");
		IMAGE_REANIM_ZOMBIE_MUSTACHE3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_MUSTACHE3");
		IMAGE_REANIM_ZOMBIE_HEAD_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_HEAD_GIGA");
		IMAGE_REANIM_ZOMBIE_BUCKET1_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET1_GIGA");
		IMAGE_REANIM_ZOMBIE_BUCKET2_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET2_GIGA");
		IMAGE_REANIM_ZOMBIE_BUCKET3_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_BUCKET3_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER1_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER1_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER2_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER2_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER3_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER3_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER4_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER4_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER5_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER5_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER6_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER6_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER7_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER7_GIGA");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER8_GIGA = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER8_GIGA");
		IMAGE_REANIM_ZOMBIE_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER");
		IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD");
		IMAGE_REANIM_ZOMBIE_PAPER_PAPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_PAPER2");
		IMAGE_REANIM_ZOMBIE_PAPER_PAPER3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_PAPER_PAPER3");
		IMAGE_REANIM_ZOMBIE_FISHER_HAT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FISHER_HAT");
		IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1");
		IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2");
		IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1");
		IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2");
		IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2");
		IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_SCARE_HEAD = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCARE_HEAD");
		IMAGE_REANIM_ZOMBIE_SCARE_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCARE_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_SCREENDOOR1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCREENDOOR1");
		IMAGE_REANIM_ZOMBIE_SCREENDOOR2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCREENDOOR2");
		IMAGE_REANIM_ZOMBIE_SCREENDOOR3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SCREENDOOR3");
		IMAGE_REANIM_ZOMBIE_TRASHCAN1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_TRASHCAN1");
		IMAGE_REANIM_ZOMBIE_TRASHCAN2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_TRASHCAN2");
		IMAGE_REANIM_ZOMBIE_TRASHCAN3 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_TRASHCAN3");
		IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD");
		IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_VAMPIRE_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_VAMPIRE_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_FISHERMAN_OUTERARM_UPPER = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_FISHERMAN_OUTERARM_UPPER");
		IMAGE_REANIM_ZOMBIE_LEAFBLOWER_OUTERARM_UPPER = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_LEAFBLOWER_OUTERARM_UPPER");
		IMAGE_REANIM_ZOMBIE_AXE_OUTERARM_UPPER = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_AXE_OUTERARM_UPPER");
		IMAGE_REANIM_ZOMBIE_AXE_HAT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_AXE_HAT");
		IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND");
		IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2 = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2");
		IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT = aMgr.GetImageThrow("IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT");
		IMAGE_ROCKSMALL = aMgr.GetImageThrow("IMAGE_ROCKSMALL");
		IMAGE_R_BUTTON1 = aMgr.GetImageThrow("IMAGE_R_BUTTON1");
		IMAGE_R_BUTTON2 = aMgr.GetImageThrow("IMAGE_R_BUTTON2");
		IMAGE_R_FLAG1 = aMgr.GetImageThrow("IMAGE_R_FLAG1");
		IMAGE_R_FLAG2 = aMgr.GetImageThrow("IMAGE_R_FLAG2");
		IMAGE_SCARY_POT = aMgr.GetImageThrow("IMAGE_SCARY_POT");
		IMAGE_SEEDBANK = aMgr.GetImageThrow("IMAGE_SEEDBANK");
		IMAGE_SEEDBANK_SMALL = aMgr.GetImageThrow("IMAGE_SEEDBANK_SMALL");
		IMAGE_SEEDCHOOSER_BACKGROUND = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BACKGROUND");
		IMAGE_SEEDCHOOSER_BACKGROUND_ZOMBIES = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BACKGROUND_ZOMBIES");
		IMAGE_SEEDCHOOSER_BUTTON = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON");
		IMAGE_SEEDCHOOSER_BUTTON2 = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON2");
		IMAGE_SEEDCHOOSER_BUTTON2_GLOW = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON2_GLOW");
		IMAGE_SEEDCHOOSER_BUTTON_DISABLED = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON_DISABLED");
		IMAGE_SEEDCHOOSER_BUTTON_GLOW = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_BUTTON_GLOW");
		IMAGE_SEEDCHOOSER_IMITATERADDON = aMgr.GetImageThrow("IMAGE_SEEDCHOOSER_IMITATERADDON");
		IMAGE_SEEDPACKETFLASH = aMgr.GetImageThrow("IMAGE_SEEDPACKETFLASH");
		IMAGE_SEEDPACKETSILHOUETTE = aMgr.GetImageThrow("IMAGE_SEEDPACKETSILHOUETTE");
		IMAGE_SEEDPACKET_LARGER = aMgr.GetImageThrow("IMAGE_SEEDPACKET_LARGER");
		IMAGE_SEEDS = aMgr.GetImageThrow("IMAGE_SEEDS");
		IMAGE_SELECTORSCREEN_ALMANAC = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ALMANAC");
		IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT");
		IMAGE_SELECTORSCREEN_HELP1 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_HELP1");
		IMAGE_SELECTORSCREEN_HELP2 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_HELP2");
		IMAGE_SELECTORSCREEN_LEVELNUMBERS = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_LEVELNUMBERS");
		IMAGE_SELECTORSCREEN_OPTIONS1 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_OPTIONS1");
		IMAGE_SELECTORSCREEN_OPTIONS2 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_OPTIONS2");
		IMAGE_SELECTORSCREEN_QUIT1 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_QUIT1");
		IMAGE_SELECTORSCREEN_QUIT2 = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_QUIT2");
		IMAGE_SELECTORSCREEN_STORE = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_STORE");
		IMAGE_SELECTORSCREEN_STOREHIGHLIGHT = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_STOREHIGHLIGHT");
		IMAGE_SELECTORSCREEN_ZENGARDEN = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ZENGARDEN");
		IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT = aMgr.GetImageThrow("IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT");
		IMAGE_SHOVEL = aMgr.GetImageThrow("IMAGE_SHOVEL");
		IMAGE_SHOVELBANK = aMgr.GetImageThrow("IMAGE_SHOVELBANK");
		IMAGE_SHOVEL_HI_RES = aMgr.GetImageThrow("IMAGE_SHOVEL_HI_RES");
		IMAGE_SH_FLAG1 = aMgr.GetImageThrow("IMAGE_SH_FLAG1");
		IMAGE_SH_FLAG2 = aMgr.GetImageThrow("IMAGE_SH_FLAG2");
		IMAGE_SLOTMACHINE_OVERLAY = aMgr.GetImageThrow("IMAGE_SLOTMACHINE_OVERLAY");
		IMAGE_SNOWFLAKES = aMgr.GetImageThrow("IMAGE_SNOWFLAKES");
		IMAGE_SNOWPEA_PARTICLES = aMgr.GetImageThrow("IMAGE_SNOWPEA_PARTICLES");
		IMAGE_SNOWPEA_PUFF = aMgr.GetImageThrow("IMAGE_SNOWPEA_PUFF");
		IMAGE_SNOWPEA_SPLATS = aMgr.GetImageThrow("IMAGE_SNOWPEA_SPLATS");
		IMAGE_SPOTLIGHT = aMgr.GetImageThrow("IMAGE_SPOTLIGHT");
		IMAGE_SPOTLIGHT2 = aMgr.GetImageThrow("IMAGE_SPOTLIGHT2");
		IMAGE_STAR_PARTICLES = aMgr.GetImageThrow("IMAGE_STAR_PARTICLES");
		IMAGE_STAR_SPLATS = aMgr.GetImageThrow("IMAGE_STAR_SPLATS");
		IMAGE_STONE2 = aMgr.GetImageThrow("IMAGE_STONE2");
		IMAGE_STONE3 = aMgr.GetImageThrow("IMAGE_STONE3");
		IMAGE_STONE4 = aMgr.GetImageThrow("IMAGE_STONE4");
		IMAGE_STONE5 = aMgr.GetImageThrow("IMAGE_STONE5");
		IMAGE_STORE_SPEECHBUBBLE = aMgr.GetImageThrow("IMAGE_STORE_SPEECHBUBBLE");
		IMAGE_STORE_SPEECHBUBBLE2 = aMgr.GetImageThrow("IMAGE_STORE_SPEECHBUBBLE2");
		IMAGE_SUNBANK = aMgr.GetImageThrow("IMAGE_SUNBANK");
		IMAGE_SUNFLOWER_TROPHY = aMgr.GetImageThrow("IMAGE_SUNFLOWER_TROPHY");
		IMAGE_DIAMOND_SUNFLOWER_TROPHY = aMgr.GetImageThrow("IMAGE_DIAMOND_SUNFLOWER_TROPHY");
		IMAGE_S_FLAG1 = aMgr.GetImageThrow("IMAGE_S_FLAG1");
		IMAGE_S_FLAG2 = aMgr.GetImageThrow("IMAGE_S_FLAG2");
		IMAGE_TACO = aMgr.GetImageThrow("IMAGE_TACO");
		IMAGE_TARGET = aMgr.GetImageThrow("IMAGE_TARGET");
		IMAGE_TARGET_1 = aMgr.GetImageThrow("IMAGE_TARGET_1");
		IMAGE_TARGET_2 = aMgr.GetImageThrow("IMAGE_TARGET_2");
		IMAGE_TARGET_3 = aMgr.GetImageThrow("IMAGE_TARGET_3");
		IMAGE_TOMBSTONES = aMgr.GetImageThrow("IMAGE_TOMBSTONES");
		IMAGE_TOMBSTONE_MOUNDS = aMgr.GetImageThrow("IMAGE_TOMBSTONE_MOUNDS");
		IMAGE_TREEFOOD = aMgr.GetImageThrow("IMAGE_TREEFOOD");
		IMAGE_TROPHY = aMgr.GetImageThrow("IMAGE_TROPHY");
		IMAGE_DIAMOND_TROPHY = aMgr.GetImageThrow("IMAGE_DIAMOND_TROPHY");
		IMAGE_TROPHY_HI_RES = aMgr.GetImageThrow("IMAGE_TROPHY_HI_RES");
		IMAGE_DIAMOND_TROPHY_HI_RES = aMgr.GetImageThrow("IMAGE_DIAMOND_TROPHY_HI_RES");
		IMAGE_VASE_CHUNKS = aMgr.GetImageThrow("IMAGE_VASE_CHUNKS");
		IMAGE_VERSUS_BUTTON = aMgr.GetImageThrow("IMAGE_VERSUS_BUTTON");
		IMAGE_VERSUS_BUTTON_HIGHLIGHTED = aMgr.GetImageThrow("IMAGE_VERSUS_BUTTON_HIGHLIGHTED");
		IMAGE_WALLNUTPARTICLESLARGE = aMgr.GetImageThrow("IMAGE_WALLNUTPARTICLESLARGE");
		IMAGE_WALLNUTPARTICLESSMALL = aMgr.GetImageThrow("IMAGE_WALLNUTPARTICLESSMALL");
		IMAGE_WALLNUT_BOWLINGSTRIPE = aMgr.GetImageThrow("IMAGE_WALLNUT_BOWLINGSTRIPE");
		IMAGE_FLOWER_STRIPE = aMgr.GetImageThrow("IMAGE_FLOWER_STRIPE");
		IMAGE_WATERDROP = aMgr.GetImageThrow("IMAGE_WATERDROP");
		IMAGE_WATERINGCAN = aMgr.GetImageThrow("IMAGE_WATERINGCAN");
		IMAGE_WATERINGCANGOLD = aMgr.GetImageThrow("IMAGE_WATERINGCANGOLD");
		IMAGE_WATERPARTICLE = aMgr.GetImageThrow("IMAGE_WATERPARTICLE");
		IMAGE_WHITEPIXEL = aMgr.GetImageThrow("IMAGE_WHITEPIXEL");
		IMAGE_WHITEWATER = aMgr.GetImageThrow("IMAGE_WHITEWATER");
		IMAGE_WHITEWATER_SHADOW = aMgr.GetImageThrow("IMAGE_WHITEWATER_SHADOW");
		IMAGE_WINTERMELON_PARTICLES = aMgr.GetImageThrow("IMAGE_WINTERMELON_PARTICLES");
		IMAGE_YY_FLAG1 = aMgr.GetImageThrow("IMAGE_YY_FLAG1");
		IMAGE_YY_FLAG2 = aMgr.GetImageThrow("IMAGE_YY_FLAG2");
		IMAGE_ZAMBONISMOKE = aMgr.GetImageThrow("IMAGE_ZAMBONISMOKE");
		IMAGE_ZENSHOPBUTTON = aMgr.GetImageThrow("IMAGE_ZENSHOPBUTTON");
		IMAGE_ZENSHOPBUTTON_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_ZENSHOPBUTTON_HIGHLIGHT");
		IMAGE_ZEN_GARDENGLOVE = aMgr.GetImageThrow("IMAGE_ZEN_GARDENGLOVE");
		IMAGE_ZEN_GOLDTOOLRETICLE = aMgr.GetImageThrow("IMAGE_ZEN_GOLDTOOLRETICLE");
		IMAGE_ZEN_MONEYSIGN = aMgr.GetImageThrow("IMAGE_ZEN_MONEYSIGN");
		IMAGE_ZEN_NEED_ICONS = aMgr.GetImageThrow("IMAGE_ZEN_NEED_ICONS");
		IMAGE_ZEN_NEXTGARDEN = aMgr.GetImageThrow("IMAGE_ZEN_NEXTGARDEN");
		IMAGE_ZEN_WHEELBARROW = aMgr.GetImageThrow("IMAGE_ZEN_WHEELBARROW");
		IMAGE_ZOMBIEBACKUPDANCERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEBACKUPDANCERARM");
		IMAGE_ZOMBIEBACKUPDANCERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEBACKUPDANCERHEAD");
		IMAGE_ZOMBIEBALLOONHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEBALLOONHEAD");
		IMAGE_ZOMBIEBOBSLEDHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEBOBSLEDHEAD");
		IMAGE_ZOMBIEDANCERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEDANCERARM");
		IMAGE_ZOMBIEDANCERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEDANCERHEAD");
		IMAGE_ZOMBIEDIGGERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEDIGGERARM");
		IMAGE_ZOMBIEDIGGERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEDIGGERHEAD");
		IMAGE_ZOMBIEDOLPHINRIDERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEDOLPHINRIDERHEAD");
		IMAGE_ZOMBIEFOOTBALLHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEFOOTBALLHEAD");
		IMAGE_ZOMBIEFUTUREGLASSES = aMgr.GetImageThrow("IMAGE_ZOMBIEFUTUREGLASSES");
		IMAGE_ZOMBIEIMPHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEIMPHEAD");
		IMAGE_ZOMBIEJACKBOXARM = aMgr.GetImageThrow("IMAGE_ZOMBIEJACKBOXARM");
		IMAGE_ZOMBIELADDERARM = aMgr.GetImageThrow("IMAGE_ZOMBIELADDERARM");
		IMAGE_ZOMBIELADDERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIELADDERHEAD");
		IMAGE_ZOMBIEPAPERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEPAPERARM");
		IMAGE_ZOMBIEPOGO = aMgr.GetImageThrow("IMAGE_ZOMBIEPOGO");
		IMAGE_ZOMBIEPOGOARM = aMgr.GetImageThrow("IMAGE_ZOMBIEPOGOARM");
		IMAGE_ZOMBIEPOLEVAULTERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEPOLEVAULTERARM");
		IMAGE_ZOMBIEPOLEVAULTERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEPOLEVAULTERHEAD");
		IMAGE_ZOMBIESCARECROWARM = aMgr.GetImageThrow("IMAGE_ZOMBIESCARECROWARM");
		IMAGE_ZOMBIEFISHERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEFISHERARM");
		IMAGE_ZOMBIEHUNTERARM = aMgr.GetImageThrow("IMAGE_ZOMBIEHUNTERARM");
		IMAGE_ZOMBIELEAFBLOWERARM = aMgr.GetImageThrow("IMAGE_ZOMBIELEAFBLOWERARM");
		IMAGE_ZOMBIEAXEARM = aMgr.GetImageThrow("IMAGE_ZOMBIEAXEARM");
		IMAGE_ZOMBIEBIGFOOTARM = aMgr.GetImageThrow("IMAGE_ZOMBIEBIGFOOTARM");
		IMAGE_ZOMBIEVAMPIREARM = aMgr.GetImageThrow("IMAGE_ZOMBIEVAMPIREARM");
		IMAGE_ZOMBIEVAMPIREHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEVAMPIREHEAD");
		IMAGE_ZOMBIEFISHERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEFISHERHEAD");
		IMAGE_ZOMBIELEAFBLOWERHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIELEAFBLOWERHEAD");
		IMAGE_ZOMBIEAXEHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEAXEHEAD");
		IMAGE_ZOMBIEBIGFOOTHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEBIGFOOTHEAD");
		IMAGE_ZOMBIEYETIHEAD = aMgr.GetImageThrow("IMAGE_ZOMBIEYETIHEAD");
		IMAGE_ZOMBIE_BOBSLED1 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED1");
		IMAGE_ZOMBIE_BOBSLED2 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED2");
		IMAGE_ZOMBIE_BOBSLED3 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED3");
		IMAGE_ZOMBIE_BOBSLED4 = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED4");
		IMAGE_ZOMBIE_BOBSLED_INSIDE = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOBSLED_INSIDE");
		IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES");
		IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES");
		IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES");
		IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES");
		IMAGE_ZOMBIE_NOTE_SMALL = aMgr.GetImageThrow("IMAGE_ZOMBIE_NOTE_SMALL");
		IMAGE_ZOMBIE_PACK = aMgr.GetImageThrow("IMAGE_ZOMBIE_PACK");
		IMAGE_ZOMBIE_SEAWEED = aMgr.GetImageThrow("IMAGE_ZOMBIE_SEAWEED");
		IMAGE_ZOMBOSS_PARTICLES = aMgr.GetImageThrow("IMAGE_ZOMBOSS_PARTICLES");
		IMAGE_Z_FLAG1 = aMgr.GetImageThrow("IMAGE_Z_FLAG1");
		IMAGE_Z_FLAG2 = aMgr.GetImageThrow("IMAGE_Z_FLAG2");
		IMAGE_CREDITSBACKGROUND = aMgr.GetImageThrow("IMAGE_CREDITSBACKGROUND");
		IMAGE_DISCLAIMERBACKGROUND = aMgr.GetImageThrow("IMAGE_DISCLAIMERBACKGROUND");
		IMAGE_CREDITS_BTN1 = aMgr.GetImageThrow("IMAGE_CREDITS_BTN1");
		IMAGE_CREDITS_BTN2 = aMgr.GetImageThrow("IMAGE_CREDITS_BTN2");
		IMAGE_CROW1 = aMgr.GetImageThrow("IMAGE_CROW1");
		IMAGE_CROW2 = aMgr.GetImageThrow("IMAGE_CROW2");
		IMAGE_VIOLET_PADDLE = aMgr.GetImageThrow("IMAGE_VIOLET_PADDLE");
		IMAGE_FOREST_OBJECTS = aMgr.GetImageThrow("IMAGE_FOREST_OBJECTS");
		IMAGE_LOG1 = aMgr.GetImageThrow("IMAGE_LOG1");
		IMAGE_LOG2 = aMgr.GetImageThrow("IMAGE_LOG2");
		IMAGE_LOG3 = aMgr.GetImageThrow("IMAGE_LOG3");
		IMAGE_GEM_RED = aMgr.GetImageThrow("IMAGE_GEM_RED");
		IMAGE_GEM_GREEN = aMgr.GetImageThrow("IMAGE_GEM_GREEN");
		IMAGE_GEM_WHITE = aMgr.GetImageThrow("IMAGE_GEM_WHITE");
		IMAGE_GEM_PURPLE = aMgr.GetImageThrow("IMAGE_GEM_PURPLE");
		IMAGE_GEM_YELLOW = aMgr.GetImageThrow("IMAGE_GEM_YELLOW");
		IMAGE_GEM_ORANGE = aMgr.GetImageThrow("IMAGE_GEM_ORANGE");
		IMAGE_DISCLAIMER_BTN1 = aMgr.GetImageThrow("IMAGE_DISCLAIMER_BTN1");
		IMAGE_DISCLAIMER_BTN2 = aMgr.GetImageThrow("IMAGE_DISCLAIMER_BTN2");
		IMAGE_FLASHLIGHT_LIGHT = aMgr.GetImageThrow("IMAGE_FLASHLIGHT_LIGHT");
		IMAGE_FOREST_NIGHT_MAP = aMgr.GetImageThrow("IMAGE_FOREST_NIGHT_MAP");
		IMAGE_FOREST_NIGHT_ITEMS = aMgr.GetImageThrow("IMAGE_FOREST_NIGHT_ITEMS");
		IMAGE_VINENUT_2 = aMgr.GetImageThrow("IMAGE_VINENUT_2");
		IMAGE_VINENUT_3 = aMgr.GetImageThrow("IMAGE_VINENUT_3");
		IMAGE_VINENUT_2_BODY = aMgr.GetImageThrow("IMAGE_VINENUT_2_BODY");
		IMAGE_VINENUT_3_BODY = aMgr.GetImageThrow("IMAGE_VINENUT_3_BODY");
		IMAGE_NET = aMgr.GetImageThrow("IMAGE_NET");
		IMAGE_GAME = aMgr.GetImageThrow("IMAGE_GAME");
		IMAGE_GAME2 = aMgr.GetImageThrow("IMAGE_GAME2");
		IMAGE_WOOD = aMgr.GetImageThrow("IMAGE_WOOD");
		IMAGE_HUNTER_HAT = aMgr.GetImageThrow("IMAGE_HUNTER_HAT");
		IMAGE_VERSUS_NOTE = aMgr.GetImageThrow("IMAGE_VERSUS_NOTE");
		IMAGE_BACKGROUND7_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND7_GAMEOVER_MASK");
		IMAGE_BACKGROUNDPP_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUNDPP_GAMEOVER_MASK");
		IMAGE_BACKGROUND_GLADIANTUAR_GAMEOVER_MASK = aMgr.GetImageThrow("IMAGE_BACKGROUND_GLADIANTUAR_GAMEOVER_MASK");
		IMAGE_WOODS_NOTE = aMgr.GetImageThrow("IMAGE_WOODS_NOTE");
		IMAGE_SHOVEL_ROTATED = aMgr.GetImageThrow("IMAGE_SHOVEL_ROTATED");
		IMAGE_ICON_WOODCHIPPER = aMgr.GetImageThrow("IMAGE_ICON_WOODCHIPPER");
		IMAGE_ICON_NEW = aMgr.GetImageThrow("IMAGE_ICON_NEW");
		IMAGE_PLAYER1_MOUSE = aMgr.GetImageThrow("IMAGE_PLAYER1_MOUSE");
		IMAGE_PLAYER2_MOUSE = aMgr.GetImageThrow("IMAGE_PLAYER2_MOUSE");
		IMAGE_PLAYER1_KEYBOARD = aMgr.GetImageThrow("IMAGE_PLAYER1_KEYBOARD");
		IMAGE_PLAYER2_KEYBOARD = aMgr.GetImageThrow("IMAGE_PLAYER2_KEYBOARD");
		IMAGE_OPTIONS_SLIDERKNOB3 = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERKNOB3");
		IMAGE_OPTIONS_SLIDERSLOT4 = aMgr.GetImageThrow("IMAGE_OPTIONS_SLIDERSLOT4");
		IMAGE_DISCORD_BUTTON = aMgr.GetImageThrow("IMAGE_DISCORD_BUTTON");
		IMAGE_DISCORD_BUTTON_HOVER = aMgr.GetImageThrow("IMAGE_DISCORD_BUTTON_HOVER");
		IMAGE_DISCORD_BUTTON_DOWN = aMgr.GetImageThrow("IMAGE_DISCORD_BUTTON_DOWN");
		IMAGE_GIGA_HEAD = aMgr.GetImageThrow("IMAGE_GIGA_HEAD");
		IMAGE_GIGA_POLE_HEAD = aMgr.GetImageThrow("IMAGE_GIGA_POLE_HEAD");
		IMAGE_GIGA_PROGRESS_FLAG = aMgr.GetImageThrow("IMAGE_GIGA_PROGRESS_FLAG");
		IMAGE_BOWLING_STRIPE_POOL = aMgr.GetImageThrow("IMAGE_BOWLING_STRIPE_POOL");
		IMAGE_BOWLING_STRIPE_ROOF = aMgr.GetImageThrow("IMAGE_BOWLING_STRIPE_ROOF");
		IMAGE_BOWLING_STRIPE_ROOF_VERSUS = aMgr.GetImageThrow("IMAGE_BOWLING_STRIPE_ROOF_VERSUS");
		IMAGE_PLANT_TROPHY = aMgr.GetImageThrow("IMAGE_PLANT_TROPHY");
		IMAGE_PLANT_TROPHY_HIGH_RES = aMgr.GetImageThrow("IMAGE_PLANT_TROPHY_HIGH_RES");
		IMAGE_ZOMBIE_TROPHY = aMgr.GetImageThrow("IMAGE_ZOMBIE_TROPHY");
		IMAGE_ZOMBIE_TROPHY_HIGH_RES = aMgr.GetImageThrow("IMAGE_ZOMBIE_TROPHY_HIGH_RES");
		IMAGE_VERSUS_BACKGROUND = aMgr.GetImageThrow("IMAGE_VERSUS_BACKGROUND");
		IMAGE_VERSUS_WINDOW = aMgr.GetImageThrow("IMAGE_VERSUS_WINDOW");
		IMAGE_VERSUS_WINDOW_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_VERSUS_WINDOW_HIGHLIGHT");
		IMAGE_MINIGAME_3 = aMgr.GetImageThrow("IMAGE_MINIGAME_3");
		IMAGE_MULTIPLAYER_OPTION = aMgr.GetImageThrow("IMAGE_MULTIPLAYER_OPTION");
		IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT = aMgr.GetImageThrow("IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT");
		IMAGE_GRAVESTONE_ROOF1 = aMgr.GetImageThrow("IMAGE_GRAVESTONE_ROOF1");
		IMAGE_GRAVESTONE_ROOF2 = aMgr.GetImageThrow("IMAGE_GRAVESTONE_ROOF2");
		IMAGE_GRAVESTONE_ROOF3 = aMgr.GetImageThrow("IMAGE_GRAVESTONE_ROOF3");
		IMAGE_GRAVESTONE_ROOF4 = aMgr.GetImageThrow("IMAGE_GRAVESTONE_ROOF4");
		IMAGE_GRAVESTONE_ROOF5 = aMgr.GetImageThrow("IMAGE_GRAVESTONE_ROOF5");
		IMAGE_GRAVESTONE_ROOF6 = aMgr.GetImageThrow("IMAGE_GRAVESTONE_ROOF6");
		IMAGE_GRAVESTONE_NIGHT_DIRT = aMgr.GetImageThrow("IMAGE_GRAVESTONE_NIGHT_DIRT");
		IMAGE_MAP_FLIPPED = aMgr.GetImageThrow("IMAGE_MAP_FLIPPED");
		IMAGE_ZOMBIEPOLE = aMgr.GetImageThrow("IMAGE_ZOMBIEPOLE");
		IMAGE_STICK = aMgr.GetImageThrow("IMAGE_STICK");
		IMAGE_GAME_OVER_FLIPPED = aMgr.GetImageThrow("IMAGE_GAME_OVER_FLIPPED");
		IMAGE_REANIM_BUSH_PARTICLE1 = aMgr.GetImageThrow("IMAGE_REANIM_BUSH_PARTICLE1");
		IMAGE_REANIM_BUSH_PARTICLE2 = aMgr.GetImageThrow("IMAGE_REANIM_BUSH_PARTICLE2");
		IMAGE_REANIM_BUSH_PARTICLE3 = aMgr.GetImageThrow("IMAGE_REANIM_BUSH_PARTICLE3");
		IMAGE_REANIM_BUSH_PARTICLE4 = aMgr.GetImageThrow("IMAGE_REANIM_BUSH_PARTICLE4");
		IMAGE_ZOMBIE_BUSHES = aMgr.GetImageThrow("IMAGE_ZOMBIE_BUSHES");
		IMAGE_YOUTUBE_BUTTON = aMgr.GetImageThrow("IMAGE_YOUTUBE_BUTTON");
		IMAGE_YOUTUBE_BUTTON_HOVER = aMgr.GetImageThrow("IMAGE_YOUTUBE_BUTTON_HOVER");
		IMAGE_STONEBUTTON_RIGHT = aMgr.GetImageThrow("IMAGE_STONEBUTTON_RIGHT");
		IMAGE_STONEBUTTON_RIGHT_HOVER = aMgr.GetImageThrow("IMAGE_STONEBUTTON_RIGHT_HOVER");
		IMAGE_STONEBUTTON_LEFT = aMgr.GetImageThrow("IMAGE_STONEBUTTON_LEFT");
		IMAGE_STONEBUTTON_LEFT_HOVER = aMgr.GetImageThrow("IMAGE_STONEBUTTON_LEFT_HOVER");
		IMAGE_RHYTHM_NUMBERGRID = aMgr.GetImageThrow("IMAGE_RHYTHM_NUMBERGRID");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

// LoadingSounds Resources
int Sexy::SOUND_AWOOGA;
int Sexy::SOUND_BALLOONINFLATE;
int Sexy::SOUND_BALLOON_POP;
int Sexy::SOUND_BASKETBALL;
int Sexy::SOUND_BIGCHOMP;
int Sexy::SOUND_BLEEP;
int Sexy::SOUND_BLOOD_MOON;
int Sexy::SOUND_BLOVER;
int Sexy::SOUND_BOING;
int Sexy::SOUND_BONK;
int Sexy::SOUND_BOSSBOULDERATTACK;
int Sexy::SOUND_BOSSEXPLOSION;
int Sexy::SOUND_BOWLING;
int Sexy::SOUND_BOWLINGIMPACT;
int Sexy::SOUND_BOWLINGIMPACT2;
int Sexy::SOUND_BUGSPRAY;
int Sexy::SOUND_BUNGEE_SCREAM;
int Sexy::SOUND_BUNGEE_SCREAM2;
int Sexy::SOUND_BUNGEE_SCREAM3;
int Sexy::SOUND_BUTTER;
int Sexy::SOUND_BUZZER;
int Sexy::SOUND_CERAMIC;
int Sexy::SOUND_CHERRYBOMB;
int Sexy::SOUND_CHILLY_FREEZE;
int Sexy::SOUND_CHIME;
int Sexy::SOUND_CHOMP;
int Sexy::SOUND_CHOMP2;
int Sexy::SOUND_CHOMPSOFT;
int Sexy::SOUND_COBLAUNCH;
int Sexy::SOUND_COFFEE;
int Sexy::SOUND_COIN;
int Sexy::SOUND_CRAZYDAVECRAZY;
int Sexy::SOUND_BRAVEDAVE1;
int Sexy::SOUND_BRAVEDAVE2;
int Sexy::SOUND_BRAVEDAVE3;
int Sexy::SOUND_BRAVEDAVE4;
int Sexy::SOUND_BRAVEDAVE5;
int Sexy::SOUND_BRAVEDAVE6;
int Sexy::SOUND_BEE1;
int Sexy::SOUND_BEE2;
int Sexy::SOUND_BONK1;
int Sexy::SOUND_BONK2;
int Sexy::SOUND_VIOLET;
int Sexy::SOUND_RELOAD;
int Sexy::SOUND_CRASH;
int Sexy::SOUND_BELL;
int Sexy::SOUND_SHOOTINGSTAR;
int Sexy::SOUND_LOG_PLACE;
int Sexy::SOUND_WOODCHIPPER;
int Sexy::SOUND_CRAZYDAVEEXTRALONG1;
int Sexy::SOUND_CRAZYDAVEEXTRALONG2;
int Sexy::SOUND_CRAZYDAVEEXTRALONG3;
int Sexy::SOUND_CRAZYDAVELONG1;
int Sexy::SOUND_CRAZYDAVELONG2;
int Sexy::SOUND_CRAZYDAVELONG3;
int Sexy::SOUND_CRAZYDAVESCREAM;
int Sexy::SOUND_CRAZYDAVESCREAM2;
int Sexy::SOUND_CRAZYDAVESHORT1;
int Sexy::SOUND_CRAZYDAVESHORT2;
int Sexy::SOUND_CRAZYDAVESHORT3;
int Sexy::SOUND_CROW;
int Sexy::SOUND_CROW_DEATH;
int Sexy::SOUND_BREAK;
int Sexy::SOUND_DANCER;
int Sexy::SOUND_DIAMOND;
int Sexy::SOUND_DIGGER_ZOMBIE;
int Sexy::SOUND_DIRT_RISE;
int Sexy::SOUND_DOLPHIN_APPEARS;
int Sexy::SOUND_DOLPHIN_BEFORE_JUMPING;
int Sexy::SOUND_DOOMSHROOM;
int Sexy::SOUND_ELECTRIC;
int Sexy::SOUND_ELECTRIC2;
int Sexy::SOUND_ELECTRIC3;
int Sexy::SOUND_EVILLAUGH;
int Sexy::SOUND_EXPLOSION;
int Sexy::SOUND_FERTILIZER;
int Sexy::SOUND_FINALFANFARE;
int Sexy::SOUND_FINALWAVE;
int Sexy::SOUND_FIREPEA;
int Sexy::SOUND_FLOOP;
int Sexy::SOUND_FROZEN;
int Sexy::SOUND_FUME;
int Sexy::SOUND_GARGANTUAR_THUMP;
int Sexy::SOUND_GARGANTUDEATH;
int Sexy::SOUND_GLADIANTUAR_DEATH;
int Sexy::SOUND_GRASSSTEP;
int Sexy::SOUND_GRAVEBUSTERCHOMP;
int Sexy::SOUND_GRAVEBUTTON;
int Sexy::SOUND_GRAVESTONE_RUMBLE;
int Sexy::SOUND_GROAN;
int Sexy::SOUND_GROAN2;
int Sexy::SOUND_GROAN3;
int Sexy::SOUND_GROAN4;
int Sexy::SOUND_GROAN5;
int Sexy::SOUND_GROAN6;
int Sexy::SOUND_GULP;
int Sexy::SOUND_HATCHBACK_CLOSE;
int Sexy::SOUND_HATCHBACK_OPEN;
int Sexy::SOUND_HUGE_WAVE;
int Sexy::SOUND_HYDRAULIC;
int Sexy::SOUND_HYDRAULIC_SHORT;
int Sexy::SOUND_ICE;
int Sexy::SOUND_IGNITE;
int Sexy::SOUND_IGNITE2;
int Sexy::SOUND_IMP;
int Sexy::SOUND_IMP2;
int Sexy::SOUND_JACKINTHEBOX;
int Sexy::SOUND_JACK_SURPRISE;
int Sexy::SOUND_JACK_SURPRISE2;
int Sexy::SOUND_JALAPENO;
int Sexy::SOUND_JUICY;
int Sexy::SOUND_KERNELPULT;
int Sexy::SOUND_KERNELPULT2;
int Sexy::SOUND_LADDER_ZOMBIE;
int Sexy::SOUND_LAWNMOWER;
int Sexy::SOUND_LIGHTFILL;
int Sexy::SOUND_LIMBS_POP;
int Sexy::SOUND_LOSEMUSIC;
int Sexy::SOUND_LOWGROAN;
int Sexy::SOUND_LOWGROAN2;
int Sexy::SOUND_MAGNETSHROOM;
int Sexy::SOUND_MELONIMPACT;
int Sexy::SOUND_MELONIMPACT2;
int Sexy::SOUND_MINDCONTROLLED;
int Sexy::SOUND_MONEYFALLS;
int Sexy::SOUND_NEWSPAPER_RARRGH;
int Sexy::SOUND_NEWSPAPER_RARRGH2;
int Sexy::SOUND_NEWSPAPER_RIP;
int Sexy::SOUND_PAPER;
int Sexy::SOUND_PAUSE;
int Sexy::SOUND_PHONOGRAPH;
int Sexy::SOUND_PLANT;
int Sexy::SOUND_PLANT2;
int Sexy::SOUND_PLANTERN;
int Sexy::SOUND_PLANTGROW;
int Sexy::SOUND_PLANT_WATER;
int Sexy::SOUND_PLASTICHIT;
int Sexy::SOUND_PLASTICHIT2;
int Sexy::SOUND_POGO_ZOMBIE;
int Sexy::SOUND_POINTS;
int Sexy::SOUND_POLEVAULT;
int Sexy::SOUND_POOL_CLEANER;
int Sexy::SOUND_PORTAL;
int Sexy::SOUND_POTATO_MINE;
int Sexy::SOUND_PRIZE;
int Sexy::SOUND_PUFF;
int Sexy::SOUND_RAIN;
int Sexy::SOUND_READYSETPLANT;
int Sexy::SOUND_REVERSE_EXPLOSION;
int Sexy::SOUND_ROLL_IN;
int Sexy::SOUND_RVTHROW;
int Sexy::SOUND_SCREAM;
int Sexy::SOUND_SEEDLIFT;
int Sexy::SOUND_SHIELDHIT;
int Sexy::SOUND_SHIELDHIT2;
int Sexy::SOUND_SHOOP;
int Sexy::SOUND_SHOVEL;
int Sexy::SOUND_SIREN;
int Sexy::SOUND_SLOT_MACHINE;
int Sexy::SOUND_SLURP;
int Sexy::SOUND_SNOW_PEA_SPARKLES;
int Sexy::SOUND_SPLAT;
int Sexy::SOUND_SPLAT2;
int Sexy::SOUND_SPLAT3;
int Sexy::SOUND_SQUASH_HMM;
int Sexy::SOUND_SQUASH_HMM2;
int Sexy::SOUND_SUKHBIR;
int Sexy::SOUND_SUKHBIR2;
int Sexy::SOUND_SUKHBIR3;
int Sexy::SOUND_SUKHBIR4;
int Sexy::SOUND_SUKHBIR5;
int Sexy::SOUND_SUKHBIR6;
int Sexy::SOUND_SWING;
int Sexy::SOUND_TAP;
int Sexy::SOUND_TAP2;
int Sexy::SOUND_TAPGLASS;
int Sexy::SOUND_THROW;
int Sexy::SOUND_THROW2;
int Sexy::SOUND_THUNDER;
int Sexy::SOUND_VASE_BREAKING;
int Sexy::SOUND_WAKEUP;
int Sexy::SOUND_WAKEUP_REVERSE;
int Sexy::SOUND_WATERING;
int Sexy::SOUND_WINMUSIC;
int Sexy::SOUND_YUCK;
int Sexy::SOUND_YUCK2;
int Sexy::SOUND_ZAMBONI;
int Sexy::SOUND_ZOMBAQUARIUM_DIE;
int Sexy::SOUND_ZOMBIESPLASH;
int Sexy::SOUND_ZOMBIE_ENTERING_WATER;
int Sexy::SOUND_ZOMBIE_FALLING_1;
int Sexy::SOUND_ZOMBIE_FALLING_2;
int Sexy::SOUND_BUSH_RUSTLING1;
int Sexy::SOUND_BUSH_RUSTLING2;
int Sexy::SOUND_BUSH_RUSTLING3;
int Sexy::SOUND_HUNTER_SHOOT;
int Sexy::SOUND_SKELETON_DIE;
int Sexy::SOUND_SKELETON_REVIVE;
int Sexy::SOUND_BUSH_DESTROYED1;
int Sexy::SOUND_BUSH_DESTROYED2;
int Sexy::SOUND_BUSH_DESTROYED3;

bool Sexy::ExtractLoadingSoundsResources(ResourceManager *theManager)
{
	gNeedRecalcVariableToIdMap = true;

	ResourceManager &aMgr = *theManager;
	try
	{
		SOUND_AWOOGA = aMgr.GetSoundThrow("SOUND_AWOOGA");
		SOUND_BALLOONINFLATE = aMgr.GetSoundThrow("SOUND_BALLOONINFLATE");
		SOUND_BALLOON_POP = aMgr.GetSoundThrow("SOUND_BALLOON_POP");
		SOUND_BASKETBALL = aMgr.GetSoundThrow("SOUND_BASKETBALL");
		SOUND_BIGCHOMP = aMgr.GetSoundThrow("SOUND_BIGCHOMP");
		SOUND_BLEEP = aMgr.GetSoundThrow("SOUND_BLEEP");
		SOUND_BLOOD_MOON = aMgr.GetSoundThrow("SOUND_BLOOD_MOON");
		SOUND_BLOVER = aMgr.GetSoundThrow("SOUND_BLOVER");
		SOUND_BOING = aMgr.GetSoundThrow("SOUND_BOING");
		SOUND_BONK = aMgr.GetSoundThrow("SOUND_BONK");
		SOUND_BOSSBOULDERATTACK = aMgr.GetSoundThrow("SOUND_BOSSBOULDERATTACK");
		SOUND_BOSSEXPLOSION = aMgr.GetSoundThrow("SOUND_BOSSEXPLOSION");
		SOUND_BOWLING = aMgr.GetSoundThrow("SOUND_BOWLING");
		SOUND_BOWLINGIMPACT = aMgr.GetSoundThrow("SOUND_BOWLINGIMPACT");
		SOUND_BOWLINGIMPACT2 = aMgr.GetSoundThrow("SOUND_BOWLINGIMPACT2");
		SOUND_BUGSPRAY = aMgr.GetSoundThrow("SOUND_BUGSPRAY");
		SOUND_BUNGEE_SCREAM = aMgr.GetSoundThrow("SOUND_BUNGEE_SCREAM");
		SOUND_BUNGEE_SCREAM2 = aMgr.GetSoundThrow("SOUND_BUNGEE_SCREAM2");
		SOUND_BUNGEE_SCREAM3 = aMgr.GetSoundThrow("SOUND_BUNGEE_SCREAM3");
		SOUND_BUTTER = aMgr.GetSoundThrow("SOUND_BUTTER");
		SOUND_BUZZER = aMgr.GetSoundThrow("SOUND_BUZZER");
		SOUND_CERAMIC = aMgr.GetSoundThrow("SOUND_CERAMIC");
		SOUND_CHERRYBOMB = aMgr.GetSoundThrow("SOUND_CHERRYBOMB");
		SOUND_CHILLY_FREEZE = aMgr.GetSoundThrow("SOUND_CHILLY_FREEZE");
		SOUND_CHIME = aMgr.GetSoundThrow("SOUND_CHIME");
		SOUND_CHOMP = aMgr.GetSoundThrow("SOUND_CHOMP");
		SOUND_CHOMP2 = aMgr.GetSoundThrow("SOUND_CHOMP2");
		SOUND_CHOMPSOFT = aMgr.GetSoundThrow("SOUND_CHOMPSOFT");
		SOUND_COBLAUNCH = aMgr.GetSoundThrow("SOUND_COBLAUNCH");
		SOUND_COFFEE = aMgr.GetSoundThrow("SOUND_COFFEE");
		SOUND_COIN = aMgr.GetSoundThrow("SOUND_COIN");
		SOUND_CRAZYDAVECRAZY = aMgr.GetSoundThrow("SOUND_CRAZYDAVECRAZY");
		SOUND_BRAVEDAVE1 = aMgr.GetSoundThrow("SOUND_BRAVEDAVE1");
		SOUND_BRAVEDAVE2 = aMgr.GetSoundThrow("SOUND_BRAVEDAVE2");
		SOUND_BRAVEDAVE3 = aMgr.GetSoundThrow("SOUND_BRAVEDAVE3");
		SOUND_BRAVEDAVE4 = aMgr.GetSoundThrow("SOUND_BRAVEDAVE4");
		SOUND_BRAVEDAVE5 = aMgr.GetSoundThrow("SOUND_BRAVEDAVE5");
		SOUND_BRAVEDAVE6 = aMgr.GetSoundThrow("SOUND_BRAVEDAVE6");
		SOUND_BEE1 = aMgr.GetSoundThrow("SOUND_BEE1");
		SOUND_BEE2 = aMgr.GetSoundThrow("SOUND_BEE2");
		SOUND_BONK1 = aMgr.GetSoundThrow("SOUND_BONK1");
		SOUND_BONK2 = aMgr.GetSoundThrow("SOUND_BONK2");
		SOUND_VIOLET = aMgr.GetSoundThrow("SOUND_VIOLET");
		SOUND_RELOAD = aMgr.GetSoundThrow("SOUND_RELOAD");
		SOUND_CRASH = aMgr.GetSoundThrow("SOUND_CRASH");
		SOUND_BELL = aMgr.GetSoundThrow("SOUND_BELL");
		SOUND_SHOOTINGSTAR = aMgr.GetSoundThrow("SOUND_SHOOTINGSTAR");
		SOUND_LOG_PLACE = aMgr.GetSoundThrow("SOUND_LOG_PLACE");
		SOUND_WOODCHIPPER = aMgr.GetSoundThrow("SOUND_WOODCHIPPER");
		SOUND_CRAZYDAVEEXTRALONG1 = aMgr.GetSoundThrow("SOUND_CRAZYDAVEEXTRALONG1");
		SOUND_CRAZYDAVEEXTRALONG2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVEEXTRALONG2");
		SOUND_CRAZYDAVEEXTRALONG3 = aMgr.GetSoundThrow("SOUND_CRAZYDAVEEXTRALONG3");
		SOUND_CRAZYDAVELONG1 = aMgr.GetSoundThrow("SOUND_CRAZYDAVELONG1");
		SOUND_CRAZYDAVELONG2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVELONG2");
		SOUND_CRAZYDAVELONG3 = aMgr.GetSoundThrow("SOUND_CRAZYDAVELONG3");
		SOUND_CRAZYDAVESCREAM = aMgr.GetSoundThrow("SOUND_CRAZYDAVESCREAM");
		SOUND_CRAZYDAVESCREAM2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESCREAM2");
		SOUND_CRAZYDAVESHORT1 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESHORT1");
		SOUND_CRAZYDAVESHORT2 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESHORT2");
		SOUND_CRAZYDAVESHORT3 = aMgr.GetSoundThrow("SOUND_CRAZYDAVESHORT3");
		SOUND_CROW = aMgr.GetSoundThrow("SOUND_CROW");
		SOUND_CROW_DEATH = aMgr.GetSoundThrow("SOUND_CROW_DEATH");
		SOUND_BREAK = aMgr.GetSoundThrow("SOUND_BREAK");
		SOUND_DANCER = aMgr.GetSoundThrow("SOUND_DANCER");
		SOUND_DIAMOND = aMgr.GetSoundThrow("SOUND_DIAMOND");
		SOUND_DIGGER_ZOMBIE = aMgr.GetSoundThrow("SOUND_DIGGER_ZOMBIE");
		SOUND_DIRT_RISE = aMgr.GetSoundThrow("SOUND_DIRT_RISE");
		SOUND_DOLPHIN_APPEARS = aMgr.GetSoundThrow("SOUND_DOLPHIN_APPEARS");
		SOUND_DOLPHIN_BEFORE_JUMPING = aMgr.GetSoundThrow("SOUND_DOLPHIN_BEFORE_JUMPING");
		SOUND_DOOMSHROOM = aMgr.GetSoundThrow("SOUND_DOOMSHROOM");
		SOUND_ELECTRIC = aMgr.GetSoundThrow("SOUND_ELECTRIC");
		SOUND_ELECTRIC2 = aMgr.GetSoundThrow("SOUND_ELECTRIC2");
		SOUND_ELECTRIC3 = aMgr.GetSoundThrow("SOUND_ELECTRIC3");
		SOUND_EVILLAUGH = aMgr.GetSoundThrow("SOUND_EVILLAUGH");
		SOUND_EXPLOSION = aMgr.GetSoundThrow("SOUND_EXPLOSION");
		SOUND_FERTILIZER = aMgr.GetSoundThrow("SOUND_FERTILIZER");
		SOUND_FINALFANFARE = aMgr.GetSoundThrow("SOUND_FINALFANFARE");
		SOUND_FINALWAVE = aMgr.GetSoundThrow("SOUND_FINALWAVE");
		SOUND_FIREPEA = aMgr.GetSoundThrow("SOUND_FIREPEA");
		SOUND_FLOOP = aMgr.GetSoundThrow("SOUND_FLOOP");
		SOUND_FROZEN = aMgr.GetSoundThrow("SOUND_FROZEN");
		SOUND_FUME = aMgr.GetSoundThrow("SOUND_FUME");
		SOUND_GARGANTUAR_THUMP = aMgr.GetSoundThrow("SOUND_GARGANTUAR_THUMP");
		SOUND_GARGANTUDEATH = aMgr.GetSoundThrow("SOUND_GARGANTUDEATH");
		SOUND_GLADIANTUAR_DEATH = aMgr.GetSoundThrow("SOUND_GLADIANTUAR_DEATH");
		SOUND_GRASSSTEP = aMgr.GetSoundThrow("SOUND_GRASSSTEP");
		SOUND_GRAVEBUSTERCHOMP = aMgr.GetSoundThrow("SOUND_GRAVEBUSTERCHOMP");
		SOUND_GRAVEBUTTON = aMgr.GetSoundThrow("SOUND_GRAVEBUTTON");
		SOUND_GRAVESTONE_RUMBLE = aMgr.GetSoundThrow("SOUND_GRAVESTONE_RUMBLE");
		SOUND_GROAN = aMgr.GetSoundThrow("SOUND_GROAN");
		SOUND_GROAN2 = aMgr.GetSoundThrow("SOUND_GROAN2");
		SOUND_GROAN3 = aMgr.GetSoundThrow("SOUND_GROAN3");
		SOUND_GROAN4 = aMgr.GetSoundThrow("SOUND_GROAN4");
		SOUND_GROAN5 = aMgr.GetSoundThrow("SOUND_GROAN5");
		SOUND_GROAN6 = aMgr.GetSoundThrow("SOUND_GROAN6");
		SOUND_GULP = aMgr.GetSoundThrow("SOUND_GULP");
		SOUND_HATCHBACK_CLOSE = aMgr.GetSoundThrow("SOUND_HATCHBACK_CLOSE");
		SOUND_HATCHBACK_OPEN = aMgr.GetSoundThrow("SOUND_HATCHBACK_OPEN");
		SOUND_HUGE_WAVE = aMgr.GetSoundThrow("SOUND_HUGE_WAVE");
		SOUND_HYDRAULIC = aMgr.GetSoundThrow("SOUND_HYDRAULIC");
		SOUND_HYDRAULIC_SHORT = aMgr.GetSoundThrow("SOUND_HYDRAULIC_SHORT");
		SOUND_ICE = aMgr.GetSoundThrow("SOUND_ICE");
		SOUND_IGNITE = aMgr.GetSoundThrow("SOUND_IGNITE");
		SOUND_IGNITE2 = aMgr.GetSoundThrow("SOUND_IGNITE2");
		SOUND_IMP = aMgr.GetSoundThrow("SOUND_IMP");
		SOUND_IMP2 = aMgr.GetSoundThrow("SOUND_IMP2");
		SOUND_JACKINTHEBOX = aMgr.GetSoundThrow("SOUND_JACKINTHEBOX");
		SOUND_JACK_SURPRISE = aMgr.GetSoundThrow("SOUND_JACK_SURPRISE");
		SOUND_JACK_SURPRISE2 = aMgr.GetSoundThrow("SOUND_JACK_SURPRISE2");
		SOUND_JALAPENO = aMgr.GetSoundThrow("SOUND_JALAPENO");
		SOUND_JUICY = aMgr.GetSoundThrow("SOUND_JUICY");
		SOUND_KERNELPULT = aMgr.GetSoundThrow("SOUND_KERNELPULT");
		SOUND_KERNELPULT2 = aMgr.GetSoundThrow("SOUND_KERNELPULT2");
		SOUND_LADDER_ZOMBIE = aMgr.GetSoundThrow("SOUND_LADDER_ZOMBIE");
		SOUND_LAWNMOWER = aMgr.GetSoundThrow("SOUND_LAWNMOWER");
		SOUND_LIGHTFILL = aMgr.GetSoundThrow("SOUND_LIGHTFILL");
		SOUND_LIMBS_POP = aMgr.GetSoundThrow("SOUND_LIMBS_POP");
		SOUND_LOSEMUSIC = aMgr.GetSoundThrow("SOUND_LOSEMUSIC");
		SOUND_LOWGROAN = aMgr.GetSoundThrow("SOUND_LOWGROAN");
		SOUND_LOWGROAN2 = aMgr.GetSoundThrow("SOUND_LOWGROAN2");
		SOUND_MAGNETSHROOM = aMgr.GetSoundThrow("SOUND_MAGNETSHROOM");
		SOUND_MELONIMPACT = aMgr.GetSoundThrow("SOUND_MELONIMPACT");
		SOUND_MELONIMPACT2 = aMgr.GetSoundThrow("SOUND_MELONIMPACT2");
		SOUND_MINDCONTROLLED = aMgr.GetSoundThrow("SOUND_MINDCONTROLLED");
		SOUND_MONEYFALLS = aMgr.GetSoundThrow("SOUND_MONEYFALLS");
		SOUND_NEWSPAPER_RARRGH = aMgr.GetSoundThrow("SOUND_NEWSPAPER_RARRGH");
		SOUND_NEWSPAPER_RARRGH2 = aMgr.GetSoundThrow("SOUND_NEWSPAPER_RARRGH2");
		SOUND_NEWSPAPER_RIP = aMgr.GetSoundThrow("SOUND_NEWSPAPER_RIP");
		SOUND_PAPER = aMgr.GetSoundThrow("SOUND_PAPER");
		SOUND_PAUSE = aMgr.GetSoundThrow("SOUND_PAUSE");
		SOUND_PHONOGRAPH = aMgr.GetSoundThrow("SOUND_PHONOGRAPH");
		SOUND_PLANT = aMgr.GetSoundThrow("SOUND_PLANT");
		SOUND_PLANT2 = aMgr.GetSoundThrow("SOUND_PLANT2");
		SOUND_PLANTERN = aMgr.GetSoundThrow("SOUND_PLANTERN");
		SOUND_PLANTGROW = aMgr.GetSoundThrow("SOUND_PLANTGROW");
		SOUND_PLANT_WATER = aMgr.GetSoundThrow("SOUND_PLANT_WATER");
		SOUND_PLASTICHIT = aMgr.GetSoundThrow("SOUND_PLASTICHIT");
		SOUND_PLASTICHIT2 = aMgr.GetSoundThrow("SOUND_PLASTICHIT2");
		SOUND_POGO_ZOMBIE = aMgr.GetSoundThrow("SOUND_POGO_ZOMBIE");
		SOUND_POINTS = aMgr.GetSoundThrow("SOUND_POINTS");
		SOUND_POLEVAULT = aMgr.GetSoundThrow("SOUND_POLEVAULT");
		SOUND_POOL_CLEANER = aMgr.GetSoundThrow("SOUND_POOL_CLEANER");
		SOUND_PORTAL = aMgr.GetSoundThrow("SOUND_PORTAL");
		SOUND_POTATO_MINE = aMgr.GetSoundThrow("SOUND_POTATO_MINE");
		SOUND_PRIZE = aMgr.GetSoundThrow("SOUND_PRIZE");
		SOUND_PUFF = aMgr.GetSoundThrow("SOUND_PUFF");
		SOUND_RAIN = aMgr.GetSoundThrow("SOUND_RAIN");
		SOUND_READYSETPLANT = aMgr.GetSoundThrow("SOUND_READYSETPLANT");
		SOUND_REVERSE_EXPLOSION = aMgr.GetSoundThrow("SOUND_REVERSE_EXPLOSION");
		SOUND_ROLL_IN = aMgr.GetSoundThrow("SOUND_ROLL_IN");
		SOUND_RVTHROW = aMgr.GetSoundThrow("SOUND_RVTHROW");
		SOUND_SCREAM = aMgr.GetSoundThrow("SOUND_SCREAM");
		SOUND_SEEDLIFT = aMgr.GetSoundThrow("SOUND_SEEDLIFT");
		SOUND_SHIELDHIT = aMgr.GetSoundThrow("SOUND_SHIELDHIT");
		SOUND_SHIELDHIT2 = aMgr.GetSoundThrow("SOUND_SHIELDHIT2");
		SOUND_SHOOP = aMgr.GetSoundThrow("SOUND_SHOOP");
		SOUND_SHOVEL = aMgr.GetSoundThrow("SOUND_SHOVEL");
		SOUND_SIREN = aMgr.GetSoundThrow("SOUND_SIREN");
		SOUND_SLOT_MACHINE = aMgr.GetSoundThrow("SOUND_SLOT_MACHINE");
		SOUND_SLURP = aMgr.GetSoundThrow("SOUND_SLURP");
		SOUND_SNOW_PEA_SPARKLES = aMgr.GetSoundThrow("SOUND_SNOW_PEA_SPARKLES");
		SOUND_SPLAT = aMgr.GetSoundThrow("SOUND_SPLAT");
		SOUND_SPLAT2 = aMgr.GetSoundThrow("SOUND_SPLAT2");
		SOUND_SPLAT3 = aMgr.GetSoundThrow("SOUND_SPLAT3");
		SOUND_SQUASH_HMM = aMgr.GetSoundThrow("SOUND_SQUASH_HMM");
		SOUND_SQUASH_HMM2 = aMgr.GetSoundThrow("SOUND_SQUASH_HMM2");
		SOUND_SUKHBIR = aMgr.GetSoundThrow("SOUND_SUKHBIR");
		SOUND_SUKHBIR2 = aMgr.GetSoundThrow("SOUND_SUKHBIR2");
		SOUND_SUKHBIR3 = aMgr.GetSoundThrow("SOUND_SUKHBIR3");
		SOUND_SUKHBIR4 = aMgr.GetSoundThrow("SOUND_SUKHBIR4");
		SOUND_SUKHBIR5 = aMgr.GetSoundThrow("SOUND_SUKHBIR5");
		SOUND_SUKHBIR6 = aMgr.GetSoundThrow("SOUND_SUKHBIR6");
		SOUND_SWING = aMgr.GetSoundThrow("SOUND_SWING");
		SOUND_TAP = aMgr.GetSoundThrow("SOUND_TAP");
		SOUND_TAP2 = aMgr.GetSoundThrow("SOUND_TAP2");
		SOUND_TAPGLASS = aMgr.GetSoundThrow("SOUND_TAPGLASS");
		SOUND_THROW = aMgr.GetSoundThrow("SOUND_THROW");
		SOUND_THROW2 = aMgr.GetSoundThrow("SOUND_THROW2");
		SOUND_THUNDER = aMgr.GetSoundThrow("SOUND_THUNDER");
		SOUND_VASE_BREAKING = aMgr.GetSoundThrow("SOUND_VASE_BREAKING");
		SOUND_WAKEUP = aMgr.GetSoundThrow("SOUND_WAKEUP");
		SOUND_WAKEUP_REVERSE = aMgr.GetSoundThrow("SOUND_WAKEUP_REVERSE");
		SOUND_WATERING = aMgr.GetSoundThrow("SOUND_WATERING");
		SOUND_WINMUSIC = aMgr.GetSoundThrow("SOUND_WINMUSIC");
		SOUND_YUCK = aMgr.GetSoundThrow("SOUND_YUCK");
		SOUND_YUCK2 = aMgr.GetSoundThrow("SOUND_YUCK2");
		SOUND_ZAMBONI = aMgr.GetSoundThrow("SOUND_ZAMBONI");
		SOUND_ZOMBAQUARIUM_DIE = aMgr.GetSoundThrow("SOUND_ZOMBAQUARIUM_DIE");
		SOUND_ZOMBIESPLASH = aMgr.GetSoundThrow("SOUND_ZOMBIESPLASH");
		SOUND_ZOMBIE_ENTERING_WATER = aMgr.GetSoundThrow("SOUND_ZOMBIE_ENTERING_WATER");
		SOUND_ZOMBIE_FALLING_1 = aMgr.GetSoundThrow("SOUND_ZOMBIE_FALLING_1");
		SOUND_ZOMBIE_FALLING_2 = aMgr.GetSoundThrow("SOUND_ZOMBIE_FALLING_2");
		SOUND_BUSH_RUSTLING1 = aMgr.GetSoundThrow("SOUND_BUSH_RUSTLING1");
		SOUND_BUSH_RUSTLING2 = aMgr.GetSoundThrow("SOUND_BUSH_RUSTLING2");
		SOUND_BUSH_RUSTLING3 = aMgr.GetSoundThrow("SOUND_BUSH_RUSTLING3");
		SOUND_HUNTER_SHOOT = aMgr.GetSoundThrow("SOUND_HUNTER_SHOOT");
		SOUND_SKELETON_DIE = aMgr.GetSoundThrow("SOUND_SKELETON_DIE");
		SOUND_SKELETON_REVIVE = aMgr.GetSoundThrow("SOUND_SKELETON_REVIVE");
		SOUND_BUSH_DESTROYED1 = aMgr.GetSoundThrow("SOUND_BUSH_DESTROYED1");
		SOUND_BUSH_DESTROYED2 = aMgr.GetSoundThrow("SOUND_BUSH_DESTROYED2");
		SOUND_BUSH_DESTROYED3 = aMgr.GetSoundThrow("SOUND_BUSH_DESTROYED3");
	}
	catch(ResourceManagerException&)
	{
		return false;
	}
	return true;
}

static void* gResources[] =
{
	&IMAGE_BLANK,
	&IMAGE_POPCAP_LOGO,
	&IMAGE_NEW_LOGO,
	&IMAGE_PARTNER_LOGO,
	&IMAGE_TITLESCREEN,
	&IMAGE_LOADBAR_DIRT,
	&IMAGE_LOADBAR_GRASS,
	&IMAGE_PVZ_LOGO,
	&IMAGE_REANIM_SODROLLCAP,
	&FONT_BRIANNETOD16,
	&SOUND_BUTTONCLICK,
	&SOUND_LOADINGBAR_FLOWER,
	&SOUND_LOADINGBAR_ZOMBIE,
	&FONT_IMAGE_HOUSEOFTERROR28,
	&FONT_HOUSEOFTERROR28,
	&FONT_HOUSEOFTERROR20,
	&FONT_HOUSEOFTERROR16,
	&FONT_LUCKFIXHOUSEOFTERROR15,
	&FONT_TINYBOLD,
	&FONT_CONTINUUMBOLD14,
	&FONT_CONTINUUMBOLD14OUTLINE,
	&FONT_DWARVENTODCRAFT12,
	&FONT_DWARVENTODCRAFT15,
	&FONT_DWARVENTODCRAFT18,
	&FONT_DWARVENTODCRAFT18BRIGHTGREENINSET,
	&FONT_DWARVENTODCRAFT18GREENINSET,
	&FONT_DWARVENTODCRAFT18YELLOW,
	&FONT_DWARVENTODCRAFT24,
	&FONT_DWARVENTODCRAFT36BRIGHTGREENINSET,
	&FONT_DWARVENTODCRAFT36GREENINSET,
	&FONT_PICO129,
	&FONT_BRIANNETOD12,
	//&FONT_BRIANNETOD9,
	&FONT_PIX118BOLD,
	&IMAGE_EDITBOX,
	&IMAGE_DIALOG_TOPLEFT,
	&IMAGE_DIALOG_TOPMIDDLE,
	&IMAGE_DIALOG_TOPRIGHT,
	&IMAGE_DIALOG_CENTERLEFT,
	&IMAGE_DIALOG_CENTERMIDDLE,
	&IMAGE_DIALOG_CENTERRIGHT,
	&IMAGE_DIALOG_BOTTOMLEFT,
	&IMAGE_DIALOG_BOTTOMMIDDLE,
	&IMAGE_DIALOG_BOTTOMRIGHT,
	&IMAGE_DIALOG_BIGBOTTOMLEFT,
	&IMAGE_DIALOG_BIGBOTTOMMIDDLE,
	&IMAGE_DIALOG_BIGBOTTOMRIGHT,
	&IMAGE_DIALOG_HEADER,
	&IMAGE_BUTTON_LEFT,
	&IMAGE_BUTTON_MIDDLE,
	&IMAGE_BUTTON_RIGHT,
	&IMAGE_BUTTON_DOWN_LEFT,
	&IMAGE_BUTTON_DOWN_MIDDLE,
	&IMAGE_BUTTON_DOWN_RIGHT,
	&IMAGE_ALMANAC_SHIRT,
	&IMAGE_ALMANAC_GOLDEN_LOCK,
	&IMAGE_SEEDCHOOSER_BACKGROUND,
	&IMAGE_SEEDCHOOSER_BACKGROUND_ZOMBIES,
	&IMAGE_SEEDCHOOSER_BUTTON,
	&IMAGE_SEEDCHOOSER_BUTTON_DISABLED,
	&IMAGE_SEEDCHOOSER_BUTTON_GLOW,
	&IMAGE_SEEDCHOOSER_BUTTON2,
	&IMAGE_SEEDCHOOSER_BUTTON2_GLOW,
	&IMAGE_SEEDCHOOSER_IMITATERADDON,
	&IMAGE_SEEDS,
	&IMAGE_SEEDPACKET_LARGER,
	&IMAGE_SEEDPACKETSILHOUETTE,
	&IMAGE_FLAGMETER,
	&IMAGE_FLAGMETERLEVELPROGRESS,
	&IMAGE_FLAGMETERPARTS,
	&IMAGE_FLAGMETERPARTS_HARDMODE,
	&IMAGE_TROPHY,
	&IMAGE_DIAMOND_TROPHY,
	&IMAGE_TROPHY_HI_RES,
	&IMAGE_DIAMOND_TROPHY_HI_RES,
	&IMAGE_MINIGAME_TROPHY,
	&IMAGE_ZOMBIE_NOTE_SMALL,
	&IMAGE_TACO,
	&IMAGE_CARKEYS,
	&IMAGE_ALMANAC,
	&IMAGE_ICON_POOLCLEANER,
	&IMAGE_ICON_ROOFCLEANER,
	&IMAGE_ICON_RAKE,
	&IMAGE_BRAIN,
	&IMAGE_MONEYBAG,
	&IMAGE_MONEYBAG_HI_RES,
	&IMAGE_CHOCOLATE,
	&IMAGE_OPTIONS_BACKTOGAMEBUTTON0,
	&IMAGE_OPTIONS_BACKTOGAMEBUTTON2,
	&IMAGE_OPTIONS_CHECKBOX0,
	&IMAGE_OPTIONS_CHECKBOX1,
	&IMAGE_OPTIONS_MENUBACK,
	&IMAGE_OPTIONS_SLIDERKNOB2,
	&IMAGE_OPTIONS_SLIDERSLOT,
	&IMAGE_SELECTORSCREEN_HELP1,
	&IMAGE_SELECTORSCREEN_HELP2,
	&IMAGE_SELECTORSCREEN_OPTIONS1,
	&IMAGE_SELECTORSCREEN_OPTIONS2,
	&IMAGE_SELECTORSCREEN_QUIT1,
	&IMAGE_SELECTORSCREEN_QUIT2,
	&IMAGE_SELECTORSCREEN_ALMANAC,
	&IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT,
	&IMAGE_SELECTORSCREEN_STORE,
	&IMAGE_SELECTORSCREEN_STOREHIGHLIGHT,
	&IMAGE_SELECTORSCREEN_LEVELNUMBERS,
	&IMAGE_SELECTORSCREEN_ZENGARDEN,
	&IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT,
	&IMAGE_STORE_SPEECHBUBBLE,
	&IMAGE_STORE_SPEECHBUBBLE2,
	&IMAGE_SHOVEL,
	&IMAGE_SHOVEL_HI_RES,
	&IMAGE_TOMBSTONES,
	&IMAGE_TOMBSTONE_MOUNDS,
	&IMAGE_NIGHT_GRAVE_GRAPHIC,
	&IMAGE_CRATER,
	&IMAGE_CRATER_FADING,
	&IMAGE_CRATER_ROOF_CENTER,
	&IMAGE_CRATER_ROOF_LEFT,
	&IMAGE_CRATER_WATER_DAY,
	&IMAGE_CRATER_WATER_NIGHT,
	&IMAGE_COBCANNON_TARGET,
	&IMAGE_COBCANNON_POPCORN,
	&IMAGE_FERTILIZER,
	&IMAGE_WATERINGCAN,
	&IMAGE_WATERINGCANGOLD,
	&IMAGE_PHONOGRAPH,
	&IMAGE_BEGHOULED_TWIST_OVERLAY,
	&IMAGE_ZEN_GOLDTOOLRETICLE,
	&IMAGE_ZEN_GARDENGLOVE,
	&IMAGE_ZEN_MONEYSIGN,
	&IMAGE_ZEN_NEXTGARDEN,
	&IMAGE_ZEN_WHEELBARROW,
	&IMAGE_ZENSHOPBUTTON,
	&IMAGE_ZENSHOPBUTTON_HIGHLIGHT,
	&IMAGE_PRESENT,
	&IMAGE_PRESENTOPEN,
	&IMAGE_SUNFLOWER_TROPHY,
	&IMAGE_DIAMOND_SUNFLOWER_TROPHY,
	&IMAGE_SLOTMACHINE_OVERLAY,
	&IMAGE_SCARY_POT,
	&IMAGE_BUG_SPRAY,
	&IMAGE_PLANTSPEECHBUBBLE,
	&IMAGE_WATERDROP,
	&IMAGE_TREEFOOD,
	&IMAGE_PACKET_PLANTS,
	&IMAGE_ZEN_NEED_ICONS,
	&IMAGE_PROJECTILEPEA,
	&IMAGE_PROJECTILESNOWPEA,
	&IMAGE_PROJECTILECACTUS,
	&IMAGE_DIRTSMALL,
	&IMAGE_DIRTBIG,
	&IMAGE_ROCKSMALL,
	&IMAGE_WATERPARTICLE,
	&IMAGE_WHITEWATER,
	&IMAGE_WHITEWATER_SHADOW,
	&IMAGE_MELONPULT_PARTICLES,
	&IMAGE_WINTERMELON_PARTICLES,
	&IMAGE_PROJECTILE_STAR,
	&IMAGE_SEEDBANK,
	&IMAGE_CONVEYORBELT_BACKDROP,
	&IMAGE_CONVEYORBELT,
	&IMAGE_SHOVELBANK,
	&IMAGE_SUNBANK,
	&IMAGE_COINBANK,
	&IMAGE_POOL,
	&IMAGE_POOL_NIGHT,
	&IMAGE_POOL_BASE,
	&IMAGE_POOL_BASE_NIGHT,
	&IMAGE_POOL_SHADING,
	&IMAGE_POOL_SHADING_NIGHT,
	&IMAGE_POOL_CAUSTIC_EFFECT,
	&IMAGE_PLANTSHADOW,
	&IMAGE_PLANTSHADOW2,
	&IMAGE_PEA_SHADOWS,
	&IMAGE_WALLNUT_BOWLINGSTRIPE,
	&IMAGE_FLOWER_STRIPE,
	&IMAGE_ICE,
	&IMAGE_ICE_CAP,
	&IMAGE_ICE_SPARKLES,
	&IMAGE_IMITATERSEED,
	&IMAGE_ALMANAC_IMITATER,
	&IMAGE_IMITATERSEEDDISABLED,
	&IMAGE_ICETRAP,
	&IMAGE_ICETRAP2,
	&IMAGE_ICETRAP_PARTICLES,
	&IMAGE_ELECTRIC,
	&IMAGE_FF1,
	&IMAGE_FF2,
	&IMAGE_BACKGROUND_BLOODMOON,
	&IMAGE_PROJECTILEICEQUEEN,
	&IMAGE_PROJECTILE_SEASTAR,
	&IMAGE_LOCKED_ZOMBIE,
	&IMAGE_NEW_SURVIVAL_THUMBNAIL,
	&IMAGE_ALMANAC_PLANTBACK_2,
	&IMAGE_BRAINBANK,
	&IMAGE_BRAINBANK_SMALL,
	&IMAGE_STONE2,
	&IMAGE_STONE3,
	&IMAGE_STONE4,
	&IMAGE_STONE5,
	&IMAGE_ZOMBIE_PACK,
	&IMAGE_S_FLAG1,
	&IMAGE_S_FLAG2,
	&IMAGE_Z_FLAG1,
	&IMAGE_Z_FLAG2,
	&IMAGE_D_FLAG1,
	&IMAGE_D_FLAG2,
	&IMAGE_R_FLAG1,
	&IMAGE_R_FLAG2,
	&IMAGE_M_FLAG1,
	&IMAGE_M_FLAG2,
	&IMAGE_F_FLAG1,
	&IMAGE_F_FLAG2,
	&IMAGE_C_FLAG1,
	&IMAGE_C_FLAG2,
	&IMAGE_E_FLAG1,
	&IMAGE_E_FLAG2,
	&IMAGE_MA_FLAG1,
	&IMAGE_MA_FLAG2,
	&IMAGE_DA_FLAG1,
	&IMAGE_DA_FLAG2,
	&IMAGE_IP_FLAG1,
	&IMAGE_IP_FLAG2,
	&IMAGE_SH_FLAG1,
	&IMAGE_SH_FLAG2,
	&IMAGE_PR_FLAG1,
	&IMAGE_PR_FLAG2,
	&IMAGE_HW_FLAG1,
	&IMAGE_HW_FLAG2,
	&IMAGE_YY_FLAG1,
	&IMAGE_YY_FLAG2,
	&IMAGE_KF_FLAG1,
	&IMAGE_KF_FLAG2,
	&IMAGE_L_BUTTON1,
	&IMAGE_L_BUTTON2,
	&IMAGE_R_BUTTON1,
	&IMAGE_R_BUTTON2,
	&IMAGE_BACKGROUND_PP,
	&IMAGE_BACKGROUND_ICE,
	&IMAGE_BOMBALL,
	&IMAGE_BACKGROUND_GLADIANTUAR,
	&IMAGE_BACKGROUND_HIGHGROUND,
	&IMAGE_MINIGAME_2,
	&IMAGE_BACKGROUND_FOREST,
	&IMAGE_OAK_ARROW,
	&IMAGE_SEEDBANK_SMALL,
	&IMAGE_TARGET,
	&IMAGE_CROSS,
	&IMAGE_TARGET_1,
	&IMAGE_TARGET_2,
	&IMAGE_TARGET_3,
	&IMAGE_P1_1,
	&IMAGE_P1_2,
	&IMAGE_P1_3,
	&IMAGE_P2_1,
	&IMAGE_P2_2,
	&IMAGE_P2_3,
	&IMAGE_BEJEWEL_SELECTORSHADOW,
	&IMAGE_VERSUS_BUTTON,
	&IMAGE_VERSUS_BUTTON_HIGHLIGHTED,
	&IMAGE_PUDDLE,
	&IMAGE_ZOMBIE_BOBSLED1,
	&IMAGE_ZOMBIE_BOBSLED2,
	&IMAGE_ZOMBIE_BOBSLED3,
	&IMAGE_ZOMBIE_BOBSLED4,
	&IMAGE_ZOMBIE_BOBSLED_INSIDE,
	&IMAGE_BUNGEECORD,
	&IMAGE_BUNGEETARGET,
	&IMAGE_SPOTLIGHT,
	&IMAGE_SPOTLIGHT2,
	&IMAGE_WHITEPIXEL,
	&IMAGE_ZOMBIEPOLEVAULTERARM,
	&IMAGE_ZOMBIEPOLEVAULTERHEAD,
	&IMAGE_ZOMBIEFOOTBALLHEAD,
	&IMAGE_ZOMBIEPAPERARM,
	&IMAGE_POOLSPARKLY,
	&IMAGE_WALLNUTPARTICLESSMALL,
	&IMAGE_WALLNUTPARTICLESLARGE,
	&IMAGE_PEA_SPLATS,
	&IMAGE_STAR_PARTICLES,
	&IMAGE_STAR_SPLATS,
	&IMAGE_PEA_PARTICLES,
	&IMAGE_SNOWPEA_SPLATS,
	&IMAGE_SNOWPEA_PARTICLES,
	&IMAGE_SNOWPEA_PUFF,
	&IMAGE_SNOWFLAKES,
	&IMAGE_POTATOMINE_PARTICLES,
	&IMAGE_PUFFSHROOM_PUFF1,
	&IMAGE_ZAMBONISMOKE,
	&IMAGE_ZOMBIEDANCERARM,
	&IMAGE_ZOMBIEDANCERHEAD,
	&IMAGE_ZOMBIEBALLOONHEAD,
	&IMAGE_ZOMBIEIMPHEAD,
	&IMAGE_ZOMBIEDIGGERHEAD,
	&IMAGE_ZOMBIEDIGGERARM,
	&IMAGE_ZOMBIEDOLPHINRIDERHEAD,
	&IMAGE_ZOMBIEPOGO,
	&IMAGE_ZOMBIEPOGOARM,
	&IMAGE_ZOMBIEBACKUPDANCERARM,
	&IMAGE_ZOMBIEBACKUPDANCERHEAD,
	&IMAGE_ZOMBIEBOBSLEDHEAD,
	&IMAGE_ZOMBIELADDERARM,
	&IMAGE_ZOMBIELADDERHEAD,
	&IMAGE_ZOMBIEYETIHEAD,
	&IMAGE_SEEDPACKETFLASH,
	&IMAGE_ZOMBIEJACKBOXARM,
	&IMAGE_IMITATERCLOUDS,
	&IMAGE_IMITATERPUFFS,
	&IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES,
	&IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES,
	&IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES,
	&IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES,
	&IMAGE_DOOMSHROOM_EXPLOSION_BASE,
	&IMAGE_RAIN,
	&IMAGE_MINIGAME_DIAMOND_TROPHY,
	&IMAGE_VASE_CHUNKS,
	&IMAGE_ZOMBOSS_PARTICLES,
	&IMAGE_AWARDPICKUPGLOW,
	&IMAGE_ZOMBIE_SEAWEED,
	&IMAGE_PINATA,
	&IMAGE_ZOMBIEFUTUREGLASSES,
	&IMAGE_DUST_PUFFS,
	&IMAGE_ZOMBIEVAMPIREHEAD,
	&IMAGE_ZOMBIEFISHERHEAD,
	&IMAGE_ZOMBIELEAFBLOWERHEAD,
	&IMAGE_ZOMBIEAXEHEAD,
	&IMAGE_ZOMBIEBIGFOOTHEAD,
	&IMAGE_ZOMBIEVAMPIREARM,
	&IMAGE_ZOMBIESCARECROWARM,
	&IMAGE_ZOMBIEFISHERARM,
	&IMAGE_ZOMBIEHUNTERARM,
	&IMAGE_ZOMBIELEAFBLOWERARM,
	&IMAGE_ZOMBIEAXEARM,
	&IMAGE_ZOMBIEBIGFOOTARM,
	&IMAGE_CREDITSBACKGROUND,
	&IMAGE_DISCLAIMERBACKGROUND,
	&IMAGE_CREDITS_BTN1,
	&IMAGE_CREDITS_BTN2,
	&IMAGE_DISCLAIMER_BTN1,
	&IMAGE_DISCLAIMER_BTN2,
	&IMAGE_CROW1,
	&IMAGE_CROW2,
	&IMAGE_VIOLET_PADDLE,
	&IMAGE_FOREST_OBJECTS,
	&IMAGE_LOG1,
	&IMAGE_LOG2,
	&IMAGE_LOG3,
	&IMAGE_GEM_RED,
	&IMAGE_GEM_GREEN,
	&IMAGE_GEM_WHITE,
	&IMAGE_GEM_PURPLE,
	&IMAGE_GEM_YELLOW,
	&IMAGE_GEM_ORANGE,
	&IMAGE_FLASHLIGHT_LIGHT,
	&IMAGE_FOREST_NIGHT_MAP,
	&IMAGE_FOREST_NIGHT_ITEMS,
	&IMAGE_VINENUT_2,
	&IMAGE_VINENUT_3,
	&IMAGE_VINENUT_2_BODY,
	&IMAGE_VINENUT_3_BODY,
	&IMAGE_NET,
	&IMAGE_GAME,
	&IMAGE_GAME2,
	&IMAGE_WOOD,
	&IMAGE_HUNTER_HAT,
	&IMAGE_VERSUS_NOTE,
	&IMAGE_BACKGROUND7_GAMEOVER_MASK,
	&IMAGE_BACKGROUNDPP_GAMEOVER_MASK,
	&IMAGE_BACKGROUND_GLADIANTUAR_GAMEOVER_MASK,
	&IMAGE_WOODS_NOTE,
	&IMAGE_SHOVEL_ROTATED,
	&IMAGE_ICON_WOODCHIPPER,
	&IMAGE_ICON_NEW,
	&IMAGE_PLAYER1_MOUSE,
	&IMAGE_PLAYER2_MOUSE,
	&IMAGE_PLAYER1_KEYBOARD,
	&IMAGE_PLAYER2_KEYBOARD,
	&IMAGE_OPTIONS_SLIDERKNOB3,
	&IMAGE_OPTIONS_SLIDERSLOT4,
	&IMAGE_DISCORD_BUTTON,
	&IMAGE_DISCORD_BUTTON_HOVER,
	&IMAGE_DISCORD_BUTTON_DOWN,
	&IMAGE_GIGA_HEAD,
	&IMAGE_GIGA_POLE_HEAD,
	&IMAGE_GIGA_PROGRESS_FLAG,
	&IMAGE_BOWLING_STRIPE_POOL,
	&IMAGE_BOWLING_STRIPE_ROOF,
	&IMAGE_BOWLING_STRIPE_ROOF_VERSUS,
	&IMAGE_PLANT_TROPHY,
	&IMAGE_PLANT_TROPHY_HIGH_RES,
	&IMAGE_ZOMBIE_TROPHY,
	&IMAGE_ZOMBIE_TROPHY_HIGH_RES,
	&IMAGE_VERSUS_BACKGROUND,
	&IMAGE_VERSUS_WINDOW,
	&IMAGE_VERSUS_WINDOW_HIGHLIGHT,
	&IMAGE_MINIGAME_3,
	&IMAGE_MULTIPLAYER_OPTION,
	&IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT,
	&IMAGE_GRAVESTONE_ROOF1,
	&IMAGE_GRAVESTONE_ROOF2,
	&IMAGE_GRAVESTONE_ROOF3,
	&IMAGE_GRAVESTONE_ROOF4,
	&IMAGE_GRAVESTONE_ROOF5,
	&IMAGE_GRAVESTONE_ROOF6,
	&IMAGE_GRAVESTONE_NIGHT_DIRT,
	&IMAGE_MAP_FLIPPED,
	&IMAGE_ZOMBIEPOLE,
	&IMAGE_STICK,
	&IMAGE_GAME_OVER_FLIPPED,
	&IMAGE_REANIM_BUSH_PARTICLE1,
	&IMAGE_REANIM_BUSH_PARTICLE2,
	&IMAGE_REANIM_BUSH_PARTICLE3,
	&IMAGE_REANIM_BUSH_PARTICLE4,
	&IMAGE_ZOMBIE_BUSHES,
	&IMAGE_YOUTUBE_BUTTON,
	&IMAGE_YOUTUBE_BUTTON_HOVER,
	&IMAGE_STONEBUTTON_RIGHT,
	&IMAGE_STONEBUTTON_RIGHT_HOVER,
	&IMAGE_RHYTHM_NUMBERGRID,
	&IMAGE_STONEBUTTON_LEFT,
	&IMAGE_STONEBUTTON_LEFT_HOVER,
	&IMAGE_REANIM_WALLNUT_BODY,
	&IMAGE_REANIM_WALLNUT_CRACKED1,
	&IMAGE_REANIM_WALLNUT_CRACKED2,
	&IMAGE_REANIM_TALLNUT_CRACKED1,
	&IMAGE_REANIM_TALLNUT_CRACKED2,
	&IMAGE_REANIM_DUMMY_CRACKED1,
	&IMAGE_REANIM_DUMMY_CRACKED2,
	&IMAGE_REANIM_PUMPKIN_DAMAGE1,
	&IMAGE_REANIM_PUMPKIN_DAMAGE3,
	&IMAGE_REANIM_FIRESHROOM_CRACKED1,
	&IMAGE_REANIM_FIRESHROOM_CRACKED2,
	&IMAGE_REANIM_FIRESHROOM_BODY2,
	&IMAGE_REANIM_ZOMBIE_CONE1,
	&IMAGE_REANIM_ZOMBIE_CONE2,
	&IMAGE_REANIM_ZOMBIE_CONE3,
	&IMAGE_REANIM_ZOMBIE_BUCKET1,
	&IMAGE_REANIM_ZOMBIE_BUCKET2,
	&IMAGE_REANIM_ZOMBIE_BUCKET3,
	&IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT,
	&IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2,
	&IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3,
	&IMAGE_REANIM_ZOMBIE_SCREENDOOR1,
	&IMAGE_REANIM_ZOMBIE_SCREENDOOR2,
	&IMAGE_REANIM_ZOMBIE_SCREENDOOR3,
	&IMAGE_REANIM_ZOMBIE_TRASHCAN1,
	&IMAGE_REANIM_ZOMBIE_TRASHCAN2,
	&IMAGE_REANIM_ZOMBIE_TRASHCAN3,
	&IMAGE_REANIM_ZOMBIE_FLAG1,
	&IMAGE_REANIM_ZOMBIE_FLAG3,
	&IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND,
	&IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET1,
	&IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET2,
	&IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET3,
	&IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HAND,
	&IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER,
	&IMAGE_REANIM_ZOMBIE_PAPER_PAPER2,
	&IMAGE_REANIM_ZOMBIE_PAPER_PAPER3,
	&IMAGE_REANIM_ZOMBIE_FISHER_HAT,
	&IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT,
	&IMAGE_REANIM_ZOMBIE_ICE2,
	&IMAGE_REANIM_ZOMBIE_ICE3,
	&IMAGE_REANIM_COIN_SILVER_DOLLAR,
	&IMAGE_REANIM_COIN_GOLD_DOLLAR,
	&IMAGE_REANIM_DIAMOND,
	&IMAGE_REANIM_COINGLOW,
	&IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_DANCER_INNERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE,
	&IMAGE_REANIM_ZOMBIE_IMP_ARM2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_2,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_3,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE,
	&IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET1,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET2,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET3,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET_RED,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_AXE2,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_HAND_REDEYE,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD_REDEYE,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2_REDEYE,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER_REDEYE,
	&IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2_REDEYE,
	&IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1,
	&IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2,
	&IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2,
	&IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_JACKBOX_BOX,
	&IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2,
	&IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL,
	&IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE,
	&IMAGE_REANIM_ZOMBIE_LADDER_1,
	&IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_LADDER_5,
	&IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL,
	&IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1,
	&IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2,
	&IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE,
	&IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE,
	&IMAGE_REANIM_CABBAGEPULT_CABBAGE,
	&IMAGE_REANIM_CORNPULT_KERNAL,
	&IMAGE_REANIM_CORNPULT_BUTTER,
	&IMAGE_REANIM_CORNPULT_BUTTER_SPLAT,
	&IMAGE_REANIM_MELONPULT_MELON,
	&IMAGE_REANIM_WINTERMELON_PROJECTILE,
	&IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE,
	&IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3,
	&IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4,
	&IMAGE_REANIM_GARLIC_BODY2,
	&IMAGE_REANIM_GARLIC_BODY3,
	&IMAGE_REANIM_COBCANNON_COB,
	&IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND,
	&IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD,
	&IMAGE_REANIM_ZOMBIE_SCARE_HEAD,
	&IMAGE_REANIM_ZOMBIE_SCARE_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_VAMPIRE_OUTERARM_UPPER2,
	&IMAGE_REANIM_ZOMBIE_FISHERMAN_OUTERARM_UPPER,
	&IMAGE_REANIM_ZOMBIE_LEAFBLOWER_OUTERARM_UPPER,
	&IMAGE_REANIM_ZOMBIE_AXE_OUTERARM_UPPER,
	&IMAGE_REANIM_ZOMBIE_AXE_HAT,
	&IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON,
	&IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT,
	&IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS,
	&IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3,
	&IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS,
	&IMAGE_REANIM_SELECTORSCREEN_BG,
	&IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW,
	&IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW,
	&IMAGE_REANIM_TREE_BG,
	&IMAGE_REANIM_POT_TOP_DARK,
	&IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE,
	&IMAGE_REANIM_STINKY_TURN3,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH1,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH4,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH5,
	&IMAGE_REANIM_CRAZYDAVE_MOUTH6,
	&IMAGE_REANIM_ZOMBIE_MUSTACHE2,
	&IMAGE_REANIM_ZOMBIE_MUSTACHE3,
	&IMAGE_REANIM_ZOMBIE_HEAD_GIGA,
	&IMAGE_REANIM_ZOMBIE_BUCKET1_GIGA,
	&IMAGE_REANIM_ZOMBIE_BUCKET2_GIGA,
	&IMAGE_REANIM_ZOMBIE_BUCKET3_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER1_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER2_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER3_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER4_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER5_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER6_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER7_GIGA,
	&IMAGE_REANIM_ZOMBIE_POLEVAULTER8_GIGA,
	&SOUND_AWOOGA,
	&SOUND_BLEEP,
	&SOUND_BUZZER,
	&SOUND_CHOMP,
	&SOUND_CHOMP2,
	&SOUND_CHOMPSOFT,
	&SOUND_EVILLAUGH,
	&SOUND_FLOOP,
	&SOUND_FROZEN,
	&SOUND_GULP,
	&SOUND_GROAN,
	&SOUND_GROAN2,
	&SOUND_GROAN3,
	&SOUND_GROAN4,
	&SOUND_GROAN5,
	&SOUND_GROAN6,
	&SOUND_LOSEMUSIC,
	&SOUND_MINDCONTROLLED,
	&SOUND_PAUSE,
	&SOUND_PLANT,
	&SOUND_PLANT2,
	&SOUND_POINTS,
	&SOUND_SEEDLIFT,
	&SOUND_SIREN,
	&SOUND_SLURP,
	&SOUND_SPLAT,
	&SOUND_SPLAT2,
	&SOUND_SPLAT3,
	&SOUND_SUKHBIR,
	&SOUND_SUKHBIR2,
	&SOUND_SUKHBIR3,
	&SOUND_SUKHBIR4,
	&SOUND_SUKHBIR5,
	&SOUND_SUKHBIR6,
	&SOUND_TAP,
	&SOUND_TAP2,
	&SOUND_THROW,
	&SOUND_THROW2,
	&SOUND_BLOVER,
	&SOUND_WINMUSIC,
	&SOUND_LAWNMOWER,
	&SOUND_BOING,
	&SOUND_JACKINTHEBOX,
	&SOUND_DIAMOND,
	&SOUND_DOLPHIN_APPEARS,
	&SOUND_DOLPHIN_BEFORE_JUMPING,
	&SOUND_POTATO_MINE,
	&SOUND_ZAMBONI,
	&SOUND_BALLOON_POP,
	&SOUND_THUNDER,
	&SOUND_ZOMBIESPLASH,
	&SOUND_BOWLING,
	&SOUND_BOWLINGIMPACT,
	&SOUND_BOWLINGIMPACT2,
	&SOUND_GRAVEBUSTERCHOMP,
	&SOUND_GRAVEBUTTON,
	&SOUND_LIMBS_POP,
	&SOUND_PLANTERN,
	&SOUND_POGO_ZOMBIE,
	&SOUND_SNOW_PEA_SPARKLES,
	&SOUND_PLANT_WATER,
	&SOUND_ZOMBIE_ENTERING_WATER,
	&SOUND_ZOMBIE_FALLING_1,
	&SOUND_ZOMBIE_FALLING_2,
	&SOUND_BUSH_RUSTLING1,
	&SOUND_BUSH_RUSTLING2,
	&SOUND_BUSH_RUSTLING3,
	&SOUND_HUNTER_SHOOT,
	&SOUND_SKELETON_DIE,
	&SOUND_SKELETON_REVIVE,
	&SOUND_BUSH_DESTROYED1,
	&SOUND_BUSH_DESTROYED2,
	&SOUND_BUSH_DESTROYED3,
	&SOUND_PUFF,
	&SOUND_FUME,
	&SOUND_HUGE_WAVE,
	&SOUND_SLOT_MACHINE,
	&SOUND_COIN,
	&SOUND_ROLL_IN,
	&SOUND_DIGGER_ZOMBIE,
	&SOUND_HATCHBACK_CLOSE,
	&SOUND_HATCHBACK_OPEN,
	&SOUND_KERNELPULT,
	&SOUND_KERNELPULT2,
	&SOUND_ZOMBAQUARIUM_DIE,
	&SOUND_BUNGEE_SCREAM,
	&SOUND_BUNGEE_SCREAM2,
	&SOUND_BUNGEE_SCREAM3,
	&SOUND_BUTTER,
	&SOUND_JACK_SURPRISE,
	&SOUND_JACK_SURPRISE2,
	&SOUND_NEWSPAPER_RARRGH,
	&SOUND_NEWSPAPER_RARRGH2,
	&SOUND_NEWSPAPER_RIP,
	&SOUND_SQUASH_HMM,
	&SOUND_SQUASH_HMM2,
	&SOUND_VASE_BREAKING,
	&SOUND_POOL_CLEANER,
	&SOUND_MAGNETSHROOM,
	&SOUND_LADDER_ZOMBIE,
	&SOUND_GARGANTUAR_THUMP,
	&SOUND_BASKETBALL,
	&SOUND_FIREPEA,
	&SOUND_IGNITE,
	&SOUND_IGNITE2,
	&SOUND_READYSETPLANT,
	&SOUND_DOOMSHROOM,
	&SOUND_EXPLOSION,
	&SOUND_FINALWAVE,
	&SOUND_REVERSE_EXPLOSION,
	&SOUND_RVTHROW,
	&SOUND_SHIELDHIT,
	&SOUND_SHIELDHIT2,
	&SOUND_BOSSEXPLOSION,
	&SOUND_CHERRYBOMB,
	&SOUND_BONK,
	&SOUND_SWING,
	&SOUND_RAIN,
	&SOUND_LIGHTFILL,
	&SOUND_PLASTICHIT,
	&SOUND_PLASTICHIT2,
	&SOUND_JALAPENO,
	&SOUND_BALLOONINFLATE,
	&SOUND_BIGCHOMP,
	&SOUND_MELONIMPACT,
	&SOUND_MELONIMPACT2,
	&SOUND_PLANTGROW,
	&SOUND_SHOOP,
	&SOUND_TAPGLASS,
	&SOUND_JUICY,
	&SOUND_COFFEE,
	&SOUND_WAKEUP,
	&SOUND_WAKEUP_REVERSE,
	&SOUND_LOWGROAN,
	&SOUND_LOWGROAN2,
	&SOUND_PRIZE,
	&SOUND_YUCK,
	&SOUND_YUCK2,
	&SOUND_GRASSSTEP,
	&SOUND_SHOVEL,
	&SOUND_COBLAUNCH,
	&SOUND_WATERING,
	&SOUND_POLEVAULT,
	&SOUND_GRAVESTONE_RUMBLE,
	&SOUND_DIRT_RISE,
	&SOUND_FERTILIZER,
	&SOUND_PORTAL,
	&SOUND_BUGSPRAY,
	&SOUND_SCREAM,
	&SOUND_PAPER,
	&SOUND_MONEYFALLS,
	&SOUND_IMP,
	&SOUND_IMP2,
	&SOUND_HYDRAULIC_SHORT,
	&SOUND_HYDRAULIC,
	&SOUND_GARGANTUDEATH,
	&SOUND_CERAMIC,
	&SOUND_BOSSBOULDERATTACK,
	&SOUND_CHIME,
	&SOUND_CRAZYDAVESHORT1,
	&SOUND_CRAZYDAVESHORT2,
	&SOUND_CRAZYDAVESHORT3,
	&SOUND_CRAZYDAVELONG1,
	&SOUND_CRAZYDAVELONG2,
	&SOUND_CRAZYDAVELONG3,
	&SOUND_CRAZYDAVEEXTRALONG1,
	&SOUND_CRAZYDAVEEXTRALONG2,
	&SOUND_CRAZYDAVEEXTRALONG3,
	&SOUND_CRAZYDAVECRAZY,
	&SOUND_BRAVEDAVE1,
	&SOUND_BRAVEDAVE2,
	&SOUND_BRAVEDAVE3,
	&SOUND_BRAVEDAVE4,
	&SOUND_BRAVEDAVE5,
	&SOUND_BRAVEDAVE6,
	&SOUND_BEE1,
	&SOUND_BEE2,
	&SOUND_BONK1,
	&SOUND_BONK2,
	&SOUND_VIOLET,
	&SOUND_RELOAD,
	&SOUND_CRASH,
	&SOUND_BELL,
	&SOUND_SHOOTINGSTAR,
	&SOUND_LOG_PLACE,
	&SOUND_WOODCHIPPER,
	&SOUND_PHONOGRAPH,
	&SOUND_DANCER,
	&SOUND_FINALFANFARE,
	&SOUND_CRAZYDAVESCREAM,
	&SOUND_CRAZYDAVESCREAM2,
	&SOUND_CHILLY_FREEZE,
	&SOUND_ELECTRIC,
	&SOUND_ELECTRIC2,
	&SOUND_ELECTRIC3,
	&SOUND_ICE,
	&SOUND_GLADIANTUAR_DEATH,
	&SOUND_BLOOD_MOON,
	&SOUND_CROW,
	&SOUND_CROW_DEATH,
	&SOUND_BREAK,
	&IMAGE_BACKGROUND1,
	&IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND1_GAMEOVER_MASK,
	&IMAGE_BACKGROUND1UNSODDED,
	&IMAGE_SOD1ROW,
	&IMAGE_SOD3ROW,
	&IMAGE_BACKGROUND2,
	&IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND2_GAMEOVER_MASK,
	&IMAGE_BACKGROUND3,
	&IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND3_GAMEOVER_MASK,
	&IMAGE_BACKGROUND4,
	&IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY,
	&IMAGE_BACKGROUND4_GAMEOVER_MASK,
	&IMAGE_FOG,
	&IMAGE_FOG_SOFTWARE,
	&IMAGE_BACKGROUND5,
	&IMAGE_BACKGROUND5_GAMEOVER_MASK,
	&IMAGE_BACKGROUND6BOSS,
	&IMAGE_BACKGROUND6_GAMEOVER_MASK,
	&IMAGE_BACKGROUND_MUSHROOMGARDEN,
	&IMAGE_BACKGROUND_GREENHOUSE,
	&IMAGE_BACKGROUND_GREENHOUSE_OVERLAY,
	&IMAGE_AQUARIUM1,
	&IMAGE_WAVECENTER,
	&IMAGE_WAVESIDE,
	&IMAGE_AWARDSCREEN_BACK,
	&IMAGE_CHALLENGE_BACKGROUND,
	&IMAGE_CHALLENGE_WINDOW,
	&IMAGE_CHALLENGE_WINDOW_HIGHLIGHT,
	&IMAGE_CHALLENGE_BLANK,
	&IMAGE_CHALLENGE_THUMBNAILS,
	&IMAGE_SURVIVAL_THUMBNAILS,
	&IMAGE_LOCK,
	&IMAGE_LOCK_OPEN,
	&IMAGE_ALMANAC_INDEXBACK,
	&IMAGE_ALMANAC_PLANTBACK,
	&IMAGE_ALMANAC_ZOMBIEBACK,
	&IMAGE_ALMANAC_PLANTCARD,
	&IMAGE_ALMANAC_ZOMBIECARD,
	&IMAGE_ALMANAC_ZOMBIEWINDOW,
	&IMAGE_ALMANAC_ZOMBIEWINDOW2,
	&IMAGE_ALMANAC_ZOMBIEBLANK,
	&IMAGE_ALMANAC_GROUNDDAY,
	&IMAGE_ALMANAC_GROUNDNIGHT,
	&IMAGE_ALMANAC_GROUNDPOOL,
	&IMAGE_ALMANAC_GROUNDNIGHTPOOL,
	&IMAGE_ALMANAC_GROUNDROOF,
	&IMAGE_ALMANAC_GROUNDICE,
	&IMAGE_ALMANAC_GROUNDFOREST,
	&IMAGE_ALMANAC_CLOSEBUTTON,
	&IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT,
	&IMAGE_ALMANAC_INDEXBUTTON,
	&IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT,
	&IMAGE_STORE_BACKGROUND,
	&IMAGE_STORE_BACKGROUNDNIGHT,
	&IMAGE_STORE_CAR,
	&IMAGE_STORE_CAR_NIGHT,
	&IMAGE_STORE_CARCLOSED,
	&IMAGE_STORE_CARCLOSED_NIGHT,
	&IMAGE_STORE_HATCHBACKOPEN,
	&IMAGE_STORE_SIGN,
	&IMAGE_STORE_MAINMENUBUTTON,
	&IMAGE_STORE_MAINMENUBUTTONDOWN,
	&IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT,
	&IMAGE_STORE_NEXTBUTTON,
	&IMAGE_STORE_NEXTBUTTONHIGHLIGHT,
	&IMAGE_STORE_NEXTBUTTONDISABLED,
	&IMAGE_STORE_PREVBUTTON,
	&IMAGE_STORE_PREVBUTTONHIGHLIGHT,
	&IMAGE_STORE_PREVBUTTONDISABLED,
	&IMAGE_STORE_PRICETAG,
	&IMAGE_STORE_PACKETUPGRADE,
	&IMAGE_STORE_MUSHROOMGARDENICON,
	&IMAGE_STORE_AQUARIUMGARDENICON,
	&IMAGE_STORE_TREEOFWISDOMICON,
	&IMAGE_STORE_FIRSTAIDWALLNUTICON,
	&IMAGE_STORE_PVZICON,
	&IMAGE_ZOMBIE_NOTE,
	&IMAGE_ZOMBIE_NOTE1,
	&IMAGE_ZOMBIE_NOTE2,
	&IMAGE_ZOMBIE_NOTE3,
	&IMAGE_ZOMBIE_NOTE4,
	&IMAGE_ZOMBIE_NOTE5,
	&IMAGE_ZOMBIE_NOTE6,
	&IMAGE_ZOMBIE_FINAL_NOTE,
	&IMAGE_ZOMBIE_NOTE_HELP,
	&FONT_BRIANNETOD32,
	&FONT_BRIANNETOD32BLACK,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING1,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING2,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING3,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING4,
	&IMAGE_REANIM_SUNFLOWER_HEAD_SING5,
	&IMAGE_REANIM_SUNFLOWER_HEAD_WINK,
	&IMAGE_REANIM_CREDITS_DISCOLIGHTS,
	&IMAGE_REANIM_CREDITS_FOGMACHINE,
	&IMAGE_CREDITS_ZOMBIENOTE,
	&IMAGE_CREDITS_PLAYBUTTON,
	NULL
};

Image* Sexy::LoadImageById(ResourceManager *theManager, int theId)
{
	return (*((Image**)gResources[theId]) = theManager->LoadImage(GetStringIdById(theId)));
}

void Sexy::ReplaceImageById(ResourceManager *theManager, int theId, Image *theImage)
{
	theManager->ReplaceImage(GetStringIdById(theId),theImage);
	*(Image**)gResources[theId] = theImage;
}

Image* Sexy::GetImageById(int theId)
{
	return *(Image**)gResources[theId];
}

Font* Sexy::GetFontById(int theId)
{
	return *(Font**)gResources[theId];
}

int Sexy::GetSoundById(int theId)
{
	return *(int*)gResources[theId];
}

Image*& Sexy::GetImageRefById(int theId)
{
	return *(Image**)gResources[theId];
}

Font*& Sexy::GetFontRefById(int theId)
{
	return *(Font**)gResources[theId];
}

int& Sexy::GetSoundRefById(int theId)
{
	return *(int*)gResources[theId];
}

static Sexy::ResourceId GetIdByVariable(const void *theVariable)
{
	typedef std::map<int,int> MyMap;
	static MyMap aMap;
	if(gNeedRecalcVariableToIdMap)
	{
		gNeedRecalcVariableToIdMap = false;
		aMap.clear();
		for(int i=0; i<RESOURCE_ID_MAX; i++)
			aMap[*(int*)gResources[i]] = i;
	}

	MyMap::iterator anItr = aMap.find((int)theVariable);
	if (anItr == aMap.end())
		return RESOURCE_ID_MAX;
	else
		return (ResourceId) anItr->second;
}

Sexy::ResourceId Sexy::GetIdByImage(Image *theImage)
{
	return GetIdByVariable(theImage);
}

Sexy::ResourceId Sexy::GetIdByFont(Font *theFont)
{
	return GetIdByVariable(theFont);
}

Sexy::ResourceId Sexy::GetIdBySound(int theSound)
{
	return GetIdByVariable((void*)theSound);
}

const char* Sexy::GetStringIdById(int theId)
{
	switch(theId)
	{
		case IMAGE_BLANK_ID: return "IMAGE_BLANK";
		case IMAGE_POPCAP_LOGO_ID: return "IMAGE_POPCAP_LOGO";
		case IMAGE_PARTNER_LOGO_ID: return "IMAGE_PARTNER_LOGO";
		case IMAGE_TITLESCREEN_ID: return "IMAGE_TITLESCREEN";
		case IMAGE_LOADBAR_DIRT_ID: return "IMAGE_LOADBAR_DIRT";
		case IMAGE_LOADBAR_GRASS_ID: return "IMAGE_LOADBAR_GRASS";
		case IMAGE_PVZ_LOGO_ID: return "IMAGE_PVZ_LOGO";
		case IMAGE_REANIM_SODROLLCAP_ID: return "IMAGE_REANIM_SODROLLCAP";
		case FONT_BRIANNETOD16_ID: return "FONT_BRIANNETOD16";
		case SOUND_BUTTONCLICK_ID: return "SOUND_BUTTONCLICK";
		case SOUND_LOADINGBAR_FLOWER_ID: return "SOUND_LOADINGBAR_FLOWER";
		case SOUND_LOADINGBAR_ZOMBIE_ID: return "SOUND_LOADINGBAR_ZOMBIE";
		case FONT_IMAGE_HOUSEOFTERROR28_ID: return "FONT_IMAGE_HOUSEOFTERROR28";
		case FONT_HOUSEOFTERROR28_ID: return "FONT_HOUSEOFTERROR28";
		case FONT_HOUSEOFTERROR20_ID: return "FONT_HOUSEOFTERROR20";
		case FONT_HOUSEOFTERROR16_ID: return "FONT_HOUSEOFTERROR16";
		case FONT_LUCKFIXHOUSEOFTERROR15_ID: return "FONT_LUCKFIXHOUSEOFTERROR15";
		case FONT_TINYBOLD_ID: return "FONT_TINYBOLD";
		case FONT_CONTINUUMBOLD14_ID: return "FONT_CONTINUUMBOLD14";
		case FONT_CONTINUUMBOLD14OUTLINE_ID: return "FONT_CONTINUUMBOLD14OUTLINE";
		case FONT_DWARVENTODCRAFT12_ID: return "FONT_DWARVENTODCRAFT12";
		case FONT_DWARVENTODCRAFT15_ID: return "FONT_DWARVENTODCRAFT15";
		case FONT_DWARVENTODCRAFT18_ID: return "FONT_DWARVENTODCRAFT18";
		case FONT_DWARVENTODCRAFT18BRIGHTGREENINSET_ID: return "FONT_DWARVENTODCRAFT18BRIGHTGREENINSET";
		case FONT_DWARVENTODCRAFT18GREENINSET_ID: return "FONT_DWARVENTODCRAFT18GREENINSET";
		case FONT_DWARVENTODCRAFT18YELLOW_ID: return "FONT_DWARVENTODCRAFT18YELLOW";
		case FONT_DWARVENTODCRAFT24_ID: return "FONT_DWARVENTODCRAFT24";
		case FONT_DWARVENTODCRAFT36BRIGHTGREENINSET_ID: return "FONT_DWARVENTODCRAFT36BRIGHTGREENINSET";
		case FONT_DWARVENTODCRAFT36GREENINSET_ID: return "FONT_DWARVENTODCRAFT36GREENINSET";
		case FONT_PICO129_ID: return "FONT_PICO129";
		case FONT_BRIANNETOD12_ID: return "FONT_BRIANNETOD12";
		//case FONT_BRIANNETOD9_ID: return "FONT_BRIANNETOD9";
		case FONT_PIX118BOLD_ID: return "FONT_PIX118BOLD";
		case IMAGE_EDITBOX_ID: return "IMAGE_EDITBOX";
		case IMAGE_DIALOG_TOPLEFT_ID: return "IMAGE_DIALOG_TOPLEFT";
		case IMAGE_DIALOG_TOPMIDDLE_ID: return "IMAGE_DIALOG_TOPMIDDLE";
		case IMAGE_DIALOG_TOPRIGHT_ID: return "IMAGE_DIALOG_TOPRIGHT";
		case IMAGE_DIALOG_CENTERLEFT_ID: return "IMAGE_DIALOG_CENTERLEFT";
		case IMAGE_DIALOG_CENTERMIDDLE_ID: return "IMAGE_DIALOG_CENTERMIDDLE";
		case IMAGE_DIALOG_CENTERRIGHT_ID: return "IMAGE_DIALOG_CENTERRIGHT";
		case IMAGE_DIALOG_BOTTOMLEFT_ID: return "IMAGE_DIALOG_BOTTOMLEFT";
		case IMAGE_DIALOG_BOTTOMMIDDLE_ID: return "IMAGE_DIALOG_BOTTOMMIDDLE";
		case IMAGE_DIALOG_BOTTOMRIGHT_ID: return "IMAGE_DIALOG_BOTTOMRIGHT";
		case IMAGE_DIALOG_BIGBOTTOMLEFT_ID: return "IMAGE_DIALOG_BIGBOTTOMLEFT";
		case IMAGE_DIALOG_BIGBOTTOMMIDDLE_ID: return "IMAGE_DIALOG_BIGBOTTOMMIDDLE";
		case IMAGE_DIALOG_BIGBOTTOMRIGHT_ID: return "IMAGE_DIALOG_BIGBOTTOMRIGHT";
		case IMAGE_DIALOG_HEADER_ID: return "IMAGE_DIALOG_HEADER";
		case IMAGE_BUTTON_LEFT_ID: return "IMAGE_BUTTON_LEFT";
		case IMAGE_BUTTON_MIDDLE_ID: return "IMAGE_BUTTON_MIDDLE";
		case IMAGE_BUTTON_RIGHT_ID: return "IMAGE_BUTTON_RIGHT";
		case IMAGE_BUTTON_DOWN_LEFT_ID: return "IMAGE_BUTTON_DOWN_LEFT";
		case IMAGE_BUTTON_DOWN_MIDDLE_ID: return "IMAGE_BUTTON_DOWN_MIDDLE";
		case IMAGE_BUTTON_DOWN_RIGHT_ID: return "IMAGE_BUTTON_DOWN_RIGHT";
		case IMAGE_ALMANAC_SHIRT_ID: return "IMAGE_ALMANAC_ZOMBIEBACK1";
		case IMAGE_ALMANAC_GOLDEN_LOCK_ID: return "IMAGE_ALMANAC_ZOMBIEBACK2";
		case IMAGE_SEEDCHOOSER_BACKGROUND_ID: return "IMAGE_SEEDCHOOSER_BACKGROUND";
		case IMAGE_SEEDCHOOSER_BACKGROUND_ZOMBIES_ID: return "IMAGE_SEEDCHOOSER_BACKGROUND_ZOMBIES";
		case IMAGE_SEEDCHOOSER_BUTTON_ID: return "IMAGE_SEEDCHOOSER_BUTTON";
		case IMAGE_SEEDCHOOSER_BUTTON_DISABLED_ID: return "IMAGE_SEEDCHOOSER_BUTTON_DISABLED";
		case IMAGE_SEEDCHOOSER_BUTTON_GLOW_ID: return "IMAGE_SEEDCHOOSER_BUTTON_GLOW";
		case IMAGE_SEEDCHOOSER_BUTTON2_ID: return "IMAGE_SEEDCHOOSER_BUTTON2";
		case IMAGE_SEEDCHOOSER_BUTTON2_GLOW_ID: return "IMAGE_SEEDCHOOSER_BUTTON2_GLOW";
		case IMAGE_SEEDCHOOSER_IMITATERADDON_ID: return "IMAGE_SEEDCHOOSER_IMITATERADDON";
		case IMAGE_SEEDS_ID: return "IMAGE_SEEDS";
		case IMAGE_SEEDPACKET_LARGER_ID: return "IMAGE_SEEDPACKET_LARGER";
		case IMAGE_SEEDPACKETSILHOUETTE_ID: return "IMAGE_SEEDPACKETSILHOUETTE";
		case IMAGE_FLAGMETER_ID: return "IMAGE_FLAGMETER";
		case IMAGE_FLAGMETERLEVELPROGRESS_ID: return "IMAGE_FLAGMETERLEVELPROGRESS";
		case IMAGE_FLAGMETERPARTS_ID: return "IMAGE_FLAGMETERPARTS";
		case IMAGE_FLAGMETERPARTS_HARDMODE_ID: return "IMAGE_FLAGMETERPARTS_HARDMODE";
		case IMAGE_TROPHY_ID: return "IMAGE_TROPHY";
		case IMAGE_DIAMOND_TROPHY_ID: return "IMAGE_DIAMOND_TROPHY";
		case IMAGE_TROPHY_HI_RES_ID: return "IMAGE_TROPHY_HI_RES";
		case IMAGE_DIAMOND_TROPHY_HI_RES_ID: return "IMAGE_DIAMOND_TROPHY_HI_RES";
		case IMAGE_MINIGAME_TROPHY_ID: return "IMAGE_MINIGAME_TROPHY";
		case IMAGE_ZOMBIE_NOTE_SMALL_ID: return "IMAGE_ZOMBIE_NOTE_SMALL";
		case IMAGE_TACO_ID: return "IMAGE_TACO";
		case IMAGE_CARKEYS_ID: return "IMAGE_CARKEYS";
		case IMAGE_ALMANAC_ID: return "IMAGE_ALMANAC";
		case IMAGE_ICON_POOLCLEANER_ID: return "IMAGE_ICON_POOLCLEANER";
		case IMAGE_ICON_ROOFCLEANER_ID: return "IMAGE_ICON_ROOFCLEANER";
		case IMAGE_ICON_RAKE_ID: return "IMAGE_ICON_RAKE";
		case IMAGE_BRAIN_ID: return "IMAGE_BRAIN";
		case IMAGE_MONEYBAG_ID: return "IMAGE_MONEYBAG";
		case IMAGE_MONEYBAG_HI_RES_ID: return "IMAGE_MONEYBAG_HI_RES";
		case IMAGE_CHOCOLATE_ID: return "IMAGE_CHOCOLATE";
		case IMAGE_OPTIONS_BACKTOGAMEBUTTON0_ID: return "IMAGE_OPTIONS_BACKTOGAMEBUTTON0";
		case IMAGE_OPTIONS_BACKTOGAMEBUTTON2_ID: return "IMAGE_OPTIONS_BACKTOGAMEBUTTON2";
		case IMAGE_OPTIONS_CHECKBOX0_ID: return "IMAGE_OPTIONS_CHECKBOX0";
		case IMAGE_OPTIONS_CHECKBOX1_ID: return "IMAGE_OPTIONS_CHECKBOX1";
		case IMAGE_OPTIONS_MENUBACK_ID: return "IMAGE_OPTIONS_MENUBACK";
		case IMAGE_OPTIONS_SLIDERKNOB2_ID: return "IMAGE_OPTIONS_SLIDERKNOB2";
		case IMAGE_OPTIONS_SLIDERSLOT_ID: return "IMAGE_OPTIONS_SLIDERSLOT";
		case IMAGE_SELECTORSCREEN_HELP1_ID: return "IMAGE_SELECTORSCREEN_HELP1";
		case IMAGE_SELECTORSCREEN_HELP2_ID: return "IMAGE_SELECTORSCREEN_HELP2";
		case IMAGE_SELECTORSCREEN_OPTIONS1_ID: return "IMAGE_SELECTORSCREEN_OPTIONS1";
		case IMAGE_SELECTORSCREEN_OPTIONS2_ID: return "IMAGE_SELECTORSCREEN_OPTIONS2";
		case IMAGE_SELECTORSCREEN_QUIT1_ID: return "IMAGE_SELECTORSCREEN_QUIT1";
		case IMAGE_SELECTORSCREEN_QUIT2_ID: return "IMAGE_SELECTORSCREEN_QUIT2";
		case IMAGE_SELECTORSCREEN_ALMANAC_ID: return "IMAGE_SELECTORSCREEN_ALMANAC";
		case IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT_ID: return "IMAGE_SELECTORSCREEN_ALMANACHIGHLIGHT";
		case IMAGE_SELECTORSCREEN_STORE_ID: return "IMAGE_SELECTORSCREEN_STORE";
		case IMAGE_SELECTORSCREEN_STOREHIGHLIGHT_ID: return "IMAGE_SELECTORSCREEN_STOREHIGHLIGHT";
		case IMAGE_SELECTORSCREEN_LEVELNUMBERS_ID: return "IMAGE_SELECTORSCREEN_LEVELNUMBERS";
		case IMAGE_SELECTORSCREEN_ZENGARDEN_ID: return "IMAGE_SELECTORSCREEN_ZENGARDEN";
		case IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT_ID: return "IMAGE_SELECTORSCREEN_ZENGARDENHIGHLIGHT";
		case IMAGE_STORE_SPEECHBUBBLE_ID: return "IMAGE_STORE_SPEECHBUBBLE";
		case IMAGE_STORE_SPEECHBUBBLE2_ID: return "IMAGE_STORE_SPEECHBUBBLE2";
		case IMAGE_SHOVEL_ID: return "IMAGE_SHOVEL";
		case IMAGE_SHOVEL_HI_RES_ID: return "IMAGE_SHOVEL_HI_RES";
		case IMAGE_TOMBSTONES_ID: return "IMAGE_TOMBSTONES";
		case IMAGE_TOMBSTONE_MOUNDS_ID: return "IMAGE_TOMBSTONE_MOUNDS";
		case IMAGE_NIGHT_GRAVE_GRAPHIC_ID: return "IMAGE_NIGHT_GRAVE_GRAPHIC";
		case IMAGE_CRATER_ID: return "IMAGE_CRATER";
		case IMAGE_CRATER_FADING_ID: return "IMAGE_CRATER_FADING";
		case IMAGE_CRATER_ROOF_CENTER_ID: return "IMAGE_CRATER_ROOF_CENTER";
		case IMAGE_CRATER_ROOF_LEFT_ID: return "IMAGE_CRATER_ROOF_LEFT";
		case IMAGE_CRATER_WATER_DAY_ID: return "IMAGE_CRATER_WATER_DAY";
		case IMAGE_CRATER_WATER_NIGHT_ID: return "IMAGE_CRATER_WATER_NIGHT";
		case IMAGE_COBCANNON_TARGET_ID: return "IMAGE_COBCANNON_TARGET";
		case IMAGE_COBCANNON_POPCORN_ID: return "IMAGE_COBCANNON_POPCORN";
		case IMAGE_FERTILIZER_ID: return "IMAGE_FERTILIZER";
		case IMAGE_WATERINGCAN_ID: return "IMAGE_WATERINGCAN";
		case IMAGE_WATERINGCANGOLD_ID: return "IMAGE_WATERINGCANGOLD";
		case IMAGE_PHONOGRAPH_ID: return "IMAGE_PHONOGRAPH";
		case IMAGE_BEGHOULED_TWIST_OVERLAY_ID: return "IMAGE_BEGHOULED_TWIST_OVERLAY";
		case IMAGE_ZEN_GOLDTOOLRETICLE_ID: return "IMAGE_ZEN_GOLDTOOLRETICLE";
		case IMAGE_ZEN_GARDENGLOVE_ID: return "IMAGE_ZEN_GARDENGLOVE";
		case IMAGE_ZEN_MONEYSIGN_ID: return "IMAGE_ZEN_MONEYSIGN";
		case IMAGE_ZEN_NEXTGARDEN_ID: return "IMAGE_ZEN_NEXTGARDEN";
		case IMAGE_ZEN_WHEELBARROW_ID: return "IMAGE_ZEN_WHEELBARROW";
		case IMAGE_ZENSHOPBUTTON_ID: return "IMAGE_ZENSHOPBUTTON";
		case IMAGE_ZENSHOPBUTTON_HIGHLIGHT_ID: return "IMAGE_ZENSHOPBUTTON_HIGHLIGHT";
		case IMAGE_PRESENT_ID: return "IMAGE_PRESENT";
		case IMAGE_PRESENTOPEN_ID: return "IMAGE_PRESENTOPEN";
		case IMAGE_SUNFLOWER_TROPHY_ID: return "IMAGE_SUNFLOWER_TROPHY";
		case IMAGE_DIAMOND_SUNFLOWER_TROPHY_ID: return "IMAGE_DIAMOND_SUNFLOWER_TROPHY";
		case IMAGE_SLOTMACHINE_OVERLAY_ID: return "IMAGE_SLOTMACHINE_OVERLAY";
		case IMAGE_SCARY_POT_ID: return "IMAGE_SCARY_POT";
		case IMAGE_BUG_SPRAY_ID: return "IMAGE_BUG_SPRAY";
		case IMAGE_PLANTSPEECHBUBBLE_ID: return "IMAGE_PLANTSPEECHBUBBLE";
		case IMAGE_WATERDROP_ID: return "IMAGE_WATERDROP";
		case IMAGE_TREEFOOD_ID: return "IMAGE_TREEFOOD";
		case IMAGE_PACKET_PLANTS_ID: return "IMAGE_PACKET_PLANTS";
		case IMAGE_ZEN_NEED_ICONS_ID: return "IMAGE_ZEN_NEED_ICONS";
		case IMAGE_PROJECTILEPEA_ID: return "IMAGE_PROJECTILEPEA";
		case IMAGE_PROJECTILESNOWPEA_ID: return "IMAGE_PROJECTILESNOWPEA";
		case IMAGE_PROJECTILECACTUS_ID: return "IMAGE_PROJECTILECACTUS";
		case IMAGE_DIRTSMALL_ID: return "IMAGE_DIRTSMALL";
		case IMAGE_DIRTBIG_ID: return "IMAGE_DIRTBIG";
		case IMAGE_ROCKSMALL_ID: return "IMAGE_ROCKSMALL";
		case IMAGE_WATERPARTICLE_ID: return "IMAGE_WATERPARTICLE";
		case IMAGE_WHITEWATER_ID: return "IMAGE_WHITEWATER";
		case IMAGE_WHITEWATER_SHADOW_ID: return "IMAGE_WHITEWATER_SHADOW";
		case IMAGE_MELONPULT_PARTICLES_ID: return "IMAGE_MELONPULT_PARTICLES";
		case IMAGE_WINTERMELON_PARTICLES_ID: return "IMAGE_WINTERMELON_PARTICLES";
		case IMAGE_PROJECTILE_STAR_ID: return "IMAGE_PROJECTILE_STAR";
		case IMAGE_SEEDBANK_ID: return "IMAGE_SEEDBANK";
		case IMAGE_CONVEYORBELT_BACKDROP_ID: return "IMAGE_CONVEYORBELT_BACKDROP";
		case IMAGE_CONVEYORBELT_ID: return "IMAGE_CONVEYORBELT";
		case IMAGE_SHOVELBANK_ID: return "IMAGE_SHOVELBANK";
		case IMAGE_SUNBANK_ID: return "IMAGE_SUNBANK";
		case IMAGE_COINBANK_ID: return "IMAGE_COINBANK";
		case IMAGE_POOL_ID: return "IMAGE_POOL";
		case IMAGE_POOL_NIGHT_ID: return "IMAGE_POOL_NIGHT";
		case IMAGE_POOL_BASE_ID: return "IMAGE_POOL_BASE";
		case IMAGE_POOL_BASE_NIGHT_ID: return "IMAGE_POOL_BASE_NIGHT";
		case IMAGE_POOL_SHADING_ID: return "IMAGE_POOL_SHADING";
		case IMAGE_POOL_SHADING_NIGHT_ID: return "IMAGE_POOL_SHADING_NIGHT";
		case IMAGE_POOL_CAUSTIC_EFFECT_ID: return "IMAGE_POOL_CAUSTIC_EFFECT";
		case IMAGE_PLANTSHADOW_ID: return "IMAGE_PLANTSHADOW";
		case IMAGE_PLANTSHADOW2_ID: return "IMAGE_PLANTSHADOW2";
		case IMAGE_PEA_SHADOWS_ID: return "IMAGE_PEA_SHADOWS";
		case IMAGE_WALLNUT_BOWLINGSTRIPE_ID: return "IMAGE_WALLNUT_BOWLINGSTRIPE";
		case IMAGE_FLOWER_STRIPE_ID: return "IMAGE_FLOWER_STRIPE";
		case IMAGE_ICE_ID: return "IMAGE_ICE";
		case IMAGE_ICE_CAP_ID: return "IMAGE_ICE_CAP";
		case IMAGE_ICE_SPARKLES_ID: return "IMAGE_ICE_SPARKLES";
		case IMAGE_IMITATERSEED_ID: return "IMAGE_IMITATERSEED";
		case IMAGE_ALMANAC_IMITATER_ID: return "IMAGE_ALMANAC_IMITATER";
		case IMAGE_IMITATERSEEDDISABLED_ID: return "IMAGE_IMITATERSEEDDISABLED";
		case IMAGE_ICETRAP_ID: return "IMAGE_ICETRAP";
		case IMAGE_ICETRAP2_ID: return "IMAGE_ICETRAP2";
		case IMAGE_ICETRAP_PARTICLES_ID: return "IMAGE_ICETRAP_PARTICLES";
		case IMAGE_ELECTRIC_ID: return "IMAGE_ELECTRIC";
		case IMAGE_FF1_ID: return "IMAGE_FF1";
		case IMAGE_FF2_ID: return "IMAGE_FF2";
		case IMAGE_BACKGROUND_BLOODMOON_ID: return "IMAGE_BACKGROUND_BLOODMOON";
		case IMAGE_NEW_LOGO_ID: return "IMAGE_NEW_LOGO";
		case IMAGE_PROJECTILEICEQUEEN_ID: return "IMAGE_PROJECTILEICEQUEEN";
		case IMAGE_PROJECTILE_SEASTAR_ID: return "IMAGE_PROJECTILE_SEASTAR";
		case IMAGE_LOCKED_ZOMBIE_ID: return "IMAGE_LOCKED_ZOMBIE";
		case IMAGE_NEW_SURVIVAL_THUMBNAIL_ID: return "IMAGE_NEW_SURVIVAL_THUMBNAIL";
		case IMAGE_ALMANAC_PLANTBACK_2_ID: return "IMAGE_ALMANAC_PLANTBACK_2";
		case IMAGE_BRAINBANK_ID: return "IMAGE_BRAINBANK";
		case IMAGE_BRAINBANK_SMALL_ID: return "IMAGE_BRAINBANK_SMALL";
		case IMAGE_STONE2_ID: return "IMAGE_STONE2";
		case IMAGE_STONE3_ID: return "IMAGE_STONE3";
		case IMAGE_STONE4_ID: return "IMAGE_STONE4";
		case IMAGE_STONE5_ID: return "IMAGE_STONE5";
		case IMAGE_ZOMBIE_PACK_ID: return "IMAGE_ZOMBIE_PACK";
		case IMAGE_S_FLAG1_ID: return "IMAGE_S_FLAG1";
		case IMAGE_S_FLAG2_ID: return "IMAGE_S_FLAG2";
		case IMAGE_Z_FLAG1_ID: return "IMAGE_Z_FLAG1";
		case IMAGE_Z_FLAG2_ID: return "IMAGE_Z_FLAG2";
		case IMAGE_D_FLAG1_ID: return "IMAGE_D_FLAG1";
		case IMAGE_D_FLAG2_ID: return "IMAGE_D_FLAG2";
		case IMAGE_R_FLAG1_ID: return "IMAGE_R_FLAG1";
		case IMAGE_R_FLAG2_ID: return "IMAGE_R_FLAG2";
		case IMAGE_M_FLAG1_ID: return "IMAGE_M_FLAG1";
		case IMAGE_M_FLAG2_ID: return "IMAGE_M_FLAG2";
		case IMAGE_F_FLAG1_ID: return "IMAGE_F_FLAG1";
		case IMAGE_F_FLAG2_ID: return "IMAGE_F_FLAG2";
		case IMAGE_C_FLAG1_ID: return "IMAGE_C_FLAG1";
		case IMAGE_C_FLAG2_ID: return "IMAGE_C_FLAG2";
		case IMAGE_E_FLAG1_ID: return "IMAGE_E_FLAG1";
		case IMAGE_E_FLAG2_ID: return "IMAGE_E_FLAG2";
		case IMAGE_MA_FLAG1_ID: return "IMAGE_MA_FLAG1";
		case IMAGE_MA_FLAG2_ID: return "IMAGE_MA_FLAG2";
		case IMAGE_DA_FLAG1_ID: return "IMAGE_DA_FLAG1";
		case IMAGE_DA_FLAG2_ID: return "IMAGE_DA_FLAG2";
		case IMAGE_IP_FLAG1_ID: return "IMAGE_IP_FLAG1";
		case IMAGE_IP_FLAG2_ID: return "IMAGE_IP_FLAG2";
		case IMAGE_SH_FLAG1_ID: return "IMAGE_SH_FLAG1";
		case IMAGE_SH_FLAG2_ID: return "IMAGE_SH_FLAG2";
		case IMAGE_PR_FLAG1_ID: return "IMAGE_PR_FLAG1";
		case IMAGE_PR_FLAG2_ID: return "IMAGE_PR_FLAG2";
		case IMAGE_HW_FLAG1_ID: return "IMAGE_HW_FLAG1";
		case IMAGE_HW_FLAG2_ID: return "IMAGE_HW_FLAG2";
		case IMAGE_YY_FLAG1_ID: return "IMAGE_YY_FLAG1";
		case IMAGE_YY_FLAG2_ID: return "IMAGE_YY_FLAG2";
		case IMAGE_KF_FLAG1_ID: return "IMAGE_KF_FLAG1";
		case IMAGE_KF_FLAG2_ID: return "IMAGE_KF_FLAG2";
		case IMAGE_L_BUTTON1_ID: return "IMAGE_L_BUTTON1";
		case IMAGE_L_BUTTON2_ID: return "IMAGE_L_BUTTON2";
		case IMAGE_R_BUTTON1_ID: return "IMAGE_R_BUTTON1";
		case IMAGE_R_BUTTON2_ID: return "IMAGE_R_BUTTON2";
		case IMAGE_BACKGROUND_PP_ID: return "IMAGE_BACKGROUND_PP";
		case IMAGE_BACKGROUND_ICE_ID: return "IMAGE_BACKGROUND_ICE";
		case IMAGE_BOMBALL_ID: return "IMAGE_BOMBALL";
		case IMAGE_BACKGROUND_GLADIANTUAR_ID: return "IMAGE_BACKGROUND_GLADIANTUAR";
		case IMAGE_BACKGROUND_HIGHGROUND_ID: return "IMAGE_BACKGROUND_HIGHGROUND";
		case IMAGE_MINIGAME_2_ID: return "IMAGE_MINIGAME_2";
		case IMAGE_BACKGROUND_FOREST_ID: return "IMAGE_BACKGROUND_FOREST";
		case IMAGE_OAK_ARROW_ID: return "IMAGE_OAK_ARROW";
		case IMAGE_SEEDBANK_SMALL_ID: return "IMAGE_SEEDBANK_SMALL";
		case IMAGE_TARGET_ID: return "IMAGE_TARGET";
		case IMAGE_CROSS_ID: return "IMAGE_CROSS";
		case IMAGE_TARGET_1_ID: return "IMAGE_TARGET_1";
		case IMAGE_TARGET_2_ID: return "IMAGE_TARGET_2";
		case IMAGE_TARGET_3_ID: return "IMAGE_TARGET_3";
		case IMAGE_P1_1_ID: return "IMAGE_P1_1";
		case IMAGE_P1_2_ID: return "IMAGE_P1_2";
		case IMAGE_P1_3_ID: return "IMAGE_P1_3";
		case IMAGE_P2_1_ID: return "IMAGE_P2_1";
		case IMAGE_P2_2_ID: return "IMAGE_P2_2";
		case IMAGE_P2_3_ID: return "IMAGE_P2_3";
		case IMAGE_BEJEWEL_SELECTORSHADOW_ID: return "IMAGE_BEJEWEL_SELECTORSHADOW";
		case IMAGE_VERSUS_BUTTON_ID: return "IMAGE_VERSUS_BUTTON";
		case IMAGE_VERSUS_BUTTON_HIGHLIGHTED_ID: return "IMAGE_VERSUS_BUTTON_HIGHLIGHTED";
		case IMAGE_PUDDLE_ID: return "IMAGE_PUDDLE";
		case IMAGE_ZOMBIE_BOBSLED1_ID: return "IMAGE_ZOMBIE_BOBSLED1";
		case IMAGE_ZOMBIE_BOBSLED2_ID: return "IMAGE_ZOMBIE_BOBSLED2";
		case IMAGE_ZOMBIE_BOBSLED3_ID: return "IMAGE_ZOMBIE_BOBSLED3";
		case IMAGE_ZOMBIE_BOBSLED4_ID: return "IMAGE_ZOMBIE_BOBSLED4";
		case IMAGE_ZOMBIE_BOBSLED_INSIDE_ID: return "IMAGE_ZOMBIE_BOBSLED_INSIDE";
		case IMAGE_BUNGEECORD_ID: return "IMAGE_BUNGEECORD";
		case IMAGE_BUNGEETARGET_ID: return "IMAGE_BUNGEETARGET";
		case IMAGE_SPOTLIGHT_ID: return "IMAGE_SPOTLIGHT";
		case IMAGE_SPOTLIGHT2_ID: return "IMAGE_SPOTLIGHT2";
		case IMAGE_WHITEPIXEL_ID: return "IMAGE_WHITEPIXEL";
		case IMAGE_ZOMBIEPOLEVAULTERARM_ID: return "IMAGE_ZOMBIEPOLEVAULTERARM";
		case IMAGE_ZOMBIEPOLEVAULTERHEAD_ID: return "IMAGE_ZOMBIEPOLEVAULTERHEAD";
		case IMAGE_ZOMBIEFOOTBALLHEAD_ID: return "IMAGE_ZOMBIEFOOTBALLHEAD";
		case IMAGE_ZOMBIEPAPERARM_ID: return "IMAGE_ZOMBIEPAPERARM";
		case IMAGE_POOLSPARKLY_ID: return "IMAGE_POOLSPARKLY";
		case IMAGE_WALLNUTPARTICLESSMALL_ID: return "IMAGE_WALLNUTPARTICLESSMALL";
		case IMAGE_WALLNUTPARTICLESLARGE_ID: return "IMAGE_WALLNUTPARTICLESLARGE";
		case IMAGE_PEA_SPLATS_ID: return "IMAGE_PEA_SPLATS";
		case IMAGE_STAR_PARTICLES_ID: return "IMAGE_STAR_PARTICLES";
		case IMAGE_STAR_SPLATS_ID: return "IMAGE_STAR_SPLATS";
		case IMAGE_PEA_PARTICLES_ID: return "IMAGE_PEA_PARTICLES";
		case IMAGE_SNOWPEA_SPLATS_ID: return "IMAGE_SNOWPEA_SPLATS";
		case IMAGE_SNOWPEA_PARTICLES_ID: return "IMAGE_SNOWPEA_PARTICLES";
		case IMAGE_SNOWPEA_PUFF_ID: return "IMAGE_SNOWPEA_PUFF";
		case IMAGE_SNOWFLAKES_ID: return "IMAGE_SNOWFLAKES";
		case IMAGE_POTATOMINE_PARTICLES_ID: return "IMAGE_POTATOMINE_PARTICLES";
		case IMAGE_PUFFSHROOM_PUFF1_ID: return "IMAGE_PUFFSHROOM_PUFF1";
		case IMAGE_ZAMBONISMOKE_ID: return "IMAGE_ZAMBONISMOKE";
		case IMAGE_ZOMBIEDANCERARM_ID: return "IMAGE_ZOMBIEDANCERARM";
		case IMAGE_ZOMBIEDANCERHEAD_ID: return "IMAGE_ZOMBIEDANCERHEAD";
		case IMAGE_ZOMBIEBALLOONHEAD_ID: return "IMAGE_ZOMBIEBALLOONHEAD";
		case IMAGE_ZOMBIEIMPHEAD_ID: return "IMAGE_ZOMBIEIMPHEAD";
		case IMAGE_ZOMBIEDIGGERHEAD_ID: return "IMAGE_ZOMBIEDIGGERHEAD";
		case IMAGE_ZOMBIEDIGGERARM_ID: return "IMAGE_ZOMBIEDIGGERARM";
		case IMAGE_ZOMBIEDOLPHINRIDERHEAD_ID: return "IMAGE_ZOMBIEDOLPHINRIDERHEAD";
		case IMAGE_ZOMBIEPOGO_ID: return "IMAGE_ZOMBIEPOGO";
		case IMAGE_ZOMBIEPOGOARM_ID: return "IMAGE_ZOMBIEPOGOARM";
		case IMAGE_ZOMBIEBACKUPDANCERARM_ID: return "IMAGE_ZOMBIEBACKUPDANCERARM";
		case IMAGE_ZOMBIEBACKUPDANCERHEAD_ID: return "IMAGE_ZOMBIEBACKUPDANCERHEAD";
		case IMAGE_ZOMBIEBOBSLEDHEAD_ID: return "IMAGE_ZOMBIEBOBSLEDHEAD";
		case IMAGE_ZOMBIELADDERARM_ID: return "IMAGE_ZOMBIELADDERARM";
		case IMAGE_ZOMBIELADDERHEAD_ID: return "IMAGE_ZOMBIELADDERHEAD";
		case IMAGE_ZOMBIEYETIHEAD_ID: return "IMAGE_ZOMBIEYETIHEAD";
		case IMAGE_SEEDPACKETFLASH_ID: return "IMAGE_SEEDPACKETFLASH";
		case IMAGE_ZOMBIEJACKBOXARM_ID: return "IMAGE_ZOMBIEJACKBOXARM";
		case IMAGE_IMITATERCLOUDS_ID: return "IMAGE_IMITATERCLOUDS";
		case IMAGE_IMITATERPUFFS_ID: return "IMAGE_IMITATERPUFFS";
		case IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_FIREBALL_PARTICLES";
		case IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_ICEBALL_PARTICLES";
		case IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_FIREBALL_GROUNDPARTICLES";
		case IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES_ID: return "IMAGE_ZOMBIE_BOSS_ICEBALL_GROUNDPARTICLES";
		case IMAGE_DOOMSHROOM_EXPLOSION_BASE_ID: return "IMAGE_DOOMSHROOM_EXPLOSION_BASE";
		case IMAGE_RAIN_ID: return "IMAGE_RAIN";
		case IMAGE_MINIGAME_DIAMOND_TROPHY_ID: return "IMAGE_MINIGAME_DIAMOND_TROPHY";
		case IMAGE_VASE_CHUNKS_ID: return "IMAGE_VASE_CHUNKS";
		case IMAGE_ZOMBOSS_PARTICLES_ID: return "IMAGE_ZOMBOSS_PARTICLES";
		case IMAGE_AWARDPICKUPGLOW_ID: return "IMAGE_AWARDPICKUPGLOW";
		case IMAGE_ZOMBIE_SEAWEED_ID: return "IMAGE_ZOMBIE_SEAWEED";
		case IMAGE_PINATA_ID: return "IMAGE_PINATA";
		case IMAGE_ZOMBIEFUTUREGLASSES_ID: return "IMAGE_ZOMBIEFUTUREGLASSES";
		case IMAGE_DUST_PUFFS_ID: return "IMAGE_DUST_PUFFS";
		case IMAGE_ZOMBIEVAMPIREHEAD_ID: return "IMAGE_ZOMBIEVAMPIREHEAD";
		case IMAGE_ZOMBIEFISHERHEAD_ID: return "IMAGE_ZOMBIEFISHERHEAD";
		case IMAGE_ZOMBIELEAFBLOWERHEAD_ID: return "IMAGE_ZOMBIELEAFBLOWERHEAD";
		case IMAGE_ZOMBIEBIGFOOTHEAD_ID: return "IMAGE_ZOMBIEBIGFOOTHEAD";
		case IMAGE_ZOMBIEAXEHEAD_ID: return "IMAGE_ZOMBIEAXEHEAD";
		case IMAGE_ZOMBIEVAMPIREARM_ID: return "IMAGE_ZOMBIEVAMPIREARM";
		case IMAGE_ZOMBIESCARECROWARM_ID: return "IMAGE_ZOMBIESCARECROWARM";
		case IMAGE_ZOMBIEFISHERARM_ID: return "IMAGE_ZOMBIEFISHERARM";
		case IMAGE_ZOMBIEHUNTERARM_ID: return "IMAGE_ZOMBIEHUNTERARM";
		case IMAGE_ZOMBIELEAFBLOWERARM_ID: return "IMAGE_ZOMBIELEAFBLOWERARM";
		case IMAGE_ZOMBIEAXEARM_ID: return "IMAGE_ZOMBIEAXEARM";
		case IMAGE_ZOMBIEBIGFOOTARM_ID: return "IMAGE_ZOMBIEBIGFOOTARM";
		case IMAGE_CREDITSBACKGROUND_ID: return "IMAGE_CREDITSBACKGROUND";
		case IMAGE_DISCLAIMERBACKGROUND_ID: return "IMAGE_DISCLAIMERBACKGROUND";
		case IMAGE_CREDITS_BTN1_ID: return "IMAGE_CREDITS_BTN1";
		case IMAGE_CREDITS_BTN2_ID: return "IMAGE_CREDITS_BTN2";
		case IMAGE_DISCLAIMER_BTN1_ID: return "IMAGE_DISCLAIMER_BTN1";
		case IMAGE_DISCLAIMER_BTN2_ID: return "IMAGE_DISCLAIMER_BTN2";
		case IMAGE_CROW1_ID: return "IMAGE_CROW1";
		case IMAGE_CROW2_ID: return "IMAGE_CROW2";
		case IMAGE_VIOLET_PADDLE_ID: return "IMAGE_VIOLET_PADDLE";
		case IMAGE_FOREST_OBJECTS_ID: return "IMAGE_FOREST_OBJECTS";
		case IMAGE_LOG1_ID: return "IMAGE_LOG1";
		case IMAGE_LOG2_ID: return "IMAGE_LOG2";
		case IMAGE_LOG3_ID: return "IMAGE_LOG3";
		case IMAGE_GEM_RED_ID: return "IMAGE_GEM_RED";
		case IMAGE_GEM_GREEN_ID: return "IMAGE_GEM_GREEN";
		case IMAGE_GEM_WHITE_ID: return "IMAGE_GEM_WHITE";
		case IMAGE_GEM_PURPLE_ID: return "IMAGE_GEM_PURPLE";
		case IMAGE_GEM_YELLOW_ID: return "IMAGE_GEM_YELLOW";
		case IMAGE_GEM_ORANGE_ID: return "IMAGE_GEM_ORANGE";
		case IMAGE_FLASHLIGHT_LIGHT_ID: return "IMAGE_FLASHLIGHT_LIGHT";
		case IMAGE_FOREST_NIGHT_MAP_ID: return "IMAGE_FOREST_NIGHT_MAP";
		case IMAGE_FOREST_NIGHT_ITEMS_ID: return "IMAGE_FOREST_NIGHT_MAP";
		case IMAGE_VINENUT_2_ID: return "IMAGE_VINENUT_2";
		case IMAGE_VINENUT_3_ID: return "IMAGE_VINENUT_3";
		case IMAGE_VINENUT_2_BODY_ID: return "IMAGE_VINENUT_2_BODY";
		case IMAGE_VINENUT_3_BODY_ID: return "IMAGE_VINENUT_3_BODY";
		case IMAGE_NET_ID: return "IMAGE_NET";
		case IMAGE_GAME_ID: return "IMAGE_GAME";
		case IMAGE_GAME2_ID: return "IMAGE_GAME2";
		case IMAGE_WOOD_ID: return "IMAGE_WOOD";
		case IMAGE_HUNTER_HAT_ID: return "IMAGE_HUNTER_HAT";
		case IMAGE_VERSUS_NOTE_ID: return "IMAGE_VERSUS_NOTE";
		case IMAGE_BACKGROUND7_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND7_GAMEOVER_MASK";
		case IMAGE_BACKGROUNDPP_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUNDPP_GAMEOVER_MASK";
		case IMAGE_BACKGROUND_GLADIANTUAR_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND_GLADIANTUAR_GAMEOVER_MASK";
		case IMAGE_WOODS_NOTE_ID: return "IMAGE_WOODS_NOTE";
		case IMAGE_SHOVEL_ROTATED_ID: return "IMAGE_SHOVEL_ROTATED";
		case IMAGE_ICON_WOODCHIPPER_ID: return "IMAGE_ICON_WOODCHIPPER";
		case IMAGE_ICON_NEW_ID: return "IMAGE_ICON_NEW";
		case IMAGE_PLAYER1_MOUSE_ID: return "IMAGE_TEST1";
		case IMAGE_PLAYER2_MOUSE_ID: return "IMAGE_TEST2";
		case IMAGE_PLAYER1_KEYBOARD_ID: return "IMAGE_TEST3";
		case IMAGE_PLAYER2_KEYBOARD_ID: return "IMAGE_TEST4";
		case IMAGE_OPTIONS_SLIDERKNOB3_ID: return "IMAGE_OPTIONS_SLIDERKNOB3";
		case IMAGE_OPTIONS_SLIDERSLOT4_ID: return "IMAGE_OPTIONS_SLIDERSLOT4";
		case IMAGE_DISCORD_BUTTON_ID: return "IMAGE_DISCORD_BUTTON";
		case IMAGE_DISCORD_BUTTON_HOVER_ID: return "IMAGE_DISCORD_BUTTON_HOVER";
		case IMAGE_DISCORD_BUTTON_DOWN_ID: return "IMAGE_DISCORD_BUTTON_DOWN";
		case IMAGE_GIGA_HEAD_ID: return "IMAGE_GIGA_HEAD";
		case IMAGE_GIGA_POLE_HEAD_ID: return "IMAGE_GIGA_POLE_HEAD";
		case IMAGE_GIGA_PROGRESS_FLAG_ID: return "IMAGE_GIGA_PROGRESS_FLAG";
		case IMAGE_BOWLING_STRIPE_POOL_ID: return "IMAGE_BOWLING_STRIPE_POOL";
		case IMAGE_BOWLING_STRIPE_ROOF_ID: return "IMAGE_BOWLING_STRIPE_ROOF";
		case IMAGE_BOWLING_STRIPE_ROOF_VERSUS_ID: return "IMAGE_BOWLING_STRIPE_ROOF_VERSUS";
		case IMAGE_PLANT_TROPHY_ID: return "IMAGE_PLANT_TROPHY";
		case IMAGE_PLANT_TROPHY_HIGH_RES_ID: return "IMAGE_PLANT_TROPHY_HIGH_RES";
		case IMAGE_ZOMBIE_TROPHY_ID: return "IMAGE_ZOMBIE_TROPHY";
		case IMAGE_ZOMBIE_TROPHY_HIGH_RES_ID: return "IMAGE_ZOMBIE_TROPHY_HIGH_RES";
		case IMAGE_VERSUS_BACKGROUND_ID: return "IMAGE_VERSUS_BACKGROUND";
		case IMAGE_VERSUS_WINDOW_ID: return "IMAGE_VERSUS_WINDOW";
		case IMAGE_VERSUS_WINDOW_HIGHLIGHT_ID: return "IMAGE_VERSUS_WINDOW_HIGHLIGHT";
		case IMAGE_MINIGAME_3_ID: return "IMAGE_MINIGAME_3";
		case IMAGE_MULTIPLAYER_OPTION_ID: return "IMAGE_MULTIPLAYER_OPTION";
		case IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT_ID: return "IMAGE_MULTIPLAYER_OPTION_HIGHLIGHT";
		case IMAGE_GRAVESTONE_ROOF1_ID: return "IMAGE_GRAVESTONE_ROOF1";
		case IMAGE_GRAVESTONE_ROOF2_ID: return "IMAGE_GRAVESTONE_ROOF2";
		case IMAGE_GRAVESTONE_ROOF3_ID: return "IMAGE_GRAVESTONE_ROOF3";
		case IMAGE_GRAVESTONE_ROOF4_ID: return "IMAGE_GRAVESTONE_ROOF4";
		case IMAGE_GRAVESTONE_ROOF5_ID: return "IMAGE_GRAVESTONE_ROOF5";
		case IMAGE_GRAVESTONE_ROOF6_ID: return "IMAGE_GRAVESTONE_ROOF6";
		case IMAGE_GRAVESTONE_NIGHT_DIRT_ID: return "IMAGE_GRAVESTONE_NIGHT_DIRT";
		case IMAGE_MAP_FLIPPED_ID: return "IMAGE_MAP_FLIPPED";
		case IMAGE_ZOMBIEPOLE_ID: return "IMAGE_ZOMBIEPOLE";
		case IMAGE_STICK_ID: return "IMAGE_STICK";
		case IMAGE_GAME_OVER_FLIPPED_ID: return "IMAGE_GAME_OVER_FLIPPED";
		case IMAGE_REANIM_BUSH_PARTICLE1_ID: return "IMAGE_REANIM_BUSH_PARTICLE1";
		case IMAGE_REANIM_BUSH_PARTICLE2_ID: return "IMAGE_REANIM_BUSH_PARTICLE2";
		case IMAGE_REANIM_BUSH_PARTICLE3_ID: return "IMAGE_REANIM_BUSH_PARTICLE3";
		case IMAGE_REANIM_BUSH_PARTICLE4_ID: return "IMAGE_REANIM_BUSH_PARTICLE4";
		case IMAGE_ZOMBIE_BUSHES_ID: return "IMAGE_ZOMBIE_BUSHES";
		case IMAGE_YOUTUBE_BUTTON_ID: return "IMAGE_YOUTUBE_BUTTON";
		case IMAGE_YOUTUBE_BUTTON_HOVER_ID: return "IMAGE_YOUTUBE_BUTTON_HOVER";
		case IMAGE_STONEBUTTON_RIGHT_ID: return "IMAGE_STONEBUTTON_RIGHT";
		case IMAGE_STONEBUTTON_RIGHT_HOVER_ID: return "IMAGE_STONEBUTTON_RIGHT_HOVER";
		case IMAGE_STONEBUTTON_LEFT_ID: return "IMAGE_STONEBUTTON_LEFT";
		case IMAGE_STONEBUTTON_LEFT_HOVER_ID: return "IMAGE_STONEBUTTON_LEFT_HOVER";
		case IMAGE_REANIM_WALLNUT_BODY_ID: return "IMAGE_REANIM_WALLNUT_BODY";
		case IMAGE_REANIM_WALLNUT_CRACKED1_ID: return "IMAGE_REANIM_WALLNUT_CRACKED1";
		case IMAGE_REANIM_WALLNUT_CRACKED2_ID: return "IMAGE_REANIM_WALLNUT_CRACKED2";
		case IMAGE_REANIM_TALLNUT_CRACKED1_ID: return "IMAGE_REANIM_TALLNUT_CRACKED1";
		case IMAGE_REANIM_TALLNUT_CRACKED2_ID: return "IMAGE_REANIM_TALLNUT_CRACKED2";
		case IMAGE_REANIM_DUMMY_CRACKED1_ID: return "IMAGE_REANIM_DUMMY_CRACKED1";
		case IMAGE_REANIM_DUMMY_CRACKED2_ID: return "IMAGE_REANIM_DUMMY_CRACKED2";
		case IMAGE_REANIM_PUMPKIN_DAMAGE1_ID: return "IMAGE_REANIM_PUMPKIN_DAMAGE1";
		case IMAGE_REANIM_PUMPKIN_DAMAGE3_ID: return "IMAGE_REANIM_PUMPKIN_DAMAGE3";
		case IMAGE_REANIM_FIRESHROOM_CRACKED1_ID: return "IMAGE_REANIM_FIRESHROOM_CRACKED1";
		case IMAGE_REANIM_FIRESHROOM_CRACKED2_ID: return "IMAGE_REANIM_FIRESHROOM_CRACKED2";
		case IMAGE_REANIM_FIRESHROOM_BODY2_ID: return "IMAGE_REANIM_FIRESHROOM_BODY2";
		case IMAGE_REANIM_ZOMBIE_CONE1_ID: return "IMAGE_REANIM_ZOMBIE_CONE1";
		case IMAGE_REANIM_ZOMBIE_CONE2_ID: return "IMAGE_REANIM_ZOMBIE_CONE2";
		case IMAGE_REANIM_ZOMBIE_CONE3_ID: return "IMAGE_REANIM_ZOMBIE_CONE3";
		case IMAGE_REANIM_ZOMBIE_BUCKET1_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET1";
		case IMAGE_REANIM_ZOMBIE_BUCKET2_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET2";
		case IMAGE_REANIM_ZOMBIE_BUCKET3_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET3";
		case IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT";
		case IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT2";
		case IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_HARDHAT3";
		case IMAGE_REANIM_ZOMBIE_SCREENDOOR1_ID: return "IMAGE_REANIM_ZOMBIE_SCREENDOOR1";
		case IMAGE_REANIM_ZOMBIE_SCREENDOOR2_ID: return "IMAGE_REANIM_ZOMBIE_SCREENDOOR2";
		case IMAGE_REANIM_ZOMBIE_SCREENDOOR3_ID: return "IMAGE_REANIM_ZOMBIE_SCREENDOOR3";
		case IMAGE_REANIM_ZOMBIE_TRASHCAN1_ID: return "IMAGE_REANIM_ZOMBIE_TRASHCAN1";
		case IMAGE_REANIM_ZOMBIE_TRASHCAN2_ID: return "IMAGE_REANIM_ZOMBIE_TRASHCAN2";
		case IMAGE_REANIM_ZOMBIE_TRASHCAN3_ID: return "IMAGE_REANIM_ZOMBIE_TRASHCAN3";
		case IMAGE_REANIM_ZOMBIE_FLAG1_ID: return "IMAGE_REANIM_ZOMBIE_FLAG1";
		case IMAGE_REANIM_ZOMBIE_FLAG3_ID: return "IMAGE_REANIM_ZOMBIE_FLAG3";
		case IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET2";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_HELMET3";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_HAND";
		case IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_FOOTBALL_LEFTARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET1_ID: return "IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET1";
		case IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET2_ID: return "IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET2";
		case IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET3_ID: return "IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HELMET3";
		case IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HAND_ID: return "IMAGE_REANIM_ZOMBIE_GIGAFOOTBALL_HAND";
		case IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_LEFTARM_LOWER";
		case IMAGE_REANIM_ZOMBIE_PAPER_PAPER2_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_PAPER2";
		case IMAGE_REANIM_ZOMBIE_PAPER_PAPER3_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_PAPER3";
		case IMAGE_REANIM_ZOMBIE_FISHER_HAT_ID: return "IMAGE_REANIM_ZOMBIE_FISHER_HAT";
		case IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD_ID: return "IMAGE_REANIM_ZOMBIE_PAPER_MADHEAD";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_1_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_2_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT_ID: return "IMAGE_REANIM_ZOMBIE_ZAMBONI_WHEEL_FLAT";
		case IMAGE_REANIM_ZOMBIE_ICE2_ID: return "IMAGE_REANIM_ZOMBIE_ICE2";
		case IMAGE_REANIM_ZOMBIE_ICE3_ID: return "IMAGE_REANIM_ZOMBIE_ICE3";
		case IMAGE_REANIM_COIN_SILVER_DOLLAR_ID: return "IMAGE_REANIM_COIN_SILVER_DOLLAR";
		case IMAGE_REANIM_COIN_GOLD_DOLLAR_ID: return "IMAGE_REANIM_COIN_GOLD_DOLLAR";
		case IMAGE_REANIM_DIAMOND_ID: return "IMAGE_REANIM_DIAMOND";
		case IMAGE_REANIM_COINGLOW_ID: return "IMAGE_REANIM_COINGLOW";
		case IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_JACKSON_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_DANCER_INNERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_DANCER_INNERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_BALLOON_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE_ID: return "IMAGE_REANIM_ZOMBIE_IMP_ARM1_BONE";
		case IMAGE_REANIM_ZOMBIE_IMP_ARM2_ID: return "IMAGE_REANIM_ZOMBIE_IMP_ARM2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_BODY1_3";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_2_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_2";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_3_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_BODY1_3";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_DUCKXING";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_ZOMBIE";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_FOOT2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_OUTERARM_LOWER2";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD2_REDEYE";
		case IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GARGANTUAR_HEAD_REDEYE";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET1_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET1";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET2_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET2";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET3_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET3";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET_RED_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HELMET_RED";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_AXE2_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_AXE2";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_HAND_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_HAND_REDEYE";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD_REDEYE";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_HEAD2_REDEYE";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER_REDEYE";
		case IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2_REDEYE_ID: return "IMAGE_REANIM_ZOMBIE_GLADIANTUAR_OUTERARM_LOWER2_REDEYE";
		case IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_DOLPHINRIDER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE1";
		case IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICKDAMAGE2";
		case IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICK2DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2_ID: return "IMAGE_REANIM_ZOMBIE_POGO_STICKHANDS2";
		case IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_BOBSLED_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_JACKBOX_BOX_ID: return "IMAGE_REANIM_ZOMBIE_JACKBOX_BOX";
		case IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2_ID: return "IMAGE_REANIM_ZOMBIE_JACKBOX_OUTERARM_LOWER2";
		case IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_SNORKLE_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED_ID: return "IMAGE_REANIM_ZOMBIE_BUNGI_HEAD_SCARED";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_BASKETBALL";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_WITHBALL";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_POLE_DAMAGE_WITHBALL";
		case IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE_ID: return "IMAGE_REANIM_ZOMBIE_CATAPULT_SIDING_DAMAGE";
		case IMAGE_REANIM_ZOMBIE_LADDER_1_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_1";
		case IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_1_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_LADDER_5_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_5";
		case IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_LADDER_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_ICEBALL";
		case IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_HEAD_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_JAW_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_HAND_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_OUTERARM_THUMB_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE1";
		case IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_FOOT_DAMAGE2";
		case IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_EYEGLOW_BLUE";
		case IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE_ID: return "IMAGE_REANIM_ZOMBIE_BOSS_MOUTHGLOW_BLUE";
		case IMAGE_REANIM_CABBAGEPULT_CABBAGE_ID: return "IMAGE_REANIM_CABBAGEPULT_CABBAGE";
		case IMAGE_REANIM_CORNPULT_KERNAL_ID: return "IMAGE_REANIM_CORNPULT_KERNAL";
		case IMAGE_REANIM_CORNPULT_BUTTER_ID: return "IMAGE_REANIM_CORNPULT_BUTTER";
		case IMAGE_REANIM_CORNPULT_BUTTER_SPLAT_ID: return "IMAGE_REANIM_CORNPULT_BUTTER_SPLAT";
		case IMAGE_REANIM_MELONPULT_MELON_ID: return "IMAGE_REANIM_MELONPULT_MELON";
		case IMAGE_REANIM_WINTERMELON_PROJECTILE_ID: return "IMAGE_REANIM_WINTERMELON_PROJECTILE";
		case IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE_ID: return "IMAGE_REANIM_ZOMBIE_DIGGER_PICKAXE";
		case IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_GROSSOUT";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES1";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES2";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES3";
		case IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_SUNGLASSES4";
		case IMAGE_REANIM_GARLIC_BODY2_ID: return "IMAGE_REANIM_GARLIC_BODY2";
		case IMAGE_REANIM_GARLIC_BODY3_ID: return "IMAGE_REANIM_GARLIC_BODY3";
		case IMAGE_REANIM_COBCANNON_COB_ID: return "IMAGE_REANIM_COBCANNON_COB";
		case IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND_ID: return "IMAGE_REANIM_ZOMBIE_YETI_OUTERARM_HAND";
		case IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD_ID: return "IMAGE_REANIM_ZOMBIE_SNORKLE_HEAD";
		case IMAGE_REANIM_ZOMBIE_SCARE_HEAD_ID: return "IMAGE_REANIM_ZOMBIE_SCARE_HEAD";
		case IMAGE_REANIM_ZOMBIE_SCARE_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_SCARE_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_VAMPIRE_OUTERARM_UPPER2_ID: return "IMAGE_REANIM_ZOMBIE_VAMPIRE_OUTERARM_UPPER2";
		case IMAGE_REANIM_ZOMBIE_FISHERMAN_OUTERARM_UPPER_ID: return "IMAGE_REANIM_ZOMBIE_FISHERMAN_OUTERARM_UPPER";
		case IMAGE_REANIM_ZOMBIE_LEAFBLOWER_OUTERARM_UPPER_ID: return "IMAGE_REANIM_ZOMBIE_LEAFBLOWER_OUTERARM_UPPER";
		case IMAGE_REANIM_ZOMBIE_AXE_OUTERARM_UPPER_ID: return "IMAGE_REANIM_ZOMBIE_AXE_OUTERARM_UPPER";
		case IMAGE_REANIM_ZOMBIE_AXE_HAT_ID: return "IMAGE_REANIM_ZOMBIE_AXE_HAT";
		case IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_ADVENTURE_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_STARTADVENTURE_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_SURVIVAL_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_CHALLENGES_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON_ID: return "IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_BUTTON";
		case IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT_ID: return "IMAGE_REANIM_SELECTORSCREEN_VASEBREAKER_HIGHLIGHT";
		case IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS_ID: return "IMAGE_REANIM_SELECTORSCREEN_WOODSIGN2_PRESS";
		case IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_ID: return "IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3";
		case IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS_ID: return "IMAGE_REANIM_SELECTORSCREEN_WOODSIGN3_PRESS";
		case IMAGE_REANIM_SELECTORSCREEN_BG_ID: return "IMAGE_REANIM_SELECTORSCREEN_BG";
		case IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW_ID: return "IMAGE_REANIM_SELECTORSCREEN_ALMANAC_SHADOW";
		case IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW_ID: return "IMAGE_REANIM_SELECTORSCREEN_KEY_SHADOW";
		case IMAGE_REANIM_TREE_BG_ID: return "IMAGE_REANIM_TREE_BG";
		case IMAGE_REANIM_POT_TOP_DARK_ID: return "IMAGE_REANIM_POT_TOP_DARK";
		case IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE_ID: return "IMAGE_REANIM_ZENGARDEN_BUGSPRAY_BOTTLE";
		case IMAGE_REANIM_STINKY_TURN3_ID: return "IMAGE_REANIM_STINKY_TURN3";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH1_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH1";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH4_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH4";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH5_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH5";
		case IMAGE_REANIM_CRAZYDAVE_MOUTH6_ID: return "IMAGE_REANIM_CRAZYDAVE_MOUTH6";
		case IMAGE_REANIM_ZOMBIE_MUSTACHE2_ID: return "IMAGE_REANIM_ZOMBIE_MUSTACHE2";
		case IMAGE_REANIM_ZOMBIE_MUSTACHE3_ID: return "IMAGE_REANIM_ZOMBIE_MUSTACHE3";
		case IMAGE_REANIM_ZOMBIE_HEAD_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_HEAD_GIGA";
		case IMAGE_REANIM_ZOMBIE_BUCKET1_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET1_GIGA";
		case IMAGE_REANIM_ZOMBIE_BUCKET2_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET2_GIGA";
		case IMAGE_REANIM_ZOMBIE_BUCKET3_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_BUCKET3_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER1_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER1_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER2_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER2_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER3_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER3_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER4_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER4_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER5_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER5_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER6_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER6_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER7_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER7_GIGA";
		case IMAGE_REANIM_ZOMBIE_POLEVAULTER8_GIGA_ID: return "IMAGE_REANIM_ZOMBIE_POLEVAULTER8_GIGA";
		case SOUND_AWOOGA_ID: return "SOUND_AWOOGA";
		case SOUND_BLEEP_ID: return "SOUND_BLEEP";
		case SOUND_BUZZER_ID: return "SOUND_BUZZER";
		case SOUND_CHOMP_ID: return "SOUND_CHOMP";
		case SOUND_CHOMP2_ID: return "SOUND_CHOMP2";
		case SOUND_CHOMPSOFT_ID: return "SOUND_CHOMPSOFT";
		case SOUND_EVILLAUGH_ID: return "SOUND_EVILLAUGH";
		case SOUND_FLOOP_ID: return "SOUND_FLOOP";
		case SOUND_FROZEN_ID: return "SOUND_FROZEN";
		case SOUND_GULP_ID: return "SOUND_GULP";
		case SOUND_GROAN_ID: return "SOUND_GROAN";
		case SOUND_GROAN2_ID: return "SOUND_GROAN2";
		case SOUND_GROAN3_ID: return "SOUND_GROAN3";
		case SOUND_GROAN4_ID: return "SOUND_GROAN4";
		case SOUND_GROAN5_ID: return "SOUND_GROAN5";
		case SOUND_GROAN6_ID: return "SOUND_GROAN6";
		case SOUND_LOSEMUSIC_ID: return "SOUND_LOSEMUSIC";
		case SOUND_MINDCONTROLLED_ID: return "SOUND_MINDCONTROLLED";
		case SOUND_PAUSE_ID: return "SOUND_PAUSE";
		case SOUND_PLANT_ID: return "SOUND_PLANT";
		case SOUND_PLANT2_ID: return "SOUND_PLANT2";
		case SOUND_POINTS_ID: return "SOUND_POINTS";
		case SOUND_SEEDLIFT_ID: return "SOUND_SEEDLIFT";
		case SOUND_SIREN_ID: return "SOUND_SIREN";
		case SOUND_SLURP_ID: return "SOUND_SLURP";
		case SOUND_SPLAT_ID: return "SOUND_SPLAT";
		case SOUND_SPLAT2_ID: return "SOUND_SPLAT2";
		case SOUND_SPLAT3_ID: return "SOUND_SPLAT3";
		case SOUND_SUKHBIR_ID: return "SOUND_SUKHBIR";
		case SOUND_SUKHBIR2_ID: return "SOUND_SUKHBIR2";
		case SOUND_SUKHBIR3_ID: return "SOUND_SUKHBIR3";
		case SOUND_SUKHBIR4_ID: return "SOUND_SUKHBIR4";
		case SOUND_SUKHBIR5_ID: return "SOUND_SUKHBIR5";
		case SOUND_SUKHBIR6_ID: return "SOUND_SUKHBIR6";
		case SOUND_TAP_ID: return "SOUND_TAP";
		case SOUND_TAP2_ID: return "SOUND_TAP2";
		case SOUND_THROW_ID: return "SOUND_THROW";
		case SOUND_THROW2_ID: return "SOUND_THROW2";
		case SOUND_BLOVER_ID: return "SOUND_BLOVER";
		case SOUND_WINMUSIC_ID: return "SOUND_WINMUSIC";
		case SOUND_LAWNMOWER_ID: return "SOUND_LAWNMOWER";
		case SOUND_BOING_ID: return "SOUND_BOING";
		case SOUND_JACKINTHEBOX_ID: return "SOUND_JACKINTHEBOX";
		case SOUND_DIAMOND_ID: return "SOUND_DIAMOND";
		case SOUND_DOLPHIN_APPEARS_ID: return "SOUND_DOLPHIN_APPEARS";
		case SOUND_DOLPHIN_BEFORE_JUMPING_ID: return "SOUND_DOLPHIN_BEFORE_JUMPING";
		case SOUND_POTATO_MINE_ID: return "SOUND_POTATO_MINE";
		case SOUND_ZAMBONI_ID: return "SOUND_ZAMBONI";
		case SOUND_BALLOON_POP_ID: return "SOUND_BALLOON_POP";
		case SOUND_THUNDER_ID: return "SOUND_THUNDER";
		case SOUND_ZOMBIESPLASH_ID: return "SOUND_ZOMBIESPLASH";
		case SOUND_BOWLING_ID: return "SOUND_BOWLING";
		case SOUND_BOWLINGIMPACT_ID: return "SOUND_BOWLINGIMPACT";
		case SOUND_BOWLINGIMPACT2_ID: return "SOUND_BOWLINGIMPACT2";
		case SOUND_GRAVEBUSTERCHOMP_ID: return "SOUND_GRAVEBUSTERCHOMP";
		case SOUND_GRAVEBUTTON_ID: return "SOUND_GRAVEBUTTON";
		case SOUND_LIMBS_POP_ID: return "SOUND_LIMBS_POP";
		case SOUND_PLANTERN_ID: return "SOUND_PLANTERN";
		case SOUND_POGO_ZOMBIE_ID: return "SOUND_POGO_ZOMBIE";
		case SOUND_SNOW_PEA_SPARKLES_ID: return "SOUND_SNOW_PEA_SPARKLES";
		case SOUND_PLANT_WATER_ID: return "SOUND_PLANT_WATER";
		case SOUND_ZOMBIE_ENTERING_WATER_ID: return "SOUND_ZOMBIE_ENTERING_WATER";
		case SOUND_ZOMBIE_FALLING_1_ID: return "SOUND_ZOMBIE_FALLING_1";
		case SOUND_ZOMBIE_FALLING_2_ID: return "SOUND_ZOMBIE_FALLING_2";
		case SOUND_BUSH_RUSTLING1_ID: return "SOUND_BUSH_RUSTLING1";
		case SOUND_BUSH_RUSTLING2_ID: return "SOUND_BUSH_RUSTLING2";
		case SOUND_BUSH_RUSTLING3_ID: return "SOUND_BUSH_RUSTLING3";
		case SOUND_HUNTER_SHOOT_ID: return "SOUND_HUNTER_SHOOT";
		case SOUND_SKELETON_DIE_ID: return "SOUND_SKELETON_DIE";
		case SOUND_SKELETON_REVIVE_ID: return "SOUND_SKELETON_REVIVE";
		case SOUND_BUSH_DESTROYED1_ID: return "SOUND_BUSH_DESTROYED1";
		case SOUND_PUFF_ID: return "SOUND_PUFF";
		case SOUND_FUME_ID: return "SOUND_FUME";
		case SOUND_HUGE_WAVE_ID: return "SOUND_HUGE_WAVE";
		case SOUND_SLOT_MACHINE_ID: return "SOUND_SLOT_MACHINE";
		case SOUND_COIN_ID: return "SOUND_COIN";
		case SOUND_ROLL_IN_ID: return "SOUND_ROLL_IN";
		case SOUND_DIGGER_ZOMBIE_ID: return "SOUND_DIGGER_ZOMBIE";
		case SOUND_HATCHBACK_CLOSE_ID: return "SOUND_HATCHBACK_CLOSE";
		case SOUND_HATCHBACK_OPEN_ID: return "SOUND_HATCHBACK_OPEN";
		case SOUND_KERNELPULT_ID: return "SOUND_KERNELPULT";
		case SOUND_KERNELPULT2_ID: return "SOUND_KERNELPULT2";
		case SOUND_ZOMBAQUARIUM_DIE_ID: return "SOUND_ZOMBAQUARIUM_DIE";
		case SOUND_BUNGEE_SCREAM_ID: return "SOUND_BUNGEE_SCREAM";
		case SOUND_BUNGEE_SCREAM2_ID: return "SOUND_BUNGEE_SCREAM2";
		case SOUND_BUNGEE_SCREAM3_ID: return "SOUND_BUNGEE_SCREAM3";
		case SOUND_BUTTER_ID: return "SOUND_BUTTER";
		case SOUND_JACK_SURPRISE_ID: return "SOUND_JACK_SURPRISE";
		case SOUND_JACK_SURPRISE2_ID: return "SOUND_JACK_SURPRISE2";
		case SOUND_NEWSPAPER_RARRGH_ID: return "SOUND_NEWSPAPER_RARRGH";
		case SOUND_NEWSPAPER_RARRGH2_ID: return "SOUND_NEWSPAPER_RARRGH2";
		case SOUND_NEWSPAPER_RIP_ID: return "SOUND_NEWSPAPER_RIP";
		case SOUND_SQUASH_HMM_ID: return "SOUND_SQUASH_HMM";
		case SOUND_SQUASH_HMM2_ID: return "SOUND_SQUASH_HMM2";
		case SOUND_VASE_BREAKING_ID: return "SOUND_VASE_BREAKING";
		case SOUND_POOL_CLEANER_ID: return "SOUND_POOL_CLEANER";
		case SOUND_MAGNETSHROOM_ID: return "SOUND_MAGNETSHROOM";
		case SOUND_LADDER_ZOMBIE_ID: return "SOUND_LADDER_ZOMBIE";
		case SOUND_GARGANTUAR_THUMP_ID: return "SOUND_GARGANTUAR_THUMP";
		case SOUND_BASKETBALL_ID: return "SOUND_BASKETBALL";
		case SOUND_FIREPEA_ID: return "SOUND_FIREPEA";
		case SOUND_IGNITE_ID: return "SOUND_IGNITE";
		case SOUND_IGNITE2_ID: return "SOUND_IGNITE2";
		case SOUND_READYSETPLANT_ID: return "SOUND_READYSETPLANT";
		case SOUND_DOOMSHROOM_ID: return "SOUND_DOOMSHROOM";
		case SOUND_EXPLOSION_ID: return "SOUND_EXPLOSION";
		case SOUND_FINALWAVE_ID: return "SOUND_FINALWAVE";
		case SOUND_REVERSE_EXPLOSION_ID: return "SOUND_REVERSE_EXPLOSION";
		case SOUND_RVTHROW_ID: return "SOUND_RVTHROW";
		case SOUND_SHIELDHIT_ID: return "SOUND_SHIELDHIT";
		case SOUND_SHIELDHIT2_ID: return "SOUND_SHIELDHIT2";
		case SOUND_BOSSEXPLOSION_ID: return "SOUND_BOSSEXPLOSION";
		case SOUND_CHERRYBOMB_ID: return "SOUND_CHERRYBOMB";
		case SOUND_BONK_ID: return "SOUND_BONK";
		case SOUND_SWING_ID: return "SOUND_SWING";
		case SOUND_RAIN_ID: return "SOUND_RAIN";
		case SOUND_LIGHTFILL_ID: return "SOUND_LIGHTFILL";
		case SOUND_PLASTICHIT_ID: return "SOUND_PLASTICHIT";
		case SOUND_PLASTICHIT2_ID: return "SOUND_PLASTICHIT2";
		case SOUND_JALAPENO_ID: return "SOUND_JALAPENO";
		case SOUND_BALLOONINFLATE_ID: return "SOUND_BALLOONINFLATE";
		case SOUND_BIGCHOMP_ID: return "SOUND_BIGCHOMP";
		case SOUND_MELONIMPACT_ID: return "SOUND_MELONIMPACT";
		case SOUND_MELONIMPACT2_ID: return "SOUND_MELONIMPACT2";
		case SOUND_PLANTGROW_ID: return "SOUND_PLANTGROW";
		case SOUND_SHOOP_ID: return "SOUND_SHOOP";
		case SOUND_TAPGLASS_ID: return "SOUND_TAPGLASS";
		case SOUND_JUICY_ID: return "SOUND_JUICY";
		case SOUND_COFFEE_ID: return "SOUND_COFFEE";
		case SOUND_WAKEUP_ID: return "SOUND_WAKEUP";
		case SOUND_WAKEUP_REVERSE_ID: return "SOUND_WAKEUP_REVERSE";
		case SOUND_LOWGROAN_ID: return "SOUND_LOWGROAN";
		case SOUND_LOWGROAN2_ID: return "SOUND_LOWGROAN2";
		case SOUND_PRIZE_ID: return "SOUND_PRIZE";
		case SOUND_YUCK_ID: return "SOUND_YUCK";
		case SOUND_YUCK2_ID: return "SOUND_YUCK2";
		case SOUND_GRASSSTEP_ID: return "SOUND_GRASSSTEP";
		case SOUND_SHOVEL_ID: return "SOUND_SHOVEL";
		case SOUND_COBLAUNCH_ID: return "SOUND_COBLAUNCH";
		case SOUND_WATERING_ID: return "SOUND_WATERING";
		case SOUND_POLEVAULT_ID: return "SOUND_POLEVAULT";
		case SOUND_GRAVESTONE_RUMBLE_ID: return "SOUND_GRAVESTONE_RUMBLE";
		case SOUND_DIRT_RISE_ID: return "SOUND_DIRT_RISE";
		case SOUND_FERTILIZER_ID: return "SOUND_FERTILIZER";
		case SOUND_PORTAL_ID: return "SOUND_PORTAL";
		case SOUND_BUGSPRAY_ID: return "SOUND_BUGSPRAY";
		case SOUND_SCREAM_ID: return "SOUND_SCREAM";
		case SOUND_PAPER_ID: return "SOUND_PAPER";
		case SOUND_MONEYFALLS_ID: return "SOUND_MONEYFALLS";
		case SOUND_IMP_ID: return "SOUND_IMP";
		case SOUND_IMP2_ID: return "SOUND_IMP2";
		case SOUND_HYDRAULIC_SHORT_ID: return "SOUND_HYDRAULIC_SHORT";
		case SOUND_HYDRAULIC_ID: return "SOUND_HYDRAULIC";
		case SOUND_GARGANTUDEATH_ID: return "SOUND_GARGANTUDEATH";
		case SOUND_CERAMIC_ID: return "SOUND_CERAMIC";
		case SOUND_BOSSBOULDERATTACK_ID: return "SOUND_BOSSBOULDERATTACK";
		case SOUND_CHIME_ID: return "SOUND_CHIME";
		case SOUND_CRAZYDAVESHORT1_ID: return "SOUND_CRAZYDAVESHORT1";
		case SOUND_CRAZYDAVESHORT2_ID: return "SOUND_CRAZYDAVESHORT2";
		case SOUND_CRAZYDAVESHORT3_ID: return "SOUND_CRAZYDAVESHORT3";
		case SOUND_CRAZYDAVELONG1_ID: return "SOUND_CRAZYDAVELONG1";
		case SOUND_CRAZYDAVELONG2_ID: return "SOUND_CRAZYDAVELONG2";
		case SOUND_CRAZYDAVELONG3_ID: return "SOUND_CRAZYDAVELONG3";
		case SOUND_CRAZYDAVEEXTRALONG1_ID: return "SOUND_CRAZYDAVEEXTRALONG1";
		case SOUND_CRAZYDAVEEXTRALONG2_ID: return "SOUND_CRAZYDAVEEXTRALONG2";
		case SOUND_CRAZYDAVEEXTRALONG3_ID: return "SOUND_CRAZYDAVEEXTRALONG3";
		case SOUND_CRAZYDAVECRAZY_ID: return "SOUND_CRAZYDAVECRAZY";
		case SOUND_BRAVEDAVE1_ID: return "SOUND_BRAVEDAVE1";
		case SOUND_BRAVEDAVE2_ID: return "SOUND_BRAVEDAVE2";
		case SOUND_BRAVEDAVE3_ID: return "SOUND_BRAVEDAVE3";
		case SOUND_BRAVEDAVE4_ID: return "SOUND_BRAVEDAVE4";
		case SOUND_BRAVEDAVE5_ID: return "SOUND_BRAVEDAVE5";
		case SOUND_BRAVEDAVE6_ID: return "SOUND_BRAVEDAVE6";
		case SOUND_BEE1_ID: return "SOUND_BEE1";
		case SOUND_BEE2_ID: return "SOUND_BEE2";
		case SOUND_BONK1_ID: return "SOUND_BONK1";
		case SOUND_BONK2_ID: return "SOUND_BONK2";
		case SOUND_VIOLET_ID: return "SOUND_VIOLET";
		case SOUND_RELOAD_ID: return "SOUND_RELOAD";
		case SOUND_CRASH_ID: return "SOUND_CRASH";
		case SOUND_BELL_ID: return "SOUND_BELL";
		case SOUND_SHOOTINGSTAR_ID: return "SOUND_SHOOTINGSTAR";
		case SOUND_LOG_PLACE_ID: return "SOUND_LOG_PLACE";
		case SOUND_WOODCHIPPER_ID: return "SOUND_WOODCHIPPER";
		case SOUND_PHONOGRAPH_ID: return "SOUND_PHONOGRAPH";
		case SOUND_DANCER_ID: return "SOUND_DANCER";
		case SOUND_FINALFANFARE_ID: return "SOUND_FINALFANFARE";
		case SOUND_CRAZYDAVESCREAM_ID: return "SOUND_CRAZYDAVESCREAM";
		case SOUND_CRAZYDAVESCREAM2_ID: return "SOUND_CRAZYDAVESCREAM2";
		case SOUND_CHILLY_FREEZE_ID: return "SOUND_CHILLY_FREEZE";
		case SOUND_ELECTRIC_ID: return "SOUND_ELECTRIC";
		case SOUND_ELECTRIC2_ID: return "SOUND_ELECTRIC2";
		case SOUND_ELECTRIC3_ID: return "SOUND_ELECTRIC3";
		case SOUND_ICE_ID: return "SOUND_ICE";
		case SOUND_GLADIANTUAR_DEATH_ID: return "SOUND_GLADIANTUAR_DEATH";
		case SOUND_BLOOD_MOON_ID: return "SOUND_BLOOD_MOON";
		case SOUND_CROW_ID: return "SOUND_CROW";
		case SOUND_CROW_DEATH_ID: return "SOUND_CROW_DEATH";
		case SOUND_BREAK_ID: return "SOUND_BREAK";
		case IMAGE_BACKGROUND1_ID: return "IMAGE_BACKGROUND1";
		case IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND1_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND1_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND1_GAMEOVER_MASK";
		case IMAGE_BACKGROUND1UNSODDED_ID: return "IMAGE_BACKGROUND1UNSODDED";
		case IMAGE_SOD1ROW_ID: return "IMAGE_SOD1ROW";
		case IMAGE_SOD3ROW_ID: return "IMAGE_SOD3ROW";
		case IMAGE_BACKGROUND2_ID: return "IMAGE_BACKGROUND2";
		case IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND2_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND2_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND2_GAMEOVER_MASK";
		case IMAGE_BACKGROUND3_ID: return "IMAGE_BACKGROUND3";
		case IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND3_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND3_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND3_GAMEOVER_MASK";
		case IMAGE_BACKGROUND4_ID: return "IMAGE_BACKGROUND4";
		case IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY_ID: return "IMAGE_BACKGROUND4_GAMEOVER_INTERIOR_OVERLAY";
		case IMAGE_BACKGROUND4_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND4_GAMEOVER_MASK";
		case IMAGE_FOG_ID: return "IMAGE_FOG";
		case IMAGE_FOG_SOFTWARE_ID: return "IMAGE_FOG_SOFTWARE";
		case IMAGE_BACKGROUND5_ID: return "IMAGE_BACKGROUND5";
		case IMAGE_BACKGROUND5_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND5_GAMEOVER_MASK";
		case IMAGE_BACKGROUND6BOSS_ID: return "IMAGE_BACKGROUND6BOSS";
		case IMAGE_BACKGROUND6_GAMEOVER_MASK_ID: return "IMAGE_BACKGROUND6_GAMEOVER_MASK";
		case IMAGE_BACKGROUND_MUSHROOMGARDEN_ID: return "IMAGE_BACKGROUND_MUSHROOMGARDEN";
		case IMAGE_BACKGROUND_GREENHOUSE_ID: return "IMAGE_BACKGROUND_GREENHOUSE";
		case IMAGE_BACKGROUND_GREENHOUSE_OVERLAY_ID: return "IMAGE_BACKGROUND_GREENHOUSE_OVERLAY";
		case IMAGE_AQUARIUM1_ID: return "IMAGE_AQUARIUM1";
		case IMAGE_WAVECENTER_ID: return "IMAGE_WAVECENTER";
		case IMAGE_WAVESIDE_ID: return "IMAGE_WAVESIDE";
		case IMAGE_AWARDSCREEN_BACK_ID: return "IMAGE_AWARDSCREEN_BACK";
		case IMAGE_CHALLENGE_BACKGROUND_ID: return "IMAGE_CHALLENGE_BACKGROUND";
		case IMAGE_CHALLENGE_WINDOW_ID: return "IMAGE_CHALLENGE_WINDOW";
		case IMAGE_CHALLENGE_WINDOW_HIGHLIGHT_ID: return "IMAGE_CHALLENGE_WINDOW_HIGHLIGHT";
		case IMAGE_CHALLENGE_BLANK_ID: return "IMAGE_CHALLENGE_BLANK";
		case IMAGE_CHALLENGE_THUMBNAILS_ID: return "IMAGE_CHALLENGE_THUMBNAILS";
		case IMAGE_SURVIVAL_THUMBNAILS_ID: return "IMAGE_SURVIVAL_THUMBNAILS";
		case IMAGE_LOCK_ID: return "IMAGE_LOCK";
		case IMAGE_LOCK_OPEN_ID: return "IMAGE_LOCK_OPEN";
		case IMAGE_ALMANAC_INDEXBACK_ID: return "IMAGE_ALMANAC_INDEXBACK";
		case IMAGE_ALMANAC_PLANTBACK_ID: return "IMAGE_ALMANAC_PLANTBACK";
		case IMAGE_ALMANAC_ZOMBIEBACK_ID: return "IMAGE_ALMANAC_ZOMBIEBACK";
		case IMAGE_ALMANAC_PLANTCARD_ID: return "IMAGE_ALMANAC_PLANTCARD";
		case IMAGE_ALMANAC_ZOMBIECARD_ID: return "IMAGE_ALMANAC_ZOMBIECARD";
		case IMAGE_ALMANAC_ZOMBIEWINDOW_ID: return "IMAGE_ALMANAC_ZOMBIEWINDOW";
		case IMAGE_ALMANAC_ZOMBIEWINDOW2_ID: return "IMAGE_ALMANAC_ZOMBIEWINDOW2";
		case IMAGE_ALMANAC_ZOMBIEBLANK_ID: return "IMAGE_ALMANAC_ZOMBIEBLANK";
		case IMAGE_ALMANAC_GROUNDDAY_ID: return "IMAGE_ALMANAC_GROUNDDAY";
		case IMAGE_ALMANAC_GROUNDNIGHT_ID: return "IMAGE_ALMANAC_GROUNDNIGHT";
		case IMAGE_ALMANAC_GROUNDPOOL_ID: return "IMAGE_ALMANAC_GROUNDPOOL";
		case IMAGE_ALMANAC_GROUNDNIGHTPOOL_ID: return "IMAGE_ALMANAC_GROUNDNIGHTPOOL";
		case IMAGE_ALMANAC_GROUNDROOF_ID: return "IMAGE_ALMANAC_GROUNDROOF";
		case IMAGE_ALMANAC_GROUNDICE_ID: return "IMAGE_ALMANAC_GROUNDICE";
		case IMAGE_ALMANAC_GROUNDFOREST_ID: return "IMAGE_ALMANAC_GROUNDFOREST";
		case IMAGE_ALMANAC_CLOSEBUTTON_ID: return "IMAGE_ALMANAC_CLOSEBUTTON";
		case IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT_ID: return "IMAGE_ALMANAC_CLOSEBUTTONHIGHLIGHT";
		case IMAGE_ALMANAC_INDEXBUTTON_ID: return "IMAGE_ALMANAC_INDEXBUTTON";
		case IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT_ID: return "IMAGE_ALMANAC_INDEXBUTTONHIGHLIGHT";
		case IMAGE_STORE_BACKGROUND_ID: return "IMAGE_STORE_BACKGROUND";
		case IMAGE_STORE_BACKGROUNDNIGHT_ID: return "IMAGE_STORE_BACKGROUNDNIGHT";
		case IMAGE_STORE_CAR_ID: return "IMAGE_STORE_CAR";
		case IMAGE_STORE_CAR_NIGHT_ID: return "IMAGE_STORE_CAR_NIGHT";
		case IMAGE_STORE_CARCLOSED_ID: return "IMAGE_STORE_CARCLOSED";
		case IMAGE_STORE_CARCLOSED_NIGHT_ID: return "IMAGE_STORE_CARCLOSED_NIGHT";
		case IMAGE_STORE_HATCHBACKOPEN_ID: return "IMAGE_STORE_HATCHBACKOPEN";
		case IMAGE_STORE_SIGN_ID: return "IMAGE_STORE_SIGN";
		case IMAGE_STORE_MAINMENUBUTTON_ID: return "IMAGE_STORE_MAINMENUBUTTON";
		case IMAGE_STORE_MAINMENUBUTTONDOWN_ID: return "IMAGE_STORE_MAINMENUBUTTONDOWN";
		case IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT_ID: return "IMAGE_STORE_MAINMENUBUTTONHIGHLIGHT";
		case IMAGE_STORE_NEXTBUTTON_ID: return "IMAGE_STORE_NEXTBUTTON";
		case IMAGE_STORE_NEXTBUTTONHIGHLIGHT_ID: return "IMAGE_STORE_NEXTBUTTONHIGHLIGHT";
		case IMAGE_STORE_NEXTBUTTONDISABLED_ID: return "IMAGE_STORE_NEXTBUTTONDISABLED";
		case IMAGE_STORE_PREVBUTTON_ID: return "IMAGE_STORE_PREVBUTTON";
		case IMAGE_STORE_PREVBUTTONHIGHLIGHT_ID: return "IMAGE_STORE_PREVBUTTONHIGHLIGHT";
		case IMAGE_STORE_PREVBUTTONDISABLED_ID: return "IMAGE_STORE_PREVBUTTONDISABLED";
		case IMAGE_STORE_PRICETAG_ID: return "IMAGE_STORE_PRICETAG";
		case IMAGE_STORE_PACKETUPGRADE_ID: return "IMAGE_STORE_PACKETUPGRADE";
		case IMAGE_STORE_MUSHROOMGARDENICON_ID: return "IMAGE_STORE_MUSHROOMGARDENICON";
		case IMAGE_STORE_AQUARIUMGARDENICON_ID: return "IMAGE_STORE_AQUARIUMGARDENICON";
		case IMAGE_STORE_TREEOFWISDOMICON_ID: return "IMAGE_STORE_TREEOFWISDOMICON";
		case IMAGE_STORE_FIRSTAIDWALLNUTICON_ID: return "IMAGE_STORE_FIRSTAIDWALLNUTICON";
		case IMAGE_STORE_PVZICON_ID: return "IMAGE_STORE_PVZICON";
		case IMAGE_ZOMBIE_NOTE_ID: return "IMAGE_ZOMBIE_NOTE";
		case IMAGE_ZOMBIE_NOTE1_ID: return "IMAGE_ZOMBIE_NOTE1";
		case IMAGE_ZOMBIE_NOTE2_ID: return "IMAGE_ZOMBIE_NOTE2";
		case IMAGE_ZOMBIE_NOTE3_ID: return "IMAGE_ZOMBIE_NOTE3";
		case IMAGE_ZOMBIE_NOTE4_ID: return "IMAGE_ZOMBIE_NOTE4";
		case IMAGE_ZOMBIE_NOTE5_ID: return "IMAGE_ZOMBIE_NOTE5";
		case IMAGE_ZOMBIE_NOTE6_ID: return "IMAGE_ZOMBIE_NOTE6";
		case IMAGE_ZOMBIE_FINAL_NOTE_ID: return "IMAGE_ZOMBIE_FINAL_NOTE";
		case IMAGE_ZOMBIE_NOTE_HELP_ID: return "IMAGE_ZOMBIE_NOTE_HELP";
		case FONT_BRIANNETOD32_ID: return "FONT_BRIANNETOD32";
		case FONT_BRIANNETOD32BLACK_ID: return "FONT_BRIANNETOD32BLACK";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING1_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING1";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING2_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING2";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING3_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING3";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING4_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING4";
		case IMAGE_REANIM_SUNFLOWER_HEAD_SING5_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_SING5";
		case IMAGE_REANIM_SUNFLOWER_HEAD_WINK_ID: return "IMAGE_REANIM_SUNFLOWER_HEAD_WINK";
		case IMAGE_REANIM_CREDITS_DISCOLIGHTS_ID: return "IMAGE_REANIM_CREDITS_DISCOLIGHTS";
		case IMAGE_REANIM_CREDITS_FOGMACHINE_ID: return "IMAGE_REANIM_CREDITS_FOGMACHINE";
		case IMAGE_CREDITS_ZOMBIENOTE_ID: return "IMAGE_CREDITS_ZOMBIENOTE";
		case IMAGE_CREDITS_PLAYBUTTON_ID: return "IMAGE_CREDITS_PLAYBUTTON";
		default: return "";
	}
}

