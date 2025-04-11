#include "../Board.h"
#include "../Zombie.h"
#include "../Challenge.h"
#include "GameButton.h"
#include "StoreScreen.h"
#include "../Cutscene.h"
#include "../SeedPacket.h"
#include "../../LawnApp.h"
#include "AlmanacDialog.h"
#include "ImitaterDialog.h"
#include "../System/Music.h"
#include "../../Resources.h"
#include "../../Lawn/Plant.h"
#include "../ToolTipWidget.h"
#include "SeedChooserScreen.h"
#include "../../GameConstants.h"
#include "../System/PlayerInfo.h"
#include "../System/PopDRMComm.h"
#include "../../SexyAppFramework/Debug.h"
#include "../../SexyAppFramework/Dialog.h"
#include "../../SexyAppFramework/MTRand.h"
#include "../../Sexy.TodLib/TodStringFile.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../SexyAppFramework/SexyMatrix.h"
#include <iostream>

//0x483380
SeedChooserScreen::SeedChooserScreen()
{
	mApp = (LawnApp*)gSexyAppBase;
	mBoard = mApp->mBoard;
	mClip = false;
	// mSeedChooserAge = 0;  原版并没有初始化 mSeedChooserAge
	mSeedsInFlight = 0;
	mSeedsInBank = 0;
	mP2SeedsInBank = 0;
	mLastMouseX = -1;
	mLastMouseY = -1;
	mChooseState = CHOOSE_NORMAL;
	mViewLawnTime = 0;
	mToolTip = new ToolTipWidget();
	mToolTipP2 = new ToolTipWidget();
	mToolTipSeed = -1;
	mVersusNoteIsOn = false;
	mZombieID = 0;
	mPlantID = 0;
	mClickCooldown = 0;
	mPlantsPick = false;
	mCanSwitchSides = true;
	mKeyboardIsChoosing = false;
	mCloseToolTip = false;
	if (mApp->mTodCheatKeys)mMinPage = -1;



	mLeftButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Left);
	//mLeftButton->SetLabel(_S("Left"));
	mLeftButton->mButtonImage = Sexy::IMAGE_L_BUTTON1;
	mLeftButton->mOverImage = nullptr;
	mLeftButton->mDownImage = nullptr;
	mLeftButton->mDisabledImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_DISABLED;
	mLeftButton->mOverOverlayImage = Sexy::IMAGE_L_BUTTON2;
	//mLeftButton->mDrawStoneButton = true;
	mLeftButton->Resize(20, 545, 77, 46);


	mRightButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Right);
	//mRightButton->SetLabel(_S("Right"));
	mRightButton->mButtonImage = Sexy::IMAGE_R_BUTTON1;
	mRightButton->mOverImage = nullptr;
	mRightButton->mDownImage = nullptr;
	mRightButton->mDisabledImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_DISABLED;
	mRightButton->mOverOverlayImage = Sexy::IMAGE_R_BUTTON2;
	//mRightButton->mDrawStoneButton = true;
	mRightButton->Resize(190 + 156 + 27, 545, 77, 46);


	mDiscordButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Discord);
	mDiscordButton->mButtonImage = Sexy::IMAGE_DISCORD_BUTTON;
	mDiscordButton->mOverImage = nullptr;
	mDiscordButton->mDownImage = nullptr;
	mDiscordButton->mDisabledImage = Sexy::IMAGE_DISCORD_BUTTON_HOVER;
	mDiscordButton->mOverOverlayImage = Sexy::IMAGE_DISCORD_BUTTON_DOWN;
	int removeDiscord = 0;
	//if (mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_VERSUS)
	{
		removeDiscord = 5000;
	}
	mDiscordButton->Resize(465, 464 + removeDiscord, 36, 40);


	mStartButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Start);
	mStartButton->SetLabel(_S("[LETS_ROCK_BUTTON]"));
	mStartButton->mButtonImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON;
	mStartButton->mOverImage = nullptr;
	mStartButton->mDownImage = nullptr;
	mStartButton->mDisabledImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_DISABLED;
	mStartButton->mOverOverlayImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON_GLOW;
	//mStartButton->SetFont(Sexy::FONT_DWARVENTODCRAFT15);
	mStartButton->SetFont(Sexy::FONT_DWARVENTODCRAFT18YELLOW);
	mStartButton->mColors[ButtonWidget::COLOR_LABEL] = Color::White;
	mStartButton->mColors[ButtonWidget::COLOR_LABEL_HILITE] = Color::White;
	int moveXtoRight = 0;
	if (mApp->IsVersusLevel())
	{
		moveXtoRight = 40;
	}
	mStartButton->Resize(154 + moveXtoRight, 545, 156, 42);
	mStartButton->mTextOffsetY = -1;
	EnableStartButton(false);

	mMenuButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Menu);
	mMenuButton->SetLabel(_S("[MENU_BUTTON]"));
	mMenuButton->Resize(681, -10, 117, 46);
	mMenuButton->mDrawStoneButton = true;

	mRandomButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Random);
	mRandomButton->SetLabel(_S("(Debug Play)"));
	mRandomButton->mButtonImage = Sexy::IMAGE_BLANK;
	mRandomButton->mOverImage = Sexy::IMAGE_BLANK;
	mRandomButton->mDownImage = Sexy::IMAGE_BLANK;
	mRandomButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mRandomButton->mColors[0] = Color(255, 240, 0);
	mRandomButton->mColors[1] = Color(200, 200, 255);
	mRandomButton->Resize(332, 546, 100, 30);
	//if (!mApp->mTodCheatKeys)
	{
		mRandomButton->mBtnNoDraw = true;
		mRandomButton->mDisabled = true;
	}

	Color aBtnColor = Color(42, 42, 90);
	Image* aBtnImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON2;
	Image* aOverImage = Sexy::IMAGE_SEEDCHOOSER_BUTTON2_GLOW;
	int aImageWidth = aBtnImage->GetWidth();
	int aImageHeight = aOverImage->GetHeight();

	mViewLawnButton = new GameButton(SeedChooserScreen::SeedChooserScreen_ViewLawn);
	mViewLawnButton->SetLabel(_S("[VIEW_LAWN]"));
	mViewLawnButton->mButtonImage = aBtnImage;
	mViewLawnButton->mOverImage = aOverImage;
	mViewLawnButton->mDownImage = nullptr;
	mViewLawnButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mViewLawnButton->mColors[0] = aBtnColor;
	mViewLawnButton->mColors[1] = aBtnColor;
	mViewLawnButton->Resize(560, 545, aImageWidth, aImageHeight);
	mViewLawnButton->mParentWidget = this;
	mViewLawnButton->mTextOffsetY = 1;
	if (!mBoard->mCutScene->IsSurvivalRepick())
	{
		mViewLawnButton->mBtnNoDraw = true;
		mViewLawnButton->mDisabled = true;
	}

	mAlmanacButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Almanac);
	mAlmanacButton->SetLabel(_S("[ALMANAC_BUTTON]"));
	mAlmanacButton->mButtonImage = aBtnImage;
	mAlmanacButton->mOverImage = aOverImage;
	mAlmanacButton->mDownImage = nullptr;
	mAlmanacButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mAlmanacButton->mColors[0] = aBtnColor;
	mAlmanacButton->mColors[1] = aBtnColor;
	int outOfScreenX = 0;
	int outOfScreenY = 0;
	if (mApp->IsVersusLevel())
	{
		outOfScreenX = 80;
		//outOfScreenY= 30;
		outOfScreenY= 5000;
	}
	mAlmanacButton->Resize(560 - outOfScreenX, 572 - outOfScreenY, aImageWidth, aImageHeight);
	mAlmanacButton->mParentWidget = this;
	mAlmanacButton->mTextOffsetY = 1;

	mMapButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Map);
	mMapButton->SetLabel(_S("[VERSUSMODE_DAY_BUTTON]"));
	mMapButton->mButtonImage = aBtnImage;
	mMapButton->mOverImage = aOverImage;
	mMapButton->mDownImage = nullptr;
	mMapButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mMapButton->mColors[0] = aBtnColor;
	mMapButton->mColors[1] = aBtnColor;
	outOfScreenX = 0;
	outOfScreenY = 5000;
	if (mApp->IsVersusLevel())
	{
		outOfScreenX = 80;
		outOfScreenY= 5000;
	}
	mMapButton->Resize(560 - outOfScreenX, 572 - outOfScreenY, aImageWidth, aImageHeight);
	mMapButton->mParentWidget = this;
	mMapButton->mTextOffsetY = 1;

	mStoreButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Store);
	mStoreButton->SetLabel(_S("[SHOP_BUTTON]"));
	mStoreButton->mButtonImage = aBtnImage;
	mStoreButton->mOverImage = aOverImage;
	mStoreButton->mDownImage = nullptr;
	mStoreButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mStoreButton->mColors[0] = aBtnColor;
	mStoreButton->mColors[1] = aBtnColor;
	outOfScreenX = 0;
	outOfScreenY = 0;
	if (mApp->IsVersusLevel())
	{
		outOfScreenX = 93;
		//outOfScreenY = 30;
		outOfScreenY = 5000;
	}
	mStoreButton->Resize(680 - outOfScreenX, 572 - outOfScreenY, aImageWidth, aImageHeight);
	mStoreButton->mParentWidget = this;
	mStoreButton->mTextOffsetY = 1;

	mVersusButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Versus);
	mVersusButton->SetLabel(_S("[VERSUS_BUTTON]"));
	mVersusButton->mButtonImage = aBtnImage;
	mVersusButton->mOverImage = aOverImage;
	mVersusButton->mDownImage = nullptr;
	mVersusButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mVersusButton->mColors[0] = aBtnColor;
	mVersusButton->mColors[1] = aBtnColor;
	outOfScreenX = 0;
	outOfScreenY = 0;
	if (mApp->IsVersusLevel())
	{
		outOfScreenX = 93;
		//outOfScreenY = 7;
		outOfScreenY = 20;
	}
	else
	{
		outOfScreenY = 5000;
	}
	mVersusButton->Resize(680 - outOfScreenX, 572 - outOfScreenY, aImageWidth, aImageHeight);
	mVersusButton->mParentWidget = this;
	mVersusButton->mTextOffsetY = 1;

	mKeyboardButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Keyboard);
	mKeyboardButton->SetLabel(_S("[KEYBOARD_BUTTON]"));
	mKeyboardButton->mButtonImage = aBtnImage;
	mKeyboardButton->mOverImage = aOverImage;
	mKeyboardButton->mDownImage = nullptr;
	mKeyboardButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mKeyboardButton->mColors[0] = aBtnColor;
	mKeyboardButton->mColors[1] = aBtnColor;
	outOfScreenX = 0;
	outOfScreenY = 0;
	if (mApp->IsVersusLevel())
	{
		outOfScreenX = 80;
		//outOfScreenY = 7;
		outOfScreenY = 20;
	}
	else
	{
		outOfScreenY = 5000;
	}
	mKeyboardButton->Resize(560 - outOfScreenX, 572 - outOfScreenY, aImageWidth, aImageHeight);
	mKeyboardButton->mParentWidget = this;
	mKeyboardButton->mTextOffsetY = 1;

	mSkipButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Skip);
	mSkipButton->SetLabel(_S("[NAVIGATE_BUTTON]"));
	mSkipButton->mButtonImage = aBtnImage;
	mSkipButton->mOverImage = aOverImage;
	mSkipButton->mDownImage = nullptr;
	mSkipButton->SetFont(Sexy::FONT_BRIANNETOD12);
	mSkipButton->mColors[0] = aBtnColor;
	mSkipButton->mColors[1] = aBtnColor;
	outOfScreenX = 0;
	outOfScreenY = 5000;
	if (mApp->mGameMode != GameMode::GAMEMODE_ADVENTURE || mApp->mPlayerInfo->mFinishedAdventure == 0)
	{
		outOfScreenX = 50;
		outOfScreenY = 5000;
	}
	mSkipButton->Resize(680 - outOfScreenX, 542 - outOfScreenY, aImageWidth, aImageHeight);
	mSkipButton->mParentWidget = this;
	mSkipButton->mTextOffsetY = 1;

	mImitaterButton = new GameButton(SeedChooserScreen::SeedChooserScreen_Imitater);
	mImitaterButton->mButtonImage = Sexy::IMAGE_IMITATERSEED;
	mImitaterButton->mOverImage = Sexy::IMAGE_IMITATERSEED;
	mImitaterButton->mDownImage = Sexy::IMAGE_IMITATERSEED;
	mImitaterButton->mDisabledImage = Sexy::IMAGE_IMITATERSEEDDISABLED;
	outOfScreenY = 0;
	if (mApp->IsVersusLevel()) outOfScreenY = 1000;
	mImitaterButton->Resize(464, 515 + outOfScreenY, Sexy::IMAGE_IMITATERSEED->mWidth, Sexy::IMAGE_IMITATERSEED->mHeight);
	mImitaterButton->mParentWidget = this;

	if (!mApp->CanShowAlmanac())
	{
		mAlmanacButton->mBtnNoDraw = true;
		mAlmanacButton->mDisabled = true;
	}
	if (!mApp->CanShowStore())
	{
		mStoreButton->mBtnNoDraw = true;
		mStoreButton->mDisabled = true;
	}

	//DBG_ASSERT(mApp->GetSeedsAvailable() <= NUM_SEED_TYPES);
	mChosenSeeds.clear();
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;


			ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
			aChosenSeed.mSeedType = aSeedType;
			GetSeedPositionInChooser(aSeedType, aChosenSeed.mX, aChosenSeed.mY, aSeedType);
			aChosenSeed.mTimeStartMotion = 0;
			aChosenSeed.mTimeEndMotion = 0;
			aChosenSeed.mStartX = aChosenSeed.mX;
			aChosenSeed.mStartY = aChosenSeed.mY;
			aChosenSeed.mEndX = aChosenSeed.mX;
			aChosenSeed.mEndY = aChosenSeed.mY;
			aChosenSeed.mSeedState = aSeedType == SEED_IMITATER ? SEED_PACKET_HIDDEN : SEED_IN_CHOOSER;
			aChosenSeed.mSeedIndexInBank = 0;
			aChosenSeed.mP2SeedIndexInBank = 0;
			aChosenSeed.mRefreshCounter = 0;
			aChosenSeed.mRefreshing = false;
			aChosenSeed.mImitaterType = SEED_NONE;
			aChosenSeed.mCrazyDavePicked = false;

		}
	}


	if (mBoard->mCutScene->IsSurvivalRepick())
	{
		for (int anIdx = 0; anIdx < mBoard->mSeedBank->mNumPackets; anIdx++)
		{
			SeedPacket* aSeedPacket = &mBoard->mSeedBank->mSeedPackets[anIdx];
			ChosenSeed& aChosenSeed = mChosenSeeds[aSeedPacket->mPacketType];
			aChosenSeed.mRefreshing = aSeedPacket->mRefreshing;
			aChosenSeed.mRefreshCounter = aSeedPacket->mRefreshCounter;
		}
		mBoard->mSeedBank->mNumPackets = 0;
	}
	if (mApp->mGameMode == GAMEMODE_CHALLENGE_SEEING_STARS)
	{
		ChosenSeed& aStarFruit = mChosenSeeds[SEED_STARFRUIT];
		int aX = mBoard->GetSeedPacketPositionX(0, !SeedPacket::IsZombiePack(aStarFruit.mSeedType));
		aStarFruit.mX = aX, aStarFruit.mY = 8;
		aStarFruit.mStartX = aX, aStarFruit.mStartY = 8;
		aStarFruit.mEndX = aX, aStarFruit.mEndY = 8;
		aStarFruit.mSeedState = SEED_IN_BANK;
		aStarFruit.mSeedIndexInBank = 0;
		mSeedsInBank++;
	}
	if (mApp->mGameMode == GAMEMODE_CHALLENGE_SEASTAR)
	{
		ChosenSeed& aStarFruit = mChosenSeeds[SEED_PINKSTAR];
		int aX = mBoard->GetSeedPacketPositionX(0, !SeedPacket::IsZombiePack(aStarFruit.mSeedType));
		aStarFruit.mX = aX, aStarFruit.mY = 8;
		aStarFruit.mStartX = aX, aStarFruit.mStartY = 8;
		aStarFruit.mEndX = aX, aStarFruit.mEndY = 8;
		aStarFruit.mSeedState = SEED_IN_BANK;
		aStarFruit.mSeedIndexInBank = 0;
		aStarFruit.mSeedIndexInBank = 0;
		mSeedsInBank++;
	}
	if (mApp->IsVersusLevel())
	{
		ChosenSeed & aProducer = mChosenSeeds[SEED_SUNFLOWER];
		int aX = mBoard->GetSeedPacketPositionX(0, !SeedPacket::IsZombiePack(aProducer.mSeedType));
		aProducer.mX = aX, aProducer.mY = 8;
		aProducer.mStartX = aX, aProducer.mStartY = 8;
		aProducer.mEndX = aX, aProducer.mEndY = 8;
		aProducer.mSeedState = SEED_IN_BANK;
		aProducer.mSeedIndexInBank = 0;
		mSeedsInBank++;	

		ChosenSeed& aProducerZombies = mChosenSeeds[SEED_GRAVE];
		int bX = mBoard->GetSeedPacketPositionX(0, !SeedPacket::IsZombiePack(aProducerZombies.mSeedType));
		aProducerZombies.mX = bX, aProducerZombies.mY = 8;
		aProducerZombies.mStartX = bX, aProducerZombies.mStartY = 8;
		aProducerZombies.mEndX = bX, aProducerZombies.mEndY = 8;
		aProducerZombies.mSeedState = SEED_IN_BANK;
		aProducerZombies.mSeedIndexInBank = 0;
		mP2SeedsInBank++;	
	}
	if (mApp->IsAdventureMode() && !mApp->IsFirstTimeAdventureMode())
		CrazyDavePickSeeds();
	UpdateImitaterButton();
}

