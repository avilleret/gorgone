sudo mount -o remount,rw /
sudo killall gorgone 
sudo killall pd 

cd ${0%/*}
git stash
git pull
git submodule update --init
cd build
ninja -j 3
sudo reboot

