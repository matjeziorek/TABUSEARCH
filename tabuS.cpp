#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>

using namespace std;

struct zad
{
    vector<int> maszyny;
    int wZad, idZad;
    zad()
    {
        wZad=0;
        idZad=0;
    }
};



void wczytaj(list<zad> &msz, string nazwaPliku, int nrInst)
{
    fstream plik;
    plik.open(nazwaPliku.c_str(), ios::in);
    string tmpS;
    int tmpT, i=0, iMaszyn=0;

    if (plik.good())
    {
        for (int j=0; j<nrInst; j++)
        {
            plik >> tmpS >> i >> iMaszyn;
            for (int k=0; k<i; k++)
            {
                for (int l=0; l<iMaszyn; l++)
                    plik >> tmpT >> tmpT;
            }
        }
        plik >> tmpS >> i >> iMaszyn;
        for (int j=0; j<i; j++)
        {
            zad tmpZ;
            for (int k=0; k<iMaszyn; k++)
            {
                plik >> tmpT >> tmpT;
                tmpZ.maszyny.push_back(tmpT);
            }
            tmpZ.idZad=j+1;
            msz.push_back(tmpZ);
        }
    }
    else
    {
        cout << "Blad przy otwieraniu pliku" << endl;
        system("PAUSE");
        plik.close();
    }
    plik.close();
}

int CMax(list<zad> &msz, int idZad, int idMaszyny)
{
    int cmax=0;

    if (idMaszyny<0)
        return 0;
    if (idZad<0)
        return 0;
    if ((idMaszyny==0)&&(idZad==0))
        return msz.front().maszyny[0];
    else
    {
        list<zad>::iterator i = msz.begin();
        advance(i,idZad);
        cmax=max(CMax(msz, idZad-1, idMaszyny), CMax(msz, idZad, idMaszyny-1))+(*i).maszyny[idMaszyny];

    }
    return cmax;
}


int main()
{
    int nriter=0;

    list<zad> inst;

    wczytaj(inst, "FSTA.txt", 0);
    for (list<zad>::iterator i = inst.begin(); i != inst.end(); ++i)
    {
        cout << (*i).idZad << " ";
    }
    cout<<endl;
    cout << endl << "poczatkowy CMax: " << CMax(inst, inst.size()-1, inst.back().maszyny.size()-1) << endl;

    list<zad> tmp = inst;   //przypisuje pocz¹tkowe ustawienie do nowej listy
    int s = CMax(tmp, tmp.size()-1, tmp.back().maszyny.size()-1); //przypisuje poczatkowy cmax do zmiennej s
    list<zad>::iterator x;
    list<zad>::iterator y;
    list<zad>::iterator t;    // zapamietanie pozycji na ktorej byl najlepszy cmax
   //list<zad> tabu[10];

    while( nriter < 10) //warunkiem zakonczenia jest wykonanie 10 iteracji
    {
        zad tmp2 = tmp.front();     //tworzy zmienna przechowujaca pierwszy element listy
        tmp.pop_front();            // usuwa pierwszy element

        x=tmp.begin();          //wskazuje na poczatek listy zadan
        y=tmp.end();            //wskazuje na koniec listy zadan
        t=tmp.begin();
        int t0=0;
        for( ; x != y ; x++)
        {
            tmp.insert(++x,tmp2); //na poczatku pierwsze zadanie jest wstawiane w kolejne miejsca
            if(CMax(tmp, tmp.size()-1, tmp.back().maszyny.size()-1)<s) //je¿eli nowa kolejnoœæ ma lepszy cmax
            {
                s=CMax(tmp, tmp.size()-1, tmp.back().maszyny.size()-1); //to zamien zmienna przechowujaca najmniejszy cmax
                t0=distance(x,t);   //aby wiedziec jaka kolejnosc daje najlepszy wynik
                advance(t,t0);      //nale¿y przesun¹æ iterator do danej pozycji
            }
            tmp.erase(--x);         //usuniêcie wartoœci z u¿ywanej pozycji aby mo¿na by³o w kolejnych potórzeniach wstawiæ w kolejne pozycje

        }
        tmp.insert(t,tmp2);         //iterator t przechowuje pozycje dla ktorej cmax byl najlepszy i obecnie u¿ywana kolejnosc bedzie ta najlepsza
        //tabu[nriter]=tmp;

        nriter++; //zwiekszenie liczby iteracji
    }
    for (list<zad>::iterator i = tmp.begin(); i != tmp.end(); ++i) //na koniec wypisywana jest najlepsza kolejnosc
    {
        cout << (*i).idZad << " ";
    }
    cout << endl << "najlepszy CMax: " << s << endl;            //i najlepszy czas
    inst.clear();

    system("PAUSE");

    return 0;
}
