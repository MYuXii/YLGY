#pragma once
#ifndef __GAME_LOGIC__
#define __GAME_LOGIC__


#define         MAX_CARD_INGAME       90         //单局游戏卡片最大数量
#define         MAX_CARD_INSLOT       7           //单局游戏卡槽最大容纳卡片数量
#define         MAX_KIND_SIZE         12          //单局游戏卡片种类数量           
//easyX 长 宽
#define         WIDTH                 500         //easyX宽度
#define         HEIGHT                900         //easyX高度

#define         CARD_WIDTH            61          //单局游戏卡片宽度
#define         CARD_HEIGHT           68          //单据游戏卡片高度
#define         CARDSLOT_X            22          //游戏卡槽x坐标   
#define         CARDSLOT_Y            683         //游戏卡槽y坐标


/*
    负责人：MYXii
    实现要求：点击事件
*/
enum gameState
{
    STATE_START,
    STATE_MENU,
    STATE_EXIT
};

/*
    负责人：MYXii
    实现要求：根据需求文档来完善类型
*/
enum CardKind {
    Carrot = 1,//胡萝卜
    Grass,//草
    Maize,//玉米
    Bonfire,//篝火
    Woolen,//毛线
    Glove,//手套
    Basin,//盆
    Cabbage,//白菜
    Bell,//铃铛
    Hayfork,//干草叉
    Milk,//牛奶
    Stump,//树桩
    //Wool,//羊毛
    //Brush,//刷子
    //Scissor,//剪刀
    RemoveKind=0,//此类型用以消除
};

//坐标类型
typedef struct PosInfo {
    //x坐标
    int x;
    //y坐标
    int y;
}Pos;

//卡片信息类型
typedef struct {
    //坐标信息
    Pos pos;
    //所属种类
    CardKind kind;
    //是否被点击（1被点击;0没有被点击）
    char isClicked;
    //是否在最上面（true被覆盖；false没有被覆盖）
    bool top;

}CardInfo;

//待消除卡片类型
typedef struct {
    //待消除卡片的数组
    CardInfo Cards[MAX_CARD_INGAME];
    //当前待消除卡片的数量
    int size;
}ToBeEliminatedCards;

//卡槽内卡片类型
typedef struct {
    //卡槽内卡片的数组
    CardInfo Cards[MAX_CARD_INSLOT];
    //当前卡槽卡片的数量
    int size;
}SlotCards;

//对数组封装的一些API：
/*
    负责人： 
    函数简介：增加卡片信息、删除卡片信息、修改卡片信息、查询卡片信息
    TIP: 形参为指针接收数组
*/
void addCards(ToBeEliminatedCards* L,Pos pos,CardKind kind);
void removeCards(ToBeEliminatedCards* L, int idenx);
void updateCards(ToBeEliminatedCards* L, Pos newpos, int idenx, bool newtop, char newisclicked);
int queryCards(ToBeEliminatedCards* L, Pos pos);

/*
    负责人：MYxii
    函数简介：卡片被点击
    函数形参：卡牌，卡槽
    函数返回值：true(按到卡片)false(没按到)
*/
bool clickedCard(ToBeEliminatedCards* L, SlotCards* L1);

/*
    负责人：MYxii
    函数简介：三消
    函数形参：卡槽卡牌
    函数返回值：无
*/
void removeThreeCards(SlotCards* L);

/*
    负责人： 
    函数简介：判断卡槽是否爆了，爆了就寄
    函数形参：
    函数返回值：1(失败),0(胜利),-1(继续游戏)
*/
int isFailed(ToBeEliminatedCards* L, SlotCards* L1);

/*
    负责人： 
    函数简介：判断是否胜利
    函数形参：
    函数返回值：
*/
void isWin(ToBeEliminatedCards* L, SlotCards* L1);


void gameInit(ToBeEliminatedCards* L,SlotCards *L1);

/*
    负责人：MYxii
    函数简介：更新地图
    函数形参：卡牌 , 更新索引
    函数返回值：无
*/
void updateMap(ToBeEliminatedCards* L, int i, int idenx);
/*
    负责人：MYxii
    函数简介：更新卡槽
    函数形参：卡槽卡牌 , 更新索引
    函数返回值：无
*/
void updateSlot(SlotCards* L1);
#endif
