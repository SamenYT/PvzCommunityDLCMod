#ifndef __IMITATERDIALOG_H__
#define __IMITATERDIALOG_H__

#include "LawnDialog.h"

class ToolTipWidget;
class ImitaterDialog : public LawnDialog
{
protected:
    enum
    {
        ImitaterDialog_Arrow,
    };
public:
    ToolTipWidget*          mToolTip;
    SeedType                mToolTipSeed;
    NewLawnButton*          mRightButton;
    NewLawnButton*          mLeftButton;
    int                     mPageIndex;

public:
    ImitaterDialog();
    virtual ~ImitaterDialog();

    SeedType                SeedHitTest(int x, int y);
    void                    UpdateCursor();
    virtual void            Update();
    /*inline*/ void         GetSeedPosition(int theIndex, int& x, int& y);
    virtual void            Draw(Graphics* g);
    void                    ShowToolTip();
    /*inline*/ void         RemoveToolTip();
    virtual void            MouseDown(int x, int y, int theClickCount);
    virtual void            MouseUp(int x, int y, int theClickCount) { ; }
    virtual void  			AddedToManager(Sexy::WidgetManager* theWidgetManager);
    virtual void  			RemovedFromManager(Sexy::WidgetManager* theWidgetManager);
    virtual void			ButtonDepress(int theId);
};

#endif