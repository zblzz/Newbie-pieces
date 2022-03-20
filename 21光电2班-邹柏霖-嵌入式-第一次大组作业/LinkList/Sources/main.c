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
	printf("|---\t\t 10:��պ���ֲ˵�\t---|\n");


	while (1)
	{
		printf("������ʹ�ù��ܵ����(ֻ����������):\n");
		scanf_s("%d", &mode);
		while (!(mode >= 0 && mode <= 10))
		{
			printf("��������룡�������룡\n");
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
			printf("��������Ҫ�����λ�ã�\n");
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
				printf("�����ݴ���\n");
				break;
			}
			q = (LNode* )malloc(sizeof(LNode));
			if (q == NULL)
			{
				exit(1);
			}
			printf("��������������Ԫ�أ�\n");
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
