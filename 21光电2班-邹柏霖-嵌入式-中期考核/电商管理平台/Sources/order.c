#include "order.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>

Status InitLOrder_File(ListOrder* Head)//��������������ļ���//ͷ��㲻������
{
	Order* p;
	char buf[1024];				//������

	*Head = (Order*)malloc(sizeof(Order));		//��ͷ�������ڴ�
	if (*Head == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//ͷ�����һ������ÿ�
	p = *Head;					//��pָ��ͷ���

	/*�ļ�*/
	FILE* fp = fopen("order.txt", "r");
	if (fp == NULL)
	{
		printf("�����ļ������ڣ����Զ�Ϊ��������\n");
		fp = fopen("order.txt", "w");
		if (fp == NULL)
		{
			printf("�����ļ�����ʧ�ܣ�\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//��һ��ΪĿ¼����һ������

	while (1)
	{
		Order* q;
		q = (Order*)malloc(sizeof(Order));
		if (q == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			return OVERFLOW;
		}

		/*���¼�����ݵ��ļ����Ƿ����*/
		if (fscanf(fp, "%d%s%s%s%s", &q->ID, q->goodsname, q->buyer, q->address, q->delivery) != 5)	//�ɹ��󷵻�5�������¼�뵽���һ�����Ϊ�գ��˳�
		{
			free(q);			//¼��������Ϻ���շ�����ڴ�
			break;
		}
		q->next = NULL;

		p->next = q;			//��ֵ���ý��
		p = q;					//��λ���¸����

	}

	printf("�������ʼ���ɹ���\n");
	return SUCCESS;
}

Status User_AddOrder(ListOrder* Head,LinkedList U)//�û���Ӷ���//ͷ�巨
{
	if (*Head == NULL)
	{
		printf("�ö�����δ��ʼ����\n");
		return ERROR;
	}
	Order* p = *Head;		//ָ��ͷ���
	Order* q;

	q = (Order*)malloc(sizeof(Order));
	if (q == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}

	/*��������*/
	printf("������Ҫ��ӵĶ�������Ʒ����\n");
	scanf("%s", q->goodsname);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->goodsname, q->goodsname))
		{
			printf("�����Ѵ��ڣ����ʧ�ܣ�\n");
			return ERROR;
		}

		p = p->next;
	}
	p = *Head;				//����ָ��ͷ���
	printf("�����������ǳƣ�\n");
	scanf("%s", q->buyer);
	printf("�������ַ��\n");
	scanf("%s", q->address);
	strcpy(q->delivery, "δ����");
	q->ID = ++LID;

	/*�������޶������*/
	if (p->next == NULL)
	{
		p->next = q;
		p->next->next = NULL;		//���һ������ÿ�
	}

	/*���������ж���*/
	else
	{
		q->next = p->next;			//ͷ�巨
		p->next = q;
	}

	return SUCCESS;
}

Status ModifyOrder(MLinkedList M, ListOrder* Head)//�̼��޸Ķ���
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return AERROR;
	}
	if (M == NULL)
	{
		printf("��½ʧ�ܣ�\n");
		return AERROR;
	}

	Order* p = (* Head)->next;		//ָ���һ�����
	int a, flag, b;

	/*����ID*/
	printf("����������Ҫ�޸ĵĶ���ID:");
	while (1)
	{
		a = scanf_s("%d", &flag);
		if (a != 0)
		{
			if (!(flag >= 1))
			{
				printf("��������룬���������룡\n");
			}
			else break;
		}
		else
		{
			printf("��������֣����������룡\n");
			rewind(stdin);			//��������
		}
	}

	/*����������*/
	/*������Ʒ��*/
	while (p != NULL)
	{
		if (!(flag == p->ID))
		{
			printf("�ɹ��ҵ���\n");
			printf("�ö�����ϢΪ:\n");
			printf("�����ţ�%d\t", p->ID);
			printf("��Ʒ����%s\t\t", p->goodsname);
			printf("�������ǳƣ�%s\n", p->buyer);
			printf("��ַ��%s\n", p->address);
			printf("����״̬��%s\n", p->delivery);

			/*�޸���Ϣ*/
			printf("�Ƿ�ѡ�񷢻�?(1:yes/ 2:no)\n");
			if (scanf("%d", &b) == 1)
			{
				strcpy(p->delivery, "�ѷ���");
			}
			return SUCCESS;
		}
		p = p->next;
	}
	printf("�ö��������ڣ�\n");
	return AERROR;
}

Status SaveData_OrderEnd(ListOrder* Head)//�������ݲ��˳�//�ж��Ƿ�����ظ�����
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return AERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("�ö�����Ϊ�գ��޷��������ݣ�\n");
		return ERROR;
	}

	FILE* fp;
	fp = fopen("order.txt", "w+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return OVERFLOW;
	}
	fprintf(fp, "������");
	fprintf(fp, "\t");
	fprintf(fp, "��Ʒ��");
	fprintf(fp, "\t\t");
	fprintf(fp, "������");
	fprintf(fp, "\t\t");
	fprintf(fp, "��ַ");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "����״̬");
	fprintf(fp, "\n");

	Order* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, "%d", p->ID);
		fprintf(fp, "\t");
		fprintf(fp, p->goodsname);
		fprintf(fp, "\t\t");
		fprintf(fp, p->buyer);
		fprintf(fp, "\t\t");
		fprintf(fp, p->address);
		fprintf(fp, "\t\t\t");
		fprintf(fp, p->delivery);
		fprintf(fp, "\n");
	}

	printf("���ݴ���ɹ���\n");
	fclose(fp);
	return SUCCESS;
}