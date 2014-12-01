#include"book_class.h"

/*********************************************
*函数介绍：图书类构造函数
*函数功能：初始化数据成员
*函数参数：书名、作者、出版社、价格、总数
*函数返回值：无
**********************************************/
Book::Book(char *_b_name, char *_author, char *_publisher, float _price, int _total)
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

	if(NULL == _author)
	{
		author = new char[1];
	}
	else
	{
		author = new char[strlen(_author) + 1];
		strcpy(author, _author);
	}
	
	if(NULL == _publisher)
	{
		publisher = new char[1];
	}
	else
	{
		publisher = new char[strlen(_publisher) + 1];
		strcpy(publisher, _publisher);
	}

	price = _price;
	total = _total;
}

/*********************************************
*函数介绍：图书类析构函数
*函数功能：释放资源
*函数参数：无
*函数返回值：无
**********************************************/
Book::~Book()
{
	delete b_name;
	delete author;
	delete publisher;
}

/*********************************************
*函数介绍：图书类拷贝构造函数
*函数功能：实现类的拷贝
*函数参数：图书类对象
*函数返回值：无
**********************************************/
Book::Book(const Book &b)
{
	b_name = new char[strlen(b.b_name) + 1];
	strcpy(b_name, b.b_name);
	author = new char[strlen(b.author) + 1];
	strcpy(author, b.author);
	publisher = new char[strlen(b.publisher) + 1];
	strcpy(publisher, b.publisher);
	price = b.price;
	total = b.total;
}

/*********************************************
*函数介绍：获取书名函数
*函数功能：获取书名
*函数参数：无
*函数返回值：字符串类型书名
**********************************************/
char* Book::get_b_name()
{
	return b_name;
}

/*********************************************
*函数介绍：获取作者函数
*函数功能：获取图书作者
*函数参数：无
*函数返回值：字符串类型作者名
**********************************************/
char* Book::get_author()
{
	return author;
}

/*********************************************
*函数介绍：获取出版社函数
*函数功能：获取出版社名称
*函数参数：无
*函数返回值：字符串类型出版社名称
**********************************************/
char* Book::get_publisher()
{
	return publisher;
}

/*********************************************
*函数介绍：获取图书总额函数
*函数功能：获取库存图书总额
*函数参数：无
*函数返回值：图书总额
**********************************************/
int Book::get_total()
{
	return total;
}

/*********************************************
*函数介绍：获取图书价格函数
*函数功能：获取图书价格
*函数参数：无
*函数返回值：价格
**********************************************/
float Book::get_price()
{
	return price;
}

/*********************************************
*函数介绍：设置图书总额函数
*函数功能：设置图书总额
*函数参数：新的图书总额
*函数返回值：无
**********************************************/
void Book::set_total(int _total)
{
	total = _total;
}

/*********************************************
*函数介绍：显示图书信息函数
*函数功能：显示库存图书相关信息
*函数参数：无
*函数返回值：无
**********************************************/
void Book::display()
{
	cout<<setw(15)<<b_name
		<<setw(20)<<author
		<<setw(10)<<publisher
		<<setw(7)<<price
		<<setw(7)<<total<<endl;
}

