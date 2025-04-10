#include "Board.h"
#include "Cutscene.h"
#include "Challenge.h"
#include "SeedPacket.h"
#include "../LawnApp.h"
#include "CursorObject.h"
#include "../Resources.h"
#include "MessageWidget.h"
#include "../SexyAppFramework/Font.h"
#include "../Sexy.TodLib/FilterEffect.h"
#include "../SexyAppFramework/SexyMatrix.h"

SeedPacket::SeedPacket()
{
	mSlotMachiningPosition = 0.0f;
	mPacketType = SeedType::SEED_NONE;
	mImitaterType = SeedType::SEED_NONE;
	mIndex = -1;
	mSlotMachiningNextSeed = SeedType::SEED_NONE;
	mWidth = 50;
	mHeight = 70;
	mRefreshCounter = 0;
	mRefreshTime = 0;
	mRefreshing = false;
	mActive = true;
	mOffsetX = 0;
	mSlotMachineCountDown = 0;
	mSlotMachiningNextSeed = SeedType::SEED_NONE;
	mTimesUsed = 0;
}

//0x487070
void SeedPacket::PickNextSlotMachineSeed()
{
	int aPeasCount = mBoard->CountPlantByType(SeedType::SEED_PEASHOOTER);

	SeedType SLOT_SEED_TYPES[] = {
		SeedType::SEED_SUNFLOWER,
		SeedType::SEED_PEASHOOTER,
		SeedType::SEED_SNOWPEA,
		SeedType::SEED_WALLNUT,
		SeedType::SEED_SLOT_MACHINE_SUN,
		SeedType::SEED_SLOT_MACHINE_DIAMOND
	};

	int aSeedsCount = 0;
	TodWeightedArray aSeedWeightArray[(int)SeedType::NUM_SEED_TYPES];
	for (int i = 0; i < LENGTH(SLOT_SEED_TYPES); i++)
	{
		SeedType aSeedType = SLOT_SEED_TYPES[i];

		int aWeight = 100;
		if (aSeedType == SeedType::SEED_PEASHOOTER)
		{
			aWeight = TodAnimateCurve(0, 5, aPeasCount, 200, 100, TodCurves::CURVE_LINEAR);
		}
		else if (aSeedType == SeedType::SEED_SLOT_MACHINE_DIAMOND)
		{
			aWeight = 30;
		}

		if (mIndex == 2 && aSeedType != SeedType::SEED_SLOT_MACHINE_DIAMOND)
		{
			if (aSeedType == mBoard->mSeedBank->mSeedPackets[0].mSlotMachiningNextSeed || aSeedType == mBoard->mSeedBank->mSeedPackets[1].mSlotMachiningNextSeed)
			{
				aWeight += aWeight / 2;
			}
		}

		aSeedWeightArray[aSeedsCount].mItem = (int)aSeedType;
		aSeedWeightArray[aSeedsCount].mWeight = aWeight;
		aSeedsCount++;
	}

	mSlotMachiningNextSeed = (SeedType)TodPickFromWeightedArray(aSeedWeightArray, aSeedsCount);
}

void SeedPacket::SlotMachineStart()
{
	mSlotMachineCountDown = 300;
	mSlotMachiningPosition = 0.0f;
	PickNextSlotMachineSeed();
}

//0x487190
void SeedPacket::FlashIfReady()
{
	if (!CanPickUp() || mApp->mEasyPlantingCheat)
		return;

	if (!mBoard->HasConveyorBeltSeedBank())
	{
		int aRenderPosition = Board::MakeRenderOrder(RenderLayer::RENDER_LAYER_UI_BOTTOM, 0, 2);
		mApp->AddTodParticle(mX + mBoard->mSeedBank->mX, mY + mBoard->mSeedBank->mY, aRenderPosition, ParticleEffect::PARTICLE_SEED_PACKET_FLASH);
	}
	
	if (mBoard->mTutorialState == TutorialState::TUTORIAL_LEVEL_1_REFRESH_PEASHOOTER)
	{
		mBoard->SetTutorialState(TutorialState::TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER);
	}
	else if (mBoard->mTutorialState == TutorialState::TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER && mPacketType == SeedType::SEED_SUNFLOWER)
	{
		mBoard->SetTutorialState(TutorialState::TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER);
	}
	else if (mBoard->mTutorialState == TutorialState::TUTORIAL_MORESUN_REFRESH_SUNFLOWER && mPacketType == SeedType::SEED_SUNFLOWER)
	{
		mBoard->SetTutorialState(TutorialState::TUTORIAL_MORESUN_PICK_UP_SUNFLOWER);
	}
}

void SeedPacket::Activate()
{
	TOD_ASSERT(mPacketType != SeedType::SEED_NONE);
	mActive = true;
}

void SeedPacket::Deactivate()
{
	mActive = false;
	mRefreshCounter = 0;
	mRefreshTime = 0;
	mRefreshing = false;
}

void SeedPacket::SetActivate(bool theActive)
{
	if (theActive)
	{
		Activate();
	}
	else
	{
		Deactivate();
	}
}

//0x487250
void SeedPacket::Update()
{
	if (mApp->mGameScene != GameScenes::SCENE_PLAYING || mPacketType == SeedType::SEED_NONE)
	{
		return;
	}

	if (mBoard->mMainCounter == 0)
	{
		FlashIfReady();
	}

	if (!mActive && mRefreshing)
	{
		mRefreshCounter++;
		if (mRefreshCounter > mRefreshTime)
		{
			mRefreshCounter = 0;
			mRefreshing = false;
			Activate();
			FlashIfReady();
		}
	}

	if (mSlotMachineCountDown > 0)
	{
		mSlotMachineCountDown--;
		float aFlipsPerSecont = TodAnimateCurveFloat(SLOT_MACHINE_TIME, 0, mSlotMachineCountDown, 6.0f, 2.0f, TodCurves::CURVE_LINEAR);
		mSlotMachiningPosition += aFlipsPerSecont * 0.01f;

		if (mSlotMachiningPosition >= 1.0f)
		{
			mPacketType = mSlotMachiningNextSeed;
			if (mSlotMachineCountDown == 0)
			{
				Activate();
				mSlotMachiningPosition = 0.0f;
			}
			else
			{
				mSlotMachiningPosition -= 1.0f;
				PickNextSlotMachineSeed();
			}
		}
		else if (mSlotMachineCountDown == 0)
		{
			mSlotMachineCountDown = 1;
		}
	}
}

//0x487380
void SeedPacketDrawSeed(Graphics* g, float x, float y, SeedType theSeedType, SeedType theImitaterType, float theOffsetX, float theOffsetY, float theScale)
{
	Image* aImage = IMAGE_PACKET_PLANTS;
	SeedType aSeedType = theSeedType;
	if (theSeedType == SeedType::SEED_IMITATER && theImitaterType != SeedType::SEED_NONE)
	{
		aSeedType = theImitaterType;
		FilterEffect aFilterEffect = FilterEffect::FILTER_EFFECT_WASHED_OUT;
		if (theImitaterType == SeedType::SEED_HYPNOSHROOM || theImitaterType == SeedType::SEED_SQUASH || theImitaterType == SeedType::SEED_POTATOMINE ||
			theImitaterType == SeedType::SEED_GARLIC || theImitaterType == SeedType::SEED_LILYPAD)
			aFilterEffect = FilterEffect::FILTER_EFFECT_LESS_WASHED_OUT;
		aImage = FilterEffectGetImage(aImage, aFilterEffect);
	}

/*
	if (aSeedType == SeedType::SEED_POTATOMINE && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 0, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_CHOMPER && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 1, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_HYPNOSHROOM && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 2, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_TALLNUT && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 3, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_BLOVER && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 4, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_PUMPKINSHELL && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 5, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_CABBAGEPULT && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 6, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_KERNELPULT && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 7, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_MELONPULT && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 8, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_TWINSUNFLOWER && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 9, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_WINTERMELON && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 10, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_SPIKEROCK && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 11, 0, g->mScaleX, g->mScaleY);
	}
	else if (aSeedType == SeedType::SEED_COBCANNON && g->mScaleX <= 1.0f)
	{
		TodDrawImageCelScaledF(g, aImage, x, y, 12, 0, g->mScaleX, g->mScaleY);
	}
	
	else */

	{	
		Graphics aSeedG(*g);
		aSeedG.mScaleX = theScale * g->mScaleX;
		aSeedG.mScaleY = theScale * g->mScaleY;
		if (theSeedType == SEED_ZOMBIE_BUNGEE || theSeedType == SEED_VERSUS_BUNGEE)
		{
			aSeedG.mClipRect.mY = y + theOffsetY + 10;
			y -= 180;
		}

		Plant::DrawSeedType(&aSeedG, theSeedType, theImitaterType, DrawVariation::VARIATION_NORMAL, x + theOffsetX, y + theOffsetY);
	}
	
}

