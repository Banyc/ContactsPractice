// 通讯录.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//---------------链表
struct contacts
{
	int ID;
	char name[80];
	char num1[80];
	char num2[80];
	char num3[80];
	struct contacts *next;
};
struct contacts *head, *tail;
//-------------------------------函数声明

		

void AppendContactDoc();
void CountContactsDoc();
void PrintContactFromNode(struct contacts *p);
int DeleteConsole();
	void DeleteByID();
int SearchConsole();
void SearchByIDConsole();
	struct contacts *SearchByID(int ID);
void SearchByNameConsole();
	bool SearchByName(char *str);
	bool DoesIncludeStr(char *sourceStr, char *matchStr);
int ModifyConsole();
	void ModifyByID();
void safeFunc();
	void PrintFileLikeStr(struct contacts *p, char *str);
void Test();
//===============================Main!!!
int main()
{
	while (true)
	{
		printf("\n Which section do you prefer? \n add: 1 | search: 2 | modify: 3 | delete: 4 | statistics: 5 | safe: 6\n");
		printf(" Your choice: ");
		int chosenInt;
		scanf(" %d", &chosenInt);
		switch (chosenInt)
		{
		case 1:
			AppendContactDoc();
			break;
		case 2:
			switch (SearchConsole())
			{
			case 1: SearchByIDConsole(); break;
			case 2: SearchByNameConsole(); break;
			}
			break;
		case 3:
			switch (ModifyConsole())
			{
			case 1: ModifyByID(); break;
			case 2: printf("\n 不支持\n"); break;
			}
			break;
		case 4:
			if (DeleteConsole() == 1)
			{
				DeleteByID();
			}
			else {
				printf("\n 不支持\n");
			}
			break;
		case 5:
			CountContactsDoc();
			break;
		case 6:
			safeFunc();
			break;
		case 99:
			Test(); break;
		}
	}
    return 0;
}
//===============================函数定义
//Test
void Test()
{
	struct contacts *p = NULL;
	printf("%d\n", p->ID);
}
//-----------------在链表尾 添加 结构实例-----添加类
void AppendContactDoc()
{
	char name[80];
	char num1[80];
	char num2[80];
	char num3[80];
	//struct contacts *head, *tail, *p;
	struct contacts *p;
	
	bool DoesExist = false;

	printf("\n Input balabala \n");
	scanf("%s%s%s%s", name, num1, num2, num3);

	p = head;
	while (p != NULL)
	{
		if (strcmp(p->name, name) == 0)//所要添加的表 的主键 是否已经存在
		{
			DoesExist = true;
			break;
		}
		p = p->next;
	}

	if (DoesExist)//如果 所要添加的表 的主键 已经存在
	{
		p->name[0] = '\0';
		strcpy(p->name, name);
		p->num1[0] = '\0';
		strcpy(p->num1, num1);
		p->num2[0] = '\0';
		strcpy(p->num2, num2);
		p->num3[0] = '\0';
		strcpy(p->num3, num3);
	}
	else//如果不存在
	{
		p = NULL;
		int size = sizeof(p);
		p = (struct contacts *)malloc(size);

		if (tail != NULL)
		{
			p->ID = tail->ID + 1;
		}
		else
		{
			p->ID = 0;
		}
		p->name[0] = '\0';
		strcpy(p->name, name);
		p->num1[0] = '\0';
		strcpy(p->num1, num1);
		p->num2[0] = '\0';
		strcpy(p->num2, num2);
		p->num3[0] = '\0';
		strcpy(p->num3, num3);

		p->next = NULL;
		if (head == NULL)
		{
			head = p;
		}
		else
		{
			tail->next = p;
		}
		tail = p;
	}
}
//------------------------------------删除类
//链表 删除 某个表 的 控制台
int DeleteConsole()
{
	int choiceInt;
	printf("\n Input 1:byID | 2:byName \n");
	scanf("%d", &choiceInt);
	return choiceInt;
}
//根据 ID 搜索出表 然后 删除
void DeleteByID()
{
	int ID;
	struct contacts *pHead = NULL;
	struct contacts *pTail = NULL;
	printf("\n Input \n ");
	scanf("%d", &ID);
	if (head != NULL)//看看 head 是不是 NULL
	{
		if (head->ID != ID)//看看head对不对的上 如果对不上
		{
			pHead = head;
			if (pHead->next != NULL)
			{
				while (pHead->next->ID != ID && pHead->next != NULL)//如果pHead的下一个不是所找目标 且 不是空
				{
					pHead = pHead->next;//迭代
				}
				if (pHead->next->ID == ID)//如果pHead下一个表是所选的
				{
					pTail = pHead->next->next;
					free(pHead->next);
					pHead->next = pTail;
				}
				else
				{
					printf(" Cannot find!\n");
				}
			}
		}
		else//如果一上来就是符合的
		{
			pTail = head->next;
			free(head);
			if (pTail != NULL)//如果有不止一个表
			{
				head = pTail;
			}
			else//如果整个链表只有一个表
			{
				head = tail = NULL;
			}//这个if 防止 tail 被释放
		}
	}
	else
	{
		printf("\n It doesn't exist!\n");
	}
}
//------------------------------------统计类
void CountContactsDoc()
{
	struct contacts *p = NULL;
	p = head;
	printf("\n");
	while (p != NULL)
	{
		printf("--------------------------------------------------------------------------------------\n");
		PrintContactFromNode(p);
		p = p->next;
	}
	printf("\n--------------------------------------------------------------------------------------\n\n");
}
//打印 某个结构实例
void PrintContactFromNode(struct contacts *p)
{
	printf(" |%d:\t", p->ID);
	printf("|%13s", p->name);
	printf("|%13s", p->num1);
	printf("|%13s", p->num2);
	printf("|%13s", p->num3);
	printf("|\n");
	printf("--------------------------------------------------------------------------------------\n");
}
//------------------------------------修改类
//修改 控制台
int ModifyConsole()
{
	int choiceInt;
	printf("\n Input 1:byID | 2:byName\n");
	scanf("%d", &choiceInt);
	return choiceInt;
}
//通过 ID 修改 控制台
void ModifyByID()
{
	int selectedNum, ID;
	struct contacts *p;
	char newNum[80];
	printf("\n Input ID\n");
	scanf("%d", &ID);
	p = SearchByID(ID);
	if (p != NULL)
	{
		PrintContactFromNode(p);
		printf("\n which number? (Input 1-3)\n ");
		scanf("%d", &selectedNum);
		
		printf("\n Input\n ");
		scanf("%s", newNum);
		switch (selectedNum)
		{
		case 1:
			p->num1[0] = '\0';
			strcpy(p->num1, newNum);
			break;
		case 2:
			p->num2[0] = '\0';
			strcpy(p->num2, newNum);
			break;
		case 3:
			p->num3[0] = '\0';
			strcpy(p->num3, newNum);
			break;
		}
	}
	else
	{
		printf("\n It doesn't exist!\n");
	}
}
//------------------------------------查找类
//查找 控制台
int SearchConsole()
{
	int choiceInt;
	printf("\n Input 1:byID | 2:byName\n");
	scanf("%d", &choiceInt);
	return choiceInt;
}
//查找 通过ID 控制台
void SearchByIDConsole()
{
	int ID;
	struct contacts *p;
	printf("\n Input ID\n");
	scanf("%d", &ID);
	p = SearchByID(ID);
	if (p != NULL)
	{
		PrintContactFromNode(p);
	}
	else
	{
		printf(" It doesn't exist!\n");
	}
}
//查找 ID 功能 
struct contacts *SearchByID(int ID)
{
	struct contacts *p;
	p = head;
	if (p != NULL)//防止越界
	{
		while (p->ID != ID)
		{
			p = p->next;
			if (p == NULL)//如果越界
				break;
		}
	}
	return p;
}
//查找 通过Name 控制台
void SearchByNameConsole()
{
	char str[80];
	struct contacts *p;
	printf("\n Input Name\n");
	scanf("%s", str);
	
	if (SearchByName(str) == false)
	{
		printf(" It doesn't exist!\n");
	}
}
//查找 Name 功能 并打印
bool SearchByName(char *str)
{
	bool flag = false;
	struct contacts *p;
	p = head;
	while (p != NULL)
	{
		if (DoesIncludeStr(p->name, str))
		{
			PrintContactFromNode(p);
			flag = true;
		}
		p = p->next;
	}
	return flag;
}
//---------------------------------------------是否包含某字符串
bool DoesIncludeStr(char *sourceStr, char *matchStr)
{
	int iSource = 0;
	int iMatch = 0;
	bool result = false;
	while (sourceStr[iSource] != '\0')
	{
		if (sourceStr[iSource] == matchStr[iMatch])
		{
			if (matchStr[iMatch + 1] == '\0')
			{
				result = true;
			}
			else
			{
				iMatch++;
			}
		}
		else
		{
			iMatch = 0;
		}
		iSource++;
	}
	return result;
}
//------------------------------------保存类
void safeConsole()
{

}
void safeFunc() 
{
	struct contacts *p;
	FILE *fp = NULL;
	fp = fopen("contacts.txt", "w");
	if (fp == NULL)
	{
		printf("\n fopen ERROR!\n");
	}
	else
	{
		p = head;
		while (p) //每次都要失败一次才能成功
		{
			char outPutStr[80 * 4 + 1];
			PrintFileLikeStr(p, outPutStr);

			/*int i = 0;
			while (outPutStr[i])
			{
				fputs(outPutStr[i], fp);
				i++;

			}*/

			if (fputs(outPutStr, fp) == EOF)
				printf("\n fputs ERROR!\n");
			break;
			//fputs("12315", fp); //没问题
			//fprintf(fp, "%s", PrintFileLikeStr(p)); //不要函数套函数
			//fprintf(fp, "%s", "12314"); //没问题
			p = p->next;
		}

		fclose(fp);
	}
}

void PrintFileLikeStr(struct contacts *p, char *str)
{
	//char str[80] = "";
	//*str = '\0';
	sprintf(str, "%d\t%s\t%s\t%s\t%s\n", p->ID, p->name, p->num1, p->num2, p->num3);
	//*str = '1';
	//*(str + 1) = '\0';
	//return str;
}