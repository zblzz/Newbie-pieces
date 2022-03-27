#include "LQueue.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string.h>

void InitLQueue(LQueue* Q)//��ʼ������,����һ���ն���
{
	Q->front = (Node* )malloc(sizeof(Node));
	if (Q->front == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}
	
	Q->rear = Q->front;			//��ͷ��β����
	Q->front->next = NULL;		//ͷ����ÿ�
	Q->length = 1;				//�����ж��Ƿ��ʼ�����������������-1
}

void DestoryLQueue(LQueue* Q)//���ٶ���
{
	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return;
	}

	//��ͷָ�뿪ʼɾ��
	while (Q->front != NULL)
	{
		Q->rear = Q->front->next;
		free(Q->front);
		Q->front = Q->rear;
	}
	Q->length = 0;

	printf("���ٳɹ���\n");
}

Status IsEmptyLQueue(const LQueue* Q)//�ж��Ƿ�Ϊ�� 
{
	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return FALSE;
	}

	if (Q->front == Q->rear)
	{
		printf("�ö���Ϊ�գ�\n");
	}
	else
		printf("�ö�����Ϊ�գ�\n");

	return TRUE;
}

Status GetHeadLQueue(LQueue* Q, void* e)//�õ���ͷ����
{
	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return FALSE;
	}

	if (Q->front == Q->rear)
	{
		printf("�ö���Ϊ�գ�\n");
		return FALSE;
	}
	e = Q->front->next->data;
	printf("��ֵΪ%d\n", (int)e);
	return TRUE;
}

int LengthLQueue(LQueue* Q)//��������
{
	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return FALSE;
	}
	if (Q->front == Q->rear)
	{
		printf("�ö���Ϊ�գ�\n");
		return FALSE;
	}

	return ((int)Q->length-1);			//��ʼ��������Ϊ1���˴���Ҫ-1
}

Status EnLQueue(LQueue* Q, void* data)//���
{
	int a;
	Node* p;

	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return FALSE;
	}

	p = (Node *)malloc(sizeof(Node));
	if (p == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}

	printf("������Ҫ��������ݣ�\n");
	while (1)
	{
		a = scanf_s("%d", &(int)data);
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
	p->next = NULL;
	Q->rear->next = p;		//�ڶ�β������
	Q->rear = p;			//���¶�β���
	Q->length++;
	return TRUE;
}

Status DeLQueue(LQueue* Q)//����
{
	Node* p;

	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return FALSE;
	}
	if (Q->front == Q->rear)
	{
		printf("�ö���Ϊ�գ�\n");
		return FALSE;
	}

	p = Q->front->next;				//pָ��ͷ���
	if (p == Q->rear)//��ֻ��ͷ���ʱ
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

void ClearLQueue(LQueue* Q)//��ն���
{
	Node* p, * q;

	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return;
	}
	if (Q->front == Q->rear)
	{
		printf("�ö���Ϊ�գ�\n");
		return FALSE;
	}

	//����ͷָ�룬ɾ������
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
	printf("������ճɹ���\n");
}

Status TraverseLQueue(const LQueue* Q, void (*foo)(void* q))//��������
{
	Node* q;

	if (Q->length == 0)
	{
		printf("�ö���δ��ʼ��,���ʼ����\n");
		return FALSE;
	}
	if (Q->front == Q->rear)
	{
		printf("�ö���Ϊ�գ�\n");
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

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);   //��
	printf("\t\t|---\t\t 0:��ʼ������\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //��
	printf("\t\t|---\t\t 1:���ٶ���\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("\t\t|---\t\t 2:�ж϶����Ƿ�Ϊ��\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);   //��
	printf("\t\t|---\t\t 3:�õ���ͷԪ��\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);//��
	printf("\t\t|---\t\t 4:��������\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE);//��
	printf("\t\t|---\t\t 5:���\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_BLUE | BACKGROUND_RED);//��
	printf("\t\t|---\t\t 6:����\t\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);  //��
	printf("\t\t|---\t\t 7:��ն���\t\t---|\n");


	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_INTENSITY);  //����
	printf("\t\t|---\t\t 8:��������\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_INTENSITY);  //�ߺ�
	printf("\t\t|---\t\t 9:����\t\t\t---|\n");

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
				if (!(mode >= 0 && mode <= 9))
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
			printf("�ó���Ϊ%ld\n", a);
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
	CloseHandle(hdl); //Ҫ�ǵùر�Handle���ͷ� Handle ��Դ
}
