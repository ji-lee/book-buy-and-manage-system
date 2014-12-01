#include"book_class.h"
#include"user_class.h"
#include"transaction_class.h"

list<User> list_user;
list<Book> list_book;
list<Transaction> list_t;


/*********************************************
*函数介绍：登录操作函数
*函数功能：管理员登录、会员登录、会员注册
*函数参数：无
*函数返回值：无
**********************************************/
void login()
{
	load_from_mysql();

	while(1)
	{
		char select = 0;
	
		show_menu();
	
		select = tolower(getchar());
		while(getchar() != '\n');

		switch(select)
		{
			case '1':
				admin();
				break;
			case '2':
				user();
				break;
			case '3':
				user_regist();
				press_any_one();
				break;
			case 'q':
				save_to_mysql();
				return;
			default:
				input_error();
				press_any_one();
		}
	}
}

/*********************************************
*函数介绍：会员注册函数
*函数功能：新会员注册
*函数参数：无
*函数返回值：无
**********************************************/
void user_regist()
{
	system("clear");

	int id;
	char name[20];
	char passwd_1[20];
	char passwd_2[20];
	char level[7] = "normal";
	char telephone[10];
	char address[20];
	
	id = set_user_id();

	if(FAILE == set_user_name(name))
	{
		return;
	}
	
	if(FAILE == set_user_passwd(passwd_1, passwd_2))
	{
		return;
	}

	if(FAILE == set_user_telephone(telephone))
	{
		return;
	}
	
	if(FAILE == set_user_address(address))
	{
		return;
	}
	
	update_user_list(id, name, passwd_1, level, telephone, address);
	
	system("clear");
	cout<<"注册成功.你的id为："<<id<<endl;
}

/*********************************************
*函数介绍：设置会员id
*函数功能：自动分配新会员id
*函数参数：无
*函数返回值：新的id
**********************************************/
int set_user_id()
{
	int id;

	list<User>::iterator i = list_user.end();
	--i;
	id = i->get_id();
	return ++id;
}

/*********************************************
*函数介绍：设置会员名称
*函数功能：设置新的会员名称
*函数参数：会员名称接收字符串
*函数返回值：FAILE或SUCCESS
**********************************************/
int set_user_name(char *name)
{
	cout<<"请输入会员名称(不大于20位)：";
	mygets(name, 20);
	if(strlen(name) == 0)
	{
		system("clear");
		cout<<"名称输入为空."<<endl;
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数介绍：设置会员密码
*函数功能：设置新会员密码
*函数参数：两次输入密码的字符串
*函数返回值：FAILE或SUCCESS
**********************************************/
int set_user_passwd(char *passwd_1, char*passwd_2)
{
	strcpy(passwd_1, getpass("请输入注册密码:"));
	
	if(strlen(passwd_1) == 0)
	{
		system("clear");
		cout<<"密码输入为空，注册会员失败."<<endl;
		return FAILE;
	}
	
	strcpy(passwd_2, getpass("请再次输入密码:"));
	
	if(strlen(passwd_2) == 0)
	{
		system("clear");
		cout<<"密码输入为空，注册会员失败."<<endl;
		return FAILE;
	}
	
	if(strcmp(passwd_1, passwd_2) != 0)
	{
		system("clear");
		cout<<"两次密码输入不一致，注册会员失败."<<endl;
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数功能：设置新会员电话
*函数参数：接收电话字符串
*函数返回值：FAILE或SUCCESS
**********************************************/
int set_user_telephone(char *telephone)
{
	cout<<"请输入电话(8位)：";
	mygets(telephone, 10);
	if(strlen(telephone) != 8)
	{
		system("clear");
		cout<<"电话输入错误."<<endl;
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数功能：设置会员地址
*函数参数：接收会员地址字符串
*函数返回值：FAILE或SUCCESS
**********************************************/
int set_user_address(char *address)
{  
	cout<<"请输入邮递地址(不大于20位)：";
	mygets(address, 20);

	if(strlen(address) == 0)
	{
		system("clear");
		cout<<"邮递地址输入为空."<<endl;
		return FAILE;
	}

	return SUCCESS;
}

/*********************************************
*函数功能：更新会员容器
*函数参数：会员类各个数据成员
*函数返回值：无
**********************************************/
void update_user_list(int id, char *name, char *passwd,
		char *level, char *telephone, char *address)
{
	User user(id, name, passwd, level, telephone, address);
	list_user.push_back(user);
}

/*********************************************
*函数功能：开始时界面操作显示
*函数参数：无
*函数返回值：无
**********************************************/
void show_menu()
{
	system("clear");
    cout<<"\n\t欢迎登录图书管理/购买系统"
		  "\n\n\t1) --- 管理员登录"
		  "\n\n\t2) --- 用户登录"
		  "\n\n\t3) --- 用户注册"
		  "\n\n\tq) --- 退出"
		  "\n\n\t请输入选择：";
}

/*********************************************
*函数功能：回车确认继续
*函数参数：无
*函数返回值：无
**********************************************/
void press_any_one()
{
	cout<<"\n\n按回车继续"<<endl;
	getchar();
}

/*********************************************
*函数功能：输入错误显示
*函数参数：无
*函数返回值：无
**********************************************/
void input_error()
{
	system("clear");
	cout<<"\n输入有误.\n";
}

/*********************************************
*函数功能：自己实现的字符串输入函数
*函数参数：字符串数组，长度
*函数返回值：无
**********************************************/
void mygets(char buf[], int len)
{
	int i = 0;

	for(i = 0; i < len-1; i++)  
	{
		buf[i] = getchar();

		if(buf[i] == '\n')
		{
			break;
		}
	}

	if(buf[i] != '\n')
	{
		while(getchar() != '\n');
	}

	buf[i] = '\0';
}

