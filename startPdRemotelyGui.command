ssh -Y $1 "sudo killall pd ; /usr/local/bin/pd -noadc /home/pi/ofnode/gorgone/Pd/laser-driver.pd" && exit 0