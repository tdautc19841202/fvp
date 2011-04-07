/*
 * File: access_file.c
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
 * 2011-04-07 zhoumin <dcdcmin@gmail.com> created
 *
 */

#include"access_file.h"


typedef struct _PrivInfo
{
	unsigned int i_nb_reads;
	int fd;
}PrivInfo;


/*read a block from the file*/
static Block* access_file_block(Access *thiz)
{
	Block *block = NULL;
	

	
	return block;
}


/*
 * Read: standard read on a file descriptor.
 */
static int  access_file_read(Access *thiz, uint8_t *buffer, size_t len)
{
	return_val_if_failed(thiz != NULL && buffer != NULL && len >= 0, -1);
	
	MSG_DBG("access_file_read\n");
	int ret = -1;
	DECL_PRIV(thiz, priv);	
	/*read a len length data to the buffer*/
	ret = read(priv->fd, buffer, len);
	
	if(ret < 0)
	{
		MSG_DBG("Failed to read\n");
        switch (errno)
        {
            case EINTR:
            case EAGAIN:
                break;

            default:
				MSG_DBG("Failed to read\n");
                thiz->info.b_eof = true;
                return 0;
        }
	}
	else if(ret > 0)
	{
        thiz->info.i_pos += ret;
        printf("current pos(%d)\n", thiz->info.i_pos);
	}
	else
	{
		/*read the file end*/
        thiz->info.b_eof = true;
	}
	
	priv->i_nb_reads++;
	
	return ret;
}


/*
 * seek the file 
 */
static void access_file_seek(Access *thiz, unsigned long pos)
{
	return_if_failed(thiz != NULL );

	
	DECL_PRIV(thiz, priv);	
	lseek(priv->fd, pos, SEEK_SET);
	
	return;
}


/*
 * control the file
 */
static void access_file_control(Access *thiz, int query, va_list args)
{	
	return_if_failed(thiz != NULL);
	
	MSG_DBG("access_file_control\n");
	
	return;
}


/*
 * destroy the access
 */
static void access_file_destroy(Access *thiz)
{
	if(thiz)
	{
		DECL_PRIV(thiz, priv);	
		if(priv->fd >= 0)
		{
			close(priv->fd);
			priv->fd = -1;
		}

		COMM_ZFREE(priv, sizeof(PrivInfo));
		COMM_ZFREE(thiz, sizeof(*thiz));
	}
	
	return;
}


/*
 * create access 
 */
Access *access_file_create(char *file_path)
{
	return_val_if_failed(file_path, NULL);
	
	int fd = -1;

	/*open the file */
	fd = open(file_path, O_RDONLY);
	if(fd <= 0)
	{
		MSG_DBG("error:open the file failed!\n");
		return NULL;
	}
	
	Access *thiz = (Access *)COMM_ZALLOC(sizeof(Access) + sizeof(PrivInfo));
	return_val_if_failed(thiz != NULL, NULL);
	
	thiz->seek = access_file_seek;
	thiz->read = access_file_read;
	thiz->block = access_file_block;
	thiz->control = access_file_control;
	thiz->destroy = access_file_destroy;
	
	
	PrivInfo* priv = (PrivInfo *)thiz->priv;
	priv->fd = fd;
	priv->i_nb_reads = 0;

	return thiz;
}


