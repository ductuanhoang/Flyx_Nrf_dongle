/** @file:    vsm_saturation.c
 *  @details: Value limitation
 *
 *
 *
 * THE SOURCE CODE AND ITS RELATED DOCUMENTATION IS PROVIDED "AS IS". VINSMART
 * JSC MAKES NO OTHER WARRANTY OF ANY KIND, WHETHER EXPRESS, IMPLIED OR,
 * STATUTORY AND DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF MERCHANTABILITY,
 * SATISFACTORY QUALITY, NON INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * THE SOURCE CODE AND DOCUMENTATION MAY INCLUDE ERRORS. VINSMART JSC
 * RESERVES THE RIGHT TO INCORPORATE MODIFICATIONS TO THE SOURCE CODE IN LATER
 * REVISIONS OF IT, AND TO MAKE IMPROVEMENTS OR CHANGES IN THE DOCUMENTATION OR
 * THE PRODUCTS OR TECHNOLOGIES DESCRIBED THEREIN AT ANY TIME.
 *
 * VINSMART JSC SHALL NOT BE LIABLE FOR ANY DIRECT, INDIRECT OR
 * CONSEQUENTIAL DAMAGE OR LIABILITY ARISING FROM YOUR USE OF THE SOURCE CODE OR
 * ANY DOCUMENTATION, INCLUDING BUT NOT LIMITED TO, LOST REVENUES, DATA OR
 * PROFITS, DAMAGES OF ANY SPECIAL, INCIDENTAL OR CONSEQUENTIAL NATURE, PUNITIVE
 * DAMAGES, LOSS OF PROPERTY OR LOSS OF PROFITS ARISING OUT OF OR IN CONNECTION
 * WITH THIS AGREEMENT, OR BEING UNUSABLE, EVEN IF ADVISED OF THE POSSIBILITY OR
 * PROBABILITY OF SUCH DAMAGES AND WHETHER A CLAIM FOR SUCH DAMAGE IS BASED UPON
 * WARRANTY, CONTRACT, TORT, NEGLIGENCE OR OTHERWISE.
 *
 * (C)Copyright VINSMART JSC 2020 All rights reserved
 ******************************************************************************/

/***************************** Include Files *********************************/
#include <stdint.h>
#include "vsm_saturation.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/********************** Internal Function Prototypes *************************/

/************************** Variable Definitions *****************************/

/********************* Exported Function Definitions *************************/
/**
 * @brief      Value limitation
 *
 * @param[in]  value      The value
 * @param[in]  min_value  The minimum value
 * @param[in]  max_value  The maximum value
 *
 * @return     The limited value
 */
int32_t saturation(int32_t value,
                   int32_t min_value,
                   int32_t max_value)
{

   int32_t ret = 0;

   if (value > max_value)
    {
       ret = max_value;
    }
   else if (value < min_value)
    {
       ret = min_value;
    }
   else
    {
       ret = value;
    }

   return(ret);
}
/********************* Internal Function Definitions *************************/

/*****************************************************************************/
