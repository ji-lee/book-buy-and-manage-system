#include"user_class.h"
#include"transaction_class.h"
#include"book_class.h"

extern list<Transaction> list_t;
extern list<Book> list_book;
extern list<User> list_user;
list<Transaction> list_tmp;

/*********************************************
*函数功能：会员操作
*函数参数：无
*函数返回值：无
**********************************************/
void user()
{
	system("clear");

	char passwd[20];

	list<User>::iterator i = list_user.begin();
	
	list<User>::iterator &tmp = i;

	if(FAILE == check_user_login_id(tmp,passwd))
	{
		return;
	}

	if(FAILE == check_user_login_passwd(passwd))
	{
		return;
	}
//	User u;
	User u = *i; 
//	User &fu = u;
//	fu = *i;
//	u = *i;

	while(1)
	{
		show_user_menu();

		char select = tolower( getchar() );
		while(select != '\n' && getchar() != '\n' );
		
		switch(select)
		{
			case '1':
				u.buy();
				press_any_one();
				break;
			case '2':
				u.pay();
				press_any_one();
				break;
			case '3':
				u.view_transaction_history();
				press_any_one();
				break;
			case 'q':
				return;
			default:
				input_error();
				press_any_one();
		}
	}
}


/*********************************************
*函数功能：会员类构造函数
*函数参数：会员类各个数据成员
*函数返回值：无
**********************************************/
User::User(int _id, char *_name, char *_passwd, char *_level, char *_telephone, char *_address)
{
//	cout<<"会员构造"<<endl;
//	press_any_one();

	id = _id;
	if(NULL == _name)
	{
		name = new char[1];
	}
	else
	{
		name = new char[strlen(_name) + 1];
		strcpy(name, _name);
	}
	if(NULL == _passwd)
	{
		passwd == new char[1];
	}
	else
	{
		passwd = new char[strlen(_passwd) + 1];
		strcpy(passwd, _passwd);
	}
	if(NULL == _level)
	{
		level = new char[1];
	}
	else
	{
		level = new char[strlen(_level) + 1];
		strcpy(level, _level);
	}
	if(NULL == _telephone)
	{
		telephone = new char[1];
	}
	else
	{
		telephone = new char[strlen(_telephone) + 1];
		strcpy(telephone, _telephone);
	}
	if(NULL == _address)
	{
		address = new char[1];
	}
	else
	{
		address = new char[strlen(_address) + 1];
		strcpy(address, _address);
	}
}

/*********************************************
*函数功能：会员拷贝构造函数
*函数参数：会员类
*函数返回值：无
**********************************************/
User::User(const User &u)
{
//	cout<<"会员拷贝构造"<<endl;
//	press_any_one();

	id = u.id;
	name = new char[strlen(u.name) + 1];
	passwd = new char[strlen(u.passwd) + 1];
	level = new char[strlen(u.level) + 1];
	telephone = new char[strlen(u.telephone) + 1];
	address = new char[strlen(u.address) + 1];

	strcpy(name, u.name);
	strcpy(passwd, u.passwd);
	strcpy(level, u.level);
	strcpy(telephone, u.telephone);
	strcpy(address, u.address);
}

/*********************************************
*函数功能：会员类析构函数
*函数参数：无
*函数返回值：无
**********************************************/
User::~User()
{
//	cout<<"会员destruction"<<endl;
//	press_any_one();

	delete []name;
	delete []passwd;
	delete []level;
	delete []telephone;
	delete []address;
}

/*********************************************
*函数功能：会员购买函数
*函数参数：无
*函数返回值：无
**********************************************/
void User::buy()
{
	system("clear");
	
	char b_name[40];
	float b_price;
	float total_price;
	float discount = 1;
	float postage = 10;
	
	int u_id = get_id();
	char *user_level = get_level();

	float *price = &b_price;
	float *p_postage = &postage;
	float *p_discount = &discount;
	
	if(BOOK_NOT_EXIST == find_book(b_name, price))
	{
		return;
	}
	
	if(!(total_price = judge_book_number(b_name, b_price)))
	{
		return;
	}
	
	cal_postage_and_discount(user_level, total_price, p_postage, p_discount);

	total_price = total_price * discount + postage;

	Transaction t(u_id, b_name, discount, postage, total_price, "NO REMARK");
    
	list_tmp.push_back(t);

//	go_to_pay();

	system("clear");
	char c;
	cout<<"商品已加入到购物车，是否前去付款？(y/n):";
	cin>>c;
	while(getchar() != '\n');

	if(c == 'y')
	{
		User::pay();
	}
	else if(c == 'n')
	{
		return;
	}
	else if(c != 'y' && c != 'n')
	{
		input_error();
		return;
	}
}

