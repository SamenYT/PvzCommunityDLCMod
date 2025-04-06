#include "../Plant.h"
#include "GameButton.h"
#include "../SeedPacket.h"
#include "../../LawnApp.h"
#include "ImitaterDialog.h"
#include "SeedChooserScreen.h"
#include "../ToolTipWidget.h"
#include "../../GameConstants.h"
#include "../../SexyAppFramework/WidgetManager.h"
#include "../../Resources.h"


//0x482B00
ImitaterDialog::ImitaterDialog() : 
	LawnDialog(gLawnApp, Dialogs::DIALOG_IMITATER, true, ("               "), _S(""), _S("[DIALOG_BUTTON_OK]"), Dialog::BUTTONS_YES_NO)
{
	CalcSize(IMITATER_DIALOG_WIDTH - mWidth, IMITATER_DIALOG_HEIGHT - mHeight);
	mToolTip = new ToolTipWidget();
	mClip = false;
	mToolTipSeed = SeedType::SEED_NONE;
	mLawnYesButton->mBtnNoDraw = true;
	mLawnYesButton->mMouseVisible = false;
	mLawnNoButton->mBtnNoDraw = true;
	mLawnNoButton->mMouseVisible = false;
	mPageIndex = 0;

	mRightButton = MakeNewButton(ImitaterDialog::ImitaterDialog_Arrow, this, _S(""), nullptr, Sexy::IMAGE_STONEBUTTON_RIGHT, IMAGE_STONEBUTTON_RIGHT_HOVER, IMAGE_STONEBUTTON_RIGHT_HOVER);
	mRightButton->Resize(400, 495, mRightButton->mWidth, mRightButton->mHeight);

	mLeftButton = MakeNewButton(ImitaterDialog::ImitaterDialog_Arrow, this, _S(""), nullptr, Sexy::IMAGE_STONEBUTTON_LEFT, IMAGE_STONEBUTTON_LEFT_HOVER, IMAGE_STONEBUTTON_LEFT_HOVER);
	mLeftButton->Resize(30, 495, mRightButton->mWidth, mRightButton->mHeight);
}

//0x482CE0
ImitaterDialog::~ImitaterDialog()
{
	delete mToolTip;
	delete mRightButton;
	delete mLeftButton;
}

//0x482D30
SeedType ImitaterDialog::SeedHitTest(int x, int y)
{
	for (SeedType aSeedType = (SeedType)0; aSeedType < SeedType::SEED_GATLINGPEA; aSeedType = (SeedType)(aSeedType + 1))
	{
		if (mApp->SeedTypeAvailable(aSeedType))
		{
			int aSeedX, aSeedY;
			GetSeedPosition(aSeedType, aSeedX, aSeedY);
			if (Rect(aSeedX, aSeedY, SEED_PACKET_WIDTH, SEED_PACKET_HEIGHT).Contains(x, y))
			{
				return aSeedType;
			}
		}
	}
	return SeedType::SEED_NONE;
}

//0x482DD0
void ImitaterDialog::UpdateCursor()
{
	int aX = mApp->mWidgetManager->mLastMouseX - mX;
	int aY = mApp->mWidgetManager->mLastMouseY - mY;
	SeedType aSeedType = SeedHitTest(aX, aY);
	if ((aSeedType != SeedType::SEED_NONE && !mApp->mSeedChooserScreen->SeedNotAllowedToPick(aSeedType)) || mRightButton->GetRect().Contains(aX, aY) || mLeftButton->GetRect().Contains(aX, aY))
	{
		mApp->SetCursor(CURSOR_HAND);
	}
	else
	{
		mApp->SetCursor(CURSOR_POINTER);
	}
}

//0x482E50
void ImitaterDialog::Update()
{
	LawnDialog::Update();
	ShowToolTip();
	UpdateCursor();
}

//0x482E70
void ImitaterDialog::GetSeedPosition(int theIndex, int& x, int& y)
{
	if (mPageIndex == 1)
	{
		theIndex -= 40;
	}

	if (theIndex >= 40) return;

	x = (theIndex % 8) * (SEED_PACKET_WIDTH + 1) + mWidth / 2 - 210;
	y = (theIndex / 8) * (SEED_PACKET_HEIGHT + 1) +90;
}

