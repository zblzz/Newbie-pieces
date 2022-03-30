/***************************************************************************************
 *	File Name				:	good.h
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
#ifndef GOOD_H_INCLUDED
#define GOOD_H_INCLUDED
#include "lead.h"
#include "merchant.h"
#include "user.h"
#include "order.h"
/**************************************************************
*	Struct Define Section
**************************************************************/


/**************************************************************
*	Prototype Declare Section
**************************************************************/

/**
 *  @name        : Status InitGood_File(LinkedList* Head);
 *	@description : Create an empty linked list into a file
 *	@param		 : ListGood* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status InitGood_File(ListGood* Head);//��������������ļ���

/**
 *  @name        : Status AddGood(LinkedList* Head);
 *	@description : Add basic product information 
 *	@param		 : ListGood* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status AddGood(ListGood* Head);//�����Ʒ//β�巨

/**
 *  @name        : Status SaveData_GoodEnd(ListGood* Head);
 *	@description : Top up and check your balance
 *	@param		 : ListGood* Head
 *	@return		 : Status
 *  @notice      : None
 */
Status SaveData_GoodEnd(ListGood* Head);//�������ݲ��˳�//�ж��Ƿ�����ظ�����


#endif
