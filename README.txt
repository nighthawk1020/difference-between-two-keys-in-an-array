To run this program you have to first type make into the command line.
Then after compilation you have to type:
./submission INPUTFILE.TXT OUTPUTFILE.TXT
If this isn't the input the program will reject it as incorrect input.
My code is as follows:
#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <queue>
using namespace std;
struct nums{
	int number1 = 0;
	int number2 = 0;
	int number3 = 0;
};
struct comp{
	bool operator()(nums a, nums b){
		return a.number1 > b.number1;
	}
};
int main(int argc, char* argv[]){
	if(argc != 3){
		cerr<<"Usage: ./submission inputFile outputFile"<<endl;
	}else{
		vector<int> * compVec = new vector<int>;
		vector<int> * numVec = new vector<int>;
		vector<int> * printed = new vector<int>;
		priority_queue<nums, vector<nums>, comp> numQueue;
		int count = 0;
		int current = 0;
		int max = 0;
		bool print = false;
		ifstream inFile(argv[1]);
		ofstream outFile(argv[2]);
		ofstream extraCreditFile("output_ExtraCredit.txt");
		while(inFile.is_open()){
			inFile>>current;
			if(current > 0){
				if(current > max){
					max = current;
					compVec->resize(max + 1);
					printed->resize(max + 1);
				}if(compVec->at(current) != 255){
					count++;
					numVec->push_back(current);
					compVec->at(current) = 255;
					if(count > 2){
						for(int i = 0; i < count - 1; i++){
							if(compVec->at(abs(current - numVec->at(i))) == 255 && abs(current - numVec->at(i)) != current){
								int num = numVec->at(i);
								int num2 = current;
								if(!print){
									outFile<<abs(num2 - num)<<endl;
									print = true;
								}if(printed->at(abs(current-numVec->at(i))) != 255){
									if(num2 > num){
										nums number;
										number.number1 = num2-num;
										number.number2 = num2;
										number.number3 = num;
										numQueue.push(number);
										printed->at(num2-num) = 255;
									}else{
										nums number;
										number.number1 = num - num2;
										number.number2 = num;
										number.number3 = num2;
										numQueue.push(number);
										printed->at(num-num2) = 255;
									}
								}
							}
						}
					}
				}
			}if(inFile.eof()){
				inFile.close();
				delete compVec;
				delete numVec;
			}
		}while(!numQueue.empty()){
			extraCreditFile<<numQueue.top().number1<< " " << numQueue.top().number2 << " " << numQueue.top().number3<< endl;
			numQueue.pop();
		}
	}return 0;
};
This is more efficient than a searching algorithm if there is a value that is the difference between two other keys. If there is not a value that is the difference between two keys, then it approaches the same efficiency as a sequential searching algorithm. Once my algorithm accepts a value that would either be the difference between two keys or a value that, when subtracted from another key, is a key, it will immediately be printed to the output file and the program will terminate.
The worst-case time complexity is O(n^2). When the input file is being read by my algorithm, each new key value is immediately compared to every other key value so as to keep effeciency up. It stays at O(n^2) because my algorithm is basically two for loops that processes the entire input immediately.
I used a vector to make the indexes all of the values that are input from the text file. I used another vector to keep track of all of the input as it is sequentially input for easier comparisons to each input value. I used a third vector to keep track of whatever values were already printed to the extra credit file. Then for the sorted output I kept track of all the triples that worked by using a struct for the three print out values and I kept it in a priority queue so that sorting was automatic. My comparisons would be whatever value was recently input is subtracted from every value that was previously input and if that number existed in my comparison array (where the indexes are the input values) then I would print out those three numbers in the specified order.

input:
1
2
3
7
15
22

output:
2

Extra Credit:
1 3 2
2 3 1
7 22 15
15 22 7

input: 
14
89
18
105
23
4
35
99
67
76
198
20
5
38
55
2
30
19
487
11
40
10
13
27
22
45
37
231
46
17
731
49
167
234
59
91
179
201

output:
14

Extra Credit:
2 40 38
4 23 19
5 35 30
10 23 13
11 13 2
13 27 14
14 18 4
17 76 59
18 23 5
19 30 11
20 38 18
23 99 76
27 45 18
30 40 10
35 55 20
38 40 2
40 67 27
45 49 4
46 105 59
49 59 10
55 59 4
67 105 38
76 89 13
89 99 10
99 198 99
167 234 67
 

input:
10
15
16
19
22
25
200
150
175

output:
15

Extra Credit:
10 25 15
15 25 10
25 200 175
150 175 25

input:
10
15
16
17
18
19
21
22
23
24
100
250

output:
