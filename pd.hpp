#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <string>
#include "functions.hpp"
#pragma once
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

class probability_distribution{
	private:
		vector<double> pvector; 
		int distSize;
	public:
		probability_distribution(int inputSize) {
			distSize = inputSize; 
			pvector.resize(inputSize);
		}
		
		void set_random(){
			vector<double> count(distSize, 0);
			for (int i = 0; i < 100; i++){
				int num = realrandom_int(distSize);
				count[num] = count[num] + 1.0;
			}
			
			for (int j = 0; j < distSize; j++){
				pvector[j] = count[j] / 100;
			}	
		}
		
		string as_string(){
			string output = "";
			for (int i = 0; i < distSize; i++){
				cout << std::to_string(i) + ":" + std::to_string(pvector[i]).substr(0, 5) + ", ";
				
			}	
			return output;
		}	
		// access a specific element
		double get_pvalue(int index){
			return pvector[index];
		}
	
		void set_pvalue(int index, double newPValue){
			pvector[index] = newPValue;
		}
		//set whole distribution to random and normalize so sum of prob is 1
		void normalize(){
			double ptotal = 0;
			for (int i = 0; i < distSize; i++){
				ptotal += pvector[i];
			}
			for (int j = 0; j < distSize; j++){
				pvector[j] = pvector[j] / ptotal;
			}
		}

		/* vector<vector<double>> rankp(){
			vector<vector<double>> rankedP;
			for(int i = 0; i < distSize; i++){
				rankedP.push_back([i, pvector[i]]);
			}
			std::sort(rankedP.begin(), rankedP.end(), [](const std::vector<double>& a, const std::vector<double>& b) {  return a[1] < b[1];);
			return rankedP;
		} */


}; 

