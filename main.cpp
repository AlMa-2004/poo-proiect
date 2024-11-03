#include <iostream>
#include <ostream>
#include <chrono>
#include <vector>
#include <thread>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace std::chrono;

class Timp
{
    steady_clock::time_point start;
    public:
    //initializez parametrul cu momentul in care a fost creat obiectul, care ar fi "momentul 0"
    //pentru ca nu pot sa atribui valori intregi
    Timp(steady_clock::time_point s=steady_clock::now()):start(s)
    {
        cout<<"Numaratoarea a inceput!\n"<<endl;
    }
    int elapsed(const steady_clock::time_point moment) const
    {
        return duration_cast<seconds>(moment - start).count();
    }

    //Nu pot realiza supraincarcarea operatorului << pentru ca time_point nu memoreaza o valoare exacta,
    //ci este doar o variabila "onorifica" folosita pentru a marca un moment specific in timp;
    //Conform documentatiei, time_point este definit relativ la un "epoch" (punct de inceput),
    //specific fiecarui tip de clasa clock (de exemplu, steady_clock)
    //Acest tip de variabila este folosit doar in calcule, cum ar fi functia elapsed, pentru a masura timpul scurs intre doua momente.


};
class Animal
{
    string Nume;
    const int timpProducere;
    bool statusHranit, statusProdus;

    public:
    Animal(const string& nume, const int timp_producere, const bool status_hranit, const bool status_produs)
        : Nume(nume),
          timpProducere(timp_producere),
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
    const string Nume;
    const int timpCrestere;//o planta creste in 1sec,5sec,10sec, iar ele sunt contorizate prin elapsed
    int timpPlantat; ///!!!!timpPlantat din clasa Recolta nu poate fi 0, deoarece in secunda 0 jocul arata meniul!!!
    bool statusCrestere, statusUdat;

    ///functii complexe - de crestere cfm elapsed time, de udare
    public:

    Recolta(const string& nume="Recoltax", const int timp_crestere=0, int timp_plantat=0, const bool status_crestere=false, const bool status_udat=false)
        : Nume(nume),
          timpCrestere(timp_crestere),
          timpPlantat(timp_plantat),
          statusCrestere(status_crestere),
          statusUdat(status_udat)

    {
    }
    friend std::ostream& operator<<(std::ostream& os, const Recolta& obj)
    {
        os<< "Nume: "<<obj.Nume
        <<" timpPlantare: "<<obj.timpCrestere
        <<" statusUdat: "<<obj.statusUdat
        <<" statusCrestere: "<<obj.statusCrestere;
        return os;
    }
    void Crestere(int secunde)
    {
        if(statusCrestere==false && statusUdat && (secunde-timpPlantat)>=timpCrestere)
        {
            statusCrestere=true;
            cout<<"Planta "<<Nume<<" a crescut!\n";
        }
        else cout<<"Planta "<<Nume<<" inca creste!\n";

    }
    bool getCrescut() const
    {
        return statusCrestere;
    }
    void setUdat(bool t)
    {
        statusUdat = t;
    }
    bool getUdat() const
    {
        return statusUdat;
    }

};
class Item {
    string Nume;
    int Cantitate;
public:
    Item(const std::string& n, int c = 1) : Nume(n),Cantitate(c)
    {
        cout<<"Constructor item\n";
    }
    string getNume() const
    {
        return Nume;
    }
    int getCantitate() const
    {
        return Cantitate;
    }
    void setCantitate(int c)
    {
        Cantitate = c;
    }
    friend ostream& operator<<(ostream& os,const Item& obj) const {
        return os << obj.Nume << " (In numar de: " << obj.Cantitate << ")\n";
    }

};
class Player{

    string Nume;
    int Bani;
    //vector<Animal> Tarc;

    //DE INLOCUIT CU SMART POINTERS
    vector<Item> Inventariu;
    vector<Recolta> Camp;

public:
    //Player(): Nume("Jucator"), Bani(0){std::cout<<"Player constructor default"<<std::endl;}
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

    friend ostream& operator<<(ostream&os, const Player& obj)
    {
        os<<"Nume: "<<obj.Nume
        <<" Bani: "<<obj.Bani;
        return os;
    }

    //INVENTORY MANAGEMENT
    void adaugareItem(const Item& i) {
        for (auto& item : Inventariu) {
            if (item.getNume() == i.getNume()) {
                item.setCantitate(item.getCantitate() + i.getCantitate());
                return;
            }
        }
        Inventariu.push_back(i);

    }


    ~Player()
    {   //dealocare memorie pentru inventariu (?) optionala
        Inventariu.clear();
        Inventariu.shrink_to_fit();
        cout<<"Player destructor\n";
    }
};

int main() {

    //TEST CLASA PLAYER
    //Player p1("Anca",1000);
    // p2;
    //cout<<p1<<"\n"<<p2<<"\n";
    //Player p3(p2);
    //p1=p2;
    //cout<<p1<<"\n"<<p3<<"\n";

    //TEST CLASA TIMP + RECOLTA IN FUNCTIE DE TIMP
    Timp timpInGame;
    Recolta Grau("Grau", 1,timpInGame.elapsed(steady_clock::now()),0,1);
    std::this_thread::sleep_for(std::chrono::seconds(5)); //test pentru simularea trecerii timpului in game
    int x=timpInGame.elapsed(steady_clock::now());
    cout<<"Au trecut: "<<x<<" secunde de la pornirea jocului.\n";
    Grau.Crestere(x);


    return 0;


}