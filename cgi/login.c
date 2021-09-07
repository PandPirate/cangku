#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "cgic.h"

int cgiMain(int argc, const char *argv[])
{
	char name[32] = "";
	char password[32] = "";
	sqlite3 *db = NULL;
	int res;
	char sql[256] = "";
	char *errmsg = NULL;
	char **pres = NULL;
	int row, col;

	cgiFormString("username", name, sizeof(name));
	cgiFormString("userpass", password, sizeof(password));

	// 创建数据库
	res = sqlite3_open("./user.db", &db);
	sprintf(sql, "create table if not exists user(username char primary key, userpass char)");
	sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	bzero(sql, sizeof(sql));
	sprintf(sql, "insert into user values('admin', '0000')");
	sqlite3_exec(db, sql, NULL, NULL, &errmsg);

	bzero(sql, sizeof(sql));
	sprintf(sql, "select *from user where username='%s'", name);
	sqlite3_get_table(db, sql, &pres, &row, &col, &errmsg);
	if (row)
	{
		if (strcmp(pres[3], password) == 0)
		{
			cgiHeaderContentType("text/html");
			fprintf(cgiOut, "<script>location.href='../main1.html'</script>\n");
			sqlite3_free_table(pres);
			sqlite3_close(db);
			return 0;
		}
	}

	cgiHeaderContentType("text/html");
	fprintf(cgiOut, "<html>username or userpassword error</html>");
	sqlite3_free_table(pres);
	sqlite3_close(db);
	return -1;
}
