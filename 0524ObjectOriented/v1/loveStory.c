#include <stdio.h>
/*
故事梗慨：
很久很久就以前，天上的织女思凡下界，看上了在河边放牛的牛郎。
柳树精看穿了织女的心思，于是向成全他们。
柳树精偷偷牵走了牛郎的牛，将其栓在河边吃草。
柳树精偷偷偷走了织女的纺车，将其放到了牛郎的牛车上
牛郎去找牛。。。
织女去找纺车。。。
牛郎和织女见面，一见钟情！
牛郎和织女结婚了！
*/
int main(){
    /* **********面向过程********** */
    tookCowboy_Cow("matchmaker","river");
    stoleWeaver_spinningWheel("matchmaker","cow");
    searchCow("cowboy");
    searchSpinningWheel("weaver");
    meet("cowboy","weaver");
    married("cowboy","weaver");

}