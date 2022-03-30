/***************************************************************************************
 *	File Name				:	lead.h
 *	CopyRight				:	zbl
 *	SYSTEM					:   win11
 *	Create Data				:	2022.3.27
 *
 *
 *--------------------------------Revision History--------------------------------------
 *	No	version		Data			Revised By			Item			Description
 *
 *
 ***************************************************************************************/

 /**************************************************************
*	Multi-Include-Prevent Section
**************************************************************/
#ifndef LEAD_H_INCLUDED
#define LEAD_H_INCLUDED

/**************************************************************
*	Prototype Declare Section
**************************************************************/
int LID ;

/**************************************************************
*	Struct Define Section
**************************************************************/
// define Status
typedef enum Status {
	OVERFLOW = -1,
	AERROR = 0,
	SUCCESS = 1
} Status;

// 用户
typedef struct LNode {
	char name[20];						//昵称
	char password[20];					//密码
	char phone[20];						//手机号(用于找回密码)
	double money;						//资金
	struct LNode* next;
} LNode, * LinkedList;

// 商家
typedef struct MLNode {
	char name[20];						//商家名
	char password[20];					//密码
	char phone[20];						//手机号(用于找回密码)
	double income;						//收益
	double money;						//余额
	int orders;							//订单数
	struct MLNode* next;
} MLNode, * MLinkedList;

// 商品
typedef struct Goods {
	char name[20];						//商品名
	double price;						//价格
	int amount;							//库存
	char belong[40];					//所属商家
	struct Goods* next;
}Goods, * ListGood;

// 订单
typedef struct Order {
	int ID;								//订单号
	char goodsname[20];					//商品名
	char buyer[20];						//购买者昵称
	char address[30];					//地址
	char delivery[20];					//是否发货 //商家可修改，买家只读
	struct Order* next;
}Order, *ListOrder;

#endif