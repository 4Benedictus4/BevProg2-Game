#include "App.h"

/// STUFF TO SOLVE:
/// GARRISONED UNITS TAKING DAMAGE
/// SPAWNING UNITS WHILE THERE'S A GARRISONED ONE
/// ATTACK/GARRISON - SOLVED BY PLAYERS / TURNS


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
    Castle* C1=new Castle(0+Usize_diff, 0+Usize_diff, UnitSize, UnitSize, 1, "c");
    TX.push_back(C1);
    CX.push_back(C1);
    BX.push_back(C1);
    cX.push_back(C1);
    Warrior* W1=new Warrior(200+Usize_diff, 200+Usize_diff, UnitSize, UnitSize, 1, "w");
    TX.push_back(W1);
    CX.push_back(W1);
    UX.push_back(W1);
    Warrior* W2=new Warrior(300+Usize_diff, 300+Usize_diff, UnitSize, UnitSize, 2, "w");
    TX.push_back(W2);
    CX.push_back(W2);
    UX.push_back(W2);
    Warrior* W3=new Warrior(400+Usize_diff, 400+Usize_diff, UnitSize, UnitSize, 3, "w");
    TX.push_back(W3);
    CX.push_back(W3);
    UX.push_back(W3);
    Archer* A1=new Archer(100+Usize_diff, 100+Usize_diff, UnitSize, UnitSize, 1, "a");
    TX.push_back(A1);
    CX.push_back(A1);
    UX.push_back(A1);
}

void clean(){
    gout<<move_to(0,0)<<color(black)<<box(XX, YY);
}

