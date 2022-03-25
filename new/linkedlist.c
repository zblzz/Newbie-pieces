#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Windows.h>

Status InitList(LinkedList* L)//��ʼ��������
{
	int i,j, n,k;
	char a[40];
	LNode* p, * q;

	*L = (LinkedList)malloc(sizeof(LNode));
	if (*L == NULL )
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}
	(*L)->next = NULL;
	p = *L;
	printf("��ʼ���ɹ���\n");
	printf("�Ƿ�Ҫ����ڵ㣿��y/n��\n");
	getchar();
	gets(a);
	if (strcmp(a,"y") == 0)
	{
		printf("����Ľڵ���Ϊ��\n");
		j = scanf_s("%d", &n);
		if (j == 0)
		{
			printf("����Ϊ�����֣�������ѡ��\n");
			gets(&(char)n);
			return ERROR;
		}
		for (i = 1; i <= n; i++)
		{
			q = (LinkedList)malloc(sizeof(LNode));
			printf("����ĵ�%d���ڵ��ֵΪ��", i);
			k = scanf_s("%d", &q->data);
			if (j == 0)
			{
				printf("��������������ѡ��\n");
				gets(&(char)q->data);
				return ERROR;
			}
			q->next = NULL;
			p->next = q;
			p = p->next;
		}
			p = *L;
			return SUCCESS;
	}
	else if (strcmp(a, "n") == 0)
	{
		printf("�õ��أ�\n");
		return SUCCESS;
	}
	else
	{
		printf("�벻Ҫ�����룡\n");
		return ERROR;
	}
	
}

void DestroyList(LinkedList* L)//��������
{
	char a;
	LNode* p;
	LNode* t;

	if (*L == NULL)
	{
		printf("������δ��ʼ����\n");
		printf("�Ƿ�Ҫ��ʼ������(y/n)\n");
		getchar();
		scanf_s("%c", &a);
		if (a == 'y')
		{
			InitList(L);
			return;
		}
		else if (a == 'n')
		{
			printf("�õ��أ�\n");
			return;
		}
		else
		{
			printf("�벻Ҫ�����룡\n");
			return;
		}
	}
	p = (*L)->next;
	while (p != NULL)
	{
		t = p->next;
		free(p);
		p = t;
	}
	printf("���ٳɹ���\n");
	exit(1);
}

Status InsertList(LNode* p, LNode* q)//����������p֮�����q(qΪ�����������)
{
	if (p == NULL || q == NULL)
	{
		printf("���������������\n");
		return ERROR;
	}
	q->next = p->next;
	p->next = q;

	return SUCCESS;
	
}

Status DeleteList(LNode* p, ElemType* e)//ɾ������ɾ��p֮��Ľڵ㣬�������ֵ���ظ�����e��
{
	int j;
	LNode* t;
	LNode* q;
	if (p == NULL || p->next == NULL)
	{
		printf("������δ��ʼ����ɾ��λ������\n");
		return ERROR;
	}

	printf("����ɾ���Ľڵ�Ϊ:\n");
	j = scanf_s("%d", e);
	if (j == 0)
	{
		printf("��������������ѡ��\n");
		gets(&(char)e);
		return ERROR;
	}

	t = p->next;
	q = t->next;
	p->next = q;
	e = t->data;					//��ɾ���Ľڵ������
	free(t);						//�ͷű�ɾ���Ľڵ�
	return SUCCESS;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e))//��������
{
	LNode* p;

	if (L == NULL)
	{
		printf("������δ��ʼ����\n");
		return;
	}
	p = L->next;
	while (p != NULL)
	{
		printf("%d", p->data);
		p = p->next;
		if (p != NULL)
		{
			printf("->");
		}
	}
	printf("\n");
}

Status SearchList(LinkedList L, ElemType e)//��������
{
	int j;
	if (L == NULL)
	{
		printf("������δ��ʼ����\n");
		return ERROR;
	}

	printf("������ҵĽڵ�Ϊ:\n");
	j = scanf_s("%d", &e);
	if (j == 0)
	{
		printf("��������������ѡ��\n");
		gets(&(char)e);
		return ERROR;
	}

	while (L != NULL)
	{
		if (L->data == e)
		{
			printf("��ϲ���ҵ��ˣ�\n");
			printf("��ֵΪ%d\n", L->data);
			return SUCCESS;
		}
		L = L->next;
	}
	printf("������˼������Ҫ�ҵĲ��ڸ������ڣ�\n");
	return ERROR;
}

Status ReverseList(LinkedList* L)//��������(�Ƚ�ͷ�ڵ�Ͽ����ٴ�ǰ����Ԫ�ز���ͷ�ڵ�֮��)
{
	LNode* p;
	LNode* t;
	LNode* q;
	p = *L;

	if (p == NULL || p->next == NULL || (p->next)->next == NULL)
	{
		printf("����������������\n");
		return ERROR;
	}
	else
	{
		t = p->next;					//����ͷ�ڵ���һλ�ĵ�ַ
		(*L)->next = NULL;				//�Ͽ�ͷ�ڵ�

		//���ν�Ԫ�ش�ǰ�������ͷ�ڵ�֮��
		while (t != NULL)
		{
			q = t->next;				//q�����Ǵ������ֱ�Ӻ��
			InsertList(*L, t);
			t = q;
		}
		
		printf("���óɹ���\n");
		return SUCCESS;
	}
}