int SeedChooserScreen::PickFromWeightedArrayUsingSpecialRandSeed(TodWeightedArray* theArray, int theCount, MTRand& theLevelRNG)
{
	int aTotalWeight = 0;
	for (int i = 0; i < theCount; i++)
		aTotalWeight += theArray[i].mWeight;
	DBG_ASSERT(aTotalWeight > 0);

	int aRndResult = theLevelRNG.Next((unsigned long)aTotalWeight);
	int aWeight = 0;
	for (int j = 0; j < theCount; j++)
	{
		aWeight += theArray[j].mWeight;
		if
			(aWeight > aRndResult) return theArray[j].mItem;
	}
	DBG_ASSERT(false);
}

//0x483F70
void SeedChooserScreen::CrazyDavePickSeeds()
{
	TodWeightedArray* aSeedArray = new TodWeightedArray[NUM_SEED_TYPES];
	for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1))
	{
		aSeedArray[aSeedType].mItem = aSeedType;
		uint aRecFlags = SeedNotRecommendedToPick(aSeedType);
		if ((aSeedType == SEED_GATLINGPEA && !mApp->mPlayerInfo->mPurchases[STORE_ITEM_PLANT_GATLINGPEA]) || !mApp->SeedTypeAvailable(aSeedType) || mBoard->CheckZombiePack(aSeedType) ||
			SeedNotAllowedToPick(aSeedType) || Plant::IsUpgrade(aSeedType) || aSeedType == SEED_IMITATER || aSeedType == SEED_UMBRELLA || aSeedType == SEED_BLOVER || gPlantDefs[aSeedType].getPage() < 0)
		{
			aSeedArray[aSeedType].mWeight = 0;
		}
		else
		{
			aSeedArray[aSeedType].mWeight = 1;
		}
	}
	if (mBoard->mZombieAllowed[ZOMBIE_BUNGEE] || mBoard->mZombieAllowed[ZOMBIE_CATAPULT])
	{
		aSeedArray[SEED_UMBRELLA].mWeight = 1;
	}
	if (mBoard->mZombieAllowed[ZOMBIE_BALLOON] || mBoard->StageHasFog())
	{
		aSeedArray[SEED_BLOVER].mWeight = 1;
	}
	if (mBoard->StageHasRoof())
	{
		aSeedArray[SEED_TORCHWOOD].mWeight = 0;
	}

	MTRand aLevelRNG = MTRand(mBoard->GetLevelRandSeed());
	for (int i = 0; i < 3; i++)
	{

		SeedType aPickedSeed = (SeedType)PickFromWeightedArrayUsingSpecialRandSeed(aSeedArray, NUM_SEEDS_IN_CHOOSER, aLevelRNG);
		aSeedArray[aPickedSeed].mWeight = 0;
		ChosenSeed& aChosenSeed = mChosenSeeds[aPickedSeed];

		int aPosX = mBoard->GetSeedPacketPositionX(i, true);
		aChosenSeed.mX = aPosX;
		aChosenSeed.mY = 8;
		aChosenSeed.mStartX = aPosX;
		aChosenSeed.mStartY = 8;
		aChosenSeed.mEndX = aPosX;
		aChosenSeed.mEndY = 8;
		aChosenSeed.mSeedState = SEED_IN_BANK;
		aChosenSeed.mSeedIndexInBank = i;
		aChosenSeed.mCrazyDavePicked = true;
		mSeedsInBank++;
		mP2SeedsInBank++;
	}
	delete aSeedArray;
}

//0x484220
int SeedChooserScreen::Has7Rows()
{
	PlayerInfo* aPlayer = mApp->mPlayerInfo;
	if (mApp->HasFinishedAdventure() || mApp->mPlayerInfo->mPurchases[STORE_ITEM_PLANT_GATLINGPEA]) return true;
	for (SeedType aSeedType = SEED_TWINSUNFLOWER; aSeedType < SEED_COBCANNON; aSeedType = (SeedType)(aSeedType + 1))
		if (aSeedType != SEED_SPIKEROCK && mApp->SeedTypeAvailable(aSeedType)) return true;
	return false;
}

//0x484400
void SeedChooserScreen::GetSeedPositionInChooser(int theIndex, int& x, int& y, SeedType theSeedType)
{
	if (theIndex == SEED_IMITATER)
	{
		x = mImitaterButton->mX;
		y = mImitaterButton->mY;
	}
	else
	{
		int theRealIndex = -1;
		for each (auto plantDefinition in gPlantDefs)
		{
			if (true) {
				SeedType aSeedType = plantDefinition.mSeedType;
				if (aSeedType != SEED_IMITATER)theRealIndex++;
				if (theIndex == aSeedType)break;
			}
		}
		int aRow = theRealIndex / 8;
		int aCol = theRealIndex % 8;

		x = aCol * 53 + 22;
		if (Has7Rows())
		{
			y = aRow * 70 + 123;
		}
		else
		{
			y = aRow * 73 + 128;
		}	
	}

	for (int i = 0; i < 8; i++)
	{
		if (theSeedType == SEED_GATLINGPEA + i && mPage == 0) { x = i * 53 + 22; y = 5 * 70 + 123; }
	}

	for (int i = 0; i < 8; i++)
	{
		if (theSeedType == SEED_PULTSHROOM + i && mPage == 1) { x = i * 53 + 22; y = 0 * 70 + 123; }
	}

	for (int i = 0; i < 8; i++)
	{
		if (theSeedType == SEED_BEE_SHOOTER + i && mPage == 1) { x = i * 53 + 22; y = 1 * 70 + 123; }
	}

	for (int i = 0; i < 8; i++)
	{
		if (theSeedType == SEED_ICYFUME + i && mPage == 1) { x = i * 53 + 22; y = 5 * 70 + 123; }
	}

	for (int i = 0; i < 8; i++)
	{
		if (theSeedType == SEED_FLAMEPEA + i && mPage == 2) { x = i * 53 + 22; y = 0 * 70 + 123; }
	}
	
	if (theSeedType == SEED_PLASMAPEA && mPage == 2) { x = 0 * 53 + 22; y = 5 * 70 + 123; }
	if (theSeedType == SEED_SHOOTINGSTAR && mPage == 2) { x = 1 * 53 + 22; y = 5 * 70 + 123; }

	if (theSeedType == SEED_IMITATER) { x = 464; y = 515; }

	if (mApp->IsVersusLevel())
	{
		for (int i = 0; i < 30; i++)
		{
			if (theSeedType == SEED_VERSUS_NORMAL + i && mPageP2 == 0) { x = (i % 5) * 53 + 483; y = (i / 5) * 70 + 123; }
		}

		for (int i = 0; i < 5; i++)
		{
			if (theSeedType == SEED_VERSUS_LEAFBLOWER + i && mPageP2 == 1) { x = (i % 5) * 53 + 483; y = (i / 5) * 70 + 123; }
		}

		if ((theSeedType == SEED_VERSUS_GLADIANTUAR_GIGA) && mPageP2 == 2) { x = 0 * 53 + 483; y = 0 * 70 + 123; }
	}
	else
	{
		if ((theSeedType >= SEED_VERSUS_NORMAL && theSeedType <= SEED_VERSUS_GLADIANTUAR_GIGA)) { x = 0; y = 1000; }
	}
}

//0x484480
void SeedChooserScreen::GetSeedPositionInBank(int theIndex, int& x, int& y, SeedType theSeedType)
{
	x = mBoard->mSeedBank->mX - mX + mBoard->GetSeedPacketPositionX(theIndex, !SeedPacket::IsZombiePack(theSeedType));
	y = mBoard->mSeedBank->mY - mY + 8;
}

//0x4844D0
SeedChooserScreen::~SeedChooserScreen()
{
	if (mLeftButton) delete mLeftButton;
	if (mRightButton) delete mRightButton;
	if (mDiscordButton) delete mDiscordButton;
	if (mStartButton) delete mStartButton;
	if (mRandomButton) delete mRandomButton;
	if (mViewLawnButton) delete mViewLawnButton;
	if (mAlmanacButton) delete mAlmanacButton;
	if (mImitaterButton) delete mImitaterButton;
	if (mStoreButton) delete mStoreButton;
	if (mVersusButton) delete mVersusButton;
	if (mKeyboardButton) delete mKeyboardButton;
	if (mSkipButton) delete mSkipButton;
	if (mToolTip) delete mToolTip;
	if (mToolTipP2) delete mToolTipP2;
	if (mMenuButton) delete mMenuButton;
	if (mMapButton) delete mMapButton;
}

