
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	ifstream ifs("read.txt");


	if (!ifs) {
		cout << "can not open file" << endl;
		exit(EXIT_FAILURE);
	}

	string words;  //for words
  char c; //for characters
  string line;
	int countc = 0;
  int countw = 0;
  int countl = 0;

	while (ifs >> c)
		countc++;

	cout <<"char:" << countc << endl;

  ifs.clear();
  ifs.seekg(0,ios::beg);

  while(ifs >> words)
    countw++;

  cout<<" words : "<<countw<<endl;

  ifs.clear();
  ifs.seekg(0,ios::beg);

  while(getline(ifs,line))
    countl++;

  cout<<"line : "<<countl<<endl;

	return 0;
}
