/*
 * AfterSalesService.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include <algorithm>
#include "AfterSalesService.h"

using namespace std;

int AfterSalesService::tableOrdinal = 0;

bool compare(Article* a, Article* b){
	if(a->getDeliverHome() && !b->getDeliverHome()){
		return false;
	}
	else if(!a->getDeliverHome() && b->getDeliverHome()){
					return true;
		}
	else if(!a->getDeliverHome() && !b->getDeliverHome()){
		if(abs(a->getPresentNumber() - b->getPresentNumber()) > 2){
					return (a->getPresentNumber() < b->getPresentNumber());
		}
	}
	else return false;
}

AfterSalesService::AfterSalesService(int toWrapQS) : toWrapQueueSize(toWrapQS) {
}

vector<Article*> AfterSalesService::getPresentsTable() const {
	return presentsTable;
}

queue<Article*> AfterSalesService::getToWrap() const {
	return toWrap;
}

queue<Article*> AfterSalesService::getToDeliver() const {
	return toDeliver;
}

/**
 *  Place presents on the presents table, assigning them a relative present number and a sequential number.
 *  Assumes all given presents are from the same client.
 */
void AfterSalesService::dropPresentsOnTable(vector<Article*> presents) {
	for(vector<Article*>::size_type i = 0; i<presents.size(); i++) {
		presents[i]->setPresentNumber(i+1);
		presents[i]->setArrivalNumber(++tableOrdinal);
		presentsTable.push_back(presents[i]);
	}
}

/**
 * Remove from the table all articles of a given client.
 */
vector<Article*> AfterSalesService::pickPresentsFromTable(long client) {

	vector<Article*> clientPresents;
	for(unsigned int i = 0;i < this->presentsTable.size();i++){
		if(this->presentsTable[i]->getClient() == client){
			clientPresents.push_back(this->presentsTable[i]);
			this->presentsTable.erase(this->presentsTable.begin() + i);
			i--;
		}
	}
	return clientPresents;
}

/**
 * Sort the first 10 articles in the presents table:
 *   (i) give priority to articles that are NOT to be delivered at home (client is waiting);
 *  (ii) if two articles have (relative) present numbers differing more than 2,
 *       the one with lower present number should have priority (clients should not wait too much);
 * (iii) else, maintain article order in the table.
 */
void AfterSalesService::sortArticles() {
	sort(this->presentsTable.begin(),this->presentsTable.begin()+10,compare);


}

/**
 * Move the first presents in the table to the queue of presents to wrap, taking into account the size of the queue.
 */
void AfterSalesService::enqueueArticles() {

	for(unsigned int i = 0; this->toWrap.size() < this->toWrapQueueSize && i < this->presentsTable.size();i++){
		this->toWrap.push(this->presentsTable[i]);
		this->presentsTable.erase(this->presentsTable.begin()+i);
		i--;
	}

}

/**
 * Process the first present to wrap. If it is an article to deliver home, the article is placed in the toDeliver queue.
 */
Article* AfterSalesService::wrapNext() {
	if(this->toWrap.size() == 0){
		return NULL;
	}
	Article * art;
	art = this->toWrap.front();
	this->toWrap.pop();
	if(art->getDeliverHome()){
		this->toDeliver.push(art);
		return NULL;
	}
	else return art;

}
