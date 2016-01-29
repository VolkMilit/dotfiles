zmount() {
 if [ -f $1 ] ; then
 case $1 in
 *.iso)   	  sudo mount -t iso9660 -o loop $1 /media/cdrom									  ;;
 *.udf)    	  sudo mount -t udf -o loop $1 /media/cdrom    									  ;;
 *.mdf)       mdf2iso $1 $1.iso && rm $1 && sudo mount -t iso9660 -o loop $1.iso /media/cdrom ;;
 *.ngr)       sudo mount -o loop,offset=307200 $1 /media/cdrom  						      ;;
 *.mdx)       sudo mount -o loop,offset=64 $1 /media/cdrom   	                        	  ;;
 *)           echo "I don't know how to mount '$1'..." 										  ;;
 esac
 else
 echo "'$1' is not a valid file"
 fi
}

zumount() {
	sudo umount /media/cdrom
}
