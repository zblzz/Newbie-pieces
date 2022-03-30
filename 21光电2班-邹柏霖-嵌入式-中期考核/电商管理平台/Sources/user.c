#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>


Status InitList_File(LinkedList* Head)//创建空链表放入文件中//头结点不放数据
{
	LNode* p;
	char buf[1024];				//缓冲区

	*Head = (LNode *)malloc(sizeof(LNode));		//给头结点分配内存
	if (*Head == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//头结点下一个结点置空
	p = *Head;					//用p指向头结点
			
	/*文件*/
	FILE* fp = fopen("user.txt", "r");		
	if (fp == NULL)
	{
		printf("用户文件不存在，已自动为您创建！\n");
		fp = fopen("user.txt", "w");
		if (fp == NULL)
		{
			printf("用户文件创建失败！\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//第一行为目录，读一行数据

	while (1)
	{
		LNode* q;
		q = (LNode*)malloc(sizeof(LNode));
		if (q == NULL)
		{
			printf("内存分配失败！\n");
			return OVERFLOW;
		}

		/*检测录入数据到文件流是否完成*/
		if (fscanf(fp, "%s%s%s%lf", q->name, q->password, q->phone,&q->money) != 4)	//成功后返回4，否则就录入到最后一个结点为空，退出
		{
			free(q);			//录入数据完毕后情空分配的内存
			break;
		}
		q->next = NULL;

		p->next = q;			//赋值给该结点
		p = q;					//点位到下个结点

	}

	printf("用户表初始化成功！\n");
	return SUCCESS;
}

Status RegisterUser(LinkedList* Head)//注册用户//头插法
{
	if (*Head == NULL)
	{
		printf("该用户表未初始化！\n");
		return ERROR;
	}
	LNode* p = *Head;		//指向头结点
	LNode* q;

	q = (LNode*)malloc(sizeof(LNode));
	if (q == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}

	/*输入数据*/
	printf("请输入昵称：\n");
	scanf("%s", q->name);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->name, q->name))
		{
			printf("用户名已存在，注册失败！\n");
			return ERROR;
		}
		
		p = p->next;
	}
	p = *Head;				//重新指向头结点
	printf("请输入密码：\n");
	scanf("%s", q->password);
	printf("请输入手机号：\n");
	scanf("%s", q->phone);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->phone, q->phone))
		{
			printf("手机号已注册过，注册失败！\n");
			return ERROR;
		}

		p = p->next;
	}
	p = *Head;				//重新指向头结点
	q->money = 0;			//新用户金额为0

	/*若表中无注册用户*/
	if (p->next == NULL)
	{
		p->next = q;
		p->next->next = NULL;		//最后一个结点置空
	}

	/*若表中有用户注册*/
	else
	{
		q->next = p->next;			//头插法
		p->next = q;
	}
	
	return SUCCESS;
}

Status RePassword(LinkedList* Head)//找回密码
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("无用户注册！\n");
		return ERROR;
	}

	char phoneID[20] = { 0 };
	LNode* p = (*Head)->next;

	printf("请输入要查找密码的用户的手机号：\n");
	scanf("%s", phoneID);

	/*遍历*/
	while (1)
	{
		while (p != NULL)
		{
			if (!(strcmp(phoneID, p->phone)))
			{
				printf("找到密码！\n");
				printf("该密码为：%s\n", p->password);
				printf("且昵称为：%s\n", p->name);
				return SUCCESS;

			}
			p = p->next;//指到下一个结点

		}
		printf("改手机号未注册！\n");
		break;
	}
	return SUCCESS;
}

LNode* Login(LinkedList* Head)//登录
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return NULL;
	}
	if ((*Head)->next == NULL)
	{
		printf("无用户注册\n");
		return NULL;
	}


	LNode* p;		//指向第一个结点
	p = (LNode*)malloc(sizeof(LNode));
	p = (*Head)->next;

    char names[20] = { 0 };
	char pass[20] = { 0 };

	/*输入数据*/
	printf("请输入你的昵称：\n");
	scanf("%s", names);
	printf("请输入你的密码：\n");
	scanf("%s", pass);

	while (p != NULL)
	{
		if ((strcmp(p->name, names) && strcmp(p->password, pass)) == 0)
		{
			printf("登陆成功！\n");
			return p;
		}

		p = p->next;
	}
	
	printf("用户不存在！");
	return NULL;
}

Status SaveData_UserEnd(LinkedList* Head)//保存数据并退出//判断是否出现重复数据
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("该用户表为空，无法存入数据！\n");
		return ERROR;
	}

	FILE* fp;
	fp = fopen("user.txt", "w+");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return OVERFLOW;
	}
	fprintf(fp, "昵称");
	fprintf(fp, "\t\t");
	fprintf(fp, "密码");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "手机号");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "余额");
	fprintf(fp, "\n");

	LNode* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, p->name);
		fprintf(fp, "\t\t");
		fprintf(fp, p->password);
		fprintf(fp, "\t\t\t");
		fprintf(fp, p->phone);
		fprintf(fp, "\t\t\t");
		fprintf(fp, "%.2lf",p->money);
		fprintf(fp, "\n");
	}

	printf("数据存入成功！\n");
	fclose(fp);
	return SUCCESS;
}

