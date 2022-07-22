#pragma once
/******************************************************************************/
/* File   : NvM.hpp                                                           */
/* Author : NAGARAJA HM (c) since 1982. All rights reserved.                  */
/******************************************************************************/

/******************************************************************************/
/* #INCLUDES                                                                  */
/******************************************************************************/
#include "ConstNvM.hpp"
#include "CfgNvM.hpp"
#include "NvM_core.hpp"
#include "infNvM_Exp.hpp"

/******************************************************************************/
/* #DEFINES                                                                   */
/******************************************************************************/

/******************************************************************************/
/* MACROS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* TYPEDEFS                                                                   */
/******************************************************************************/
class module_NvM:
      INTERFACES_EXPORTED_NVM
      public abstract_module
   ,  public class_NvM_Functionality
{
   private:
/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
      const ConstNvM_Type* lptrConstNvM;

   public:
/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/
      FUNC(void, NVM_CODE) InitFunction(
         CONSTP2CONST(CfgModule_TypeAbstract, NVM_CONFIG_DATA, NVM_APPL_CONST) lptrCfgModule
      );
      FUNC(void, NVM_CODE) DeInitFunction (void);
      FUNC(void, NVM_CODE) MainFunction   (void);
      NVM_CORE_FUNCTIONALITIES
};

/******************************************************************************/
/* CONSTS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* PARAMS                                                                     */
/******************************************************************************/

/******************************************************************************/
/* OBJECTS                                                                    */
/******************************************************************************/
extern VAR(module_NvM, NVM_VAR) NvM;

/******************************************************************************/
/* EOF                                                                        */
/******************************************************************************/
