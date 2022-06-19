#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;
/*flagI标记当前登录账户，flagN标记当前转账的账户*/
int flagI, flagN;
int userID = 0;
int UserNumber = 0;

struct User  		//这里面变量的位置不要动
{
    char name[50];  //账号
    double  money;  //金额
    int flag;     	//账号能否正常使用，  1表示能 2表示冻结 3表示挂失
    int d;        	//账户类型
    char key[50];  	//密码
} user[10000];

void Save()  		//更新用户信息
{
    FILE* fp;
    if ((fp = fopen("user.txt", "w")) != NULL)
    {
        for(int i=1; i<=UserNumber; i++)
        {
            fwrite(&user[i], sizeof(struct User), 1, fp);
        }
        fclose(fp);
    }
    else printf("\n\t\t\t\t\t\t用户信息更新失败");
}
void TiQu() 		//提取用户信息
{
    UserNumber = 0;
    FILE* fp;
    if ((fp = fopen("user.txt", "r")) != NULL)
    {
        while (!feof(fp))
        {
            fread(&user[++UserNumber], sizeof(struct User), 1, fp);
        }
        fclose(fp);
    }
    else printf("\n\t\t\t\t\t\t用户信息加载失败");

    UserNumber--;    //

}

void drawmoney()	//功能1：取款业务
{
    int a, i;
    char c;
    while (1)
    {
        printf("\n\t\t\t\t\t\t请输入您的取款金额(整百)：");
        scanf("%d", &a);
        if (a > user[userID].money)
            printf("\n\t\t\t\t\t\t账户余额不足，请重新输入！\n");
        else if (a < 0 || a % 100 != 0)
            printf("\n\t\t\t\t\t\t输入有误，请重新输入！\n");
        else
            break;
    }
    getchar();
    user[userID].money -= a;
    printf("\n\t\t\t\t\t\t取款成功,请收好您的钞票！\n");
    printf("\n\t\t\t\t\t\t是否打印凭条？ 【 y/n 】  ");
    scanf("%c", &c);
    getchar();
    if (c == 'Y' || c == 'y')
    {
        printf("\n\t\t\t\t\t\t正在打印请稍后。。。。。\n\t\t");
        printf("\n\t\t\t\t\t");
        for (i = 0; i < 10; i++)
        {
            printf("■");
            Sleep(200);
        }
        printf("\n");

        Save();

        printf("\n\t\t\t\t\t\t打印完成，请收好您的凭条\n");
        printf("\n\t\t\t\t\t\t请按Enter键退出\n");
        getchar();
    }
    else
    {
        printf("\n\t\t\t\t\t\t请按Enter键退出\n");
        getchar();
    }
}
void savemoney()	//功能2：存款业务
{
    int a, i;
    char c;
    while (1)
    {
        printf("\n\t\t\t\t\t\t请输入您的存款金额(整百)：");
        scanf("%d", &a);
        if (a < 0 || a % 100 != 0)
            printf("\n\t\t\t\t\t\t输入有误，请重新输入！\n");
        else
            break;
    }
    getchar();
    user[userID].money += a;
    printf("\n\t\t\t\t\t\t存款成功\n");
    printf("\n\t\t\t\t\t\t是否打印凭条？ 【 y/n 】  ");
    scanf("%c", &c);
    getchar();
    if (c == 'Y' || c == 'y')
    {
        printf("\n\t\t\t\t\t\t正在打印请稍侯。。。。。\n\t\t\t\t");
        //printf("\n\t\t\t\t\t\t\t         ");
        for (i = 0; i < 10; i++)
        {
            printf("■");
            Sleep(200);
        }
        printf("\n");

        Save();

        printf("\n\t\t\t\t\t\t打印完成，请收好您的凭条\n");
        printf("\n\t\t\t\t\t\t请按Enter键退出\n");
        getchar();
    }
    else
    {
        printf("\n\t\t\t\t\t\t请按Enter键退出\n");
        getchar();
    }
}
void showmoney()	//功能3：查询余额
{
    printf("\n\t\t\t\t\t\t用户名  ：%s\n", user[userID].name);
    printf("\n\t\t\t\t\t\t账户余额：%.2lf\n", user[userID].money);
    printf("\n\t\t\t\t\t\t请按Enter键返回\n");
    getchar();
}

