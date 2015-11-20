sudo mount -o remount,rw /
cd ${0%/*}
git pull 
cd build
ninja
sudo reboot

