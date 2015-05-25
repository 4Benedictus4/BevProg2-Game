#include "Castle.h"
#include "Unit.h"

Castle::Castle(const int x, const int y, const int w, const int h, const int id, Player* player, std::string type) : Building(x, y, w, h, id, player, type), looks(W,std::vector<std::vector<int> >(H,std::vector<int>(3)))  {
    std::ifstream f;
    f.open("Castle.txt");
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

void Castle::draw(){
    if(IsActive()){
        gout<<move_to(X,Y)<<color(P->Color()[0], P->Color()[1], P->Color()[2])<<box(W, H);
        gout<<move_to(620, YY-98)<<color(200,200,200)<<box(70,18)<<move_to(625, YY-83)<<color(black)<<text("Warrior");
        gout<<move_to(620, YY-78)<<color(200,200,200)<<box(70,18)<<move_to(625, YY-63)<<color(black)<<text("Archer");
        gout<<move_to(620, YY-58)<<color(200,200,200)<<box(70,18)<<move_to(625, YY-43)<<color(black)<<text("Merchant");
        Unit* W=new Unit("w");
        Unit* A=new Unit("a");
        if(!CanSpawn() || !CanSpawnC(W)){
            gout<<move_to(622,YY-96)<<color(black)<<line(66,14)<<move_to(688,YY-96)<<line(-66,14);
        }
        if(!CanSpawn() || !CanSpawnC(A)){
            gout<<move_to(622,YY-76)<<color(black)<<line(66,14)<<move_to(688,YY-76)<<line(-66,14);
        }
        if(!CanSpawn() || this->Owner()->Wealth()<this->Owner()->Merchant_Cost()){
            gout<<move_to(622,YY-56)<<color(black)<<line(66,14)<<move_to(688,YY-56)<<line(-66,14);
        }
    }
    gout<<move_to(X,Y);
    for (int i=0; i<W; i++){
            for (int j=0; j<H; j++){
                if(looks[i][j][0]==255 && looks[i][j][1]==255 && looks[i][j][2]==255) continue;
                if(looks[i][j][0]==0 && looks[i][j][1]==0 && looks[i][j][2]==255) gout<<color(P->Color()[0], P->Color()[1], P->Color()[2])<< move_to(X+i,Y+j)<<dot;
                else gout<<color(looks[i][j][0],looks[i][j][1],looks[i][j][2])<< move_to(X+i,Y+j)<<dot;
            }
    }
}

void Castle::Log(){
    Building::Log();
    std::string d, a, h, dm, am, r;
    std::stringstream ss;
    ss<<def<<" "<<atk<<" "<<hp<<" "<<def_mod<<" "<<atk_mod<<" "<<range;
    ss>>d>>a>>h>>dm>>am>>r;
    gout<<color(white)<<move_to(545,YY-85)<<text("Castle")<<move_to(545,YY-65)<<text(a)<<text(" + ")<<text(am)<<move_to(545,YY-45)<<text(d)<<text(" + ")<<text(dm)<<move_to(545, YY-25)<<text(h)<<move_to(545, YY-5)<<text(r);
}

std::string Castle::Spawn(event ev){
    if(ev.pos_x>620 && ev.pos_x<690 && ev.pos_y>YY-98 && ev.pos_y<YY-80){
        spawnpoints--;
        return "w";
    }
    if(ev.pos_x>620 && ev.pos_x<690 && ev.pos_y>YY-78 && ev.pos_y<YY-60){
        spawnpoints--;
        return "a";
    }
    if(ev.pos_x>620 && ev.pos_x<690 && ev.pos_y>YY-58 && ev.pos_y<YY-40){
        if(this->Owner()->Wealth()>=this->Owner()->Merchant_Cost()){
            spawnpoints--;
            this->Owner()->CallMerchant();
            this->Owner()->mod_Gold(-this->Owner()->Merchant_Cost());
            this->Owner()->mod_Mcost(10);
        }
        return "m";
    }
    else return "-";
}

void Castle::Elapse_Turn(){
    Building::Elapse_Turn();
    spawnpoints=1;
}

bool Castle::CanSpawn(){
    if(spawnpoints>0) return canSpawn;
    else return false;
}

bool Castle::CanSpawnC(Controlled* c){
    if(c->Cost()<=this->Owner()->Wealth()) return true;
    else return false;
}
