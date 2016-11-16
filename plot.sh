cat << 'EOF' | gnuplot

set terminal pngcairo size 640,360 enhanced font 'DejaVuSansMono,8'

# set xrange [1:60000]
# set yrange [0:100]

set mytics 2
set grid mytics

set offsets 0.1, 0.1, 0.1, 0.1

# set xlabel ""
# set ylabel "accuracy"
# plot \
#     "aaaa" w l ls 8 t 'aaaa'
# plot \
#     "output" w p ls 8 t ''
# plot "< awk -F , '$3 == 1 ' train.csv" using 1:2 w p ls 8 ps 1 t '', \
#      "< awk -F , '$3 == -1' train.csv" using 1:2 w p ls 4 t '',  \
#      "< awk      '$3 == 1'  output"    using 1:2 w p ls 2 t '', \
#      "< awk      '$3 == -1' output"    using 1:2 w p ls 6 t ''
# set datafile separator ","

# plot "< awk      '$3 == 1'  output"                       using 1:2 w p ls 10 pt 1 ps 0.5 lw 1 t '', \
#      "< awk      '$3 == -1' output"                       using 1:2 w p ls 9  pt 1 ps 0.5 lw 1 t '', \
#      "< awk -F , '$3 == 1'  train.csv | sed -e 's/,/ /g'" using 1:2 w p ls 6 ps 1.5 t '', \
#      "< awk -F , '$3 == -1' train.csv | sed -e 's/,/ /g'" using 1:2 w p ls 8 ps 1.5 t ''

# plot "< awk '$3 == 1'  test2"  using 1:2 w p ls 10 pt 1 ps 0.5 lw 1 t '', \
#      "< awk '$3 == -1' test2"  using 1:2 w p ls 9  pt 1 ps 0.5 lw 1 t '', \
#      "< awk '$3 == 1'  output" using 1:2 w p ls 6 ps 1.5 t '', \
#      "< awk '$3 == -1' output" using 1:2 w p ls 8 ps 1.5 t ''

# plot "< awk '$3 == 0' output" using 1:2 w p ls 2  ps 1.5 lw 1 t 'a', \
#      "< awk '$3 == 1' output" using 1:2 w p ls 4  ps 1.5 lw 1 t 'i', \
#      "< awk '$3 == 2' output" using 1:2 w p ls 6  ps 1.5 lw 1 t 'u', \
#      "< awk '$3 == 3' output" using 1:2 w p ls 8  ps 1.5 lw 1 t 'e', \
#      "< awk '$3 == 4' output" using 1:2 w p ls 1  ps 1.5 lw 1 t 'o', \

# plot "< awk '$3 == 0' output" using 1:2 w p ls 2 lc rgb '#8E68A6' ps 1.5 lw 1 t 'yukari', \
#      "< awk '$3 == 1' output" using 1:2 w p ls 4 lc rgb '#F5D800' ps 1.5 lw 1 t 'makimaki', \
#      "< awk '$3 == 2' output" using 1:2 w p ls 6 lc rgb '#E2738A' ps 1.5 lw 1 t 'akane', \

# plot "output"                       using 1:2 w p ls 10 pt 1 ps 0.5 lw 1 t '', \

# binv(p,q)=exp(lgamma(p+q)-lgamma(p)-lgamma(q))
# beta(x,p,q)=p<=0||q<=0?1/0:x<0||x>1?0.0:binv(p,q)*x**(p-1.0)*(1.0-x)**(q-1.0)
# set xrange [0:1]
# plot beta(x, 10.2, 5.8) ls 10 t 'beta', \
#      1 ls 12 t 'uniform', \
#      "output" using 1:2 w p ls 11 pt 6 ps 1.0 lw 1 t ''

plot (x ** 10) * (13 ** 11) / exp(x * 13) / gamma(11) ls 10 t 'gamma', \
     "output" using 1:2 w p ls 11 pt 6 ps 1.0 lw 1 t ''

# set xlabel "position"
# set ylabel "momentum"
# plot "output" using 1:2 w p ls 12 ps 1.0 lw 1 t ''

# set origin 0.06, 0
# set xlabel "position"
# set ylabel "momentum"
# set zlabel "hamiltonian"
# set xrange[0:3]
# set yrange[-5:5]
# set isosample 50
# unset ztics
# splot (13.0 * x - 10.0 * log(x)) + y * y / 2 ls 9 lw 0.5 t '', \
#     "output" using 1:2:3 w p ls 12 ps 1.0 lw 1 t ''

EOF
