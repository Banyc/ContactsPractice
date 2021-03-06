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

		
void ReadFile();
void AppendContactDoc();
	void AddFunc(char *name, char *num1, char *num2, char *num3, int ID = - 1);
	void Insert(char *name, char *num1, char *num2, char *num3);
void CountContactsDoc();
void PrintContactFromNode(struct contacts *p);
int DeleteConsole();
	void DeleteByID();
	void DeleteAll(struct contacts **deleting_head, struct contacts **deleting_tail);
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
void Inverse();
void Test();
//===============================Main!!!
int main()
{
	ReadFile();
	while (true)
	{
		printf("\n Which section do you prefer? \n add: 1 | search: 2 | modify: 3 | delete: 4 | statistics: 5 | save: 6 | inverse: 7\n");
		printf(" Statement: This app is made by 丘升迈\n");
		printf(" Your choice: ");
		int chosenInt = -1;
		scanf(" %d", &chosenInt);
		switch (chosenInt)
		{
		case -1:  // 如果输入的是非数字，就经过这步吸收一个字符
			getchar();
			break;
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
			switch (DeleteConsole())
			{
			case 1:
				DeleteByID();
				break;
			case 2: 
				printf("\n 不支持\n");
				break;
			case 3:
				DeleteAll(&head, &tail);
				break;
			}
			break;
		case 5:
			CountContactsDoc();
			break;
		case 6:
			safeFunc();
			break;
		case 7:
			Inverse();
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
	int chosenInt;
	printf(" Insert to the first: 1 | append to the end: 2 \n");
	printf(" Your choice: ");
	scanf("%d", &chosenInt);
	if (chosenInt == 1 || chosenInt == 2)
	{
		char name[80];
		char num1[80];
		char num2[80];
		char num3[80];

		printf("\n Input (name, num1, num2, num3): \n");
		scanf("%s%s%s%s", name, num1, num2, num3);
		if (chosenInt == 1)
		{
			Insert(name, num1, num2, num3);
		}
		else if (chosenInt == 2)
		{
			AddFunc(name, num1, num2, num3);
		}
	}
}

void AddFunc(char *name, char *num1, char *num2, char *num3, int ID)
{
	//struct contacts *head, *tail, *p;
	struct contacts *p;
	
	bool DoesExist = false;

	

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
		//p = NULL; 这玩意直接把类型从 head的contacts结构变成什么都不是
		int size = sizeof(struct contacts);
		p = (struct contacts *)malloc(size);

		if (ID == -1)//如果ID没有被 特别指定
		{
			if (tail != NULL)
			{
				p->ID = tail->ID + 1;
			}
			else
			{
				p->ID = 0;
			}
		}
		else
		{
			p->ID = ID;
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
// 把输入的链表作为表头
void Insert(char *name, char *num1, char *num2, char *num3)
{
	struct contacts *p, *head_temp;
	p = (struct contacts *)malloc(sizeof(struct contacts));
	p->name[0] = '\0';
	strcpy(p->name, name);
	p->num1[0] = '\0';
	strcpy(p->num1, num1);
	p->num2[0] = '\0';
	strcpy(p->num2, num2);
	p->num3[0] = '\0';
	strcpy(p->num3, num3);
	p->next = NULL;

	if (head)
	{
		if (head->ID == 0)
		{
			p->ID = -2;
		}
		else
		{
			p->ID = head->ID - 1;
		}
		head_temp = head;
		head = p;
		p->next = head_temp;
	}
	else
	{
		p->ID = 0;
		head = p;
		tail = p;
	}
}
//------------------------------------删除类
//链表 删除 某个表 的 控制台
int DeleteConsole()
{
	int choiceInt;
	printf("\n Input 1:byID | 2:byName | 3:All \n");
	scanf("%d", &choiceInt);
	return choiceInt;
}
//根据 ID 搜索出表 然后 删除
void DeleteByID()
{
	int ID;
	struct contacts *pHead = NULL;
	struct contacts *pTail = NULL;
	printf("\n Input ID: ");
	scanf("%d", &ID);
	if (head != NULL)//看看 head 是不是 NULL
	{
		if (head->ID != ID)//看看head对不对的上 如果对不上
		{
			pHead = head;
			if (pHead->next != NULL)
			{
				while (pHead->next != NULL && pHead->next->ID != ID)//如果pHead的下一个不是所找目标 且 不是空
				{
					pHead = pHead->next;//迭代
				}
				if (pHead->next != NULL && pHead->next->ID == ID)//如果pHead下一个表是所选的
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
		printf("\n Contact is empty!\n");
	}
}
// 删除整条链表
// 输入：待删除链表的表头
void DeleteAll(struct contacts **deleting_head, struct contacts **deleting_tail)
{
	struct contacts *p_next;
	while (*deleting_head)
	{
		p_next = (*deleting_head)->next;
		free(*deleting_head);
		*deleting_head = p_next;
	}
	*deleting_head = *deleting_tail = NULL;
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
		while (p) //每次都要失败一次才能成功 好像现在不是啦
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
			{
				printf("\n fputs ERROR!\n");
				break;
			}
			//fputs("12315", fp); //没问题
			//fprintf(fp, "%s", PrintFileLikeStr(p)); //不要函数套函数
			//fprintf(fp, "%s", "12314"); //没问题
			p = p->next;
		}

		fclose(fp);
	}
}
// 格式化 每行的文本文件输出
// 输入：一个链表的地址，byRef 用作储存结果的 空字符数组
void PrintFileLikeStr(struct contacts *p, char *str)
{
	//char str[80] = "";
	//*str = '\0';
	sprintf(str, "%d %s %s %s %s\n", p->ID, p->name, p->num1, p->num2, p->num3);
	//*str = '1';
	//*(str + 1) = '\0';
	//return str;
}
//--------------------------------------读取文件类
void ReadFile()
{
	FILE *fp;
	int ID;
	char name[80];
	char num1[80];
	char num2[80];
	char num3[80];
	fp = fopen("contacts.txt", "a");//创建一个 txt 防止报错
	fclose(fp);
	fp = fopen("contacts.txt", "r");
	while (fscanf(fp, "%d", &ID) != EOF)//为什么这里的ID要初始化
	{
		fscanf(fp, "%s", name);
		fscanf(fp, "%s", num1);
		fscanf(fp, "%s", num2);
		fscanf(fp, "%s", num3);
		AddFunc(name, num1, num2, num3, ID);
	}
	fclose(fp);
}
//--------------------------------------链表逆置
void Inverse()
{
	struct contacts *p, *new_head, *new_tail;
	if (head)
	{
		int index;  // 重新理顺ID
		new_head = tail;
		new_head->ID = 0;  // 重新理顺ID
		index = 1;
		new_tail = new_head;
		while (new_tail != head)  // 逆置结束标志
		{
			p = head;
			while (p->next != new_tail)  // 遍历至 p 指向 new_tail 的未来 ->next
			{
				p = p->next;
			}
			new_tail->next = p;
			new_tail = p;
			new_tail->ID = index;  // 重新理顺ID
			index++;  // 重新理顺ID
		}
		//DeleteAll(&head, &tail);  // 不能删
		head = new_head;
		new_tail->next = NULL;
		tail = new_tail;
	}
}
