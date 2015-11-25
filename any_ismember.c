/*==========================================================
 * arrayProduct.c - example in MATLAB External Interfaces
 *
 * Multiplies an input scalar (multiplier) 
 * times a 1xN matrix (inMatrix)
 * and outputs a 1xN matrix (outMatrix)
 *
 * The calling syntax is:
 *
 *		outMatrix = arrayProduct(multiplier, inMatrix)
 *
 * This is a MEX-file for MATLAB.
 * Copyright 2007-2012 The MathWorks, Inc.
 *
 *========================================================*/

#include "mex.h"
#include "matrix.h"
#define A(i,j) A[(i) + (j)*n_A_rows]
#define B(i,j) B[(i) + (j)*n_B_rows]

/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    size_t n_A_rows;
    size_t n_B_rows;
    double multiplier;              /* input scalar */
    size_t ncols;                   /* size of matrix */
    size_t out_flag;

    /* check for proper number of arguments */
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:any_ismember:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:any_ismember:nlhs","One output required.");
    }

    n_A_rows = 8;
    n_B_rows = 8;
    ncols = 3;
    /*
    mexPrintf("n_A_rows: %d\n", n_A_rows);
    mexPrintf("n_B_rows: %d\n", n_B_rows);
    mexPrintf("ncols: %d\n", ncols);
    */
    if(ncols!=mxGetN(prhs[1])){
        mexErrMsgIdAndTxt("MyToolbox:any_ismember:nrhs","The number of columns in A and B must be identical.");
    }
    
    /* create a pointer to the real data in the input matrix  */
    double *A = mxGetPr(prhs[0]);
    /*
    int k;
    int kk;
    for(k=0;k<n_A_rows;k++){
        for(kk=0;kk<ncols;kk++){
            mexPrintf("%lf  ",A(k,kk));
        }
        mexPrintf("\n");
    }
    mexPrintf("\n");
    */
    double *B = mxGetPr(prhs[1]);
    /*
    for(k=0;k<n_B_rows;k++){
        for(kk=0;kk<ncols;kk++){
            mexPrintf("%lf  ",B(k,kk));
        }
        mexPrintf("\n");
    }
    */
    
    int a_rownum;
    int b_rownum;
    int colnum;
    int row_match;
    
    for(b_rownum = 0; b_rownum<n_B_rows; b_rownum++){
        for(a_rownum = 0; a_rownum<n_A_rows; a_rownum++){
            row_match = 0;
            for(colnum = 0; colnum < ncols; colnum++){
                if(A(a_rownum,colnum)==B(b_rownum,colnum)){
                    row_match++;
                }
            }
            if(row_match==ncols){
                plhs[0] = mxCreateDoubleScalar(1);
                return;            
            }        
        }
    }
    plhs[0] = mxCreateDoubleScalar(0);
    return;
}
