#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>

// Verificare daca un vector e ordonat
bool check(std::vector<int> vec)
{
    for(int i=1; i<vec.size(); i++)
    {
        if(vec[i]<vec[i-1]) return false;
    }

    return true;
}

// Verificare daca un vector e o ordonare a altui vector
bool bicheck(std::vector<int> init, std::vector<int> fin)
{
    if(init.size()!=fin.size()) return false;

    std::vector<int> tmp = init;

    std::sort(tmp.begin(), tmp.end());

    for(int i=1; i<fin.size(); i++)
    {
        if(tmp[i]!=fin[i]) return false;
        if(fin[i]<fin[i-1]) return false;
    }

    return true;
}

// Determinarea elementului maxim dintr-un vector
int maxelem(std::vector<int> vec)
{
    int rez = vec[0];

    for(int i=1; i<vec.size(); i++)
    {
        if(vec[i]>rez) rez = vec[i];
    }

    return rez;
}

// Auxiliar pentru verificarea timpului
int acum()
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

// Bubble sort
std::vector<int> bubble(std::vector<int> vec)
{
    std::vector<int> rez = vec;

    for(int i=0; i<rez.size(); i++)
    {
        for(int j=0; j<rez.size(); j++)
        {
            if(rez[i]<rez[j]) std::swap(rez[i],rez[j]);
        }
    }

    return rez;
}

// Counting sort prin recreare
std::vector<int> cnt(std::vector<int> vec)
{
    std::vector<int> rez;
    std::map<int, int> H;

    for(int i=0; i<vec.size(); i++)
    {
        H[vec[i]]++;
    }

    for(auto k : H)
    {
        for(int i=0; i<k.second; i++)
        {
            rez.push_back(k.first);
        }
    }

    return rez;
}

// Counting sort prin copiere, ordonare dupa o singura cifra (auxiliar pentru Radix sort)
std::vector<int> cntdig(std::vector<int> vec, int exp)
{
    std::vector<int> rez(vec.size());

    int H[10] = { };

    for(int i=0; i<vec.size(); i++)
    {
        H[(vec[i]/exp)%10]++;
    }

    for(int i=1; i<10; i++)
    {
        H[i]=H[i]+H[i-1];
    }

    for(int i=vec.size()-1; i>=0; i--)
    {
        rez[H[(vec[i]/exp)%10] -1]=vec[i];
        H[(vec[i]/exp)%10]--;
    }

    return rez;
}

// Merge sort
std::vector<int> mrg(std::vector<int> vec)
{
    std::vector<int> rez = vec;
    //
    return rez;
}

// Quick sort
std::vector<int> quick(std::vector<int> vec)
{
    std::vector<int> rez = vec;
    //
    return rez;
}

// Radix sort
std::vector<int> radix(std::vector<int> vec)
{
    std::vector<int> rez = vec;

    int m=maxelem(vec), exp=1;

    while(m>0)
    {
        rez=cntdig(rez, exp);
        m=m/10;
        exp=exp*10;
    }

    return rez;
}


int main()
{
    std::ifstream fin("vec.in");
    std::ofstream fout("rez.md");

    // Header + formatare

    fout<<"Nr. crt. | Bubble Sort (timp) | Bubble Sort (corectitudine) | Counting Sort (timp) | Counting Sort (corectitudine) | Merge Sort (timp) | Merge Sort (corectitudine) | Radix Sort (timp) | Radix Sort (corectitudine) | Quick Sort (timp) | Quick Sort (corectitudine)\n--|--|--|--|--|--|--|--|--|--|--\n";

    // Citire + testare algoritmi

    int n;
    fin>>n;

    for(int i=0; i<n; i++)
    {
        int k,t,start,stop;
        std::vector<int> vec,rez;

        fin>>k;

        for(int j=0; j<k; j++)
        {
            fin>>t;
            vec.push_back(t);
        }

        // Nr. crt.

        fout<<i+1<<" | ";

        // Timp + corectitudine bubble sort

        start = acum();

        rez = bubble(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine count sort

        start = acum();

        rez = cnt(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine merge sort

        start = acum();

        rez = mrg(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine radix sort

        start = acum();

        rez = radix(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine quick sort

        start = acum();

        rez = quick(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);



        // Delimitator

        fout<<'\n';

    }

    fin.close();
    fout.close();
    return 0;
}