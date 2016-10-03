sudo amixer cset numid=3 1
amixer -c 0 -- sset PCM playback -1dB
#pd -nogui -lib  Jamoma ${0%/*}/Pd/laser-driver.pd &

mkdir -p ${0%/*}/bin/images
sshfs stefane@gorgone-master.local:/Users/stefane/gorgone/images/${HOSTNAME} ${0%/*}/bin/images

LD_LIBRARY_PATH=/usr/local/jamoma/lib ${0%/*}/bin/gorgone -name ${HOSTNAME} $@
