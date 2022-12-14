//Names: Sresha Ventrapragada, Amy Manning, Amanda Lee
////UT EID: svv346, alm7377, awl646
#include <iostream>
#include <memory>
#include <algorithm>
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
			for (int i = 0; i < 100 * distSize; i++){
				int num = realrandom_int(distSize);
				count[num] = count[num] + 1.0;
			}
			
			for (int j = 0; j < distSize; j++){
				pvector[j] = count[j] / (100 * distSize);
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
		
		// add to the pvalue
		void add_pvalue(int index, double addPValue){
                        pvector[index] += addPValue;
                }

		//set whole distribution to random and normalize so sum of prob is 1
		void normalize(){
			double ptotal = 0;
			for (int i = 0; i < distSize; i++){
				ptotal += pvector[i];
			}
			for (int j = 0; j < distSize; j++){
				if (ptotal == 0){
					pvector[j] = 0;
				}
				else {
					pvector[j] = pvector[j] / ptotal;
				}
			}
		}

		vector<vector<double>> rankp(){
			vector<vector<double>> rankedP;
			for(int i = 0; i < distSize; i++){
				vector<double> newinput{pvector[i], (double)i};
				rankedP.push_back(newinput);
			}
			std::sort(rankedP.begin(), rankedP.end());
			std::reverse(rankedP.begin(), rankedP.end());
			return rankedP;
		}
}; 

