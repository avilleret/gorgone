osascript -e 'tell application "Terminal" to do script "/Users/stefane/gorgone/startPdRemotelyGui.command pi@gorgone-1.local"'
sleep 2
osascript -e 'tell application "Terminal" to do script "/Users/stefane/gorgone/startPdRemotelyGui.command pi@gorgone-2.local"'
sleep 2
osascript -e 'tell application "Terminal" to do script "/Users/stefane/gorgone/startPdRemotelyGui.command pi@gorgone-3.local"'