bool SeedPacket::IsZombiePack(SeedType theSeedType)
{
	if ((((LawnApp*)gSexyAppBase)->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES && theSeedType == SEED_GRAVE)) return false;
	if ((theSeedType >= SeedType::SEED_VERSUS_NORMAL && theSeedType <= SEED_VERSUS_GLADIANTUAR_GIGA)) return true;
	return false;
}

bool SeedPacket::IsLegacyPack(SeedType theSeedType)
{
	if ((theSeedType >= SeedType::SEED_PEASHOOTER && theSeedType <= SEED_MELONPULT)) return true;
	return false;
}

bool SeedPacket::IsLegacyNotAffectedbySuddenDeath(SeedType theSeedType)
{
	if (theSeedType == SeedType::SEED_WALLNUT || theSeedType == SeedType::SEED_TALLNUT || theSeedType == SeedType::SEED_PUMPKINSHELL || theSeedType == SeedType::SEED_VERSUS_TRASHCAN || theSeedType == SeedType::SEED_VERSUS_SCREENDOOR)
		return true;
	return false;
}

//0x4876F0
void DrawSeedPacket(Graphics* g, float x, float y, SeedType theSeedType, SeedType theImitaterType, float thePercentDark, int theGrayness, bool theDrawCost, bool theUseCurrentCost)
{
	SeedType aSeedType = theSeedType;
	if (aSeedType == SeedType::SEED_IMITATER && theImitaterType != SeedType::SEED_NONE)
	{
		aSeedType = theImitaterType;
	}

	if (theGrayness != 255)
	{
		g->SetColor(Color(theGrayness, theGrayness, theGrayness));
		g->SetColorizeImages(true);
	}
	else if (thePercentDark > 0)
	{
		g->SetColor(Color(128, 128, 128, 255));
		g->SetColorizeImages(true);
	}

	int aPacketBackground =
		theSeedType == SeedType::SEED_IMITATER ? 0 :
		theSeedType >= SeedType::SEED_PLASMAPEA && theSeedType <= SeedType::SEED_SHOOTINGSTAR ? 10 :
		Plant::IsUpgrade(aSeedType) ? 1 :
		theSeedType == SeedType::SEED_BEGHOULED_BUTTON_CRATER ? 3 :
		theSeedType == SeedType::SEED_BEGHOULED_BUTTON_SHUFFLE ? 4 :
		theSeedType == SeedType::SEED_SLOT_MACHINE_SUN ? 5 :
		theSeedType == SeedType::SEED_SLOT_MACHINE_DIAMOND ? 6 :
		theSeedType == SeedType::SEED_ZOMBIQUARIUM_SNORKLE ? 7 :
		theSeedType == SeedType::SEED_ZOMBIQUARIUM_TROPHY ? 8 :
		theSeedType >= SeedType::SEED_FLAMEPEA && theSeedType <= SeedType::SEED_EPEA ? 9 : 2;

	if (g->mScaleX > 1)
	{
		TodDrawImageCelScaledF(g, Sexy::IMAGE_SEEDPACKET_LARGER, x, y, 0, 0, g->mScaleX * 0.5f, g->mScaleY * 0.5f);
	}
	else
	{
		if (SeedPacket::IsZombiePack(theSeedType) || (((LawnApp*)gSexyAppBase)->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES && ((LawnApp*)gSexyAppBase)->mBoard && (theSeedType >= SEED_ZOMBIE_NORMAL && theSeedType <= SEED_ZOMBIE_ZOMBOSS || theSeedType == SEED_GRAVE)))
		{
			TodDrawImageScaledF(g, Sexy::IMAGE_ZOMBIE_PACK, x, y, g->mScaleX, g->mScaleY);
		}
		else
		{
			TodDrawImageCelScaledF(g, Sexy::IMAGE_SEEDS, x, y, aPacketBackground, 0, g->mScaleX, g->mScaleY);
		}
	}

	float aScale = 0.5f;
	bool aDrawSeedInMiddle = true;
	float aOffsetX = 5.0f;
	float aOffsetY = 8.0f;
	switch (aSeedType)
	{
	case SeedType::SEED_TALLNUT:
	case SeedType::SEED_VINENUT:
		aScale = 0.3f;
		aOffsetX = 13.0f;
		aOffsetY = 22.0f;
		break;

	case SeedType::SEED_INSTANT_COFFEE:
		aScale = 0.55f;
		aOffsetX = 0;
		aOffsetY = 9.0f;
		break;

	case SeedType::SEED_COBCANNON:
		aScale = 0.26f;
		aOffsetX = 6.0f;
		aOffsetY = 22.0f;
		break;

	case SeedType::SEED_CACTUS:
		aOffsetX = 9.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_REVERSE_CACTUS:
		aOffsetX = -1.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_ECACTUS:
		aScale = 0.4f;
		aOffsetX = 9.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_LEMON_NADE:
		aScale = 0.45f;
		aOffsetX = 6.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_SHRINK:
		aScale = 0.39f;
		aOffsetX = 4.0f;
		aOffsetY = 2.0f;
		break;

	case SeedType::SEED_AMPLI_FLOWER:
		aScale = 0.48f;
		aOffsetX = 4.0f;
		aOffsetY = 5.0f;
		break;

	case SeedType::SEED_BRAVESHROOM:
		aOffsetX = 7.0f;
		break;

	case SeedType::SEED_CHARD_GUARD:
		aScale = 0.345f;
		aOffsetX = 30.7f;
		aOffsetY = 59.5f;
		break;

	case SeedType::SEED_ALOEVERA:
		aScale = 0.45f;
		aOffsetX = 4.0f;
		aOffsetY = 8.0f;
		break;

	case SeedType::SEED_BONKCHOY:
		aScale = 0.37f;
		aOffsetX = 9.0f;
		aOffsetY = 24.0f;
		break;

	case SeedType::SEED_GHOSTPEPPER:
		aScale = 0.47f;
		aOffsetX = 7.0f;
		aOffsetY = 11.0f;
		break;

	case SeedType::SEED_OAK_ARCHER:
		aScale = 0.37f;
		aOffsetX = 3.0f;
		aOffsetY = 7.0f;
		break;

	case SeedType::SEED_THORNMOSS:
		aScale = 0.4f;
		aOffsetX = 8.0f;
		aOffsetY = 16.0f;
		break;

	case SeedType::SEED_POTATOMINE:
		aScale = 0.4f;
		aOffsetX = 8.0f;
		aOffsetY = 12.0f;
		break;

	case SeedType::SEED_MAGNETSHROOM:
		aOffsetY = 12.0f;
		break;

	case SeedType::SEED_FUMESHROOM:
	case SeedType::SEED_PUMPKINSHELL:
	case SeedType::SEED_CHOMPER:
	case SeedType::SEED_REVERSE_CHOMPER:
	case SeedType::SEED_DOOMSHROOM:
	case SeedType::SEED_SQUASH:
	case SeedType::SEED_HYPNOSHROOM:
	case SeedType::SEED_SPIKEWEED:
	case SeedType::SEED_SPIKEROCK:
	case SeedType::SEED_PLANTERN:
	case SeedType::SEED_TORCHWOOD:
	case SeedType::SEED_TANGLEKELP:
	case SeedType::SEED_SUPERCHOMP:
		aScale = 0.4f;
		aOffsetX = 8.0f;
		aOffsetY = 12.0f;
		break;

	case SeedType::SEED_FLAMEWOOD:
		aScale = 0.4f;
		aOffsetX = 8.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_FIRESHROOM:
		aScale = 0.45f;
		aOffsetX = 4.0f;
		aOffsetY =10.0f;
		break;

	case SeedType::SEED_PICKLEPEPPER:
		aScale = 0.45f;
		aOffsetX = 8.0f;
		aOffsetY = 11.0f;
		break;

	case SeedType::SEED_TWINSUNFLOWER:
	case SeedType::SEED_GLOOMSHROOM:
		aScale = 0.45f;
		aOffsetX = 7.0f;
		aOffsetY = 14.0f;
		break;

	case SeedType::SEED_CATTAIL:
		aScale = 0.45f;
		aOffsetX = 8.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_UMBRELLA:
		aScale = 0.5f;
		aOffsetX = 5.0f;
		aOffsetY = 10.0f;
		break;

	case SeedType::SEED_KERNELPULT:
		aScale = 0.4f;
		aOffsetX = 13.0f;
		aOffsetY = 14.0f;
		break;

	case SeedType::SEED_CABBAGEPULT:
		aScale = 0.4f;
		aOffsetX = 15.0f;
		aOffsetY = 14.0f;
		break;

	case SeedType::SEED_PEPPER:
		aScale = 0.45f;
		aOffsetX = 14.0f;
		aOffsetY = 14.0f;
		break;

	case SeedType::SEED_PULTSHROOM:
		aScale = 0.47f;
		aOffsetX = 9.0f;
		aOffsetY = 12.0f;
		break;

	case SeedType::SEED_LUMESHROOM:
		aScale = 0.40f;
		aOffsetX = 8.0f;
		aOffsetY = 14.5f;
		break;

	case SeedType::SEED_MORTARSHROOM:
		aScale = 0.425f;
		aOffsetX = 7.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_BLOODORANGE:
		aScale = 0.45f;
		aOffsetX = 7.0f;
		aOffsetY = 17.0f;
		break;

	case SeedType::SEED_MELONPULT:
	case SeedType::SEED_WINTERMELON:
		aScale = 0.35f;
		aOffsetX = 18.0f;
		aOffsetY = 19.0f;
		break;

	case SeedType::SEED_GRAVEBUSTER:
		aScale = 0.4f;
		aOffsetX = 10.0f;
		aOffsetY = 15.0f;
		break;

	case SeedType::SEED_SPLITPEA:
		aScale = 0.45f;
		aOffsetX = 12.0f;
		aOffsetY = 12.0f;
		break;

	case SeedType::SEED_HURRIKALE:
		aScale = 1.0f;
		aOffsetX = 8.0f;
		aOffsetY = 17.0f;

	case SeedType::SEED_BLOVER:
		aScale = 0.4f;
		aOffsetX = 8.0f;
		aOffsetY = 17.0f;
		break;

	case SeedType::SEED_REED:
		aScale = 0.44f;
		aOffsetX = 8.4f;
		aOffsetY = 13.5f;
		break;

	case SeedType::SEED_ICYFUME:
		aScale = 0.41f;
		aOffsetX = 8.0f;
		aOffsetY = 13.0f;
		break;

	case SeedType::SEED_STARFRUIT:
	case SeedType::SEED_REVERSE_STARFRUIT:
		aScale = 0.5f;
		aOffsetX = 6.0f;
		aOffsetY = 8.0f;
		break;

	case SeedType::SEED_THREEPEATER:
	case SeedType::SEED_REVERSE_THREEPEATER:
		aScale = 0.5f;
		aOffsetX = 5.0f;
		aOffsetY = 10.0f;
		break;

	case SeedType::SEED_GATLINGPEA:
		aScale = 0.5f;
		aOffsetX = 2.0f;
		aOffsetY = 8.0f;
		break;

	case SeedType::SEED_WATERPOT:
		aScale = 0.4f;
		aOffsetX = 8.0f;
		aOffsetY = 16.0f;
		break;

	case SeedType::SEED_ZOMBIE_NORMAL:
	case SeedType::SEED_ZOMBIE_TRAFFIC_CONE:
	case SeedType::SEED_ZOMBIE_PAIL:
	case SeedType::SEED_ZOMBIE_DANCER:
	case SeedType::SEED_ZOMBIE_SCARECROW:
	case SeedType::SEED_VERSUS_NORMAL:
	case SeedType::SEED_VERSUS_CONEHEAD:
	case SeedType::SEED_VERSUS_BUCKET:
	case SeedType::SEED_VERSUS_DANCER:
	case SeedType::SEED_VERSUS_SCARECROW:
	case SeedType::SEED_VERSUS_FLAG:
	case SeedType::SEED_VERSUS_NEWSPAPER:
	case SeedType::SEED_VERSUS_JACK:
	case SeedType::SEED_VERSUS_VAMPIRE:
	case SeedType::SEED_VERSUS_BACKUP:
	case SeedType::SEED_VERSUS_LEAFBLOWER:
	case SeedType::SEED_VERSUS_FISHERMAN:
	case SeedType::SEED_VERSUS_HUNTER:	
		aScale = 0.35f;
		aOffsetX = -3.0f;
		aOffsetY = -7.0f;
		break;


	case SeedType::SEED_ZOMBIE_ICE:
	case SeedType::SEED_VERSUS_ICE:
		aScale = 0.30f;
		aOffsetX = -3.0f;
		aOffsetY = 2.0f;
		break;

	case SeedType::SEED_VERSUS_SNORKEL:
		aScale = 0.30f;
		aOffsetX = 0.0f;
		aOffsetY = -4.0f;
		break;


	case SeedType::SEED_ZOMBIE_POLEVAULTER:
	case SeedType::SEED_VERSUS_POLE:
	case SeedType::SEED_ZOMBIE_SNORKEL:
		aScale = 0.35f;
		aOffsetX = -8.0f;
		aOffsetY = -12.0f;
		break;

	case SeedType::SEED_ZOMBIE_LADDER:
	case SeedType::SEED_ZOMBIE_DIGGER:
	case SeedType::SEED_ZOMBIE_SCREEN_DOOR:
	case SeedType::SEED_ZOMBIE_POGO:
	case SeedType::SEED_VERSUS_LADDER:
	case SeedType::SEED_VERSUS_DIGGER:
	case SeedType::SEED_VERSUS_SCREENDOOR:
	case SeedType::SEED_VERSUS_TRASHCAN:
	case SeedType::SEED_VERSUS_POGO:
		aScale = 0.35f;
		aOffsetX = -3.0f;
		aOffsetY = -10.0f;
		break;

	case SeedType::SEED_ZOMBIE_BUNGEE:
	case SeedType::SEED_VERSUS_BUNGEE:
		aScale = 0.3f;
		aOffsetX = 1.0f;
		aOffsetY = -1.0f;
		break;

	case SeedType::SEED_ZOMBIE_FOOTBALL:
	case SeedType::SEED_ZOMBIE_GIGA_FOOTBALL:
	case SeedType::SEED_VERSUS_FOOTBALL:
	case SeedType::SEED_VERSUS_FOOTBALL_GIGA:
		aScale = 0.33f;
		aOffsetX = -7.0f;
		aOffsetY = -6.0f;
		break;

	case SeedType::SEED_VERSUS_LUMBERJACK:
		aScale = 0.31f;
		aOffsetX = 0.0f;
		aOffsetY = -2.0f;
		break;

	case SeedType::SEED_VERSUS_DOLPHIN:
		aScale = 0.35f;
		aOffsetX = 0.0f;
		aOffsetY = -12.0f;
		break;

	case SeedType::SEED_ZOMBIE_BALLOON:
	case SeedType::SEED_VERSUS_BALLOON:
		aScale = 0.35f;
		aOffsetX = -3.0f;
		aOffsetY = -5.0f;
		break;

	case SeedType::SEED_ZOMBIE_IMP:
	case SeedType::SEED_VERSUS_IMP:
		aScale = 0.4f;
		aOffsetX = -12.0f;
		aOffsetY = -17.0f;
		break;

	case SeedType::SEED_ZOMBONI:
	case SeedType::SEED_VERSUS_ZOMBONI:
		aScale = 0.23f;
		aOffsetX = 7.0f;
		aOffsetY = 3.0f;
		break;

	case SeedType::SEED_VERSUS_CATAPULT:
		aScale = 0.23f;
		aOffsetX = 1.0f;
		aOffsetY = 3.0f;
		break;

	case SeedType::SEED_ZOMBIE_GARGANTUAR:
	case SeedType::SEED_VERSUS_GARGANTUAR:
	case SeedType::SEED_VERSUS_GARGANTUAR_GIGA:
		aScale = 0.23f;
		aOffsetX = 4.0f;
		aOffsetY = 8.0f;
		break;

	case SeedType::SEED_VERSUS_GLADIANTUAR:
		aScale = 0.25f;
		aOffsetX = 4.0f;
		aOffsetY = 6.0f;
		break;

	case SeedType::SEED_VERSUS_GLADIANTUAR_GIGA:
		aScale = 0.5f;
		aOffsetX = 4.0f;
		aOffsetY = 6.0f;
		break;

	case SeedType::SEED_ZOMBIE_ZOMBOSS:
	case SeedType::SEED_VERSUS_ZOMBOSS:
		aScale = 0.25f;
		aOffsetX = 0.0f;
		aOffsetY = 0.0f;
		break;

	case SeedType::SEED_BEGHOULED_BUTTON_SHUFFLE:
	case SeedType::SEED_BEGHOULED_BUTTON_CRATER:
	case SeedType::SEED_SLOT_MACHINE_SUN:
	case SeedType::SEED_SLOT_MACHINE_DIAMOND:
	case SeedType::SEED_ZOMBIQUARIUM_SNORKLE:
	case SeedType::SEED_ZOMBIQUARIUM_TROPHY:
		aDrawSeedInMiddle = false;
		break;
	}
	if (((LawnApp*)gSexyAppBase)->mGameMode == GameMode::GAMEMODE_CHALLENGE_BIG_TIME)
	{
		if (aSeedType == SeedType::SEED_WALLNUT || aSeedType == SeedType::SEED_SUNFLOWER || aSeedType == SeedType::SEED_MARIGOLD)
		{
			aOffsetX = 16.0f;
			aOffsetY = 34.0f;
		}
	}
	if (aSeedType == SeedType::SEED_GIANT_WALLNUT)
	{
		aScale *= 0.75f;
		aOffsetX = 52.0f;
		aOffsetY = 58.0f;
	}
	aOffsetX = g->mScaleX * aOffsetX;
	aOffsetY = g->mScaleY * (aOffsetY + 1.0f);
	if (aDrawSeedInMiddle)
	{
		Graphics aSeedpacketG(*g);
		aSeedpacketG.ClipRect(x, y, SEED_PACKET_WIDTH, SEED_PACKET_HEIGHT - 16.0f);
		SeedPacketDrawSeed(&aSeedpacketG, x, y, theSeedType, theImitaterType, aOffsetX, aOffsetY, aScale);
	}

	if (thePercentDark > 0.0f)
	{
		int aDarknessHeight = FloatRoundToInt(68.0f * thePercentDark) + 2;
		Graphics aPlantG(*g);
		aPlantG.SetColor(Color(64, 64, 64, 255));
		aPlantG.SetColorizeImages(true);
		aPlantG.ClipRect(x, y, SEED_PACKET_WIDTH, aDarknessHeight);

		if (((LawnApp*)gSexyAppBase)->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES && ((LawnApp*)gSexyAppBase)->mBoard)
		{
			TodDrawImageScaledF(&aPlantG, Sexy::IMAGE_ZOMBIE_PACK, x, y, aPlantG.mScaleX, aPlantG.mScaleY);
		}
		else 
		{
			TodDrawImageCelScaledF(&aPlantG, Sexy::IMAGE_SEEDS, x, y, aPacketBackground, 0, aPlantG.mScaleX, aPlantG.mScaleY);
		}

		if (aDrawSeedInMiddle)
		{
			SeedPacketDrawSeed(&aPlantG, x, y, theSeedType, theImitaterType, aOffsetX, aOffsetY, aScale);
		}
	}

	if (theDrawCost)
	{
		SexyString aCostStr;
		if (gLawnApp->mBoard && gLawnApp->mBoard->PlantUsesAcceleratedPricing(aSeedType))
		{
			if (theUseCurrentCost)
			{
				aCostStr = StrFormat(_S("%d"), gLawnApp->mBoard->GetCurrentPlantCost(theSeedType, theImitaterType));
			}
			else
			{
				aCostStr = StrFormat(_S("%d+"), Plant::GetCost(theSeedType, theImitaterType));
			}
		}
		else
		{
			aCostStr = StrFormat(_S("%d"), Plant::GetCost(theSeedType, theImitaterType));
		}

		Font* aTextFont = Sexy::FONT_BRIANNETOD12;
		int aTextOffsetX = 32 - aTextFont->StringWidth(aCostStr); //32
		int aTextOffsetY = aTextFont->GetAscent() + 52; //54
		if (g->mScaleX == 1.0f && g->mScaleY == 1.0f)
		{
			TodDrawString(g, aCostStr, x + aTextOffsetX, y + aTextOffsetY, aTextFont, Color::Black, DS_ALIGN_LEFT);
		}
		else
		{
			SexyMatrix3 aMatrix;
			TodScaleTransformMatrix(aMatrix, aTextOffsetX * g->mScaleX + x, aTextOffsetY * g->mScaleY + y, g->mScaleX, g->mScaleY);
			if (g->mScaleX > 1.8f)
			{
				g->SetLinearBlend(false);
			}
			TodDrawStringMatrix(g, aTextFont, aMatrix, aCostStr, Color::Black);
			g->SetLinearBlend(true);
		}
	}

	g->SetColorizeImages(false);
}

