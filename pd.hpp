#include <iostream>
#include <memory>
#include <vector>
#include "page.hpp"
#include <cstdlib>
#pragma once
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::to_string;

class probability_distribution{
	private:
		vector<double> pvector; 
		int distSize;
	public:
		probability_distribution(int inputSize) {
			distSize = inputSize; 
		}
		
		void set_random(){
			vector<int> count(distSize , 0);
			for (int i=0; i < 100; i++){
				int num = rand % distSize;
				count[num] = count[num] + 1;
			}
			
			for (int j=0; j<distSize; j++){
				pvector[j] = count[j] / 100;
			}
	
		}
		

		string as_string(){

			string output = "";
			for (int i=0; i<distSize; i++){
				output += to_string(i) + ":" + to_string(pvector[i]) + ", ";
			}	
			return output;
		}	
		// access a specific element
		double get_pvalue(int index){
			return pvector[index];
		}
		//set whole distribution to random and normalize so sum of prob is 1
		void normalize(){
			double ptotal = 0;
			for (int i=0; i<distSize; i++){
				ptotal += pvector[i];
			}
			for (int j=0; j<distSize; j++){
				pvector[j] = pvector[j] / ptotal;
			}
		}


} 

