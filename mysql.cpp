#include"mysql.h"

extern list<User> list_user;
extern list<Book> list_book;
extern list<Transaction> list_t;

/*********************************************
*函数功能：装载数据库数据到各个容器
*函数参数：无
*函数返回值：无
**********************************************/
void load_from_mysql()
{
	const char *host = "localhost";
	const char *user = "root";
	const char *pass = "zi@guo";
	const char *db   = "book";
	MYSQL *connect = NULL;	
	
	connect = mysql_init(NULL);
	if(NULL == connect)
	{
		cout<<"init failed"<<endl;
		return ;
	}

	connect = mysql_real_connect(connect, host, user, pass, db, 0, NULL, 0);
	if(NULL == connect)
	{
		cout<<"connect failed"<<endl;
		return ;
	}

	//装载用户数据
	list_user = load_user_data(connect);
	//装载图书数据	
	list_book = load_book_data(connect);
	//装载历史记录数据
	list_t = load_transaction_data(connect);

	mysql_close(connect);
}

/*********************************************
*函数功能：保存容器数据到数据库
*函数参数：无
*函数返回值：无
**********************************************/
void save_to_mysql()
{
	MYSQL *connect = NULL;	
	const char *host = "localhost";
	const char *user = "root";
	const char *pass = "zi@guo";
	const char *db   = "book";
	
	connect = mysql_init(NULL);
	if(NULL == connect)
	{
		cout<<"init failed"<<endl;
		return;
	}

	connect = mysql_real_connect(connect, host, user, pass, db, 0, NULL, 0);
	if(NULL == connect)
	{
		cout<<"connect failed"<<endl;
		return;
	}
	
	//保存会员数据
	save_user_to_mysql(connect);
	//保存图书数据
	save_book_to_mysql(connect);
	//保存购物记录
	save_transaction_to_mysql(connect);

	mysql_close(connect);
	
	system("clear");
}

/*********************************************
*函数功能：装载会员数据
*函数参数：数据库链接参数
*函数返回值：会员容器
**********************************************/
list<User> load_user_data(MYSQL *connect)
{
	MYSQL_RES *res = NULL;  
	MYSQL_ROW row  = NULL;  
	list<User> list_user;
	const char *com = "select * from user";

	int re = mysql_real_query(connect, com, strlen(com));
	if(re != 0)
	{
		cout<<"query failed"<<endl;
		return list_user;
	}
	
	res = mysql_use_result(connect);
	if(NULL == res)
	{
		cout<<"result failed"<<endl;
		return list_user;
	}
	
	int num = mysql_num_fields(res);

	while(row = mysql_fetch_row(res))
	{
		int _id	= atoi(row[0]);
		char *_u_name	 = row[1];
		char *_passwd	 = row[2];
		char *_level	 = row[3];
		char *_telephone = row[4];
		char *_address	 = row[5];

		User user(_id, _u_name, _passwd, _level, _telephone, _address);
		list_user.push_back(user);
	}
	
	mysql_free_result(res);

	return list_user;
}

/*********************************************
*函数功能：装载图书数据
*函数参数：数据库链接参数
*函数返回值：图书容器
**********************************************/
list<Book> load_book_data(MYSQL *connect)
{
	MYSQL_RES *res = NULL;  
	MYSQL_ROW row  = NULL; 
	list<Book> list_book;
	const char *com = "select * from book";

	int re = mysql_real_query(connect, com, strlen(com));
	if(re != 0)
	{
		cout<<"query failed"<<endl;
		return list_book;
	}

	res = mysql_use_result(connect);
	if(NULL == res)
	{
		cout<<"result failed"<<endl;
		return list_book;
	}
	
	int num = mysql_num_fields(res);

	while(row = mysql_fetch_row(res))
	{
		char *b_name = row[0];
		char *author = row[1];
		char *publisher = row[2];
		float price = (float)atoi(row[3]);
		int total = atoi(row[4]);

		Book book(b_name, author, publisher, price, total);
		list_book.push_back(book);
	}

	mysql_free_result(res);

	return list_book;
}

/*********************************************
*函数功能：装载交易数据
*函数参数：数据库链接参数
*函数返回值：交易数据存放容器
**********************************************/
list<Transaction> load_transaction_data(MYSQL *connect)
{
	MYSQL_RES *res = NULL;   
	MYSQL_ROW row  = NULL;  
	list<Transaction> list_t;
	const char *com = "select * from transaction_history";

	int re = mysql_real_query(connect, com, strlen(com));
	if(re != 0)
	{
		cout<<"query failed"<<endl;
		return list_t;
	}

	res = mysql_use_result(connect);

	if(NULL == res)
	{
		cout<<"result failed"<<endl;
		return list_t;
	}
	
	int num = mysql_num_fields(res);

	while(row = mysql_fetch_row(res))
	{
		int u_id = atoi(row[0]);
		char *b_name = row[1];
		float discount = (float)atoi(row[2]);
		float postage = (float)atoi(row[3]);
		float total_price = (float)atoi(row[4]);
		char *remark = row[5];

		Transaction t(u_id, b_name, discount, postage, total_price, remark);
		list_t.push_back(t);
	}

	mysql_free_result(res);

	return list_t;
}