//0x4845E0
unsigned int SeedChooserScreen::SeedNotRecommendedToPick(SeedType theSeedType)
{
	uint aRecFlags = mBoard->SeedNotRecommendedForLevel(theSeedType);
	if (TestBit(aRecFlags, NOT_RECOMMENDED_NOCTURNAL) && PickedPlantType(SEED_INSTANT_COFFEE))
		SetBit(aRecFlags, NOT_RECOMMENDED_NOCTURNAL, false);
	else if (TestBit(aRecFlags, NOT_RECOMMENDED_NEEDS_POOL) && PickedPlantType(SEED_WATERPOT))
		SetBit(aRecFlags, NOT_RECOMMENDED_NEEDS_POOL, false);
	return aRecFlags;
}

//0x484620
int SeedChooserScreen::SeedNotAllowedToPick(SeedType theSeedType)
{
	return (mApp->mGameMode == GAMEMODE_CHALLENGE_LAST_STAND && (theSeedType == SEED_SUNFLOWER  || theSeedType == SEED_SUNSHROOM ||
		theSeedType == SEED_TWINSUNFLOWER || theSeedType == SEED_SEASHROOM || theSeedType == SEED_PUFFSHROOM || theSeedType == SEED_PULTSHROOM)) ||
		(mApp->mGameMode == GAMEMODE_CHALLENGE_GLADIANTUAR && (theSeedType == SEED_MAGNETSHROOM || theSeedType == SEED_GRAVEBUSTER) ||
		(mApp->IsVersusLevel() && ((theSeedType == SEED_MARIGOLD) || ((SeedNotAllowedToPickVersusPlants(theSeedType) && !mPlantsPick) || (SeedNotAllowedToPickVersusZombies(theSeedType) && mPlantsPick)))) && !mApp->mDebugKeysEnabled);
}

int SeedChooserScreen::SeedNotAllowedToPickVersusPlants(SeedType theSeedType)
{
	return (mApp->IsVersusLevel() && (!SeedPacket::IsZombiePack(theSeedType)));
}

int SeedChooserScreen::SeedNotAllowedToPickVersusZombies(SeedType theSeedType)
{
	return (mApp->IsVersusLevel() && (SeedPacket::IsZombiePack(theSeedType)));
}

//0x484640
int SeedChooserScreen::SeedNotAllowedDuringTrial(SeedType theSeedType)
{
	return mApp->IsTrialStageLocked() && (theSeedType == SEED_SQUASH || theSeedType == SEED_THREEPEATER);
}

//0x484690
void SeedChooserScreen::Draw(Graphics* g)
{
	if (mApp->GetDialog(DIALOG_STORE) || mApp->GetDialog(DIALOG_ALMANAC))
		return;

	g->SetLinearBlend(true);
	if (!mBoard->ChooseSeedsOnCurrentLevel() || (mBoard->mCutScene && mBoard->mCutScene->IsBeforePreloading()))
		return;

	g->DrawImage(Sexy::IMAGE_SEEDCHOOSER_BACKGROUND, 0, 87);
	if (mApp->IsVersusLevel()) g->DrawImage(Sexy::IMAGE_SEEDCHOOSER_BACKGROUND_ZOMBIES, 460, 87);
	if (mApp->SeedTypeAvailable(SEED_IMITATER) && !mApp->IsVersusLevel())
	{
		g->DrawImage(Sexy::IMAGE_SEEDCHOOSER_IMITATERADDON, 459, 503);
	}
	TodDrawString(g, _S("[CHOOSE_YOUR_PLANTS]"), 229, 110, Sexy::FONT_DWARVENTODCRAFT18YELLOW, Color::White, DS_ALIGN_CENTER);
	if (mApp->IsVersusLevel()) TodDrawString(g, _S("[CHOOSE_YOUR_ZOMBIES]"), 619, 110, Sexy::FONT_DWARVENTODCRAFT18BRIGHTGREENINSET, Color::White, DS_ALIGN_CENTER);

	//int aNumSeeds = Has7Rows() ? 48 : 40;
	int theRealPosIndex = -1;

	for each (auto plantDefinition in gPlantDefs)
	{
		if (true && (plantDefinition.getPage() == mPage && !SeedPacket::IsZombiePack(plantDefinition.mSeedType)) || (plantDefinition.getPage() == mPageP2 && SeedPacket::IsZombiePack(plantDefinition.mSeedType))) {
			SeedType aSeedType = plantDefinition.mSeedType;
			auto& chosenSeed = mChosenSeeds[aSeedType];
			if (chosenSeed.mSeedState != SEED_PACKET_HIDDEN)
			{
				theRealPosIndex++;
				int x, y;
				GetSeedPositionInChooser(theRealPosIndex, x, y, aSeedType);
				if (mApp->SeedTypeAvailable(aSeedType))
				{

					if (chosenSeed.mSeedState != SEED_IN_CHOOSER)
					{
						DrawSeedPacket(g, x, y, aSeedType, SEED_NONE, 0, 55, true, false);
					}
				}
				else
				{
					g->DrawImage(Sexy::IMAGE_SEEDPACKETSILHOUETTE, x, y);
				}
			}
		}
	}

	int aNumSeedsInBank;
	if (mApp->IsVersusLevel()) aNumSeedsInBank = 12;
	else aNumSeedsInBank = mBoard->mSeedBank->mNumPackets;
	for (int anIndex = 0; anIndex < aNumSeedsInBank; anIndex++)
	{
		//if (FindSeedInBank(anIndex) == SEED_NONE) //changed teleport shows seed shadow removed for versusmode
		{
			int x, y;
			GetSeedPositionInBank(anIndex, x, y, SEED_SUNFLOWER);
			int xOffsett = 0;
			if (anIndex >= 6 && mApp->IsVersusLevel()) xOffsett = 22;
			g->DrawImage(Sexy::IMAGE_SEEDPACKETSILHOUETTE, x + xOffsett, y);
		}
	}
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {

			SeedType aSeedType = plantDefinition.mSeedType;
			ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
			ChosenSeedState aSeedState = aChosenSeed.mSeedState;
			if (mApp->SeedTypeAvailable(aSeedType) && aSeedState != SEED_FLYING_TO_BANK && aSeedState != SEED_FLYING_TO_CHOOSER &&
				aSeedState != SEED_PACKET_HIDDEN && (aSeedState == SEED_IN_CHOOSER || mBoard->mCutScene->mSeedChoosing))
			{
				int aGrayed = false;
				if (((SeedNotRecommendedToPick(aSeedType) || SeedNotAllowedToPick(aSeedType)) && aSeedState == SEED_IN_CHOOSER) ||
					SeedNotAllowedDuringTrial(aSeedType))
					aGrayed = true;

				if ((aChosenSeed.mSeedType == SEED_VERSUS_SNORKEL || aChosenSeed.mSeedType == SEED_VERSUS_DOLPHIN) && aSeedState == SEED_IN_CHOOSER && mApp->IsVersusLevel() && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_POOL && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_FOG)
					aGrayed = true;

				if ((aChosenSeed.mSeedType == SEED_VERSUS_DANCER || aChosenSeed.mSeedType == SEED_VERSUS_DIGGER) && aSeedState == SEED_IN_CHOOSER && (mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON))
					aGrayed = true;

				int aPosX = aChosenSeed.mX;
				int aPosY = aChosenSeed.mY;
				if (aSeedState == SEED_IN_BANK)
				{
					aPosX -= mX;
					aPosY -= mY;
				}
				if (aSeedState == SEED_IN_BANK || (aSeedState != SEED_IN_BANK && plantDefinition.getPage() == mPage && !SeedPacket::IsZombiePack(aChosenSeed.mSeedType)) || (aSeedState != SEED_IN_BANK && plantDefinition.getPage() == mPageP2 && SeedPacket::IsZombiePack(aChosenSeed.mSeedType)))
					DrawSeedPacket(g, aPosX, aPosY, aChosenSeed.mSeedType, aChosenSeed.mImitaterType, 0, aGrayed ? 115 : 255, true, false);
			}

		}
	}

	/*DrawSeedPacket(g, 0 * 53 + 483, 0 * 70 + 123, SeedType::SEED_VERSUS_GRAVE, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 1 * 53 + 483, 0 * 70 + 123, SeedType::SEED_ZOMBIE_NORMAL, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 2 * 53 + 483, 0 * 70 + 123, SeedType::SEED_ZOMBIE_TRAFFIC_CONE, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 3 * 53 + 483, 0 * 70 + 123, SeedType::SEED_ZOMBIE_PAIL, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 4 * 53 + 483, 0 * 70 + 123, SeedType::SEED_ZOMBIE_POLEVAULTER, SeedType::SEED_IMITATER, 0, 255, true, false);

	DrawSeedPacket(g, 0 * 53 + 483, 1 * 70 + 123, SeedType::SEED_ZOMBIE_POGO, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 1 * 53 + 483, 1 * 70 + 123, SeedType::SEED_ZOMBIE_SCREEN_DOOR, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 2 * 53 + 483, 1 * 70 + 123, SeedType::SEED_ZOMBIE_SCARECROW, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 3 * 53 + 483, 1 * 70 + 123, SeedType::SEED_ZOMBIE_DANCER, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 4 * 53 + 483, 1 * 70 + 123, SeedType::SEED_ZOMBIE_GARGANTUAR, SeedType::SEED_IMITATER, 0, 255, true, false);

	DrawSeedPacket(g, 0 * 53 + 483, 2 * 70 + 123, SeedType::SEED_ZOMBIE_DIGGER, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 1 * 53 + 483, 2 * 70 + 123, SeedType::SEED_ZOMBIE_BUNGEE, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 2 * 53 + 483, 2 * 70 + 123, SeedType::SEED_ZOMBIE_DIGGER, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 3 * 53 + 483, 2 * 70 + 123, SeedType::SEED_ZOMBIE_FOOTBALL, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 4 * 53 + 483, 2 * 70 + 123, SeedType::SEED_ZOMBIE_ZOMBOSS, SeedType::SEED_IMITATER, 0, 255, true, false);

	DrawSeedPacket(g, 0 * 53 + 483, 3 * 70 + 123, SeedType::SEED_VERSUS_GRAVE, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 1 * 53 + 483, 3 * 70 + 123, SeedType::SEED_ZOMBIE_NORMAL, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 2 * 53 + 483, 3 * 70 + 123, SeedType::SEED_ZOMBIE_TRAFFIC_CONE, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 3 * 53 + 483, 3 * 70 + 123, SeedType::SEED_ZOMBIE_PAIL, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 4 * 53 + 483, 3 * 70 + 123, SeedType::SEED_ZOMBIE_POLEVAULTER, SeedType::SEED_IMITATER, 0, 255, true, false);

	DrawSeedPacket(g, 0 * 53 + 483, 4 * 70 + 123, SeedType::SEED_ZOMBIE_POGO, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 1 * 53 + 483, 4 * 70 + 123, SeedType::SEED_ZOMBIE_SCREEN_DOOR, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 2 * 53 + 483, 4 * 70 + 123, SeedType::SEED_ZOMBIE_SCARECROW, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 3 * 53 + 483, 4 * 70 + 123, SeedType::SEED_ZOMBIE_DANCER, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 4 * 53 + 483, 4 * 70 + 123, SeedType::SEED_ZOMBIE_GARGANTUAR, SeedType::SEED_IMITATER, 0, 255, true, false);

	DrawSeedPacket(g, 0 * 53 + 483, 5 * 70 + 123, SeedType::SEED_ZOMBIE_DIGGER, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 1 * 53 + 483, 5 * 70 + 123, SeedType::SEED_ZOMBIE_BUNGEE, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 2 * 53 + 483, 5 * 70 + 123, SeedType::SEED_ZOMBIE_DIGGER, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 3 * 53 + 483, 5 * 70 + 123, SeedType::SEED_ZOMBIE_FOOTBALL, SeedType::SEED_IMITATER, 0, 255, true, false);
	DrawSeedPacket(g, 4 * 53 + 483, 5 * 70 + 123, SeedType::SEED_ZOMBIE_ZOMBOSS, SeedType::SEED_IMITATER, 0, 255, true, false);*/

	mImitaterButton->Draw(g);
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;
			ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
			ChosenSeedState aSeedState = aChosenSeed.mSeedState;
			if (mApp->SeedTypeAvailable(aSeedType) && (aSeedState == SEED_FLYING_TO_BANK || aSeedState == SEED_FLYING_TO_CHOOSER))
			{
				DrawSeedPacket(g, aChosenSeed.mX, aChosenSeed.mY, aChosenSeed.mSeedType, aChosenSeed.mImitaterType, 0, 255, true, false);
			}
		}
	}

	mLeftButton->Draw(g);
	mRightButton->Draw(g);
	mDiscordButton->Draw(g);
	mStartButton->Draw(g);
	mRandomButton->Draw(g);
	mViewLawnButton->Draw(g);
	mAlmanacButton->Draw(g);
	mStoreButton->Draw(g);
	mVersusButton->Draw(g);
	mKeyboardButton->Draw(g);
	mSkipButton->Draw(g);
	mMapButton->Draw(g);
	Graphics aBoardFrameG = Graphics(*g);
	aBoardFrameG.mTransX -= mX;
	aBoardFrameG.mTransY -= mY;
	mMenuButton->Draw(&aBoardFrameG);
	if (mApp->IsVersusLevel())
	{
		if (mApp->mIsKeyboardPlayer1)
		{
			g->DrawImage(Sexy::IMAGE_PLAYER1_KEYBOARD, 110, 545);
			g->DrawImage(Sexy::IMAGE_PLAYER2_MOUSE, 697, 545);
		}
		else
		{
			g->DrawImage(Sexy::IMAGE_PLAYER1_MOUSE, 110, 545);
			g->DrawImage(Sexy::IMAGE_PLAYER2_KEYBOARD, 697, 545);
		}
	}
	int time = 200;
	float scale = 1 + time / 100.0f * 0.10f;
	float translationX = 6.25f * time / 100.0f;
	float translationY = 8.75f * time / 100.0f;
	Graphics seedG(*g);
	seedG.mScaleX = 1.0f;
	seedG.mScaleY = 1.0f;
	seedG.ClearClipRect();
	SexyMatrix3 matr;
	matr.ZeroMatrix();
	matr.m00 = scale / 2.25f;
	matr.m11 = scale / 2.25f;
	if (mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop)
	{
		int aPlantCorrection = 0;
		if (mApp->mIsKeyboardPlayer1 || (!mApp->mPlayerInfo->mIsNotCoop && !mApp->IsVersusLevel()))
		{
			if (mPlantID >= SEED_GATLINGPEA && mPlantID <= SEED_COBCANNON && mPage == 0) aPlantCorrection = 16;
			else if (mPlantID >= SEED_ICYFUME - SEED_PULTSHROOM && mPlantID <= SEED_ECACTUS - SEED_PULTSHROOM && mPage == 1) aPlantCorrection = -16;
			else if (mPlantID >= SEED_PLASMAPEA - SEED_FLAMEPEA && mPlantID <= SEED_SHOOTINGSTAR - SEED_FLAMEPEA && mPage == 2) aPlantCorrection = -32;
			Image* aImage = nullptr;
			if (mApp->IsVersusLevel())
				aImage = IMAGE_P1_1;
			else
				aImage = IMAGE_P2_1;
			seedG.DrawImageMatrix(aImage, matr, 47 + (53 * ((mPlantID - aPlantCorrection) % 8)), 157 + (70 * ((mPlantID - aPlantCorrection) / 8)));
			
		}
		else
		{
			seedG.DrawImageMatrix(IMAGE_P2_1, matr, 507 + (53 * (mZombieID % 5)), 157 + (70 * (mZombieID / 5)));
		}
		int& arrowTime = mBoard->mPlayer2->mArrowTime;
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
			if (mApp->mIsKeyboardPlayer1 || (!mApp->mPlayerInfo->mIsNotCoop && !mApp->IsVersusLevel()))
			{
				if (mApp->IsVersusLevel())
					aImage = aImage = IMAGE_P1_3;
				else
					aImage = IMAGE_P2_3;
			}
			else
			{
				aImage = IMAGE_P2_3;
			}

			//seedG.DrawImageMatrix(aImage, matr, 200 + 16 * 1.25f, 200 + P2ArrowY);
			if (mApp->mIsKeyboardPlayer1 || (!mApp->mPlayerInfo->mIsNotCoop && !mApp->IsVersusLevel()))
			{
				seedG.DrawImageMatrix(aImage, matr, 47 + (53 * ((mPlantID - aPlantCorrection) % 8)), 157 + (70 * ((mPlantID - aPlantCorrection) / 8)) + P2ArrowY - 30.0f);
			}
			else
			{
				seedG.DrawImageMatrix(aImage, matr, 507 + (53 * (mZombieID % 5)), 157 + (70 * (mZombieID / 5)) + P2ArrowY - 30.0f);
			}			
			seedG.mScaleX = 1;
			seedG.mScaleY = 1;
			seedG.mTransX += translationX;
			seedG.mTransY += translationY;
		}
	}
	mToolTip->Draw(g);
	mToolTipP2->Draw(g);
	if (mVersusNoteIsOn) g->DrawImage(Sexy::IMAGE_VERSUS_NOTE, 0, 0);
}

