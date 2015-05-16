#include "App.h"

App::App(){
    int p=0, f=0, h=0;
    for(int i=0; i<XX; i+=LandscapeSize){
        for(int j=0; j<YY-LandscapeSize; j+=LandscapeSize){
            int r=rand()%3;
            if(r==0){
                Plain* P=new Plain(i,j,LandscapeSize,LandscapeSize,p);
                PLAINS.push_back(P);
                LANDSCAPES.push_back(P);
                TILES.push_back(P);
                p++;
            }
            if(r==1){
                Forest* F=new Forest(i,j,LandscapeSize,LandscapeSize,f);
                FORESTS.push_back(F);
                LANDSCAPES.push_back(F);
                TILES.push_back(F);
                f++;
            }
            if(r==2){
                Hill* H=new Hill(i,j,LandscapeSize,LandscapeSize,h);
                HILLS.push_back(H);
                LANDSCAPES.push_back(H);
                TILES.push_back(H);
                h++;
            }
        }
    }


}

void clean(){
    gout<<move_to(0,0)<<color(black)<<box(XX, YY);
}

void App::Run(){
    gout.open(XX, YY);
    event ev;
    gin.timer(40);
    unsigned posX=0, posY=0;

    while(gin >> ev && ev.keycode!=key_escape){
        clean();
        if(ev.type==ev_mouse){
            posX=ev.pos_x;
            posY=ev.pos_y;
        }
        if(ev.type==ev_timer){
            for(int i=0; i<LANDSCAPES.size(); i++){
                LANDSCAPES[i]->draw();
            }
            for(Tile* t : TILES){
                if(t->OnMouse(posX, posY)){
                    t->Log();
                }
            }
            gout<<refresh;
        }


    }
}
