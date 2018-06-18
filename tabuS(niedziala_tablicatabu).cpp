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

    list<zad> tmp = inst;
    int s = CMax(tmp, tmp.size()-1, tmp.back().maszyny.size()-1);
    list<zad>::iterator x;
    list<zad>::iterator y;
    list<zad>::iterator t;    // zapamietanie pozycji na ktorej byl najlepszy cmax
    list<zad> tabu[10];

while( nriter < 20)
{
    zad tmp2 = tmp.front();
    tmp.pop_front();

    x=tmp.begin();
    y=tmp.end();
    t=tmp.begin();
    int t0=0;
    for( ; x != y ; x++)
    {
        tmp.insert(++x,tmp2);
                if(CMax(tmp, tmp.size()-1, tmp.back().maszyny.size()-1)<s)
                {
                    s=CMax(tmp, tmp.size()-1, tmp.back().maszyny.size()-1);
                    t0=distance(x,t);
                    advance(t,t0);
                }
                tmp.erase(--x);

    }
    tmp.insert(t,tmp2);
    tabu[nriter]=tmp;

    nriter++;
}
    for (list<zad>::iterator i = tmp.begin(); i != tmp.end(); ++i)
        {
            cout << (*i).idZad << " ";
        }
     cout << endl << "najlepszy CMax: " << s << endl;
    inst.clear();

    system("PAUSE");

    return 0;
}