//0x488220
void SeedPacket::Draw(Graphics* g)
{
	float aPercentDark = 0.0f;
	if (!mActive)
	{
		if (mRefreshTime == 0)
		{
			aPercentDark = 1.0f;
		}
		else
		{
			aPercentDark = (float)(mRefreshTime - mRefreshCounter) / (float)mRefreshTime;
		}
	}

	if (mSlotMachineCountDown > 0)
	{
		int aOffsetY = FloatRoundToInt(-mHeight * mSlotMachiningPosition);

		Graphics aClipG(*g);
		aClipG.ClipRect(0, 0, mWidth, mHeight);

		DrawSeedPacket(&aClipG, 0.0f, aOffsetY, mPacketType, SeedType::SEED_NONE, 0.0f, 128, false, false);
		DrawSeedPacket(&aClipG, 0.0f, mHeight + aOffsetY, mSlotMachiningNextSeed, SeedType::SEED_NONE, 0.0f, 128, false, false);
	}
	else
	{
		SeedType aUseSeedType = mPacketType;
		if (mPacketType == SeedType::SEED_IMITATER && mImitaterType != SeedType::SEED_NONE)
		{
			aUseSeedType = mImitaterType;
		}

		bool aDrawCost = true;
		if (mBoard->HasConveyorBeltSeedBank() || mApp->IsSlotMachineLevel())
		{
			aDrawCost = false;
		}
		int aCost = mBoard->GetCurrentPlantCost(mPacketType, mImitaterType);

		int aGrayness = 255;
		if ((mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED && !mActive) ||
			(mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST && !mActive))
		{
			aGrayness = 64;
		}
		else if (mApp->mGameScene != GameScenes::SCENE_PLAYING)
		{
			aGrayness = mBoard->mSeedBank->mCutSceneDarken;
			aPercentDark = 0.0f;
		}
		else if (mBoard->mTutorialState == TutorialState::TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER && mBoard->mTutorialTimer == -1 && mPacketType == SeedType::SEED_PEASHOOTER)
		{
			aGrayness = GetFlashingColor(mBoard->mMainCounter, 75).mRed;
		}
		else if (mBoard->mTutorialState == TutorialState::TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER && mPacketType == SeedType::SEED_SUNFLOWER)
		{
			aGrayness = GetFlashingColor(mBoard->mMainCounter, 75).mRed;
		}
		else if (mBoard->mTutorialState == TutorialState::TUTORIAL_MORESUN_PICK_UP_SUNFLOWER && mPacketType == SeedType::SEED_SUNFLOWER)
		{
			aGrayness = GetFlashingColor(mBoard->mMainCounter, 75).mRed;
		}
		else if (mBoard->mTutorialState == TutorialState::TUTORIAL_WHACK_A_ZOMBIE_PICK_SEED)
		{
			aGrayness = GetFlashingColor(mBoard->mMainCounter, 75).mRed;
		}
		else if (mApp->mEasyPlantingCheat)
		{
			aPercentDark = 0.0f;
		}
		else if (mApp->mGameMode == GAMEMODE_CHALLENGE_BOMBALL && mBoard->mBombAllCounter <= 0 && aUseSeedType != SEED_WALLNUT && aUseSeedType != SEED_INSTANT_COFFEE)
		{
			aGrayness = 128;
		}
		else if (mApp->IsVersusLevel() && mBoard->mBoardAge >= 30000 && (aUseSeedType == SEED_SUNFLOWER || aUseSeedType == SEED_GRAVE))
		{
			aGrayness = 128;
		}
		else if (mBoard->mLevelAwardSpawned && mApp->IsVersusLevel())
		{
			aGrayness = 128;
		}
		else if ((!mBoard->CanTakeSunMoney(aCost) && aDrawCost && !SeedPacket::IsZombiePack(aUseSeedType)) || (!mBoard->CanTakeBrainMoney(aCost) && aDrawCost && SeedPacket::IsZombiePack(aUseSeedType)) ||
			aPercentDark > 1.0f || !mBoard->PlantingRequirementsMet(aUseSeedType))
		{
			aGrayness = 128;
		}
		DrawSeedPacket(g, mOffsetX, 0.0f, mPacketType, mImitaterType, aPercentDark, aGrayness, aDrawCost, true);
	}
}

