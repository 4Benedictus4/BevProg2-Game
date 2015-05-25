#include "Hourglass.h"

Hourglass::Hourglass(const int x, const int y, const int w, const int h, const int id, std::string type) : Tile(x, y, w, h, id, type), looks(W,std::vector<std::vector<int> >(H,std::vector<int>(3)))  {
    std::ifstream f;
    f.open("Hourglass.txt");
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
}

void Hourglass::Next_Player(std::vector<Player*> &PlX){
    for(int i=0; i<PlX.size(); i++){
        if(PlX[i]->IsActive()){
            PlX[i]->DeActivate();
            PlX[i]->Elapse_Turn();
            if(i!=PlX.size()-1){
                PlX[i+1]->Activate();
                AcP=PlX[i+1]->Num();
                break;
            }
            else{
                PlX[0]->Activate();
                AcP=PlX[0]->Num();
                break;
            }
        }
    }
}

void Hourglass::Log(){
    std::string acp, turnc;
    std::stringstream ss;
    ss<<AcP<<" "<<TurnCount;
    ss>>acp>>turnc;
    gout<<color(white)<<move_to(XX-290, YY-85)<<text("Turn: ")<<text(turnc)<<move_to(XX-290, YY-65)<<text("Active Player: ")<<text(acp);
}

void Hourglass::draw(){
    gout<<move_to(X,Y);
    for (int i=0; i<W; i++){
            for (int j=0; j<H; j++){
                if(looks[i][j][0]==255 && looks[i][j][1]==255 && looks[i][j][2]==255) continue;
                else gout<<color(looks[i][j][0],looks[i][j][1],looks[i][j][2])<< move_to(X+i,Y+j)<<dot;
            }
    }
}
