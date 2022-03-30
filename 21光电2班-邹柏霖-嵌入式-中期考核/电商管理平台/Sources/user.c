#include "user.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>


Status InitList_File(LinkedList* Head)//��������������ļ���//ͷ��㲻������
{
	LNode* p;
	char buf[1024];				//������

	*Head = (LNode *)malloc(sizeof(LNode));		//��ͷ�������ڴ�
	if (*Head == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		return OVERFLOW;
	}
	(*Head)->next = NULL;		//ͷ�����һ������ÿ�
	p = *Head;					//��pָ��ͷ���
			
	/*�ļ�*/
	FILE* fp = fopen("user.txt", "r");		
	if (fp == NULL)
	{
		printf("�û��ļ������ڣ����Զ�Ϊ��������\n");
		fp = fopen("user.txt", "w");
		if (fp == NULL)
		{
			printf("�û��ļ�����ʧ�ܣ�\n");
			return OVERFLOW;
		}
	}
	fgets(buf, 1024, fp);			//��һ��ΪĿ¼����һ������

	while (1)
	{
		LNode* q;
		q = (LNode*)malloc(sizeof(LNode));
		if (q == NULL)
		{
			printf("�ڴ����ʧ�ܣ�\n");
			return OVERFLOW;
		}

		/*���¼�����ݵ��ļ����Ƿ����*/
		if (fscanf(fp, "%s%s%s%lf", q->name, q->password, q->phone,&q->money) != 4)	//�ɹ��󷵻�4�������¼�뵽���һ�����Ϊ�գ��˳�
		{
			free(q);			//¼��������Ϻ���շ�����ڴ�
			break;
		}
		q->next = NULL;

		p->next = q;			//��ֵ���ý��
		p = q;					//��λ���¸����

	}

	printf("�û����ʼ���ɹ���\n");
	return SUCCESS;
}

Status RegisterUser(LinkedList* Head)//ע���û�//ͷ�巨
{
	if (*Head == NULL)
	{
		printf("���û���δ��ʼ����\n");
		return ERROR;
	}
	LNode* p = *Head;		//ָ��ͷ���
	LNode* q;

	q = (LNode*)malloc(sizeof(LNode));
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
			printf("�û����Ѵ��ڣ�ע��ʧ�ܣ�\n");
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
	q->money = 0;			//���û����Ϊ0

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

Status RePassword(LinkedList* Head)//�һ�����
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return ERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("���û�ע�ᣡ\n");
		return ERROR;
	}

	char phoneID[20] = { 0 };
	LNode* p = (*Head)->next;

	printf("������Ҫ����������û����ֻ��ţ�\n");
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
				printf("���ǳ�Ϊ��%s\n", p->name);
				return SUCCESS;

			}
			p = p->next;//ָ����һ�����

		}
		printf("���ֻ���δע�ᣡ\n");
		break;
	}
	return SUCCESS;
}

LNode* Login(LinkedList* Head)//��¼
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return NULL;
	}
	if ((*Head)->next == NULL)
	{
		printf("���û�ע��\n");
		return NULL;
	}


	LNode* p;		//ָ���һ�����
	p = (LNode*)malloc(sizeof(LNode));
	p = (*Head)->next;

    char names[20] = { 0 };
	char pass[20] = { 0 };

	/*��������*/
	printf("����������ǳƣ�\n");
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
	
	printf("�û������ڣ�");
	return NULL;
}

Status SaveData_UserEnd(LinkedList* Head)//�������ݲ��˳�//�ж��Ƿ�����ظ�����
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
	fp = fopen("user.txt", "w+");
	if (fp == NULL)
	{
		printf("�ļ���ʧ�ܣ�\n");
		return OVERFLOW;
	}
	fprintf(fp, "�ǳ�");
	fprintf(fp, "\t\t");
	fprintf(fp, "����");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "�ֻ���");
	fprintf(fp, "\t\t\t");
	fprintf(fp, "���");
	fprintf(fp, "\n");

	LNode* p = *Head;

	while (p->next != NULL)
	{
		p = p->next;
		fprintf(fp, p->name);
		fprintf(fp, "\t\t");
		fprintf(fp, p->password);
		fprintf(fp, "\t\t\t");
		fprintf(fp, p->phone);
		fprintf(fp, "\t\t\t");
		fprintf(fp, "%.2lf",p->money);
		fprintf(fp, "\n");
	}

	printf("���ݴ���ɹ���\n");
	fclose(fp);
	return SUCCESS;
}