/*********************************************
*函数功能：会员付款函数
*函数参数：无
*函数返回值：无
**********************************************/
void User::pay()
{
	system("clear");

	char ch;
	char mes[50];
	int u_id = get_id();
	char *user_level = get_level();

	if(CAR_EMPTY == show_transaction_car())
	{
		return;
	}
	
	cout<<"\n是否确定付款？(y/n):";
	scanf("%c", &ch);
	while(getchar() != '\n');
	
	tolower(ch);

	if(ch == 'y')
	{
		if(strcmp(user_level, "normal") == 0)
		{
			float history_total_price = 0;

			history_total_price = calculate_total_price(u_id);
			if(history_total_price >= 1000)
			{
				change_user_level(u_id);
				set_level("vip");

				cout<<"你的消费总额已达"<<history_total_price<<"元，会员级别升级为vip."<<endl;
			}
		}
		
		if(strcmp(user_level, "vip") == 0)
		{
			add_remark(mes); 
		}

		update_book_number();
		clear_transaction_car(mes);

		system("clear");
		cout<<"付款成功."<<endl;
		return;
	}
	else if(ch != 'y' && ch != 'n')
	{
		system("clear");
		cout<<"输入有误，付款失败."<<endl;
		return;
	}
	else if(ch == 'n')
	{
		system("clear");
		cout<<"付款已放弃."<<endl;
		return;
	}
}

/*********************************************
*函数功能：显示会员购买记录
*函数参数：无
*函数返回值：无
**********************************************/
void User::view_transaction_history()
{
	system("clear");

	int u_id = get_id();
	cout<<"你的历史购物记录："<<endl<<endl;
	
	transaction_top_table_show();

	list<Transaction>::iterator i = list_t.begin();
	int count = 0;
	while(i != list_t.end())
	{
		if(u_id == i->get_u_id())
		{
			count++;
			i->display();
			cout<<endl;
		}
		i++;
	}
	if(!count)
	{
		system("clear");
		cout<<"\n你的购买记录为空."<<endl;
	}

}

