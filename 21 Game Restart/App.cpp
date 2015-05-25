#include "App.h"

/// STUFF TO SOLVE:
/// THE INVINCIBLE UNIT PHENOMENA: EFFECT DISAPPEARS AT MOVEMENT/MOVING BACK/DOING ANYTHING AT ALL? ONLY OCCURS DURING LATE-GAME (90+ TURNS) ONLY. WHY?

App::App(){
    int PC;
    std::cout<<"How many players?"<<std::endl;
    std::cin>>PC;
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

    for(int i=0; i<PC; i++){
        Player* P=new Player(i+1);
        PlX.push_back(P);
        int X, Y;
        if(i==0){
            X=0+Usize_diff;
            Y=0+Usize_diff;
        }
        if(i==1){
            X=XX-100+Usize_diff;
            Y=YY-200+Usize_diff;
        }
        if(i==2){
            X=XX-100+Usize_diff;
            Y=0+Usize_diff;
        }
        if(i==3){
            X=0+Usize_diff;
            Y=YY-200+Usize_diff;
        }
        Castle* C=new Castle(X, Y, UnitSize, UnitSize, i+1, P, "c");
        TX.push_back(C);
        CX.push_back(C);
        BX.push_back(C);
        cX.push_back(C);
    }

    H=new Hourglass(XX-100, YY-100, LandscapeSize, LandscapeSize, 0);
}

void clean(){
    gout<<move_to(0,0)<<color(black)<<box(XX, YY);
}

void App::Run(App &A){
    gout.open(XX, YY);
    event ev;
    gin.timer(40);
    unsigned posX=0, posY=0;
    int Wcount=1, Acount=1;
    Player* PA;
    bool StartNewGame=false;

    while(gin >> ev && ev.keycode!=key_escape){
        clean();
        if(ev.keycode==key_enter) StartNewGame=true;
        if(ev.keycode==-key_enter) StartNewGame=false;
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
                            Unit* Ref=new Unit("w");
                            if(c->Owner()->Wealth()>=Ref->Cost()){
                                Warrior* W=new Warrior(c->get_pos()["x"], c->get_pos()["y"], UnitSize, UnitSize, Wcount, c->Owner(),"w");
                                Wcount++;
                                TX.push_back(W);
                                CX.push_back(W);
                                UX.push_back(W);
                            }
                        }
                        if(c->Spawn(ev)=="a"){
                            Unit* Ref=new Unit("a");
                            if(c->Owner()->Wealth()>=Ref->Cost()){
                                Archer* A=new Archer(c->get_pos()["x"], c->get_pos()["y"], UnitSize, UnitSize, Acount, c->Owner(), "a");
                                Acount++;
                                TX.push_back(A);
                                CX.push_back(A);
                                UX.push_back(A);
                            }
                        }
                    }
                }
            }
            /*for(Controlled* c : CX){
                if(c->OnMouse(posX, posY)) c->Activate();
                else c->DeActivate();
            }*/
            bool UonB=false;
            for(Controlled* c : CX){
                if(c->OnMouse(posX, posY) && c->Owner()->IsActive()){
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
            if(H->OnMouse(posX, posY)){                             /// TAKING TURNS
                H->Next_turn();
                H->Next_Player(PlX);
                for(Controlled* c : CX){
                    c->Elapse_Turn();
                }
            }
        }
        if(ev.button==btn_middle){
            for(Building* b : BX){
                if(b->OnMouse(posX, posY) && b->Owner()->IsActive()){
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
                    Unit* Garr=new Unit("w");                                        /// GIVING IT A BASE VALUE MAY HAVE SOLVED TEH INVINCIBLE UNIT PHENOMENA
                    for(Controlled* c2 : CX){                                        /// COMBAT
                        bool isonB=false;
                        if(c2->OnMouse(posX, posY)){
                            int c2x=c2->get_pos()["x"];
                            int c2y=c2->get_pos()["y"];
                            if(c->Owner()!=c2->Owner()){
                                if(abs(c2x-cx)<=LandscapeSize*c->get_stats()["r"] && abs(c2y-cy)<=LandscapeSize*c->get_stats()["r"] && c->CanAtk()){
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
                                    if(c2!=Garr){   ///deleted: !isonB &&  -  SOLVED last castle's invincibility problem  -  INVESTIGATE for cause & further bugs!  -  could be source of invincible unit phenomena
                                        c2->take_damage(c->get_stats()["atk"]);
                                    }
                                    if(c->get_stats()["r"]<=1 && c2!=Garr){                         /// RETALIATION
                                        c->take_damage(c2->get_stats()["atk"]-4);
                                    }
                                    c->Attack();
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
                            if(c->Owner()==c2->Owner() && c->get_stats()["movep"]>0 && (c2->get_stats()["movep"]>0 || c2->get_type()=="c")){                   /// POSITION SWAPPING
                                cx=c->get_pos()["x"];
                                cy=c->get_pos()["y"];
                                for(Landscape* lprev : LX){
                                    if(cx==lprev->get_pos()["x"]+Usize_diff && cy==lprev->get_pos()["y"]+Usize_diff){
                                        lprev->UnOccupy();
                                    }
                                }
                                c->Move(c2x, c2y);
                                bool isB=false;
                                for(Building* b : BX){
                                    if(c2==b) isB=true;
                                }
                                if(!isB) c2->Move(cx, cy);
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
            Player* erase_p=0;
            clean();
            for(Controlled* c : CX){                        /// STAT BONUSES
                for(Landscape* l : LX){
                    if(c->get_pos()["x"]==l->get_pos()["x"]+Usize_diff && c->get_pos()["y"]==l->get_pos()["y"]+Usize_diff){
                       l->Occupy();
                       c->mod_stats(l->get_mods()["am"], l->get_mods()["dm"], l->get_mods()["rm"]);
                       for(Unit* u : UX){
                            if(c->get_pos()["x"]==u->get_pos()["x"] && c->get_pos()["y"]==u->get_pos()["y"] && c!=u){                                                  /// GARRISON
                                c->mod_stats(l->get_mods()["am"]+u->get_stats()["atk"]-12, l->get_mods()["dm"]+u->get_stats()["def"]-6, l->get_mods()["rm"]);
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
                        if(u->get_pos()["x"]==b->get_pos()["x"] && u->get_pos()["y"]==b->get_pos()["y"] && b->Owner()==u->Owner())
                            u->take_damage(u->get_stats()["hp"]+u->get_stats()["def"]+1);
                    }
                    erase_b=b;
                    b->Owner()->C_death(erase_b);
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
                    u->Owner()->C_death(erase_u);
                }
            }
            UX.erase(std::remove(UX.begin(), UX.end(), erase_u), UX.end());
            CX.erase(std::remove(CX.begin(), CX.end(), erase_u), CX.end());
            TX.erase(std::remove(TX.begin(), TX.end(), erase_u), TX.end());
            delete erase_u;
            for(Player* p : PlX){
                if(p->Army().size()<=0){
                    erase_p=p;
                }
            }
            PlX.erase(std::remove(PlX.begin(), PlX.end(), erase_p), PlX.end());
            delete erase_p;
            for(Castle* c : cX){
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
            for(Player* p : PlX){
                if(p->IsActive()){
                    p->Log();
                    PA=p;
                }
            }
            if(PlX.size()==1){
                if(StartNewGame) {
                    std::cout<<"Winner of this round: Player "<<PlX[0]->Num()<<std::endl;
                    A=App();
                }
            }
            H->draw();
            H->Log();

            gout<<refresh;
        }
    }
}
