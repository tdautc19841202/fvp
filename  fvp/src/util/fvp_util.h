/*
 * File: fvp_function.h
 * Author:  zhoumin  <dcdcmin@gmail.com>
 * Brief:   
 *
 * Copyright (c) 2010 - 2013  zhoumin <dcdcmin@gmail.com>>
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2011-01-25 zhoumin <dcdcmin@gmail.com> created
 *
 */
#include"fvp_common.h"
#include"fvp_typedef.h"
#include<pthread.h>

#ifndef FVP_UTIL_H
#define FVP_UTIL_H


#ifdef __cplusplus 
extern "C"{
#endif

typedef void *(*ThreadFunction)(void *para);

int fvp_create_normal_thread(ThreadFunction function, void *para, pthread_t *pid);
void fvp_msleep(unsigned int milli_second);
int fvp_get_file_size(char *file_name);
size_t fvp_get_relative_time(void);

#ifdef __cplusplus
}
#endif

#endif/*__FVP_UTIL_H*/
