#!/bin/bash
#Naloga1.sh prostor /home/iletavchioski/Desktop/P
# stat /home/iletavchioski/Desktop/P
velikost=0;
stblokov=0;
function presmetaj {
	cd "$1";
	for i in *
	do
		if [ "$i" != "*" ]
		then
			daliedir=0;
			a=5;
			
			if [ -L "$i" ]
			then 
				daliedir=0;
			elif [ -d "$i" ]
			then 
				daliedir=1;
			fi
			
			vel=$(stat -c%s "$i");
			nb=$(stat -c%b "$i");
			velikost=$(($velikost + $vel));
			stblokov=$(($stblokov + $nb));
			if [ $daliedir == "1" ]
			then
				
				if (($2 < $3));
				then
					d=1;
					presmetaj "$i" "$(($2+$d))" "$3";
					cd ..;
				fi
			fi
		fi
		
	done
}
function izpis {
	cd "$1";
	for i in *
	do
		if [ "$i" != "*" ]
		then
			for ((q = 0; q < $2; q++)); 
			do
				echo -n "----";
			done
			daliedir=0;
			a=5;
			
			if [ -f "$i" ]
			then
				echo -n "FILE  ";
			elif [ -L "$i" ]
			then 
				echo -n "LINK  ";
			elif [ -d "$i" ]
			then 
				echo -n "DIR   ";
				daliedir=1;
			elif [ -c "$i" ]
			then 
				echo -n "CHAR  ";
			elif [ -b "$i" ]
			then 
				echo -n "BLOCK ";
			elif [ -p "$i" ]
			then 
				echo -n "PIPE  ";
			elif [ -S "$i" ]
			then 
				echo -n "SOCK  ";
			fi
			echo -e "$i";
			if [ $daliedir == "1" ]
			then
				if (($2 < $3));
				then
					d=1;
					izpis "$i" "$(($2+$d))" "$3";
					cd ..;
				fi
			fi
		fi
		
	done
}
case $1 in
	(pomoc)
	shift
	echo -e "Uporaba: $0 akcija parametri";
	;;
	(status)
	shift
	a=$1;
	b=$2;
	while (("$a" != "0"));
	do
		t=$a;
		a=$(($b % $a));
		b=$t;
	done
	exit $b;
	;;
	(userinfo)
	shift
		for i in $@
		do
			echo -n "$i:";
			
			
			nema="id: ‘$i’: no such user";
			kec=1;
			# imauser=$(cat /etc/passwd | grep "$i");
			# echo -e $imauser;
			if [ $(getent passwd $i) ]
			then
				prvo=$(id -u "$i");
				vtor=$(id -g "$i");
				if (("$prvo" == "$vtor"));
				then
					echo -n " enaka";
				fi
				ima=0;
				if [ -d "/home/$i" ]
				then
					ima=1;
				fi
				if [ -d "/home/uni/$i" ]
				then
					ima=1;
				fi
				if (($ima == $kec));
				then
					echo -n " obstaja";
 				fi
				
				ggg=$(groups $i);
				set -- "$ggg";
				IFS=" ";
				declare -a grupi=($*);
				brojac=${#grupi[@]};
				brojac=$(($brojac - 2));
				echo -e " $brojac";
				
			else 
				echo -e " err";
			fi
			
		done
	;;
	(drevo)
	shift
		if [ -f "$1" ]
		then
			echo -n "FILE  ";
		elif [ -d "$1" ]
		then 
			echo -n "DIR   ";
			daliedir=1;
		elif [ -L "$1" ]
		then 
			echo -n "LINK  ";
		elif [ -c "$1" ]
		then 
			echo -n "CHAR  ";
		elif [ -b "$1" ]
		then 
			echo -n "BLOCK ";
		elif [ -p "$1" ]
		then 
			echo -n "PIPE  ";
		elif [ -S "$1" ]
		then 
			echo -n "SOCK  ";
		fi
		echo -e "$1";
		if (("$#" == "1"));
		then
			izpis "$1" "1" "3";
		elif (("$2" != "drevo"));
		then
			izpis "$1" "1" "$2"
		else
			izpis "$1" "1" "100";
		fi
	;;
	(leto)
	shift
	for i in $@
	do
		e=400;
		d=4;
		f=100;
		a=$(($i % $e));
		b=$(($i % $d));
		c=$(($i % $f));
		if (("$a" == "0" ));
		then
			echo "Leto $i je prestopno.";
		elif (("$b" == "0")) && (("$c" != "0"));
		then
			echo "Leto $i je prestopno.";
		else
			echo "Leto $i ni prestopno.";
		fi
		
	done
	;;
	(fib)
	shift
	for i in $@
	do
		a=0;
		b=1;
		if (($i == "0"));
		then
			echo -e "0: 0";
		elif (($i == "1"));
		then
			echo -e "1: 1";
		else
			c=$(($a + $b));
			for ((j=2;j<=$i;j++));
			do
				c=$(($a + $b));
				a=$b;
				b=$c;	
			done
			echo -e "$i: $b";
		fi
	done
	;;
	(tocke)
	shift
		br1=0;
		br2=0;
		RANDOM=42;
		while read i
		do
			set -- "$i";
			IFS=" ";
			declare -a niza=($*);
			taraba=${niza[0]};
			dolzina=${#niza[@]};
			if [ "$taraba" == "#" ]
			then
				continue;
			fi

			vpisna=${niza[0]};
			a=${niza[1]};
			b=${niza[2]};
			c=${niza[3]};
			zbir=$(($a + $b + $c));
			tip=0;
			if [ "${niza[4]}" == "p" ]
			then
				tip=1;
			elif [ "${niza[4]}" == "P" ]
			then
				tip=1;
			fi
			br1=$(($br1 + 1));
			vpis=$vpisna;
			vpis=$(($vpis / 10000));
			vpis=$(($vpis % 100));
			# echo -e "$vpis $tip";
			if [ $tip == "1" ]
			then
				# echo -e $zbir;
				zbir=$(($zbir / 2)); 
				# echo -e $zbir;
			elif [ $vpis == "14" ]
			then	
				dodaj=$(($RANDOM % 5));
				dodaj=$(($dodaj + 1));
				zbir=$(($zbir + $dodaj));
			fi
			pedeset=50;
			if (($zbir>=50));
			then
				zbir=50;
			fi
			br2=$(($br2 + $zbir));
			echo -e "$vpisna: $zbir";
			
		done
		prosek=$(($br2 / $br1));
		echo -e "St. studentov: $br1";
		echo -e "Povprecne tocke: $prosek";
	;;
	(prostor)
	shift
		vel=$(stat -c%s "$1");
		nb=$(stat -c%b "$1");
		velikost=$(($velikost + $vel));
		stblokov=$(($stblokov + $nb));
		if (("$#" == "1"));
		then
			presmetaj "$1" "1" "3";
		elif (("$2" != "drevo"));
		then
			presmetaj "$1" "1" "$2"
		else
			presmetaj "$1" "1" "100";
		fi
		echo -e "Velikost: $velikost";
		echo -e "Blokov: $stblokov";
		stblokov=$(($stblokov * 512));
		echo -e "Prostor: $stblokov";
	;;
	(*)
	shift
		echo -e "Napacna uporaba skripte!";
		echo -e "Uporaba: $0 akcija parametri";
	;; 
esac
exit
