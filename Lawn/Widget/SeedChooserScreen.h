#ifndef __SEEDCHOOSERSCREEN_H__
#define __SEEDCHOOSERSCREEN_H__

#include "../../ConstEnums.h"
#include "../../SexyAppFramework/Widget.h"
using namespace Sexy;

class Board;
class LawnApp;
class GameButton;
class ToolTipWidget;
namespace Sexy
{
    class MTRand;
}

class ChosenSeed
{
public:
    int                     mX;                                //+0x0
    int                     mY;                                //+0x4
    int                     mTimeStartMotion;                  //+0x8
    int                     mTimeEndMotion;                    //+0xC
    int                     mStartX;                           //+0x10
    int                     mStartY;                           //+0x14
    int                     mEndX;                             //+0x18
    int                     mEndY;                             //+0x1C
    SeedType                mSeedType;                         //+0x20
    ChosenSeedState         mSeedState;                        //+0x24
    int                     mSeedIndexInBank;                  //+0x28
    int                     mP2SeedIndexInBank;                  //+0x28
    int                     mRefreshing;                       //+0x2C
    int                     mRefreshCounter;                   //+0x30
    SeedType                mImitaterType;                     //+0x34
    int                     mCrazyDavePicked;                  //+0x38            
};

class SeedChooserScreen : public Widget
{
private:
    enum
    {
        SeedChooserScreen_Start = 100,
        SeedChooserScreen_Random = 101,
        SeedChooserScreen_ViewLawn = 102,
        SeedChooserScreen_Almanac = 103,
        SeedChooserScreen_Menu = 104,
        SeedChooserScreen_Store = 105,
        SeedChooserScreen_Imitater = 106,
        SeedChooserScreen_Left = 107,
        SeedChooserScreen_Right = 108,
        SeedChooserScreen_Test = 109,
        SeedChooserScreen_Skip = 110,
        SeedChooserScreen_Versus = 111,
        SeedChooserScreen_Keyboard = 112,
        SeedChooserScreen_Discord = 113,
        SeedChooserScreen_Map = 114
    };

public:
    GameButton* mStartButton;                       //+0x88
    GameButton* mRandomButton;                      //+0x8C
    GameButton* mViewLawnButton;                    //+0x90
    GameButton* mStoreButton;                       //+0x94
    GameButton* mVersusButton;
    GameButton* mKeyboardButton;
    GameButton* mSkipButton;
    GameButton* mAlmanacButton;                     //+0x98
    GameButton* mMenuButton;                        //+0x9C
    GameButton* mImitaterButton;                    //+0xA0
    GameButton* mDiscordButton;
    GameButton* mMapButton;
    std::map<int, ChosenSeed>              mChosenSeeds;       //+0xA4
    LawnApp* mApp;                               //+0xD10
    Board* mBoard;                             //+0xD14
    int                     mNumSeedsToChoose;                  //+0xD18
    int                     mSeedChooserAge;                    //+0xD1C
    int                     mSeedsInFlight;                     //+0xD20
    int                     mSeedsInBank;                       //+0xD24
    int                     mP2SeedsInBank;                       //+0xD24
    bool                    mVersusNoteIsOn;                       
    ToolTipWidget*          mToolTip;                           //+0xD28
    ToolTipWidget*          mToolTipP2;                           
    int                     mToolTipSeed;                       //+0xD2C
    int                     mLastMouseX;                        //+0xD30
    int                     mLastMouseY;                        //+0xD34
    SeedChooserState        mChooseState;                       //+0xD38
    int                     mViewLawnTime;                      //+0xD3C
    int                     mZombieID;
    int                     mPlantID;
    int                     mClickCooldown;
    bool                    mPlantsPick;
    bool                    mCanSwitchSides;
    bool                    mKeyboardIsChoosing;
    bool                    mCloseToolTip;

    GameButton* mLeftButton;
    GameButton* mRightButton;
    int  mPage = 0;
    int  mPageP2 = 0;
    int mMaxPage = 0;
    int mMinPage = 0;
public:
    SeedChooserScreen();
    ~SeedChooserScreen();

    static /*inline*/ int   PickFromWeightedArrayUsingSpecialRandSeed(TodWeightedArray* theArray, int theCount, MTRand& theLevelRNG);
    void                    CrazyDavePickSeeds();
    int                     Has7Rows();
    void                    GetSeedPositionInChooser(int theIndex, int& x, int& y, SeedType theSeedType);
    /*inline*/ void         GetSeedPositionInBank(int theIndex, int& x, int& y, SeedType theSeedType);
    /*inline*/ unsigned int SeedNotRecommendedToPick(SeedType theSeedType);
    /*inline*/ int          SeedNotAllowedToPick(SeedType theSeedType);
    /*inline*/ int          SeedNotAllowedToPickVersusPlants(SeedType theSeedType);
    /*inline*/ int          SeedNotAllowedToPickVersusZombies(SeedType theSeedType);
    /*inline*/ int          SeedNotAllowedDuringTrial(SeedType theSeedType);
    virtual void            Draw(Graphics* g);
    void                    UpdateViewLawn();
    void                    LandFlyingSeed(ChosenSeed& theChosenSeed);
    void                    UpdateCursor();
    virtual void            Update();
    /*inline*/ int          DisplayRepickWarningDialog(const SexyChar* theMessage);
    int                     FlyersAreComming();
    int                     FlyProtectionCurrentlyPlanted();
    int                     CheckSeedUpgrade(SeedType theSeedTypeTo, SeedType theSeedTypeFrom);
    void                    OnStartButton();
    void                    PickRandomSeeds();
    virtual void            ButtonDepress(int theId);
    SeedType                SeedHitTest(int x, int y);
    SeedType                FindSeedInBank(int theIndexInBank, bool isZombie);
    /*inline*/ void         EnableStartButton(int theEnabled);
    void                    ClickedSeedInBank(ChosenSeed& theChosenSeed);
    void                    ClickedSeedInChooser(ChosenSeed& theChosenSeed);
    void                    ShowToolTip();
    void                    ShowToolTipP2();
    /*inline*/ void         RemoveToolTip();
    /*inline*/ void         RemoveToolTipP2();
    /*inline*/ void         CancelLawnView();
    virtual void            MouseUp(int x, int y, int theClickCount);
    void                    UpdateImitaterButton();
    virtual void            MouseDown(int x, int y, int theClickCount);
    /*inline*/ int          PickedPlantType(SeedType theSeedType);
    void                    CloseSeedChooser();
    virtual void            KeyDown(KeyCode theKey);
    virtual void            KeyChar(SexyChar theChar);
    void                    UpdateAfterPurchase();
    static /*inline*/ int   CheckPageNumber();
    static /*inline*/ bool  CheckSeedchooserClosed();
};

#endif
