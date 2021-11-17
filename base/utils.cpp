/* 
 * @Author: fangqi
 * @Date: 2021-11-16 15:54:11
 * @LastEditors: fangqi
 * @LastEditTime: 2021-11-16 15:54:11
 * @Description: 通用工具函数
 * @Copyright(c) 2021 CMIM Network Co.,Ltd. All Rights Reserve
 */
#include "utils.h"
int getArrLength(int * arr) {
  return sizeof(arr) / sizeof(*arr);
}
