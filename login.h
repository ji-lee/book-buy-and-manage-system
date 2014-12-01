#ifndef __LOGIN_H_
#define __LOGIN_H_

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<ctype.h>
#include<cstring>
#include<unistd.h>
#include<mysql/mysql.h>
#include<iomanip>
#include<list>
#include<ctype.h>  

#define ADMIN_ID         1
#define SUCCESS          1
#define FAILE            0

using namespace std;


void login();                                             //登录
void show_menu();                                         //显示登录界面菜单
void admin();                                             //管理员操作 
void user();                                              //会员操作

//会员注册
void user_regist();                                       //注册会员
int set_user_id();                                        //分配会员id
int set_user_name(char *name);                            //设置名称
int set_user_passwd(char *passwd_1, char *passwd_2);      //设置密码
int set_user_telephone(char *telephone);                  //设置电话
int set_user_address(char *address);                      //设置地址  
void update_user_list(int id, char *name, char *passwd,  
		char *level, char *telephone, char *address);     //更新用户容器

void press_any_one();                                     //确认控制
void input_error();                                       //输入错误显示
void mygets(char buf[], int len);                         //输入字符串

extern void load_from_mysql();                            //装载数据到容器
extern void save_to_mysql();                              //保存数据到数据库

#endif
