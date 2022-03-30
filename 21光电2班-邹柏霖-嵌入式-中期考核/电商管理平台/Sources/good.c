#include "good.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

Status InitGood_File(ListGood* Head)//创建空链表放入文件中
{
	Goods* p;
	char buf[1024];				//缓冲区

	*Head = (Goods*)malloc(sizeof(Goods));		//给头结点分配内存
	if (*Head == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//头结点下一个结点置空
	p = *Head;					//用p指向头结点

	/*文件*/
	FILE* fp = fopen("good.txt", "r");
	if (fp == NULL)
	{
		printf("商品文件不存在，已自动为您创建！\n");
		fp = fopen("good.txt", "w");
		if (fp == NULL)
		{
			printf("商品文件创建失败！\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//第一行为目录，读一行数据

	while (1)
	{
		Goods* q;
		q = (Goods*)malloc(sizeof(Goods));
		if (q == NULL)
		{
			printf("内存分配失败！\n");
			return OVERFLOW;
		}

		/*检测录入数据到文件流是否完成*/
		if (fscanf(fp, "%s%lf%d%s", q->name, &q->price, &q->amount, q->belong) != 4)//成功后返回4，否则就录入到最后一个结点为空，退出
		{
			free(q);			//录入数据完毕后情空分配的内存
			break;
		}

		/*检测商品是否卖光  库存为0*/
		if (q->amount == 0)
		{
			free(q);
			continue;
		}
		q->next = NULL;

		p->next = q;			//赋值给该结点
		p = q;					//点位到下个结点

	}

	printf("商品表初始化成功！\n");
	return SUCCESS;
}

Status AddGood(ListGood* Head)//添加商品//头插法
{
	if (*Head == NULL)
	{
		printf("该商品表未初始化！\n");
		return ERROR;
	}
	Goods* p = *Head;		//指向头结点
	Goods* q;

	q = (Goods*)malloc(sizeof(Goods));
	if (q == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}

	/*输入数据*/
	printf("请输入商品名：\n");
	scanf("%s", q->name);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->name, q->name))
		{
			printf("商品已存在，存入失败！\n");
			return ERROR;
		}

		p = p->next;
	}
	p = *Head;				//重新指向头结点
	printf("请输入价格：\n");
	scanf("%lf", &q->price);
	printf("请输入库存：\n");
	scanf("%d", &q->amount);
	printf("请输入所属商家：\n");
	scanf("%s", q->belong);

	/*若表中无注册商品*/
	if (p->next == NULL)
	{
		p->next = q;
		p->next->next = NULL;		//最后一个结点置空
	}

	/*若表中有商品注册*/
	else
	{
		q->next = p->next;			//头插法
		p->next = q;
	}

	return SUCCESS;
}

Status SaveData_GoodEnd(ListGood* Head)//保存数据并退出//判断是否出现重复数据
{
	if (*Head == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("该商品表为空，无法存入数据！\n");
		return ERROR;
	}

	FILE* fp;
	fp = fopen("good.txt", "w+");
	if (fp == NULL)
	{
		printf("文件打开失败！\n");
		return OVERFLOW;
	}
	fprintf(fp, "商品名");
	fprintf(fp, "\t\t");
	fprintf(fp, "价格");
	fprintf(fp, "\t\t");
	fprintf(fp, "库存");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "所属商家");
	fprintf(fp, "\n");

	Goods* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, p->name);
		fprintf(fp, "\t\t");
		fprintf(fp, "%.2lf", p->price);
		fprintf(fp, "\t\t");
		fprintf(fp, "%d", p->amount);
		fprintf(fp, "\t\t\t");
		fprintf(fp, p->belong);
		fprintf(fp, "\n");
	}

	printf("数据存入成功！\n");
	fclose(fp);
	return SUCCESS;
}

