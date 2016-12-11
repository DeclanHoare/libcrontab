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

	libcrontab.c - Library implementation
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "config.h"
#include "libcrontab.h"

extern const char *__progname;

static pid_t __libcrontab_progId;
static uid_t __libcrontab_userId;
static struct passwd *__libcrontab_userEntry;

char *__libcrontab_userName;
char *__libcrontab_originalUserName;

bool __libcrontab_crontabInitialised = false;

bool __libcrontab_initialise_crontab();



bool __libcrontab_initialise_crontab()
{
	if (!__libcrontab_crontabInitialised)
	{
		__libcrontab_progId = getpid();
		__libcrontab_userId = getuid();
		
		if (!(__libcrontab_userEntry = getpwuid(__libcrontab_userId)))
		{
			fprintf(stderr, "libcrontab: failed to retrieve passwd entry for %d\n", __libcrontab_userId);
			return false;
		}
		
		if (!(__libcrontab_userName = malloc(strlen(__libcrontab_userEntry->pw_name) + 1))) {
			fprintf(stderr, "libcrontab: malloc() failed\n");
			return false;
		}
		strcpy(__libcrontab_userName, __libcrontab_userEntry->pw_name);
		if (!(__libcrontab_originalUserName = malloc(strlen(__libcrontab_userName) + 1))) {
			fprintf(stderr, "libcrontab: malloc() failed\n");
			return false;
		}
		strcpy(__libcrontab_originalUserName, __libcrontab_userName);
		__libcrontab_crontabInitialised = true;
	}
	return true;
}

bool setUserCrontab(char *newUserName)
{
	if (!(__libcrontab_initialise_crontab()))
	{
		fprintf(stderr, "libcrontab: failed to initialise\n");
		return false;
	}
	if (__libcrontab_userId != 0)
	{
		fprintf(stderr, "libcrontab: %s is not root, cannot change user\n", __libcrontab_userName);
		return false;
	}
	if (!(__libcrontab_userEntry = getpwnam(newUserName))) {
		fprintf(stderr, "libcrontab: failed to retrieve passwd entry for %s\n", newUserName);
		return false;
	}
	if (!(__libcrontab_userName = malloc(strlen(newUserName) + 1))) {
		fprintf(stderr, "libcrontab: malloc() failed\n");
		return false;
	}
	strcpy(__libcrontab_userName, newUserName);
	return true;
}

char *getCrontabPath()
{
	char *returnValue;
	if (!(__libcrontab_initialise_crontab()))
	{
		fprintf(stderr, "libcrontab: failed to initialise\n");
		return NULL;
	}
	if (!(returnValue = malloc(strlen(LIBCRONTAB_CRONTABS) + strlen(__libcrontab_userName) + 2 /* 1 for the null byte, one for the directory delimiter */ )))
	{
		fprintf(stderr, "libcrontab: malloc() failed\n");
		return NULL;
	}
	strcpy(returnValue, LIBCRONTAB_CRONTABS);
	strcat(returnValue, "/");
	strcat(returnValue, __libcrontab_userName);
	return returnValue;
}

char *getCrontab()
{
	char *returnValue;
	char *crontabPath;
	FILE *crontabFile;
	struct stat crontabStat;
	
	crontabPath = getCrontabPath();
	if (!(crontabFile = fopen(crontabPath, "r")))
	{
		fprintf(stderr, "libcrontab: failed to open crontab %s\n", crontabPath);
		return NULL;
	}
	fstat(fileno(crontabFile), &crontabStat);
	if (!(returnValue = malloc(crontabStat.st_size + 1)))
	{
		fprintf(stderr, "libcrontab: malloc() failed\n");
		return NULL;
	}
	if (!(fread(returnValue, 1, crontabStat.st_size, crontabFile)))
	{
		fprintf(stderr, "libcrontab: fread() failed\n");
		return NULL;
	}
	fclose(crontabFile);
	return returnValue;
}

