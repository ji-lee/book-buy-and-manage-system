#ifndef BOOK_MANAGE_H_
#define BOOK_MANAGE_H_

#include"book_class.h"

void show_book_manage_menu();                              //图书操作界面菜单显示
void book_top_table_show();

void add_book();                                           //添加图书
list<Book>::iterator judge_book_exist(char *b_name);       //判断图书是否已存在

int add_book_number(list<Book>::iterator i);               //增加图书数目  
int update_book_number(list<Book>::iterator i, int total); //更新图书数目

int add_new_book(char *b_name);                            //增加新的图书 
int set_book_author(char *author);                        //设置作者名   
int set_book_publisher(char *publisher);                  //设置出版社名
int set_book_price(float *p_price);                        //设置价格 
int set_book_number(int *p_total);                         //设置图书数目
int update_book_list(char *b_name, char *author,
		char *publisher, float price, int total);          //更新图书容器  

void show_books();                                         //显示图书
void find_book();                                          //查找图书
void show_find_book_menu();                                //查找图书界面菜单显示 
void find_by_book_name();                                  //根据书名查找
void find_by_author();                                     //根据作者查找

void delete_book();                                        //删除图书
void show_delete_book_menu();                              //删除图书界面菜单显示 
void delete_by_book_name();                                //根据书名删除
void delete_by_author();                                   //根据作者删除  

#endif