char* get_password()//星号密码获取函数；
{
    int i = 0;
    char a[50];
    char ch = '\0';
    while (ch != '\r')
    {
        ch = _getch();//无回显的从键盘接收一个字符，
        if (ch == 8)  //8是退格符的 ASSIC码。
        {
            a[--i] = '\0';
            putchar(8);
            putchar(' ');
            putchar(8);
        }
        else
        {
            if (ch == '\r')
                break;
            a[i++] = ch;
            printf("*");//输出星号
        }
    }
    a[i] = '\0';
    printf("\n");
    return &a[0];
}

void updatekey()	//功能4：密码修改业务
{
    char ch[10];
    char str[10];
    int i;
    printf("\n\t\t\t\t\t\t请输入您的初始密码   ：");
    strcpy(ch, get_password());
    while (1)
    {
        if (strcmp(ch, user[userID].key) != 0)
        {
            printf("\n\t\t\t\t\t\t您的初始密码输入错误请重新输入：");
            strcpy(ch, get_password());
        }
        else
            break;
    }
    while (1)
    {
        printf("\n\t\t\t\t\t\t请输入您要修改的密码  ：");
        strcpy(ch, get_password());
        printf("\n\t\t\t\t\t\t请再次输入要修改的密码：");
        strcpy(str, get_password());
        if (strcmp(ch, str) == 0)
        {
            strcpy(user[userID].key, ch);
            printf("\n\t\t\t\t\t\t正在为您修改，请稍候\n\t");
            printf("\n\t\t\t\t\t\t");
            for (i = 0; i < 10; i++)
            {
                printf("■");
                Sleep(200);
            }
  			printf("\n");
            Save();

            printf("\n\t\t\t\t\t\t密码修改成功\n");
            printf("\n\t\t\t\t\t\t请按回车键退出\n");
            getchar();
            break;
        }
        else
            printf("\n\t\t\t\t\t\t您两次密码输入不一致，请重新输入！\n");
    }
}

void transfer() 	// 功能5： 转账
{

    char a[50];
    while (1)
    {

        printf("\n\t\t\t\t\t\t请输入转账人账户：");
        scanf("%s", a);
        int flag = 0;
        for (int i = 1; i <= UserNumber; i++)
        {

            if (strcmp(a, user[i].name) == 0)
            {
                flag = i;
                break;
            }
        }

        if (flag == 0)
        {
            printf("\n\t\t\t\t\t\t收款人未在此银行或不存在，转账失败\n");
            while (1)
            {

                printf("\n\t\t\t\t\t\t [1]重新输入账号\n\n\t\t\t\t\t\t[2]退出\n\n\t\t\t\t\t\t请输入编号:");
                int b=0;
                scanf("%d", &b);
                if (b == 2)
                    return;
                else if (b == 1)
                    break;
                else
                    printf("\n\t\t\t\t\t\t编号错误\n");
            }
        }
        else 
        {
            printf("请输入转账金额：");
            double s=0;
            int x = 0;
            while (1)
            {
                if (x){
                    printf("\n\t\t\t\t\t\t余额不足，是否重新输入转账金额【y/n】");
                    char ff[5];
                    scanf("%s",ff);
                    if(ff[0]=='n' || ff[0]=='N')
                        return ;
                    else printf("\n\t\t\t\t\t\t重新输入转账金额\n");
                }

                x = 0;
                scanf("%lf", &s);
                if (user[userID].money - 2.50 < s)
                    x = 1;
                if (!x)
                {
                    printf("\n\t\t\t\t\t\t转账金额为：%.2f\n\n\t\t\t\t\t\t是否确认转账【y/n】", s);
                    char f[5];
                    scanf("%s", f);
                    if (f[0] == 'n' || f[0] == 'N')
                        return;
                    user[flag].money += s;
                    user[userID].money -= s;
                    Save();
                    printf("\n\t\t\t\t\t\t转账成功\n");
                    Sleep(800);
                    return;
                }
            }
        }
    }
}

void exitsystem()	//功能6：退出系统
{
    system("cls");
    Save();
    printf("\n");
    printf("\n\t\t\t\t\t\t请按Enter键退出\n");
    getchar();
}

