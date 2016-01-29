# Распаковка архивов
# example: ex file

ex () {
 if [ -f $1 ] ; then
 case $1 in
 *.tar.bz2)   tar xjvf $1      						     ;;
 *.tar.gz)    tar xzvf $1  							     ;;
 *.tar.xz)	  tar xvf  $1                                    ;;
 *.bz2)       bunzip2 $1   							     ;;
 *.rar)       unrar x $1    							 ;;
 *.gz)        gunzip $1     							 ;;
 *.tar)       tar xvf $1    						     ;;
 *.*.*.*.*.pol)       tar xvf $1    				     ;;
 *.tbz2)      tar xjvf $1   						     ;;
 *.tbz)       tar -xjvf $1    							 ;;
 *.tgz)       tar xzvf $1     						     ;;
 *.zip)       unzip $1     								 ;;
 *.Z)         uncompress $1  							 ;;
 *.7z)        7z x $1    								 ;;
 *.deb)		  dpkg -x $1 ./$1-extract 					 ;;
 *)           echo "I don't know how to extract '$1'..." ;;
 esac
 else
 echo "'$1' is not a valid file"
 fi
}

# Запаковать архив
# example: pk tar file
pk () {
 if [ $1 ] ; then
 case $1 in
 tbz)       tar cjvf $2.tar.bz2 $2     			  ;;
 tgz)       tar czvf $2.tar.gz  $2      		  ;;
 tar)      	tar cpvf $2.tar  $2       			  ;;
 bz2)    	bzip $2 							  ;;
 gz)        gzip -c -9 -n $2 > $2.gz 			  ;;
 zip)       zip -r $2.zip $2   					  ;;
 7z)        7z a $2.7z $2    					  ;;
 rar)		rar a $2.rar $2						  ;;
 *)         echo "'$1' cannot be packed via pk()" ;;
 esac
 else
 echo "'$1' is not a valid file"
 fi

}   