//0x484C30
void SeedChooserScreen::UpdateViewLawn()
{
	if (mChooseState != CHOOSE_VIEW_LAWN) return;
	mViewLawnTime++;
	if (mViewLawnTime == 100) mBoard->DisplayAdviceAgain("[CLICK_TO_CONTINUE]", MESSAGE_STYLE_HINT_STAY, ADVICE_CLICK_TO_CONTINUE);
	else if (mViewLawnTime == 251) mViewLawnTime = 250;

	int aBoardX = BOARD_IMAGE_WIDTH_OFFSET - mApp->mWidth;
	int aSeedChooserY = SEED_CHOOSER_OFFSET_Y - Sexy::IMAGE_SEEDCHOOSER_BACKGROUND->mHeight;
	if (mViewLawnTime <= 100)
	{
		mBoard->Move(-TodAnimateCurve(0, 100, mViewLawnTime, aBoardX, 0, CURVE_EASE_IN_OUT), 0);
		Move(0, TodAnimateCurve(0, 40, mViewLawnTime, aSeedChooserY, SEED_CHOOSER_OFFSET_Y, CURVE_EASE_IN_OUT));
	}
	else if (mViewLawnTime <= 250)
	{
		mBoard->Move(0, 0);
		Move(0, SEED_CHOOSER_OFFSET_Y);
	}
	else if (mViewLawnTime <= 350)
	{
		mBoard->ClearAdvice(ADVICE_CLICK_TO_CONTINUE);
		mBoard->Move(-TodAnimateCurve(250, 350, mViewLawnTime, 0, aBoardX, CURVE_EASE_IN_OUT), 0);
		Move(0, TodAnimateCurve(310, 350, mViewLawnTime, SEED_CHOOSER_OFFSET_Y, aSeedChooserY, CURVE_EASE_IN_OUT));
	}
	else
	{
		mChooseState = CHOOSE_NORMAL;
		mViewLawnTime = 0;
		mMenuButton->mDisabled = false;
	}
}

//0x484FD0
void SeedChooserScreen::LandFlyingSeed(ChosenSeed& theChosenSeed)
{
	if (theChosenSeed.mSeedState == SEED_FLYING_TO_BANK)
	{
		theChosenSeed.mX = theChosenSeed.mEndX;
		theChosenSeed.mY = theChosenSeed.mEndY;
		theChosenSeed.mTimeStartMotion = 0;
		theChosenSeed.mTimeEndMotion = 0;
		theChosenSeed.mSeedState = SEED_IN_BANK;
		mSeedsInFlight--;
	}
	else if (theChosenSeed.mSeedState == SEED_FLYING_TO_CHOOSER)
	{
		theChosenSeed.mX = theChosenSeed.mEndX;
		theChosenSeed.mY = theChosenSeed.mEndY;
		theChosenSeed.mTimeStartMotion = 0;
		theChosenSeed.mTimeEndMotion = 0;
		theChosenSeed.mSeedState = SEED_IN_CHOOSER;
		mSeedsInFlight--;
		if (theChosenSeed.mSeedType == SEED_IMITATER)
		{
			theChosenSeed.mSeedState = SEED_PACKET_HIDDEN;
			theChosenSeed.mImitaterType = SEED_NONE;
			UpdateImitaterButton();
		}
	}
}

//0x485040
void SeedChooserScreen::UpdateCursor()
{
	if (mApp->GetDialogCount() || mBoard->mCutScene->IsInShovelTutorial() || mApp->mGameMode == GAMEMODE_UPSELL) 
		return;
	SeedType aMouseSeedType = SeedHitTest(mLastMouseX, mLastMouseY);
	if (aMouseSeedType != SEED_NONE)
	{
		ChosenSeed& aMouseChosenSeed = mChosenSeeds[aMouseSeedType];
		if (aMouseChosenSeed.mSeedState == SEED_IN_BANK && aMouseChosenSeed.mCrazyDavePicked)
			aMouseSeedType = SEED_NONE;
	}

	if (mMouseVisible && mChooseState != CHOOSE_VIEW_LAWN && ((aMouseSeedType != SEED_NONE && !SeedNotAllowedToPick(aMouseSeedType)) ||
		mRandomButton->IsMouseOver() || mViewLawnButton->IsMouseOver() || mAlmanacButton->IsMouseOver() || mImitaterButton->IsMouseOver() || mMapButton->IsMouseOver() ||
		mStoreButton->IsMouseOver() || mMenuButton->IsMouseOver() || mStartButton->IsMouseOver() || mLeftButton->IsMouseOver() || mRightButton->IsMouseOver() || mDiscordButton->IsMouseOver() ||
		mSkipButton->IsMouseOver() || mVersusButton->IsMouseOver() || mKeyboardButton->IsMouseOver()))
		mApp->SetCursor(CURSOR_HAND);
	else
		mApp->SetCursor(CURSOR_POINTER);
}

//0x4851A0
void SeedChooserScreen::Update()
{
	Widget::Update();

	int amount = -1;
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;
			amount++;
		}
	}
	//mMaxPage = amount / 49 - 1;
	mMaxPage = 2;

	int theRealPosIndex = -1;
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true && (plantDefinition.getPage() == mPage && !SeedPacket::IsZombiePack(plantDefinition.mSeedType)) || (plantDefinition.getPage() == mPageP2 && SeedPacket::IsZombiePack(plantDefinition.mSeedType))) {
			SeedType aSeedType = plantDefinition.mSeedType;
			ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
			theRealPosIndex++;

			if (aChosenSeed.mSeedState != SEED_IN_BANK)
			{
				GetSeedPositionInChooser(theRealPosIndex, aChosenSeed.mX, aChosenSeed.mY, aSeedType);
			}
		}
	}






	mLastMouseX = mApp->mWidgetManager->mLastMouseX;
	mLastMouseY = mApp->mWidgetManager->mLastMouseY;

	mSeedChooserAge++;
	mToolTip->Update();
	mToolTipP2->Update();


	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;
			if (mApp->SeedTypeAvailable(aSeedType))
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
				if (aChosenSeed.mSeedState == SEED_FLYING_TO_BANK || aChosenSeed.mSeedState == SEED_FLYING_TO_CHOOSER)
				{
					int aTimeStart = aChosenSeed.mTimeStartMotion;
					int aTimeEnd = aChosenSeed.mTimeEndMotion;
					aChosenSeed.mX = TodAnimateCurve(aTimeStart, aTimeEnd, mSeedChooserAge, aChosenSeed.mStartX, aChosenSeed.mEndX, CURVE_EASE_IN_OUT);
					aChosenSeed.mY = TodAnimateCurve(aTimeStart, aTimeEnd, mSeedChooserAge, aChosenSeed.mStartY, aChosenSeed.mEndY, CURVE_EASE_IN_OUT);
					if (mSeedChooserAge >= aChosenSeed.mTimeEndMotion)
					{
						LandFlyingSeed(aChosenSeed);
					}
				}
			}
		}
	}




	ShowToolTip();
	ShowToolTipP2();
	mLeftButton->Update();
	mRightButton->Update();
	mDiscordButton->Update();
	mStartButton->Update();
	mRandomButton->Update();
	mViewLawnButton->Update();
	mAlmanacButton->Update();
	mImitaterButton->Update();
	mStoreButton->Update();
	mSkipButton->Update();
	mVersusButton->Update();
	mKeyboardButton->Update();
	mMenuButton->Update();
	mMapButton->Update();
	UpdateViewLawn();
	UpdateCursor();
	MarkDirty();

	if (mClickCooldown > 0)
	{
		mClickCooldown--;
	}
}

//0x485340
int SeedChooserScreen::DisplayRepickWarningDialog(const SexyChar* theMessage)
{
	return mApp->LawnMessageBox(
		Dialogs::DIALOG_CHOOSER_WARNING,
		_S("[DIALOG_WARNING]"),
		theMessage,
		_S("[DIALOG_BUTTON_YES]"),
		_S("[REPICK_BUTTON]"),
		Dialog::BUTTONS_YES_NO
	) == Dialog::ID_YES;
}

//0x485370
int SeedChooserScreen::FlyersAreComming()
{
	for (int aWave = 0; aWave < mBoard->mNumWaves; aWave++)
	{
		for (int anIndex = 0; anIndex < MAX_ZOMBIES_IN_WAVE; anIndex++)
		{
			ZombieType aZombieType = mBoard->mZombiesInWave[aWave][anIndex];
			if (aZombieType == ZOMBIE_INVALID)
				break;

			if (aZombieType == ZOMBIE_BALLOON)
				return true;
		}
	}
	return false;
}

//0x4853D0
int SeedChooserScreen::FlyProtectionCurrentlyPlanted()
{
	Plant* aPlant = nullptr;
	while (mBoard->IteratePlants(aPlant))
	{
		if (aPlant->mSeedType == SEED_CATTAIL || aPlant->mSeedType == SEED_CACTUS)
		{
			return true;
		}
	}
	return false;
}

