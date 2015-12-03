sudo mount -o remount,rw /
cd ${0%/*}
git pull
git submodule update --init
cd build
ninja
sudo reboot

