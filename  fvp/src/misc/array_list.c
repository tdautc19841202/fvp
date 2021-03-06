/*
 * File: alarm_list.c
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
 * 2011-01-05 zhoumin <dcdcmin@gmail.com> created
 *
 */
#include<stdio.h>
#include<stdlib.h>
#include"array_list.h"

struct _List;
typedef struct _List List;

struct _List{
	List *next;
	void *data;
};

struct _ArrayList
{
	int array_list_number; 
	List *header;
};

static List *list_node_create(void *data)
{
	return_val_if_fail(data, NULL);
	
	List *list = (List *)COMM_ZALLOC(sizeof(List));
	
	list->data = data;
	list->next = NULL;

	return list;	
}

ArrayList *array_list_create()
{
	ArrayList *array_list = NULL;
	array_list = (ArrayList *)COMM_ZALLOC(sizeof(ArrayList));
	if(array_list == NULL)
	{
            msg_dbg("Fun[%s]error : not enough memory!\n", __func__);
	}
	
	return array_list;
}

int array_list_add(ArrayList *thiz, void *data)
{
	return_val_if_fail(thiz && data, -1);

	List *p = NULL;	
	List *current = NULL;	

	p = thiz->header;
	if(p == NULL)
	{
		thiz->header = list_node_create(data);
	}
	else
	{
		while(p)
		{
			current = p;
			p = p->next;
		}
		p = list_node_create(data);	
		current->next = p;
	}

	thiz->array_list_number++;

	return 0;
}

int array_list_remove(ArrayList *thiz, void *data, int data_size)
{
	return_val_if_fail(thiz && data && data_size > 0, -1);

	List *p = thiz->header;

	List *prev = p;
	while(p)
	{
		if((p->data) && (memcmp(p->data, data, data_size) == 0))
		{
			if( p == thiz->header)
			{
				p = NULL;
			}
			else
			{
				prev->next = p->next;
			}
			thiz->array_list_number--;
			return 0;
		}
		prev = p;
		p = p->next;		
	}
	
	return -1;
}	

int array_list_get_id_by_data(ArrayList *thiz, void *data, int data_size)
{		
	return_val_if_fail(thiz && data && data_size>0, -1);		
	
	if(thiz->array_list_number == 0)
	{
		printf("fun(%s): error \n", __func__);
		return -1;
	}
	
	List *p = thiz->header;
	int i = -1;

	while(p)
	{
		++i;
		if((p->data) && (memcmp(p->data, data, data_size) == 0))
		{
			return i;
		}
		p = p->next;
	}
	
	return -1;
}

void *array_list_get_data_by_id(ArrayList *thiz, int id)
{
	return_val_if_fail(thiz&&(id>=0), NULL);
	
	int i = 0;	
	List *p = NULL;
	
	p = thiz->header;
	for(i = 0; i <= id; i++)
	{		
		if(p && p->data && (i == id))
		{
			return p->data;
		}
		p = p->next;	
	}
	
	return NULL;
}

int array_list_get_size(ArrayList *thiz)
{
	return_val_if_fail(thiz, -1);

	return thiz->array_list_number;
}

void array_list_destroy(ArrayList *thiz)
{
	return_if_fail(thiz);	
	
	List *p = NULL;
	List *prev = NULL;	

	p = thiz->header;
	while(p)
	{
		prev = p;
		p = p->next;
		if(prev->data)
		{
			COMM_FREE(prev->data);
		}
		COMM_FREE(prev);
	}
	COMM_FREE(thiz);
}

