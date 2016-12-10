/*
	This file is part of libcrontab.
	libcrontab is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	libcrontab is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with libcrontab.  If not, see <http://www.gnu.org/licenses/>.

	libcrontab.h - Library public declarations
*/

#include <stdbool.h>

#ifndef __LIBCRONTAB_LIBCRONTAB_H
#define __LIBCRONTAB_LIBCRONTAB_H

bool setUserCrontab(char *newUserName);
char *getCrontabPath();
char *getCrontab();

#endif /* __LIBCRONTAB_LIBCRONTAB_H */
