#include <stdio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>

#include "GameLogic.h"
#include "..\..\page\end-page\EndPage.h"

extern IMAGE imgBg;
//�ö�ά����map��¼��Ƭλ��
int map[HEIGHT][WIDTH];

ToBeEliminatedCards  toBeEliminatedCards;
SlotCards slotCards;

//�������װ��һЩAPI��
/*
    �����ˣ�MYXii
    ������飺���ӿ�Ƭ��Ϣ��ɾ����Ƭ��Ϣ���޸Ŀ�Ƭ��Ϣ����ѯ��Ƭ��Ϣ
    TIP: �β�Ϊָ���������
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

int queryCards(ToBeEliminatedCards *L,Pos pos) {//���������
    for (int i = 0; i < L->size; i++) {
        if (L->Cards[i].pos.x == pos.x && L->Cards[i].pos.y==pos.y) {
            return i;
        }
    }
    return -1;
}

/*
    �����ˣ�MYxii
    ������飺��Ƭ�����
    �����βΣ����ƣ�����
    ��������ֵ��true(������Ƭ)false(û����)
*/
bool clickedCard(ToBeEliminatedCards *L,SlotCards *L1) {
    ExMessage msg;
    if (peekmessage(&msg, EM_MOUSE) && msg.message == WM_LBUTTONDOWN) {//������������
        for (int i = 0; i < L->size; i++){//��������
            if ( L->Cards[i].top || L->Cards[i].isClicked) {//��������ǻ򱻵���򲻲���
                continue;
            }else if (msg.x >= L->Cards[i].pos.x && msg.x < L->Cards[i].pos.x + CARD_WIDTH &&
                      msg.y >= L->Cards[i].pos.y && msg.y < L->Cards[i].pos.y + CARD_HEIGHT){
                    updateMap(L, i,0);
                    Pos newpos;
                    newpos.x = CARDSLOT_X+(L1->size* (CARD_WIDTH+4));
                    newpos.y = CARDSLOT_Y;
                    //�����ƶ���������
                    updateCards(L, newpos, i, false,1);
                    CardInfo moveCards = L->Cards[i];
                    L1->Cards[L1->size] = moveCards;
                    L1->size++;
                    removeCards(L, i);
                    //��������
                    removeThreeCards(L1);
                    return true;
                  }
        }
    }
    return false;
}

