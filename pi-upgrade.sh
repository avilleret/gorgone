# ssh pi@gorgone-1.local /home/pi/ofnode/gorgone/upgrade.sh
# ssh pi@gorgone-2.local /home/pi/ofnode/gorgone/upgrade.sh
# ssh pi@gorgone-3.local /home/pi/ofnode/gorgone/upgrade.sh

osascript -e 'tell application "Terminal" to do script "ssh pi@gorgone-1.local /home/pi/ofnode/gorgone/upgrade.sh"'
osascript -e 'tell application "Terminal" to do script "ssh pi@gorgone-2.local /home/pi/ofnode/gorgone/upgrade.sh"'
osascript -e 'tell application "Terminal" to do script "ssh pi@gorgone-3.local /home/pi/ofnode/gorgone/upgrade.sh"'
