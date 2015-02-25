#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>
#include <queue>
using namespace std;
struct nums{
	int number1;
	int number2;
	int number3;
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
							if(compVec->at(abs(current - numVec->at(i))) == 255 && abs(current-numVec->at(i)) != current){
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
		}outFile.close();
		extraCreditFile.close();
	}return 0;
};
