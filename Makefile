FINAL:=main
OBJECT:=main.o login.o admin_class.o user_class.o mysql.o user_manage.o book_manage.o book_class.o transaction_class.o
OPTIONS:= -Wall -rdynamic -g -L /usr/lib/mysql/ -lmysqlclient

$(FINAL):$(OBJECT)
	g++ $^ -o $@ $(OPTIONS)

%.o:%.c
	g++ -c $< -o $@ $(OPTIONS)
		
clean:
	rm -rvf $(OBJECT) $(FINAL)
