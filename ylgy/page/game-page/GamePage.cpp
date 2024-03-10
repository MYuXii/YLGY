#include <graphics.h>
#include <stdio.h>

#include "GamePage.h"

#pragma warning(disable:4996)

//����ͼƬ��Դ
 IMAGE imgBg;
 IMAGE imgCards[MAX_CARD_INGAME]; 
 IMAGE imgCards_Slot[MAX_CARD_INSLOT];
//��Ƭ�ļ���
char Filename[256];

/*
    �����ˣ� MYXii
    ������飺��Ϸ����
    �����βΣ���Ƭ,����
    ��������ֵ���Ƿ��˳�����(0�˳�,1����)
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
    �����ˣ�MYXii
    ������飺δ������Ƭ��Ⱦ����
    �����βΣ�δ������Ƭ
    ��������ֵ����
*/
void toBeEliminatedCardRender(ToBeEliminatedCards *L) {
    cleardevice();
    //���ص�ͼ
    loadimage(&imgBg, "static/game-page/image/bg.png", 500, 900);
    putimage(0, 0, &imgBg);
    //���ؿ�Ƭ
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
    �����ˣ�MYXii
    ������飺δ������Ƭ��Ⱦ����
    �����βΣ����ۿ�Ƭ
    ��������ֵ��
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