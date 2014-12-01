#ifndef __ADMIN_CLASS_H_
#define __ADMIN_CLASS_H_

#include"login.h"

//管理员类
class Admin
{
public:
	Admin(int _id = 0, char *_passwd = NULL);
	~Admin();
//	Admin& operator=(const Admin &ad);

	void change_admin_passwd();
	void book_manage();
	void user_manage();
	void set_id(int _id);
	void reset_passwd(char *new_passwd);
private:
	int id;
	char *passwd;
};

int admin_login(Admin &f_ad);                               //管理员登录
int check_admin_login_id(int *p_id);                        //检查管理员登录id
int check_admin_login_passwd(char *passwd);                 //检查管理员登录密码 

void show_admin_menu();                                     //显示管理员操作 
int input_new_passwd(char *passwd_1, char *passwd_2);       //输入新密码 
int check_new_passwd(char *passwd_1, char *passwd_2);       //检查新密码

string load_admin_passwd();                                 //加载管理员密码 
void save_admin_passwd(const string new_passwd);            //保存管理元更新的密码
#endif
