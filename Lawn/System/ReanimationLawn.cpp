#include "../Plant.h"
#include "../Zombie.h"
#include "../../LawnApp.h"
#include "ReanimationLawn.h"
#include "../../Sexy.TodLib/TodDebug.h"
#include "../../SexyAppFramework/Color.h"
#include "../../Sexy.TodLib/Reanimator.h"
#include "../../SexyAppFramework/MemoryImage.h"
#include "../../Resources.h"

//0x46EF00
void ReanimatorCache::UpdateReanimationForVariation(Reanimation* theReanim, DrawVariation theDrawVariation)
{
	if (theDrawVariation >= DrawVariation::VARIATION_MARIGOLD_WHITE && theDrawVariation <= DrawVariation::VARIATION_MARIGOLD_LIGHT_GREEN)
	{
		int aVariationIndex = (int)theDrawVariation - (int)DrawVariation::VARIATION_MARIGOLD_WHITE;
		Color MARIGOLD_VARIATIONS[] = {
			Color(255, 255, 255),
			Color(230, 30, 195),
			Color(250, 125, 5),
			Color(255, 145, 215),
			Color(160, 255, 245),
			Color(230, 30, 30),
			Color(5, 130, 255),
			Color(195, 55, 235),
			Color(235, 210, 255),
			Color(255, 245, 55),
			Color(180, 255, 105)
		};

		TOD_ASSERT(aVariationIndex >= 0 && aVariationIndex < LENGTH(MARIGOLD_VARIATIONS));
		theReanim->GetTrackInstanceByName("Marigold_petals")->mTrackColor = MARIGOLD_VARIATIONS[aVariationIndex];
	}
	else
	{
		switch (theDrawVariation)
		{
		case DrawVariation::VARIATION_IMITATER:
			theReanim->mFilterEffect = FilterEffect::FILTER_EFFECT_WASHED_OUT;
			break;
		case DrawVariation::VARIATION_IMITATER_LESS:
			theReanim->mFilterEffect = FilterEffect::FILTER_EFFECT_LESS_WASHED_OUT;
			break;
		case DrawVariation::VARIATION_ZEN_GARDEN:
			theReanim->SetFramesForLayer("anim_zengarden");
			break;
		case DrawVariation::VARIATION_ZEN_GARDEN_WATER:
			theReanim->SetFramesForLayer("anim_waterplants");
			break;
		case DrawVariation::VARIATION_AQUARIUM:
			theReanim->SetFramesForLayer("anim_idle_aquarium");
			break;
		case DrawVariation::VARIATION_SPROUT_NO_FLOWER:
			theReanim->SetFramesForLayer("anim_idle_noflower");
			break;
		default:
			TOD_ASSERT(false);
			break;
		}
	}
}

//0x46F100
void ReanimatorCache::DrawReanimatorFrame(Graphics* g, float thePosX, float thePosY, ReanimationType theReanimationType, const char* theTrackName, DrawVariation theDrawVariation)
{
	Reanimation aReanim;
	aReanim.ReanimationInitializeType(thePosX, thePosY, theReanimationType);

	if (theTrackName != nullptr && aReanim.TrackExists(theTrackName))
	{
		aReanim.SetFramesForLayer(theTrackName);
	}
	if (theReanimationType == ReanimationType::REANIM_KERNELPULT)
	{
		aReanim.AssignRenderGroupToTrack("Cornpult_butter", RENDER_GROUP_HIDDEN);
	}
	else if (theReanimationType == ReanimationType::REANIM_SUNFLOWER)
	{
		aReanim.mAnimTime = 0.15f;
	}
	aReanim.AssignRenderGroupToTrack("anim_waterline", RENDER_GROUP_HIDDEN);

	if (g->GetColorizeImages())
	{
		aReanim.mColorOverride = g->GetColor();
	}
	aReanim.OverrideScale(g->mScaleX, g->mScaleY);
	
	if (theDrawVariation != DrawVariation::VARIATION_NORMAL)
	{
		UpdateReanimationForVariation(&aReanim, theDrawVariation);
	}

	aReanim.Draw(g);
}