//0x485420
int SeedChooserScreen::CheckSeedUpgrade(SeedType theSeedTypeTo, SeedType theSeedTypeFrom)
{
	if (mApp->IsSurvivalMode() || !PickedPlantType(theSeedTypeTo) || PickedPlantType(theSeedTypeFrom))
		return true;

	SexyString aWarning = TodStringTranslate(_S("[SEED_CHOOSER_UPGRADE_WARNING]"));
	aWarning = TodReplaceString(aWarning, _S("{UPGRADE_TO}"), Plant::GetNameString(theSeedTypeTo));
	aWarning = TodReplaceString(aWarning, _S("{UPGRADE_FROM}"), Plant::GetNameString(theSeedTypeFrom));
	return DisplayRepickWarningDialog(aWarning.c_str());
}

//0x485600
void SeedChooserScreen::OnStartButton()
{
	if (mApp->mGameMode == GAMEMODE_CHALLENGE_SEEING_STARS && !PickedPlantType(SEED_STARFRUIT))
	{
		if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_SEEING_STARS_WARNING]")))
		{
			return;
		}
	}

	if (mApp->mGameMode == GAMEMODE_CHALLENGE_SEASTAR && !PickedPlantType(SEED_PINKSTAR))
	{
		if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_SEAING_STARS_WARNING]")))
		{
			return;
		}
	}

	if (mApp->IsFirstTimeAdventureMode() && mBoard->mLevel == 11 && !PickedPlantType(SEED_PUFFSHROOM))
	{
		if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_PUFFSHROOM_WARNING]")))
		{
			return;
		}
	}
	if (!PickedPlantType(SEED_SUNFLOWER) && !PickedPlantType(SEED_TWINSUNFLOWER) && !PickedPlantType(SEED_SUNSHROOM) &&
		!mBoard->mCutScene->IsSurvivalRepick() && mApp->mGameMode != GAMEMODE_CHALLENGE_LAST_STAND)
	{
		if (mApp->IsFirstTimeAdventureMode() && mBoard->mLevel == 11)
		{
			if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_NIGHT_SUN_WARNING]")))
			{
				return;
			}
		}
		else if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_SUN_WARNING]")))
		{
			return;
		}
	}
	if (mBoard->StageHasPool() && !PickedPlantType(SEED_LILYPAD) && !PickedPlantType(SEED_SEASHROOM) && !PickedPlantType(SEED_TANGLEKELP) && !PickedPlantType(SEED_PINKSTAR) 
		&& !mBoard->mCutScene->IsSurvivalRepick())
	{
		if (mApp->IsFirstTimeAdventureMode() && mBoard->mLevel == 21)
		{
			if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_LILY_WARNING]")))
			{
				return;
			}
		}
		else if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_POOL_WARNING]")))
		{
			return;
		}
	}
	if (mBoard->StageHasRoof() && !PickedPlantType(SEED_FLOWERPOT) && mApp->SeedTypeAvailable(SEED_FLOWERPOT) && !PickedPlantType(SEED_WATERPOT))
	{
		if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_ROOF_WARNING]")))
		{
			return;
		}
	}

	if (mApp->mGameMode == GAMEMODE_CHALLENGE_ART_CHALLENGE_WALLNUT && !PickedPlantType(SEED_WALLNUT))
	{
		if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_ART_WALLNUT_WARNING]")))
		{
			return;
		}
	}
	if (mApp->mGameMode == GAMEMODE_CHALLENGE_ART_CHALLENGE_SUNFLOWER &&
		(!PickedPlantType(SEED_STARFRUIT) || !PickedPlantType(SEED_UMBRELLA) || !PickedPlantType(SEED_WALLNUT)))
	{
		if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_ART_2_WARNING]")))
		{
			return;
		}
	}

	if (FlyersAreComming() && !FlyProtectionCurrentlyPlanted() && !PickedPlantType(SEED_CATTAIL) && !PickedPlantType(SEED_ECACTUS) && !PickedPlantType(SEED_CACTUS) && !PickedPlantType(SEED_BLOVER) && !PickedPlantType(SEED_HURRIKALE) &&
	    !PickedPlantType(SEED_REED))
	{
		if (!DisplayRepickWarningDialog(_S("[SEED_CHOOSER_FLYER_WARNING]")))
		{
			return;
		}
	}

	if (!CheckSeedUpgrade(SEED_GATLINGPEA, SEED_REPEATER) ||
		!CheckSeedUpgrade(SEED_WINTERMELON, SEED_MELONPULT) ||
		!CheckSeedUpgrade(SEED_TWINSUNFLOWER, SEED_SUNFLOWER) ||
		!CheckSeedUpgrade(SEED_SPIKEROCK, SEED_SPIKEWEED) ||
		!CheckSeedUpgrade(SEED_COBCANNON, SEED_KERNELPULT) ||
		!CheckSeedUpgrade(SEED_GOLD_MAGNET, SEED_MAGNETSHROOM) ||
		!CheckSeedUpgrade(SEED_GOLD_MAGNET, SEED_MAGNETSHROOM) ||
		!CheckSeedUpgrade(SEED_GLOOMSHROOM, SEED_FUMESHROOM) ||
		!CheckSeedUpgrade(SEED_ICYFUME, SEED_FUMESHROOM) ||
		!CheckSeedUpgrade(SEED_SUPERCHOMP, SEED_CHOMPER) ||
		!CheckSeedUpgrade(SEED_FLAMEWOOD, SEED_TORCHWOOD) ||
		!CheckSeedUpgrade(SEED_QUEENPEA, SEED_SNOWPEA) ||
		!CheckSeedUpgrade(SEED_VINENUT, SEED_TALLNUT) ||
		!CheckSeedUpgrade(SEED_THORNMOSS, SEED_SPIKEWEED) ||
		!CheckSeedUpgrade(SEED_BRAVESHROOM, SEED_SCAREDYSHROOM) ||
		!CheckSeedUpgrade(SEED_ECACTUS, SEED_CACTUS) ||
		!CheckSeedUpgrade(SEED_CATTAIL, SEED_LILYPAD))
		return;

	mCloseToolTip = true;
	CloseSeedChooser();
}

//0x4859B0
void SeedChooserScreen::PickRandomSeeds()
{
	for (int anIndex = mSeedsInBank; anIndex < mBoard->mSeedBank->mNumPackets; anIndex++)
	{
		SeedType aSeedType;
		do aSeedType = (SeedType)Rand(mApp->GetSeedsAvailable());
		while (!mApp->SeedTypeAvailable(aSeedType) || aSeedType == SEED_IMITATER || mChosenSeeds[aSeedType].mSeedState != SEED_IN_CHOOSER);
		ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
		aChosenSeed.mTimeStartMotion = 0;
		aChosenSeed.mTimeEndMotion = 0;
		aChosenSeed.mStartX = aChosenSeed.mX;
		aChosenSeed.mStartY = aChosenSeed.mY;
		GetSeedPositionInBank(anIndex, aChosenSeed.mEndX, aChosenSeed.mEndY, aChosenSeed.mSeedType);
		aChosenSeed.mSeedState = SEED_IN_BANK;
		aChosenSeed.mSeedIndexInBank = anIndex;
		mSeedsInBank++;
	}
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;
			LandFlyingSeed(mChosenSeeds[aSeedType]);

		}
	}
	CloseSeedChooser();
}

//0x485BB0
void SeedChooserScreen::ButtonDepress(int theId)
{
	if (mSeedsInFlight > 0 || mChooseState == CHOOSE_VIEW_LAWN || !mMouseVisible)
		return;

	if (theId == SeedChooserScreen::SeedChooserScreen_ViewLawn)
	{
		mChooseState = CHOOSE_VIEW_LAWN;
		mMenuButton->mDisabled = true;
		mViewLawnTime = 0;
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Almanac)
	{
		mApp->DoAlmanacDialog()->WaitForResult(true);
		mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Map)
	{

	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Right)
	{
		if ((((!mPlantsPick && !mApp->mIsKeyboardPlayer1) || (mPlantsPick && mApp->mIsKeyboardPlayer1)) && mApp->IsVersusLevel()) && !mApp->mDebugKeysEnabled)
		{
			mApp->PlaySample(SOUND_BUZZER);
			return;
		}
		if (mApp->mIsKeyboardPlayer1 && !mPlantsPick && mApp->IsVersusLevel())
		{
			if (mPageP2 < mMaxPage)
			{
				mPageP2++;
				if (mZombieID > 5) mZombieID = 0;
				//if (mPlantID > 15) mPlantID = 0;
			}
			else
			{
				mPageP2 = 0;
				if (mZombieID > 5) mZombieID = 0;
				//if (mPlantID > 15) mPlantID = 0;
			}
		}
		else
		{
			if (mPage < mMaxPage)
			{
				mPage++;
				//if (mZombieID > 5) mZombieID = 0;
				if (mPlantID > 15) mPlantID = 0;
			}
			else
			{
				mPage = 0;
				//if (mZombieID > 5) mZombieID = 0;
				if (mPlantID > 15) mPlantID = 0;
			}
		}
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Discord)
	{
		ShellExecute(NULL, "open", "https://discord.gg/rTz2QHD9aR", NULL, NULL, SW_SHOWNORMAL);
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Left)
	{
		if ((((!mPlantsPick && !mApp->mIsKeyboardPlayer1) || (mPlantsPick && mApp->mIsKeyboardPlayer1)) && mApp->IsVersusLevel()) && !mApp->mDebugKeysEnabled)
		{
			mApp->PlaySample(SOUND_BUZZER);
			return;
		}
		if (mApp->mIsKeyboardPlayer1 && !mPlantsPick && mApp->IsVersusLevel())
		{
			if (mPageP2 > 0)
			{
				mPageP2--;
				if (mZombieID > 5) mZombieID = 0;
				//if (mPlantID > 15) mPlantID = 0;
			}
			else
			{
				mPageP2 = mMaxPage;
				if (mZombieID > 5) mZombieID = 0;
				//if (mPlantID > 15) mPlantID = 0;
			}
		}
		else
		{
			if (mPage > 0)
			{
				mPage--;
				//if (mZombieID > 5) mZombieID = 0;
				if (mPlantID > 15) mPlantID = 0;
			}
			else
			{
				mPage = mMaxPage;
				//if (mZombieID > 5) mZombieID = 0;
				if (mPlantID > 15) mPlantID = 0;
			}
		}
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Store)
	{
		StoreScreen* aStore = mApp->ShowStoreScreen();
		aStore->mBackButton->SetLabel("[STORE_BACK_TO_GAME]");
		aStore->WaitForResult();
		if (aStore->mGoToTreeNow)
		{
			mApp->KillBoard();
			mApp->PreNewGame(GAMEMODE_TREE_OF_WISDOM, false);
		}
		else mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Skip)
	{
		mApp->DoCheatDialog();
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Versus)
	{
		mVersusNoteIsOn = !mVersusNoteIsOn;
		//mApp->LoadingCompleted();
		//mApp->KillGameSelector();
		//mApp->PreNewGame(GameMode::GAMEMODE_CHALLENGE_GLADIANTUAR, false);
	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Keyboard)
	{
		if (mCanSwitchSides)
		{
			mApp->mIsKeyboardPlayer1 = !mApp->mIsKeyboardPlayer1;
		}
		else mApp->PlaySample(SOUND_BUZZER);
		//int gridNumber;
		//if (mApp->mIsKeyboardPlayer1) gridNumber = 0;
		//else gridNumber = 8;
		if (!mApp->mIsKeyboardPlayer1) mBoard->mPlayer2->mX = mBoard->GridToPixelX(8, 0) + 33;
		else mBoard->mPlayer2->mX = mBoard->GridToPixelX(0, 0) + 33;

	}
	else if (theId == SeedChooserScreen::SeedChooserScreen_Menu)
	{
		mMenuButton->mIsOver = false;
		mMenuButton->mIsDown = false;
		UpdateCursor();
		mApp->DoNewOptions(false);
	}
	else if (mApp->GetSeedsAvailable() >= mBoard->mSeedBank->mNumPackets)
	{
		if (theId == SeedChooserScreen::SeedChooserScreen_Start)
			OnStartButton();
		else if (theId == SeedChooserScreen::SeedChooserScreen_Random)
			PickRandomSeeds();
	}
}

//0x485D80
SeedType SeedChooserScreen::SeedHitTest(int x, int y)
{
	if (mMouseVisible)
	{
		for each (auto plantDefinition in gPlantDefs)
		{
			ChosenSeed& aChosenSeed = mChosenSeeds[plantDefinition.mSeedType];

			if (true && (aChosenSeed.mSeedState == SEED_IN_BANK) || plantDefinition.getPage() == mPage && !SeedPacket::IsZombiePack(aChosenSeed.mSeedType) || plantDefinition.getPage() == mPageP2 && SeedPacket::IsZombiePack(aChosenSeed.mSeedType)) {
				SeedType aSeedType = plantDefinition.mSeedType;
				if (!mApp->SeedTypeAvailable(aSeedType) || aChosenSeed.mSeedState == SEED_PACKET_HIDDEN) continue;
				if (Rect(aChosenSeed.mX, aChosenSeed.mY, SEED_PACKET_WIDTH, SEED_PACKET_HEIGHT).Contains(x, y)) return aSeedType;
			}
		}

	}
	return SEED_NONE;
}

