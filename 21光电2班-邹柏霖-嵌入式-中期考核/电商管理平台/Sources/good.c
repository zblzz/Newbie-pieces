#include "good.h"
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

Status InitGood_File(ListGood* Head)//��������������ļ���
{
	Goods* p;
	char buf[1024];				//������

	*Head = (Goods*)malloc(sizeof(Goods));		//��ͷ�������ڴ�
	if (*Head == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//ͷ�����һ������ÿ�
	p = *Head;					//��pָ��ͷ���

	/*�ļ�*/
	FILE* fp = fopen("good.txt", "r");
	if (fp == NULL)
	{
		printf("��Ʒ�ļ������ڣ����Զ�Ϊ��������\n");
		fp = fopen("good.txt", "w");
		if (fp == NULL)
		{
			printf("��Ʒ�ļ�����ʧ�ܣ�\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//��һ��ΪĿ¼����һ������

	while (1)
	{
		Goods* q;
		q = (Goods*)malloc(sizeof(Goods));
		if (q == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			return OVERFLOW;
		}

		/*���¼�����ݵ��ļ����Ƿ����*/
		if (fscanf(fp, "%s%lf%d%s", q->name, &q->price, &q->amount, q->belong) != 4)//�ɹ��󷵻�4�������¼�뵽���һ�����Ϊ�գ��˳�
		{
			free(q);			//¼��������Ϻ���շ�����ڴ�
			break;
		}

		/*�����Ʒ�Ƿ�����  ���Ϊ0*/
		if (q->amount == 0)
		{
			free(q);
			continue;
		}
		q->next = NULL;

		p->next = q;			//��ֵ���ý��
		p = q;					//��λ���¸����

	}

	printf("��Ʒ���ʼ���ɹ���\n");
	return SUCCESS;
}

Status AddGood(ListGood* Head)//�����Ʒ//ͷ�巨
{
	if (*Head == NULL)
	{
		printf("����Ʒ��δ��ʼ����\n");
		return ERROR;
	}
	Goods* p = *Head;		//ָ��ͷ���
	Goods* q;

	q = (Goods*)malloc(sizeof(Goods));
	if (q == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}

	/*��������*/
	printf("��������Ʒ����\n");
	scanf("%s", q->name);
	while (p->next != NULL)
	{
		if (!strcmp(p->next->name, q->name))
		{
			printf("��Ʒ�Ѵ��ڣ�����ʧ�ܣ�\n");
			return ERROR;
		}

		p = p->next;
	}
	p = *Head;				//����ָ��ͷ���
	printf("������۸�\n");
	scanf("%lf", &q->price);
	printf("�������棺\n");
	scanf("%d", &q->amount);
	printf("�����������̼ң�\n");
	scanf("%s", q->belong);

	/*��������ע����Ʒ*/
	if (p->next == NULL)
	{
		p->next = q;
		p->next->next = NULL;		//���һ������ÿ�
	}

	/*����������Ʒע��*/
	else
	{
		q->next = p->next;			//ͷ�巨
		p->next = q;
	}

	return SUCCESS;
}

Status SaveData_GoodEnd(ListGood* Head)//�������ݲ��˳�//�ж��Ƿ�����ظ�����
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("����Ʒ��Ϊ�գ��޷��������ݣ�\n");
		return ERROR;
	}

	FILE* fp;
	fp = fopen("good.txt", "w+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return OVERFLOW;
	}
	fprintf(fp, "��Ʒ��");
	fprintf(fp, "\t\t");
	fprintf(fp, "�۸�");
	fprintf(fp, "\t\t");
	fprintf(fp, "���");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "�����̼�");
	fprintf(fp, "\n");

	Goods* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, p->name);
		fprintf(fp, "\t\t");
		fprintf(fp, "%.2lf", p->price);
		fprintf(fp, "\t\t");
		fprintf(fp, "%d", p->amount);
		fprintf(fp, "\t\t\t");
		fprintf(fp, p->belong);
		fprintf(fp, "\n");
	}

	printf("���ݴ���ɹ���\n");
	fclose(fp);
	return SUCCESS;
}

