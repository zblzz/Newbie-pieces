#include "LQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

void InitLQueue(LQueue* Q)//初始化队链,建立一个空队链
{
	Q->front = (Node* )malloc(sizeof(Node));
	if (Q->front == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}
	
	Q->rear = Q->front;			//队头队尾对齐
	Q->front->next = NULL;		//头结点置空
	Q->length = 1;				//用来判断是否初始化队链，最后输出结果-1
}

void DestoryLQueue(LQueue* Q)//销毁队链
{
	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return;
	}

	//从头指针开始删除
	while (Q->front != NULL)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	Q->length = 0;

	printf("销毁成功！\n");
}

Status IsEmptyLQueue(const LQueue* Q)//判断是否为空 
{
	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return FALSE;
	}

	if (Q->front == Q->rear)
	{
		printf("该队链为空！\n");
	}
	else
		printf("该队链不为空！\n");

	return TRUE;
}

Status GetHeadLQueue(LQueue* Q, void* e)//得到队头数据
{
	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return FALSE;
	}

	if (Q->front == Q->rear)
	{
		printf("该队链为空！\n");
		return FALSE;
	}
	e = Q->front->next->data;
	printf("该值为%d\n", (int)e);
	return TRUE;
}

int LengthLQueue(LQueue* Q)//队链长度
{
	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return FALSE;
	}
	if (Q->front == Q->rear)
	{
		printf("该队链为空！\n");
		return FALSE;
	}

	return ((int)Q->length-1);			//初始化长度设为1，此处需要-1
}

Status EnLQueue(LQueue* Q, void* data)//入队
{
	int a;
	Node* p;

	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return FALSE;
	}

	p = (Node *)malloc(sizeof(Node));
	if (p == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}

	printf("请输入要输入的数据：\n");
	while (1)
	{
		a = scanf_s("%d", &(int)data);
		if (a != 0)
		{
			if (!(data >= 0))
			{
				printf("请别乱输入，请重新输入！\n");
			}
			else break;
		}
		else
		{
			printf("输入非数字，请重新输入！\n");
			gets(&(char)data);
			printf("请输入要插入的数据：");
		}
	}
	p->data = data;
	p->next = NULL;
	Q->rear->next = p;		//在队尾插入结点
	Q->rear = p;			//更新队尾结点
	Q->length++;
	return TRUE;
}

Status DeLQueue(LQueue* Q)//出队
{
	Node* p;

	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return FALSE;
	}
	if (Q->front == Q->rear)
	{
		printf("该队链为空！\n");
		return FALSE;
	}

	p = Q->front->next;				//p指向头结点
	if (p == Q->rear)//当只有头结点时
	{
		Q->rear = Q->front;
	}
	else
	{
		Q->front->next = p->next;
	}
	free(p);
	Q->length--;
	return TRUE;
}

void ClearLQueue(LQueue* Q)//清空队链
{
	Node* p, * q;

	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return;
	}
	if (Q->front == Q->rear)
	{
		printf("该队链为空！\n");
		return FALSE;
	}

	//保留头指针，删除后面
	p = Q->front->next;
	while (p != NULL)
	{
		q = p;
		free(q);
		p = p->next;
	}
	Q->rear = Q->front;
	Q->front->next = NULL;
	Q->length = 0;
	printf("队链清空成功！\n");
}

Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q))//遍历队链
{
	Node* q;

	if (Q->length == 0)
	{
		printf("该队链未初始化,请初始化！\n");
		return FALSE;
	}
	if (Q->front == Q->rear)
	{
		printf("该队链为空！\n");
		return FALSE;
	}

	q = Q->front->next;
	while (q)
	{
		LPrint(q->data);
		q = q->next;
		if (q != NULL)
		{
			printf("->");
		}
	}
	printf("\n");

	return TRUE;
}

void LPrint(void* q)
{
	printf("%d",(int)q);
}

void menu(void)
{
	int mode = 0;

	int a, e;
	
	int* c = NULL; 
	int* b = NULL;
	
	static LQueue L;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);   //红
	printf("\t\t|---\t\t 0:初始化队链\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //橙
	printf("\t\t|---\t\t 1:销毁队链\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //黄
	printf("\t\t|---\t\t 2:判断队链是否为空\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);   //绿
	printf("\t\t|---\t\t 3:得到队头元素\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);//青
	printf("\t\t|---\t\t 4:队链长度\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE);//蓝
	printf("\t\t|---\t\t 5:入队\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE | BACKGROUND_RED);//紫
	printf("\t\t|---\t\t 6:出队\t\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //橙
	printf("\t\t|---\t\t 7:清空队链\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_INTENSITY);  //高绿
	printf("\t\t|---\t\t 8:遍历队链\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_INTENSITY);  //高红
	printf("\t\t|---\t\t 9:清屏\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	//设置文字属性：绿色，底色：白色、加亮，


	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 0 && mode <= 9))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				gets(&(char)mode);
			}

		}

		switch (mode)
		{
		case 0:
			InitLQueue(&L);
			break;
		case 1:
			DestoryLQueue(&L);
			break;
		case 2:
			IsEmptyLQueue(&L);
			break;
		case 3:
			GetHeadLQueue(&L,&e);
			break;
		case 4:
			a = LengthLQueue(&L);
			if (L.length == 0)
			{
				break;
			}
			printf("该长度为%ld\n", a);
			break;
		case 5:
			EnLQueue(&L, b);
			break;
		case 6:
			DeLQueue(&L);
			break;
		case 7:
			ClearLQueue(&L);
			break;
		case 8:
			TraverseLQueue(&L, c);
			break;
		case 9:
			menu();
			break;
		}
	}
	CloseHandle(hdl); //要记得关闭Handle，释放 Handle 资源
}
