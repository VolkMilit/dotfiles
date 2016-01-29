#!/usr/bin/env bash
 
PADDING=" "
PADDING2="  "
 
while read -r line ; do
    case $line in
        C*)
            # clock output
            clock="${line#?}%{F-}%{B-}  " # if use padding here - clock icon has double Oo
            ;;
 
        D*)
            # date output
            date="${line#?}%{F-}%{B-}$PADDING2"
            ;;
       
       V*)
			# volume output
			volume="${line#?}%{F-}%{B-}$PADDING2"
			;;
            
       W*)
            # workspace
            ws="$PADDING2${line#?}%{F-}%{B-}"
            ;;
            
       N*)
			# window name
			wn="$PADDING2${line#?}%{F-}%{B-}"
			;;
    esac
    printf "%s\n" "%{l}${ws}${wn}%{r}${volume}${date}${clock}"
done
