#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;
/*flagI��ǵ�ǰ��¼�˻���flagN��ǵ�ǰת�˵��˻�*/
int flagI, flagN;
int userID = 0;
int UserNumber = 0;

struct User  		//�����������λ�ò�Ҫ��
{
    char name[50];  //�˺�
    double  money;  //���
    int flag;     	//�˺��ܷ�����ʹ�ã�  1��ʾ�� 2��ʾ���� 3��ʾ��ʧ
    int d;        	//�˻�����
    char key[50];  	//����
} user[10000];

void Save()  		//�����û���Ϣ
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
    else printf("\n\t\t\t\t\t\t�û���Ϣ����ʧ��");
}
void TiQu() 		//��ȡ�û���Ϣ
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
    else printf("\n\t\t\t\t\t\t�û���Ϣ����ʧ��");

    UserNumber--;    //

}

void drawmoney()	//����1��ȡ��ҵ��
{
    int a, i;
    char c;
    while (1)
    {
        printf("\n\t\t\t\t\t\t����������ȡ����(����)��");
        scanf("%d", &a);
        if (a > user[userID].money)
            printf("\n\t\t\t\t\t\t�˻����㣬���������룡\n");
        else if (a < 0 || a % 100 != 0)
            printf("\n\t\t\t\t\t\t�����������������룡\n");
        else
            break;
    }
    getchar();
    user[userID].money -= a;
    printf("\n\t\t\t\t\t\tȡ��ɹ�,���պ����ĳ�Ʊ��\n");
    printf("\n\t\t\t\t\t\t�Ƿ��ӡƾ���� �� y/n ��  ");
    scanf("%c", &c);
    getchar();
    if (c == 'Y' || c == 'y')
    {
        printf("\n\t\t\t\t\t\t���ڴ�ӡ���Ժ󡣡�������\n\t\t");
        printf("\n\t\t\t\t\t");
        for (i = 0; i < 10; i++)
        {
            printf("��");
            Sleep(200);
        }
        printf("\n");

        Save();

        printf("\n\t\t\t\t\t\t��ӡ��ɣ����պ�����ƾ��\n");
        printf("\n\t\t\t\t\t\t�밴Enter���˳�\n");
        getchar();
    }
    else
    {
        printf("\n\t\t\t\t\t\t�밴Enter���˳�\n");
        getchar();
    }
}
void savemoney()	//����2�����ҵ��
{
    int a, i;
    char c;
    while (1)
    {
        printf("\n\t\t\t\t\t\t���������Ĵ����(����)��");
        scanf("%d", &a);
        if (a < 0 || a % 100 != 0)
            printf("\n\t\t\t\t\t\t�����������������룡\n");
        else
            break;
    }
    getchar();
    user[userID].money += a;
    printf("\n\t\t\t\t\t\t���ɹ�\n");
    printf("\n\t\t\t\t\t\t�Ƿ��ӡƾ���� �� y/n ��  ");
    scanf("%c", &c);
    getchar();
    if (c == 'Y' || c == 'y')
    {
        printf("\n\t\t\t\t\t\t���ڴ�ӡ���Ժ��������\n\t\t\t\t");
        //printf("\n\t\t\t\t\t\t\t         ");
        for (i = 0; i < 10; i++)
        {
            printf("��");
            Sleep(200);
        }
        printf("\n");

        Save();

        printf("\n\t\t\t\t\t\t��ӡ��ɣ����պ�����ƾ��\n");
        printf("\n\t\t\t\t\t\t�밴Enter���˳�\n");
        getchar();
    }
    else
    {
        printf("\n\t\t\t\t\t\t�밴Enter���˳�\n");
        getchar();
    }
}
void showmoney()	//����3����ѯ���
{
    printf("\n\t\t\t\t\t\t�û���  ��%s\n", user[userID].name);
    printf("\n\t\t\t\t\t\t�˻���%.2lf\n", user[userID].money);
    printf("\n\t\t\t\t\t\t�밴Enter������\n");
    getchar();
}

char* get_password()//�Ǻ������ȡ������
{
    int i = 0;
    char a[50];
    char ch = '\0';
    while (ch != '\r')
    {
        ch = _getch();//�޻��ԵĴӼ��̽���һ���ַ���
        if (ch == 8)  //8���˸���� ASSIC�롣
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
            printf("*");//����Ǻ�
        }
    }
    a[i] = '\0';
    printf("\n");
    return &a[0];
}

