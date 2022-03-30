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
Status InitList_File(LinkedList* Head);//创建空链表放入文件中

/**
 *  @name        : Status Register(LinkedList* Head);
 *	@description : Registered user into a file
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : When there is no user in the table to register directly after the head node, 
				if there is, register at the end of the table 
 */
Status RegisterUser(LinkedList* Head);//注册用户//尾插法

/**
 *  @name        : Status RePassword(LinkedList* Head);
 *	@description : Retrieve the account password and select Change Password 
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status RePassword(LinkedList* Head);//找回密码

/**
 *  @name        : LNode* Login(LinkedList* Head);
 *	@description : Login function 
 *	@param		 : LinkedList* Head
 *	@return		 : LNode*
 *  @notice      : None
 */
LNode* Login(LinkedList* Head);//登录函数

/**
 *  @name        : Status SaveData_UserEnd(LinkedList* Head);
 *	@description : Save the data to the txt file and exit the program
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status SaveData_UserEnd(LinkedList* Head);//保存数据并退出

/**
 *  @name        : Status Charge(LinkedList* Head);
 *	@description : Top up and check your balance
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status Charge(LinkedList U);//充值并查看余额


/**
 *  @name        : Status Search(ListGood* Head);
 *	@description : Search Good and get its belong
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status Search(ListGood* Head);//搜索商品

/**
 *  @name        : Status Purchase(LinkedList U,ListGood* Head);
 *	@description : Purchase the good
 *	@param		 : LinkedList* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status Purchase(LinkedList U,ListGood* Head,MLinkedList M);//购买商品

/**
 *  @name        : void LoginMenu(LinkedList* Head, LinkedList U,MLinkedList MU);
 *	@description : Login menu
 *	@param		 : LinkedList U(User nodes),ListGood* GHead,MLinkedList MU
 *	@return		 : Status
 *  @notice      : None
 */


#endif