# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    loading.sh                                       .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: rlossy <marvin@le-101.fr>                  +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/04/16 17:17:55 by rlossy       #+#   ##    ##    #+#        #
#    Updated: 2018/09/10 10:31:53 by rlossy      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

#!/bin/bash

# Loading progressbar
source $1/progressbar.sh || exit 1

i=0 start=0 end=6
for i in $(seq ${start} ${end}); do
	if [[ ("$3" != "o") ]] ; then
		sleep 0.1
	fi
	if [[ ("$3" != "r") ]] ; then
		progressbar "$2" ${i} ${end} "Compiling process..."
	else
		export ILoveCandy=true
		progressbar "⥷ $5⭃    $2" ${i} ${end} "Deletion process..."
	fi
done
	if [[ ("$4" == "y") ]] ; then
		echo
	fi
