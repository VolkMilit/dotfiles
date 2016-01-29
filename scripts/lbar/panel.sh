#!/usr/bin/env bash

PANEL_FIFO=/tmp/panel-fifo
PANEL_HEIGHT=16
PANEL_FONT_FAMILY="Sans-10"
ICON_FONT="FontAwesome-11"

#colors
FONT_COLOR='#fff'
PANEL_BACKGROUND='#2d2d2d'

SLEEP=0.5 #sleep of mainloop

if [ $(pgrep -cx panel) -gt 1 ] ; then
        printf "%s\n" "The panel is already running." >&2
        exit 1
fi
 
#trap 'trap - TERM; kill 0' INT TERM QUIT EXIT
 
[ -e "$PANEL_FIFO" ] && rm "$PANEL_FIFO"
mkfifo "$PANEL_FIFO"

#main loop
while true
do
		d=`xprop -root _NET_CURRENT_DESKTOP | rev | cut -c1`
		
		if [ "$d" = "0" ]; then
			echo W$(echo -e '\uf111 \uf1db \uf1db \uf1db \uf1db')
		elif [ "$d" = "1" ]; then
			echo W$(echo -e '\uf1db \uf111 \uf1db \uf1db \uf1db')
		elif [ "$d" = "2" ]; then
			echo W$(echo -e '\uf1db \uf1db \uf111 \uf1db \uf1db')
		elif [ "$d" = "3" ]; then
			echo W$(echo -e '\uf1db \uf1db \uf1db \uf111 \uf1db')
		else
			echo W$(echo -e '\uf1db \uf1db \uf1db \uf1db \uf111')
		fi
		
		echo N$(xdotool getwindowname `xdotool getactivewindow`)
		
		echo V$(echo -e '\uf028') $(awk -F"[][]" '/dB/ { print $2 }' <(amixer -D hw:1) | head -n1)
        echo D$(echo -e '\uf073') $(date +'%d %b, %a')
        echo C$(echo -e '\uf017') $(date "+%H:%M")
        
        sleep $SLEEP
done > "$PANEL_FIFO" &

cat "$PANEL_FIFO" | ./panel_bar.sh | ./lemonbar -p -g x$PANEL_HEIGHT -F $FONT_COLOR -B $PANEL_BACKGROUND -f $PANEL_FONT_FAMILY -f $ICON_FONT
