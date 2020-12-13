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

bool TestMode = false; // Print database out.

struct SentNode{
	int SentNo;
	int count;
	//string sent;

	SentNode(int i){
		SentNo = i;
		count = 0;
		//sent = "";
	}
};

struct WordNode{
	int SentNo;
	int count;
};

class myDatabase{
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

void Initialization(int sentCount, vector<SentNode> &SentArr);
void searchSent(string Sent, vector<SentNode> &SentArr, int sentCount, myDatabase myDB);
/*-------------HEAP---------------*/
int compareNode(vector<SentNode> &SentArr, int i, int j);
//void swap(vector<SentNode> &SentArr, int i, int j);
void maxHeapify(vector<SentNode> &SentArr, int n, int i);
void Heapify(vector<SentNode> &SentArr, int n);
void CheckHeapOrder(vector<SentNode> &SentArr,int n);
void HeapSort(vector<SentNode> &SentArr, int n);
/*------------END_HEAP-------------*/

void printTenSent(vector<SentNode> &SentArr, int n, vector<string> sents);
void printAllNode(vector<SentNode> &SentArr, vector<string> sents);
//int readWords(string inputFile, myDatabase myDB, vector<string> &Twits);
int readFile(myDatabase& myDB, vector<string> &Twits, string fileName);


int main(int argc, char *argv[]){

	double TT2;
  	clock_t startt, endt;

	myDatabase myDB;
	vector<string> sents;

	if(argc!=2){
		cout<<"Usage "<<argv[0]<<" + INPUT_FILE_NAME\nPlease check your input"<<endl;
		return -1;
	}

	string fileName = argv[1];

	int sentCount = 0;

	// INSERT WORDS
	cout<<"Reading files\n";
	startt = clock(); 
	sentCount = readFile(myDB, sents, fileName);
	endt = clock();
	TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
  	printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);

	if(sentCount==(-1)) {
		cout<<"Error reading file from main\n";
		return -1;
	}

	if(TestMode) myDB.printAll();

	vector<SentNode> SentArr;

	if(sentCount==0) {
		cout<<"No sentences read, please check your input\n";
		return -1;
	}

	string sent;
	cout<<"Please input your search:"<<endl;
	getline(cin, sent);

	cout<<"Initialization\n";
	startt = clock(); 
	Initialization(sentCount, SentArr);
	endt = clock();
	TT2 = (double)(endt-startt)/CLOCKS_PER_SEC;
  	printf("FINISHED --- TOTAL CPU TIME %f SECS \n",(float)TT2);

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

	if(TestMode){ 
		cout<<"-----------After Heap Sort----------------\n";
		printAllNode(SentArr, sents);
	}
	
	cout<<"--------------Results----------------\n";

	printTenSent(SentArr, sentCount, sents);

	return 0;
}

int readFile(myDatabase& myDB, vector<string> &Twits, string fileName){
	char line[300];
	int i = 1;
	ifstream myfile (fileName);

	Twits.push_back(""); // Fill up the first one line

	if (myfile.is_open()){
		while ( myfile.getline(line, 300, '\n') ){
			//cout << line << '\n';
			Twits.push_back(line);
			//char * str = new char [line.length()+1];;
			//strcpy (str, line.c_str());
			char * rest = line;
			char * p;
			while ((p = strtok_r(rest, " ,.?!:;-", &rest))){
				myDB.setUpDatabase(p,i);
			}
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

void printTenSent(vector<SentNode> &SentArr, int n, vector<string> sents){
	for(int i = n; i > (n-10) && i > 0 ; i--){
		if(SentArr[i].count==0) break;
		cout<<sents[SentArr[i].SentNo]<<endl;
	}
}

void printAllNode(vector<SentNode> &SentArr, vector<string> sents){
	for(vector<SentNode>::iterator it = SentArr.begin(); it != SentArr.end(); it++){
		cout<<"-----------------------"<<endl;
		cout<<it->SentNo<<" "<<it->count<<endl;
		cout<<sents[it->SentNo]<<endl;
	}
}

void myDatabase::printAll(){
	for(unordered_map<string, vector<WordNode> >::iterator it = Database.begin(); it != Database.end();it++){
		cout<<it->first<<endl;
		for(int i = 0; i < it->second.size();i++){
			cout<<it->second[i].SentNo<<" "<<it->second[i].count<<endl;
		}
	}
}

void myDatabase::setUpDatabase(string word, int i){
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

void myDatabase::searchWord(string word, vector<SentNode> &SentArr){

	unordered_map<string, vector<WordNode> >::iterator it;
	it = Database.find(word);

	if(it==Database.end()) return;

	for(int i = 0; i < it->second.size();i++){
		SentArr[it->second[i].SentNo].count += it->second[i].count;
	}
}

void Initialization(int sentCount, vector<SentNode> &SentArr){
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

void searchSent(string Sent, vector<SentNode> &SentArr, int sentCount, myDatabase myDB){
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
int compareNode(vector<SentNode> &SentArr, int i, int j){
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

void maxHeapify(vector<SentNode> &SentArr, int n, int i)
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
  	//swap(SentArr, i, largest);
    maxHeapify(SentArr, n, largest);
  }
}

 void Heapify(vector<SentNode> &SentArr, int n)
 {
  for(int i = int((n+1)/2); i > 0; i--)
    maxHeapify(SentArr, n, i);
 }

 void CheckHeapOrder(vector<SentNode> &SentArr,int n)
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

void HeapSort(vector<SentNode> &SentArr, int n)
{
  Heapify(SentArr, n);
  CheckHeapOrder(SentArr,n);
  int tmp;

  for(int i = n; i >= 2; i--){
  	iter_swap(SentArr.begin() + 1, SentArr.begin() + i);

  	//swap(SentArr,1,i);

    maxHeapify(SentArr, i-1, 1);  
  }
}
