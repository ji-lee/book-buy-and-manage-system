#include"transaction_class.h"

/*********************************************
*函数功能：交易记录类构造函数
*函数参数：该类各个数据成员
*函数返回值：无
**********************************************/
Transaction::Transaction(int _u_id, char *_b_name, 
		float _discount, float _postage, 
		float _total_price, const char *_remark)
{
	if(NULL == _b_name) 
	{
		b_name = new char[1];
	}
	else
	{
		b_name = new char[strlen(_b_name) + 1];
		strcpy(b_name, _b_name);
	}

	if(NULL == _remark)
	{
		remark = new char[1];
	}
	else
	{
		remark = new char[strlen(_remark) + 1];
		strcpy(remark, _remark);
	}

	u_id = _u_id;
	discount = _discount;
	postage = _postage;
	total_price = _total_price;
}

/*********************************************
*函数功能：交易记录类拷贝构造函数
*函数参数：交易类对象
*函数返回值：无
**********************************************/
Transaction::Transaction(const Transaction &t)
{
	b_name = new char[strlen(t.b_name) + 1];
	remark = new char[strlen(t.remark) + 1];

	strcpy(b_name, t.b_name);
	strcpy(remark, t.remark);
	
	u_id = t.u_id;
	discount = t.discount;
	postage = t.postage;
	total_price = t.total_price;
}

/*********************************************
*函数功能：交易类析构函数
*函数参数：无
*函数返回值：无
**********************************************/
Transaction::~Transaction()
{
	delete []b_name;
	delete []remark;
}

/*********************************************
*函数功能：获取会员id
*函数参数：无
*函数返回值：id
**********************************************/
int Transaction::get_u_id()
{
	return u_id;
}

/*********************************************
*函数功能：获取图书名称
*函数参数：无
*函数返回值：图书名称
**********************************************/
char* Transaction::get_b_name()
{
	return b_name;
}

/*********************************************
*函数功能：获取折扣
*函数参数：无
*函数返回值：折扣
**********************************************/
float Transaction::get_discount()
{
	return discount;
}

/*********************************************
*函数功能：获取邮费
*函数参数：无
*函数返回值：邮费
**********************************************/
float Transaction::get_postage()
{
	return postage;
}

/*********************************************
*函数功能：获取购买总额
*函数参数：无
*函数返回值：总额
**********************************************/
float Transaction::get_total_price()
{
	return total_price;
}

/*********************************************
*函数功能：获取备注
*函数参数：无
*函数返回值：备注
**********************************************/
char* Transaction::get_remark()
{
	return remark;
}

/*********************************************
*函数功能：交易记录显示
*函数参数：无
*函数返回值：无
**********************************************/
void Transaction::display()
{
	cout<<setw(6)<<u_id
		<<setw(15)<<this->b_name
		<<setw(7)<<this->discount
		<<setw(10)<<this->postage
		<<setw(10)<<this->total_price
		<<setw(20)<<this->remark<<endl;
}

/*********************************************
*函数功能：设置备注
*函数参数：备注信息
*函数返回值：无
**********************************************/
void Transaction::set_remark(char* _remark)
{
	delete []remark;

	remark = new char[strlen(_remark) + 1];
	strcpy(remark, _remark);
}

/*********************************************
*函数功能：交易记录类=操作符实现
*函数参数：交易类对象
*函数返回值：交易类对象
**********************************************/
Transaction& Transaction::operator=(const Transaction &t)
{
	delete []this->b_name;
	delete []this->remark;

	this->b_name = new char[strlen(t.b_name) + 1];
	this->remark = new char[strlen(t.remark) + 1];
	
	strcpy(this->b_name, t.b_name);
	strcpy(this->remark, t.remark);

	this->u_id = t.u_id;
	this->discount = t.discount;
	this->postage = t.postage;
	this->total_price = t.total_price;

	return *this;
}