/*********************************************
*函数功能：保存会员数据到数据库
*函数参数：数据库连接参数
*函数返回值：无
**********************************************/
void save_user_to_mysql(MYSQL *connect)
{
	char buf[100] = "0";
	
	const char buf0[40] = "insert into user values(";
	const char buf1[4] = ",'";
	const char buf2[4] = "','";
	const char buf3[3] = "')";
	
	const char *u_name;
	const char *passwd;
	const char *level;
	const char *telephone;
	const char *address;
	const char *u_id;

	int id;

	const char *com = "delete from user";

	int re = mysql_real_query(connect, com, strlen(com));
	if(re != 0)
	{
		cout<<"query failed"<<endl;
		return;
	}

	list<User>::iterator i = list_user.begin();
	
	while(!list_user.empty())
	{
		i = list_user.begin();

		u_name = i->get_name();
		passwd = i->get_passwd();
		level = i->get_level();
		telephone = i->get_telephone();
		address = i->get_address();
		id = i->get_id();

		char tmp[6] = { 0 };
		sprintf(tmp, "%d", id);
		u_id = tmp;

		strcpy(buf, buf0);
		strcat(buf, u_id);
		strcat(buf, buf1);
		strcat(buf, u_name);
		strcat(buf, buf2);
		strcat(buf, passwd);
		strcat(buf, buf2);
		strcat(buf, level);
		strcat(buf, buf2);
		strcat(buf, telephone);
		strcat(buf, buf2);
		strcat(buf, address);
		strcat(buf, buf3);
	
		const char *com = buf;
		int re = mysql_real_query(connect, com, strlen(com));
		if(re != 0)
		{
			cout<<"query failed"<<endl;
			return;
		}
		
		list_user.pop_front();	
	}

}

/*********************************************
*函数功能：保存图书数据到数据库
*函数参数：数据库连接参数
*函数返回值：无
**********************************************/
void save_book_to_mysql(MYSQL *connect)
{
	char buf[100] = "0";
	
	const char buf0[40] = "insert into book values('";
	const char buf1[4] = "','";
	const char buf2[3] = "',";
	const char buf3[2] = ",";
	const char buf4[2] = ")";

	const char *b_name;
	const char *author;
	const char *publisher;
	const char *price;
	const char *total;

	float f_price;
	float f_total;
	
	const char *com = "delete from book";

	int re = mysql_real_query(connect, com, strlen(com));
	if(re != 0)
	{
		cout<<"query failed"<<endl;
		return;
	}

	list<Book>::iterator i = list_book.begin();
	
	while(!list_book.empty())
	{
		i = list_book.begin();

		b_name = i->get_b_name();
		author = i->get_author();
		publisher = i->get_publisher();
		f_price = i->get_price();
		f_total = i->get_total();

		char tmp_1[10] = { 0 };
		char tmp_2[10] = { 0 };
		sprintf(tmp_1, "%.2f", f_price);
		price = tmp_1;
		sprintf(tmp_2, "%.2f", f_total);
		total = tmp_2;

		strcpy(buf, buf0);
		strcat(buf, b_name);
		strcat(buf, buf1);
		strcat(buf, author);
		strcat(buf, buf1);
		strcat(buf, publisher);
		strcat(buf, buf2);
		strcat(buf, price);
		strcat(buf, buf3);
		strcat(buf, total);
		strcat(buf, buf4);
		
		const char *com = buf;
		int re = mysql_real_query(connect, com, strlen(com));
		if(re != 0)
		{
			cout<<"query failed"<<endl;
			return;
		}
		
		list_book.pop_front();	
	}
}

/*********************************************
*函数功能：保存交易记录数据到数据库
*函数参数：数据库连接参数
*函数返回值：无
**********************************************/
void save_transaction_to_mysql(MYSQL *connect)
{
	char buf[150] = "0";
	
	const char buf0[50] = "insert into transaction_history values(";
	const char buf1[4] = ",'";
	const char buf2[4] = "',";
	const char buf3[4] = ",";
	const char buf4[3] = "')";
	
	const char *u_id;
	const char *b_name;
	const char *discount;
	const char *postage;
	const char *total_price;
	const char *remark;

	int _u_id;
	float _discount;
	float _postage;
	float _total_price;

	const char *com = "delete from transaction_history";
	int re = mysql_real_query(connect, com, strlen(com));
	if(re != 0)
	{
		cout<<"query failed"<<endl;
		return;
	}
	
	list<Transaction>::iterator i = list_t.begin();
	
	while(!list_t.empty())
	{
		i = list_t.begin();

		_u_id = i->get_u_id();
		_discount = i->get_discount();
		_postage = i->get_postage();
		_total_price = i->get_total_price();
		
		char tmp1[10] = { 0 };
		char tmp2[10] = { 0 };
		char tmp3[10] = { 0 };
		char tmp4[10] = { 0 };

		sprintf(tmp1, "%d", _u_id);
		sprintf(tmp2, "%.2f", _discount);
		sprintf(tmp3, "%.2f", _postage);
		sprintf(tmp4, "%.2f", _total_price);
		u_id = tmp1;
		discount = tmp2;
		postage = tmp3;
		total_price = tmp4;

		b_name = i->get_b_name();
		remark = i->get_remark();

		strcpy(buf, buf0);
		strcat(buf, u_id);
		strcat(buf, buf1);
		strcat(buf, b_name);
		strcat(buf, buf2);
		strcat(buf, discount);
		strcat(buf, buf3);
		strcat(buf, postage);
		strcat(buf, buf3);
		strcat(buf, total_price);
		strcat(buf, buf1);
		strcat(buf, remark);
		strcat(buf, buf4);
	
		const char *com = buf;
		int re = mysql_real_query(connect, com, strlen(com));
		if(re != 0)
		{
			cout<<"query failed"<<endl;
			return;
		}
		
		list_t.pop_front();	
	}
}