int login()         //登陆函数；
{

    char a[50];
    char b[50];
    int count = 0, i, flag = 0;
    while (1)
    {
    	printf("\n");
    	printf("\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t请输入【管理员账号】或【用户账户】：");
        scanf("%s", a);
        printf("\n");
        printf("\t\t\t\t\t请输入密码：");
        strcpy(b, get_password());

        int fff = 0;
        for (int i = 1; i <= UserNumber; i++)
        {
            if (strcmp(a, user[i].name) == 0 && strcmp(b, user[i].key) == 0)
            {
                fff = 1;
                userID = i;
            }
        }


        if (!fff){
        	printf("\n");
        	printf("\t\t\t\t\t用户名或者密码输入错误！请重新输入！\n");
		}
            
        else if(user[userID].flag==3){
            printf("该用户已经挂失，请重新登录！\n");
            system("pause");
            return 1;
        }
        else if(user[userID].flag==2){
            printf("该用户已经冻结，请重新登录！\n");
            system("pause");
            return 1;
        }
        else
        {
        	printf("\n");
            printf("\t\t\t\t\t正在登陆  请稍后\n");
            printf("\n");
            printf("\t\t\t\t\t");
            for (i = 0; i < 8; i++)
            {
                printf("■");
                Sleep(100);   //让系统在此处停留100毫秒之后在运行。
            }
            printf("\n");
            break;
        }
        count++;
        if (count == 3)
        {
        	printf("\n");
            printf("\t\t\t\t\t您输入错误已超过三次,系统已退出！\n");
            flag = 1;
            break;
        }
    }
    return flag;
}

void Main_Menu()//主菜单；
{
    printf("\n");
    printf("\t\t############################################用户#######################################\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t                           请输入想要实现的功能选项:\n");
	printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[1] 取款\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[2] 存款\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[3] 查询余额\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[4] 修改密码\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[5] 转账\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[6] 退出系统\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t############################################用户#######################################\n");
    printf("\n");
}
void Admin_Menu()
{
    printf("\n");
    printf("\t\t############################################管理员######################################\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t                           请输入想要实现的功能选项:\n");
	printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[1] 查看用户信息\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[2] 挂失账户\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[3] 解除挂失\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[4] 开户\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[5] 修改用户密码\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[6] 退出系统\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t############################################管理员######################################\n");
    printf("\n");
            
}