/*********************************************
*函数功能：会员信息显示
*函数参数：无
*函数返回值：无
**********************************************/
void User::display()
{
	cout<<setw(5)<<id
	 	<<setw(10)<<name
		<<setw(10)<<level
		<<setw(10)<<telephone
		<<setw(10)<<address<<endl;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
int User::get_id()
{
	return id;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
char* User::get_passwd()
{
	return passwd;
}

/*********************************************
*函数功能：获取会员名称
*函数参数：无
*函数返回值：会员名称
**********************************************/
char* User::get_name()
{
	return name;
}

/*********************************************
*函数功能：获取会员级别
*函数参数：无
*函数返回值：会员级别
**********************************************/
char* User::get_level()
{
	return level;
}

/*********************************************
*函数功能：获取会员电话
*函数参数：无
*函数返回值：会员电话
**********************************************/
char* User::get_telephone()
{
	return telephone;
}

/*********************************************
*函数功能：获取会员地址
*函数参数：无
*函数返回值：会员地址
**********************************************/
char* User::get_address()
{
	return address;
}

/*********************************************
*函数功能：设置会员密码
*函数参数：会员密码
*函数返回值：无
**********************************************/
void User::set_passwd(const char *_passwd)
{
	delete []passwd;
	passwd = new char[strlen(_passwd) + 1];
	strcpy(passwd, _passwd);
}

/*********************************************
*函数功能：设置会员级别
*函数参数：会员级别
*函数返回值：无
**********************************************/
void User::set_level(const char *_level)
{
	delete []level;
	level = new char[strlen(_level) + 1];
	strcpy(level, _level);
}

/*********************************************
*函数功能：==操作符实现
*函数参数：会员类对象
*函数返回值：0或1
**********************************************/
bool User::operator==(User &u)const
{
	return (id == u.id);
}

/*
User& User::operator=(const User &u)
{
	cout<<"="<<endl;
	press_any_one();

	delete []this->name;
	delete []this->passwd;
	delete []this->level;
	delete []this->telephone;
	delete []this->address;
	
	this->name = new char[strlen(u.name) + 1];
	this->passwd = new char[strlen(u.passwd) + 1];
	this->level = new char[strlen(u.level) + 1];
	this->telephone = new char[strlen(u.telephone) + 1];
	this->address = new char[strlen(u.address) + 1];

	strcpy(this->name, u.name);
	strcpy(this->passwd, u.passwd);
	strcpy(this->level, u.level);
	strcpy(this->telephone, u.telephone);
	strcpy(this->address, u.address);

	this->id = u.id;

	return *this;
}
*/

/*********************************************
*函数功能：查找购买图书
*函数参数：图书名字，图书价格
*函数返回值：FAILE或SUCCESS
**********************************************/
int find_book(char *b_name, float *b_price)
{
	cout<<"请输入你要购买的图书书名：";
	mygets(b_name, 40);

	list<Book>::iterator i = list_book.begin();
	while(i != list_book.end())
	{
		if(strcmp(b_name, i->get_b_name()) == 0)
		{
			*b_price = i->get_price();
			break;
		}
		i++;
	}
	if(i == list_book.end())
	{
		system("clear");
		cout<<"抱歉，没有你要购买的图书."<<endl;
		return BOOK_NOT_EXIST;
	}
	return BOOK_EXIST;
}

/*********************************************
*函数功能：检查会员登录id是否存在
*函数参数：会员类容器，会员密码
*函数返回值：FAILE或SUCCESS
**********************************************/
int check_user_login_id(list<User>::iterator &i, char *passwd)
{
	int id;

	cout<<"请输入id(100X):";
	cin>>id;
	cin.get();

	while(i != list_user.end())
	{
		if(i->get_id() == id)
		{
			strcpy(passwd, i->get_passwd());
			break;
		}
		i++;
	}

	if(i == list_user.end())
	{
		system("clear");
		cout<<"该id不存在，请重新输入."<<endl;
		press_any_one();
		return FAILE;
	}

	return SUCCESS;
}

/*********************************************
*函数功能：检查会员登录密码
*函数参数：输入密码
*函数返回值：FAILE或SUCCESS
**********************************************/
int check_user_login_passwd(char *passwd)
{
	int count = 2;
	char input_passwd[20];

	strcpy(input_passwd, getpass("请输入密码："));

	while(strcmp(input_passwd, passwd) != 0 && count != 0)
	{
		system("clear");
		cout<<"密码输入不对，你还有"<<count<<"次输入机会："<<endl;
		strcpy(input_passwd, getpass(""));
		count--;
	}

	if((0 == count) && strcmp(input_passwd, passwd) != 0)
	{
		system("clear");
		cout<<"三次密码输入错误.登录不成功."<<endl;
		press_any_one();
		return FAILE;
	}

	return SUCCESS;
}

/*********************************************
*函数功能：判断图书数目是否足够
*函数参数：图书名称，图书价格
*函数返回值：购买的总价格
**********************************************/
float judge_book_number(char *b_name, float b_price)
{
	int buy_book_num = 0;
	int book_total;
	float total_price = 0;

	cout<<"请输入你要购买的数量：";
	scanf("%d", &buy_book_num);
	while(getchar() != '\n');
	
	if(buy_book_num == 0)
	{
		system("clear");
		cout<<"购买数量输入错误."<<endl;
		return total_price;
	}
	
	list<Book>::iterator i = list_book.begin();
	while(i != list_book.end())
	{
		if(strcmp(b_name, i->get_b_name()) == 0)
		{
			book_total = i->get_total();	
			break;
		}
		i++;
	}
	if(buy_book_num > book_total)
	{
		system("clear");
		cout<<"抱歉，图书库存不足."<<endl;
		return total_price;
	}

	total_price = b_price * buy_book_num;
	
	return total_price;
}

/*************************************************
*函数功能：计算邮费和折扣
*函数参数：用户级别、购买金额、邮费指针、折扣指针
*函数返回值：无
**************************************************/
void cal_postage_and_discount(char *user_level, float total_price, float *p_postage, float *p_discount)
{
	if(strcmp(user_level, "normal") == 0)
	{
		if(total_price >= 150)
		{
			*p_discount = 0.95;
			*p_postage = 0;
		}
		else if(total_price >= 100)
		{
			*p_discount = 0.95;
		}
	}
	else if(strcmp(user_level, "vip") == 0)
	{
		if(total_price >= 100)
		{
			*p_postage = 0;
		}
	}
}

/*********************************************
*函数功能：显示购物车
*函数参数：无
*函数返回值：CAR_EMPTY 或 CAR_NOT_EMPTY
**********************************************/
int show_transaction_car()
{
	if(list_tmp.empty())
	{
		cout<<"你的购物车为空."<<endl;
		return CAR_EMPTY;
	}

	cout<<"你的购物车信息："<<endl;

	transaction_top_table_show();

	list<Transaction>::iterator i = list_tmp.begin();
	while(i != list_tmp.end())
	{
		i->display();
		i++;
	}
	return CAR_NOT_EMPTY;
}

/*********************************************
*函数功能：计算购买总金额
*函数参数：会员id
*函数返回值：总金额
**********************************************/
int calculate_total_price(int u_id)
{
	float history_total_price = 0;
	list<Transaction>::iterator i = list_t.begin();
	list<Transaction>::iterator j = list_tmp.begin();

	while(i != list_t.end())
	{
		if(u_id == i->get_u_id())
		{	
			history_total_price += i->get_total_price();
		}
		i++;
	}
	while(j != list_tmp.end())
	{
		history_total_price += j->get_total_price();
		j++;
	}
	
	return history_total_price;
}

/*********************************************
*函数功能：更改会员级别
*函数参数：会员id
*函数返回值：无
**********************************************/
void change_user_level(int u_id)
{
	list<User>::iterator i = list_user.begin();
	while(i != list_user.end())
	{
		if(u_id == i->get_id())
		{
			i->set_level("vip");
			break;
		}
		i++;
	}
}

/*********************************************
*函数功能：添加备注
*函数参数：备注信息
*函数返回值：无
**********************************************/
void add_remark(char *mes)
{
	char c;

	cout<<"是否添加备注？(y/n):";
	cin>>c;
	cin.get();
	tolower(c);

	if(c == 'n')
	{
		strcpy(mes, "NO REMARK");
	}
	else if(c == 'y')
	{
		cout<<"请输入备注信息："<<endl;
		mygets(mes, 50);
	}
}

/*********************************************
*函数功能：更新图书数量
*函数参数：无
*函数返回值：无
**********************************************/
void update_book_number()
{
	char *b_name;
	int b_num;
	
	list<Transaction>::iterator i = list_tmp.begin();
	list<Book>::iterator j = list_book.begin();

	while(i != list_tmp.end())
	{
		b_name = i->get_b_name();
		float b_total_price = (i->get_total_price() - i->get_postage()) / i->get_discount();
		while(j != list_book.end())
		{
			if(strcmp(b_name, j->get_b_name()) == 0)
			{
				b_num = (int) b_total_price / j->get_price();
				j->set_total(j->get_total() - b_num);
			}
			j++;
		}
		i++;
	}
}

/*********************************************
*函数功能：清空购物车，并添加备注信息到交易容器
*函数参数：备注信息
*函数返回值：无
**********************************************/
void clear_transaction_car(char *mes)
{
	list<Transaction>::iterator i = list_tmp.begin();
	while(!list_tmp.empty())
	{
		list_tmp.begin()->set_remark(mes);	
		Transaction tmp = list_tmp.front();
		
		list_tmp.pop_front();
		list_t.push_back(tmp);
	}
}

/*********************************************
*函数功能：会员操作界面显示
*函数参数：无
*函数返回值：无
**********************************************/
void show_user_menu()
{
	system("clear");

    cout<<"\n\t欢迎进入用户操作界面"
		  "\n\n\t1) --- 购买书籍"
		  "\n\n\t2) --- 付款"
		  "\n\n\t3) --- 查看历史购买记录"
		  "\n\n\tq) --- 返回上一层"
		  "\n\n\t请输入选择：";
}
