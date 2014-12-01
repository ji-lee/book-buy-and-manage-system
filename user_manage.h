#ifndef __USER_MANAGE_H_
#define __USER_MANAGE_H_

#include"user_class.h"
#include"transaction_class.h"

#define TRANSACTION_FOUND      1
#define TRANSACTION_NOT_FOUND  0
#define INPUT_ERROR           -1

void show_user_manage_menu();                                    //显示会员管理菜单
void add_user();                                                 //增加会员
extern int set_user_id();                                        //外部设置会员id函数  
extern int set_user_name(char *name);                            //外部设置会员名词函数 
int set_user_level(char *level);                                 //设置会员级别 
extern int set_user_telephone(char *telephone);                  //外部设置会员电话函数
extern int set_user_address(char *address);                      //外部设置会员地址函数
extern void update_user_list(int id, char *name, char *passwd,   //外部更新新增会员到容器函数
		char *level, char *telephone, char *address);

void show_user();                                                //显示会员信息 
void user_show_menu();                                           //显示会员信息界面菜单

void user_top_table_show();                                      //会员信息显示时表头显示
void show_by_id();                                               //根据id显示会员信息  

void show_by_level();                                            //根据级别显示会员信息
void show_normal_user(list<User>::iterator i);                   //显示普通会员信息
void show_vip_user(list<User>::iterator i);                      //显示vip会员信息 

void show_transaction();                                         //显示交易记录
void show_transaction_menu();                                    //显示交易记录界面菜单  
void transaction_top_table_show();                               //显示交易记录时表头显示

void show_all_transaction();                                     //显示所有交易记录
void show_one_transaction();                                     //显示某个会员交易记录
int find_transaction();                                          //查找某个会员交易记录   

void reset_user_passwd();                                        //重置会员密码
int find_user(list<User>::iterator &i);                          //从容器中查找会员  

#endif
