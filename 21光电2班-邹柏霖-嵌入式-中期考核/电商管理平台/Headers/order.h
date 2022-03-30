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
#ifndef ORDER_H_INCLUDED
#define ORDER_H_INCLUDED
#include "lead.h"
#include "good.h"
#include "merchant.h"
#include "user.h"
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
 *  @name        : Status InitLOrder_File(ListOrder* Head);
 *	@description : Create an empty linked list into a file
 *	@param		 : ListOrder* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status InitLOrder_File(ListOrder* Head);//订单初始化

/**
 *  @name        : Status User_AddOrder(ListOrder* Head, LinkedList U);
 *	@description : The user adds an order
 *	@param		 : ListOrder* Head, LinkedList U
 *	@return		 : Status
 *  @notice      : None
 */
Status User_AddOrder(ListOrder* Head, LinkedList U);//用户添加订单//头插法

/**
 *  @name        : Status ModifyOrder(MLinkedList M, ListOrder* Head);
 *	@description : Merchant modify the order
 *	@param		 : MLinkedList M, ListOrder* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status ModifyOrder(MLinkedList M, ListOrder* Head);//商家修改订单


/**
 *  @name        : Status SaveData_OrderEnd(ListOrder* Head);
 *	@description : Save the data to the txt file and exit the program
 *	@param		 : ListOrder* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status SaveData_OrderEnd(ListOrder* Head);//保存数据并退出//判断是否出现重复数据
#endif