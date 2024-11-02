#include <iostream>
#include <ostream>
using namespace std;
#include <SFML/Graphics.hpp>
#include <ctime>
#include <chrono>

class Animal
{
    string Nume;
    bool statusHranit;
    bool statusProdus;

    public:
    Animal(const string& nume, const bool status_hranit, const bool status_produs)
        : Nume(nume),
          statusHranit(status_hranit),
          statusProdus(status_produs)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, const Animal& obj)
    {
            os<< "Nume: " << obj.Nume
            << " statusHranit: " << obj.statusHranit
            << " statusProdus: " << obj.statusProdus;
        return os;
    }
};

class Recolta
{
    string Nume;
    const int timpPlantare; //o planta creste in 1min,5min,10min, iar ele sunt contorizate prin elapsedTime
    bool statusCrestere, statusUdat;

    //odata ce le recoltez, ele revin in inventarul playerului

    ///functii complexe - de crestere cfm elapsed time, de udare
    public:

    Recolta(const string& nume="Recoltax", const int timp_plantare=1, const bool status_crestere=false, const bool status_udat=false)
        : Nume(nume),
          timpPlantare(timp_plantare),
          statusCrestere(status_crestere),
          statusUdat(status_udat)
    {
    }
    friend std::ostream& operator<<(std::ostream& os, const Recolta& obj)
    {
        os<< "Nume: "<<obj.Nume
        <<" timpPlantare: "<<obj.timpPlantare
        <<" statusUdat: "<<obj.statusUdat
        <<" statusCrestere: "<<obj.statusCrestere;
        return os;
    }
};

class Player{

    string Nume;
    int Bani;
public:
    Player(): Nume("Jucator"), Bani(0){std::cout<<"Player constructor default"<<std::endl;}
    Player(const string& Nume, int bani) : Nume(Nume), Bani(bani)
    {
        cout<<"Player constructor parametrizat\n";
    }

    //cc
    Player(const Player& p): Nume(p.Nume), Bani(p.Bani)
    {
        std::cout<<"Player constructor de copiere\n";
    }


    Player& operator=(const Player& p)
    {
        this->Nume=p.Nume;
        this->Bani=p.Bani;
        std::cout<<"Player assignment\n";
        return *this;
    }

    //daca o sa am un vector inventariu, trebuie sa ma asigur neaparat ca il sterg cand sterg playerul
    ~Player(){std::cout<<"Player destructor\n";}
    friend ostream& operator<<(ostream&os, const Player& obj)
    {
        os<<"Nume: "<<obj.Nume
        <<" Bani: "<<obj.Bani;
        return os;
    }
};
class Meniu
{

};
int main() {
    Player p1("Anca",1000);
    Player p2;
    cout<<p1<<"\n"<<p2<<"\n";
    Player p3(p2);
    p1=p2;
    cout<<p1<<"\n"<<p3<<"\n";

    return 0;


}