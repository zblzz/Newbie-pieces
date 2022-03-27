#include "LinkStack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

Status initLStack(LinkStack* s)//��ʼ��ջ
{
	if (s->top != NULL)
	{
		printf("�ѳ�ʼ���������ٴγ�ʼ����\n");
		return ERROR;
	}

	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	if (s->top == NULL)
	{
		printf("�ڴ�������\n");
		return OVERFLOAT;
	}
	s->top->next = NULL;
	s->count = 0;
	printf("��ʼ���ɹ���\n");
	return SUCCESS;
}


Status isEmptyLStack(LinkStack* s)//�ж�ջ�Ƿ�Ϊ��
{
	//�ж��Ƿ��ʼ��
	if (s->top == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}

	if (s->count == 0)
	{
		printf("��ջΪ�գ�\n");
	}
	else
	{
		printf("��ջ��Ϊ�գ�\n");
	}
	return SUCCESS;
}


Status getTopLStack(LinkStack* s, ElemType* e)//�õ�ջ��Ԫ��,���ظ�e
{
	if (s->top == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}

	if (s->top->next == NULL)
	{
		printf("����ջΪ�գ�\n");
		return ERROR;
	}

	*e = s->top->data;
	printf("��ֵΪ%d\n", *e);
	return SUCCESS;
}


Status clearLStack(LinkStack* s)//���ջ
{
	LinkStackPtr p,t;

	if (s->top == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}

	p = s->top;
	while (p != 0)
	{
		t = p;			//�ݴ�p�����ͷ�
		free(t);		//�����ͷ�
		p = p->next;
	}

	s->count = 0;
	s->top->next = NULL;
	printf("��ճɹ���\n");
	return SUCCESS;
}


Status destroyLStack(LinkStack* s)//����ջ
{
	LinkStackPtr p;

	if (s->top == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}

	while (s->top != 0)
	{
		p = s->top->next;	//�ݴ�
		free(s->top);		//�����ͷ�
		s->top = p;
	}
	
	printf("���ٳɹ���\n");
	return SUCCESS;
}


Status LStackLength(LinkStack* s, int* length)//���ջ����
{
	if (s->top == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}

	*length = s->count;
	printf("����ջ����Ϊ��%d", *length);
	return SUCCESS;
}


Status pushLStack(LinkStack* s, ElemType data)//��ջ
{
	int a;
	LinkStackPtr p;
	p = (LinkStackPtr)malloc(sizeof(StackNode));
	if (p == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOAT;
	}

	if (s->top == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}
	printf("������Ҫ��������ݣ�");
	while (1)
	{
		a = scanf_s("%d", &data);
		if (a != 0)
		{
			if (!(data >= 0))
			{
				printf("��������룬���������룡\n");
			}
			else break;
		}
		else
		{
			printf("��������֣����������룡\n");
			gets(&(char)data);
			printf("������Ҫ��������ݣ�");
		}
	}

	p->data = data;
	p->next = s->top;
	s->top = p;
	s->count++;

	return SUCCESS;
}


Status popLStack(LinkStack* s, ElemType* data)//��ջ
{
	LinkStackPtr p;
	if (s->top == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}
	*data = s->top->data;		//��data������ջ��Ԫ�ص�ֵ

	p = s->top;					//��p�ݴ�ͷָ��
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

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);   //��
	printf("\t\t|---\t\t 0:��ʼ��ջ\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //��
	printf("\t\t|---\t\t 1:�ж�ջ�Ƿ�Ϊ��\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("\t\t|---\t\t 2:�õ�ջ��Ԫ��\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);   //��
	printf("\t\t|---\t\t 3:���ջ	\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);//��
	printf("\t\t|---\t\t 4:����ջ	\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE);//��
	printf("\t\t|---\t\t 5:���ջ����\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE | BACKGROUND_RED);//��
	printf("\t\t|---\t\t 6:��ջ\t\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //��
	printf("\t\t|---\t\t 7:��ջ\t\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_INTENSITY);  //����
	printf("\t\t|---\t\t 8:��������ֲ˵�\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	//�����������ԣ���ɫ����ɫ����ɫ��������


	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 0 && mode <= 8))
				{
					printf("��������룬���������룡\n");
				}
				else break;
			}
			else
			{
				printf("��������֣����������룡\n");
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
	CloseHandle(hdl); //Ҫ�ǵùر�Handle���ͷ� Handle ��Դ
}
