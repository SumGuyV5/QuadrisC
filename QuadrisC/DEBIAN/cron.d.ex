#
# Regular cron jobs for the quadrisc package
#
0 4	* * *	root	[ -x /usr/bin/quadrisc_maintenance ] && /usr/bin/quadrisc_maintenance