//0x488500
bool SeedPacket::CanPickUp()
{
	if (mBoard->mPaused || mApp->mGameScene != GameScenes::SCENE_PLAYING || mPacketType == SeedType::SEED_NONE)
	{
		return false;
	}

	SeedType aUseSeedType = mPacketType;
	if (mPacketType == SeedType::SEED_IMITATER && mImitaterType != SeedType::SEED_NONE)
	{
		aUseSeedType = mImitaterType;
	}

	if (mApp->IsSlotMachineLevel())
	{
		return false;
	}

	if (!mApp->mEasyPlantingCheat)
	{
		if (!mActive)
		{
			return false;
		}

		int aCost = mBoard->GetCurrentPlantCost(mPacketType, mImitaterType);
		if (!mBoard->CanTakeSunMoney(aCost) && !mBoard->HasConveyorBeltSeedBank() && !IsZombiePack(mPacketType))
		{
			return false;
		}

		if (!mBoard->CanTakeBrainMoney(aCost) && !mBoard->HasConveyorBeltSeedBank() && IsZombiePack(mPacketType))
		{
			return false;
		}

		if (!mBoard->PlantingRequirementsMet(aUseSeedType))
		{
			return false;
		}
	}

	return true;
}

//0x488590
void SeedPacket::MouseDown(int x, int y, int theClickCount)
{

	if (mBoard->mPaused || mApp->mGameScene != GameScenes::SCENE_PLAYING || mPacketType == SeedType::SEED_NONE)
	{
		return;
	}

	if (mApp->IsSlotMachineLevel())
	{
		if (!mBoard->mAdvice->IsBeingDisplayed())
		{
			mBoard->DisplayAdvice(_S("[ADVICE_SLOT_MACHINE_PULL]"), MessageStyle::MESSAGE_STYLE_HINT_TALL_FAST, AdviceType::ADVICE_NONE);
		}
		mBoard->mChallenge->mSlotMachineRollCount = min(mBoard->mChallenge->mSlotMachineRollCount, 2);
		return;
	}

	SeedType aUseSeedType = mPacketType;
	if (mPacketType == SeedType::SEED_IMITATER && mImitaterType != SeedType::SEED_NONE)
	{
		aUseSeedType = mImitaterType;
	}
	else if (mPacketType == SeedType::SEED_ZOMBIE_ZOMBOSS)
	{
		if (mBoard->mSunMoney >= 1000)
		{
			mBoard->AddZombie(ZOMBIE_BOSS, 0);
			mBoard->mSunMoney -= 1000;
		}
		else mApp->PlaySample(SOUND_BUZZER);
		return;
	}

	if (!mApp->mEasyPlantingCheat)
	{
		if (!mActive)
		{
			mApp->PlaySample(SOUND_BUZZER);
			if (mApp->IsFirstTimeAdventureMode() && mBoard->mLevel == 1 && mBoard->mHelpDisplayed[(int)AdviceType::ADVICE_CLICK_ON_SUN])
			{
				mBoard->DisplayAdvice(_S("[ADVICE_SEED_REFRESH]"), MessageStyle::MESSAGE_STYLE_TUTORIAL_LEVEL1, AdviceType::ADVICE_SEED_REFRESH);
			}
			return;
		}

		/*
		if (((!mBoard->CanTakeSunMoney(aCost) && !IsZombiePack(aUseSeedType)) || (!mBoard->CanTakeBrainMoney(aCost) && IsZombiePack(aUseSeedType)) && !mBoard->HasConveyorBeltSeedBank()) || 
			(mBoard->mBombAllCounter == 0 && mApp->mGameMode == GAMEMODE_CHALLENGE_BOMBALL && aUseSeedType != SEED_WALLNUT && aUseSeedType != SEED_INSTANT_COFFEE) ||
			(mBoard->mLevelAwardSpawned && mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_VERSUS))*/
		int aCost = mBoard->GetCurrentPlantCost(mPacketType, mImitaterType);

		//bool isAllowed = !mBoard->CanTakeSunMoney(aCost) && !mBoard->HasConveyorBeltSeedBank();
		bool isAllowed = ((!mBoard->CanTakeSunMoney(aCost) && !IsZombiePack(aUseSeedType)) || (!mBoard->CanTakeBrainMoney(aCost) && IsZombiePack(aUseSeedType))) && !mBoard->HasConveyorBeltSeedBank();
		if (!isAllowed) {
			if (mApp->mGameMode == GAMEMODE_CHALLENGE_BOMBALL && mBoard->mBombAllCounter == 0 && mPacketType != SEED_WALLNUT && mPacketType != SEED_INSTANT_COFFEE)
			{
				isAllowed = true;
			}
			else if (mApp->IsVersusLevel() && mBoard->mBoardAge >= 30000 && (aUseSeedType == SEED_SUNFLOWER || aUseSeedType == SEED_GRAVE))
			{
				isAllowed = true;
			}
			else if (mApp->IsVersusLevel() && mBoard->mLevelAwardSpawned)
			{
				isAllowed = true;
			}
			if ((!mApp->mIsKeyboardPlayer1 && SeedPacket::IsZombiePack(aUseSeedType)) && !mApp->mDebugKeysEnabled)
			{
				isAllowed = true;
			}
			else if ((mApp->mIsKeyboardPlayer1 && !SeedPacket::IsZombiePack(aUseSeedType)) && !mApp->mDebugKeysEnabled)
			{
				isAllowed = true;
			}
		}

		if (isAllowed && (!mBoard->HasConveyorBeltSeedBank() || mApp->mGameMode == GAMEMODE_CHALLENGE_BOMBALL))
		{
			mApp->PlaySample(SOUND_BUZZER);
			mBoard->mOutOfMoneyCounter = 70;
			if (mApp->IsFirstTimeAdventureMode() && mBoard->mLevel == 1 && mBoard->mHelpDisplayed[(int)AdviceType::ADVICE_CLICK_ON_SUN])
			{
				mBoard->DisplayAdvice(_S("[ADVICE_CANT_AFFORD_PLANT]"), MessageStyle::MESSAGE_STYLE_TUTORIAL_LEVEL1, AdviceType::ADVICE_CANT_AFFORD_PLANT);
			}
			return;
		}

		if (!mBoard->PlantingRequirementsMet(aUseSeedType))
		{
			mApp->PlaySample(SOUND_BUZZER);
			if (aUseSeedType == SeedType::SEED_GATLINGPEA)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_REPEATER]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_REPEATER);
			}
			else if (aUseSeedType == SeedType::SEED_WINTERMELON)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_MELONPULT]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_MELONPULT);
			}
			else if (aUseSeedType == SeedType::SEED_TWINSUNFLOWER)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_SUNFLOWER]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_SUNFLOWER);
			}
			else if (aUseSeedType == SeedType::SEED_SPIKEROCK)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_SPIKEWEED]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_SPIKEWEED);
			}
			else if (aUseSeedType == SeedType::SEED_COBCANNON)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_KERNELPULT]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_KERNELPULT);
			}
			else if (aUseSeedType == SeedType::SEED_FLAMEWOOD)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_TORCHWOOD]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_KERNELPULT);
			}
			else if (aUseSeedType == SeedType::SEED_GOLD_MAGNET)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_MAGNETSHROOM]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_MAGNETSHROOM);
			}
			else if (aUseSeedType == SeedType::SEED_QUEENPEA)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_SNOWPEA]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_MAGNETSHROOM);
			}
			else if (aUseSeedType == SeedType::SEED_PLASMAPEA)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_FLAMEPEA]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_MAGNETSHROOM);
			}
			else if (aUseSeedType == SeedType::SEED_SHOOTINGSTAR)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_STARFRUIT]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_MAGNETSHROOM);
			}
			else if (aUseSeedType == SeedType::SEED_GLOOMSHROOM || aUseSeedType == SeedType::SEED_ICYFUME)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_FUMESHROOM]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_FUMESHROOM);
			}
			else if (aUseSeedType == SeedType::SEED_CATTAIL)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_LILYPAD]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_LILYPAD);
			}
			else if (aUseSeedType == SeedType::SEED_SUPERCHOMP)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_CHOMPER]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_LILYPAD);
			}
			else if (aUseSeedType == SeedType::SEED_VINENUT)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_CHOMPER]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_LILYPAD);
			}
			else if (aUseSeedType == SeedType::SEED_THORNMOSS)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_CHOMPER]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_LILYPAD);
			}
			else if (aUseSeedType == SeedType::SEED_BRAVESHROOM)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_CHOMPER]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_LILYPAD);
			}
			else if (aUseSeedType == SeedType::SEED_ECACTUS)
			{
				mBoard->DisplayAdvice(_S("[ADVICE_PLANT_NEEDS_CHOMPER]"), MessageStyle::MESSAGE_STYLE_HINT_LONG, AdviceType::ADVICE_PLANT_NEEDS_LILYPAD);
			}
			else
			{
				TOD_ASSERT();
			}

			return;
		}
	}

	mBoard->ClearAdvice(AdviceType::ADVICE_CANT_AFFORD_PLANT);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_REPEATER);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_MELONPULT);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_SUNFLOWER);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_KERNELPULT);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_SPIKEWEED);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_MAGNETSHROOM);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_FUMESHROOM);
	mBoard->ClearAdvice(AdviceType::ADVICE_PLANT_NEEDS_LILYPAD);

	if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST)
	{
		mBoard->mChallenge->BeghouledPacketClicked(this);
	}
	else if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM)
	{
		mBoard->mChallenge->ZombiquariumPacketClicked(this);
	}
	else
	{
		mBoard->mCursorObject->mType = mPacketType;
		mBoard->mCursorObject->mImitaterType = mImitaterType;
		mBoard->mCursorObject->mCursorType = CursorType::CURSOR_TYPE_PLANT_FROM_BANK;
		mBoard->mCursorObject->mSeedBankIndex = mIndex;
		mApp->PlaySample(SOUND_SEEDLIFT);

		if (mBoard->mTutorialState == TutorialState::TUTORIAL_LEVEL_1_PICK_UP_PEASHOOTER)
		{
			mBoard->SetTutorialState(TutorialState::TUTORIAL_LEVEL_1_PLANT_PEASHOOTER);
		}
		else if (mBoard->mTutorialState == TutorialState::TUTORIAL_LEVEL_2_PICK_UP_SUNFLOWER)
		{
			if (mPacketType == SeedType::SEED_SUNFLOWER)
			{
				mBoard->SetTutorialState(TutorialState::TUTORIAL_LEVEL_2_PLANT_SUNFLOWER);
			}
			else
			{
				mBoard->SetTutorialState(TutorialState::TUTORIAL_LEVEL_2_REFRESH_SUNFLOWER);
			}
		}
		else if (mBoard->mTutorialState == TutorialState::TUTORIAL_MORESUN_PICK_UP_SUNFLOWER)
		{
			if (mPacketType == SeedType::SEED_SUNFLOWER)
			{
				mBoard->SetTutorialState(TutorialState::TUTORIAL_MORESUN_PLANT_SUNFLOWER);
			}
			else
			{
				mBoard->SetTutorialState(TutorialState::TUTORIAL_MORESUN_REFRESH_SUNFLOWER);
			}
		}
		else if (mBoard->mTutorialState == TutorialState::TUTORIAL_WHACK_A_ZOMBIE_PICK_SEED || mBoard->mTutorialState == TutorialState::TUTORIAL_WHACK_A_ZOMBIE_BEFORE_PICK_SEED)
		{
			mBoard->SetTutorialState(TutorialState::TUTORIAL_WHACK_A_ZOMBIE_COMPLETED);
		}

		Deactivate();
	}
}

