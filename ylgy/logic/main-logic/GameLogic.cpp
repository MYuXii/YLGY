#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>

#include "GameLogic.h"
#include "..\..\page\end-page\EndPage.h"

extern IMAGE imgBg;
//用二维数组map记录卡片位置
int map[HEIGHT][WIDTH];

ToBeEliminatedCards  toBeEliminatedCards;
SlotCards slotCards;

//对数组封装的一些API：
/*
    负责人：MYXii
    函数简介：增加卡片信息、删除卡片信息、修改卡片信息、查询卡片信息
    TIP: 形参为指针接收数组
*/
void addCards(ToBeEliminatedCards *L,Pos pos,CardKind kind) {
    CardInfo newcard;
    newcard.isClicked = 0;
    newcard.kind = kind;
    newcard.pos.x = pos.x;
    newcard.pos.y = pos.y;
    newcard.top = false;
    map[pos.y][pos.x]++;
    L->Cards[L->size] = newcard;
    L->size++;
}

void removeCards(ToBeEliminatedCards *L,int idenx) {
    for (int i = idenx; i < L->size - 1; i++) {
        L->Cards[i] = L->Cards[i + 1];
    }
    L->size--;
}

void updateCards(ToBeEliminatedCards *L,Pos newpos,int idenx,bool newtop,char newisclicked) {
    L->Cards[idenx].pos = newpos;
    L->Cards[idenx].isClicked = newisclicked;
    L->Cards[idenx].top = newtop;
}

int queryCards(ToBeEliminatedCards *L,Pos pos) {//按坐标查找
    for (int i = 0; i < L->size; i++) {
        if (L->Cards[i].pos.x == pos.x && L->Cards[i].pos.y==pos.y) {
            return i;
        }
    }
    return -1;
}

/*
    负责人：MYxii
    函数简介：卡片被点击
    函数形参：卡牌，卡槽
    函数返回值：true(按到卡片)false(没按到)
*/
bool clickedCard(ToBeEliminatedCards *L,SlotCards *L1) {
    ExMessage msg;
    if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN) {//鼠标左键被按下
        for (int i = 0; i < L->size; i++){//遍历搜索
            if ( L->Cards[i].top || L->Cards[i].isClicked) {//如果被覆盖或被点击则不操作
                continue;
            }else if (msg.x >= L->Cards[i].pos.x && msg.x < L->Cards[i].pos.x + CARD_WIDTH &&
                      msg.y >= L->Cards[i].pos.y && msg.y < L->Cards[i].pos.y + CARD_HEIGHT){
                    updateMap(L, i,0);
                    Pos newpos;
                    newpos.x = CARDSLOT_X+(L1->size* (CARD_WIDTH+4));
                    newpos.y = CARDSLOT_Y;
                    //卡牌移动到卡槽内
                    updateCards(L, newpos, i, false,1);
                    CardInfo moveCards = L->Cards[i];
                    L1->Cards[L1->size] = moveCards;
                    L1->size++;
                    removeCards(L, i);
                    //进行三消
                    removeThreeCards(L1);
                    return true;
                  }
        }
    }
    return false;
}

/*
    负责人：MYxii
    函数简介：三消
    函数形参：卡槽卡牌
    函数返回值：无
*/
void removeThreeCards(SlotCards *L) {
    int count_s[MAX_KIND_SIZE + 20] = { 0 }; // 用数组计数
    for (int i = 0; i < L->size; i++) {
            count_s[L->Cards[i].kind]++;

    }
    // 检查是否有三个相同的卡片
    for (int i = 1; i <= MAX_KIND_SIZE; i++) {
        if (count_s[i] >= 3) {
            // 三消
            int removed = 0;
            for (int j = 0; j < L->size && removed < 3; j++)
            {
                if (L->Cards[j].kind == i)
                {
                    L->Cards[j].kind = RemoveKind;
                    removed++;
                }
            }
            updateSlot(L);
            break; // 执行一次消除后返回
        }
    }
    return;
}
/*
    负责人：MYxii
    函数简介：更新卡槽
    函数形参：卡槽卡牌 
    函数返回值：无
*/
void updateSlot(SlotCards* L) {
    // 重新排列
           int index = 0;
           for (int j = 0; j < L->size; j++) {
               if (L->Cards[j].kind != 0) {
                   L->Cards[index++] = L->Cards[j];
               }
           }
           L->size -= 3;
           for (int i = 0; i < L->size; i++){
               Pos newpos;
               newpos.x = CARDSLOT_X + (i * (CARD_WIDTH + 4));
               newpos.y = CARDSLOT_Y;
               L->Cards[i].pos.x = newpos.x;
               L->Cards[i].pos.y = newpos.y;
           }
}
/*
    负责人：
    函数简介：判断卡槽是否爆了，爆了就寄
    函数形参：
    函数返回值：
*/
int isFailed(ToBeEliminatedCards* L,SlotCards* L1) {
    if (L1->size >= 7)
    {
        return 1;
    }
    if (L->size == 0)
    {
        return 0;
    }
    return -1;
}

