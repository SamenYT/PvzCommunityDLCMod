#include "PlayerController.h"
#include "Board.h"
#include "SeedPacket.h"
#include "../LawnApp.h" // This line is the only issue? How about the SexyMatrix?
#include "../Resources.h"
#include "System/ReanimationLawn.h"
#include "../Sexy.TodLib/Reanimator.h"
#include "../SexyAppFramework/MemoryImage.h"

// don leak this
PlayerController::PlayerController() {
}

void PlayerController::Initialize() {
	mPlant = new Plant();
	mPlant->mIsOnBoard = true;
	mPlant->mSeedType = SEED_SUNFLOWER;
	mPlant->mIsPreview = true;
	mPlant->PlantInitialize(0,0,SEED_SUNFLOWER, SEED_NONE);
	//no errors
	// 
	//Bro what happened to our edits LMAO

	mSelectorTime = Rand(100);
	mArrowTime = Rand(100);
	mSeedBankIndex = -1;
	mControlType = CONTROL_KEYBOARD;
	mAbilityType = ABILITY_SHOVEL;
}

void PlayerController::Draw(Graphics* g) {


	//Do your thing here xd

	// I HATE MY TOOTH ACHE

	// If there are no more errors. Try debugging it
	// alright
	/// Yo it also compiles for me


	int	gridX = mBoard->PixelToGridXKeepOnBoard(mX, mY);
	int gridY = mBoard->PixelToGridYKeepOnBoard(mX, mY);

	float arrowFloat = mBoard->StageHasRoof() ? 12 : 0;

	if (mControllerType == CONTROLLER_PLANT || mControllerType == CONTROLLER_ZOMBIE || mControllerType == CONTROLLER_SHOVEL)
	{
		SexyMatrix3 matrix = SexyMatrix3();
		matrix.ZeroMatrix();
		matrix.m00 = 0.8173f;
		matrix.m11 = mBoard->StageHas6Rows() || mBoard->StageHasRoof() ? 0.59f : 0.69f;

		if (mBoard->StageHasRoof() && mX < 440.0f)
			matrix.m10 = -0.25f;

		float selectorFloat = mBoard->StageHasRoof() ? 12 : 0;
		float selectorCycle = mSelectorTime % 100;
		if (selectorCycle < 25) {
			selectorFloat -= 1.5f * (1 - selectorCycle / 25.0f);
		}
		else if (selectorCycle < 50) {
			selectorFloat += 1.5f * ((selectorCycle - 25) / 25.0f);
		}
		else if (selectorCycle < 75) {
			selectorFloat += 1.5f * (1 - (selectorCycle - 50) / 25.0f);
		}
		else {
			selectorFloat -= 1.5f * ((selectorCycle - 75) / 25.0f);
		}

		if (mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop)
		{
			Image* aImage = nullptr;
			if (mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel())
			{
				aImage = IMAGE_P1_1;
			}
			else aImage = IMAGE_P2_1;
			g->DrawImageMatrix(aImage, matrix, mBoard->GridToPixelX(gridX, gridY) + 32.5f, mBoard->GridToPixelY(gridX, gridY) + 42.5f + selectorFloat);
			if (mBoard->mCobActivated) g->DrawImageCel(IMAGE_COBCANNON_TARGET, mBoard->GridToPixelX(gridX, gridY), mBoard->GridToPixelY(gridX, gridY) + 10.0f + selectorFloat, 0);
		}
			
		float scale = 1;
		float arrowCycle = mArrowTime % 100;
		if (arrowCycle < 25) {
			scale += 0.1f * (arrowCycle / 25.0f - 1);
			arrowFloat -= 1.5f * (1 - arrowCycle / 25.0f);
		}
		else if (arrowCycle < 50) {
			scale += 0.1f * ((arrowCycle - 25.0f) / 25.0f);
			arrowFloat += 1.5f * ((arrowCycle - 25) / 25.0f);
		}
		else if (arrowCycle < 75) {
			scale += 0.1f * (1 - (arrowCycle - 50.0f) / 25.0f);
			arrowFloat += 1.5f * (1 - (arrowCycle - 50) / 25.0f);
		}
		else {
			scale -= 0.1f * ((arrowCycle - 75.0f) / 25.0f);
			arrowFloat -= 1.5f * ((arrowCycle - 75) / 25.0f);
		}

		matrix.m00 = scale;
		matrix.m11 = scale;

		if (mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop)
			g->DrawImageMatrix(IMAGE_BEJEWEL_SELECTORSHADOW, matrix, mX + 7.5f, mY + (mBoard->StageHasRoof() || mBoard->StageHas6Rows() ? 42.5f : 50) - 45.0f);

		if (mControllerType == CONTROLLER_PLANT && mSeedBankIndex != -1) {
			SeedType seedType = mBoard->mSeedBank->mSeedPackets[mSeedBankIndex].mPacketType;
			SeedType imitaterType = mBoard->mSeedBank->mSeedPackets[mSeedBankIndex].mImitaterType;

			if (seedType == SEED_IMITATER) {
				SeedType prevSeedType = seedType;
				seedType = imitaterType;
				imitaterType = prevSeedType;
			}
			if (!mBoard->mCobActivated)
			{
				int mPlayerX = mBoard->GridToPixelX(gridX, gridY);
				int mPlayerY = mBoard->GridToPixelY(gridX, gridY);
				g->SetColorizeImages(true);
				g->SetColor(Color(255, 255, 255, 100));
				Graphics seedG(*g);
				if ((!mApp->mIsKeyboardPlayer1 && (mBoard->mSeedBank->mSeedPackets[mBoard->mPlayer2->mSeedBankIndex].mPacketType != SEED_GRAVE || mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES)) && (mApp->IsVersusLevel() || mApp->IsIZombieLevel() || mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES))
				{
					if (mApp->mGameMode == GAMEMODE_CHALLENGE_ZOMBIESVSZOMBIES)
					{
						seedG.mScaleX *= -1;
						mPlayerX += 130.0f;
						mPlayerY -= 78.0f;
						if (mBoard->mSeedBank->mSeedPackets[mBoard->mPlayer2->mSeedBankIndex].mPacketType == SEED_GRAVE)
						{
							mPlayerY += 78.0f;
							mPlayerX -= 60.0f;
						}
					}
					else
					{
						mPlayerY -= 78.0f;
						mPlayerX -= 49.0f;
					}
					if (seedType == SEED_VERSUS_BUNGEE || seedType == SEED_ZOMBIE_BUNGEE)
					{
						seedG.mTransY -= 600;
					}
				}
				if (!mBoard->CanPlantAt(gridX, gridY, mBoard->mSeedBank->mSeedPackets[mBoard->mPlayer2->mSeedBankIndex].mPacketType) && (mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop))
				{
					Plant::DrawSeedType(&seedG, mBoard->mSeedBank->mSeedPackets[mBoard->mPlayer2->mSeedBankIndex].mPacketType, SEED_NONE, DrawVariation::VARIATION_NORMAL, mPlayerX, mPlayerY);
				}
				g->SetColorizeImages(false);
			}
		}
	}

	SexyMatrix3 matrix = SexyMatrix3();
	matrix.ZeroMatrix();
	matrix.m00 = 1.25f;
	matrix.m11 = 1.25f;

	if (mApp->IsVersusLevel() || !mApp->mPlayerInfo->mIsNotCoop)
	{
		Image* aImage = nullptr;
		Image* bImage = nullptr;
		if (mApp->mIsKeyboardPlayer1 && mApp->IsVersusLevel())
		{
			aImage = IMAGE_P1_2;
			bImage = IMAGE_P1_3;
		}
		else
		{
			aImage = IMAGE_P2_2;
			bImage = IMAGE_P2_3;
		}

		g->DrawImageF(aImage, mX - 15, mY - 22.5f - 45.0f);
		g->DrawImageMatrix(bImage, matrix, mX, mY + arrowFloat + 7.5f - (mBoard->StageHasRoof() ? 15 : 0) - 45.0f);
	}
	
}

void PlayerController::UpdateAnimations() {
	mSelectorTime++;
	mSelectorTime = fmod(mSelectorTime, 100);
	mArrowTime++;
	mArrowTime = fmod(mArrowTime, 100);

	if (mArrowTime % 2 == 1) {
		mArrowTime++;
		mArrowTime = fmod(mArrowTime, 100);
	}
}