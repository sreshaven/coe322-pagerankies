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

		int number_of_pages(){
			return numOfPages;
		}

		vector<shared_ptr<Page>> all_pages(){
			return pagesVector;
		}
		
		void create_random_links(int numOfLinks){
			for (int i = 0; i < numOfLinks; i++){
				int randNum1 = rand() % pagesVector.size();
				int randNum2 = rand() % pagesVector.size();
				while (randNum1 == randNum2 || pagesVector[randNum1]->page_is_link(pagesVector[randNum2])){
					randNum1 = rand() % pagesVector.size();
                                	randNum2 = rand() % pagesVector.size();
				}
				pagesVector[randNum1]->add_link(pagesVector[randNum2]);
			}
		}

		shared_ptr<Page> random_walk(shared_ptr<Page> inputPage, int length){
			auto currentPage = inputPage;
			auto endPage = inputPage;
			// cout << "From: " << currentPage->as_string() << endl;	
			for (int i = 0; i < length; i++){
				currentPage = currentPage->random_click();
				if (currentPage->global_ID() != -1){
					endPage = currentPage; 
				}
				// cout << "To: " << currentPage->as_string() << endl;		
			}
			return endPage;
		}	

};