//0x46F280
MemoryImage* ReanimatorCache::MakeBlankMemoryImage(int theWidth, int theHeight)
{
	MemoryImage* aImage = new MemoryImage();

	int aBitsCount = theWidth * theHeight;
	aImage->mBits = new unsigned long[aBitsCount + 1];
	aImage->mWidth = theWidth;
	aImage->mHeight = theHeight;
	aImage->mHasTrans = true;
	aImage->mHasAlpha = true;
	memset(aImage->mBits, 0, aBitsCount * 4);
	aImage->mBits[aBitsCount] = Sexy::MEMORYCHECK_ID;
	return aImage;
}

void ReanimatorCache::GetPlantImageSize(SeedType theSeedType, int& theOffsetX, int& theOffsetY, int& theWidth, int& theHeight)
{
	theOffsetX = -20;
	theOffsetY = -20;
	theWidth = 120;
	theHeight = 120;

	if (theSeedType == SeedType::SEED_TALLNUT || theSeedType == SeedType::SEED_VINENUT || theSeedType == SeedType::SEED_OAK_ARCHER)
	{
		theOffsetY = -40;
		theHeight += 40;
		theOffsetX = -40;
		theWidth += 40;
	}
	else if (theSeedType == SeedType::SEED_MELONPULT || theSeedType == SeedType::SEED_WINTERMELON || theSeedType == SeedType::SEED_PEPPER || theSeedType == SeedType::SEED_PULTSHROOM)
	{
		theOffsetX = -40;
		theWidth += 40;
	}
	else if (theSeedType == SeedType::SEED_COBCANNON)
	{
		theWidth += 80;
	}
	else if (theSeedType == SeedType::SEED_CHARD_GUARD)
	{
		theHeight += 400;
		theWidth += 400;
	}
}

//0x46F330
MemoryImage* ReanimatorCache::MakeCachedMowerFrame(LawnMowerType theMowerType)
{
	MemoryImage* aImage;

	switch (theMowerType)
	{
	case LawnMowerType::LAWNMOWER_LAWN:
	{
		aImage = MakeBlankMemoryImage(90, 100);
		Graphics aMemoryGraphics(aImage);
		aMemoryGraphics.SetLinearBlend(true);
		aMemoryGraphics.mScaleX = 0.85f;
		aMemoryGraphics.mScaleY = 0.85f;
		DrawReanimatorFrame(&aMemoryGraphics, 10.0f, 0.0f, ReanimationType::REANIM_LAWNMOWER, "anim_normal", DrawVariation::VARIATION_NORMAL);
		break;
	}
	case LawnMowerType::LAWNMOWER_POOL:
	{
		aImage = MakeBlankMemoryImage(90, 100);
		Graphics aMemoryGraphics(aImage);
		aMemoryGraphics.SetLinearBlend(true);
		aMemoryGraphics.mScaleX = 0.8f;
		aMemoryGraphics.mScaleY = 0.8f;
		DrawReanimatorFrame(&aMemoryGraphics, 10.0f, 25.0f, ReanimationType::REANIM_POOL_CLEANER, nullptr, DrawVariation::VARIATION_NORMAL);
		break;
	}
	case LawnMowerType::LAWNMOWER_ROOF:
	{
		aImage = MakeBlankMemoryImage(90, 100);
		Graphics aMemoryGraphics(aImage);
		aMemoryGraphics.SetLinearBlend(true);
		aMemoryGraphics.mScaleX = 0.85f;
		aMemoryGraphics.mScaleY = 0.85f;
		DrawReanimatorFrame(&aMemoryGraphics, 10.0f, 0.0f, ReanimationType::REANIM_ROOF_CLEANER, nullptr, DrawVariation::VARIATION_NORMAL);
		break;
	}
	case LawnMowerType::LAWNMOWER_SUPER_MOWER:
	{
		aImage = MakeBlankMemoryImage(90, 100);
		Graphics aMemoryGraphics(aImage);
		aMemoryGraphics.SetLinearBlend(true);
		aMemoryGraphics.mScaleX = 0.85f;
		aMemoryGraphics.mScaleY = 0.85f;
		DrawReanimatorFrame(&aMemoryGraphics, 10.0f, 0.0f, ReanimationType::REANIM_LAWNMOWER, "anim_tricked", DrawVariation::VARIATION_NORMAL);
		break;
	}
	case LawnMowerType::LAWNMOWER_FOREST_MOWER:
	{
		/*Reanimation aLawnMower;
		aLawnMower.ReanimationInitializeType(0, 0, ReanimationType::REANIM_LAWNMOWER);
		aLawnMower.SetFramesForLayer("anim_normal");
		aLawnMower.SetImageOverride("LawnMower_body", IMAGE_FOREST_MOWER_BODY);
		aLawnMower.SetImageOverride("LawnMower_engine", IMAGE_FOREST_MOWER_ENGINE);
		aLawnMower.OverrideScale(0.85f, 0.85f);*/

		aImage = MakeBlankMemoryImage(100, 100);
		Graphics aMemoryGraphics(aImage);
		aMemoryGraphics.mScaleX = 0.85f;
		aMemoryGraphics.mScaleY = 0.85f;
		aMemoryGraphics.SetLinearBlend(true);
		DrawReanimatorFrame(&aMemoryGraphics, 10.0f, 5.0f, ReanimationType::REANIM_WOOD_CHIPPER, nullptr, DrawVariation::VARIATION_NORMAL);
		//aLawnMower.Draw(&aMemoryGraphics);
		break;
	}
	default:
		TOD_ASSERT(false);
		break;
	}

	return aImage;
}

