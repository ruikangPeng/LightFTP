/*
* cfgparse.c
*
*  Created on: Aug 20, 2016
*
*  Modified on: Feb 09, 2018
*
*      Author: lightftp
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "x_malloc.h"

char *skip_comments_and_blanks(char *p)
{
	while (*p != 0) {

		while (
				(*p == ' ') ||
				(*p == '\n')
				)
			++p;

		if (*p == '#')
		{
			++p;

			while (
					(*p != 0) &&
					(*p != '\n')
					)
				++p;

			continue;
		}
		else
			break;

	}

	return p;
}

/* TODO: Rewrite this function */

int config_parse(
    const char      *pcfg,
    const char      *section_name,
    const char      *key_name,
    char            *value,
    unsigned long   value_size_max)
{
	unsigned long	sp;
	char			vname[256], *p = (char *)pcfg;

	if (value_size_max == 0)
		return 0;
	--value_size_max;

	while (*p != 0)
	{
		/*
		 *  skip all characters before first '['
		 */
		p = skip_comments_and_blanks(p);

		/*
		 *  if we got EOF so quit
		 */
		if (*p == 0)
			break;

		if (*p != '[')
		{
			++p;
			continue;
		}

		/*
		 *  skip '[' that we found
		 */
		++p;

		/*
		 * copy section name to vname
		 */
		sp = 0;
		while (
				(*p != ']') &&
				(*p != 0) &&
				(*p != '\n') &&
				(sp < 255)
				)
		{
			vname[sp] = *p;
			++sp;
			++p;
		}
		vname[sp] = 0;

		if (*p == 0)
			break;

		/*
		 * newline - start over again
		 */
		if (*p == '\n')
			continue;

		/*
		 * skip ']' that we found
		 */
		++p;

		if (strcmp(vname, section_name) == 0)
		{
			do {
				p = skip_comments_and_blanks(p);
				if ((*p == 0) || (*p == '['))
					break;

				sp = 0;
				while (
						(*p != '=') &&
						(*p != ' ') &&
						(*p != 0) &&
						(*p != '\n') &&
						(sp < 255)
						)
				{
					vname[sp] = *p;
					++sp;
					++p;
				}
				vname[sp] = 0;

				if (*p == 0)
					break;

				while (*p == ' ')
					++p;

				if (*p != '=')
					break;

				p++;

				if (strcmp(vname, key_name) == 0)
				{
					sp = 0;

					while (
							(*p != '\n') &&
							(*p != 0)
							)
					{
						if (sp < value_size_max)
							value[sp] = *p;
						else
							return 0;
						++sp;
						++p;
					}
					value[sp] = 0;
					return 1;
				}
				else
				{
					while (
							(*p != '\n') &&
							(*p != 0)
							)
						++p;
				}

			} while (*p != 0);
		}
		else
		{
			do {
				p = skip_comments_and_blanks(p);

				if ((*p == 0) || (*p == '['))
					break;

				while (
						(*p != '\n') &&
						(*p != 0)
						)
					++p;

			} while (1);
		}
	}

	return 0;
}

/**
 * 这是一个用于读取配置文件内容并将其存储在字符指针中的函数。
 */
char *config_init(char *cfg_filename)
{
	int		f_config;							//保存配置文件的文件描述符
	char	*buffer = NULL;						//用于存储配置文件的内容
	off_t	fsz;								//用于保存配置文件的大小

	f_config = open(cfg_filename, O_RDONLY);	//使用 open 函数以只读方式打开文件，并将文件描述符保存在 f_config 中
	while (f_config != -1)
	{
		fsz = lseek(f_config, 0L, SEEK_END) + 1;// 使用 lseek 函数将文件指针移到文件末尾，并获取文件大小
		lseek(f_config, 0L, SEEK_SET);			//使用 lseek 函数将文件指针移到文件开头，以准备读取文件内容

		buffer = x_malloc(fsz);					//使用 x_malloc 函数分配内存，大小为文件大小加 1 字节，用于存储配置文件内容

		fsz = read(f_config, buffer, fsz);		//使用 read 函数读取配置文件内容，并将其存储在 buffer 指针指向的内存中。fsz 变量将被更新为实际读取的字节数。
		buffer[fsz] = 0;						//在读取的内容末尾添加空字符，以将其转换为 C 风格的字符串
		break;
	}

	if (f_config != -1)
		close(f_config);

	return buffer;
}