/*
    �����ˣ�MYxii
    ������飺����
    �����βΣ����ۿ���
    ��������ֵ����
*/
void removeThreeCards(SlotCards *L) {
    int count_s[MAX_KIND_SIZE + 20] = { 0 }; // ���������
    for (int i = 0; i < L->size; i++) {
            count_s[L->Cards[i].kind]++;

    }
    // ����Ƿ���������ͬ�Ŀ�Ƭ
    for (int i = 1; i <= MAX_KIND_SIZE; i++) {
        if (count_s[i] >= 3) {
            // ����
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
            break; // ִ��һ�������󷵻�
        }
    }
    return;
}
/*
    �����ˣ�MYxii
    ������飺���¿���
    �����βΣ����ۿ��� 
    ��������ֵ����
*/
void updateSlot(SlotCards* L) {
    // ��������
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
    �����ˣ�
    ������飺�жϿ����Ƿ��ˣ����˾ͼ�
    �����βΣ�
    ��������ֵ��
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
    �����ˣ�
    ������飺�ж��Ƿ�ʤ��
    �����βΣ�
    ��������ֵ��
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
    //�������¼
    char count[500] = { 0 };
    L->size = 0;
    L1->size = 0;
    srand(time(NULL));
    //��һ������������������꣨���β�����
    int center_x = 220,center_y = 350;
    int width = 400,height = 480;
    int rand_x = -1, rand_y = -1;
 
    //���ɰ�����������Ԫ�ص�����
    int allKinds[MAX_KIND_SIZE] = { 0 };
    for (int i = 0; i < MAX_KIND_SIZE; i++){
        allKinds[i] = i + 1;
    }
    //��������Ԫ��˳��
    for (int i = MAX_KIND_SIZE-1; i > 0; i--){
        int j = rand() % (i + 1);
        int temp = allKinds[i];
        allKinds[i] = allKinds[j];
        allKinds[j] = temp;
    }
    int rand_index = 0;
    int kind_index = 0;
    //����ÿ������
    for (int i = 0; i < MAX_CARD_INGAME; i++){
        //�����������
        do{
            rand_x = center_x - width / 2 + rand() % width;
            rand_y = center_y - height/2 + rand() % height;
        } while (count[rand_x] != 0 || rand_x <= 0);    
        count[rand_x]++;
        Pos newpos;
        newpos.x = rand_x;
        newpos.y = rand_y;
        //�����������
        CardKind newkind = (enum CardKind)allKinds[rand_index];
        if ((kind_index+1)%3 == 0)
        {
            rand_index = (rand_index +1 ) % MAX_KIND_SIZE;
            kind_index %= 3;
        }
        kind_index++;
        //�����¿�Ƭ
        addCards(L, newpos, newkind);
        updateMap(L, i, 1);
    }
}
/*
    �����ˣ�MYxii
    ������飺���µ�ͼ
    �����βΣ����� , ��������,����ģʽ(1��ӿ�Ƭ,0�Ƴ���Ƭ)
    ��������ֵ����
*/
void updateMap(ToBeEliminatedCards* L, int i,int idenx) {
    if (idenx)
    {
        Pos center;
        center.x = L->Cards[i].pos.x + CARD_WIDTH / 2;
        center.y = L->Cards[i].pos.y + CARD_HEIGHT / 2;
        ////����Ƿ񸲸��˿��ƣ�����и��ǣ���map��¼
        for (int j = 0; j < i; j++) {
            Pos cmp_center;
            cmp_center.x = L->Cards[j].pos.x + CARD_WIDTH / 2;
            cmp_center.y = L->Cards[j].pos.y + CARD_HEIGHT / 2;
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH -2  > cmp_center.x &&
                center.y < cmp_center.y && center.y + CARD_HEIGHT -3  > cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
                continue;
            }//���ϲ�����
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH -2  > cmp_center.x &&
                center.y > cmp_center.y && center.y - CARD_HEIGHT +3  < cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
                continue;
            }//���²�����
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH +2 < cmp_center.x &&
                center.y <  cmp_center.y && center.y + CARD_HEIGHT -3 >  cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
                continue;
            }//���ϲ�����
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH +2 < cmp_center.x &&
                center.y > cmp_center.y && center.y - CARD_HEIGHT +3 < cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]++;
            }
        }
    }else{
        //����Ƿ񸲸��˿��ƣ�����и��ǣ���map��¼;
        Pos center;
        center.x = L->Cards[i].pos.x + CARD_WIDTH / 2;
        center.y = L->Cards[i].pos.y + CARD_HEIGHT / 2;
        for (int j = 0; j < i; j++) {
            Pos cmp_center;
            cmp_center.x = L->Cards[j].pos.x + CARD_WIDTH / 2;
            cmp_center.y = L->Cards[j].pos.y + CARD_HEIGHT / 2;
            //���²�����
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH  +1 > cmp_center.x &&
                center.y < cmp_center.y && center.y + CARD_HEIGHT +2 > cmp_center.y) {
                map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }//���ϲ�����
            if (center.x < cmp_center.x  && center.x + CARD_WIDTH +1 > cmp_center.x &&
                     center.y > cmp_center.y && center.y - CARD_HEIGHT -2 < cmp_center.y) {
                     map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }//���²�����
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH -1 < cmp_center.x &&
                     center.y <  cmp_center.y && center.y + CARD_HEIGHT +2 >  cmp_center.y) {
                     map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }//���ϲ�����
            if (center.x > cmp_center.x  && center.x - CARD_WIDTH -1< cmp_center.x &&
                     center.y > cmp_center.y && center.y - CARD_HEIGHT -2 < cmp_center.y) {
                     map[L->Cards[j].pos.y][L->Cards[j].pos.x]--; continue;
            }
        }
    }
     //�������ǿ��Ƶ�top�޸� true��������,����false(û�б�����,��)
    for (int i = 0; i < L->size; i++){
        if (map[L->Cards[i].pos.y][L->Cards[i].pos.x] > 1){
            L->Cards[i].top = true;
        }else{
            L->Cards[i].top = false;
        }
    }
}