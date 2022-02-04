#include <iostream>
#include <unordered_map>
#include <fstream>

using namespace std;

#ifndef UNTITLED_HASHMAP_H
#define UNTITLED_HASHMAP_H

struct Pair
{
    char ter;
    char nonter;
};

class HashMap
{
    unordered_map< char, Pair[]> htmap;

    public:

        void put(char key, char terminal,char nonterminal,int &i )
        {
          struct Pair t;

            t.nonter = nonterminal;
            t.ter = terminal;

            htmap[key][i] = t;

            ++i;
        }

        void remove(char key)
        {
            htmap.erase(key);
        }

        void get(char key,int n)
        {
            for (int i = 0; i < n; ++i)
            {
                cout<<key<<'-'<<htmap[key][i].ter<<htmap[key][i].nonter<<endl;
            }
        }

        bool check(string word,int s, int r, int d)
        {
            int x = 0, limit = s;
            char key = 'S';

            struct Pair t;

            unordered_map< char, Pair[]>  h1;

            for (int i = 0; i < limit; ++i)
            {
                if (htmap[key][i].ter == word[0] && i != 0)
                {

                    t.nonter = htmap[key][i].nonter;
                    t.ter = htmap[key][i].ter;

                    h1[key][i] = t;
                    htmap[key][i] = htmap[key][0];
                    htmap[key][0] = h1[key][i];

                    i = -1;
                }

                if (htmap[key][i].ter == word[x])
                {
                    if (htmap[key][i].nonter == 'S') x++;

                    else if (htmap[key][i].nonter == 'D')
                            {
                                ++x;
                                if (key != 'D') i = -1;
                                limit = d;
                                key = 'D';
                            }

                    else if (htmap[key][i].nonter == 'F')
                            {
                                ++x;
                                if (key != 'F') i = -1;
                                limit = r;
                                key = 'F';
                            }

                }
            }

            if (x == word.length() - 1) return true;
            else return false;

        }

};

static void read(HashMap &htm, int &s, int &d, int &r)
{
    string myText, var;
    int n = 0;

    fstream file;
    file.open("input.txt");

    while (getline(file, myText))
    {
        if (myText[0] == 'S') s++;
        if (myText[0] == 'D') d++;
        if (myText[0] == 'F') r++;

        if (myText[0] != var[0]) n = 0;

        htm.put(myText[0], myText[2], myText[3], n);

        var = myText;
    }
    file.close();
}

#endif //UNTITLED_HASHMAP_H
