#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Status InitList(LinkedList* L)//初始化空链表
{
	int i, n;
	char a;
	LNode* p, * q;

	*L = (LinkedList)malloc(sizeof(LNode));
	if (*L == NULL )
	{
		printf("内存分配失败！\n");
		return OVERFLOW;
	}
	(*L)->next = NULL;
	p = *L;
	printf("初始化成功！\n");
	printf("是否要插入节点？（y/n）\n");
	getchar();
	scanf_s("%c", &a);
	if (a == 'y')
	{
		printf("插入的节点数为：\n");
		scanf_s("%d", &n);
		for (i = 1; i <= n; i++)
		{
			q = (LinkedList)malloc(sizeof(LNode));
			printf("输入的第%d个节点的值为：", i);
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
		printf("好的呢！\n");
		return SUCCESS;
	}
	else
	{
		printf("请不要乱输入！\n");
		return ERROR;
	}
}

void DestroyList(LinkedList* L)//销毁链表
{
	LNode* p;
	LNode* t;

	if (*L == NULL)
	{
		printf("error该链表为空！\n");
		exit(1);
	}
	p = (*L)->next;
	while (p != NULL)
	{
		t = p->next;
		free(p);
		p = t;
	}
	printf("销毁成功！\n");
	exit(1);
}

Status InsertList(LNode* p, LNode* q)//插入链表，在p之后插入q(q为所插入的链表)
{
	if (p == NULL || q == NULL)
	{
		printf("输入的两参数有误！\n");
		return ERROR;
	}
	q->next = p->next;
	p->next = q;

	return SUCCESS;
	
}

Status DeleteList(LNode* p, ElemType* e)//删除链表（删除p之后的节点，并将其的值返回给参数e）
{
	LNode* t;
	LNode* q;
	if (p == NULL || p->next == NULL)
	{
		printf("该链表为空或删除位置有误！\n");
		return ERROR;
	}

	printf("你想删除的节点为:\n");
	scanf_s("%d", e);

	t = p->next;
	q = t->next;
	p->next = q;
	e = t->data;					//被删除的节点的数据
	free(t);						//释放被删除的节点
	return SUCCESS;
}

void TraverseList(LinkedList L, void (*visit)(ElemType e))
{
	LNode* p;

	if (L == NULL)
	{
		printf("该链表为空！\n");
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

Status SearchList(LinkedList L, ElemType e)//查找链表
{
	if (L == NULL)
	{
		printf("该链表为空！\n");
		return ERROR;
	}

	printf("你想查找的节点为:\n");
	scanf_s("%d", &e);

	while (L != NULL)
	{
		if (L->data == e)
		{
			printf("恭喜你找到了！\n");
			printf("该值为%d\n", L->data);
			return SUCCESS;
		}
		L = L->next;
	}
	printf("不好意思，你所要找的不在该链表内！\n");
	return ERROR;
}

Status ReverseList(LinkedList* L)//逆置链表(先将头节点断开，再从前往后将元素插入头节点之后)
{
	LNode* p;
	LNode* t;
	LNode* q;
	p = *L;

	if (p == NULL || p->next == NULL || (p->next)->next == NULL)
	{
		printf("该链表不满足条件！\n");
		return ERROR;
	}
	else
	{
		t = p->next;					//保存头节点下一位的地址
		(*L)->next = NULL;				//断开头节点

		//依次将元素从前往后插入头节点之后
		while (t != NULL)
		{
			q = t->next;				//q保存是待插入的直接后继
			InsertList(*L, t);
			t = q;
		}
		
		printf("逆置成功！\n");
		return SUCCESS;
	}
}

Status IsLoopList(LinkedList L)//判断链表是否成环
{
	LNode* p, * q;
	LNode* t;

	if (L == NULL || L->next == NULL)
	{
		printf("该链表不满足条件！\n");
		return ERROR;
	}
	p = L;
	q = L->next;
	while (p != NULL && q != NULL)
	{
		if (p == q)
		{
			printf("该链表成环！\n");
			return SUCCESS;
		}
		p = p->next;				//p的速度为1

		t = q->next;				//q的速度为2
		if (t == NULL)	break;
		q = t->next;
	}
	printf("该链表不成环！\n");
	return ERROR;
}

LNode* ReverseEvenList(LinkedList* L)//奇偶反转
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
		printf("该链表不满足条件！\n");
		return NULL;
	}
	
	p = t ->next;
	q = p ->next;

	e = q->data;
	q->data = p->data;
	p->data = e;
	while (p != NULL && q != NULL)
	{
		e = p->next;				//p的速度为2
		if (e == NULL)	break;
		p = e->next;				

		e = q->next;				//q的速度为2
		if (e == NULL)	break;
		q = e->next;
		if (q == NULL)	break;
		
		e = q->data;
		q->data = p->data;
		p->data = e;
	}
	printf("奇偶交换成功！\n");
	
	return t;
}

LNode* FindMidNode(LinkedList* L)//找到中间节点
{
	LNode* p, * q;
	LNode* t;
	p = *L;
	if (p == NULL || p->next == NULL)
	{
		printf("该链表不满足条件！\n");
		return NULL;
	}

	q = p;							//初始点相同
	while (p != NULL && q != NULL)
	{
		p = p->next;				//p的速度为1

		t = q->next;				//q的速度为2
		if (t == NULL)	break;
		q = t->next;
	}
	printf("找到该链表的中间节点了！\n");
	printf("该节点的值为：%d\n", p->data);
	return p;
}

void menu()
{
	system("cls");
	system("pause");
	printf("|---\t\t 0:链表初始化\t\t---|\n");
	printf("|---\t\t 1:销毁链表\t\t---|\n");
	printf("|---\t\t 2:插入链表\t\t---|\n");
	printf("|---\t\t 3:删除链表\t\t---|\n");
	printf("|---\t\t 4:遍历链表\t\t---|\n");
	printf("|---\t\t 5:查找链表\t\t---|\n");
	printf("|---\t\t 6:逆置链表\t\t---|\n");
	printf("|---\t\t 7:判断是否成环\t\t---|\n");
	printf("|---\t\t 8:奇偶调换\t\t---|\n");
	printf("|---\t\t 9:找到中间节点\t\t---|\n");
	printf("|---\t\t 10:清空后出现菜单\t\t---|\n");
}