/*
    负责人：
    函数简介：判断是否胜利
    函数形参：
    函数返回值：
*/
void isWin (ToBeEliminatedCards* L,SlotCards* L1){
    int res = isFailed(L, L1);
    if (res == 1)
    {
        createFailedPicture();
    }
    else if (res == 0)
    {
        createWiningPicture();
    }
    return;
} 

void gameInit(ToBeEliminatedCards *L,SlotCards *L1) {
    //用数组记录
    char count[500] = { 0 };
    L->size = 0;
    L1->size = 0;
    srand(time(NULL));
    //在一个矩形内随机生成坐标（矩形参数）
    int center_x = 220,center_y = 350;
    int width = 400,height = 480;
    int rand_x = -1, rand_y = -1;
 
    //生成包含所有种类元素的数组
    int allKinds[MAX_KIND_SIZE] = { 0 };
    for (int i = 0; i < MAX_KIND_SIZE; i++){
        allKinds[i] = i + 1;
    }
    //打乱数组元素顺序
    for (int i = MAX_KIND_SIZE-1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = allKinds[i];
        allKinds[i] = allKinds[j];
        allKinds[j] = temp;
    }
    int rand_index = 0;
    int kind_index = 0;
    //生成每个卡牌
    for (int i = 0; i < MAX_CARD_INGAME; i++){
        //生成随机坐标
        do{
            rand_x = center_x - width / 2 + rand() % width;
            rand_y = center_y - height/2 + rand() % height;
        } while (count[rand_x] != 0 || rand_x <= 0);    
        count[rand_x]++;
        Pos newpos;
        newpos.x = rand_x;
        newpos.y = rand_y;
        //生成随机种类
        CardKind newkind = (enum CardKind)allKinds[rand_index];
        if ((kind_index+1)%3 == 0)
        {
            rand_index = (rand_index +1 ) % MAX_KIND_SIZE;
            kind_index %= 3;
        }
        kind_index++;
        //生成新卡片
        addCards(L, newpos, newkind);
        updateMap(L, i, 1);
    }
}
/*
    负责人：MYxii
    函数简介：更新地图
    函数形参：卡牌 , 更新索引,更新模式(1添加卡片,0移除卡片)
    函数返回值：无
*/
void updateMap(ToBeEliminatedCards* L, int i,int idenx) {
    if (idenx)
    {
        Pos center;
        center.x = L->Cards[i].pos.x + CARD_WIDTH / 2;
        center.y = L->Cards[i].pos.y + CARD_HEIGHT / 2;
        ////检测是否覆盖了卡牌，如果有覆盖，用map记录
        for (int j = 0; j < i; j++) {
            Pos cmp_center;
            cmp_center.x = L->Cards[j].pos.x + CARD_WIDTH / 2;
            cmp_center.y = L->Cards[j].pos.y + CARD_HEIGHT / 2;
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH -2  > cmp_center.x &&
                center.y < cmp_center.y && center.y + CARD_HEIGHT -3  > cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
                continue;
            }//右上部覆盖
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH -2  > cmp_center.x &&
                center.y > cmp_center.y && center.y - CARD_HEIGHT +3  < cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
                continue;
            }//左下部覆盖
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH +2 < cmp_center.x &&
                center.y <  cmp_center.y && center.y + CARD_HEIGHT -3 >  cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
                continue;
            }//左上部覆盖
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH +2 < cmp_center.x &&
                center.y > cmp_center.y && center.y - CARD_HEIGHT +3 < cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
            }
        }
    }else{
        //检测是否覆盖了卡牌，如果有覆盖，用map记录;
        Pos center;
        center.x = L->Cards[i].pos.x + CARD_WIDTH / 2;
        center.y = L->Cards[i].pos.y + CARD_HEIGHT / 2;
        for (int j = 0; j < i; j++) {
            Pos cmp_center;
            cmp_center.x = L->Cards[j].pos.x + CARD_WIDTH / 2;
            cmp_center.y = L->Cards[j].pos.y + CARD_HEIGHT / 2;
            //右下部覆盖
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH  +1 > cmp_center.x &&
                center.y < cmp_center.y && center.y + CARD_HEIGHT +2 > cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }//右上部覆盖
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH +1 > cmp_center.x &&
                     center.y > cmp_center.y && center.y - CARD_HEIGHT -2 < cmp_center.y) {
                     map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }//左下部覆盖
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH -1 < cmp_center.x &&
                     center.y <  cmp_center.y && center.y + CARD_HEIGHT +2 >  cmp_center.y) {
                     map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }//左上部覆盖
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH -1< cmp_center.x &&
                     center.y > cmp_center.y && center.y - CARD_HEIGHT -2 < cmp_center.y) {
                     map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }
        }
    }
     //将被覆盖卡牌的top修改 true（被覆盖,暗）false(没有被覆盖,明)
    for (int i = 0; i < L->size; i++){
        if (map[L->Cards[i].pos.y][L->Cards[i].pos.x] > 1){
            L->Cards[i].top = true;
        }else{
            L->Cards[i].top = false;
        }
    }
}