//0x488EC0
void SeedPacket::WasPlanted()
{
	TOD_ASSERT(mPacketType != SeedType::SEED_NONE);

	if (mBoard->HasConveyorBeltSeedBank())
	{
		mBoard->mSeedBank->RemoveSeed(mIndex);
	}
	else if (mApp->IsSlotMachineLevel())
	{
		Deactivate();
	}
	else if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND && mBoard->mChallenge->mChallengeState != ChallengeState::STATECHALLENGE_LAST_STAND_ONSLAUGHT)
	{
		mTimesUsed++;
		mActive = true;
		FlashIfReady();
	}
	else
	{
		mTimesUsed++;
		mRefreshing = true;
		mRefreshTime = Plant::GetRefreshTime(mPacketType, mImitaterType);
	}
}

//0x488F90
bool SeedPacket::MouseHitTest(int theX, int theY, HitResult* theHitResult)
{
	if (mSlotMachineCountDown > 0 || mPacketType == SeedType::SEED_NONE)
	{
		theHitResult->mObject = nullptr;
		theHitResult->mObjectType = GameObjectType::OBJECT_TYPE_NONE;
		return false;
	}

	if (theX >= mX + mOffsetX && theX < mX + mOffsetX + mWidth && theY >= mY && theY < mY + mHeight)
	{
		theHitResult->mObject = this;
		theHitResult->mObjectType = GameObjectType::OBJECT_TYPE_SEEDPACKET;
		return true;
	}

	theHitResult->mObject = nullptr;
	theHitResult->mObjectType = GameObjectType::OBJECT_TYPE_NONE;
	return false;
}

