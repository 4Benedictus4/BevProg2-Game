#include "Archer.h"

Archer::Archer(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type) : Unit(x, y, w, h, id, player, type), looks(W,std::vector<std::vector<int> >(H,std::vector<int>(3)))  {
    std::ifstream f;
    f.open("Archer.txt");
    int r, g, b;
    for (int i=0; i<W; i++){
            for (int j=0; j<H; j++){
                f >> r >> g >> b;
                looks[i][j][0]=r;
                looks[i][j][1]=g;
                looks[i][j][2]=b;
            }
    }
    f.close();
    this->Owner()->mod_Gold(-this->Cost());
}

void Archer::draw(){
    if(IsActive()) gout<<move_to(X,Y)<<color(P->Color()[0], P->Color()[1], P->Color()[2])<<box(W, H);
    gout<<move_to(X,Y);
    for (int i=0; i<W; i++){
            for (int j=0; j<H; j++){
                if(looks[i][j][0]==255 && looks[i][j][1]==255 && looks[i][j][2]==255) continue;
                if(looks[i][j][0]==0 && looks[i][j][1]==0 && looks[i][j][2]==255) gout<<color(P->Color()[0], P->Color()[1], P->Color()[2])<< move_to(X+i,Y+j)<<dot;
                else gout<<color(looks[i][j][0],looks[i][j][1],looks[i][j][2])<< move_to(X+i,Y+j)<<dot;
            }
    }
}

void Archer::Log(){
    Unit::Log();
    std::string d, a, h, dm, am, r, ap, mp;
    std::stringstream ss;
    int Ap, Mp;
    if(atkpoints<0) Ap=0;
    else Ap=atkpoints;
    if(movepoints<0) Mp=0;
    else Mp=movepoints;
    ss<<def<<" "<<atk<<" "<<hp<<" "<<def_mod<<" "<<atk_mod<<" "<<range<<" "<<Ap<<" "<<Mp;
    ss>>d>>a>>h>>dm>>am>>r>>ap>>mp;
    gout<<color(white)<<move_to(260,YY-85)<<text(mp)<<move_to(340,YY-85)<<text(ap)<<move_to(315,YY-65)<<text(a)<<text(" + ")<<text(am)<<move_to(315,YY-45)<<text(d)<<text(" + ")<<text(dm)<<move_to(315, YY-25)<<text(h)<<move_to(315, YY-5)<<text("Melee");
}
