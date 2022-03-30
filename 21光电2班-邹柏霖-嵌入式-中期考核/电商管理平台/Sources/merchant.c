#include "merchant.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>

Status InitMerList_File(MLinkedList* Head)//创建空链表放入文件中//头结点不放数据
{
	MLNode* p;
	char buf[1024];				//缓冲区

	*Head = (MLNode*)malloc(sizeof(MLNode));		//给头结点分配内存
	if (*Head == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//头结点下一个结点置空
	p = *Head;					//用p指向头结点

	/*文件*/
	FILE* fp = fopen("merchant.txt", "r");
	if (fp == NULL)
	{
		printf("商家文件不存在，已自动为您创建！\n");
		fp = fopen("merchant.txt", "w");
		if (fp == NULL)
		{
			printf("商家文件创建失败！\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//第一行为目录，读一行数据

	while (1)
	{
		MLNode* q;
		q = (MLNode*)malloc(sizeof(MLNode));
		if (q == NULL)
		{
			printf("内存分配失败！\n");
			return OVERFLOW;
		}

		/*检测录入数据到文件流是否完成*/
		if (fscanf(fp, "%s%s%s%lf%lf%d", q->name, q->password, q->phone, &q->income,&q->money, &q->orders) != 6)	//成功后返回6，否则就录入到最后一个结点为空，退出
		{
			free(q);			//录入数据完毕后情空分配的内存
			break;
		}
		q->next = NULL;

		p->next = q;			//赋值给该结点
		p = q;					//点位到下个结点

	}

	printf("商家表初始化成功！\n");
	return SUCCESS;
}

Status RegisterMer(MLinkedList* Head)//注册用户//头插法
{
	if (*Head == NULL)
	{
		printf("该用户表未初始化！\n");
		return ERROR;
	}
	MLNode* p = *Head;		//指向头结点
	MLNode* q;

	q = (MLNode*)malloc(sizeof(MLNode));
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
			printf("商家名已存在，注册失败！\n");
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
	q->income = 0;			//新用户金额为0
	q->money = 0;			
	q->orders = 0;			

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

Status RePassword_Mer(MLinkedList* Head)//找回密码
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("无商家注册！\n");
		return ERROR;
	}

	char phoneID[20] = { 0 };
	MLNode* p = (*Head)->next;

	printf("请输入要查找的密码的手机号：\n");
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
				printf("且商家名为：%s\n", p->name);
				return SUCCESS;

			}
			p = p->next;//指到下一个结点

		}
		printf("改手机号未注册！\n");
		break;
	}
	return ERROR;
}

MLNode* Login_Mer(MLinkedList* Head)//登录
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return NULL;
	}
	if ((*Head)->next == NULL)
	{
		printf("无商家注册\n");
		return NULL;
	}


	MLNode* p;		//指向第一个结点
	p = (MLNode*)malloc(sizeof(MLNode));
	p = (*Head)->next;

	char names[20] = { 0 };
	char pass[20] = { 0 };

	/*输入数据*/
	printf("请输入你的商家名：\n");
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

	printf("商家户不存在！");
	return NULL;
}

Status SaveData_MerEnd(MLinkedList* Head)//保存数据并退出//判断是否出现重复数据
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
	fp = fopen("merchant.txt", "w+");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return OVERFLOW;
	}
	fprintf(fp, "商家名");
	fprintf(fp, "\t\t");
	fprintf(fp, "密码");
	fprintf(fp, "\t\t");
	fprintf(fp, "手机号");
	fprintf(fp, "\t\t");
	fprintf(fp, "收益");
	fprintf(fp, "\t\t");
	fprintf(fp, "余额");
	fprintf(fp, "\t\t");
	fprintf(fp, "订单数");
	fprintf(fp, "\n");

	MLNode* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, p->name);
		fprintf(fp, "\t\t");
		fprintf(fp, p->password);
		fprintf(fp, "\t\t");
		fprintf(fp, p->phone);
		fprintf(fp, "\t\t");
		fprintf(fp, "%.2lf", p->income);
		fprintf(fp, "\t\t");
		fprintf(fp, "%.2lf", p->money);
		fprintf(fp, "\t\t");
		fprintf(fp, "%d", p->orders);
		fprintf(fp, "\n");
	}

	printf("数据存入成功！\n");
	fclose(fp);
	return SUCCESS;
}

Status Withdraw(MLinkedList MU)//提现
{
	if (MU == NULL)
	{
		printf("未初始化，请初始化！\n");
		return AERROR;
	}
	/*判断收益*/
	if (!(MU->income > 100))
	{
		printf("对不起，您的收益不足以提现！\n");
		printf("最低限额：￥100 ！\n");
		return AERROR;
	}

	double taxi = TAXI;
	double one = 1;
	int flag;
	int a;

	printf("您的收益为：%.2lf\n", MU->income);
	printf("当前税率为：%lf", taxi);
	printf("是否选择提现?(1:yes/ 2:no)\n");
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
		MU->money = (MU->income) * (one-taxi);	//提现计算
		MU->income = 0;
		printf("提现成功！\n");
		return SUCCESS;
	}
	printf("提现功能已退出！\n");
	return SUCCESS;
}