//0x489000
SeedBank::SeedBank()
{
	mWidth = IMAGE_SEEDBANK->GetWidth();
	mHeight = IMAGE_SEEDBANK->GetHeight();

	mNumPackets = 0;
	mConveyorBeltCounter = 0;
	mCutSceneDarken = 255;
}

//0x489630
void SeedBank::Draw(Graphics* g)
{
	if (mBoard->mCutScene && mBoard->mCutScene->IsBeforePreloading())
	{
		return;
	}

	if (mApp->mGameScene != GameScenes::SCENE_PLAYING)
	{
		g->mTransX -= mBoard->mX;
		g->mTransY -= mBoard->mY;
	}

	if (mApp->IsSlotMachineLevel())
	{
		g->DrawImage(IMAGE_SUNBANK, 0, 0);
	}
	else if (mBoard->HasConveyorBeltSeedBank())
	{
		g->DrawImage(IMAGE_CONVEYORBELT_BACKDROP, 83, 0);
		g->DrawImageCel(IMAGE_CONVEYORBELT, 90, 63, mConveyorBeltCounter / 4 % 6);
		g->SetClipRect(90, 0, 501, BOARD_HEIGHT);
	}
	else
	{
		int aExtraWidth = mBoard->GetSeedBankExtraWidth();
		if (mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES)
		{
			Rect theSrcRect(IMAGE_BRAINBANK->mWidth - aExtraWidth - 12, 0, aExtraWidth + 12, IMAGE_BRAINBANK->mHeight);
			g->DrawImage(IMAGE_BRAINBANK, 0, 0);
			g->DrawImage(IMAGE_BRAINBANK, IMAGE_BRAINBANK->mWidth - 12, 0, theSrcRect);
		}
		else
		{
			Rect theSrcRect(IMAGE_SEEDBANK->mWidth - aExtraWidth - 12, 0, aExtraWidth + 12, IMAGE_SEEDBANK->mHeight);
			if (!mApp->IsVersusLevel())
			{
				g->DrawImage(IMAGE_SEEDBANK, 0, 0);
				g->DrawImage(IMAGE_SEEDBANK, IMAGE_SEEDBANK->mWidth - 12, 0, theSrcRect);
			}
			else
			{
				g->DrawImage(IMAGE_SEEDBANK_SMALL, -10, 0);
				g->DrawImage(IMAGE_BRAINBANK_SMALL, 385, 0);
			}
				
				
		}
	}

	for (int i = 0; i < mNumPackets; i++)
	{
		SeedPacket* aSeedPacket = &mSeedPackets[i];
		if (aSeedPacket->mPacketType != SeedType::SEED_NONE && aSeedPacket->BeginDraw(g))
		{
			aSeedPacket->Draw(g);
			aSeedPacket->EndDraw(g);
		}
	}

	g->ClearClipRect();
	if (mApp->IsSlotMachineLevel() && mY > -IMAGE_SEEDBANK->GetHeight())
	{
		g->DrawImage(IMAGE_SLOTMACHINE_OVERLAY, 189, -2);
	}

	if (!mBoard->HasConveyorBeltSeedBank())
	{
		SexyString aSunMoneyLabel = StrFormat(_S("%d"), max(mBoard->mSunMoney, 0)); //teleport sun count
		Color aMoneyColor(0, 0, 0);

		SexyString aBrainMoneyLabel = StrFormat(_S("%d"), max(mBoard->mBrainMoney, 0)); //teleport sun count

		if (mBoard->mOutOfMoneyCounter > 0 && mBoard->mOutOfMoneyCounter % 20 < 10)
		{
			aMoneyColor = Color(255, 0, 0);
		}
		
		if (mApp->IsVersusLevel())
		{
			TodDrawString(g, aSunMoneyLabel, 24, 78, FONT_CONTINUUMBOLD14, aMoneyColor, DrawStringJustification::DS_ALIGN_CENTER);
			TodDrawString(g, aBrainMoneyLabel, 735, 78, FONT_CONTINUUMBOLD14, aMoneyColor, DrawStringJustification::DS_ALIGN_CENTER);
		}
		else
		{
			TodDrawString(g, aSunMoneyLabel, 34, 78, FONT_CONTINUUMBOLD14, aMoneyColor, DrawStringJustification::DS_ALIGN_CENTER);
		}
	}

	if (mApp->mGameScene != GameScenes::SCENE_PLAYING)
	{
		g->mTransX += mBoard->mX;
		g->mTransY += mBoard->mY;
	}

	if ((mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop) && mApp->mGameScene == SCENE_PLAYING) {
		for (int i = 0; i < mNumPackets; i++)
		{
			bool willSkip = false;
			for (int playerID = 0; playerID < 2; playerID++) {
				if (mBoard->mPlayer2->mSeedBankIndex == i) {
					willSkip = true;
					break;
				}
			}

			if (willSkip)
				continue;

			int& time = mSeedPacketsTime[i];
			time = max(time - 10, 0);

			SeedPacket* aSeedPacket = &mSeedPackets[i];

			Graphics seedG(*g);
			seedG.mScaleX = 1 + time / 100.0f * 0.25f;
			seedG.mScaleY = 1 + time / 100.0f * 0.25f;
			seedG.mTransX -= 6.25f * time / 100.0f;
			seedG.mTransY -= 8.75f * time / 100.0f;
			if (aSeedPacket->mPacketType != SeedType::SEED_NONE && aSeedPacket->BeginDraw(&seedG))
			{
				aSeedPacket->Draw(&seedG);
				aSeedPacket->EndDraw(&seedG);
			}
		}

		PlayerController* player = mBoard->mPlayer2;

		SeedPacket* aSeedPacket = &mSeedPackets[player->mSeedBankIndex];
		if (aSeedPacket && aSeedPacket->mPacketType != SeedType::SEED_NONE)
		{
			int& time = mSeedPacketsTime[player->mSeedBankIndex];
			//time = min(100, time + 20);

			float scale = 1 + time / 100.0f * 0.10f;
			float translationX = 6.25f * time / 100.0f;
			float translationY = 8.75f * time / 100.0f;

			Graphics seedG(*g);
			seedG.mScaleX = scale;
			seedG.mScaleY = scale;
			seedG.mTransX -= translationX - 5.0f;
			seedG.mTransY -= translationY - 7.0f;
			seedG.ClearClipRect();

			SexyMatrix3 matr;
			matr.ZeroMatrix();
			matr.m00 = scale / 2.0f;
			matr.m11 = scale / 1.8f;

			float seedX = aSeedPacket->mX + aSeedPacket->mOffsetX + 25 + 6.25f * time / 100.0f;
			float seedY = aSeedPacket->mY + 35 + 8.75f * time / 100.0f;
			if (mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop)
			{
				Image* aImage = nullptr;
				if (mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel())
				{
					aImage = IMAGE_P1_1;
				}
				else aImage = IMAGE_P2_1;
				seedG.DrawImageMatrix(aImage, matr, seedX - 5.0f, seedY - 7.5f);
			}

			/*if (aSeedPacket->BeginDraw(&seedG)) {
				aSeedPacket->Draw(&seedG);
				aSeedPacket->EndDraw(&seedG);
			}*/

			int& arrowTime = player->mArrowTime;
			float P2ArrowY = 0;
			if (arrowTime < 25) {
				P2ArrowY -= 1.5f;
				P2ArrowY += arrowTime / 25.0f * 1.5f;
			}
			else if (arrowTime >= 25 && arrowTime < 50) {
				P2ArrowY += (arrowTime - 25) / 25.0f * 1.5f;
			}
			else if (arrowTime >= 50 && arrowTime < 75) {
				P2ArrowY += 1.5f;
				P2ArrowY -= (arrowTime - 50) / 25.0f * 1.5f;
			}
			else if (arrowTime >= 75 && arrowTime < 100) {
				P2ArrowY -= (arrowTime - 75) / 25.0f * 1.5f;
			}

			if (mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop)
			{
				Image* aImage = nullptr;
				if (mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel())
				{
					aImage = IMAGE_P1_3;
				}
				else
				{
					aImage = IMAGE_P2_3;
				}

				seedG.DrawImageMatrix(aImage, matr, aSeedPacket->mX + aSeedPacket->mOffsetX + 16 * 1.25f, aSeedPacket->mY + P2ArrowY);
				seedG.mScaleX = 1;
				seedG.mScaleY = 1;
				seedG.mTransX += translationX;
				seedG.mTransY += translationY;
			}
			//seedG.DrawImageMatrix(IMAGE_P2_2, matr, aSeedPacket->mX + aSeedPacket->mOffsetX + 25 * 1.25f - 23.75f, aSeedPacket->mY);
		}
		
	}
	/*else {
		for (int i = 0; i < mNumPackets; i++)
		{
			SeedPacket* aSeedPacket = &mSeedPackets[i];
			if (aSeedPacket->mPacketType != SeedType::SEED_NONE && aSeedPacket->BeginDraw(g))
			{
				aSeedPacket->Draw(g);
				aSeedPacket->EndDraw(g);
			}
		}
	}*/
}