//0x485E20
SeedType SeedChooserScreen::FindSeedInBank(int theIndexInBank, bool isZombie)
{
	if (mApp->IsVersusLevel())
	{
		if (mApp->mWidgetManager->mLastMouseX > 400)
	{
		isZombie = true;
	}

	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;
			if (mApp->SeedTypeAvailable(aSeedType))
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
				if (aChosenSeed.mSeedState == SEED_IN_BANK && aChosenSeed.mSeedIndexInBank == theIndexInBank && !isZombie) return aSeedType;
				if (aChosenSeed.mSeedState == SEED_IN_BANK && aChosenSeed.mP2SeedIndexInBank == theIndexInBank && isZombie && SeedPacket::IsZombiePack(aSeedType)) return aSeedType;
			}
		}
	}

	return SEED_NONE;
	}
	else
	{
		for (SeedType aSeedType = SEED_PEASHOOTER; aSeedType < NUM_SEEDS_IN_CHOOSER; aSeedType = (SeedType)(aSeedType + 1))
		{
			if (mApp->SeedTypeAvailable(aSeedType))
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
				if (aChosenSeed.mSeedState == SEED_IN_BANK && aChosenSeed.mSeedIndexInBank == theIndexInBank) return aSeedType;
			}
		}
		return SEED_NONE;
	}

	
}

void SeedChooserScreen::EnableStartButton(int theEnabled)
{
	mStartButton->SetDisabled(!theEnabled);
	if (theEnabled) mStartButton->mColors[GameButton::COLOR_LABEL] = Color::White;
	else mStartButton->mColors[GameButton::COLOR_LABEL] = Color(64, 64, 64);
}

//0x485E90
void SeedChooserScreen::ClickedSeedInBank(ChosenSeed& theChosenSeed)
{
	if (mApp->IsVersusLevel() && !mApp->mDebugKeysEnabled)
	{
		mApp->PlaySample(Sexy::SOUND_BUZZER);
		return;
	}
	if (!SeedPacket::IsZombiePack(theChosenSeed.mSeedType))
	{
		for (int anIndex = theChosenSeed.mSeedIndexInBank + 1; anIndex < mBoard->mSeedBank->mNumPackets; anIndex++)
		{
			SeedType aSeedType = SEED_NONE;
			if (!SeedPacket::IsZombiePack(FindSeedInBank(anIndex, false)))
			{
				aSeedType = FindSeedInBank(anIndex, false);
			}
			if (aSeedType != SEED_NONE)
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
				aChosenSeed.mTimeStartMotion = mSeedChooserAge;
				aChosenSeed.mTimeEndMotion = mSeedChooserAge + 15;
				aChosenSeed.mStartX = aChosenSeed.mX;
				aChosenSeed.mStartY = aChosenSeed.mY;
				GetSeedPositionInBank(anIndex - 1, aChosenSeed.mEndX, aChosenSeed.mEndY, aChosenSeed.mSeedType);
				aChosenSeed.mSeedState = SEED_FLYING_TO_BANK;
				aChosenSeed.mSeedIndexInBank = anIndex - 1;
				mSeedsInFlight++;
			}
		}
	}
	else
	{
		for (int anIndex2 = theChosenSeed.mP2SeedIndexInBank + 1; anIndex2 < mBoard->mP2SeedBank->mNumPackets; anIndex2++)
		{
			SeedType aSeedType = SEED_NONE;
			if (SeedPacket::IsZombiePack(FindSeedInBank(anIndex2, false)))
			{
				aSeedType = FindSeedInBank(anIndex2, false);
			}

			if (aSeedType != SEED_NONE)
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
				aChosenSeed.mTimeStartMotion = mSeedChooserAge;
				aChosenSeed.mTimeEndMotion = mSeedChooserAge + 15;
				aChosenSeed.mStartX = aChosenSeed.mX;
				aChosenSeed.mStartY = aChosenSeed.mY;
				GetSeedPositionInBank(anIndex2 - 1, aChosenSeed.mEndX, aChosenSeed.mEndY, aChosenSeed.mSeedType);
				aChosenSeed.mSeedState = SEED_FLYING_TO_BANK;
				aChosenSeed.mP2SeedIndexInBank = anIndex2 - 1;
				mSeedsInFlight++;
			}
		}
	}
	theChosenSeed.mTimeStartMotion = mSeedChooserAge;
	theChosenSeed.mTimeEndMotion = mSeedChooserAge + 25;
	theChosenSeed.mStartX = theChosenSeed.mX;
	theChosenSeed.mStartY = theChosenSeed.mY;
	GetSeedPositionInChooser(theChosenSeed.mSeedType, theChosenSeed.mEndX, theChosenSeed.mEndY, theChosenSeed.mSeedType);
	theChosenSeed.mSeedState = SEED_FLYING_TO_CHOOSER;
	theChosenSeed.mSeedIndexInBank = 0;
	theChosenSeed.mP2SeedIndexInBank = 0;
	if (!SeedPacket::IsZombiePack(theChosenSeed.mSeedType)) mSeedsInBank--;
	else mP2SeedsInBank--;
	mSeedsInFlight++;
	RemoveToolTip();
	EnableStartButton(false);
	mApp->PlaySample(Sexy::SOUND_TAP);
}

//0x486030
void SeedChooserScreen::ClickedSeedInChooser(ChosenSeed& theChosenSeed)
{
	if (mApp->IsVersusLevel() && !mApp->mDebugKeysEnabled)
	{
		if (mKeyboardIsChoosing || (mPlantsPick && !mApp->mIsKeyboardPlayer1) || (!mPlantsPick && mApp->mIsKeyboardPlayer1))
		{
			mKeyboardIsChoosing = false;
			mPlantsPick = !mPlantsPick;
		}
		else
		{
			mApp->PlaySample(SOUND_BUZZER);
			return;
		}
		mCanSwitchSides = false;
	}

	if ((mSeedsInBank == mBoard->mSeedBank->mNumPackets && !mApp->IsVersusLevel()) ||
		(mSeedsInBank == 6 && mApp->IsVersusLevel() && !SeedPacket::IsZombiePack(theChosenSeed.mSeedType))) //can't go above 6 seedslots
		return;

	else if ((mSeedsInBank == mBoard->mSeedBank->mNumPackets && !mApp->IsVersusLevel()) ||
		(mP2SeedsInBank == 6 && mApp->IsVersusLevel() && SeedPacket::IsZombiePack(theChosenSeed.mSeedType)))
		return;

	theChosenSeed.mTimeStartMotion = mSeedChooserAge;
	theChosenSeed.mTimeEndMotion = mSeedChooserAge + 25;
	theChosenSeed.mStartX = theChosenSeed.mX;
	theChosenSeed.mStartY = theChosenSeed.mY;
	if (!SeedPacket::IsZombiePack(theChosenSeed.mSeedType))
	{
		GetSeedPositionInBank(mSeedsInBank, theChosenSeed.mEndX, theChosenSeed.mEndY, theChosenSeed.mSeedType);
		theChosenSeed.mSeedIndexInBank = mSeedsInBank;
		mSeedsInBank++;
	}
	else
	{
		GetSeedPositionInBank(mP2SeedsInBank, theChosenSeed.mEndX, theChosenSeed.mEndY, theChosenSeed.mSeedType);
		theChosenSeed.mP2SeedIndexInBank = mP2SeedsInBank;
		mP2SeedsInBank++;
	}
	theChosenSeed.mSeedState = SEED_FLYING_TO_BANK;	
	//theChosenSeed.mSeedType = SEED_GRAVE;
	mSeedsInFlight++;
	//mSeedsInBank++;

	RemoveToolTip();
	mApp->PlaySample(Sexy::SOUND_TAP);
	if (mSeedsInBank == mBoard->mSeedBank->mNumPackets && !mApp->IsVersusLevel())
		EnableStartButton(true);
	else if ((mSeedsInBank == 6 && mP2SeedsInBank == 6 && mApp->IsVersusLevel()))
		EnableStartButton(true);
}

void SeedChooserScreen::ShowToolTipP2()
{
	if (mBoard->mCutScene->mCutsceneTime < 4100)
		return;

	if (!mApp->mActive || mApp->GetDialogCount() > 0 || mChooseState == CHOOSE_VIEW_LAWN || (mApp->mPlayerInfo->mIsNotCoop && !mApp->IsVersusLevel()) || mCloseToolTip)
	{
		RemoveToolTipP2();
		return;
	}
	else
	{
		int aPage2Zombies = 0;
		int aPage2Plants = 0;
		if (mPage == 1) aPage2Plants = SEED_PULTSHROOM;
		else if (mPage == 2) aPage2Plants = SEED_FLAMEPEA;
		if (mPageP2 == 1) aPage2Zombies = 30;
		else if (mPageP2 == 2) aPage2Zombies = 35;
		SeedType aSeedType;
		ChosenSeed aChosenSeed;
		if (!mApp->IsVersusLevel() || mApp->mIsKeyboardPlayer1)
		{
			aChosenSeed = mChosenSeeds[mPlantID + aPage2Plants];
			aSeedType = aChosenSeed.mSeedType;
		}
		else
		{
			aChosenSeed = mChosenSeeds[mZombieID + SEED_VERSUS_NORMAL + aPage2Zombies];
			aSeedType = aChosenSeed.mSeedType;
		}

		if (!mApp->SeedTypeAvailable(aSeedType))
		{
			RemoveToolTipP2();
			return;
		}

		uint aRecFlags = SeedNotRecommendedToPick(aSeedType);
		if (SeedNotAllowedToPickVersusPlants(aSeedType) && !mPlantsPick && !mApp->mDebugKeysEnabled)
		{
			mToolTipP2->SetWarningText(_S("[NOT_ALLOWED_VERSUS_PLANTS]"), false);
		}
		else if (SeedNotAllowedToPickVersusZombies(aSeedType) && mPlantsPick && !mApp->mDebugKeysEnabled)
		{
			mToolTipP2->SetWarningText(_S("[NOT_ALLOWED_VERSUS_ZOMBIES]"), false);
		}
		else if (SeedNotAllowedToPick(aSeedType))
		{
			mToolTipP2->SetWarningText(_S("[NOT_ALLOWED_ON_THIS_LEVEL]"), false);
		}
		else if (SeedNotAllowedDuringTrial(aSeedType))
		{
			mToolTipP2->SetWarningText(_S("[FULL_VERSION_ONLY]"), false);
		}
		else if (aChosenSeed.mSeedState == SEED_IN_BANK && aChosenSeed.mCrazyDavePicked)
		{
			mToolTipP2->SetWarningText(_S("[CRAZY_DAVE_WANTS]"), false);
		}
		else if ((SeedPacket::IsZombiePack(aChosenSeed.mSeedType) && aChosenSeed.mSeedType != SEED_GRAVE && aChosenSeed.mSeedType != SEED_VERSUS_ZOMBOSS && aChosenSeed.mSeedType != SEED_VERSUS_FLAG && Zombie::ZombieTypeCanGoInPool(Challenge::IZombieSeedTypeToZombieType(aChosenSeed.mSeedType)) || aChosenSeed.mSeedType == SEED_VERSUS_BUNGEE) && 
			(mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_POOL || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_FOG))
		{
			mToolTipP2->SetWarningText(_S("[CAN_BE_PLACED_IN_WATER]"), true);
		}
		else if ((aChosenSeed.mSeedType == SEED_VERSUS_SNORKEL || aChosenSeed.mSeedType == SEED_VERSUS_DOLPHIN) && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_POOL && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_FOG)
		{
			mToolTipP2->SetWarningText(_S("[NOT_RECOMMENDED_FOR_LEVEL]"), false);
		}
		else if ((aChosenSeed.mSeedType == SEED_VERSUS_DANCER || aChosenSeed.mSeedType == SEED_VERSUS_DIGGER) && (mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON))
		{
			mToolTipP2->SetWarningText(_S("[NOT_RECOMMENDED_FOR_LEVEL]"), false);
		}
		else if (aRecFlags != 0U)
		{
			if (TestBit(aRecFlags, NOT_RECOMMENDED_NOCTURNAL))
			{
				mToolTipP2->SetWarningText(_S("[NOCTURNAL_WARNING]"), false);
			}
			else
			{
				mToolTipP2->SetWarningText(_S("[NOT_RECOMMENDED_FOR_LEVEL]"), false);
			}
		}
		else
		{
			mToolTipP2->SetWarningText(_S(""), false);
		}

		mToolTipP2->SetTitle(Plant::GetNameString(aSeedType, SEED_NONE));
		mToolTipP2->SetLabel(Plant::GetToolTip(aSeedType));
		int aSeedX, aSeedY;
		GetSeedPositionInChooser(aSeedType, aSeedX, aSeedY, aSeedType);
		mToolTipP2->mX = aSeedX - 55.0f;
		mToolTipP2->mY = aSeedY + 70.0f;
		mToolTipP2->mVisible = true;
		mToolTipSeed = aSeedType;
	}
}