void updatekey()	//����4�������޸�ҵ��
{
    char ch[10];
    char str[10];
    int i;
    printf("\n\t\t\t\t\t\t���������ĳ�ʼ����   ��");
    strcpy(ch, get_password());
    while (1)
    {
        if (strcmp(ch, user[userID].key) != 0)
        {
            printf("\n\t\t\t\t\t\t���ĳ�ʼ��������������������룺");
            strcpy(ch, get_password());
        }
        else
            break;
    }
    while (1)
    {
        printf("\n\t\t\t\t\t\t��������Ҫ�޸ĵ�����  ��");
        strcpy(ch, get_password());
        printf("\n\t\t\t\t\t\t���ٴ�����Ҫ�޸ĵ����룺");
        strcpy(str, get_password());
        if (strcmp(ch, str) == 0)
        {
            strcpy(user[userID].key, ch);
            printf("\n\t\t\t\t\t\t����Ϊ���޸ģ����Ժ�\n\t");
            printf("\n\t\t\t\t\t\t");
            for (i = 0; i < 10; i++)
            {
                printf("��");
                Sleep(200);
            }
  			printf("\n");
            Save();

            printf("\n\t\t\t\t\t\t�����޸ĳɹ�\n");
            printf("\n\t\t\t\t\t\t�밴�س����˳�\n");
            getchar();
            break;
        }
        else
            printf("\n\t\t\t\t\t\t�������������벻һ�£����������룡\n");
    }
}

void transfer() 	// ����5�� ת��
{

    char a[50];
    while (1)
    {

        printf("\n\t\t\t\t\t\t������ת�����˻���");
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
            printf("\n\t\t\t\t\t\t�տ���δ�ڴ����л򲻴��ڣ�ת��ʧ��\n");
            while (1)
            {

                printf("\n\t\t\t\t\t\t [1]���������˺�\n\n\t\t\t\t\t\t[2]�˳�\n\n\t\t\t\t\t\t��������:");
                int b=0;
                scanf("%d", &b);
                if (b == 2)
                    return;
                else if (b == 1)
                    break;
                else
                    printf("\n\t\t\t\t\t\t��Ŵ���\n");
            }
        }
        else 
        {
            printf("������ת�˽�");
            double s=0;
            int x = 0;
            while (1)
            {
                if (x){
                    printf("\n\t\t\t\t\t\t���㣬�Ƿ���������ת�˽�y/n��");
                    char ff[5];
                    scanf("%s",ff);
                    if(ff[0]=='n' || ff[0]=='N')
                        return ;
                    else printf("\n\t\t\t\t\t\t��������ת�˽��\n");
                }

                x = 0;
                scanf("%lf", &s);
                if (user[userID].money - 2.50 < s)
                    x = 1;
                if (!x)
                {
                    printf("\n\t\t\t\t\t\tת�˽��Ϊ��%.2f\n\n\t\t\t\t\t\t�Ƿ�ȷ��ת�ˡ�y/n��", s);
                    char f[5];
                    scanf("%s", f);
                    if (f[0] == 'n' || f[0] == 'N')
                        return;
                    user[flag].money += s;
                    user[userID].money -= s;
                    Save();
                    printf("\n\t\t\t\t\t\tת�˳ɹ�\n");
                    Sleep(800);
                    return;
                }
            }
        }
    }
}

void exitsystem()	//����6���˳�ϵͳ
{
    system("cls");
    Save();
    printf("\n");
    printf("\n\t\t\t\t\t\t�밴Enter���˳�\n");
    getchar();
}

int login()         //��½������
{

    char a[50];
    char b[50];
    int count = 0, i, flag = 0;
    while (1)
    {
    	printf("\n");
    	printf("\t\t\t\t\t-------------------------------\n");
        printf("\t\t\t\t\t�����롾����Ա�˺š����û��˻�����");
        scanf("%s", a);
        printf("\n");
        printf("\t\t\t\t\t���������룺");
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
        	printf("\t\t\t\t\t�û���������������������������룡\n");
		}
            
        else if(user[userID].flag==3){
            printf("���û��Ѿ���ʧ�������µ�¼��\n");
            system("pause");
            return 1;
        }
        else if(user[userID].flag==2){
            printf("���û��Ѿ����ᣬ�����µ�¼��\n");
            system("pause");
            return 1;
        }
        else
        {
        	printf("\n");
            printf("\t\t\t\t\t���ڵ�½  ���Ժ�\n");
            printf("\n");
            printf("\t\t\t\t\t");
            for (i = 0; i < 8; i++)
            {
                printf("��");
                Sleep(100);   //��ϵͳ�ڴ˴�ͣ��100����֮�������С�
            }
            printf("\n");
            break;
        }
        count++;
        if (count == 3)
        {
        	printf("\n");
            printf("\t\t\t\t\t����������ѳ�������,ϵͳ���˳���\n");
            flag = 1;
            break;
        }
    }
    return flag;
}

