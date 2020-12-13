#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <QString>
#include <cstring>
#include <unordered_map>
#include <time.h>
#include <QObject>
#include <QStringList>
#include "database.h"
using namespace std;

class Map:public QObject
{
    Q_OBJECT
public:
    Map();


public slots:

    QStringList searchAll(QString);

    void acceptFilePath(QString);

    void acceptSearchChar(QString);

signals:
    void sendSearchResult(QStringList);
    void readFileOk(bool);
    void searchOk(bool);
    void sendClock(double);

protected:
    void Initialization(int sentCount, vector<SentNode> &SentArr);
    void searchSent(string Sent, vector<SentNode> &SentArr, int sentCount, database myDB);

    void printTenSent(vector<SentNode> &SentArr, int n, vector<string> sents);
    void printAllNode(vector<SentNode> &SentArr, vector<string> sents);
    int readFile(database& myDB, vector<string> &Twits, string fileName);

    /*-------------HEAP---------------*/
    int compareNode(vector<SentNode> &SentArr, int i, int j);
    void maxHeapify(vector<SentNode> &SentArr, int n, int i);
    void Heapify(vector<SentNode> &SentArr, int n);
    void CheckHeapOrder(vector<SentNode> &SentArr,int n);
    void HeapSort(vector<SentNode> &SentArr, int n);
    /*------------END_HEAP-------------*/

    bool TestMode; // Print database out.

private:
    QString filepath;
    clock_t startt, endt;
    double TT2;

    database myDB;
    vector<SentNode> SentArr;
    vector<string> sents;
    int sentCount = 0;
    string sent;
};

#endif // MAP_H
