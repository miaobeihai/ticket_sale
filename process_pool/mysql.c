#include"mysql.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int getByName(char*name,char*salt,char*passwd)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char* server="localhost";
	char* user="root";
	char* password="china86";
	char* database="zhangqiang";
	char query[100]={0};
	sprintf(query,"select salt,passwd from ftpuser where name='%s'",name);
	int t,r;
	conn=mysql_init(NULL);
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Error connecting to database:%s\n",mysql_error(conn));
		return -1;
	}else{
//		printf("Connected...\n");
	}
	t=mysql_query(conn,query);
	if(t)
	{
		printf("Error making query:%s\n",mysql_error(conn));
		return -1;
	}else{
		res=mysql_use_result(conn);
	//	printf("i am here\n");
		if(res)
		{
			row=mysql_fetch_row(res);
			if(row<=0)
			{
				return -1;
			}
			if(row[0]&&row[1])
			{
				strcpy(salt,row[0]);
				strcpy(passwd,row[1]);
				return 0;
			}else{
				return -1;
			}
		}else{
			return -1;
		}
		mysql_free_result(res);
	}
	mysql_close(conn);
	return 0;
}
