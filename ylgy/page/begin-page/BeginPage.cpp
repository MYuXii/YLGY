#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>

#include "BeginPage.h"
#include"../game-page/GamePage.h"

extern ToBeEliminatedCards toBeEliminatedCards;
extern SlotCards slotCards;

void drawStart()
{
    IMAGE img1;
    loadimage(&img1, "static/begin-page/image/begin1Picture.png", WIDTH, HEIGHT);
    putimage(0, 0, &img1);
}
void drawMenu()
{
    IMAGE img2;
    loadimage(&img2, "static/begin-page/image/menu1Picture.png", WIDTH, HEIGHT);
    putimage(0, 0, &img2);
}
void drawExit()
{
    IMAGE img3;
    loadimage(&img3, "static/begin-page/image/exit1Picture.png", WIDTH, HEIGHT);
    putimage(0, 0, &img3);
}
void beginPage()
{
    HWND hnd1 = GetHWnd();
    SetWindowText(hnd1, _T("羊了个羊(B985版)"));
    mciSendString("open static/begin-page/voice/lobbyMusic.mp3 alias bgm1", 0, 0, 0);
    mciSendString(("play bgm1 repeat"), 0, 0, 0);
    gameState state = STATE_START;
    while (true)
    {
        switch (state)
        {
        case STATE_START:
            drawStart();
            while (true)
            {
                MOUSEMSG mouse2 = GetMouseMsg();
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 375 && mouse2.x>125 && mouse2.y < 491 && mouse2.y>409)
                {
                    mciSendString(_T("close bgm1"), 0, 0, 0);
                    cleardevice();
                    gamePage(&toBeEliminatedCards,&slotCards);
                    break;
                }
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 480 && mouse2.x>415 && mouse2.y < 83 && mouse2.y>17)
                {
                    cleardevice();
                    state = STATE_MENU;
                    break;
                }
            }
            break;
        case STATE_MENU:
            drawMenu();
            while (true)
            {
                MOUSEMSG mouse1 = GetMouseMsg();
                if (mouse1.uMsg == WM_LBUTTONDOWN && mouse1.x < 333 && mouse1.x>167 && mouse1.y < 327 && mouse1.y>286)
                {
                    mciSendString("open static/begin-page/voice/lobbyMusic.mp3 alias bgm1", 0, 0, 0);
                    mciSendString(("play bgm1 repeat"), 0, 0, 0);
                }
                if (mouse1.uMsg == WM_LBUTTONDOWN && mouse1.x < 333 && mouse1.x>167 && mouse1.y < 409 && mouse1.y>368)
                {
                    mciSendString(_T("close bgm1"), 0, 0, 0);
                }
                if (mouse1.uMsg == WM_LBUTTONDOWN && mouse1.x < 333 && mouse1.x>167 && mouse1.y < 491 && mouse1.y>450)
                {
                    cleardevice();
                    state = STATE_START;
                    break;
                }
                if (mouse1.uMsg == WM_LBUTTONDOWN && mouse1.x < 333 && mouse1.x>167 && mouse1.y < 573 && mouse1.y>532)
                {
                    cleardevice();
                    state = STATE_EXIT;
                    break;
                }
            }
            break;
        case STATE_EXIT:
            drawExit();
            while (true)
            {
                MOUSEMSG mouse3 = GetMouseMsg();
                if (mouse3.uMsg == WM_LBUTTONDOWN && mouse3.x < 250 && mouse3.x>100 && mouse3.y < 575 && mouse3.y>525)
                {
                    exit(0);
                }
                if (mouse3.uMsg == WM_LBUTTONDOWN && mouse3.x < 400 && mouse3.x>250 && mouse3.y < 575 && mouse3.y>525)
                {
                    cleardevice();
                    state = STATE_MENU;
                    break;
                }
            }
            break;
        }
    }
    char ch = getchar();
    closegraph();
}