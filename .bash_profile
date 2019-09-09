alias list='ls'
alias makedir='mkdir'
alias changedir='cd'


if [ "`id -u` -eq 0" ]; then
    PS1='@\h:\w # '
elif [ "`id -u` -eq 1" ]; then
    PS1='\u@:\w\$ '
fi

# if [ "`id -u`" -eq 0 ]; then
#     PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"