//0x46F550
MemoryImage* ReanimatorCache::MakeCachedPlantFrame(SeedType theSeedType, DrawVariation theDrawVariation)
{
	int aOffsetX, aOffsetY, aWidth, aHeight;
	GetPlantImageSize(theSeedType, aOffsetX, aOffsetY, aWidth, aHeight);
	MemoryImage* aMemoryImage = MakeBlankMemoryImage(aWidth, aHeight);
	Graphics aMemoryGraphics(aMemoryImage);
	aMemoryGraphics.SetLinearBlend(true);

	PlantDefinition& aPlantDef = GetPlantDefinition(theSeedType);
	//TOD_ASSERT(aPlantDef.mReanimationType != ReanimationType::REANIM_NONE);

	if (theSeedType == SeedType::SEED_POTATOMINE)
	{
		aMemoryGraphics.mScaleX = 0.85f;
		aMemoryGraphics.mScaleY = 0.85f;
		DrawReanimatorFrame(&aMemoryGraphics, -(int)(aOffsetX - 12.0f), -(int)(aOffsetY - 12.0f), aPlantDef.mReanimationType, "anim_armed", theDrawVariation);
	}
	else if (theSeedType == SeedType::SEED_INSTANT_COFFEE)
	{
		aMemoryGraphics.mScaleX = 0.8f;
		aMemoryGraphics.mScaleY = 0.8f;
		DrawReanimatorFrame(&aMemoryGraphics, -(int)(aOffsetX - 12.0f), -(int)(aOffsetY - 12.0f), aPlantDef.mReanimationType, "anim_idle", theDrawVariation);
	}
	else if (theSeedType == SeedType::SEED_EXPLODE_O_NUT)
	{
		//aMemoryGraphics.SetColorizeImages(true);
		//aMemoryGraphics.SetColor(Color(255, 64, 64));
		DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_idle", theDrawVariation);
	}
	else if (theSeedType == SeedType::SEED_ICENUT)
	{
		//aMemoryGraphics.SetColorizeImages(true);
		//aMemoryGraphics.SetColor(Color(100, 160, 255));
		DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_idle", theDrawVariation);
	}
	else if (theSeedType == SeedType::SEED_SHRINK)
	{
		aMemoryGraphics.mTransY += 20;
		DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_idle_almanac", theDrawVariation);
	}
	else if (theSeedType == SeedType::SEED_SHOOTINGSTAR) {
		Reanimation aReanim;
		aReanim.ReanimationInitializeType(-aOffsetX, -aOffsetY, aPlantDef.mReanimationType);

		if (aReanim.TrackExists("anim_full_idle"))
		{
			aReanim.SetFramesForLayer("anim_full_idle");
		}

		aReanim.AssignRenderGroupToTrack("anim_waterline", RENDER_GROUP_HIDDEN);

		if (aMemoryGraphics.GetColorizeImages())
		{
			aReanim.mColorOverride = aMemoryGraphics.GetColor();
		}
		aReanim.OverrideScale(aMemoryGraphics.mScaleX, aMemoryGraphics.mScaleY);

		if (theDrawVariation != DrawVariation::VARIATION_NORMAL)
		{
			UpdateReanimationForVariation(&aReanim, theDrawVariation);
		}

		aReanim.Draw(&aMemoryGraphics);
	}
	else
	{
		DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_idle", theDrawVariation);

		if (theSeedType == SeedType::SEED_PEASHOOTER || theSeedType == SeedType::SEED_SNOWPEA || theSeedType == SeedType::SEED_REPEATER ||
			theSeedType == SeedType::SEED_LEFTPEATER || theSeedType == SeedType::SEED_GATLINGPEA || theSeedType == SEED_FLAMEPEA || theSeedType == SEED_QUEENPEA ||
			theSeedType == SEED_PLASMAPEA || theSeedType == SEED_EPEA || theSeedType == SEED_BEE_SHOOTER || theSeedType == SEED_REVERSE_PEASHOOTER || theSeedType == SEED_REVERSE_SNOWPEA)
		{
			DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_head_idle", theDrawVariation);
		}
		else if (theSeedType == SeedType::SEED_SPLITPEA)
		{
			DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_head_idle", theDrawVariation);
			DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_splitpea_idle", theDrawVariation);
		}
		else if (theSeedType == SeedType::SEED_WATERPOT)
		{
			DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_water_idle", theDrawVariation);
		}
		else if (theSeedType == SeedType::SEED_THREEPEATER || theSeedType == SeedType::SEED_REVERSE_THREEPEATER)
		{
			DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_head_idle1", theDrawVariation);
			DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_head_idle3", theDrawVariation);
			DrawReanimatorFrame(&aMemoryGraphics, -aOffsetX, -aOffsetY, aPlantDef.mReanimationType, "anim_head_idle2", theDrawVariation);
		}
	}

	return aMemoryImage;
}