void Select_Message()  //查询用户信息
{
    while (1)
    {

        printf("\n\t\t\t\t\t\t请输入要查找的用户的账户：");
        char s[50];
        scanf("%s", s);
        int flag = 0;
        for (int i = 1; i <= UserNumber; i++)
        {
            if (strcmp(s, user[i].name) == 0)
            {
                flag = i;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\t\t\t\t用户不存在，是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t管理员账户，无权查看\n\t\t\t\t\t\t是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------查询成功-----------------\n");
            printf("\n\t\t\t\t\t\t账号：%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t存款：%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t账户状态：正常 \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t账户状态：冻结 \n");
            else
				 printf("\n\t\t\t\t\t\t账户状态：挂失 \n");
            printf("\n\t\t\t\t\t\t按任意键返回菜单\n");
            getchar();
            getchar();
            return;
        }

    }
}

void Lost_Card() // 挂失
{
    while (1)
    {
        printf("\n\t\t\t\t\t\t请输入要挂失的用户的账户：");
        char s[50];
        scanf("%s", s);
        int flag = 0;
        for (int i = 1; i <= UserNumber; i++)
        {
            if (strcmp(s, user[i].name) == 0)
            {
                flag = i;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\t\t\t\t用户不存在，是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t管理员账户，无权查看\n\t\t\t\t\t\t是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------查询成功-----------------\n");
            printf("\n\t\t\t\t\t\t账号：%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t存款：%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t账户状态：正常 \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t账户状态：冻结 \n");
            else
				 printf("\n\t\t\t\t\t\t账户状态：挂失 \n");
            printf("\n\t\t\t\t\t\t是否挂失【y/n】");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
            else
            {
                user[flag].flag = 3;
                Save();
            }
            printf("\n\t\t\t\t\t\t---------------挂失成功-----------------\n");
            printf("\n\t\t\t\t\t\t按任意键返回菜单\n");
            getchar();
            getchar();
            return;
        }
    }
}

void UN_Lost_Card() // 解挂失
{
    while (1)
    {
        printf("\n\t\t\t\t\t\t请输入要解除挂失的用户的账户：");
        char s[50];
        scanf("%s", s);
        int flag = 0;
        for (int i = 1; i <= UserNumber; i++)
        {
            if (strcmp(s, user[i].name) == 0)
            {
                flag = i;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\t\t\t\t用户不存在，是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t管理员账户，无权查看\n\t\t\t\t\t\t是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------查询成功-----------------\n");
            printf("\n\t\t\t\t\t\t账号：%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t存款：%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t账户状态：正常 \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t账户状态：冻结 \n");
            else
				 printf("\n\t\t\t\t\t\t账户状态：挂失 \n");
            printf("\n\t\t\t\t\t\t是否解除挂失【y/n】");

            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
            else
            {
                user[flag].flag = 1;
                Save();
            }
			printf("\n\t\t\t\t\t\t---------------解除挂失成功-----------------\n");
            printf("\n\t\t\t\t\t\t按任意键返回菜单\n");
            getchar();
            getchar();
            return;
        }
    }
}


void Create_Card() // 开户
{
    printf("\n\t\t\t\t\t\t---------------开户中..-----------------\n");
    Sleep(1000);
    int id = UserNumber + 1;
    while (1)
    {

        for (int i=0;i<11; i++)
        {
            user[id].name[i] = rand()%9+1+'0';
        }
        user[id].name[11] = '\0';
        int flag = 0;
        for (int j=1;j<=UserNumber;j++)
        {
            if (strcmp(user[id].name, user[j].name) == 0)
            {
                flag = j;
                break;
            }
        }
        if (!flag)break;
    }
    printf("\n\t\t\t\t\t\t开户成功，账户为：%s\n", user[id].name);
    while (1)
    {
        user[id].d = 2;
        user[id].flag = 1;
        user[id].money = 0.01;
        strcpy(user[id].key,"111111");
        char ss[50], cc[50];
        while (1)
        {
            printf("\n\t\t\t\t\t\t请输入账户密码：");
            strcpy(ss, get_password());
            if (strlen(ss) != 6)
            {
                printf("\n\t\t\t\t\t\t密码必须6位，请重新输入密码\n");
                memset(ss, '\0', sizeof(char) * 50);
            }
            else
            {
                printf("\n\t\t\t\t\t\t请再次输入账户密码：");
                strcpy(cc, get_password());
                if (strcmp(ss, cc) != 0)
                {
                    printf("\n\t\t\t\t\t\t两次密码不一致\n\n\t\t\t\t\t\t请重新输入密码\n");
                    memset(ss, 0, sizeof(ss));
                    memset(cc, 0, sizeof(cc));
                }
                else
                {
                    strcpy(user[id].key, ss);
                    UserNumber++;
                    Save();
                    printf("\n\t\t\t\t\t\t密码设置成功\n\n\t\t\t\t\t\t开户成功\n\n\t\t\t\t\t\t按任意键返回\n");
                    getchar();
                    return;
                }
            }
        }
    }
}

void Modify_Key() // 修改用户密码
{
    while (1)
    {
        printf("\n\t\t\t\t\t\t请输入要修改密码的用户的账户：");
        char s[50];
        scanf("%s", s);
        int flag = 0;
        for (int i = 1; i <= UserNumber; i++)
        {
            if (strcmp(s, user[i].name) == 0)
            {
                flag = i;
                break;
            }
        }
        if (flag == 0)
        {
            printf("\n\t\t\t\t\t\t用户不存在，是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t管理员账户，无权查看\n\t\t\t\t\t\t是否重新查找【y/n】 \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------查询成功-----------------\n");
            printf("\n\t\t\t\t\t\t账号：%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t存款：%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t账户状态：正常 \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t账户状态：冻结 \n");
            else
				 printf("\n\t\t\t\t\t\t账户状态：挂失 \n");
            printf("\n\t\t\t\t\t\t是否修改密码【y/n】");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
            else
            {
                char ss[50],cc[50];
                while (1)
                {
                    printf("\n\t\t\t\t\t\t请输入账户新密码：");
                    strcpy(ss, get_password());
                    if (strlen(ss) != 6)
                    {
                        printf("\n\t\t\t\t\t\t密码必须6位，请重新输入新密码\n");
                        memset(ss, '\0', sizeof(char) * 50);
                    }
                    else
                    {
                        printf("\n\t\t\t\t\t\t请再次输入账户新密码：");
                        strcpy(cc, get_password());
                        if (strcmp(ss, cc) != 0)
                        {
                            printf("\n\t\t\t\t\t\t两次密码不一致，密码更改失败\n\n\t\t\t\t\t\t请重新输入密码\n");
                            memset(ss,0,sizeof(ss));
                            memset(cc,0,sizeof(cc));
                        }
                        else
                        {
                            strcpy(user[flag].key,ss);
                            Save();
                            printf("\n\t\t\t\t\t\t密码修改成功,按任意键返回\n");
                            getchar();
                            getchar();
                            return;
                        }
                    }
                }
            }
        }
    }
}

void init()
{

    UserNumber = 1;
    strcpy(user[1].name,"201914564");
    strcpy(user[1].key,"123456");
    user[1].money = 0.01;
    user[1].flag = 1;
    user[1].d = 1;
    Save();
    return;
}

int main()
{
	Save();
	FILE *fp;
  	fp=fopen("user.txt","r"); 	//已只读的方式进入文件 
	 if(feof(fp) == 0){			//如果文件为空，则写入默认管理员账号及密码 
  		init();
	  }	
  	srand((int)time(0));

    TiQu();//加载用户信息

    system("color f");

    while(1)
    {
        system("cls");
        for (int i = 1; i <= UserNumber; i++)
        {
            printf("-%s-%s-%.2f-%d-%d-\n", user[i].name, user[i].key, user[i].money, user[i].flag, user[i].d);
        }
            int f;
            system("cls"); //清屏
            printf("\n");
            printf("\t\t\t\t        *******************************\n");
            printf("\t\t\t\t        *******************************\n");
            printf("\n");
            printf("\t\t\t\t        *     欢迎使用 ATM 柜台机     *\n");
            printf("\n");
            printf("\t\t\t\t        *******************************\n");
            printf("\t\t\t\t        *******************************\n");
            f = login();
            system("cls");
            if (f == 1)
            {
                printf("\n\t\t\t\t\t\t正在退出系统.........");
                Sleep(3000);
                exitsystem();
            }
            else
            {
                if (user[userID].d == 2)
                {

                    while (1)
                    {
                        Main_Menu(); //菜单
                        printf("\n\t\t\t\t\t\t请输入功能【选项】：");
                        int m;
                        scanf("%d", &m);
                        getchar();
                        if (m == 1)
                        {
                            Sleep(500);
                            drawmoney();
                            system("cls");
                        }
                        else if (m == 2)
                        {
                            Sleep(500);
                            savemoney();
                            system("cls");
                        }
                        else if (m == 3)
                        {
                            Sleep(500);
                            showmoney();
                            system("cls");
                        }
                        else if (m == 4)
                        {
                            Sleep(500);
                            updatekey();
                            system("cls");
                        }
                        else if (m == 5)
                        {
                            Sleep(500);
                            transfer();
                            system("cls");
                        }
                        else if (m == 6)
                        {
                            exitsystem();
                            break;
                        }
                    }
                }
                else if (user[userID].d == 1)
                {
                    while (1)
                    {
                        Admin_Menu(); //菜单
                        printf("\n\t\t\t\t\t\t请输入功能【选项】：");
                        int m;
                        scanf("%d", &m);
                        getchar();
                        if (m == 1)
                        {
                            Sleep(500);
                            Select_Message();
                            system("cls");
                        }
                        else if (m == 2)
                        {
                            Sleep(500);
                            Lost_Card();
                            system("cls");
                        }
                        else if (m == 3)
                        {
                            Sleep(500);
                            UN_Lost_Card();
                            system("cls");
                        }
                        else if (m == 4)
                        {
                            Sleep(500);
                            Create_Card();
                            system("cls");
                        }
                        else if (m == 5)
                        {
                            Sleep(500);
                            Modify_Key();
                            system("cls");
                        }
                        else if (m == 6)
                        {
                            exitsystem();
                            break;
                        }
                    }
                }
            }
        Save();
    }
        return 0;
}