Status Charge(LinkedList U)//充值并查看余额
{
	int flag;
	int a;
	double money;

	printf("1.查看余额\n");
	printf("2.充值\n");
	printf("3.退出\n");
	printf("请输入功能编号：");
	while (1)
	{
		while (1)
		{
			a = scanf_s("%d", &flag);
			if (a != 0)
			{
				if (!(flag >= 1 && flag <= 3))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
			}
		}
		
		switch (flag)
		{
		case 1:
			/*查看余额*/
			printf("当前余额为%.2lf\n", U->money);
			goto end;
		case 2:
			/*充值*/
			printf("请输入您需要充值的金额：");
			while (1)
			{
				a = scanf_s("%lf", &money);
				if (a != 0)
				{
					if (money <= 0)
					{
						printf("请别乱输入，请重新输入！\n");
					}
					else break;
				}
				else
				{
					printf("输入非数字，请重新输入！\n");
					rewind(stdin);			//清理缓存区
				}
			}
			printf("充值成功！\n");
			U->money = U->money + money;
			printf("当前余额为：%.2lf\n", U->money);
			goto end;
		case 3:
			goto end;
		default:
			break;
		}
	}
end:
	return SUCCESS;
}

Status Search(ListGood* Head)//搜索商品
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return AERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("该商品表为空，无法查找商品！\n");
		return AERROR;
	}

	char name[20] = {0};
	Goods* p = (*Head)->next;			//指向第一个结点

	while (1)
	{
		printf("请输入商品的名字：\n");
		scanf("%s", name);

		/*遍历商品表*/
		while (p != NULL)
		{
			if (!strcmp(p->name,name))
			{
				printf("成功找到！\n");
				printf("该商品信息为:\n");
				printf("商品名：%s\t\t", (p->name));
				printf("价格：%.2lf\t\t", p->price);
				printf("库存：%d\n", p->amount);
				printf("信息：%s\n", (p->belong));

				return SUCCESS;
			}
			p = p->next;
		}
		printf("商品不存在\n");
		break;
	}
	
	return SUCCESS;
}

Status Purchase(LinkedList U, ListGood* Head, MLinkedList M)//购买商品
{
	/*判断余额*/
	if (!(U->money > 0))
	{
		printf("对不起，您的余额不足！\n");
		return AERROR;
	}

	if (M == NULL)
	{
		printf("无商家注册，无法交易！\n");
		return AERROR;
	}
	if (*Head == NULL)
	{
		printf("商品表为空！无法购买！\n");
		return AERROR;
	}
	printf("当前余额为：%.2lf\n", U->money);

	int flag,a;
	char name[20] = { 0 };
	Goods* p = (*Head)->next;			//商品指向第一个结点
	MLNode* g = M->next;				//商家指向第一个结点

	/*选择商品*/
	while (1)
	{
		printf("请输入商品的名字：\n");
		scanf("%s", name);

		/*遍历商品表*/
		while (p != NULL)
		{
			if (!strcmp(p->name, name))
			{
				printf("成功找到！\n");
				printf("该商品信息为:\n");
				printf("商品名：%s\t\t", (p->name));
				printf("价格：%.2lf\t\t", p->price);
				printf("库存：%d\n", p->amount);
				printf("所属商家：%s\n", (p->belong));

				break;
			}
			p = p->next;
		}

		if (p != NULL)//找到商品
		{
			break;
		}
		else//商品不存在
		{
			printf("商品不存在!\n");
			return AERROR;
		}
	}
	//此时p指向选择的商品

	/*找到所属商家*/
	while (M != NULL)
	{
		if (!strcmp(p->belong, M->name))
		{
			break;
		}
		M = M->next;//指向下个结点
		if ( M == NULL)
		{
			printf("错误！\n");
			return AERROR;
		}
	}

	//此时p指向选择的商品
	//此时M指向商品的所属商家

	/*购买商品*/
	printf("是否选择购买?(1:yes/ 2:no)\n");
	while (1)
	{
		a = scanf_s("%d", &flag);
		if (a != 0)
		{
			if (!(flag >= 1 && flag <= 2))
			{
				printf("请别乱输入，请重新输入！\n");
			}
			else break;
		}
		else
		{
			printf("输入非数字，请重新输入！\n");
			rewind(stdin);			//清理缓存区
		}
	}
	if (flag == 1)
	{
		if (U->money >= p->price)
		{
			printf("购买成功！\n");
			p->amount-- ;					   //库存减一
			U->money = (U->money) - (p->price);//用户余额减少
			M->money = M->money + (p->price);  //商家余额增加
			M->orders++;					   //订单数加一
			printf("当前余额为：%.2lf\n", U->money);
			printf("欢迎下次光临！\n");
			return SUCCESS;
		}
		else
		{
			printf("当前余额不足，购买失败！\n");
			return SUCCESS;
		}
	}
	else
	{
		printf("欢迎下次光临！\n");
		return SUCCESS;
	}
}

