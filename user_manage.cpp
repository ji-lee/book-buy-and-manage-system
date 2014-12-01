#include"admin_class.h"
#include"user_manage.h"

extern list<User> list_user;
extern list<Transaction> list_t;

/*********************************************
*函数功能：管理员会员操作成员函数
*函数参数：无
*函数返回值：无
**********************************************/
void Admin::user_manage()
{
	while(1)
	{
		show_user_manage_menu();

		char select = tolower( getchar() );
		while(select != '\n' && getchar() != '\n' );
		
		switch(select)
		{
			case '1':
				add_user();	
				press_any_one();
				break;
			case '2':
				show_user();
				press_any_one();
				break;
			case '3':
				show_transaction();
				press_any_one();
				break;
			case '4':
				reset_user_passwd();
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
*函数功能：添加会员
*函数参数：无
*函数返回值：无
**********************************************/
void add_user()
{
	system("clear");

	int id;
	char name[20];
	char passwd[20] = "123456";
	char level[7];
	char telephone[10];
	char address[20];
	
	id = set_user_id();

	if(FAILE == set_user_name(name))
	{
		return;
	}
	
	if(FAILE == set_user_level(level))
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
	
	update_user_list(id, name, passwd, level, telephone, address);
	
	system("clear");
	cout<<"新会员添加完成.id为："<<id<<"，初始化密码为："<<passwd<<"."<<endl;

}

/*********************************************
*函数功能：显示会员信息
*函数参数：无
*函数返回值：无
**********************************************/
void show_user()
{
	int select = 0;

	user_show_menu();
	
	cin>>select;
	cin.get();

	switch(select)
	{
		case 1:
			show_by_id();
			break;
		case 2:
			show_by_level();
			break;
		default:
			input_error();
			return;
	}
}

/*********************************************
*函数功能：根据id显示会员信息
*函数参数：无
*函数返回值：无
**********************************************/
void show_by_id()
{
	list<User>::iterator i = list_user.begin();

	user_top_table_show();

	while(i != list_user.end())
	{
		i->display();
		i++;
	}
}

/*********************************************
*函数功能：根据会员级别显示会员信息
*函数参数：无
*函数返回值：无
**********************************************/
void show_by_level()
{
	list<User>::iterator i = list_user.begin();

	user_top_table_show();

	show_normal_user(i);
	
	show_vip_user(i);
}

/*********************************************
*函数功能：显示会员交易记录
*函数参数：无
*函数返回值：无
**********************************************/
void show_transaction()
{
	int select = 0;

	show_transaction_menu();

	cin>>select;
	cin.get();

	switch(select)
	{
		case 1:
			show_all_transaction();
			break;
		case 2:
			show_one_transaction();
			break;
		default:
			input_error();
			return;
	}	
}

/*********************************************
*函数功能：显示所有会员交易记录
*函数参数：无
*函数返回值：无
**********************************************/
void show_all_transaction()
{
	int count = 0;

	list<Transaction>::iterator i = list_t.begin();
	
	transaction_top_table_show();
	
	while(i != list_t.end())
	{
		count++;
		i->display();
		i++;
	}
	if(!count)
	{
		system("clear");
		cout<<"会员购书记录为空."<<endl;
	}
}

/*********************************************
*函数功能：显示某个会员交易记录
*函数参数：无
*函数返回值：无
**********************************************/
void show_one_transaction()
{
	if(TRANSACTION_NOT_FOUND == find_transaction())
	{
		system("clear");
		cout<<"\n没有该会员购书记录."<<endl;
	}

}

/*********************************************
*函数功能：重置会员密码
*函数参数：无
*函数返回值：无
**********************************************/
void reset_user_passwd()
{
	int id;
	list<User>::iterator i = list_user.begin();
	list<User>::iterator &tmp = i;

	id = find_user(tmp);

	if(INPUT_ERROR == id || i == list_user.end())
	{
		system("clear");
		cout<<"没有id为"<<id<<"的会员.请检查id是否输入正确."<<endl;
	}
	else
	{
		i->set_passwd("123456");	
		system("clear");
		cout<<"id为"<<id<<"的会员密码已重置为123456."<<endl;
	}
}

/*********************************************
*函数功能：设置会员级别
*函数参数：会员级别指针
*函数返回值：FAILE或SUCCESS
**********************************************/
int set_user_level(char *level)
{
	cout<<"请输入会员级别('normal'or'vip')：";
	mygets(level, 7);

	if((strcmp(level, "normal") != 0) && (strcmp(level, "vip") != 0))
	{
		system("clear");
		cout<<"级别输入错误，添加会员失败."<<endl;
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数功能：显示普通会员信息
*函数参数：会员容器
*函数返回值：无
**********************************************/
void show_normal_user(list<User>::iterator i)
{
	cout<<"normal:"<<endl<<endl;
	while(i != list_user.end())
	{
		if(strcmp("normal", i->get_level()) == 0)
		{
			i->display();
		}
		i++;
	}
}

/*********************************************
*函数功能：显示vip会员信息
*函数参数：会员容器
*函数返回值：无
**********************************************/
void show_vip_user(list<User>::iterator i)
{
	cout<<endl<<"vip:"<<endl<<endl;

	while(i != list_user.end())
	{
		if(strcmp("vip", i->get_level()) == 0)
		{
			i->display();
		}
		i++;
	}
}

/*****************************************************
*函数功能：查找交易记录
*函数参数：无
*函数返回值：TRANSACTION_NOT_FOUND或TRANSACTION_FOUND
******************************************************/
int find_transaction()
{
	system("clear");

	int id = -1;
	int count = 0;
	list<Transaction>::iterator i = list_t.begin();

	cout<<"请输入要查询的会员id:";
	scanf("%d", &id);
	while(getchar() != '\n');

	if(id < 0)
	{
		return TRANSACTION_NOT_FOUND;
	}

	transaction_top_table_show();

	while(i != list_t.end())
	{
		if(id == i->get_u_id())
		{
			count++;
			i->display();
			cout<<endl;
		}
		i++;
	}

	if(!count)
	{
		return TRANSACTION_NOT_FOUND;
	}
	
	else
	{
		return TRANSACTION_FOUND;
	}
}

/*********************************************
*函数功能：查找会员
*函数参数：会员容器
*函数返回值：会员id
**********************************************/
int find_user(list<User>::iterator &i)
{
	system("clear");

	int id = -1;

	cout<<"请输入需要重置密码的会员id:";
	scanf("%d", &id);
	while(getchar() != '\n');

	if(id < 0)
	{
		return id;
	}

	while(i != list_user.end())
	{
		if(id == i->get_id())
		{
			break;
		}
		i++;
	}

	return id;
}

/*********************************************
*函数功能：交易记录表头显示
*函数参数：无
*函数返回值：无
**********************************************/
void transaction_top_table_show()
{
	system("clear");

	cout<<setw(5)<<"id"
		<<setw(15)<<"书名"
		<<setw(14)<<"折扣"
		<<setw(11)<<"邮费"
		<<setw(11)<<"总额"
		<<setw(19)<<"备注"<<endl<<endl;
}

/*********************************************
*函数功能：会员信息表头显示
*函数参数：无
*函数返回值：无
**********************************************/
void user_top_table_show()
{
	system("clear");

	cout<<setw(4)<<"id"
		<<setw(12)<<"名称"
		<<setw(12)<<"级别"
		<<setw(11)<<"电话"
		<<setw(12)<<"地址"<<endl<<endl;
}

/*********************************************
*函数功能：交易记录显示菜单
*函数参数：无
*函数返回值：无
**********************************************/
void show_transaction_menu()
{
	system("clear");
    cout<<
		  "\n\n\t显示方式："
		  "\n\n\t1) --- 显示所有会员购买记录"
		  "\n\n\t2) --- 显示某个会员购买记录"
		  "\n\n\t请输入选择：";
}

/*********************************************
*函数功能：会员显示菜单
*函数参数：无
*函数返回值：无
**********************************************/
void user_show_menu()
{
	system("clear");
    cout<<
		  "\n\n\t显示方式：\n"
		  "\n\t1) --- 按id顺序显示"
		  "\n\t2) --- 按级别顺序显示"
		  "\n\n\t请输入选择：";
}

/*********************************************
*函数功能：会员管理显示菜单
*函数参数：无
*函数返回值：无
**********************************************/
void show_user_manage_menu()
{
	system("clear");
    cout<<
		  "\n\t欢迎进入用户管理界面"
		  "\n\n\t1) --- 增加会员"
		  "\n\n\t2) --- 显示会员信息"
		  "\n\n\t3) --- 显示会员购书记录"
		  "\n\n\t4) --- 重置会员密码"
		  "\n\n\tq) --- 返回上一层"
		  "\n\n\t请输入选择：";
}