Status IsLoopList(LinkedList L)//�ж������Ƿ�ɻ�
{
	LNode* p, * q;
	LNode* t;

	if (L == NULL || L->next == NULL)
	{
		printf("����������������\n");
		return ERROR;
	}
	p = L;
	q = L->next;
	while (p != NULL && q != NULL)
	{
		if (p == q)
		{
			printf("������ɻ���\n");
			return SUCCESS;
		}
		p = p->next;				//p���ٶ�Ϊ1

		t = q->next;				//q���ٶ�Ϊ2
		if (t == NULL)	break;
		q = t->next;
	}
	printf("�������ɻ���\n");
	return ERROR;
}

LNode* ReverseEvenList(LinkedList* L)//��ż��ת
{
	LNode* p, * q, * t,* e = NULL;
	t = *L;

	e = (LNode*)malloc(sizeof(LNode));
	if (e == NULL)
	{
		exit(1);
	}
	if (t == NULL || t->next == NULL || (t->next)->next == NULL)
	{
		printf("����������������\n");
		return NULL;
	}
	
	p = t ->next;
	q = p ->next;

	e = q->data;
	q->data = p->data;
	p->data = e;
	while (p != NULL && q != NULL)
	{
		e = p->next;				//p���ٶ�Ϊ2
		if (e == NULL)	break;
		p = e->next;				

		e = q->next;				//q���ٶ�Ϊ2
		if (e == NULL)	break;
		q = e->next;
		if (q == NULL)	break;
		
		e = q->data;
		q->data = p->data;
		p->data = e;
	}
	printf("��ż�����ɹ���\n");
	
	return t;
}

LNode* FindMidNode(LinkedList* L)//�ҵ��м�ڵ�
{
	LNode* p, * q;
	LNode* t;
	p = *L;
	if (p == NULL || p->next == NULL)
	{
		printf("����������������\n");
		return NULL;
	}

	q = p;							//��ʼ����ͬ
	while (p != NULL && q != NULL)
	{
		p = p->next;				//p���ٶ�Ϊ1

		t = q->next;				//q���ٶ�Ϊ2
		if (t == NULL)	break;
		q = t->next;
	}
	printf("�ҵ���������м�ڵ��ˣ�\n");
	printf("�ýڵ��ֵΪ��%d\n", p->data);
	return p;
}

void menu()
{
	int mode = 0;
	int e = 0;
	int n, i, j, a;

	static LNode* L ;
	LNode* p = NULL;
	LNode* q = NULL;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���


	SetConsoleTextAttribute(hdl, BACKGROUND_RED);   //��
	printf("|---\t\t 0:�����ʼ��  \t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //��
	printf("|---\t\t 1:��������    \t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("|---\t\t 2:��������    \t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);   //��
	printf("|---\t\t 3:ɾ������    \t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);//��
	printf("|---\t\t 4:��������    \t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE);//��
	printf("|---\t\t 5:��������    \t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE | BACKGROUND_RED);//��
	printf("|---\t\t 6:��������    \t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //��
	printf("|---\t\t 7:�ж��Ƿ�ɻ�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_INTENSITY);  //�ߺ�
	printf("|---\t\t 8:��ż����    \t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE | BACKGROUND_INTENSITY);  //����
	printf("|---\t\t 9:�ҵ��м�ڵ�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_INTENSITY);  //����
	printf("|---\t\t 10:��������ֲ˵�\t---|\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_GREEN | BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	//�����������ԣ���ɫ����ɫ����ɫ��������


	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while(1)
		{
			a = scanf_s("%d", &mode);
				if (a != 0)
				{
					if (!(mode >= 0 && mode <= 10))
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
			InitList(&L);
			break;
		case 1:
			DestroyList(&L);
			break;
		case 2:
			if (L == NULL)
			{
				printf("������δ��ʼ����\n");
				break;
			}
			printf("��������Ҫ�����λ�ã�\n");
			j = scanf_s("%d", &i);
			if (j == 0)
			{
				printf("����Ϊ�����֣�������ѡ��\n");
				gets(&(char)e);
				break;
			}
			p = L;
			n = 1;
			while (p && n < i)
			{
				p = p->next;
				n++;
			}
			if (!p || n > i)
			{
				printf("�����ݴ���\n");
				break;
			}
			q = (LNode*)malloc(sizeof(LNode));
			if (q == NULL)
			{
				exit(1);
			}
			printf("��������������Ԫ�أ�\n");
			i = scanf_s("%d", &j);
			if (i == 0)
			{
				printf("����Ϊ�����֣�������ѡ��\n");
				gets(&(char)j);
				break;
			}

			q->data = j;
			q->next = NULL;
			InsertList(p, q);
			break;
		case 3:
			DeleteList(L, &e);
			break;
		case 4:
			TraverseList(L, e);
			break;
		case 5:
			SearchList(L, e);
			break;
		case 6:
			ReverseList(&L);
			break;
		case 7:
			IsLoopList(L);
			break;
		case 8:
			ReverseEvenList(&L);
			break;
		case 9:
			FindMidNode(&L);
			break;
		case 10:
			menu();
			break;
		}
	}
	CloseHandle(hdl); //Ҫ�ǵùر�Handle���ͷ� Handle ��Դ
}