#include <graphics.h>
#include <stdio.h>

#include "GamePage.h"

#pragma warning(disable:4996)

//保存图片资源
 IMAGE imgBg;
 IMAGE imgCards[MAX_CARD_INGAME]; 
 IMAGE imgCards_Slot[MAX_CARD_INSLOT];
//卡片文件名
char Filename[256];

/*
    负责人： MYXii
    函数简介：游戏界面
    函数形参：卡片,卡槽
    函数返回值：是否退出界面(0退出,1不退)
*/
void gamePage(ToBeEliminatedCards* L,SlotCards *L1) {
    gameInit(L, L1);
    toBeEliminatedCardRender(L);
    while(1)
    {
        if(clickedCard(L, L1))
        {
            BeginBatchDraw();
            toBeEliminatedCardRender(L);
            slotCardRender(L1);
            EndBatchDraw();
            isWin(L,L1);
        }
    }
}
/*
    负责人：MYXii
    函数简介：未消除卡片渲染函数
    函数形参：未消除卡片
    函数返回值：无
*/
void toBeEliminatedCardRender(ToBeEliminatedCards *L) {
    cleardevice();
    //加载地图
    loadimage(&imgBg, "static/game-page/image/bg.png", 500, 900);
    putimage(0, 0, &imgBg);
    //加载卡片
    for (int i = 0; i < L->size; i++) {
        if (L->Cards[i].top){
            sprintf(Filename, "static/game-page/image/%d_2.png", L->Cards[i].kind);
            loadimage(&imgCards[i], Filename);
        }else{
            sprintf(Filename, "static/game-page/image/%d_1.png", L->Cards[i].kind);
            loadimage(&imgCards[i], Filename);
        }
    }
    for (int i = 0; i < L->size; i++)
    {
        putimage(L->Cards[i].pos.x, L->Cards[i].pos.y, &imgCards[i]);
    }

}
/*
    负责人：MYXii
    函数简介：未消除卡片渲染函数
    函数形参：卡槽卡片
    函数返回值：
*/
void slotCardRender(SlotCards* L) {
    BeginBatchDraw();
    for (int i = 0; i < L->size; i++){
        sprintf_s(Filename, sizeof(Filename), "static/game-page/image/%d_1.png", L->Cards[i].kind);
        loadimage(&imgCards_Slot[i], Filename);
        putimage(L->Cards[i].pos.x, L->Cards[i].pos.y, &imgCards_Slot[i]);
    }
    EndBatchDraw();
}