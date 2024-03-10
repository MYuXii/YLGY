#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#include "EndPage.h"
#include "../../logic/main-logic/GameLogic.h"

void drawExitGameWining()
{
    IMAGE img1;
    loadimage(&img1, "static/end-page/image/winExit.png", 500, 900);
    putimage(0, 0, &img1);
}
void drawExitGameFailed()
{
    IMAGE img2;
    loadimage(&img2, "static/end-page/image/failed.png", 500, 900);
    putimage(0, 0, &img2);
}

void drawWiningPicture()
{
    IMAGE img3;
    loadimage(&img3, "static/end-page/image/win.png", 500, 900);
    putimage(0, 0, &img3);
}
void drawFailedPicture()
{
    IMAGE img4;
    loadimage(&img4, "static/end-page/image/failed1.png", 500, 900);
    putimage(0, 0, &img4);
}
void createWiningPicture()
{
    initgraph(500, 900);
    gameState state = STATE_START;
    while (true)
    {
        switch (state)
        {
        case STATE_START:
            drawWiningPicture();
            while (true)
            {
                MOUSEMSG mouse2 = GetMouseMsg();
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 400 && mouse2.x>100 && mouse2.y < 840 && mouse2.y>740)
                {
                    cleardevice();
                    state = STATE_EXIT;
                    break;
                }
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 398 && mouse2.x>98 && mouse2.y < 600 && mouse2.y>500)
                {
                    cleardevice();
                    break;
                }
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 399 && mouse2.x>99 && mouse2.y < 720 && mouse2.y>620)
                {
                    cleardevice();
                    break;
                }
            }
            break;
        case STATE_EXIT:
            drawExitGameWining();
            while (true)
            {
                MOUSEMSG mouse3 = GetMouseMsg();
                if (mouse3.uMsg == WM_LBUTTONDOWN && mouse3.x < 247 && mouse3.x>99 && mouse3.y < 460 && mouse3.y>410)
                {
                    exit(0);
                }
                if (mouse3.uMsg == WM_LBUTTONDOWN && mouse3.x < 398 && mouse3.x>250 && mouse3.y < 460 && mouse3.y>410)
                {
                    cleardevice();
                    state = STATE_START;
                    break;
                }
            }
            break;
        }
    }
    char ch = getchar();
    closegraph();
}
void createFailedPicture()
{
    initgraph(500, 900);
    gameState state = STATE_START;
    while (true)
    {
        switch (state)
        {
        case STATE_START:
            drawFailedPicture();
            while (true)
            {
                MOUSEMSG mouse2 = GetMouseMsg();
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 400 && mouse2.x>100 && mouse2.y < 840 && mouse2.y>740)
                {
                    cleardevice();
                    break;
                }
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 398 && mouse2.x>98 && mouse2.y < 600 && mouse2.y>500)
                {
                    cleardevice();
                    break;
                }
                if (mouse2.uMsg == WM_LBUTTONDOWN && mouse2.x < 399 && mouse2.x>99 && mouse2.y < 720 && mouse2.y>620)
                {
                    cleardevice();
                    state = STATE_MENU;// ????
                    break;
                }
            }
            break;
        case STATE_EXIT:
            drawExitGameFailed();
            while (true)
            {
                MOUSEMSG mouse3 = GetMouseMsg();
                if (mouse3.uMsg == WM_LBUTTONDOWN && mouse3.x < 247 && mouse3.x>99 && mouse3.y < 460 && mouse3.y>410)
                {
                    exit(0);
                }
                if (mouse3.uMsg == WM_LBUTTONDOWN && mouse3.x < 398 && mouse3.x>250 && mouse3.y < 460 && mouse3.y>410)
                {
                    cleardevice();
                    state = STATE_START;
                    break;
                }
            }
            break;
        }
    }
    char ch = getchar();
    closegraph();
}