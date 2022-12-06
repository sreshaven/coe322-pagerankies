//Names: Sresha Ventrapragada, Amy Manning, Amanda Lee
////UT EID: svv346, alm7377, awl646
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
		vector<vector<double>> webMatrix;
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
		
		// creates links from random pages in the web to other random pages
		// does not link to the same page and does not link to a page if it is already one of its links
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

		// rnadomly click on current page for length input
		shared_ptr<Page> random_walk(shared_ptr<Page> inputPage, int length){
			auto currentPage = inputPage;
			int randNum = rand() % pagesVector.size();
			for (int i = 0; i < length; i++){
				currentPage = currentPage->random_click();
				if (currentPage->global_ID() == -1){
					randNum = realrandom_int(pagesVector.size());
					currentPage = pagesVector[randNum]; 
				}
			}
			return currentPage;
		}

		// single source shortest path algorithm
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

		// global click without matrix
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

		// make adjacency matrix for web graph
		vector<vector<double>> makeMatrix(){
			vector<double> matrix;
			matrix.resize(numOfPages);
			vector<vector<double>> outputMatrix;
			for (int i = 0; i < numOfPages; i++){
				outputMatrix.push_back(matrix);
			}
			for (auto page : pagesVector){
				int numOfNeighbors = page->get_neighbors().size();
				for (auto neighbor : page->get_neighbors()){
					outputMatrix[page->global_ID()][neighbor->global_ID()] = 1.0 / numOfNeighbors;
				}
			}

			// printing matrix
			/* for (int i = 0; i < numOfPages; i++){
				for (int j = 0; j < numOfPages; j++){
					cout << std::to_string(outputMatrix[i][j]).substr(0, 4) << " ";
				}
				cout << '\n';
			} */

			webMatrix = outputMatrix;
			return outputMatrix;
		}

		// print adjacency matrix
		void printMatrix(){
                        vector<int> matrix;
                        matrix.resize(numOfPages);
                        vector<vector<int>> outputMatrix;
                        for (int i = 0; i < numOfPages; i++){
                                outputMatrix.push_back(matrix);
                        }
                        for (auto page : pagesVector){
                                for (auto neighbor : page->get_neighbors()){
                                        outputMatrix[page->global_ID()][neighbor->global_ID()] = 1;
                                }
                        }

                        // printing matrix
                        for (int i = 0; i < numOfPages; i++){
                                for (int j = 0; j < numOfPages; j++){
					if (j < numOfPages - 1){
						cout << std::to_string(outputMatrix[i][j]) << ",";
					}
					else {
						cout << std::to_string(outputMatrix[i][j]);
					}
                                }
                                cout << '\n';
                        }
                }

		// global click with matrix multiplication
		probability_distribution globalclick2(probability_distribution currentstate){
                        probability_distribution outputPD(numOfPages);
			vector<vector<double>> adjMatrix = makeMatrix();
			for (int j = 0; j < numOfPages; j++){
				double new_pvalue = 0;
				for (int i = 0; i < numOfPages; i++){
					new_pvalue += adjMatrix[i][j] * currentstate.get_pvalue(i);
				}
				outputPD.set_pvalue(j, new_pvalue);
				// if page does not have any links, add pvalue to random page
				if (pagesVector[j]->get_neighbors().size() == 0){
					int randNum = realrandom_int(pagesVector.size());
                                        double newPValue = outputPD.get_pvalue(randNum) + outputPD.get_pvalue(pagesVector[j]->global_ID());
                                        outputPD.set_pvalue(randNum, newPValue);
				}
			}
			outputPD.normalize();        
			return outputPD;
                }
};
