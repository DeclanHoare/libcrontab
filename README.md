libcrontab is a library written in C to manage cron jobs in a similar
manner to the "crontab" userspace utility.

This library is still in active development and I will make breaking
changes without a second thought; please do not rely on it yet.

Please note that any program linking against this library will need
the appropriate permissions to write to the crontabs as well as to
read cron.allow and cron.deny. This generally means u+s to root or
g+s to the crontabs group.

You should change config.h to point to the relevant files on your
system. I am going to set up autotools for this at a later date.
