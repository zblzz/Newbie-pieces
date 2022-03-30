#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "lead.h"
#include "good.h"
#include "merchant.h"
#include "user.h"

LNode* L = NULL;	//�û�ͷָ��
LNode* U = NULL;	//��¼�û����
MLNode* M = NULL;	//�̼�ͷָ��
MLNode* MU = NULL;	//��¼�̼ҽ��
Goods* G = NULL;	//��Ʒͷָ��
Order* O = NULL;	//����ͷָ��

void MainMenu(void);//���˵�
void UserMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//�û���¼�˵�
void LoginMenu(LinkedList L ,LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//�û��˵�
void MerchantMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//�̼Ҳ˵�
void LoginMenu_Mer(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//�̼��û��˵�
void GoodMenu(ListGood G, MLinkedList MU);//��Ʒ�˵�
void Use_OrderMenu(LinkedList U, ListOrder O);//�û������˵�
void Mer_OrderMenu(MLinkedList MU, ListOrder O);//�̼Ҷ����˵�

int main(void)
{
	/*ΪU����ռ䣬�Դ����¼�ɹ����û����*/
	U = (LNode*)malloc(sizeof(LNode));
	if (U == NULL)
	{
		printf("�ڴ����ʧ�ܣ�\n");
		exit(1);
	}

	//��ʼ��
	InitList_File(&L);//�û�
	InitGood_File(&G);//��Ʒ
	InitMerList_File(&M);//�̼�
	InitLOrder_File(&O);//����
	system("pause");

	MainMenu();

	return 0;
}

void MainMenu(void)//���˵�
{
	int mode;
	int a;
	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t******************�ܽ���********************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:�û���¼����\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:�̼ҵ�¼����\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("\t\t|---\t\t 3:�˳�\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	////�����������ԣ�����

	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 3))
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

		switch (mode)
		{
		case 1:
			UserMenu(L, U, &G, M, MU, O);
			break;
		case 2:
			MerchantMenu(L, U, &G, M, MU, O);
			break;
		case 3:
			SaveData_UserEnd(&L);
			SaveData_MerEnd(&M);
			SaveData_GoodEnd(&G);
			SaveData_OrderEnd(&O);
			CloseHandle(hdl); //Ҫ�ǵùر�Handle���ͷ� Handle ��Դ
			exit(0);
		default:
			break;
		}
	}

}

/****************************************
**
�û�����
**
****************************************/

void UserMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//��¼�˵�
{
	int mode;
	int a;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************�û���¼����***************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:ע���˺�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:��¼�˺�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("\t\t|---\t\t 3:�һ�����\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);									//��
	printf("\t\t|---\t\t 4:�������˵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//��
	printf("\t\t|---\t\t 5:����\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////�����������ԣ�����



	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 5))
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

		switch (mode)
		{
		case 1:
			RegisterUser(&L);
			break;
		case 2:
			U = Login(&L);
			if (U)
			{
				Sleep(1000);

				LoginMenu(L, U, G, M, MU, O);
			}
			break;
		case 3:
			RePassword(&L);
			break;
		case 4:
			SaveData_UserEnd(&L);
			MainMenu();
		case 5:
			UserMenu(L, U, G, M, MU, O);
			break;
		default:
			break;
		}
	}


}

void LoginMenu(LinkedList L,LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//�û�����
{
	int a, mode;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************�û�����*******************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:����ѯ�Լ���ֵ\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:������Ʒ\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//��
	printf("\t\t|---\t\t 3:������Ʒ\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("\t\t|---\t\t 4:�������˵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////�����������ԣ�����

	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 4))
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

		switch (mode)
		{
		case 1:
			Charge(U);
			break;
		case 2:
			Search(G);
			break;
		case 3:
			Purchase(U, G, M);
			Use_OrderMenu(U,O);
			break;
		case 4:
			
			SaveData_UserEnd(&L);
			MainMenu();
		default:
			break;
		}
	}

}

/****************************************
**
�̼Ҳ���
**
****************************************/
void MerchantMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//�̼Ҳ˵�
{
	int mode;
	int a;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************�̼ҵ�¼����***************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:ע���̵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:��¼�̵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("\t\t|---\t\t 3:�һ�����\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);									//��
	printf("\t\t|---\t\t 4:�������˵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//��
	printf("\t\t|---\t\t 5:����\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////�����������ԣ�����



	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 5))
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

		switch (mode)
		{
		case 1:
			RegisterMer(&M);
			break;
		case 2:
			MU = Login_Mer(&M);
			if (MU)
			{
				Sleep(1000);
				LoginMenu_Mer(L, U, G, M, MU, O);
			}
			break;
		case 3:
			RePassword_Mer(&M);
			break;
		case 4:
			SaveData_MerEnd(&M);
			MainMenu();
		case 5:
			MerchantMenu(L, U, G, M, MU, O);
			break;
		default:
			break;
		}
	}
}

void LoginMenu_Mer(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//�̼��û��˵�
{
	int a, mode;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************�̼��û�����***************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:��Ʒ���\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:����\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//��
	printf("\t\t|---\t\t 3:���������Լ��޸�\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //��
	printf("\t\t|---\t\t 4:�������˵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////�����������ԣ�����

	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 4))
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

		switch (mode)
		{
		case 1:
			GoodMenu(*G, MU);
			break;
		case 2:
			Withdraw(MU);
			break;
		case 3:

			break;
		case 4:

			SaveData_MerEnd(&M);
			MainMenu();
		default:
			break;
		}
	}

}

void GoodMenu(ListGood G, MLinkedList MU)//��Ʒ�˵�
{
	int a, mode;

	system("cls");
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************��Ʒ����*******************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:�����Ʒ\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:�������˵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////�����������ԣ�����

	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 2))
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

		switch (mode)
		{
		case 1:
			AddGood(&G);
			break;
		case 2:
			
			SaveData_GoodEnd(&G);
			MainMenu();
		default:
			break;
		}
	}
}

void Use_OrderMenu(LinkedList U, ListOrder O)//�û������˵�
{
	int a, mode;

	system("cls");
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t***************�û���������*****************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:��Ӷ���\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:�������˵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////�����������ԣ�����

	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 2))
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

		switch (mode)
		{
		case 1:
			User_AddOrder(&O, U);
			break;
		case 2:

			SaveData_OrderEnd(&O);
			MainMenu();
		default:
			break;
		}
	}
}


void Mer_OrderMenu(MLinkedList MU, ListOrder O)//�̼Ҷ����˵�
{
	int a, mode;

	system("cls");
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //��ȡ����̨���

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t***************�̼Ҷ�������*****************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//��
	printf("\t\t|---\t\t 1:�޸Ķ���\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//��
	printf("\t\t|---\t\t 2:�������˵�\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////�����������ԣ�����

	while (1)
	{
		printf("������ʹ�ù��ܵ����:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 2))
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

		switch (mode)
		{
		case 1:
			ModifyOrder( MU, &O);
			break;
		case 2:

			//SaveData_OrderEnd(&O);
			MainMenu();
		default:
			break;
		}
	}
}