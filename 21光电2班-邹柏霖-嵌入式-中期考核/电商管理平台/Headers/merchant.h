/***************************************************************************************
 *	File Name				:	merchant.h
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
#ifndef MERCHANT_H_INCLUDED
#define MERCHANT_H_INCLUDED
#include "lead.h"
#include "good.h"
#include "user.h"
#include "order.h"
/**************************************************************
*	Struct Define Section
**************************************************************/

#define TAXI  0.1		//提现税率

/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : Status InitMerList_File(MLinkedList* Head);
 *	@description : Create an empty linked list into a file
 *	@param		 : MLinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status InitMerList_File(MLinkedList* Head);//创建空链表放入文件中

/**
 *  @name        : Status RegisterMer(MLinkedList* Head);
 *	@description : Registered merchant into a file
 *	@param		 : MLinkedList* Head
 *	@return		 : Status
 *  @notice      : When there is no user in the table to register directly after the head node,
				if there is, register at the end of the table
 */
Status RegisterMer(MLinkedList* Head);//注册商家//尾插法

/**
 *  @name        : Status RePassword_Mer(MLinkedList* U);
 *	@description : Retrieve the account password and select Change Password
 *	@param		 : MLinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status RePassword_Mer(MLinkedList* Head);//找回密码

/**
 *  @name        : LNode* Login_Mer(MLinkedList* Head);
 *	@description : Login function
 *	@param		 : MLinkedList* Head
 *	@return		 : MLNode*
 *  @notice      : None
 */
MLNode* Login_Mer(MLinkedList* Head);//登录函数

/**
 *  @name        : Status SaveData_MerEnd(LinkedList* Head);
 *	@description : Save the data to the txt file and exit the program
 *	@param		 : MLinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status SaveData_MerEnd(MLinkedList* Head);//保存数据并退出


/**
 *  @name        : Status Withdraw(MLinkedList* Head);
 *	@description : The merchant withdraws the amount proportionally 
 *	@param		 : MLinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status Withdraw(MLinkedList MU);//提现

#endif