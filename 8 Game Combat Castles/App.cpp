#include "App.h"

App::App(){
    int p=0, f=0, h=0;
    for(int i=0; i<XX; i+=LandscapeSize){
        for(int j=0; j<YY-LandscapeSize; j+=LandscapeSize){
            int r=rand()%3;
            if(r==0){
                Plain* P=new Plain(i,j,LandscapeSize,LandscapeSize,p,"p");
                PX.push_back(P);
                LX.push_back(P);
                TX.push_back(P);
                p++;
            }
            if(r==1){
                Forest* F=new Forest(i,j,LandscapeSize,LandscapeSize,f,"f");
                FX.push_back(F);
                LX.push_back(F);
                TX.push_back(F);
                f++;
            }
            if(r==2){
                Hill* H=new Hill(i,j,LandscapeSize,LandscapeSize,h,"h");
                HX.push_back(H);
                LX.push_back(H);
                TX.push_back(H);
                h++;
            }
        }
    }
    Warrior* W1=new Warrior(200+size_diff, 200+size_diff, UnitSize, UnitSize, 1, "w");
    TX.push_back(W1);
    CX.push_back(W1);
    UX.push_back(W1);
    Warrior* W2=new Warrior(300+size_diff, 300+size_diff, UnitSize, UnitSize, 2, "w");
    TX.push_back(W2);
    CX.push_back(W2);
    UX.push_back(W2);
    Warrior* W3=new Warrior(400+size_diff, 400+size_diff, UnitSize, UnitSize, 3, "w");
    TX.push_back(W3);
    CX.push_back(W3);
    UX.push_back(W3);
    Archer* A1=new Archer(100+size_diff, 100+size_diff, UnitSize, UnitSize, 1, "a");
    TX.push_back(A1);
    CX.push_back(A1);
    UX.push_back(A1);
    Castle* C1=new Castle(0+size_diff, 0+size_diff, UnitSize, UnitSize, 1, "c");
    TX.push_back(C1);
    CX.push_back(C1);
    BX.push_back(C1);
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
        if(ev.button==btn_left){                                /// UNIT SELECTION
            for(Controlled* c: CX){
                if(c->OnMouse(posX, posY)) c->Activate();
                else c->DeActivate();
            }
        }
        if(ev.button==btn_right){
            for(Unit* u : UX){
                if(u->IsActive()){
                    int ux=u->get_pos()["x"];
                    int uy=u->get_pos()["y"];

                    for(Unit* u2 : UX){                             /// COMBAT
                        if(u2->OnMouse(posX, posY) && u!=u2){
                            int u2x=u2->get_pos()["x"];
                            int u2y=u2->get_pos()["y"];
                            if(abs(u2x-ux)<=LandscapeSize*u->get_stats()["r"] && abs(u2y-uy)<=LandscapeSize*u->get_stats()["r"]){
                                u->Attack();
                                u2->take_damage(u->get_stats()["atk"]);
                                if(u->get_stats()["r"]<=1){
                                    u->take_damage((u2->get_stats()["atk"])-3);
                                }
                            }
                            if(u2->get_stats()["hp"]<=0){
                                for(Landscape* lprev : LX){
                                    if(u->get_pos()["x"]==lprev->get_pos()["x"]+size_diff && u->get_pos()["y"]==lprev->get_pos()["y"]+size_diff){
                                        lprev->UnOccupy();
                                    }
                                }
                                if(u->get_stats()["r"]==1){
                                    u->Move(u2x, u2y);
                                }
                            }
                        }
                    }
                    for(Landscape* l : LX){                         /// MOVEMENT
                        if(l->OnMouse(posX, posY)){
                            int lx=l->get_pos()["x"];
                            int ly=l->get_pos()["y"];
                            if(ux-size_diff+LandscapeSize>=lx && ux-size_diff-LandscapeSize<=lx && uy-size_diff+LandscapeSize>=ly && uy-size_diff-LandscapeSize<=ly){
                                if(ux-size_diff==lx && uy-size_diff==ly) continue;
                                if(!l->IsOccupied()){
                                    for(Landscape* lprev : LX){
                                        if(u->get_pos()["x"]==lprev->get_pos()["x"]+size_diff && u->get_pos()["y"]==lprev->get_pos()["y"]+size_diff){
                                           lprev->UnOccupy();
                                        }
                                    }
                                    u->Move(lx+size_diff, ly+size_diff);
                                }
                            }
                        }
                    }
                }
            }
        }
        if(ev.type==ev_timer){

            for(Controlled* c : CX){
                for(Landscape* l : LX){
                    if(c->get_pos()["x"]==l->get_pos()["x"]+size_diff && c->get_pos()["y"]==l->get_pos()["y"]+size_diff){
                       l->Occupy();
                       c->mod_stats(l->get_mods()["am"], l->get_mods()["dm"], l->get_mods()["rm"]);
                    }
                }
            }
            for(Unit* u : UX){                              /// DEATH
                if(u->get_stats()["hp"]<=0){
                    for(Landscape* l : LX){
                        if(l->get_pos()["x"]==u->get_pos()["x"]-size_diff && l->get_pos()["y"]==u->get_pos()["y"]-size_diff){
                            l->UnOccupy();
                        }
                    }
                    UX.erase(std::remove(UX.begin(), UX.end(), u), UX.end());
                    CX.erase(std::remove(CX.begin(), CX.end(), u), CX.end());
                    TX.erase(std::remove(TX.begin(), TX.end(), u), TX.end());
                    delete u;
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
