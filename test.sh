#!/bin/zsh

diff_check() {
	echo -n "\033[0;35m$1\033[0m\t\t|\t"
	diff outputs/$1/ft_$1_output outputs/$1/stl_$1_output > logs/diff_$1
	if [ $? -eq "0" ]; then
		echo "\033[1;32mOK\033[0m"
	else
		echo "\033[31mKO\033[0m"
	fi
}


valgrind --log-file="logs/val_log" ./a.out > /dev/null

case $1 in
	"map" )
		diff_check $1
		;;
	"list" )
		diff_check $1
		;;
	"vector" )
		diff_check $1
		;;
	"queue" )
		diff_check $1
		;;
	"stack" )
		diff_check $1
		;;
	* )
		diff_check "map"
		diff_check "list"
		diff_check "vector"
		diff_check "queue"
		diff_check "stack"
		;;
esac
echo -n "\033[0;35mAllocation \033[0m\t|\t"
cat logs/val_log | grep allocs | awk '{print $5}'
echo -n "\033[0;35mDeallocation \033[0m\t|\t"
cat logs/val_log | grep allocs | awk '{print $7}'
