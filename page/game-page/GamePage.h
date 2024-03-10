#pragma once

#ifndef __GAME_PAGE__
#define __GAME_PAGE__

#include "..\..\logic\main-logic\GameLogic.h"


/*
    负责人： MYXii
    函数简介：游戏界面
    函数形参：卡片,卡槽
    函数返回值：是否退出界面(0退出,1不退)
*/
void gamePage(ToBeEliminatedCards* L, SlotCards* L1);

/*
    负责人： MYXii
    函数简介：未消除卡片渲染函数
    函数形参：
    函数返回值：
*/
void toBeEliminatedCardRender(ToBeEliminatedCards *L);

/*
    负责人： 
    函数简介：未消除卡片渲染函数
    函数形参：
    函数返回值：
*/
void slotCardRender(SlotCards *L1);

/*
    负责人： 暂无
    函数简介：道具渲染（待基本功能实现再搞）
    函数形参：
    函数返回值：
*/
void propRender(/* 形参需要分析业务完成 */);
#endif
