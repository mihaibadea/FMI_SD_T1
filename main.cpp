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
    bool sch;

    for(int i=0; i<vec.size()-1; i++)
    {
        sch=false;

        for(int j=0; j<vec.size()-i-1; j++)
        {
            if(vec[j]>vec[j+1])
            {
                std::swap(vec[j],vec[j+1]);
                sch=true;
            }
        }

        if(!sch) break;
    }

    return vec;
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

// Combinare (auxiliar pentru Merge Sort
void combin(std::vector<int> &vec, int st, int m, int dr)
{
    int nrs=m-st+1, nrd=dr-m;
    std::vector<int> s, d;

    for(int i=0; i<nrs; i++)
    {
        s.push_back(vec[st+i]);
    }

    for(int i=0; i<nrd; i++)
    {
        d.push_back(vec[m+i+1]);
    }

    int i=0, j=0, k=st;

    while(i<nrs && j<nrd)
    {
        if(s[i]<=d[j])
        {
            vec[k]=s[i];
            i++;
        }
        else if(j<nrd)
        {
            vec[k]=d[j];
            j++;
        }
        k++;
    }

    while(i<nrs)
    {
        vec[k]=s[i];
        i++;
        k++;
    }

    while(j<nrd)
    {
        vec[k]=d[j];
        j++;
        k++;
    }

}

// Merge Sort
void mrg(std::vector<int> &vec, int st, int dr)
{
    if(st<dr)
    {
        int m = (st+dr)/2;

        mrg(vec, st, m);
        mrg(vec, m+1, dr);
        combin(vec,st,m,dr);
    }
}

// Merge Sort wrapper
std::vector<int> mrgw(std::vector<int> vec)
{
    mrg(vec, 0, vec.size()-1);
    return vec;
}

// Quick Sort
void quick(std::vector<int> &vec)
{
    //
}

// Quick Sort wrapper
std::vector<int> quickw(std::vector<int> vec)
{
    quick(vec);
    return vec;
}


// Radix sort
std::vector<int> radix(std::vector<int> vec)
{
    int m=maxelem(vec), exp=1;

    while(m>0)
    {
        vec=cntdig(vec, exp);
        m=m/10;
        exp=exp*10;
    }

    return vec;
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

        // Timp + corectitudine Bubble Sort

        start = acum();

        rez = bubble(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine Counting Sort

        start = acum();

        rez = cnt(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine Merge Sort

        start = acum();

        rez = mrgw(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine Radix Sort

        start = acum();

        rez = radix(vec);

        stop = acum();

        fout<<stop-start;

        fout<<" | ";

        fout<<bicheck(vec,rez);

        // Separator

        fout<<" | ";

        // Timp + corectitudine Quick Sort

        start = acum();

        rez = quickw(vec);

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
