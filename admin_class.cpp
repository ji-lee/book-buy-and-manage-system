#include"admin_class.h"

/*********************************************
*函数介绍：管理员操作函数
*函数功能：修改密码、图书操作、会员操作
*函数参数：无
*函数返回值：无
**********************************************/
void admin()
{
	Admin ad;
	Admin &f_ad = ad;

	if(FAILE == admin_login(f_ad))			
	{
		return;
	}
	
	while(1)
	{
		show_admin_menu();

		char select = tolower( getchar() );
		while(select != '\n' && getchar() != '\n' );
		
		switch(select)
		{
			case '1':
				ad.change_admin_passwd();
				break;
			case '2':
				ad.book_manage();
				break;
			case '3':
				ad.user_manage();
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
*函数介绍：管理员类构造函数
*函数功能：初始化类成员
*函数参数：管理员id和密码
*函数返回值：无
**********************************************/
Admin::Admin(int _id, char *_passwd)
{
	if(NULL == _passwd)
	{
		passwd = new char[1];
	}
	else
	{
		passwd = new char[strlen(_passwd) + 1];
	}

	id = _id;
}

/*********************************************
*函数介绍：管理员类析构函数
*函数功能：释放资源
*函数参数：无
*函数返回值：无
**********************************************/
Admin::~Admin()
{
	delete []passwd;
}

/*********************************************
*函数介绍：管理员类重置密码成员函数
*函数功能：重置管理员密码
*函数参数：新密码
*函数返回值：无
**********************************************/
void Admin::reset_passwd(char *new_passwd)
{
	delete []passwd;
	
	passwd = new char[strlen(new_passwd) + 1];
	strcpy(passwd, new_passwd);
}

/*********************************************
*函数介绍：管理员类设置id函数
*函数功能：设置管理员id
*函数参数：id
*函数返回值：无
**********************************************/
void Admin::set_id(int _id)
{
	id = _id;
}

/*********************************************
*函数介绍：管理员类更改密码函数
*函数功能：更改管理员密码
*函数参数：无
*函数返回值：无
**********************************************/
void Admin::change_admin_passwd()
{
	system("clear");

	char new_passwd_1[20];
	char new_passwd_2[20];

	if(FAILE == input_new_passwd(new_passwd_1, new_passwd_2))
	{
		return;
	}

	if(FAILE == check_new_passwd(new_passwd_1, new_passwd_2))
	{
		return;
	}

	reset_passwd(new_passwd_1);
}

/*********************************************
*函数介绍：输入新密码函数
*函数功能：更改密码时输入函数
*函数参数：两次输入的密码
*函数返回值：FAILE或SUCCESS
**********************************************/
int input_new_passwd(char *new_passwd_1, char *new_passwd_2)
{
	strcpy(new_passwd_1, getpass("请输入新密码："));
	if(strcmp(new_passwd_1, "") == 0)
	{
		system("clear");
		cout<<"密码不能为空."<<endl;
		press_any_one();
		return FAILE;
	}

	strcpy(new_passwd_2, getpass("请再次输入新密码："));
	if(strcmp(new_passwd_2, "") == 0)
	{
		system("clear");
		cout<<"密码不能为空."<<endl;
		press_any_one();
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数介绍：检查输入密码函数
*函数功能：检查两次输入的新密码是否一致
*函数参数：两次输入的密码
*函数返回值：FAILE或SUCCESS
**********************************************/
int check_new_passwd(char *new_passwd_1, char *new_passwd_2)
{
	if(strcmp(new_passwd_1, new_passwd_2) == 0)
	{
		const string new_passwd(new_passwd_1);

		save_admin_passwd(new_passwd);

		system("clear");
		cout<<"密码修改成功."<<endl;
		press_any_one();
	}
	else
	{
		system("clear");
		cout<<"两次密码输入不一致，密码修改失败."<<endl;
		press_any_one();
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数介绍：管理员登录
*函数功能：判断管理员登录是否正确
*函数参数：管理员类
*函数返回值：FAILE或SUCCESS
**********************************************/
int admin_login(Admin &admin)
{
	system("clear");
	
	int id;
	char passwd[20] = "0";
	int *p_id = &id;

	if(FAILE == check_admin_login_id(p_id))
	{
		return FAILE;
	}
	
	if(FAILE == check_admin_login_passwd(passwd))
	{
		return FAILE;
	}
	
	admin.set_id(id);
	admin.reset_passwd(passwd);

	return SUCCESS;
}

/*********************************************
*函数介绍：检查管理员登录id
*函数功能：判断输入id是否存在
*函数参数：id
*函数返回值：FAILE或SUCCESS
**********************************************/
int check_admin_login_id(int *p_id)
{
	cout<<"请输入管理员id(数字):";
	scanf("%d", p_id);
	while(getchar() != '\n');

	if(*p_id != ADMIN_ID)
	{
		system("clear");
		cout<<"该id不存在，请重新输入."<<endl;
		press_any_one();
		return FAILE;
	}

	return SUCCESS;	
}

/*********************************************
*函数介绍：检查管理员登录密码
*函数功能：判断管理员密码输入是否匹配
*函数参数：输入密码
*函数返回值：FAILE或SUCCESS
**********************************************/
int check_admin_login_passwd(char *passwd)
{
	int count = 2;
	const char *load_passwd;

	string s_passwd = load_admin_passwd();

	load_passwd = s_passwd.c_str();

	strcpy(passwd, getpass("请输入管理员密码："));
	
	while(strcmp(passwd, load_passwd) != 0 && count != 0)
	{
		system("clear");
		cout<<"密码输入不对，你还有"<<count<<"次输入机会："<<endl;
		strcpy(passwd, getpass(""));
		count--;
	}
	if((0 == count) && strcmp(passwd, load_passwd) != 0)
	{
		system("clear");
		cout<<"三次密码输入错误.登录不成功."<<endl;
		press_any_one();
		return FAILE;
	}

	return SUCCESS;	
}

/*********************************************
*函数介绍：保存管理员密码
*函数功能：保存密码到文件
*函数参数：需要保存的密码值
*函数返回值：无
**********************************************/
void save_admin_passwd(const string save_passwd)
{
	ofstream ofile("admin.dat", ios::out);
	if(!ofile.is_open())
	{
		cout<<"文件打开失败."<<endl;
		return;
	}
	char buf[20] = "0";

	strcpy(buf, save_passwd.c_str());  //相互转化！！
	
	ofile.write(buf, sizeof(buf));
	
	ofile.close();
}

/*********************************************
*函数介绍：装载管理员密码
*函数功能：把管理员密码保存到string字符串
*函数参数：无
*函数返回值：string字符串
**********************************************/
string load_admin_passwd()
{
	ifstream ifile("admin.dat", ios::in);
	if(!ifile.is_open())
	{
		ofstream ofile("admin.dat", ios::out);
		if(!ofile.is_open())
		{
			cout<<"文件打开失败"<<endl;
			return NULL;
		}
		ofile.write("admin", sizeof("admin"));
		ofile.close();

		ifstream ifile("admin.dat", ios::in);
		char buf[20];

		ifile.read(buf, sizeof(buf));
		string load_passwd(buf);
		ifile.close();

		return load_passwd;
	}
	else
	{
		char buf[20];

		ifile.read(buf, sizeof(buf));
		string load_passwd(buf);
		ifile.close();
		
		return load_passwd;
	}
}

/*********************************************
*函数介绍：管理员操作界面
*函数功能：界面显示
*函数参数：无
*函数返回值：无
**********************************************/
void show_admin_menu()
{
	system("clear");
    cout<<"\n\t欢迎进入管理员操作界面"
		  "\n\n\t1) --- 更改管理员密码"
		  "\n\n\t2) --- 图书管理"
		  "\n\n\t3) --- 会员管理"
		  "\n\n\tq) --- 返回上一层"
		  "\n\n\t请输入选择：";
}
