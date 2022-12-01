#include <iostream>
#include <memory>
#include <vector>
#include "page.hpp"
#include "functions.hpp"
#include "pd.hpp"
#include <cstdlib>
#pragma once
using std::string;
using std::cout;
using std::endl;
using std::vector;
using std::shared_ptr;
using std::make_shared;

bool page_in_vector(vector<shared_ptr<Page>> inputVector, shared_ptr<Page> inputPage){
        for (int i = 0; i < inputVector.size(); i++){
                if (inputVector[i]->global_ID() == inputPage->global_ID()){
                        return true;
                }
        }
        return false;
}

class Web {
        private:
    		int numOfPages;
                vector<shared_ptr<Page>> pagesVector;
        public:
                Web(int inputNum){
                        numOfPages = inputNum;
                	for (int i = 0; i < numOfPages; i++){
				string name = "page" + std::to_string(i);
				auto page = make_shared<Page>(name);
				page->set_global_id(i);
				pagesVector.push_back(page);
			}
		};

		void add_page(){
			string name = "page" + std::to_string(numOfPages);
                        auto page = make_shared<Page>(name);
                        page->set_global_id(numOfPages);
                        pagesVector.push_back(page);
			numOfPages += 1;
		}

		void add_pages(int num){
			for (int i = 0; i < num; i++){
				add_page();
			}
		}

		int number_of_pages(){
			return numOfPages;
		}

		vector<shared_ptr<Page>> all_pages(){
			return pagesVector;
		}
		
		void create_random_links(int numOfLinks){
			for (int i = 0; i < numOfLinks; i++){
				int randNum1 = realrandom_int(pagesVector.size());
				int randNum2 = realrandom_int(pagesVector.size());
				while (randNum1 == randNum2 || pagesVector[randNum1]->page_is_link(pagesVector[randNum2])){
					randNum1 = realrandom_int(pagesVector.size());
                                	randNum2 = realrandom_int(pagesVector.size());
				}
				pagesVector[randNum1]->add_link(pagesVector[randNum2]);
			}
		}

		shared_ptr<Page> random_walk(shared_ptr<Page> inputPage, int length){
			auto currentPage = inputPage;
			int randNum = rand() % pagesVector.size();
			// cout << "From: " << currentPage->as_string() << endl;	
			for (int i = 0; i < length; i++){
				currentPage = currentPage->random_click();
				if (currentPage->global_ID() == -1){
					randNum = realrandom_int(pagesVector.size());
					currentPage = pagesVector[randNum]; 
				}
				// cout << "To: " << currentPage->as_string() << endl;		
			}
			return currentPage;
		}

		vector<int> sssp(shared_ptr<Page> inputPage){
			vector<shared_ptr<Page>> current_front;
			current_front.push_back(inputPage);
			vector<int> distances(numOfPages, 0);
			while (true){
				vector<shared_ptr<Page>> next_front;
				for (auto node : current_front){
					for (auto neighbor : node->get_neighbors()){
						if (!page_in_vector(current_front, neighbor) && distances[neighbor->global_ID()] == 0 && neighbor->global_ID() != inputPage->global_ID()){
							distances[neighbor->global_ID()] = distances[node->global_ID()]+1;
							next_front.push_back(neighbor);
						}
					}
				}
				if (next_front.size() == 0){
					break;
				}
				else {
					current_front = next_front;
				}
			}
			return distances;
		}	

		probability_distribution globalclick(probability_distribution currentstate){
			probability_distribution outputPD(numOfPages);
			for (int i = 0; i < numOfPages; i++){
				auto currentPage = pagesVector[i];
				if (currentPage->get_neighbors().size() == 0) {
					int randNum = realrandom_int(pagesVector.size());			
					double newPValue = outputPD.get_pvalue(randNum) + outputPD.get_pvalue(currentPage->global_ID());
                                        outputPD.set_pvalue(randNum, newPValue);
				}
				for (auto neighbor : currentPage->get_neighbors()){
					double newPValue = outputPD.get_pvalue(neighbor->global_ID()) + (currentstate.get_pvalue(currentPage->global_ID()) / currentPage->get_neighbors().size());	
					outputPD.set_pvalue(neighbor->global_ID(), newPValue);
				}		
			}
			outputPD.normalize(); 
			return outputPD;
		}

};
