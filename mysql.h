#ifndef __MYSQL_H_
#define __MYSQL_H_

#include"book_class.h"
#include"user_class.h"
#include"transaction_class.h"

void load_from_mysql();                                        //装载数据到容器
list<User> load_user_data(MYSQL *connect);                     //装载会员数据到容器 
list<Book> load_book_data(MYSQL *connect);                     //装载图书数据到容器
list<Transaction> load_transaction_data(MYSQL *connect);       //装载购书记录到容器

void save_to_mysql();                                          //保存数据到数据库
void save_user_to_mysql(MYSQL *connect);                       //保存会员数据到数据库
void save_book_to_mysql(MYSQL *connect);                       //保存图书数据到数据库
void save_transaction_to_mysql(MYSQL *connect);                //保存购书记录到数据库

#endif
