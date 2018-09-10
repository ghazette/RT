# Progress_Bar-for-Makefile

This project is just a revisit of the original work of Alexandre PUJOL adapted to be used in Makefile.

Find example about how to use it here : https://github.com/Althis974/Fractol/blob/master/Makefile

<table>
   <tr>
       <td>LOADIR</td>
       <td>Path to scripts location</td>
   </tr>
   <tr>
       <td>LOADF</td>
       <td>File called to launch progress bar</td>
   </tr>
     <tr>
       <td>First argument</td>
       <td>Name of progress bar</td>
   </tr>
     <tr>
       <td>Second argument</td>
       <td>Type of bar (here, r : remove, a : library, e : executabe, o : object)</td>
   </tr>
     <tr>
       <td>Third argument</td>
       <td>Need \n between bars ? (y/n)</td>
   </tr>
     <tr>
       <td>Fourth argument</td>
       <td>Specify name of bar (in case of multi-makefile for example)</td>
   </tr>
</table>

Every arguments are optionnals.

## https://github.com/roddhjav/progressbar
## progressbar - A pacman like progress bar in bash
## Copyright (C) 2016 - 2018 Alexandre PUJOL <alexandre@pujol.io>.