//0x46F8A0
MemoryImage* ReanimatorCache::MakeCachedZombieFrame(ZombieType theZombieType)
{
	MemoryImage* aMemoryImage = MakeBlankMemoryImage(200, 210);
	Graphics aMemoryGraphics(aMemoryImage);
	if (theZombieType == ZombieType::ZOMBIE_ZOMBONI)
	{
		aMemoryGraphics.mTransX += 50;
	}

	aMemoryGraphics.SetLinearBlend(true);

	ZombieType aUseZombieType = theZombieType;
	if (theZombieType == ZombieType::ZOMBIE_CACHED_POLEVAULTER_WITH_POLE)
	{
		aUseZombieType = ZombieType::ZOMBIE_POLEVAULTER;
	}
	ZombieDefinition& aZombieDef = GetZombieDefinition(aUseZombieType);
	TOD_ASSERT(aZombieDef.mReanimationType != ReanimationType::REANIM_NONE);

	float aPosX = 40.0f, aPosY = 40.0f;
	if (aZombieDef.mReanimationType == ReanimationType::REANIM_ZOMBIE || aZombieDef.mReanimationType == ReanimationType::REANIM_SKELETON)
	{
		Reanimation aReanim;
		aReanim.ReanimationInitializeType(aPosX, aPosY, aZombieDef.mReanimationType);
		aReanim.SetFramesForLayer("anim_idle");
		Zombie::SetupReanimLayers(&aReanim, aUseZombieType);

		if (theZombieType == ZombieType::ZOMBIE_SCREENDOOR)
			aReanim.AssignRenderGroupToTrack("anim_screendoor", RENDER_GROUP_NORMAL);
		else if (theZombieType == ZombieType::ZOMBIE_TRASHCAN)
			aReanim.AssignRenderGroupToTrack("anim_trashcan", RENDER_GROUP_NORMAL);
		else if (theZombieType == ZombieType::ZOMBIE_FLAG)
		{
			Reanimation aReanimFlag;
			aReanimFlag.ReanimationInitializeType(aPosX, aPosY, ReanimationType::REANIM_FLAG);
			aReanimFlag.SetFramesForLayer("Zombie_flag");
			aReanimFlag.Draw(&aMemoryGraphics);
		}
		else if (theZombieType == ZombieType::ZOMBIE_PEA_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 72, aPosY - 2, ReanimationType::REANIM_PEASHOOTER);
			aReanimHead.SetFramesForLayer("anim_head_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_GATLING_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 72, aPosY - 2, ReanimationType::REANIM_GATLINGPEA);
			aReanimHead.SetFramesForLayer("anim_head_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_REPEATER_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 72, aPosY - 2, ReanimationType::REANIM_REPEATER);
			aReanimHead.SetFramesForLayer("anim_head_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_SNOWPEA_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 72, aPosY - 2, ReanimationType::REANIM_SNOWPEA);
			aReanimHead.SetFramesForLayer("anim_head_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_FIREPEA_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 72, aPosY - 2, ReanimationType::REANIM_FLAMEPEA);
			aReanimHead.SetFramesForLayer("anim_head_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_EPEA_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 72, aPosY - 2, ReanimationType::REANIM_EPEA);
			aReanimHead.SetFramesForLayer("anim_head_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_SUNFLOWER_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 68, aPosY - 3, ReanimationType::REANIM_SUNFLOWER);
			aReanimHead.SetFramesForLayer("anim_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);

			aReanimHead.SetImageOverride("frontleaf", IMAGE_BLANK);
			aReanimHead.SetImageOverride("backleaf", IMAGE_BLANK);
			aReanimHead.SetImageOverride("backleaf_right_tip", IMAGE_BLANK);
			aReanimHead.SetImageOverride("frontleaf_left_tip", IMAGE_BLANK);
			aReanimHead.SetImageOverride("frontleaf_right_tip", IMAGE_BLANK);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_SQUASH_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 63, aPosY - 10, ReanimationType::REANIM_SQUASH);
			aReanimHead.SetFramesForLayer("anim_idle");
			aReanimHead.OverrideScale(-0.75f, 0.75f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_POTATO_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 57, aPosY - 2, ReanimationType::REANIM_POTATOMINE);
			aReanimHead.SetFramesForLayer("anim_armed");
			aReanimHead.OverrideScale(-0.65f, 0.65f);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		else if (theZombieType == ZombieType::ZOMBIE_CHOMPER_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 52, aPosY + 2, ReanimationType::REANIM_CHOMPER);
			aReanimHead.SetFramesForLayer("anim_idle");
			aReanimHead.OverrideScale(-0.7f, 0.7f);
			aReanimHead.SetImageOverride("Chomper_groundleaf1tip", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_groundleaf2tip", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_groundleaf1", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_groundleaf2", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_groundleaf3", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_groundleaf4", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Zombie_outerarm_lower", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Zombie_outerarm_hand", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_stem1", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_stem2", IMAGE_BLANK);
			aReanimHead.SetImageOverride("Chomper_stem3", IMAGE_BLANK);
			aReanimHead.Draw(&aMemoryGraphics);
			aReanim.AssignRenderGroupToTrack("Zombie_neck", RENDER_GROUP_HIDDEN);
		}
		aReanim.Draw(&aMemoryGraphics);
		if (theZombieType == ZombieType::ZOMBIE_WALLNUT_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 55, aPosY - 2, ReanimationType::REANIM_WALLNUT);
			aReanimHead.SetFramesForLayer("anim_idle");
			aReanimHead.OverrideScale(-0.8f, 0.8f);
			aReanimHead.Draw(&aMemoryGraphics);
		}
		else if (theZombieType == ZombieType::ZOMBIE_JALAPENO_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 62, aPosY - 5, ReanimationType::REANIM_JALAPENO);
			aReanimHead.SetFramesForLayer("anim_idle");
			aReanimHead.OverrideScale(-1.0f, 1.0f);
			aReanimHead.Draw(&aMemoryGraphics);
		}
		else if (theZombieType == ZombieType::ZOMBIE_TALLNUT_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 50, aPosY, ReanimationType::REANIM_TALLNUT);
			aReanimHead.SetFramesForLayer("anim_idle");
			aReanimHead.OverrideScale(-0.8f, 0.8f);
			aReanimHead.Draw(&aMemoryGraphics);
		}
		else if (theZombieType == ZombieType::ZOMBIE_CHERRY_HEAD)
		{
			Reanimation aReanimHead;
			aReanimHead.ReanimationInitializeType(aPosX + 60, aPosY - 2, ReanimationType::REANIM_CHERRYBOMB);
			aReanimHead.SetFramesForLayer("anim_idle");
			aReanimHead.OverrideScale(-0.8f, 0.8f);
			aReanimHead.Draw(&aMemoryGraphics);
		}
	}
	else if (aZombieDef.mReanimationType == ReanimationType::REANIM_BOSS)
	{
		Reanimation aReanim;
		aReanim.ReanimationInitializeType(-524.0f, -88.0f, aZombieDef.mReanimationType);
		aReanim.SetFramesForLayer("anim_head_idle");
		Reanimation aReanimDriver;
		aReanimDriver.ReanimationInitializeType(46.0f, 22.0f, ReanimationType::REANIM_BOSS_DRIVER);
		aReanimDriver.SetFramesForLayer("anim_idle");

		aReanim.Draw(&aMemoryGraphics);
		aReanimDriver.Draw(&aMemoryGraphics);
		aReanim.AssignRenderGroupToTrack("boss_body1", RENDER_GROUP_HIDDEN);
		aReanim.AssignRenderGroupToTrack("boss_neck", RENDER_GROUP_HIDDEN);
		aReanim.AssignRenderGroupToTrack("boss_head2", RENDER_GROUP_HIDDEN);
		aReanim.Draw(&aMemoryGraphics);
	}
	else if (aZombieDef.mReanimationType == ReanimationType::REANIM_GARGANTUAR || aZombieDef.mReanimationType == ReanimationType::REANIM_GLADIANTUAR)
	{
		Reanimation aReanim;
		aReanim.ReanimationInitializeType(aPosX, aPosY, aZombieDef.mReanimationType);
		aReanim.SetFramesForLayer("anim_idle");
		Zombie::SetupGargReanimLayers(&aReanim, aUseZombieType);
		aReanim.Draw(&aMemoryGraphics);
	}
	else
	{
		const char* aTrackName = "anim_idle";
		if (theZombieType == ZombieType::ZOMBIE_POGO)
		{
			aTrackName = "anim_pogo";
		}
		else if (theZombieType == ZombieType::ZOMBIE_CACHED_POLEVAULTER_WITH_POLE)
		{
			aTrackName = "anim_idle";
		}
		else if (theZombieType == ZombieType::ZOMBIE_POLEVAULTER)
		{
			aTrackName = "anim_walk";
		}
		else if (theZombieType == ZombieType::ZOMBIE_GARGANTUAR || theZombieType == ZombieType::ZOMBIE_REDEYE_GARGANTUAR)
		{
			aPosY = 60.0f;
		}

		DrawReanimatorFrame(&aMemoryGraphics, aPosX, aPosY, aZombieDef.mReanimationType, aTrackName, DrawVariation::VARIATION_NORMAL);
	}
	return aMemoryImage;

}

//0x46FDC0
void ReanimatorCache::ReanimatorCacheInitialize()
{
	mApp = (LawnApp*)gSexyAppBase;
	for (int i = 0; i < SeedType::NUM_SEED_TYPES; i++)
		mPlantImages[i] = nullptr;
	for (int i = 0; i < LawnMowerType::NUM_MOWER_TYPES; i++)
		mLawnMowers[i] = nullptr;
	for (int i = 0; i < ZombieType::NUM_ZOMBIE_TYPES; i++)
		mZombieImages[i] = nullptr;
}

//0x46FED0
void ReanimatorCache::ReanimatorCacheDispose()
{
	for (int i = 0; i < SeedType::NUM_SEED_TYPES; i++)
		delete mPlantImages[i];
	while (mImageVariationList.mSize != 0)
	{
		ReanimCacheImageVariation aImageVariation = mImageVariationList.RemoveHead();
		if (aImageVariation.mImage != nullptr)
			delete aImageVariation.mImage;
	}
	for (int i = 0; i < LawnMowerType::NUM_MOWER_TYPES; i++)
		delete mLawnMowers[i];
	for (int i = 0; i < ZombieType::NUM_ZOMBIE_TYPES; i++)
		delete mZombieImages[i];
}


//0x46FFB0
void ReanimatorCache::DrawCachedPlant(Graphics* g, float thePosX, float thePosY, SeedType theSeedType, DrawVariation theDrawVariation)
{
	TOD_ASSERT(theSeedType >= 0 && theSeedType < SeedType::NUM_SEED_TYPES);

	MemoryImage* aImage = nullptr;
	if (theDrawVariation != DrawVariation::VARIATION_NORMAL)
	{
		for (TodListNode<ReanimCacheImageVariation>* aNode = mImageVariationList.mHead; aNode != nullptr; aNode = aNode->mNext)
		{
			ReanimCacheImageVariation& aImageVariation = aNode->mValue;
			if (aImageVariation.mSeedType == theSeedType && aImageVariation.mDrawVariation == theDrawVariation)
			{
				aImage = aImageVariation.mImage;
				break;
			}
		}

		if (aImage == nullptr)
		{
			aImage = MakeCachedPlantFrame(theSeedType, theDrawVariation);
			ReanimCacheImageVariation aNewImageVariation;
			aNewImageVariation.mSeedType = theSeedType;
			aNewImageVariation.mDrawVariation = theDrawVariation;
			aNewImageVariation.mImage = aImage;
			mImageVariationList.AddHead(aNewImageVariation);
		}
	}
	else
	{
		aImage = mPlantImages[(int)theSeedType];
		if (aImage == nullptr)
		{
			aImage = MakeCachedPlantFrame(theSeedType, DrawVariation::VARIATION_NORMAL);
			mPlantImages[(int)theSeedType] = aImage;
		}
	}

	int aOffsetX, aOffsetY, aWidth, aHeight;
	GetPlantImageSize(theSeedType, aOffsetX, aOffsetY, aWidth, aHeight);
	if (!mApp->Is3DAccelerated() && g->mScaleX == 1.0f && g->mScaleY == 1.0f)
		g->DrawImage(aImage, thePosX + aOffsetX, thePosY + aOffsetY);
	else
		TodDrawImageScaledF(g, aImage, thePosX + (aOffsetX * g->mScaleX), thePosY + (aOffsetY * g->mScaleY), g->mScaleX, g->mScaleY);
}

//0x470110
void ReanimatorCache::DrawCachedMower(Graphics* g, float thePosX, float thePosY, LawnMowerType theMowerType)
{
	TOD_ASSERT(theMowerType >= 0 && theMowerType < LawnMowerType::NUM_MOWER_TYPES);
	
	if (mLawnMowers[(int)theMowerType] == nullptr)
		mLawnMowers[(int)theMowerType] = MakeCachedMowerFrame(theMowerType);
	TodDrawImageScaledF(g, mLawnMowers[(int)theMowerType], thePosX - 20.0f, thePosY, g->mScaleX, g->mScaleY);
}

//0x470170
void ReanimatorCache::DrawCachedZombie(Graphics* g, float thePosX, float thePosY, ZombieType theZombieType)
{
	TOD_ASSERT(theZombieType >= 0 && theZombieType < ZombieType::NUM_CACHED_ZOMBIE_TYPES);
	
	if (mZombieImages[(int)theZombieType] == nullptr)
		mZombieImages[(int)theZombieType] = MakeCachedZombieFrame(theZombieType);
	TodDrawImageScaledF(g, mZombieImages[(int)theZombieType], thePosX, thePosY, g->mScaleX, g->mScaleY);
}