void Main_Menu()//���˵���
{
    printf("\n");
    printf("\t\t############################################�û�#######################################\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t                           ��������Ҫʵ�ֵĹ���ѡ��:\n");
	printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[1] ȡ��\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[2] ���\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[3] ��ѯ���\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[4] �޸�����\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[5] ת��\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[6] �˳�ϵͳ\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t############################################�û�#######################################\n");
    printf("\n");
}
void Admin_Menu()
{
    printf("\n");
    printf("\t\t############################################����Ա######################################\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t                           ��������Ҫʵ�ֵĹ���ѡ��:\n");
	printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[1] �鿴�û���Ϣ\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[2] ��ʧ�˻�\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[3] �����ʧ\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[4] ����\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[5] �޸��û�����\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t\t\t\t\t[6] �˳�ϵͳ\n");
    printf("\t\t#						   				       #\n"); 
    printf("\t\t############################################����Ա######################################\n");
    printf("\n");
            
}

void Select_Message()  //��ѯ�û���Ϣ
{
    while (1)
    {

        printf("\n\t\t\t\t\t\t������Ҫ���ҵ��û����˻���");
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
            printf("\n\t\t\t\t\t\t�û������ڣ��Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t����Ա�˻�����Ȩ�鿴\n\t\t\t\t\t\t�Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------��ѯ�ɹ�-----------------\n");
            printf("\n\t\t\t\t\t\t�˺ţ�%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t��%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else
				 printf("\n\t\t\t\t\t\t�˻�״̬����ʧ \n");
            printf("\n\t\t\t\t\t\t����������ز˵�\n");
            getchar();
            getchar();
            return;
        }

    }
}

void Lost_Card() // ��ʧ
{
    while (1)
    {
        printf("\n\t\t\t\t\t\t������Ҫ��ʧ���û����˻���");
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
            printf("\n\t\t\t\t\t\t�û������ڣ��Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t����Ա�˻�����Ȩ�鿴\n\t\t\t\t\t\t�Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------��ѯ�ɹ�-----------------\n");
            printf("\n\t\t\t\t\t\t�˺ţ�%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t��%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else
				 printf("\n\t\t\t\t\t\t�˻�״̬����ʧ \n");
            printf("\n\t\t\t\t\t\t�Ƿ��ʧ��y/n��");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
            else
            {
                user[flag].flag = 3;
                Save();
            }
            printf("\n\t\t\t\t\t\t---------------��ʧ�ɹ�-----------------\n");
            printf("\n\t\t\t\t\t\t����������ز˵�\n");
            getchar();
            getchar();
            return;
        }
    }
}

void UN_Lost_Card() // ���ʧ
{
    while (1)
    {
        printf("\n\t\t\t\t\t\t������Ҫ�����ʧ���û����˻���");
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
            printf("\n\t\t\t\t\t\t�û������ڣ��Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t����Ա�˻�����Ȩ�鿴\n\t\t\t\t\t\t�Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------��ѯ�ɹ�-----------------\n");
            printf("\n\t\t\t\t\t\t�˺ţ�%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t��%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else
				 printf("\n\t\t\t\t\t\t�˻�״̬����ʧ \n");
            printf("\n\t\t\t\t\t\t�Ƿ�����ʧ��y/n��");

            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
            else
            {
                user[flag].flag = 1;
                Save();
            }
			printf("\n\t\t\t\t\t\t---------------�����ʧ�ɹ�-----------------\n");
            printf("\n\t\t\t\t\t\t����������ز˵�\n");
            getchar();
            getchar();
            return;
        }
    }
}


void Create_Card() // ����
{
    printf("\n\t\t\t\t\t\t---------------������..-----------------\n");
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
    printf("\n\t\t\t\t\t\t�����ɹ����˻�Ϊ��%s\n", user[id].name);
    while (1)
    {
        user[id].d = 2;
        user[id].flag = 1;
        user[id].money = 0.01;
        strcpy(user[id].key,"111111");
        char ss[50], cc[50];
        while (1)
        {
            printf("\n\t\t\t\t\t\t�������˻����룺");
            strcpy(ss, get_password());
            if (strlen(ss) != 6)
            {
                printf("\n\t\t\t\t\t\t�������6λ����������������\n");
                memset(ss, '\0', sizeof(char) * 50);
            }
            else
            {
                printf("\n\t\t\t\t\t\t���ٴ������˻����룺");
                strcpy(cc, get_password());
                if (strcmp(ss, cc) != 0)
                {
                    printf("\n\t\t\t\t\t\t�������벻һ��\n\n\t\t\t\t\t\t��������������\n");
                    memset(ss, 0, sizeof(ss));
                    memset(cc, 0, sizeof(cc));
                }
                else
                {
                    strcpy(user[id].key, ss);
                    UserNumber++;
                    Save();
                    printf("\n\t\t\t\t\t\t�������óɹ�\n\n\t\t\t\t\t\t�����ɹ�\n\n\t\t\t\t\t\t�����������\n");
                    getchar();
                    return;
                }
            }
        }
    }
}

