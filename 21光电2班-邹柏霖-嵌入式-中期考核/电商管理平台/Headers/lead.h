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

// �û�
typedef struct LNode {
	char name[20];						//�ǳ�
	char password[20];					//����
	char phone[20];						//�ֻ���(�����һ�����)
	double money;						//�ʽ�
	struct LNode* next;
} LNode, * LinkedList;

// �̼�
typedef struct MLNode {
	char name[20];						//�̼���
	char password[20];					//����
	char phone[20];						//�ֻ���(�����һ�����)
	double income;						//����
	double money;						//���
	int orders;							//������
	struct MLNode* next;
} MLNode, * MLinkedList;

// ��Ʒ
typedef struct Goods {
	char name[20];						//��Ʒ��
	double price;						//�۸�
	int amount;							//���
	char belong[40];					//�����̼�
	struct Goods* next;
}Goods, * ListGood;

// ����
typedef struct Order {
	int ID;								//������
	char goodsname[20];					//��Ʒ��
	char buyer[20];						//�������ǳ�
	char address[30];					//��ַ
	char delivery[20];					//�Ƿ񷢻� //�̼ҿ��޸ģ����ֻ��
	struct Order* next;
}Order, *ListOrder;

#endif