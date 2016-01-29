countdown() {
    secs=$(($1 * 60))
    while [ $secs -gt 0 ]; do
        echo -ne "Counting down from $1 minutes, \033[1;31m$secs seconds\033[0m remaining... \033[1;30m(Ctrl+C to Cancel)\033[0m\r"
        sleep 1
        : $((secs--));
    done; echo -e "\n\033[1;30m$(date)\033[1;31m Countdown has finished!\033[0m\n"
}
