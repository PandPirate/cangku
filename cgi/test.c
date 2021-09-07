#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//str, 得到的字符串 dest 目标名  res  目标值 strsize 字符串长度
int findstr(char *str, char *dest, char *res, int strsize, int destsize)
{
	char *p = str;
	int num = 0, i = 0;
	char **arr = NULL;

	while(*p++)
	{
		if(*p=='&')
			num++;
	}
	num++;
	arr = malloc(num*sizeof(p));
	if(arr==NULL)
	{
		printf("malloc err\n");
		return -2;
	}
	puts(str);
	p = str;
	while(*p)
	{
		if(*p == '&')
		{
			arr[i] = str;
			puts(arr[i]);
			str = p+1;
			puts(str);
			i++;
		}
		p++;
	}
	printf("2222222222222222222222222222222222\n");
	arr[i] = str;

	for(i = 0; i < num; i++)
	{
		if(!strncmp(arr[i], dest, destsize));
		{
			p = arr[i];
			while(*p++!='=')
			{
				strcpy(res, p);
				free(arr);
				return 0;
			}
		}
	}

	free(arr);

	return -1;
}


int main(int argc, const char *argv[])
{
	char *buf = "username=aa&userpass=ss";
	char name[10] = "";
	char password[10] = "";

	

	findstr(buf, "username", name, sizeof(buf), sizeof("username"));
//	findstr(buf, "userpass", password, sizeof(buf), sizeof("userpass"));

	printf("Content-type:text/html\n\n");
	printf("%s\n%s\n", name, password);
//	printf("<script>location.href='../main1.html'</script>\n");
	return 0;
}
