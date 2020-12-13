#include "map.h"

Map::Map()
{
    TestMode = false;
}

QStringList Map::searchAll(QString str)
{
    QStringList retList;
    cout<<"Please input your search:"<<endl;
    sent = str.toStdString();
    cout<<"Initialization\n";
    startt = clock();
    Initialization(sentCount, SentArr);
    endt = clock();
    TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
    printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
    emit sendClock(TT2);
    if(TestMode){
        cout<<"-----------Before Search----------------\n";
        printAllNode(SentArr, sents);
    }

    cout<<"Starting Search\n";
    startt = clock();
    searchSent(sent, SentArr, sentCount, myDB);
    endt = clock();
    TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
    printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
    emit sendClock(TT2);
    if(TestMode){
        cout<<"-----------Before Heap Sort----------------\n";
        printAllNode(SentArr, sents);
    }

    cout<<"Starting Sort\n";
    startt = clock();
    HeapSort(SentArr, sentCount);
    endt = clock();
    TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
    printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
    emit sendClock(TT2);
    if(TestMode){
        cout<<"-----------After Heap Sort----------------\n";
        printAllNode(SentArr, sents);
    }
    cout<<"--------------Results----------------\n";
    printTenSent(SentArr, sentCount, sents);
    for(int i = sentCount; i > (sentCount-10) && i > 0 ; i--){
        if(SentArr[i].count==0) break;
        retList.append(sents[SentArr[i].SentNo].c_str());
    }

    emit searchOk(true);
    return retList;
}

void Map::acceptFilePath(QString path)
{
    filepath = path;
    string fileName = path.toStdString();
    // INSERT WORDS
    cout<<"Reading files\n";
    startt = clock();
    sentCount = readFile(myDB, sents, fileName);
    endt = clock();
    TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
    printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);
    emit sendClock(TT2);
    if(sentCount==(-1)) {
        cout<<"Error reading file from main\n";
        emit readFileOk(false);
        return;
    }
    if(TestMode) myDB.printAll();

    if(sentCount==0) {
        emit readFileOk(false);
        cout<<"No sentences read, please check your input\n";
        return;
    }
    emit readFileOk(true);
}

void Map::acceptSearchChar(QString searchStrr)
{
    QStringList retList;
    retList = searchAll(searchStrr);
    emit sendSearchResult(retList);
}

int Map::readFile(database& myDB, vector<string> &Twits, string fileName){
    char line[300];
    int i = 1;
    ifstream myfile (fileName);

    Twits.push_back(""); // Fill up the first one line

    if (myfile.is_open()){
        while ( myfile.getline(line, 300, '\n') ){
            Twits.push_back(line);
            char * rest = line;
            char * p;
#ifdef WIN32
            while ((p = strtok_s(rest, " ,.?!:;-", &rest))){
                myDB.setUpDatabase(p,i);
            }
#else
            while ((p = strtok_r(rest, " ,.?!:;-", &rest))){
                myDB.setUpDatabase(p,i);
            }
#endif
            i++;
        }
        myfile.close();

        return i-1;
    }

    else{
        cout << "Unable to open file";
        return -1;
    }
}

void Map::printTenSent(vector<SentNode> &SentArr, int n, vector<string> sents){
    for(int i = n; i > (n-10) && i > 0 ; i--){
        if(SentArr[i].count==0) break;
        cout<<sents[SentArr[i].SentNo]<<endl;
    }
}

void Map::printAllNode(vector<SentNode> &SentArr, vector<string> sents){
    for(vector<SentNode>::iterator it = SentArr.begin(); it != SentArr.end(); it++){
        cout<<"-----------------------"<<endl;
        cout<<it->SentNo<<" "<<it->count<<endl;
        cout<<sents[it->SentNo]<<endl;
    }
}

void Map::Initialization(int sentCount, vector<SentNode> &SentArr){
    if(SentArr.size()==0){
        for(int i = 0; i <= sentCount; i++){  // SentNode(0) is used to make index start from 1
            SentNode tmp = SentNode(i);
            SentArr.push_back(tmp);
        }
    }
    else{
        for(int i = 0; i <= sentCount; i++){  // SentNode(0) is used to make index start from 1
            SentArr[i].SentNo = i;
            SentArr[i].count = 0;
        }
    }
}

void Map::searchSent(string Sent, vector<SentNode> &SentArr, int sentCount, database myDB){
    Initialization(sentCount, SentArr);
    if(Sent == "")
        Sent = "Somewhere down the road";
    istringstream iss(Sent);

    do
    {
        string subs;
        iss >> subs;

        myDB.searchWord(subs,SentArr);
    } while (iss);
}

/*-------------HEAP---------------*/
int Map::compareNode(vector<SentNode> &SentArr, int i, int j){
    if(SentArr[i].count<SentArr[j].count){
        return -1;
    }
    else if(SentArr[i].count==SentArr[j].count){
        return 0;
    }
    else{
        return 1;
    }
}

void Map::maxHeapify(vector<SentNode> &SentArr, int n, int i)
{
    int l = i*2;
    int r = i*2+1;
    int largest = -1;

    if(l<=n&&(compareNode(SentArr, l, i) > 0))
        largest = l;
    else largest = i;

    if(r<=n&&compareNode(SentArr, r, largest) > 0)
        largest = r;

    if(largest!=i){
        iter_swap(SentArr.begin() + i, SentArr.begin() + largest);
        maxHeapify(SentArr, n, largest);
    }
}

void Map::Heapify(vector<SentNode> &SentArr, int n)
{
    for(int i = int((n+1)/2); i > 0; i--)
        maxHeapify(SentArr, n, i);
}

void Map::CheckHeapOrder(vector<SentNode> &SentArr,int n)
{
    int l;
    int r;
    int largest;
    for(int i = 1; i < n/2; i++){
        l = i*2;
        r = i*2+1;
        largest = i;

        if(l<=n&&compareNode(SentArr, l, i)>0)
            cout<<"Order Wrong"<<endl;

        if(r<=n&&compareNode(SentArr, r, largest)>0)
            cout<<"Order Wrong"<<endl;
    }
}

void Map::HeapSort(vector<SentNode> &SentArr, int n)
{
    Heapify(SentArr, n);
    CheckHeapOrder(SentArr,n);
    int tmp;

    for(int i = n; i >= 2; i--){
        iter_swap(SentArr.begin() + 1, SentArr.begin() + i);
        maxHeapify(SentArr, i-1, 1);
    }
}
