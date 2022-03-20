#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Status InitList(LinkedList* L)//��ʼ��������
{
	int i, n;
	char a;
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
	scanf_s("%c", &a);
	if (a == 'y')
	{
		printf("����Ľڵ���Ϊ��\n");
		scanf_s("%d", &n);
		for (i = 1; i <= n; i++)
		{
			q = (LinkedList)malloc(sizeof(LNode));
			printf("����ĵ�%d���ڵ��ֵΪ��", i);
			scanf_s("%d", &q->data);
			q->next = NULL;
			p->next = q;
			p = p->next;
		}
		p = *L;
		return SUCCESS;
	}
	else if(a == 'n')
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
	LNode* p;
	LNode* t;

	if (*L == NULL)
	{
		printf("error������Ϊ�գ�\n");
		exit(1);
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
	LNode* t;
	LNode* q;
	if (p == NULL || p->next == NULL)
	{
		printf("������Ϊ�ջ�ɾ��λ������\n");
		return ERROR;
	}

	printf("����ɾ���Ľڵ�Ϊ:\n");
	scanf_s("%d", e);

	t = p->next;
	q = t->next;
	p->next = q;
	e = t->data;					//��ɾ���Ľڵ������
	free(t);						//�ͷű�ɾ���Ľڵ�
	return SUCCESS;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e))
{
	LNode* p;

	if (L == NULL)
	{
		printf("������Ϊ�գ�\n");
		exit(1);
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
	if (L == NULL)
	{
		printf("������Ϊ�գ�\n");
		return ERROR;
	}

	printf("������ҵĽڵ�Ϊ:\n");
	scanf_s("%d", &e);

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
	system("cls");
	system("pause");
	printf("|---\t\t 0:�����ʼ��\t\t---|\n");
	printf("|---\t\t 1:��������\t\t---|\n");
	printf("|---\t\t 2:��������\t\t---|\n");
	printf("|---\t\t 3:ɾ������\t\t---|\n");
	printf("|---\t\t 4:��������\t\t---|\n");
	printf("|---\t\t 5:��������\t\t---|\n");
	printf("|---\t\t 6:��������\t\t---|\n");
	printf("|---\t\t 7:�ж��Ƿ�ɻ�\t\t---|\n");
	printf("|---\t\t 8:��ż����\t\t---|\n");
	printf("|---\t\t 9:�ҵ��м�ڵ�\t\t---|\n");
	printf("|---\t\t 10:��պ���ֲ˵�\t\t---|\n");
}