void App::Run(){
    gout.open(XX, YY);
    event ev;
    gin.timer(40);
    unsigned posX=0, posY=0;
    int Wcount=1, Acount=1;

    while(gin >> ev && ev.keycode!=key_escape){
        clean();
        if(ev.type==ev_mouse){
            posX=ev.pos_x;
            posY=ev.pos_y;
        }
        if(ev.button==btn_left){                                /// UNIT SELECTION
            for(Castle* c : cX){
                if(c->IsActive()){
                    if(c->Spawn(ev)=="w"){
                        Warrior* W=new Warrior(c->get_pos()["x"], c->get_pos()["y"], UnitSize, UnitSize, Wcount, "w");
                        Wcount++;
                        TX.push_back(W);
                        CX.push_back(W);
                        UX.push_back(W);
                    }
                    if(c->Spawn(ev)=="a"){
                        Archer* A=new Archer(c->get_pos()["x"], c->get_pos()["y"], UnitSize, UnitSize, Acount, "a");
                        Acount++;
                        TX.push_back(A);
                        CX.push_back(A);
                        UX.push_back(A);
                    }
                }
            }
            /*for(Controlled* c: CX){
                if(c->OnMouse(posX, posY)){
                        c->Activate();
                }
                else c->DeActivate();
            }*/
            bool UonB=false;
            for(Controlled* c : CX){
                if(c->OnMouse(posX, posY)){
                    c->Activate();
                    for(Building* b : BX){
                        if(b->OnMouse(posX, posY)){
                            for(Unit* u : UX){
                                if(u->OnMouse(posX, posY)){
                                    u->Activate();
                                    b->DeActivate();
                                    UonB=true;
                                    break;
                                }
                                else UonB=false;
                            }
                            if(!UonB) b->Activate();
                        }
                    }
                }
                else c->DeActivate();
            }
        }
        if(ev.button==btn_middle){
            for(Building* b : BX){
                if(b->OnMouse(posX, posY)){
                    b->Activate();
                }
                else b->DeActivate();
                for(Controlled* c : CX){
                    if(c!=b){
                        c->DeActivate();
                    }
                }
            }
        }
        if(ev.button==btn_right){
            for(Controlled* c : CX){
                if(c->IsActive()){
                    int cx=c->get_pos()["x"];
                    int cy=c->get_pos()["y"];

                    for(Controlled* c2 : CX){                             /// COMBAT
                        if(c2->OnMouse(posX, posY) && c!=c2){
                            int c2x=c2->get_pos()["x"];
                            int c2y=c2->get_pos()["y"];
                            if(abs(c2x-cx)<=LandscapeSize*c->get_stats()["r"] && abs(c2y-cy)<=LandscapeSize*c->get_stats()["r"]){
                                c->Attack();
                                c2->take_damage(c->get_stats()["atk"]);
                                if(c->get_stats()["r"]<=1){
                                    c->take_damage((c2->get_stats()["atk"])-3);
                                }
                            }
                            if(c2->get_stats()["hp"]<=0){
                                for(Landscape* lprev : LX){
                                    if(c->get_pos()["x"]==lprev->get_pos()["x"]+Usize_diff && c->get_pos()["y"]==lprev->get_pos()["y"]+Usize_diff){
                                        lprev->UnOccupy();
                                    }
                                }
                                if(c->get_stats()["r"]==1){
                                    c->Move(c2x, c2y);
                                }
                            }
                        }
                    }
                }
            }
            for(Unit* u : UX){
                if(u->IsActive()){
                    int ux=u->get_pos()["x"];
                    int uy=u->get_pos()["y"];
                    for(Landscape* l : LX){                         /// MOVEMENT
                        if(l->OnMouse(posX, posY)){
                            int lx=l->get_pos()["x"];
                            int ly=l->get_pos()["y"];
                            if(ux-Usize_diff+LandscapeSize>=lx && ux-Usize_diff-LandscapeSize<=lx && uy-Usize_diff+LandscapeSize>=ly && uy-Usize_diff-LandscapeSize<=ly){
                                if(ux-Usize_diff==lx && uy-Usize_diff==ly) continue;
                                if(!l->IsOccupied()){
                                    for(Landscape* lprev : LX){
                                        if(u->get_pos()["x"]==lprev->get_pos()["x"]+Usize_diff && u->get_pos()["y"]==lprev->get_pos()["y"]+Usize_diff){
                                           lprev->UnOccupy();
                                        }
                                    }
                                    u->Move(lx+Usize_diff, ly+Usize_diff);
                                }
                            }
                        }
                    }
                }
            }
        }
        if(ev.type==ev_timer){
            clean();
            for(Controlled* c : CX){
                for(Landscape* l : LX){
                    if(c->get_pos()["x"]==l->get_pos()["x"]+Usize_diff && c->get_pos()["y"]==l->get_pos()["y"]+Usize_diff){
                       l->Occupy();
                       c->mod_stats(l->get_mods()["am"], l->get_mods()["dm"], l->get_mods()["rm"]);
                    }
                }
            }
            for(Unit* u : UX){                              /// DEATH
                if(u->get_stats()["hp"]<=0){
                    for(Landscape* l : LX){
                        if(l->get_pos()["x"]==u->get_pos()["x"]-Usize_diff && l->get_pos()["y"]==u->get_pos()["y"]-Usize_diff){
                            l->UnOccupy();
                        }
                    }
                    UX.erase(std::remove(UX.begin(), UX.end(), u), UX.end());
                    CX.erase(std::remove(CX.begin(), CX.end(), u), CX.end());
                    TX.erase(std::remove(TX.begin(), TX.end(), u), TX.end());
                    delete u;
                }
            }
            for(Building* b : BX){                              /// DEMOLITION
                if(b->get_stats()["hp"]<=0){
                    for(Landscape* l : LX){
                        if(l->get_pos()["x"]==b->get_pos()["x"]-Usize_diff && l->get_pos()["y"]==b->get_pos()["y"]-Usize_diff){
                            l->UnOccupy();
                        }
                    }
                    BX.erase(std::remove(BX.begin(), BX.end(), b), BX.end());
                    CX.erase(std::remove(CX.begin(), CX.end(), b), CX.end());
                    TX.erase(std::remove(TX.begin(), TX.end(), b), TX.end());
                    delete b;
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
