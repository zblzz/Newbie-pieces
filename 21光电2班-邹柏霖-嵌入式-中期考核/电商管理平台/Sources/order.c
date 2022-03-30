#include "order.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>

Status InitLOrder_File(ListOrder* Head)//创建空链表放入文件中//头结点不放数据
{
	Order* p;
	char buf[1024];				//缓冲区

	*Head = (Order*)malloc(sizeof(Order));		//给头结点分配内存
	if (*Head == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//头结点下一个结点置空
	p = *Head;					//用p指向头结点

	/*文件*/
	FILE* fp = fopen("order.txt", "r");
	if (fp == NULL)
	{
		printf("订单文件不存在，已自动为您创建！\n");
		fp = fopen("order.txt", "w");
		if (fp == NULL)
		{
			printf("订单文件创建失败！\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//第一行为目录，读一行数据

	while (1)
	{
		Order* q;
		q = (Order*)malloc(sizeof(Order));
		if (q == NULL)
		{
			printf("内存分配失败！\n");
			return OVERFLOW;
		}

		/*检测录入数据到文件流是否完成*/
		if (fscanf(fp, "%d%s%s%s%s", &q->ID, q->goodsname, q->buyer, q->address, q->delivery) != 5)	//成功后返回5，否则就录入到最后一个结点为空，退出
		{
			free(q);			//录入数据完毕后情空分配的内存
			break;
		}
		q->next = NULL;

		p->next = q;			//赋值给该结点
		p = q;					//点位到下个结点

	}

	printf("订单表初始化成功！\n");
	return SUCCESS;
}

Status User_AddOrder(ListOrder* Head,LinkedList U)//用户添加订单//头插法
{
	if (*Head == NULL)
	{
		printf("该订单表未初始化！\n");
		return ERROR;
	}
	Order* p = *Head;		//指向头结点
	Order* q;

	q = (Order*)malloc(sizeof(Order));
	if (q == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}

	/*输入数据*/
	printf("请输入要添加的订单的商品名：\n");
	scanf("%s", q->goodsname);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->goodsname, q->goodsname))
		{
			printf("订单已存在，添加失败！\n");
			return ERROR;
		}

		p = p->next;
	}
	p = *Head;				//重新指向头结点
	printf("请输入您的昵称：\n");
	scanf("%s", q->buyer);
	printf("请输入地址：\n");
	scanf("%s", q->address);
	strcpy(q->delivery, "未发货");
	q->ID = ++LID;

	/*若表中无订单添加*/
	if (p->next == NULL)
	{
		p->next = q;
		p->next->next = NULL;		//最后一个结点置空
	}

	/*若表中已有订单*/
	else
	{
		q->next = p->next;			//头插法
		p->next = q;
	}

	return SUCCESS;
}

Status ModifyOrder(MLinkedList M, ListOrder* Head)//商家修改订单
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return AERROR;
	}
	if (M == NULL)
	{
		printf("登陆失败！\n");
		return AERROR;
	}

	Order* p = (* Head)->next;		//指向第一个结点
	int a, flag, b;

	/*输入ID*/
	printf("请输入你需要修改的订单ID:");
	while (1)
	{
		a = scanf_s("%d", &flag);
		if (a != 0)
		{
			if (!(flag >= 1))
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

	/*遍历订单表*/
	/*遍历商品表*/
	while (p != NULL)
	{
		if (!(flag == p->ID))
		{
			printf("成功找到！\n");
			printf("该订单信息为:\n");
			printf("订单号：%d\t", p->ID);
			printf("商品名：%s\t\t", p->goodsname);
			printf("购买者昵称：%s\n", p->buyer);
			printf("地址：%s\n", p->address);
			printf("发货状态：%s\n", p->delivery);

			/*修改信息*/
			printf("是否选择发货?(1:yes/ 2:no)\n");
			if (scanf("%d", &b) == 1)
			{
				strcpy(p->delivery, "已发货");
			}
			return SUCCESS;
		}
		p = p->next;
	}
	printf("该订单不存在！\n");
	return AERROR;
}

Status SaveData_OrderEnd(ListOrder* Head)//保存数据并退出//判断是否出现重复数据
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return AERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("该订单表为空，无法存入数据！\n");
		return ERROR;
	}

	FILE* fp;
	fp = fopen("order.txt", "w+");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return OVERFLOW;
	}
	fprintf(fp, "订单号");
	fprintf(fp, "\t");
	fprintf(fp, "商品名");
	fprintf(fp, "\t\t");
	fprintf(fp, "购买者");
	fprintf(fp, "\t\t");
	fprintf(fp, "地址");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "发货状态");
	fprintf(fp, "\n");

	Order* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, "%d", p->ID);
		fprintf(fp, "\t");
		fprintf(fp, p->goodsname);
		fprintf(fp, "\t\t");
		fprintf(fp, p->buyer);
		fprintf(fp, "\t\t");
		fprintf(fp, p->address);
		fprintf(fp, "\t\t\t");
		fprintf(fp, p->delivery);
		fprintf(fp, "\n");
	}

	printf("数据存入成功！\n");
	fclose(fp);
	return SUCCESS;
}