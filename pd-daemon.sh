#!/bin/sh

### BEGIN INIT INFO
# Provides:          pd-daemon
# Required-Start:    $remote_fs $syslog of-daemon
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Put a short description of the service here
# Description:       Put a long description of the service here
### END INIT INFO

# see http://blog.scphillips.com/posts/2013/07/getting-a-python-script-to-run-in-the-background-as-a-service-on-boot/
# for reference

# Change the next 3 lines to suit where you install your script and what you want to call it
DIR=$(dirname $(readlink -f $0))
DAEMON=/usr/local/bin/pd
DAEMON_NAME=pd-daemon

#export LD_LIBRARY_PATH=/home/pi/of/lib-linux/release-armv7/
#export LD_LIBRARY_PATH=/usr/local/jamoma/lib

# Add any command line options for your daemon here
DAEMON_OPTS='-noadc -nogui -send "hostname symbol $HOSTNAME" $DIR/Pd/laser-driver.pd'

# This next line detersmines what user the script runs as.
# Root generally not recommended but necessary if you are using the Raspberry Pi GPIO from Python.
DAEMON_USER=pi

# The process ID of the script when it runs is stored here:
PIDFILE=/tmp/$DAEMON_NAME.pid

. /lib/lsb/init-functions

do_start () {
    log_daemon_msg "Setup sound card before starting $DAEMON_NAME daemon"
    amixer cset numid=3 1
    amixer -c 0 -- sset PCM playback -1dB
    amixer -c 1 -- sset PCM Front -15.5dB
    amixer -c 1 -- sset PCM Rear 0dB
    log_daemon_msg "Starting system $DAEMON_NAME daemon"
    start-stop-daemon --start --background --pidfile $PIDFILE --make-pidfile --user $DAEMON_USER --chuid $DAEMON_USER --startas $DAEMON -- $DAEMON_OPTS
    log_end_msg $?
}
do_stop () {
    log_daemon_msg "Stopping system $DAEMON_NAME daemon"
    start-stop-daemon --stop --pidfile $PIDFILE --retry 10
    log_end_msg $?
}

case "$1" in

    stop)
        do_${1}
        ;;

    start|restart|reload|force-reload)
        do_stop
        do_start
        ;;

    status)
        status_of_proc "$DAEMON_NAME" "$DAEMON" && exit 0 || exit $?
        ;;

    *)
        echo "Usage: /etc/init.d/$DAEMON_NAME {start|stop|restart|status}"
        exit 1
        ;;

esac
exit 0