Status Charge(LinkedList U)//��ֵ���鿴���
{
	int flag;
	int a;
	double money;

	printf("1.�鿴���\n");
	printf("2.��ֵ\n");
	printf("3.�˳�\n");
	printf("�����빦�ܱ�ţ�");
	while (1)
	{
		while (1)
		{
			a = scanf_s("%d", &flag);
			if (a != 0)
			{
				if (!(flag >= 1 && flag <= 3))
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
		
		switch (flag)
		{
		case 1:
			/*�鿴���*/
			printf("��ǰ���Ϊ%.2lf\n", U->money);
			goto end;
		case 2:
			/*��ֵ*/
			printf("����������Ҫ��ֵ�Ľ�");
			while (1)
			{
				a = scanf_s("%lf", &money);
				if (a != 0)
				{
					if (money <= 0)
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
			printf("��ֵ�ɹ���\n");
			U->money = U->money + money;
			printf("��ǰ���Ϊ��%.2lf\n", U->money);
			goto end;
		case 3:
			goto end;
		default:
			break;
		}
	}
end:
	return SUCCESS;
}

Status Search(ListGood* Head)//������Ʒ
{
	if (*Head == NULL)
	{
		printf("δ��ʼ�������ʼ����\n");
		return AERROR;
	}
	if ((*Head)->next == NULL)
	{
		printf("����Ʒ��Ϊ�գ��޷�������Ʒ��\n");
		return AERROR;
	}

	char name[20] = {0};
	Goods* p = (*Head)->next;			//ָ���һ�����

	while (1)
	{
		printf("��������Ʒ�����֣�\n");
		scanf("%s", name);

		/*������Ʒ��*/
		while (p != NULL)
		{
			if (!strcmp(p->name,name))
			{
				printf("�ɹ��ҵ���\n");
				printf("����Ʒ��ϢΪ:\n");
				printf("��Ʒ����%s\t\t", (p->name));
				printf("�۸�%.2lf\t\t", p->price);
				printf("��棺%d\n", p->amount);
				printf("��Ϣ��%s\n", (p->belong));

				return SUCCESS;
			}
			p = p->next;
		}
		printf("��Ʒ������\n");
		break;
	}
	
	return SUCCESS;
}

Status Purchase(LinkedList U, ListGood* Head, MLinkedList M)//������Ʒ
{
	/*�ж����*/
	if (!(U->money > 0))
	{
		printf("�Բ����������㣡\n");
		return AERROR;
	}

	if (M == NULL)
	{
		printf("���̼�ע�ᣬ�޷����ף�\n");
		return AERROR;
	}
	if (*Head == NULL)
	{
		printf("��Ʒ��Ϊ�գ��޷�����\n");
		return AERROR;
	}
	printf("��ǰ���Ϊ��%.2lf\n", U->money);

	int flag,a;
	char name[20] = { 0 };
	Goods* p = (*Head)->next;			//��Ʒָ���һ�����
	MLNode* g = M->next;				//�̼�ָ���һ�����

	/*ѡ����Ʒ*/
	while (1)
	{
		printf("��������Ʒ�����֣�\n");
		scanf("%s", name);

		/*������Ʒ��*/
		while (p != NULL)
		{
			if (!strcmp(p->name, name))
			{
				printf("�ɹ��ҵ���\n");
				printf("����Ʒ��ϢΪ:\n");
				printf("��Ʒ����%s\t\t", (p->name));
				printf("�۸�%.2lf\t\t", p->price);
				printf("��棺%d\n", p->amount);
				printf("�����̼ң�%s\n", (p->belong));

				break;
			}
			p = p->next;
		}

		if (p != NULL)//�ҵ���Ʒ
		{
			break;
		}
		else//��Ʒ������
		{
			printf("��Ʒ������!\n");
			return AERROR;
		}
	}
	//��ʱpָ��ѡ�����Ʒ

	/*�ҵ������̼�*/
	while (M != NULL)
	{
		if (!strcmp(p->belong, M->name))
		{
			break;
		}
		M = M->next;//ָ���¸����
		if ( M == NULL)
		{
			printf("����\n");
			return AERROR;
		}
	}

	//��ʱpָ��ѡ�����Ʒ
	//��ʱMָ����Ʒ�������̼�

	/*������Ʒ*/
	printf("�Ƿ�ѡ����?(1:yes/ 2:no)\n");
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
		if (U->money >= p->price)
		{
			printf("����ɹ���\n");
			p->amount-- ;					   //����һ
			U->money = (U->money) - (p->price);//�û�������
			M->money = M->money + (p->price);  //�̼��������
			M->orders++;					   //��������һ
			printf("��ǰ���Ϊ��%.2lf\n", U->money);
			printf("��ӭ�´ι��٣�\n");
			return SUCCESS;
		}
		else
		{
			printf("��ǰ���㣬����ʧ�ܣ�\n");
			return SUCCESS;
		}
	}
	else
	{
		printf("��ӭ�´ι��٣�\n");
		return SUCCESS;
	}
}

