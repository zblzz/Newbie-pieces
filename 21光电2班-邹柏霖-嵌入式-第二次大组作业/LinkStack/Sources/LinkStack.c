#include "LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

Status initLStack(LinkStack* s)//初始化栈
{
	if (s->top != NULL)
	{
		printf("已初始化，请勿再次初始化！\n");
		return ERROR;
	}

	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if (s->top == NULL)
	{
		printf("内存分配错误！\n");
		return OVERFLOAT;
	}
	s->top->next = NULL;
	s->count = 0;
	printf("初始化成功！\n");
	return SUCCESS;
}


Status isEmptyLStack(LinkStack* s)//判断栈是否为空
{
	//判断是否初始化
	if (s->top == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}

	if (s->count == 0)
	{
		printf("该栈为空！\n");
	}
	else
	{
		printf("该栈不为空！\n");
	}
	return SUCCESS;
}


Status getTopLStack(LinkStack* s, ElemType* e)//得到栈顶元素,返回给e
{
	if (s->top == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}

	if (s->top->next == NULL)
	{
		printf("该链栈为空！\n");
		return ERROR;
	}

	*e = s->top->data;
	printf("该值为%d\n", *e);
	return SUCCESS;
}


Status clearLStack(LinkStack* s)//清空栈
{
	LinkStackPtr p,t;

	if (s->top == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}

	p = s->top;
	while (p != 0)
	{
		t = p;			//暂存p，并释放
		free(t);		//逐条释放
		p = p->next;
	}

	s->count = 0;
	s->top->next = NULL;
	printf("清空成功！\n");
	return SUCCESS;
}


Status destroyLStack(LinkStack* s)//销毁栈
{
	LinkStackPtr p;

	if (s->top == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}

	while (s->top != 0)
	{
		p = s->top->next;	//暂存
		free(s->top);		//逐条释放
		s->top = p;
	}
	
	printf("销毁成功！\n");
	return SUCCESS;
}


Status LStackLength(LinkStack* s, int* length)//检测栈长度
{
	if (s->top == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}

	*length = s->count;
	printf("该链栈长度为：%d", *length);
	return SUCCESS;
}


Status pushLStack(LinkStack* s, ElemType data)//入栈
{
	int a;
	LinkStackPtr p;
	p = (LinkStackPtr)malloc(sizeof(StackNode));
	if (p == NULL)
	{
		printf("内存分配失败！\n");
		return OVERFLOAT;
	}

	if (s->top == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}
	printf("请输入要插入的数据：");
	while (1)
	{
		a = scanf_s("%d", &data);
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
	p->next = s->top;
	s->top = p;
	s->count++;

	return SUCCESS;
}


Status popLStack(LinkStack* s, ElemType* data)//出栈
{
	LinkStackPtr p;
	if (s->top == NULL)
	{
		printf("未初始化，请初始化！\n");
		return ERROR;
	}
	*data = s->top->data;		//用data返回其栈顶元素的值

	p = s->top;					//用p暂存头指针
	s->top = s->top->next;
	free(p);
	s->count--;
	return SUCCESS;
}

void menu(void)
{
	int mode = 0;
	
	int a,b,e,length;

	static LinkStack L;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);   //红
	printf("\t\t|---\t\t 0:初始化栈\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //橙
	printf("\t\t|---\t\t 1:判断栈是否为空\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //黄
	printf("\t\t|---\t\t 2:得到栈顶元素\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);   //绿
	printf("\t\t|---\t\t 3:清空栈	\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);//青
	printf("\t\t|---\t\t 4:销毁栈	\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE);//蓝
	printf("\t\t|---\t\t 5:检测栈长度\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE | BACKGROUND_RED);//紫
	printf("\t\t|---\t\t 6:入栈\t\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //橙
	printf("\t\t|---\t\t 7:出栈\t\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_INTENSITY);  //高绿
	printf("\t\t|---\t\t 8:清屏后出现菜单\t---|\n");

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
				if (!(mode >= 0 && mode <= 8))
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
			initLStack(&L);
			break;
		case 1:
			isEmptyLStack(&L);
			break;
		case 2:
			getTopLStack(&L,&e);
			break;
		case 3:
			clearLStack(&L);
			break;
		case 4:
			destroyLStack(&L);
			break;
		case 5:
			LStackLength(&L, &length);
			break;
		case 6:
			pushLStack(&L,a);
			break;
		case 7:
			popLStack(&L,&b);
			break;
		case 8:
			menu();
			break;
		}
	}
	CloseHandle(hdl); //要记得关闭Handle，释放 Handle 资源
}
