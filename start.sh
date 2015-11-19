sudo amixer cset numid=3 1
amixer -c 0 -- sset PCM playback -1dB
#pd -nogui -lib  Jamoma ${0%/*}/Pd/laser-driver.pd &

LD_LIBRARY_PATH=/usr/local/jamoma/lib ${0%/*}/bin/gorgone -name ${HOSTNAME}
