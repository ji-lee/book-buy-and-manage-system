#include"book_manage.h"
#include"admin_class.h"

extern list<Book> list_book;

/*********************************************
*函数介绍：管理员类成员函数
*函数功能：对图书进行管理操作
*函数参数：无
*函数返回值：无
**********************************************/
void Admin::book_manage()
{
	while(1)
	{
		show_book_manage_menu();

		char select = tolower( getchar() );
		while(select != '\n' && getchar() != '\n' );
		
		switch(select)
		{
			case '1':
				add_book();	
				press_any_one();
				break;
			case '2':
				show_books();
				press_any_one();
				break;
			case '3':
				find_book();
				press_any_one();
				break;
			case '4':
				delete_book();
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
*函数介绍：添加图书函数
*函数功能：添加图书
*函数参数：无
*函数返回值：无
**********************************************/
void add_book()
{
	system("clear");

	char b_name[40] = "0";

	list<Book>::iterator i = judge_book_exist(b_name);
	if(i != list_book.end())
	{
		if(FAILE == add_book_number(i))
		{
			return;
		}
	}
	else
	{
		if(FAILE == add_new_book(b_name))
		{
			return;
		}
	}

}

/*********************************************
*函数介绍：显示图书函数
*函数功能：显示图书
*函数参数：无
*函数返回值：无
**********************************************/
void show_books()
{
	system("clear");

	list<Book>::iterator i = list_book.begin();
	
	book_top_table_show();
	
	while(i != list_book.end())
	{
		i->display();
		i++;
	}
}

/*********************************************
*函数介绍：查找图书函数
*函数功能：查找图书
*函数参数：无
*函数返回值：无
**********************************************/
void find_book()
{
	show_find_book_menu();

	int select = 0;
	cin>>select;
	cin.get();

	switch(select)
	{
		case 1:
			find_by_book_name();
			break;
		case 2:
			find_by_author();
			break;
		default:
			input_error();
			return;
	}
}

/*********************************************
*函数介绍：删除图书函数
*函数功能：删除图书
*函数参数：无
*函数返回值：无
**********************************************/
void delete_book()
{
	show_delete_book_menu();

	int select = 0;
	cin>>select;
	cin.get();

	switch(select)
	{
		case 1:
			delete_by_book_name();
			break;
		case 2:
			delete_by_author();
			break;
		default:
			input_error();
			return;
	}
}

/*********************************************
*函数介绍：判断图书是否存在函数
*函数功能：判断图书是否存在
*函数参数：书名
*函数返回值：迭代器类型
**********************************************/
list<Book>::iterator judge_book_exist(char *b_name)
{
	list<Book>::iterator i = list_book.begin();

	while(1)
	{
		cout<<"请输新增图书的书名(不大于40个字符)：";
		mygets(b_name, 40);
		if(strlen(b_name) == 0)
		{
			system("clear");
			cout<<"书名输入为空,请重新输入.\n"<<endl;
			continue;
		}
		else
		{
			break;
		}
	}

	while(i != list_book.end())
	{
		if(strcmp(b_name, i->get_b_name()) == 0)
		{
			break;
		}
		i++;
	}

	return i;
}

/*********************************************
*函数介绍：增加图书数目函数
*函数功能：增加图书数目，更新图书容器
*函数参数：图书容器迭代器
*函数返回值：FAILE或SUCCESS
**********************************************/
int add_book_number(list<Book>::iterator i)
{
	system("clear");

	int total = -1;
	int *p_total = &total;

	if(FAILE == set_book_number(p_total))
	{
		return FAILE;
	}
	
	return update_book_number(i, total);
}

/*********************************************
*函数介绍：添加新的图书函数
*函数功能：添加新的图书
*函数参数：书名
*函数返回值：FAILE或SUCCESS
**********************************************/
int add_new_book(char *b_name)
{
	int total = -1;
	float price = -1;
	char author[20] = "0";
	char publisher[20] = "0";

	float *p_price = &price;
	int *p_total = &total;

	if(FAILE == set_book_author(author))
	{
		return FAILE;
	}
	
	if(FAILE == set_book_publisher(publisher))
	{
		return FAILE;
	}

	if(FAILE == set_book_price(p_price))
	{
		return FAILE;
	}
	
	if(FAILE == set_book_number(p_total))
	{
		return FAILE;
	}

	return update_book_list(b_name, author, publisher, price, total);
}
	
/*********************************************
*函数介绍：设置图书作者函数
*函数功能：设置图书作者
*函数参数：作者名
*函数返回值：FAILE或SUCCESS
**********************************************/
int set_book_author(char *author)
{
	cout<<"请输入图书作者姓名：";
	mygets(author, 20);

	if(strlen(author) == 0)
	{
		system("clear");
		cout<<"作者姓名输入为空."<<endl;
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数介绍：设置出版社函数
*函数功能：设置图书出版社
*函数参数：出版社名称
*函数返回值：FAILE或SUCCESS
**********************************************/
int set_book_publisher(char *publisher)
{
	cout<<"请输入出版社名称：";
	mygets(publisher, 20);

	if(strlen(publisher) == 0)
	{
		system("clear");
		cout<<"出版社名称输入为空."<<endl;
		
		return FAILE;
	}
	return SUCCESS;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
int set_book_number(int *p_total)
{
	cout<<"请输入新增图书数目:";
	scanf("%d", p_total);
	while(getchar() != '\n');
	
	if(*p_total < 0)
	{
		system("clear");
		cout<<"图书数量输入错误，图书增加失败."<<endl;
		return FAILE;
	}

	return SUCCESS;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
int set_book_price(float *p_price)
{
	cout<<"请输入图书价格：";
	scanf("%f", p_price);
	while(getchar() != '\n');

	if(*p_price < 0)
	{
		system("clear");
		cout<<"价格输入错误，新增图书失败."<<endl;
		return FAILE;
	}

	return SUCCESS;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
int update_book_list(char *b_name, char *author, 
		char *publisher, float price, int total)
{
	Book book(b_name, author, publisher, price, total);
	list_book.push_back(book);
	
	system("clear");
	cout<<"新增图书添加完成."<<endl;
	
	return SUCCESS;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
int update_book_number(list<Book>::iterator i, int total)
{
	int old_total = i->get_total();
	i->set_total(total + old_total);

	system("clear");
	cout<<"图书增加完成."<<endl;
	
	return SUCCESS;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void find_by_book_name()
{
	system("clear");

	char find_name[40];
	list<Book>::iterator i = list_book.begin();

	cout<<"请输入要查找的图书书名：";
	mygets(find_name, 40);
	
	while(i != list_book.end())
	{
		if(strcmp(find_name, i->get_b_name()) == 0)
		{
			break;
		}
		i++;
	}

	if(i != list_book.end())
	{
		system("clear");
		
		book_top_table_show();
	
		i->display();
	}
	
	else
	{
		system("clear");
		cout<<"没有查找的图书."<<endl;
	}
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void find_by_author()
{
	system("clear");

	int count = 0;
	char find_author[20];
	list<Book>::iterator i = list_book.begin();

	cout<<"请输入要查找的作者名：";
	mygets(find_author, 20);
	
	system("clear");

	book_top_table_show();
	
	while(i != list_book.end())
	{
		if(strcmp(find_author, i->get_author()) == 0)
		{
			count++;
			i->display();
		}
		i++;
	}
	if(!count)
	{
		system("clear");
		cout<<"没有作者为"<<find_author<<"的图书"<<endl;
	}
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void delete_by_book_name()
{
	system("clear");

	char delete_name[40];
	list<Book>::iterator i = list_book.begin();
	
	cout<<"请输入要删除的图书书名：";
	mygets(delete_name, 40);

	while(i != list_book.end())
	{
		if(strcmp(delete_name, i->get_b_name()) == 0)
		{
			break;
		}
		i++;
	}

	if(i != list_book.end())
	{
		list_book.erase(i);
		system("clear");
		cout<<"图书"<<delete_name<<"删除成功."<<endl;
	}
	
	else
	{
		system("clear");
		cout<<"没有要删除的图书."<<endl;
	}
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void delete_by_author()
{
	system("clear");

	char delete_author[40];
	int count = 0;
	list<Book>::iterator i = list_book.begin();
	
	cout<<"请输入要删除的作者名字：";
	mygets(delete_author, 40);

	while(i != list_book.end())
	{
		if(strcmp(delete_author, i->get_author()) == 0)
		{
			count++;
			list_book.erase(i);
			i = list_book.begin();
			goto pass;
		}
		i++;
		
		pass:
			continue;
	}

	if(!count)
	{
		system("clear");
		cout<<"没有作者为"<<delete_author<<"的图书需要删除."<<endl;
	}
	else
	{
		system("clear");
		cout<<"作者为"<<delete_author<<"的图书删除成功."<<endl;
	}
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void book_top_table_show()
{
	cout<<setw(15)<<"书名"
		<<setw(20)<<"作者"
		<<setw(17)<<"出版社"
		<<setw(10)<<"价格"
		<<setw(9)<<"数量"<<endl<<endl;
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void show_delete_book_menu()
{
	system("clear");
    cout<<
		  "\n\t删除方式："
		  "\n\n\t1) --- 根据书名删除"
		  "\n\n\t2) --- 根据作者删除"
		  "\n\n\t请输入选择：";
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void show_find_book_menu()
{
	system("clear");
    cout<<
		  "\n\t查找方式："
		  "\n\n\t1) --- 根据书名查找"
		  "\n\n\t2) --- 根据作者查找"
		  "\n\n\t请输入选择：";
}

/*********************************************
*函数介绍：
*函数功能：
*函数参数：
*函数返回值：
**********************************************/
void show_book_manage_menu()
{
	system("clear");
    cout<<"\n\t欢迎进入图书管理界面"
		  "\n\n\t1) --- 增加图书"
		  "\n\n\t2) --- 显示图书"
		  "\n\n\t3) --- 查找图书"
		  "\n\n\t4) --- 删除图书"
		  "\n\n\tq) --- 返回上一层"
		  "\n\n\t请输入选择：";
}

