#!/bin/bash

COMMAND="gnuplot"

$COMMAND << EOF
set xlabel "Precio"
set ylabel "Horas dormidas"
set yrange [1:150]
plot "tabla.txt" using 1:2 title "Una parabola" with lines, "tabla.txt"using 1:3 title "Otra parabola" with lines
set term jpeg
set output "grafica.jpeg"
replot
exit
EOF
