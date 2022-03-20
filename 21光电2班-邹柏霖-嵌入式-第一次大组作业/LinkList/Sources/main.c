#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int mode = 0;
	int e = 0;
	int n,i,j;
	
	LNode* L = NULL;
	LNode* p = NULL;
	LNode* q = NULL;

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
	printf("|---\t\t 10:清空后出现菜单\t---|\n");


	while (1)
	{
		printf("请输入使用功能的序号(只能输入数字):\n");
		scanf_s("%d", &mode);
		while (!(mode >= 0 && mode <= 10))
		{
			printf("请别乱输入！重新输入！\n");
			scanf_s("%d", &mode);

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
			printf("请输入需要插入的位置：\n");
			scanf_s("%d", &i);
			p = L;
			n = 1;
			while (p && n < i)
			{
				p = p->next;
				n++;
			}
			if (!p || n > i)
			{
				printf("该数据错误！\n");
				break;
			}
			q = (LNode* )malloc(sizeof(LNode));
			if (q == NULL)
			{
				exit(1);
			}
			printf("请输入你想插入的元素：\n");
			scanf_s("%d", &j);

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
			L = ReverseEvenList(&L); 
			break;
		case 9:
			L = FindMidNode(&L);	
			break;
		case 10:
			menu();
			break;
		}
	}
	return 0;
}
