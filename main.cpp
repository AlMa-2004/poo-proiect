#include <iostream>
#include <ostream>
#include <chrono>
#include <vector>
#include <array>
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
    explicit Timp(steady_clock::time_point s=steady_clock::now()):start(s)
    {
        cout<<"Numaratoarea a inceput!\n"<<endl;
    }
    [[nodiscard]] long long elapsed(const steady_clock::time_point moment) const
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
    explicit Animal(string nume, int timp_producere, bool status_hranit, bool status_produs)
        : Nume(std::move(nume)),
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
    string Nume;
    int timpCrestere;//o planta creste in 1sec,5sec,10sec, iar ele sunt contorizate prin elapsed
    long long timpPlantat; ///!!!!timpPlantat din clasa Recolta nu poate fi 0, deoarece in secunda 0 jocul arata meniul!!!
    bool statusCrestere, statusUdat;

public:

    explicit Recolta(string nume="RecoltaX", const int timp_crestere=0, long long timp_plantat=0, const bool status_crestere=false, const bool status_udat=false)
        : Nume(std::move(nume)),
          timpCrestere(timp_crestere),
          timpPlantat(timp_plantat),
          statusCrestere(status_crestere),
          statusUdat(status_udat)

    {
    }

    Recolta& operator=(const Recolta& r)=default;

    friend std::ostream& operator<<(std::ostream& os, const Recolta& obj)
    {
        os<< "Nume: "<<obj.Nume
        <<" timpPlantat: "<<obj.timpPlantat
        <<" timpCrestere: "<<obj.timpCrestere
        <<" statusUdat: "<<obj.statusUdat
        <<" statusCrestere: "<<obj.statusCrestere
        <<"\n";
        return os;
    }
    void Crestere(long long secunde)
    {
        if(statusCrestere==false && statusUdat && (secunde-timpPlantat)>=timpCrestere)
        {
            statusCrestere=true;
            cout<<"Planta "<<Nume<<" a crescut!\n";
        }
        else cout<<"Planta "<<Nume<<" inca creste!\n";

    }
    [[nodiscard]] string getNume() const{return Nume;}
    [[nodiscard]] bool getCrescut() const{return statusCrestere;}
    void setUdat(bool t){statusUdat = t;}
    [[nodiscard]] bool getUdat() const{return statusUdat;}
    friend void Recoltare();

};
class Item {
    string Nume;
    int Cantitate;
public:
    explicit Item(string n, int c = 1) : Nume(std::move(n)),Cantitate(c)
    {
        cout<<"Constructor item\n";
    }
    [[nodiscard]]string getNume() const{return Nume;}
    [[nodiscard]]int getCantitate() const{return Cantitate;}
    void setCantitate(int c){Cantitate = c;}
    friend ostream& operator<<(ostream& os,const Item& obj) {
        return os << obj.Nume << " (In numar de: " << obj.Cantitate << ")\n";
    }

};
class Player
{
    string Nume;
    int Bani;
    //vector<Animal> Tarc;

    //DE INLOCUIT CU SMART POINTERS
    vector<Item> Inventariu;
    array<Recolta,5> Camp;

public:
    Player(): Nume("Jucator"), Bani(0)
    {   Item initial("Seminte",1);
        Inventariu.push_back(initial);
        cout<<"Player constructor default\n";
    }
    explicit Player(string Nume, int bani, const vector<Item>& iteme, const array<Recolta,5>& camp=array<Recolta,5>())
    : Nume(std::move(Nume)),
    Bani(bani)
    {
        cout<<"Player constructor parametrizat\n";
        Inventariu=iteme;
        Camp=camp;
    }

    //cc
    Player(const Player& p):
    Nume(p.Nume),
    Bani(p.Bani),
    Inventariu(p.Inventariu),
    Camp(p.Camp)
    {
        std::cout<<"Player constructor de copiere\n";
    }

    ~Player()
    {   //dealocare memorie pentru inventariu (?) optionala
        Inventariu.clear();
        Inventariu.shrink_to_fit();
        cout<<"Player destructor\n";
    }

    Player& operator=(const Player& p)
    {
        this->Nume=p.Nume;
        this->Bani=p.Bani;
        this->Inventariu=p.Inventariu;
        cout<<"Player assignment\n";
        return *this;
    }

    friend ostream& operator<<(ostream&os, const Player& obj)
    {
        os<<"Nume: "<<obj.Nume
        <<" Bani: "<<obj.Bani
        <<" Inventariu: ";
        for(auto& i:obj.Inventariu)
            os<<i<<" ";
        os<<"Camp:\n";
        for(auto& j:obj.Camp) {
            os<<j<<" ";
        }
        os<<"\n";
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

    //RECOLTA MANAGEMENT
    void Plantare(Item& item,int nr)
    {
        int x=item.getCantitate();
        if(nr>x)
        {
            cout<<"Nu ai asa de multe seminte pentru a planta!\n";
            nr=x;
        }
        item.setCantitate(x-nr);
        cout<<"Se planteaza semintele...\n";

        int plantate = 0;
        for (auto& parcela : Camp) {
            if (plantate>=nr) break;
            if (parcela.getNume().empty()) { // verificam daca parcela este libera
                parcela=Recolta(item.getNume(),3,0,false,false);
                cout<<"Am plantat "<<item.getNume() <<" pe o parcela libera.\n";
                plantate++;
            }
        }
        if(plantate<nr) {
            cout << "Nu mai exista locuri libere in camp pentru toate semintele.\n";
        }
    }

    void Recoltare() {
        for (auto& parcela : Camp) {
            if (parcela.getCrescut()) {
                cout << "Recolta de " << parcela.getNume() << " este gata de recoltare!\n";
                adaugareItem(Item(parcela.getNume(), 1));
                parcela = Recolta(); // resetam parcela dupa recoltare
            }
        }
    }
};

int main() {

    //TEST CLASA PLAYER
    Item i1("Seminte",100),i2("Grau",120);
    Player p1("Anca",1000,{i1,i2});
    const Player p2;
    cout<<p1<<"\n"<<p2<<"\n";
    Player p3(p2);
    p1=p2;
    p3.Plantare(i1,3);
    cout<<p1<<"\n"<<p3<<"\n";

    //TEST CLASA TIMP + RECOLTA IN FUNCTIE DE TIMP
    Timp timpInGame;
    Recolta Grau("Grau", 1,timpInGame.elapsed(steady_clock::now()),false,true);
    std::this_thread::sleep_for(std::chrono::seconds(5)); //test pentru simularea trecerii timpului in game
    const long long x=timpInGame.elapsed(steady_clock::now());
    cout<<"Au trecut: "<<x<<" secunde de la pornirea jocului.\n";
    Grau.Crestere(x);


    return 0;


}