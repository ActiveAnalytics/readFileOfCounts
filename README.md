readFileOfCounts
================

C++ based R function for reading file of counts from RNA-Seq.

This repository contains code from the Active Analytics [blog](http://www.active-analytics.com/blog/) for reading
file of counts from RNA-Seq files. The underlying function is written in C++ using the Rcpp package with an R 
wrapper function. The function is designed to read files where the first column in the file is the 
symbol and the rest of the columns contains count data. It gives a performance boost where the read time is reduced
to a third of the read time of the R-based `read.delim` file.

# Usage

```
require(Rcpp)
sourceCpp("readFileOfCounts.cpp")
source("readFileOfCounts.R")
readFileOfCounts("count_table.txt", "\t")
```

# Benchmarks with R's default method

```
mb <- microbenchmark::microbenchmark
benchmarks <- mb(readFileOfCounts("count_table.txt", sep = "\t"),
                 read.delim("count_table.txt", row.names="gene"))
Unit: milliseconds
                                              expr     min       lq     mean   median       uq      max neval
  readFileOfCounts("count_table.txt", sep = "\\t") 254.419 284.8199 292.3839 288.3123 293.8638 408.4934   100
 read.delim("count_table.txt", row.names = "gene") 798.816 817.1757 838.4695 831.1102 862.1574 895.1991   100
```

