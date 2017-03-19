#include"user.h"
int login(int sfd,puser new_user)
{
	char username[30]={0};
	char salt[100]={0};
	char passwd[150]={0};
	char code[150]={0};
	int ret;
	recv_msg(sfd,username);
	ret=getByName(username,salt,passwd);
	struct spwd* sp;
	if(-1==ret)
	{
		send_msg(sfd,"wrong");
		return -1;
	}else{
		send_msg(sfd,salt);
		recv_msg(sfd,code);
		if(strcmp(code,passwd))
		{
			send_msg(sfd,"wrong");
			return -1;
		}else{
			send_msg(sfd,"right");
			strcpy(new_user->username,username);
			sprintf(new_user->root_dir,"/home/%s",username);
			strcpy(new_user->cur_dir,"/");
			return 0;
		}
	}
}
void getSalt(char*salt,char*pass)
{
	int i,j;
	for(i=0,j=0;pass[i]&&j!=3;i++)
	{
		if(pass[i]=='$')
		{
			j++;
		}
	}
	strncpy(salt,pass,i-1);
}
