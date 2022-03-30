#include "merchant.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>

Status InitMerList_File(MLinkedList* Head)//��������������ļ���//ͷ��㲻������
{
	MLNode* p;
	char buf[1024];				//������

	*Head = (MLNode*)malloc(sizeof(MLNode));		//��ͷ�������ڴ�
	if (*Head == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//ͷ�����һ������ÿ�
	p = *Head;					//��pָ��ͷ���

	/*�ļ�*/
	FILE* fp = fopen("merchant.txt", "r");
	if (fp == NULL)
	{
		printf("�̼��ļ������ڣ����Զ�Ϊ��������\n");
		fp = fopen("merchant.txt", "w");
		if (fp == NULL)
		{
			printf("�̼��ļ�����ʧ�ܣ�\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//��һ��ΪĿ¼����һ������

	while (1)
	{
		MLNode* q;
		q = (MLNode*)malloc(sizeof(MLNode));
		if (q == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			return OVERFLOW;
		}

		/*���¼�����ݵ��ļ����Ƿ����*/
		if (fscanf(fp, "%s%s%s%lf%lf%d", q->name, q->password, q->phone, &q->income,&q->money, &q->orders) != 6)	//�ɹ��󷵻�6�������¼�뵽���һ�����Ϊ�գ��˳�
		{
			free(q);			//¼��������Ϻ���շ�����ڴ�
			break;
		}
		q->next = NULL;

		p->next = q;			//��ֵ���ý��
		p = q;					//��λ���¸����

	}

	printf("�̼ұ��ʼ���ɹ���\n");
	return SUCCESS;
}

Status RegisterMer(MLinkedList* Head)//ע���û�//ͷ�巨
{
	if (*Head == NULL)
	{
		printf("���û���δ��ʼ����\n");
		return ERROR;
	}
	MLNode* p = *Head;		//ָ��ͷ���
	MLNode* q;

	q = (MLNode*)malloc(sizeof(MLNode));
	if (q == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}

	/*��������*/
	printf("�������ǳƣ�\n");
	scanf("%s", q->name);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->name, q->name))
		{
			printf("�̼����Ѵ��ڣ�ע��ʧ�ܣ�\n");
			return ERROR;
		}

		p = p->next;
	}
	p = *Head;				//����ָ��ͷ���
	printf("���������룺\n");
	scanf("%s", q->password);
	printf("�������ֻ��ţ�\n");
	scanf("%s", q->phone);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->phone, q->phone))
		{
			printf("�ֻ�����ע�����ע��ʧ�ܣ�\n");
			return ERROR;
		}

		p = p->next;
	}
	p = *Head;				//����ָ��ͷ���
	q->income = 0;			//���û����Ϊ0
	q->money = 0;			
	q->orders = 0;			

	/*��������ע���û�*/
	if (p->next == NULL)
	{
		p->next = q;
		p->next->next = NULL;		//���һ������ÿ�
	}

	/*���������û�ע��*/
	else
	{
		q->next = p->next;			//ͷ�巨
		p->next = q;
	}

	return SUCCESS;
}

Status RePassword_Mer(MLinkedList* Head)//�һ�����
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("���̼�ע�ᣡ\n");
		return ERROR;
	}

	char phoneID[20] = { 0 };
	MLNode* p = (*Head)->next;

	printf("������Ҫ���ҵ�������ֻ��ţ�\n");
	scanf("%s", phoneID);

	/*����*/
	while (1)
	{
		while (p != NULL)
		{
			if (!(strcmp(phoneID, p->phone)))
			{
				printf("�ҵ����룡\n");
				printf("������Ϊ��%s\n", p->password);
				printf("���̼���Ϊ��%s\n", p->name);
				return SUCCESS;

			}
			p = p->next;//ָ����һ�����

		}
		printf("���ֻ���δע�ᣡ\n");
		break;
	}
	return ERROR;
}

MLNode* Login_Mer(MLinkedList* Head)//��¼
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return NULL;
	}
	if ((*Head)->next == NULL)
	{
		printf("���̼�ע��\n");
		return NULL;
	}


	MLNode* p;		//ָ���һ�����
	p = (MLNode*)malloc(sizeof(MLNode));
	p = (*Head)->next;

	char names[20] = { 0 };
	char pass[20] = { 0 };

	/*��������*/
	printf("����������̼�����\n");
	scanf("%s", names);
	printf("������������룺\n");
	scanf("%s", pass);

	while (p != NULL)
	{
		if ((strcmp(p->name, names) && strcmp(p->password, pass)) == 0)
		{
			printf("��½�ɹ���\n");
			return p;
		}

		p = p->next;
	}

	printf("�̼һ������ڣ�");
	return NULL;
}

Status SaveData_MerEnd(MLinkedList* Head)//�������ݲ��˳�//�ж��Ƿ�����ظ�����
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("���û���Ϊ�գ��޷��������ݣ�\n");
		return ERROR;
	}

	FILE* fp;
	fp = fopen("merchant.txt", "w+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return OVERFLOW;
	}
	fprintf(fp, "�̼���");
	fprintf(fp, "\t\t");
	fprintf(fp, "����");
	fprintf(fp, "\t\t");
	fprintf(fp, "�ֻ���");
	fprintf(fp, "\t\t");
	fprintf(fp, "����");
	fprintf(fp, "\t\t");
	fprintf(fp, "���");
	fprintf(fp, "\t\t");
	fprintf(fp, "������");
	fprintf(fp, "\n");

	MLNode* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, p->name);
		fprintf(fp, "\t\t");
		fprintf(fp, p->password);
		fprintf(fp, "\t\t");
		fprintf(fp, p->phone);
		fprintf(fp, "\t\t");
		fprintf(fp, "%.2lf", p->income);
		fprintf(fp, "\t\t");
		fprintf(fp, "%.2lf", p->money);
		fprintf(fp, "\t\t");
		fprintf(fp, "%d", p->orders);
		fprintf(fp, "\n");
	}

	printf("���ݴ���ɹ���\n");
	fclose(fp);
	return SUCCESS;
}

Status Withdraw(MLinkedList MU)//����
{
	if (MU == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return AERROR;
	}
	/*�ж�����*/
	if (!(MU->income > 100))
	{
		printf("�Բ����������治�������֣�\n");
		printf("����޶��100 ��\n");
		return AERROR;
	}

	double taxi = TAXI;
	double one = 1;
	int flag;
	int a;

	printf("��������Ϊ��%.2lf\n", MU->income);
	printf("��ǰ˰��Ϊ��%lf", taxi);
	printf("�Ƿ�ѡ������?(1:yes/ 2:no)\n");
	while (1)
	{
		a = scanf_s("%d", &flag);
		if (a != 0)
		{
			if (!(flag >= 1 && flag <= 2))
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
	if (flag == 1)
	{
		MU->money = (MU->income) * (one-taxi);	//���ּ���
		MU->income = 0;
		printf("���ֳɹ���\n");
		return SUCCESS;
	}
	printf("���ֹ������˳���\n");
	return SUCCESS;
}