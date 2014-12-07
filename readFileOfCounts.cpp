// [[Rcpp::depends(RcppArmadillo)]]
// [[Rcpp::plugins(cpp11)]]
#include <RcppArmadillo.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace Rcpp;
using namespace std;

// [[Rcpp::export(".readFileOfCounts")]]
SEXP readFileOfCounts(std::string filePath, std::string sep) {
    
    ifstream input(filePath);
    string lineStr; // string for the line
    string colStr; // string for the columns
    stringstream strStream {};
    const char * colChar;
    
    int iCol, iRow = 0; // to capture the current column
    // The separator
    char _sep;
    const char * tsep;
    tsep = sep.c_str();
    if(tsep[0] == '\\'){
      _sep = '\t';
      }else{
      _sep = tsep[0];
    }
    
    vector<string> colNames; // column names
    
    // Read the first line into a string vector
    getline(input, lineStr);
    strStream.str(lineStr);
    while(getline(strStream, colStr, _sep))
    {
      colNames.push_back(colStr);
    }
    strStream.clear();
    vector<string> rowNames; // row names
    vector<vector<double>> countData;
    vector<double> rowData;
    iCol = colNames.size() - 1;
    double countValue;
    // Now we read the rest of the file
    while(getline(input, lineStr))
    {
      strStream.str(lineStr);
      getline(strStream, colStr, _sep); // read the rowname name
      rowNames.push_back(colStr);
      while(getline(strStream, colStr, _sep))
      {
        colChar = colStr.c_str();
        countValue = atof(colChar);
  	    rowData.push_back(countValue);
      }
      countData.push_back(rowData);
      strStream.clear();
      rowData.clear();
      ++iRow;
    }
    
    NumericMatrix rMat(iRow, iCol);
    for(int i = 0; i < iRow; ++i){
      rowData = countData[i];
      for(int j = 0; j < iCol; ++j){
        rMat(i, j) = rowData[j];
      }
      rowData.clear();
    }
    
    CharacterVector _rowNames = wrap(rowNames);
    CharacterVector _colNames = wrap(colNames);
    
    List output; output["mat"] = rMat; output["rowNames"] = _rowNames;
    output["colNames"] = _colNames;
    return wrap(output);
}

