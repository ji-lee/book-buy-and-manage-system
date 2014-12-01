#ifndef __BOOK_H_
#define __BOOK_H_

#include"login.h"

//图书类
class Book
{
public:
	Book(char *_bname, char *_author, 
			char *_publisher, float _price, int _total);
	Book(const Book &b);
	~Book();

	char* get_b_name();
	char* get_author();
	char* get_publisher();
	float get_price();
	int get_total();
	
	void set_total(int _total);
	void display();
	
private:
	char *b_name;
	char *author;
	char *publisher;
	float price;
	int total;
};


extern list<Book> list_book;

#endif
