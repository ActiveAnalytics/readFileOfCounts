#' @name readFileOfCounts
#' @tile Function to read file of counts from from RNA-Seq goes faster than read.table-based functions
#' 
#' @param filePath character path to the file of counts to be read
#' @param sep character separator defaults to tab (\t)
#'
#' @return returns either a data frame or matrix according to the asDF function
#' 
readFileOfCounts <- function(filePath, sep){
  cout <- .readFileOfCounts(filePath, sep)
  output <- cout[["mat"]]
  dimnames(output) <- list(cout[["rowNames"]], cout[["colNames"]][-1])
  return(as.data.frame(output))
}
