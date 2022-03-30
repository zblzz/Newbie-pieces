/***************************************************************************************
 *	File Name				:	user.h
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
#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include "lead.h"
#include "good.h"
#include "merchant.h"
#include "order.h"
/**************************************************************
*	Macro Define Section
**************************************************************/



/**************************************************************
*	Struct Define Section
**************************************************************/


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : Status InitList_File(LinkedList* Head);
 *	@description : Create an empty linked list into a file 
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_File(LinkedList* Head);//��������������ļ���

/**
 *  @name        : Status Register(LinkedList* Head);
 *	@description : Registered user into a file
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : When there is no user in the table to register directly after the head node, 
				if there is, register at the end of the table 
 */
Status RegisterUser(LinkedList* Head);//ע���û�//β�巨

/**
 *  @name        : Status RePassword(LinkedList* Head);
 *	@description : Retrieve the account password and select Change Password 
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status RePassword(LinkedList* Head);//�һ�����

/**
 *  @name        : LNode* Login(LinkedList* Head);
 *	@description : Login function 
 *	@param		 : LinkedList* Head
 *	@return		 : LNode*
 *  @notice      : None
 */
LNode* Login(LinkedList* Head);//��¼����

/**
 *  @name        : Status SaveData_UserEnd(LinkedList* Head);
 *	@description : Save the data to the txt file and exit the program
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status SaveData_UserEnd(LinkedList* Head);//�������ݲ��˳�

/**
 *  @name        : Status Charge(LinkedList* Head);
 *	@description : Top up and check your balance
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status Charge(LinkedList U);//��ֵ���鿴���


/**
 *  @name        : Status Search(ListGood* Head);
 *	@description : Search Good and get its belong
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status Search(ListGood* Head);//������Ʒ

/**
 *  @name        : Status Purchase(LinkedList U,ListGood* Head);
 *	@description : Purchase the good
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status Purchase(LinkedList U,ListGood* Head,MLinkedList M);//������Ʒ

/**
 *  @name        : void LoginMenu(LinkedList* Head, LinkedList U,MLinkedList MU);
 *	@description : Login menu
 *	@param		 : LinkedList U(User nodes),ListGood* GHead,MLinkedList MU
 *	@return		 : Status
 *  @notice      : None
 */


#endif