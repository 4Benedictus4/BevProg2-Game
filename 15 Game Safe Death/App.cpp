#include "App.h"

/// STUFF TO SOLVE:
/// ATTACK OR GARRISON ON RIGHT-CLICK --- WILL BE SOLVED BY PLAYERS / TURNS
/// CRASH WHEN NO MORE UNITS LEFT ALIVE --- CAN BE SOLVED BY INTRODUCING if(size>0) PARAMETERS
/// CHRASH WHEN LAST CREATED UNIT DIES --- WHEN USING LISTS --- RANGE BASED FOR CYCLE SHOULD NOT MODIFY THE CONTAINER IT'S ITERATING OVER ---
///     SOLUTION: MARK THE REMOVABLE ELEMENT WITH ANOTHER VALUE, THEN REMOVE IT !!AFTER!! THE CYCLE.

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
    Castle* C2=new Castle(XX-100+Usize_diff, 0+Usize_diff, UnitSize, UnitSize, 2, "c");
    TX.push_back(C2);
    CX.push_back(C2);
    BX.push_back(C2);
    cX.push_back(C2);
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
    srand(time(NULL));
    gin.timer(40);
    unsigned posX=0, posY=0;
    int Wcount=1, Acount=1;

    while(gin >> ev && ev.keycode!=key_escape){
        clean();
        if(ev.type==ev_mouse){
            posX=ev.pos_x;
            posY=ev.pos_y;
        }
        if(ev.button==btn_left){                                /// SELECTION / FUNCTION
            for(Castle* c : cX){
                if(c->IsActive()){
                    c->Spawn_able();
                    for(Unit* u : UX){
                        if(c->get_pos()["x"]==u->get_pos()["x"] && c->get_pos()["y"]==u->get_pos()["y"]) c->Spawn_unable();
                    }
                    if(c->CanSpawn()){
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
            }
            /*for(Controlled* c: CX){
                if(c->OnMouse(posX, posY)) c->Activate();
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
                    for(Controlled* c : CX){
                        if(c!=b){
                            c->DeActivate();
                        }
                    }
                }
                else b->DeActivate();
            }
        }
        if(ev.button==btn_right){
            for(Controlled* c : CX){
                if(c->IsActive()){
                    int cx=c->get_pos()["x"];
                    int cy=c->get_pos()["y"];
                    for(Controlled* c2 : CX){                                        /// COMBAT
                        bool isonB=false;
                        Unit* Garr;
                        if(c2->OnMouse(posX, posY) && c!=c2){
                            int c2x=c2->get_pos()["x"];
                            int c2y=c2->get_pos()["y"];
                            if(abs(c2x-cx)<=LandscapeSize*c->get_stats()["r"] && abs(c2y-cy)<=LandscapeSize*c->get_stats()["r"]){
                                c->Attack();
                                for(Building* b : BX){
                                    if(c2->get_pos()["x"]==b->get_pos()["x"] && c2->get_pos()["y"]==b->get_pos()["y"]){
                                        isonB=true;
                                    }
                                    else isonB=false;
                                    if(isonB && c2==b){
                                        for (Unit* u : UX){
                                            if(u->get_pos()["x"]==b->get_pos()["x"] && u->get_pos()["y"]==b->get_pos()["y"]){
                                                u->take_damage(u->get_stats()["def"]+1);
                                                Garr=u;
                                            }
                                        }
                                    }
                                }
                                if(!isonB && c2!=Garr){
                                    c2->take_damage(c->get_stats()["atk"]);
                                }
                                if(c->get_stats()["r"]<=1 && c2!=Garr){                         /// RETALIATION
                                        c->take_damage(c2->get_stats()["atk"]-4);
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
            Building* erase_b=0;
            Unit* erase_u=0;
            clean();
            for(Controlled* c : CX){                        /// STAT BONUSES
                for(Landscape* l : LX){
                    if(c->get_pos()["x"]==l->get_pos()["x"]+Usize_diff && c->get_pos()["y"]==l->get_pos()["y"]+Usize_diff){
                       l->Occupy();
                       c->mod_stats(l->get_mods()["am"], l->get_mods()["dm"], l->get_mods()["rm"]);
                       for(Unit* u : UX){
                            if(c->get_pos()["x"]==u->get_pos()["x"] && c->get_pos()["y"]==u->get_pos()["y"] && c!=u){           ///CITY GETS THE ATK/DEF MOD OF THE GARRISONED UNIT AS WELL?
                                c->mod_stats(l->get_mods()["am"]+u->get_stats()["atk"]-14, l->get_mods()["dm"]+u->get_stats()["def"]-8, l->get_mods()["rm"]);
                            }
                       }
                    }
                }
            }
            for(Building* b : BX){                          /// DEMOLITION
                if(b->get_stats()["hp"]<=0){
                    for(Landscape* l : LX){
                        if(l->get_pos()["x"]==b->get_pos()["x"]-Usize_diff && l->get_pos()["y"]==b->get_pos()["y"]-Usize_diff){
                            l->UnOccupy();
                        }
                    }
                    for(Unit* u : UX){
                        if(u->get_pos()["x"]==b->get_pos()["x"] && u->get_pos()["y"]==b->get_pos()["y"])
                            u->take_damage(u->get_stats()["hp"]+u->get_stats()["def"]+1);
                    }
                    erase_b=b;
                }
            }
            BX.erase(std::remove(BX.begin(), BX.end(), erase_b), BX.end());
            CX.erase(std::remove(CX.begin(), CX.end(), erase_b), CX.end());
            TX.erase(std::remove(TX.begin(), TX.end(), erase_b), TX.end());
            delete erase_b;
            for(Unit* u : UX){                              /// DEATH
                if(u->get_stats()["hp"]<=0){
                    for(Landscape* l : LX){
                        if(l->get_pos()["x"]==u->get_pos()["x"]-Usize_diff && l->get_pos()["y"]==u->get_pos()["y"]-Usize_diff){
                            l->UnOccupy();
                        }
                    }
                    erase_u=u;
                }
            }
            UX.erase(std::remove(UX.begin(), UX.end(), erase_u), UX.end());
            CX.erase(std::remove(CX.begin(), CX.end(), erase_u), CX.end());
            TX.erase(std::remove(TX.begin(), TX.end(), erase_u), TX.end());
            delete erase_u;
            for(Castle * c : cX){
                c->Spawn_able();
                for(Unit * u : UX){
                    if(c->get_pos()["x"]==u->get_pos()["x"] && c->get_pos()["y"]==u->get_pos()["y"]){
                        c->Spawn_unable();
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
