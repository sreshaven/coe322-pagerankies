#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include "link.hpp"
#pragma once
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

class Page {
	private:
		string name;
		vector<shared_ptr<Page>> linksVector;
	public:
		Page(string inputName){
			name = inputName;
		};

		string getName(){
			return name;
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
				return linksVector[rand() % linksVector.size()];
			}
		}

};
