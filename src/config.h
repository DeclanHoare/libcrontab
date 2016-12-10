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

	config.h - Cron file paths
*/

#ifndef __LIBCRONTAB_CONFIG_H
#define __LIBCRONTAB_CONFIG_H

#define LIBCRONTAB_CRONTABS "/var/spool/cron"
#define LIBCRONTAB_CRON_ALLOW "/etc/cron.allow"
#define LIBCRONTAB_CRON_DENY "/etc/cron.deny"
#define LIBCRONTAB_CRONTAB_LOG "/var/log/crontab.log"

#endif // __LIBCRONTAB_CONFIG_H