//0x486150
void SeedChooserScreen::ShowToolTip()
{
	if (!mApp->mWidgetManager->mMouseIn || !mApp->mActive || mApp->GetDialogCount() > 0 || mChooseState == CHOOSE_VIEW_LAWN)
	{
		RemoveToolTip();
	}
	else if (mSeedsInFlight <= 0)
	{
		if (mImitaterButton->IsMouseOver() && mMouseVisible)
		{
			mToolTip->SetLabel(Plant::GetToolTip(SEED_IMITATER));
			mToolTip->SetTitle(Plant::GetNameString(SEED_IMITATER));
			mToolTip->SetWarningText(_S(""), false);
			mToolTip->mX = (SEED_PACKET_WIDTH - mToolTip->mWidth) / 2 + mImitaterButton->mX;
			mToolTip->mY = mImitaterButton->mY - mToolTip->mHeight;
			mToolTip->mVisible = true;
		}
		else
		{
			SeedType aSeedType = SeedHitTest(mLastMouseX, mLastMouseY);
			if (aSeedType == SEED_NONE || ((!mApp->mIsKeyboardPlayer1 && SeedPacket::IsZombiePack(aSeedType) || (mApp->mIsKeyboardPlayer1 && !SeedPacket::IsZombiePack(aSeedType))) && mApp->IsVersusLevel()))
			{
				RemoveToolTip();
			}
			else if (aSeedType != mToolTipSeed)
			{
				RemoveToolTip();
				ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
				uint aRecFlags = SeedNotRecommendedToPick(aSeedType);
				if (SeedNotAllowedToPickVersusPlants(aSeedType) && !mPlantsPick && !mApp->mDebugKeysEnabled)
				{
					mToolTip->SetWarningText(_S("[NOT_ALLOWED_VERSUS_PLANTS]"), false);
				}
				else if (SeedNotAllowedToPickVersusZombies(aSeedType) && mPlantsPick && !mApp->mDebugKeysEnabled)
				{
					mToolTip->SetWarningText(_S("[NOT_ALLOWED_VERSUS_ZOMBIES]"), false);
				}
				else if (SeedNotAllowedToPick(aSeedType))
				{
					mToolTip->SetWarningText(_S("[NOT_ALLOWED_ON_THIS_LEVEL]"), false);
				}
				else if (SeedNotAllowedDuringTrial(aSeedType))
				{
					mToolTip->SetWarningText(_S("[FULL_VERSION_ONLY]"), false);
				}
				else if (aChosenSeed.mSeedState == SEED_IN_BANK && aChosenSeed.mCrazyDavePicked)
				{
					mToolTip->SetWarningText(_S("[CRAZY_DAVE_WANTS]"), false);
				}
				else if ((SeedPacket::IsZombiePack(aChosenSeed.mSeedType) && aChosenSeed.mSeedType != SEED_GRAVE && aChosenSeed.mSeedType != SEED_VERSUS_ZOMBOSS && aChosenSeed.mSeedType != SEED_VERSUS_FLAG && Zombie::ZombieTypeCanGoInPool(Challenge::IZombieSeedTypeToZombieType(aChosenSeed.mSeedType)) || aChosenSeed.mSeedType == SEED_VERSUS_BUNGEE) &&
					(mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_POOL || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_FOG))
				{
					mToolTip->SetWarningText(_S("[CAN_BE_PLACED_IN_WATER]"), true);
				}
				else if ((aChosenSeed.mSeedType == SEED_VERSUS_SNORKEL || aChosenSeed.mSeedType == SEED_VERSUS_DOLPHIN) && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_POOL && mApp->mGameMode != GAMEMODE_CHALLENGE_VERSUS_FOG)
				{
					mToolTip->SetWarningText(_S("[NOT_RECOMMENDED_FOR_LEVEL]"), false);
				}
				else if ((aChosenSeed.mSeedType == SEED_VERSUS_DANCER || aChosenSeed.mSeedType == SEED_VERSUS_DIGGER) && (mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_ROOF || mApp->mGameMode == GAMEMODE_CHALLENGE_VERSUS_MOON))
				{
					mToolTip->SetWarningText(_S("[NOT_RECOMMENDED_FOR_LEVEL]"), false);
				}
				else if (aRecFlags != 0U)
				{
					if (TestBit(aRecFlags, NOT_RECOMMENDED_NOCTURNAL))
					{
						mToolTip->SetWarningText(_S("[NOCTURNAL_WARNING]"), false);
					}
					else
					{
						mToolTip->SetWarningText(_S("[NOT_RECOMMENDED_FOR_LEVEL]"), false);
					}
				}
				else
				{
					mToolTip->SetWarningText(_S(""), false);
				}

				if (aSeedType == SEED_IMITATER)
				{
					mToolTip->SetTitle(Plant::GetNameString(aSeedType, aChosenSeed.mImitaterType));
					mToolTip->SetLabel(Plant::GetToolTip(aChosenSeed.mImitaterType));
				}
				else
				{
					mToolTip->SetTitle(Plant::GetNameString(aSeedType, SEED_NONE));
					mToolTip->SetLabel(Plant::GetToolTip(aSeedType));
				}

				int aSeedX, aSeedY;


				int theRealPosIndex = -1;

				for each (auto plantDefinition in gPlantDefs)
				{
					if (true && (aChosenSeed.mSeedState == SEED_IN_BANK) || plantDefinition.getPage() == mPage && !SeedPacket::IsZombiePack(aChosenSeed.mSeedType) || plantDefinition.getPage() == mPageP2 && SeedPacket::IsZombiePack(aChosenSeed.mSeedType)) {
						SeedType aSeedTypeB = plantDefinition.mSeedType;
						theRealPosIndex++;
						if (aSeedType == aSeedTypeB) break;
					}
				}


				if (aChosenSeed.mSeedState == SEED_IN_BANK)
				{
					if (!SeedPacket::IsZombiePack(aChosenSeed.mSeedType)) GetSeedPositionInBank(aChosenSeed.mSeedIndexInBank, aSeedX, aSeedY, aChosenSeed.mSeedType);
					else GetSeedPositionInBank(aChosenSeed.mP2SeedIndexInBank, aSeedX, aSeedY, aChosenSeed.mSeedType);
				}
				else
				{
					GetSeedPositionInChooser(theRealPosIndex, aSeedX, aSeedY, aSeedType);
				}

				mToolTip->mX = ClampInt((SEED_PACKET_WIDTH - mToolTip->mWidth) / 2 + aSeedX, 0, BOARD_WIDTH - mToolTip->mWidth);
				mToolTip->mY = aSeedY + 70;
				mToolTip->mVisible = true;
				mToolTipSeed = aSeedType;
			}
		}
	}
}

void SeedChooserScreen::RemoveToolTip()
{
	mToolTip->mVisible = false;
	mToolTipSeed = SEED_NONE;
}

void SeedChooserScreen::RemoveToolTipP2()
{
	mToolTipP2->mVisible = false;
	mToolTipSeed = SEED_NONE;
}

//0x486600
void SeedChooserScreen::CancelLawnView()
{
	if (mChooseState == CHOOSE_VIEW_LAWN && mViewLawnTime > 100 && mViewLawnTime <= 250) mViewLawnTime = 251;
}

//0x486630
void SeedChooserScreen::MouseUp(int x, int y, int theClickCount)
{
	if (theClickCount == 1)
	{
		if (mMenuButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Menu);
		else if (mStartButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Start);
		else if (mLeftButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Left);
		else if (mRightButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Right);
		else if (mDiscordButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Discord);
		else if (mAlmanacButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Almanac);
		else if (mStoreButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Store);
		else if (mVersusButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Versus);
		else if (mKeyboardButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Keyboard);
		else if (mSkipButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Skip);
		else if (mMapButton->IsMouseOver()) ButtonDepress(SeedChooserScreen::SeedChooserScreen_Map);
	}
}

//0x4866E0
void SeedChooserScreen::UpdateImitaterButton()
{
	if (!mApp->SeedTypeAvailable(SEED_IMITATER))
	{
		mImitaterButton->mBtnNoDraw = true;
		mImitaterButton->mDisabled = true;
	}
	else
	{
		mImitaterButton->mBtnNoDraw = false;
		mImitaterButton->mDisabled = mChosenSeeds[SEED_IMITATER].mSeedState != SEED_PACKET_HIDDEN;
	}
}

//0x486770
void SeedChooserScreen::MouseDown(int x, int y, int theClickCount)
{
	Widget::MouseDown(x, y, theClickCount);

	if (mSeedsInFlight > 0)
	{
		for each (auto plantDefinition in gPlantDefs)
		{
			if (true) {
				SeedType aSeedType = plantDefinition.mSeedType;
				LandFlyingSeed(mChosenSeeds[aSeedType]);

			}
		}
	}

	if (mChooseState == CHOOSE_VIEW_LAWN)
	{
		CancelLawnView();
	}
	else if (mRandomButton->IsMouseOver())
	{
		mApp->PlaySample(Sexy::SOUND_TAP);
		ButtonDepress(SeedChooserScreen::SeedChooserScreen_Random);
	}
	else if (mViewLawnButton->IsMouseOver())
	{
		mApp->PlaySample(Sexy::SOUND_TAP);
		ButtonDepress(SeedChooserScreen::SeedChooserScreen_ViewLawn);
	}
	else if (mMenuButton->IsMouseOver())
	{
		mApp->PlaySample(Sexy::SOUND_GRAVEBUTTON);
	}
	else if (mStartButton->IsMouseOver() || mAlmanacButton->IsMouseOver() || mLeftButton->IsMouseOver() || mRightButton->IsMouseOver() || mStoreButton->IsMouseOver() || mSkipButton->IsMouseOver() || mVersusButton->IsMouseOver() || mKeyboardButton->IsMouseOver() || mDiscordButton->IsMouseOver() || mMapButton->IsMouseOver())
	{
		mApp->PlaySample(Sexy::SOUND_TAP);
	}
	else if (mImitaterButton->IsMouseOver())
	{
		if (mSeedsInBank != mBoard->mSeedBank->mNumPackets)
		{
			mApp->PlaySample(Sexy::SOUND_TAP);
			ImitaterDialog* aDialog = new ImitaterDialog();
			mApp->AddDialog(aDialog->mId, aDialog);
			aDialog->Resize((mWidth - aDialog->mWidth) / 2, (mHeight - aDialog->mHeight) / 2, aDialog->mWidth, aDialog->mHeight);
			mApp->mWidgetManager->SetFocus(aDialog);
		}
	}
	else
	{
		if (!mBoard->mSeedBank->ContainsPoint(x, y) && !mAlmanacButton->IsMouseOver() && !mMapButton->IsMouseOver() && !mStoreButton->IsMouseOver() && !mVersusButton->IsMouseOver() && !mKeyboardButton->IsMouseOver() && !mSkipButton->IsMouseOver() && mApp->CanShowAlmanac())
		{
			Zombie* aZombie = mBoard->ZombieHitTest(x - mBoard->mX, y - mBoard->mY);
			if (aZombie && aZombie->mFromWave == Zombie::ZOMBIE_WAVE_CUTSCENE && aZombie->mZombieType != ZOMBIE_REDEYE_GARGANTUAR && aZombie->mZombieType != ZOMBIE_GIGA_BASIC && aZombie->mZombieType != ZOMBIE_GIGA_CONEHEAD && aZombie->mZombieType != ZOMBIE_GIGA_BUCKETHEAD && aZombie->mZombieType != ZOMBIE_GIGA_POLEVAULTER && aZombie->mZombieType != ZOMBIE_GIGA_FOOTBALL)
			{
				mApp->DoAlmanacDialog(SEED_NONE, aZombie->mZombieType)->WaitForResult(true);
				mApp->mMusic->MakeSureMusicIsPlaying(MUSIC_TUNE_CHOOSE_YOUR_SEEDS);
				return;
			}
		}

		SeedType aSeedType = SeedHitTest(x, y);
		if (aSeedType != SEED_NONE && !SeedNotAllowedToPick(aSeedType))
		{
			if (SeedNotAllowedDuringTrial(aSeedType))
			{
				mApp->PlaySample(Sexy::SOUND_TAP);
				if (mApp->LawnMessageBox(
					DIALOG_MESSAGE,
					_S("[GET_FULL_VERSION_TITLE]"),
					_S("[GET_FULL_VERSION_BODY]"),
					_S("[GET_FULL_VERSION_YES_BUTTON]"),
					_S("[GET_FULL_VERSION_NO_BUTTON]"),
					Dialog::BUTTONS_YES_NO
				) == Dialog::ID_YES)
				{
					if (mApp->mDRM)
					{
						mApp->mDRM->BuyGame();
					}
					mApp->DoBackToMain();
				}
			}
			else
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
				if (aChosenSeed.mSeedState == SEED_IN_BANK)
				{
					if (aChosenSeed.mCrazyDavePicked)
					{
						mApp->PlaySample(Sexy::SOUND_BUZZER);
						mToolTip->FlashWarning();
					}
					else ClickedSeedInBank(aChosenSeed);
				}
				else if (aChosenSeed.mSeedState == SEED_IN_CHOOSER)
					ClickedSeedInChooser(aChosenSeed);
			}
		}
	}
}

//0x486CE0
int SeedChooserScreen::PickedPlantType(SeedType theSeedType)
{
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;
			ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
			if (aChosenSeed.mSeedState == SEED_IN_BANK)
			{
				if (aChosenSeed.mSeedType == theSeedType || (aChosenSeed.mSeedType == SEED_IMITATER && aChosenSeed.mImitaterType == theSeedType))
				{
					return true;
				}
			}
		}
	}

	return false;
}

