# $1 ./a.out


if [ "$1" = "-v" ]; then
	valgrind ./a.out
else
	./a.out
fi

if [ $# -eq "1" ] && [ "$1" != "-v" ]; then
	diff outputs/$1/ft_$1_output outputs/$1/stl_$1_output
elif [ $# -eq "2" ]; then
	diff outputs/$2/ft_$2_output outputs/$2/stl_$2_output
else
	echo "Too much argument";
fi


