if (!exists("datafile")) datafile = "data.txt"
if (!exists("output_file")) output_file = "graph.png"
if (!exists("custom_title")) custom_title = "default_title"
if (!exists("width")) width = 800
if (!exists("height")) height = 600
if (!exists("x_label")) x_label = "X"
if (!exists("y_label")) y_label = "Y"

set terminal pngcairo size width,height font "Sans,12"
set output output_file
set title custom_title
set xlabel x_label
set ylabel y_label
set grid
set key outside top left
set termoption noenhanced

number_of_files = words(datafile)

plot for [i=1:number_of_files] word(datafile, i) using 1:2 with lines title word(datafile, i)