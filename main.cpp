#include <graphics.h>
#include "page/begin-page/BeginPage.h"

#pragma comment(lib,"winmm.lib")

int main(){
    initgraph(WIDTH, HEIGHT);
    //开始界面
    beginPage();
    return 0;
}