//0x489970
bool SeedBank::MouseHitTest(int x, int y, HitResult* theHitResult)
{
	//if (x - mX <= mWidth - 5 && mNumPackets > 0) //teleport 12 seed slot fix
	if (x - mX <= mWidth - 5 && mNumPackets > 0 || mApp->IsVersusLevel() && x > 0)
	{
		for (SeedPacket& aSeedPacket : mSeedPackets)
		{
			if (aSeedPacket.MouseHitTest(x - mX, y - mY, theHitResult))
			{
				return true;
			}
		}
	}

	theHitResult->mObject = nullptr;
	theHitResult->mObjectType = GameObjectType::OBJECT_TYPE_NONE;
	return false;
}

//0x489A20
bool SeedBank::ContainsPoint(int theX, int theY)
{
	return theX >= mX && theX < mX + mWidth && theY >= mY && theY < mY + mHeight;
}

//0x489A50
void SeedBank::AddSeed(SeedType theSeedType, bool thePlaceOnLeft)
{
	TOD_ASSERT(mBoard->HasConveyorBeltSeedBank());
	TOD_ASSERT(theSeedType != SeedType::SEED_NONE);

	int aNumSeeds = GetNumSeedsOnConveyorBelt();
	if (aNumSeeds == mNumPackets)
	{
		return;
	}

	SeedPacket* aSeedPacket = &mSeedPackets[aNumSeeds];
	aSeedPacket->mPacketType = theSeedType;
	aSeedPacket->mRefreshCounter = 0;
	aSeedPacket->mRefreshTime = 0;
	aSeedPacket->mRefreshing = false;
	aSeedPacket->mActive = true;
	aSeedPacket->mOffsetX = 515 - (SEED_PACKET_WIDTH + 1) * aNumSeeds;
	if (thePlaceOnLeft)
	{
		aSeedPacket->mOffsetX = 0;
	}
	if (aNumSeeds > 0)
	{
		SeedPacket* aPrevPacket = &mSeedPackets[aNumSeeds - 1];
		if (aSeedPacket->mOffsetX < aPrevPacket->mOffsetX)
		{
			aSeedPacket->mOffsetX = aPrevPacket->mOffsetX + 40;
		}
	}
}

