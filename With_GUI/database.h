#ifndef DATABASE_H
#define DATABASE_H
#include<iostream>
#include<sstream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>
#include<iterator>
#include<fstream>
#include<cstring>
#include<unordered_map>
#include <time.h>

using namespace std;

struct WordNode{
    int SentNo;
    int count;
};


struct SentNode{
    int SentNo;
    int count;
    SentNode(int i){
        SentNo = i;
        count = 0;
    }
};

class database{
public:
    database();
private:
        unordered_map<string, vector<WordNode> > Database;
    /*
        In each database node:
        {
            string: word;
            map:
            {
                int #OfSentence;
                int #HappenInSentence;
            }
        }
    */

public:
    void setUpDatabase(string word, int i);
    void searchWord(string word, vector<SentNode> &SentArr);
    void printAll();
};

#endif // DATABASE_H
