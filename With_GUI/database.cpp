#include "database.h"

database::database()
{

}

void database::setUpDatabase(string word, int i){
    unordered_map<string, vector<WordNode> >::iterator it;
    it = Database.find(word);

    if(it==Database.end()){
        WordNode newNode = WordNode();
        vector<WordNode> newVec;
        newNode.SentNo = i;
        newNode.count = 1;
        newVec.push_back(newNode);
        Database.insert(std::make_pair(word, newVec));
    }
    else{
        if(it->second[it->second.size()-1].SentNo==i){
            it->second[it->second.size()-1].count++;
        }
        else{
            WordNode newNode = WordNode();
            newNode.SentNo = i;
            newNode.count = 1;
            it->second.push_back(newNode);
        }
    }
}

void database::searchWord(string word, vector<SentNode> &SentArr){

    unordered_map<string, vector<WordNode> >::iterator it;
    it = Database.find(word);

    if(it==Database.end()) return;

    for(int i = 0; i < it->second.size();i++){
        SentArr[it->second[i].SentNo].count += it->second[i].count;
    }
}

void database::printAll(){
    for(unordered_map<string, vector<WordNode> >::iterator it = Database.begin(); it != Database.end();it++){
        cout<<it->first<<endl;
        for(int i = 0; i < it->second.size();i++){
            cout<<it->second[i].SentNo<<" "<<it->second[i].count<<endl;
        }
    }
}

