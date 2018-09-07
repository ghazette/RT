# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    loading.sh                                       .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: rlossy <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/16 17:17:55 by rlossy       #+#   ##    ##    #+#        #
#    Updated: 2018/09/07 15:05:09 by rlossy      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#!/bin/bash

# Loading progressbar
source /Users/rlossy/extra/Progress_Bar-for-Makefile/progressbar.sh || exit 1

i=0 start=0 end=6
for i in $(seq ${start} ${end}); do
	if [[ ("$2" != "o") ]] ; then 
		sleep 0.1
	fi
	if [[ ("$2" != "r") ]] ; then 
		progressbar "$1" ${i} ${end} "Compiling process..."
	else
		export ILoveCandy=true
		progressbar "⥷ $4⭃    $1" ${i} ${end} "Deletion process..."
	fi
done
	if [[ ("$3" == "y") ]] ; then 
		echo
	fi
