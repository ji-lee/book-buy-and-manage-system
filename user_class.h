#ifndef __USER_CLASS_H_
#define __USER_CLASS_H_

#include"login.h"

#define BOOK_EXIST     1
#define BOOK_NOT_EXIST 0
#define CAR_EMPTY      0
#define CAR_NOT_EMPTY  1

//用户类
class User
{
public:
	User(int _id = 0, char *_name = NULL, char *_passwd = NULL, 
		 char *_level = NULL, char *_telephone = NULL, 
		 char *_address = NULL);
	User(const User &u);
	~User();
	
	void buy();
	void pay();
	void view_transaction_history();
	void display();

	int get_id();
	char* get_passwd();
	char* get_name();
	char* get_level();
	char* get_telephone();
	char* get_address();
	
	void set_passwd(const char* _passwd);
	void set_level(const char* _level);
	
	bool operator==(User &u)const;
//	User& operator=(const User &u);

private:
	int id;
	char *name;
	char *passwd;
	char *level;
	char *telephone;
	char *address;
};

int user_login(User &f_u);                                        //会员登录

void show_user_menu();                                            //显示会员操作选择菜单

int check_user_login_id(list<User>::iterator &i, char *passwd);    //检查会员登录id   
int check_user_login_passwd(char *passwd);                        //检查会员密码	


int find_book(char *b_name, float *b_price);                      //查找图书 
float judge_book_number(char *b_name, float b_price);             //判断图书数量是否足够
void cal_postage_and_discount(char *user_level, 
		float total_price, float *postage, float *discount);      


int show_transaction_car();                                       //显示购物车
int calculate_total_price(int u_id);                              //计算历史购买总额
void change_user_level(int u_id);                                 //更改会员级别
void add_remark(char *mes);                                       //vip添加备注
void clear_transaction_car(char *mes);                            //清空购物车
void update_book_number();                                        //更新图书数量

extern list<User> list_user;                                      //外部定义用户容器

extern void transaction_top_table_show();                         //外部定义交易信息输出表头显示 

#endif
