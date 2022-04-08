#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <vector>
#include <map>

using namespace std;

class Token {
public :
    string token;
    string value;
    int line;
    int position;
};

int main(){

    ifstream finT("tokens.txt");
    ifstream finI("input.txt");

    map<string,string> regularExpressions;

    string t, ct;
    int counter = 0;
    while(finT >> t){
        counter++;
        if(counter % 2 == 1){
            regularExpressions.insert({t, ""});
            ct = t;
        }
        else{
            regularExpressions.find(ct)->second = t;
        }
    }

    string allRegex = "";
     for (auto regexIterator = regularExpressions.begin(); regexIterator != regularExpressions.end(); ++regexIterator){
        allRegex += regexIterator->first + "|";
     }
    allRegex = allRegex.substr(0, allRegex.size()-1);

    vector<Token> tokenList;

    int line = 1;

    string s;
    while(getline(finI, s)){ /// Parcurg linie cu linie inputul si pastrez intr-o lista de clase 'Token' toate detaliile mai putin identificatorul
        regex reg(allRegex); /// Pe care nu pot sa il stiu deoarece trec cu allRegex

        auto applyRegexOnTextIterator = sregex_iterator( s.begin(), s.end(), reg);

        auto applyRegexOnTextIteratorEnd = sregex_iterator();

        int poz = 1;

        for ( auto it = applyRegexOnTextIterator; it != applyRegexOnTextIteratorEnd; ++it ){
            Token tok;
            tok.value = it->str();
            tok.line = line;
            tok.position = poz++;

            tokenList.push_back(tok);
        }
        line++;
    }

    /// Nemaicontand pozitia si alte informatii despre tokeni, aici gasesc trecand prin fiecare expresie regulata in parte si setez identificatorul(token)
    for (auto regexIterator = regularExpressions.begin(); regexIterator != regularExpressions.end(); ++regexIterator){
        regex reg(regexIterator->first);

        smatch m;
         for (auto &fname : tokenList) {
            if(regex_match(fname.value, m, reg)){
                fname.token = regexIterator->second;
            }
         }


    }

    for (auto match = tokenList.begin(); match != tokenList.end(); ++match){
        cout<< "Token = " << match->token << " ; Value = " << match->value << " ; Line = " << match->line << " ; Index = " << match->position << endl;
    }
}
