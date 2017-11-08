# Codificación ISO Latin-1 y terminal EPS.

set encoding iso_8859_1
set terminal postscript eps

# Título de cada eje.
 
set xlabel "n (número de celdas)"
set ylabel "t(n) (tiempo en segundos)"

# Estilo de presentación (puntos interpolados linealmente).

#set data style linespoints

# Creación de los ficheros EPS.

set output "graphic.eps"
plot 'data.txt' using 1:2 title "Sin pre-ordenación" with lines, \
     '' using 1:3 title "Fusión" with lines, \
	 '' using 1:4 title "Rápida" with lines, \
	 '' using 1:5 title "Montículo" with lines
