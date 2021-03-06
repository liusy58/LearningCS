#! /bin/sh
#
# Create plots from the cachetorture script.
#
# Usage: sh plots.sh tag perfbook-path
#
# Execute this script in the directory containing the data.
# The tag is the same string passed to reduce.sh.  The perfbook-path
# is the path to the top-level perfbook directory, defaulting to
# ../../../../.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, you can access it online at
# http://www.gnu.org/licenses/gpl-2.0.html.
#
# Copyright (C) Facebook, 2020
#
# Authors: Paul E. McKenney <paulmck@kernel.org>

tag=$1
font=${2-../../../../}

fontsize=8
plotsize=0.5

gnuplot << ---EOF---
set term postscript portrait ${fontsize} enhanced "NimbusSanL-Regu" fontfile "${font}fonts/uhvr8a.pfb"
set size square ${plotsize},${plotsize}
set output "cachetorture-latency.eps"
set xlabel "Hardware Thread (CPU) Number"
set ylabel "Nanoseconds per Operation"
# set logscale xy
#set yrange [1:10000]
#set yrange [100:10000]
set nokey
set label 1 "cmpxchg 1" at 120,300 left
set label 2 "cmpxchg 2" at 120,900 left
set label 3 "atomic inc" at 120,850 left
set label 4 "write" at 120,800 left
set label 5 "local lock" at 75,100 left
set label 6 "local cmpxchg" at 75,55 left
plot "hps.2020.02.24a.atomicinc.dat" w l, "hps.2020.02.24a.blindcmpxchg.dat" w l, "hps.2020.02.24a.cmpxchg.dat" w l, "hps.2020.02.24a.write.dat" w l, 7.0862, 15.479
set term jpeg large
set size square 1.0,1.0
set output "cachetorture-latency.jpg
replot
---EOF---

gnuplot << ---EOF---
set term postscript portrait ${fontsize} enhanced "NimbusSanL-Regu" fontfile "${font}fonts/uhvr8a.pfb"
set size square ${plotsize},${plotsize}
set output "cachetorture-latency-scatter.eps"
set xlabel "Hardware Thread (CPU) Number"
set ylabel "Nanoseconds per Operation"
# set logscale xy
#set yrange [1:10000]
#set yrange [100:10000]
set nokey
set label 1 "blind" at 120,270 left
set label 2 "cmpxchg" at 120,220 left
set label 3 "cmpxchg" at 120,850 left
set label 5 "local lock" at 75,100 left
set label 6 "local cmpxchg" at 75,55 left
plot "hps.2020.02.24a.blindcmpxchg.sctr.dat" w p pt 0, "hps.2020.02.24a.cmpxchg.sctr.dat" w p pt 0, "hps.2020.02.24a.blindcmpxchg.dat" w l, "hps.2020.02.24a.cmpxchg.dat" w l, 7.0862, 15.479
set term jpeg giant size 960,480
set size nosquare 1.0,1.0
set output "cachetorture-latency-scatter.jpg
replot
---EOF---
# cp perf-refcnt.eps ../..
# cp perf-refcnt.eps ../..