//0x489AC0
void SeedBank::RemoveSeed(int theIndex)
{
	TOD_ASSERT(mBoard->HasConveyorBeltSeedBank());
	TOD_ASSERT(theIndex >= 0 && theIndex < GetNumSeedsOnConveyorBelt());

	for (int i = theIndex; i < mNumPackets; i++)
	{
		SeedPacket* aSeedPacket = &mSeedPackets[i];
		if (aSeedPacket->mPacketType == SeedType::SEED_NONE)
		{
			break;
		}

		if (i == mNumPackets - 1)
		{
			aSeedPacket->mPacketType = SeedType::SEED_NONE;
			aSeedPacket->mOffsetX = 0;
		}
		else
		{
			SeedPacket* aNextPacket = &mSeedPackets[i + 1];
			aSeedPacket->mPacketType = aNextPacket->mPacketType;
			aSeedPacket->mOffsetX = aNextPacket->mOffsetX + SEED_PACKET_WIDTH + 1;
		}

		aSeedPacket->mRefreshCounter = 0;
		aSeedPacket->mRefreshTime = 0;
		aSeedPacket->mRefreshing = false;
		aSeedPacket->mActive = true;
	}
}

//0x489B20
int SeedBank::GetNumSeedsOnConveyorBelt()
{
	for (int i = 0; i < mNumPackets; i++)
	{
		if (mSeedPackets[i].mPacketType == SeedType::SEED_NONE)
		{
			return i;
		}
	}
	return mNumPackets;
}

int SeedBank::CountOfTypeOnConveyorBelt(SeedType theSeedType)
{
	int aCount = 0;
	for (int i = 0; i < mNumPackets; i++)
	{
		if (mSeedPackets[i].mPacketType == theSeedType)
		{
			aCount++;
		}
	}
	return aCount;
}

//0x489B50
void SeedPacket::SetPacketType(SeedType theSeedType, SeedType theImitaterType)
{
	mPacketType = theSeedType;
	mImitaterType = theImitaterType;
	mRefreshCounter = 0;
	mRefreshTime = 0;
	mRefreshing = false;
	mActive = true;

	SeedType aUseSeedType = theSeedType;
	if (theSeedType == SeedType::SEED_IMITATER && theImitaterType != SeedType::SEED_NONE)
	{
		aUseSeedType = theImitaterType;
	}

	if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED || mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_BEGHOULED_TWIST ||
		mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_ZOMBIQUARIUM || mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_LAST_STAND || 
		mApp->IsIZombieLevel() || mApp->IsScaryPotterLevel() || mApp->IsWhackAZombieLevel() || (mApp->IsSurvivalMode() && mBoard->mChallenge->mSurvivalStage > 0))
		return;

	if ((Plant::IsUpgrade(aUseSeedType) && !gLawnApp->IsSurvivalMode()) || Plant::GetRefreshTime(mPacketType, mImitaterType) == 5000)
	{
		mRefreshTime = 3500;
		mRefreshing = true;
		mActive = false;
	}
	else if (Plant::IsUpgrade(aUseSeedType) && gLawnApp->IsSurvivalMode())
	{
		mRefreshTime = 8000;
		mRefreshing = true;
		mActive = false;
	}
	else if (mPacketType == SEED_INSTANT_COFFEE && mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_OLD)
	{
		mRefreshTime = 1000;
		mRefreshing = true;
		mActive = false;
	}
	else if (mPacketType == SEED_VERSUS_GARGANTUAR && mApp->IsVersusLevel())
	{
		mRefreshTime = 6000;
		mRefreshing = true;
		mActive = false;
	}
	else if ((mPacketType == SEED_VERSUS_BACKUP || mPacketType == SEED_PULTSHROOM) && mApp->IsVersusLevel())
	{
		mRefreshTime = 0;
		mRefreshing = true;
		mActive = false;
	}
	else if (mPacketType == SEED_VERSUS_GARGANTUAR_GIGA && mApp->IsVersusLevel())
	{
		mRefreshTime = 12000;
		mRefreshing = true;
		mActive = false;
	}
	else if (mApp->IsVersusLevel() && mPacketType != SEED_SUNFLOWER && mPacketType != SEED_PEASHOOTER && mPacketType != SEED_GIANT_WALLNUT && mPacketType != SEED_POTATOMINE && mPacketType != SEED_CABBAGEPULT && mPacketType != SEED_PUFFSHROOM && mPacketType != SEED_GRAVE && mPacketType != SEED_VERSUS_NORMAL && mPacketType != SEED_VERSUS_TRASHCAN && mPacketType != SEED_INSTANT_COFFEE)
	{
		mRefreshTime = Plant::GetRefreshTime(mPacketType, mImitaterType);
		mRefreshing = true;
		mActive = false;
	}
	else if (Plant::GetRefreshTime(mPacketType, mImitaterType) == 3000 && !(mPacketType == SEED_POTATOMINE && mApp->IsVersusLevel()))
	{
		mRefreshTime = 2000;
		mRefreshing = true;
		mActive = false;
	}
}

//0x489C70
void SeedBank::UpdateConveyorBelt()
{
	mConveyorBeltCounter++;
	if (mConveyorBeltCounter % CONVEYOR_SPEED == 0)
	{
		for (int i = 0; i < mNumPackets; i++)
		{
			SeedPacket* aSeedPacket = &mSeedPackets[i];
			if (aSeedPacket->mOffsetX > 0)
			{
				aSeedPacket->mOffsetX = max(aSeedPacket->mOffsetX - 1, 0);
			}
		}

		mBoard->UpdateToolTip();
	}
}

//0x489CD0
void SeedBank::UpdateWidth()
{
	mNumPackets = mBoard->GetNumSeedsInBank();
	mWidth = IMAGE_SEEDBANK->GetWidth() + mBoard->GetSeedBankExtraWidth();
	for (int i = 0; i < mNumPackets; i++)
	{
		mSeedPackets[i].mX = mBoard->GetSeedPacketPositionX(i, true);
	}
}

//0x489D50
void SeedBank::RefreshAllPackets()
{
	for (int i = 0; i < mNumPackets; i++)
	{
		SeedPacket* aSeedPacket = &mSeedPackets[i];
		if (aSeedPacket->mPacketType == SeedType::SEED_NONE)
		{
			break;
		}

		if (aSeedPacket->mRefreshing)
		{
			aSeedPacket->mRefreshCounter = 0;
			aSeedPacket->mRefreshing = false;
			aSeedPacket->mActive = true;
			aSeedPacket->FlashIfReady();
		}
	}
}
