#include "App.h"

App::App(){
    int p=0, f=0, h=0;
    for(int i=0; i<XX; i+=LandscapeSize){
        for(int j=0; j<YY-LandscapeSize; j+=LandscapeSize){
            int r=rand()%3;
            if(r==0){
                Plain* P=new Plain(i,j,LandscapeSize,LandscapeSize,p);
                PX.push_back(P);
                LX.push_back(P);
                TX.push_back(P);
                p++;
            }
            if(r==1){
                Forest* F=new Forest(i,j,LandscapeSize,LandscapeSize,f);
                FX.push_back(F);
                LX.push_back(F);
                TX.push_back(F);
                f++;
            }
            if(r==2){
                Hill* H=new Hill(i,j,LandscapeSize,LandscapeSize,h);
                HX.push_back(H);
                LX.push_back(H);
                TX.push_back(H);
                h++;
            }
        }
    }
    Warrior* W1=new Warrior(200+(LandscapeSize-UnitSize)/2, 200+(LandscapeSize-UnitSize)/2, UnitSize, UnitSize, 1, "w");
    TX.push_back(W1);
    CX.push_back(W1);
    UX.push_back(W1);
    WX.push_back(W1);

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
        if(ev.button==btn_left){
            for(Controlled* c: CX){
                if(c->OnMouse(posX, posY)) c->Activate();
                else c->DeActivate();
            }
        }
        if(ev.type==ev_timer){

            for(Controlled* c : CX){
                for(Landscape* l : LX){
                    if(c->get_pos()["x"]==l->get_pos()["x"]+(LandscapeSize-UnitSize)/2 && c->get_pos()["y"]==l->get_pos()["y"]+(LandscapeSize-UnitSize)/2){
                       l->Occupy();
                       c->mod_stats(l->get_mods()["am"], l->get_mods()["dm"]);
                    }
                    else{
                        l->UnOccupy();
                    }
                }
            }
            for(Tile* t : TX){
                t->draw();
                if(t->OnMouse(posX, posY)){
                    t->Log();
                }
            }
            gout<<refresh;
        }


    }
}
