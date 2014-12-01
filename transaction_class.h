#ifndef __TRANSACTION_CLASS_H_
#define __TRANSACTION_CLASS_H_

#include"login.h"

//交易记录类
class Transaction
{
public:
	Transaction(int _u_id = 0, char *_b_name = NULL, 
			float _discount = 0, float _postage = 0, 
			float _total_price = 0, const char *_remark = NULL);
	
	Transaction(const Transaction &t);
	~Transaction();

	int get_u_id();
	char* get_b_name();
	float get_discount();
	float get_postage();
	float get_total_price();
	char* get_remark();
	
	void display();
	void set_remark(char *_remark);
	Transaction& operator=(const Transaction &t);

private:
	int u_id;
	char *b_name;
	float discount;
	float postage;
	float total_price;
	char *remark;
};


extern list<Transaction> list_t;

#endif