//0x482EC0
void ImitaterDialog::Draw(Graphics* g)
{
	LawnDialog::Draw(g);
	g->SetLinearBlend(true);
	int startSeed = 0;
	SeedType endSeed = SEED_PULTSHROOM;
	if (mPageIndex == 1)
	{
		startSeed = 40;
		endSeed = SEED_GATLINGPEA;
	}
	for (SeedType aSeedType = (SeedType)startSeed; aSeedType < endSeed; aSeedType = (SeedType)(aSeedType + 1))
	{
		if (mApp->SeedTypeAvailable(aSeedType))
		{
			int aSeedX, aSeedY;
			GetSeedPosition(aSeedType, aSeedX, aSeedY);
			bool aGrayed = mApp->mSeedChooserScreen->SeedNotAllowedToPick(aSeedType) || mApp->mSeedChooserScreen->SeedNotRecommendedToPick(aSeedType);
			DrawSeedPacket(g, aSeedX, aSeedY, SeedType::SEED_IMITATER, aSeedType, 0, aGrayed ? 115 : 255, true, false);
		}
	}
	mToolTip->Draw(g);
}

//0x483030
void ImitaterDialog::ShowToolTip()
{
	if (!mApp->mWidgetManager->mMouseIn || !mApp->mActive)
	{
		RemoveToolTip();
		return;
	}
	
	SeedType aSeedType = SeedHitTest(mApp->mWidgetManager->mLastMouseX - mX, mApp->mWidgetManager->mLastMouseY - mY);
	if (aSeedType == SeedType::SEED_NONE)
	{
		RemoveToolTip();
	}
	else if (aSeedType != mToolTipSeed)
	{
		RemoveToolTip();
		uint aRecFlags = mApp->mSeedChooserScreen->SeedNotRecommendedToPick(aSeedType);
		if (mApp->mSeedChooserScreen->SeedNotAllowedToPick(aSeedType))  // 如果不能携带
		{
			mToolTip->SetWarningText(_S("[NOT_ALLOWED_ON_THIS_LEVEL]"), false);
		}
		else if (aRecFlags)  // 如果不推荐携带
		{
			if (TestBit(aRecFlags, NotRecommend::NOT_RECOMMENDED_NOCTURNAL))
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
		mToolTip->SetTitle(Plant::GetNameString(SeedType::SEED_IMITATER, aSeedType));
		mToolTip->SetLabel(Plant::GetToolTip(aSeedType));

		int aSeedX, aSeedY;
		GetSeedPosition(aSeedType, aSeedX, aSeedY);
		mToolTip->mX = (SEED_PACKET_WIDTH - mToolTip->mWidth) / 2 + aSeedX;
		mToolTip->mY = SEED_PACKET_HEIGHT + aSeedY;
		mToolTip->mVisible = true;
		mToolTipSeed = aSeedType;
	}
}

void ImitaterDialog::RemoveToolTip()
{
	mToolTip->mVisible = false;
	mToolTipSeed = SeedType::SEED_NONE;
}

//0x483270
void ImitaterDialog::MouseDown(int x, int y, int theClickCount)
{
	SeedType aSeedType = SeedHitTest(x, y);
	if (aSeedType != SeedType::SEED_NONE)
	{
		SeedChooserScreen* aSeedChooser = mApp->mSeedChooserScreen;
		if (!aSeedChooser->SeedNotAllowedToPick(aSeedType))
		{
			ChosenSeed& aImitater = aSeedChooser->mChosenSeeds[SeedType::SEED_IMITATER];
			aImitater.mSeedState = ChosenSeedState::SEED_IN_CHOOSER;
			aImitater.mImitaterType = aSeedType;
			aImitater.mX = aSeedChooser->mImitaterButton->mX;
			aImitater.mY = aSeedChooser->mImitaterButton->mY;
			aSeedChooser->ClickedSeedInChooser(aImitater);
			aSeedChooser->UpdateImitaterButton();
			mApp->KillDialog(mId);
		}
	}
	else
	{
		Widget::MouseDown(x, y, theClickCount);
	}
}

void ImitaterDialog::AddedToManager(Sexy::WidgetManager* theWidgetManager)
{
	Dialog::AddedToManager(theWidgetManager);
	AddWidget(mRightButton);
	AddWidget(mLeftButton);
}

void ImitaterDialog::RemovedFromManager(Sexy::WidgetManager* theWidgetManager)
{
	Dialog::RemovedFromManager(theWidgetManager);
	RemoveWidget(mRightButton);
	RemoveWidget(mLeftButton);
}

void ImitaterDialog::ButtonDepress(int theId)
{
	if (mPageIndex == 0) mPageIndex = 1;
	else mPageIndex = 0;
}