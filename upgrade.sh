sudo mount -o remount,rw /
sudo service of-daemon stop 
sudo killall pd 

cd ${0%/*}
git pull
git submodule update --init
cd build
ninja
sudo reboot

