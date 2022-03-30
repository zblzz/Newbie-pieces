#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "lead.h"
#include "good.h"
#include "merchant.h"
#include "user.h"

LNode* L = NULL;	//用户头指针
LNode* U = NULL;	//登录用户结点
MLNode* M = NULL;	//商家头指针
MLNode* MU = NULL;	//登录商家结点
Goods* G = NULL;	//商品头指针
Order* O = NULL;	//订单头指针

void MainMenu(void);//主菜单
void UserMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//用户登录菜单
void LoginMenu(LinkedList L ,LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//用户菜单
void MerchantMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//商家菜单
void LoginMenu_Mer(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O);//商家用户菜单
void GoodMenu(ListGood G, MLinkedList MU);//商品菜单
void Use_OrderMenu(LinkedList U, ListOrder O);//用户订单菜单
void Mer_OrderMenu(MLinkedList MU, ListOrder O);//商家订单菜单

int main(void)
{
	/*为U分配空间，以储存登录成功的用户结点*/
	U = (LNode*)malloc(sizeof(LNode));
	if (U == NULL)
	{
		printf("内存分配失败！\n");
		exit(1);
	}

	//初始化
	InitList_File(&L);//用户
	InitGood_File(&G);//商品
	InitMerList_File(&M);//商家
	InitLOrder_File(&O);//订单
	system("pause");

	MainMenu();

	return 0;
}

void MainMenu(void)//主菜单
{
	int mode;
	int a;
	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t******************总界面********************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:用户登录界面\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:商家登录界面\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //黄
	printf("\t\t|---\t\t 3:退出\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	////设置文字属性：红亮

	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 3))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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
			CloseHandle(hdl); //要记得关闭Handle，释放 Handle 资源
			exit(0);
		default:
			break;
		}
	}

}

/****************************************
**
用户部分
**
****************************************/

void UserMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//登录菜单
{
	int mode;
	int a;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************用户登录界面***************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:注册账号\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:登录账号\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //黄
	printf("\t\t|---\t\t 3:找回密码\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);									//绿
	printf("\t\t|---\t\t 4:返回主菜单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//青
	printf("\t\t|---\t\t 5:清屏\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////设置文字属性：红亮



	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 5))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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

void LoginMenu(LinkedList L,LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//用户界面
{
	int a, mode;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************用户界面*******************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:余额查询以及充值\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:搜索商品\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//青
	printf("\t\t|---\t\t 3:购买商品\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //黄
	printf("\t\t|---\t\t 4:返回主菜单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////设置文字属性：红亮

	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 4))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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
商家部分
**
****************************************/
void MerchantMenu(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//商家菜单
{
	int mode;
	int a;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************商家登录界面***************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:注册商店\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:登录商店\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //黄
	printf("\t\t|---\t\t 3:找回密码\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN);									//绿
	printf("\t\t|---\t\t 4:返回主菜单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//青
	printf("\t\t|---\t\t 5:清屏\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////设置文字属性：红亮



	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 5))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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

void LoginMenu_Mer(LinkedList L, LinkedList U, ListGood* G, MLinkedList M, MLinkedList MU, ListOrder O)//商家用户菜单
{
	int a, mode;

	system("cls");

	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************商家用户界面***************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:商品添加\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:提现\t\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_BLUE);				//青
	printf("\t\t|---\t\t 3:订单发货以及修改\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY); //黄
	printf("\t\t|---\t\t 4:返回主菜单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////设置文字属性：红亮

	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 4))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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

void GoodMenu(ListGood G, MLinkedList MU)//商品菜单
{
	int a, mode;

	system("cls");
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t*****************商品界面*******************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:添加商品\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:返回主菜单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////设置文字属性：红亮

	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 2))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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

void Use_OrderMenu(LinkedList U, ListOrder O)//用户订单菜单
{
	int a, mode;

	system("cls");
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t***************用户订单界面*****************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:添加订单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:返回主菜单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////设置文字属性：红亮

	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 2))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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


void Mer_OrderMenu(MLinkedList MU, ListOrder O)//商家订单菜单
{
	int a, mode;

	system("cls");
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);   //获取控制台句柄

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t***************商家订单界面*****************\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED);									//红
	printf("\t\t|---\t\t 1:修改订单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_GREEN | BACKGROUND_RED);				//橙
	printf("\t\t|---\t\t 2:返回主菜单\t\t---|\n");

	SetConsoleTextAttribute(hdl, BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	printf("\t\t********************************************\n\n");

	SetConsoleTextAttribute(hdl, FOREGROUND_RED | FOREGROUND_INTENSITY);
	////设置文字属性：红亮

	while (1)
	{
		printf("请输入使用功能的序号:\n");
		while (1)
		{
			a = scanf_s("%d", &mode);
			if (a != 0)
			{
				if (!(mode >= 1 && mode <= 2))
				{
					printf("请别乱输入，请重新输入！\n");
				}
				else break;
			}
			else
			{
				printf("输入非数字，请重新输入！\n");
				rewind(stdin);			//清理缓存区
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