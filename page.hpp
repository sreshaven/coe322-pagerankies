#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "functions.hpp"
#pragma once
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::rand;
using std::srand;


class Page {
	private:
		string name;
		vector<shared_ptr<Page>> linksVector;
		int global_id;
	public:
		Page(string inputName){
			name = inputName;
			global_id = -1;
		};

		string getName(){
			return name;
		}
	
		void set_global_id(int inputNum){
			global_id = inputNum;
		}
		
		string as_string(){
			string output = "";
			output += name + '\n';
			for (int i = 0; i < linksVector.size(); i++){
				output += linksVector[i]->getName();
				if (i != linksVector.size() - 1){
					output += '\n';
				}
			}
			return output;
		}
	
		void add_link(shared_ptr<Page> linkedPage){
			linksVector.push_back(linkedPage);		
		}
	
		shared_ptr<Page> random_click(){
			if(linksVector.empty()){
				auto output = make_shared<Page>("this page has no links");
				return output;
			}
			else{
				return linksVector[realrandom_int(linksVector.size())];
			}
		}

		int global_ID(){
			return global_id;
		}

		bool page_is_link(shared_ptr<Page> linkedPage){
			for (int i = 0; i < linksVector.size(); i++){
				if (linksVector[i]->global_ID() == linkedPage->global_ID()){
					return true;
				}	
			}
			return false;
		}

		vector<shared_ptr<Page>> get_neighbors(){
			return linksVector;
		}

};
