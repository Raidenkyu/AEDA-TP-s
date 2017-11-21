/*
 * Purchase.cpp
 *
 *  Created on: Nov 16, 2016
 *      Author: hlc
 */

#include "Purchase.h"

using namespace std;

Purchase::Purchase(long cli) : client (cli) {
}

long Purchase::getClient() const {
	return client;
}

list< stack<Article*> > Purchase::getBags() const {
	return bags;
}

/**
 * Create an Article associated with the client of this purchase.
 */
Article* Purchase::createArticle(long barCode, bool present, bool deliverHome) {

	Article * art = new Article(this->client,barCode);
	art->setPresent(present);
	art->setDeliverHome(deliverHome);

	return art;

}

/**
 * Add an Article to the bags of this purchase. A new bag is added when the last bag is full.
 */
void Purchase::putInBag(Article* article) {
	if(this->bags.back().size() == this->BAG_SIZE || this->bags.empty()){
		stack<Article*> bag;
		bag.push(article);
		this->bags.push_back(bag);
		return;
	}
	this->bags.back().push(article);
}

/**
 * Pop from the bags all articles that are presents.
 * All other articles are pushed back into the bags where they were, maintaining order.
 */
vector<Article*> Purchase::popPresents() {
	vector<Article*> presents;
	stack<Article*> articles;
	for(auto &bag: this->bags){
		while(!bag.empty()){
			if(bag.top()->getPresent()){
				presents.push_back(bag.top());
			}
			else{
				articles.push(bag.top());
			}
			bag.pop();
		}
		while(!articles.empty()){
			bag.push(articles.top());
			articles.pop();
		}
	}
	return presents;

}

