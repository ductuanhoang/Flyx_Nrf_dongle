/** @file:    vsm_rise_compute.c
 *  @details: Calclulate rise value between two points
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
#include "vsm_rise_compute.h"

/************************** Constant Definitions *****************************/

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

/********************** Internal Function Prototypes *************************/

/************************** Variable Definitions *****************************/

/********************* Exported Function Definitions *************************/
/**
 * @brief      Calculate Rise (lineration)
 *
 * @param[in]  x     input
 * @param[in]  x1    The x 1
 * @param[in]  y1    The y 1
 * @param[in]  x2    The x 2
 * @param[in]  y2    The y 2
 *
 * @return     { description_of_the_return_value }
 */
int32_t vsm_rise_compute(int32_t x,
                        int32_t x1,
                        int32_t y1,
                        int32_t x2,
                        int32_t y2)
{

   int32_t compute_value = 0;
/*%C y = (x - x1) * (y2 -y1) / (x2-x1) + y1     */
/*%C Rise compute       */
   compute_value = (x - x1) * (y2 - y1);
   compute_value = compute_value  / (x2 - x1);
   compute_value = compute_value + y1;

/*%C Saturation       */
   if (y2 < y1)
   {
      compute_value = saturation(compute_value,
                           y2,
                           y1);
   }
   else
   {
      compute_value = saturation(compute_value,
                           y1,
                           y2);
   }

   return(compute_value);
}
/********************* Internal Function Definitions *************************/

/*****************************************************************************/