void Modify_Key() // �޸��û�����
{
    while (1)
    {
        printf("\n\t\t\t\t\t\t������Ҫ�޸�������û����˻���");
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
            printf("\n\t\t\t\t\t\t�û������ڣ��Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else if (user[flag].d == 1)
        {
            printf("\n\t\t\t\t\t\t����Ա�˻�����Ȩ�鿴\n\t\t\t\t\t\t�Ƿ����²��ҡ�y/n�� \n");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
        }
        else
        {

            printf("\n\t\t\t\t\t\t---------------��ѯ�ɹ�-----------------\n");
            printf("\n\t\t\t\t\t\t�˺ţ�%s\n", user[flag].name);
            printf("\n\t\t\t\t\t\t��%.2f\n", user[flag].money);
            if(user[flag].flag == 1)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else if(user[flag].flag == 2)
            	printf("\n\t\t\t\t\t\t�˻�״̬������ \n");
            else
				 printf("\n\t\t\t\t\t\t�˻�״̬����ʧ \n");
            printf("\n\t\t\t\t\t\t�Ƿ��޸����롾y/n��");
            char f[5];
            scanf("%s", f);
            if (f[0] == 'n' || f[0] == 'N')
                return;
            else
            {
                char ss[50],cc[50];
                while (1)
                {
                    printf("\n\t\t\t\t\t\t�������˻������룺");
                    strcpy(ss, get_password());
                    if (strlen(ss) != 6)
                    {
                        printf("\n\t\t\t\t\t\t�������6λ������������������\n");
                        memset(ss, '\0', sizeof(char) * 50);
                    }
                    else
                    {
                        printf("\n\t\t\t\t\t\t���ٴ������˻������룺");
                        strcpy(cc, get_password());
                        if (strcmp(ss, cc) != 0)
                        {
                            printf("\n\t\t\t\t\t\t�������벻һ�£��������ʧ��\n\n\t\t\t\t\t\t��������������\n");
                            memset(ss,0,sizeof(ss));
                            memset(cc,0,sizeof(cc));
                        }
                        else
                        {
                            strcpy(user[flag].key,ss);
                            Save();
                            printf("\n\t\t\t\t\t\t�����޸ĳɹ�,�����������\n");
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
  	fp=fopen("user.txt","r"); 	//��ֻ���ķ�ʽ�����ļ� 
	 if(feof(fp) == 0){			//����ļ�Ϊ�գ���д��Ĭ�Ϲ���Ա�˺ż����� 
  		init();
	  }	
  	srand((int)time(0));

    TiQu();//�����û���Ϣ

    system("color f");

    while(1)
    {
        system("cls");
        for (int i = 1; i <= UserNumber; i++)
        {
            printf("-%s-%s-%.2f-%d-%d-\n", user[i].name, user[i].key, user[i].money, user[i].flag, user[i].d);
        }
            int f;
            system("cls"); //����
            printf("\n");
            printf("\t\t\t\t        *******************************\n");
            printf("\t\t\t\t        *******************************\n");
            printf("\n");
            printf("\t\t\t\t        *     ��ӭʹ�� ATM ��̨��     *\n");
            printf("\n");
            printf("\t\t\t\t        *******************************\n");
            printf("\t\t\t\t        *******************************\n");
            f = login();
            system("cls");
            if (f == 1)
            {
                printf("\n\t\t\t\t\t\t�����˳�ϵͳ.........");
                Sleep(3000);
                exitsystem();
            }
            else
            {
                if (user[userID].d == 2)
                {

                    while (1)
                    {
                        Main_Menu(); //�˵�
                        printf("\n\t\t\t\t\t\t�����빦�ܡ�ѡ���");
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
                        Admin_Menu(); //�˵�
                        printf("\n\t\t\t\t\t\t�����빦�ܡ�ѡ���");
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