//0x486D20
void SeedChooserScreen::CloseSeedChooser()
{	
	DBG_ASSERT(mBoard->mSeedBank->mNumPackets == mBoard->GetNumSeedsInBank());
	if (mApp->IsVersusLevel()) mBoard->mSeedBank->mNumPackets = 12;
	for (int anIndex = 0; anIndex < mBoard->mSeedBank->mNumPackets; anIndex++)
	{
		SeedType aSeedType;
		if (mApp->IsVersusLevel())
		{
			if (anIndex < 6) aSeedType = FindSeedInBank(anIndex, false);
			else aSeedType = FindSeedInBank(anIndex - 6, true);
		}
		else aSeedType = FindSeedInBank(anIndex, false);
		ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
		SeedPacket& aSeedPacket = mBoard->mSeedBank->mSeedPackets[anIndex];	
		aSeedPacket.SetPacketType(aSeedType, aChosenSeed.mImitaterType);
		if (aChosenSeed.mRefreshing)
		{
			aSeedPacket.mRefreshCounter = aChosenSeed.mRefreshCounter;
			aSeedPacket.mRefreshTime = Plant::GetRefreshTime(aSeedPacket.mPacketType, aSeedPacket.mImitaterType);
			aSeedPacket.mRefreshing = true;
			aSeedPacket.mActive = false;
		}
	}
	mBoard->mCutScene->EndSeedChooser();
}

//0x486E80
void SeedChooserScreen::KeyDown(KeyCode theKey)
{
	mBoard->DoTypingCheck(theKey);
	int aPage2Plants = 0;
	if (mPage == 1) aPage2Plants = SEED_PULTSHROOM;
	else if (mPage == 2) aPage2Plants = SEED_FLAMEPEA;
	int aPage2Zombies = 0;
	if (mPageP2 == 1) aPage2Zombies = 30;
	else if (mPageP2 == 2) aPage2Zombies = 35;
	if (theKey == KeyCode::KEYCODE_SPACE && mClickCooldown == 0)
	{
		if (mCanSwitchSides)
		{
			//if ((mSeedsInBank == 6 && mP2SeedsInBank == 6 && mApp->mGameMode == GameMode::GAMEMODE_CHALLENGE_VERSUS))
			{
				//mApp->PlaySample(Sexy::SOUND_TAP);
				//OnStartButton();
			}
			//else
			{
				mApp->PlaySample(Sexy::SOUND_TAP);
				mApp->mIsKeyboardPlayer1 = !mApp->mIsKeyboardPlayer1;
				if (!mApp->mIsKeyboardPlayer1) mBoard->mPlayer2->mX = mBoard->GridToPixelX(8, 0) + 33;
				else mBoard->mPlayer2->mX = mBoard->GridToPixelX(0, 0) + 33;
				mPlantID = 0;
				mZombieID = 0;
			}
			mClickCooldown = 50;
		}
		else mApp->PlaySample(SOUND_BUZZER);
	}
	else if (theKey == GetKeyCodeFromName("q") && mClickCooldown == 0)
	{
		if (((mPlantsPick && mApp->mIsKeyboardPlayer1) || (!mPlantsPick && !mApp->mIsKeyboardPlayer1)) || mApp->mDebugKeysEnabled || (!mApp->IsVersusLevel()))
		{
			if (!mApp->mIsKeyboardPlayer1 && !mPlantsPick && mApp->IsVersusLevel())
			{
				mApp->PlaySample(Sexy::SOUND_TAP);
				if (mZombieID > 5 && mPageP2 == 1) mZombieID = 0;
				else if (mPageP2 == 0) mZombieID = 0;
				if (mPageP2 == 0) mPageP2 = mMaxPage;
				else mPageP2--;
			}
			else
			{
				mApp->PlaySample(Sexy::SOUND_TAP);
				if (mPlantID > 15 && mPage == 1) mPlantID = 0;
				else if (mPlantID > 7 && mPage == 2) mPlantID = 0;
				if (mPage == 0) mPage = mMaxPage;
				else mPage--;				
			}
			mClickCooldown = 50;
		}
		else mApp->PlaySample(SOUND_BUZZER);
	}
	else if (theKey == GetKeyCodeFromName("e") && mClickCooldown == 0)
	{
		if (((mPlantsPick && mApp->mIsKeyboardPlayer1) || (!mPlantsPick && !mApp->mIsKeyboardPlayer1)) || mApp->mDebugKeysEnabled || (!mApp->IsVersusLevel()))
		{
			if (!mApp->mIsKeyboardPlayer1 && !mPlantsPick && mApp->IsVersusLevel())
			{
				if (mZombieID > 5 && mPageP2 == 0) mZombieID = 0;
				else if (mPageP2 == 1) mZombieID = 0;
				if (mPageP2 == mMaxPage) mPageP2 = 0;
				else mPageP2++;
			}
			else
			{
				if (mPlantID > 15 && mPage == 0) mPlantID = 0;
				else if (mPlantID > 7 && mPage == 1) mPlantID = 0;
				if (mPage == mMaxPage) mPage = 0;
				else mPage++;
			}
			mApp->PlaySample(Sexy::SOUND_TAP);
			mClickCooldown = 50;
		}
		else mApp->PlaySample(SOUND_BUZZER);
	}
	else if (theKey == GetKeyCodeFromName("d"))
	{
		if (((mZombieID + 1) % 5 != 0 && !mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel()) && mPageP2 != 2) mZombieID++;
		else if (((mPlantID + 1) % 8 != 0) && !(mPage == 2 && mPlantID == SEED_SHOOTINGSTAR - SEED_FLAMEPEA)) mPlantID++;
	}
	else if (theKey == GetKeyCodeFromName("a"))
	{
		if ((mZombieID % 5 != 0 && !mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel()) && mPageP2 != 2) mZombieID--;
		else if (mPlantID % 8 != 0) mPlantID--;
	}
	else if (theKey == GetKeyCodeFromName("w"))
	{
		if (mZombieID >= SEED_VERSUS_NEWSPAPER - SEED_VERSUS_NORMAL && !mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel()) mZombieID -= 5;
		else if (mPlantID >=  SEED_PUFFSHROOM && mPlantID <= SEED_MELONPULT && mPage == 0) mPlantID -= 8;
		else if (mPlantID >= SEED_GATLINGPEA && mPlantID <= SEED_COBCANNON && mPage == 0) mPlantID -= SEED_GATLINGPEA - SEED_CABBAGEPULT;
		else if (mPlantID >= SEED_BEE_SHOOTER - SEED_PULTSHROOM && mPlantID <= SEED_AMPLI_FLOWER - SEED_PULTSHROOM && mPage == 1) mPlantID -= SEED_BEE_SHOOTER - SEED_PULTSHROOM;
		else if (mPlantID >= SEED_ICYFUME - SEED_PULTSHROOM && mPlantID <= SEED_ECACTUS - SEED_PULTSHROOM && mPage == 1) mPlantID -= SEED_ICYFUME - SEED_BEE_SHOOTER;
		else if (mPlantID >= SEED_PLASMAPEA - SEED_FLAMEPEA && mPlantID <= SEED_SHOOTINGSTAR - SEED_FLAMEPEA && mPage == 2) mPlantID -= SEED_PLASMAPEA - SEED_FLAMEPEA;
	}
	else if (theKey == GetKeyCodeFromName("s"))
	{
		if (((mZombieID <= SEED_VERSUS_GARGANTUAR_GIGA - SEED_VERSUS_NORMAL && mPageP2 == 0 && !mApp->mIsKeyboardPlayer1)) && mApp->IsVersusLevel()) mZombieID += 5;
		else if ((mPlantID < SEED_CABBAGEPULT && mPage == 0) || (mPlantID < SEED_BEE_SHOOTER - SEED_PULTSHROOM && mPage == 1)) mPlantID += 8;
		else if (mPlantID >= SEED_CABBAGEPULT && mPlantID <= SEED_MELONPULT && mPage == 0) mPlantID += SEED_GATLINGPEA - SEED_CABBAGEPULT;
		else if (mPlantID >= SEED_BEE_SHOOTER - SEED_PULTSHROOM && mPlantID <= SEED_AMPLI_FLOWER - SEED_PULTSHROOM && mPage == 1) mPlantID += SEED_ICYFUME - SEED_BEE_SHOOTER;
		else if (mPlantID >= SEED_FLAMEPEA - SEED_FLAMEPEA && mPlantID <= SEED_PEPPER - SEED_FLAMEPEA && mPage == 2) mPlantID += SEED_PLASMAPEA - SEED_FLAMEPEA;
	}
	else if (theKey == GetKeyCodeFromName("j") && mClickCooldown == 0)
	{
		if (mP2SeedsInBank < 6 && !mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel())
		{
			if (!mPlantsPick || mApp->mDebugKeysEnabled)
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[mZombieID + SEED_VERSUS_NORMAL + aPage2Zombies];
				if (aChosenSeed.mSeedState == SEED_IN_CHOOSER && mApp->SeedTypeAvailable(aChosenSeed.mSeedType))
				{
					mKeyboardIsChoosing = true;
					ClickedSeedInChooser(aChosenSeed);
					mApp->PlaySample(Sexy::SOUND_TAP);
					mClickCooldown = 50;
				}
			}
			else mApp->PlaySample(SOUND_BUZZER);
		}
		else if ((mSeedsInBank < 6 && mApp->mIsKeyboardPlayer1) || (mSeedsInBank < 10 && !mApp->IsVersusLevel()))
		{
			if (mPlantsPick || mApp->mDebugKeysEnabled || !mApp->mPlayerInfo->mIsNotCoop)
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[mPlantID + aPage2Plants];
				if (aChosenSeed.mSeedState == SEED_IN_CHOOSER && !SeedNotAllowedToPick(aChosenSeed.mSeedType) && mApp->SeedTypeAvailable(aChosenSeed.mSeedType))
				{
					mKeyboardIsChoosing = true;
					ClickedSeedInChooser(aChosenSeed);
					mApp->PlaySample(Sexy::SOUND_TAP);
					mClickCooldown = 50;
				}
			}
			else mApp->PlaySample(SOUND_BUZZER);
		}
	}
	else if (theKey == GetKeyCodeFromName("k") && mClickCooldown == 0)
	{
		if (mApp->mDebugKeysEnabled || !mApp->mPlayerInfo->mIsNotCoop)
		{
			if (!mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel())
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[mZombieID + SEED_VERSUS_NORMAL + aPage2Zombies];
				if (aChosenSeed.mSeedState != SEED_IN_CHOOSER)
				{
					ClickedSeedInBank(aChosenSeed);
					mApp->PlaySample(Sexy::SOUND_TAP);
					mClickCooldown = 50;
				}
			}
			else
			{
				ChosenSeed& aChosenSeed = mChosenSeeds[mPlantID + aPage2Plants];
				if (aChosenSeed.mSeedState != SEED_IN_CHOOSER)
				{
					ClickedSeedInBank(aChosenSeed);
					mApp->PlaySample(Sexy::SOUND_TAP);
					mClickCooldown = 50;
				}
			}
		}
		else mApp->PlaySample(Sexy::SOUND_BUZZER);
	}
}

//0x486EA0
void SeedChooserScreen::KeyChar(SexyChar theChar)
{
	if (mChooseState == CHOOSE_VIEW_LAWN && (theChar == ' ' || theChar == '\r' || theChar == '\u001B'))
		CancelLawnView();
	else if (mApp->mTodCheatKeys && theChar == '\u001B')
		PickRandomSeeds();
	else mBoard->KeyChar(theChar);
}

//0x486F10
void SeedChooserScreen::UpdateAfterPurchase()
{
	for each (auto plantDefinition in gPlantDefs)
	{
		if (true) {
			SeedType aSeedType = plantDefinition.mSeedType;
			ChosenSeed& aChosenSeed = mChosenSeeds[aSeedType];
			if (aChosenSeed.mSeedState == SEED_IN_BANK)
				GetSeedPositionInBank(aChosenSeed.mSeedIndexInBank, aChosenSeed.mX, aChosenSeed.mY, aChosenSeed.mSeedType);
			else if (aChosenSeed.mSeedState == SEED_IN_CHOOSER)
				GetSeedPositionInChooser(aSeedType, aChosenSeed.mX, aChosenSeed.mY, aSeedType);
			else continue;
			aChosenSeed.mStartX = aChosenSeed.mX;
			aChosenSeed.mStartY = aChosenSeed.mY;
			aChosenSeed.mEndX = aChosenSeed.mX;
			aChosenSeed.mEndY = aChosenSeed.mY;
		}
	}

	EnableStartButton(mSeedsInBank == mBoard->mSeedBank->mNumPackets);
	UpdateImitaterButton();
}

int SeedChooserScreen::CheckPageNumber()
{
	return ((LawnApp*)gSexyAppBase)->mSeedChooserScreen->mPage;
}

bool SeedChooserScreen::CheckSeedchooserClosed()
{
	return ((LawnApp*)gSexyAppBase)->mSeedChooserScreen->mCloseToolTip;
}