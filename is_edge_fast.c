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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define A(i,j) A[(i) + (j)*n_A_rows]
#define B(i,j) B[(i) + (j)*n_B_rows]
#define vert1(i,j) vert1[(i) + (j)*n_cell_int]
#define vert2(i,j) vert2[(i) + (j)*n_cell_int]

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
    
    
    
    double *V1 = mxGetPr(prhs[0]);
    double *V2 = mxGetPr(prhs[1]);
    
    int k;
    int kk;
    /*
    mexPrintf("V1\n");
    for(k=0;k<6;k++){
        mexPrintf("%f  ",V1[k]);
    }
    mexPrintf("\n");
    mexPrintf("V2\n");
    for(k=0;k<6;k++){
        mexPrintf("%f  ",V2[k]);
    }
    mexPrintf("\n");
     */
    double p1[3] = {0,0,0};
    double q1[3] = {0,0,0};
    double p2[3] = {0,0,0};
    double q2[3] = {0,0,0};
    double n_cell = 1;
    
    for(k=0;k<3;k++){
        p1[k] = V1[k];
        q1[k] = V1[k+3];
        p2[k] = V2[k];
        q2[k] = V2[k+3];
        n_cell = n_cell*q2[k];
    }
    
    int n_cell_int = (int)n_cell;
    int n_dim = 3;
    /*
    mexPrintf("%d \n", n_cell_int);
    */
    double vert1_raw[n_cell_int*n_dim];
    memset( vert1_raw, 0, n_cell_int*n_dim*sizeof(double));
    double vert2_raw[n_cell_int*n_dim];
    memset( vert2_raw, 0, n_cell_int*n_dim*sizeof(double));
    double * vert1 = vert1_raw;
    double * vert2 = vert2_raw;    

    n_A_rows = n_cell_int;
    n_B_rows = n_cell_int;
    ncols = n_dim;
    int s = 0;
    
    int i;
    int j;
    
    for(i=0;i<q1[0];i++){
        for(j=0;j<q1[1];j++){
            for(k=0;k<q1[2];k++){
                vert1(s,0) = p1[0]+ 0.5 +(double)i;
                vert1(s,1) = p1[1]+ 0.5 +(double)j;
                vert1(s,2) = p1[2]+ 0.5 +(double)k;
                s = s+1;
            }
        }
    }

    s = 0;
    for(i=0;i<q2[0];i++){
        for(j=0;j<q2[1];j++){
            for(k=0;k<q2[2];k++){
                vert2(s,0) = p2[0]+ 0.5 +(double)i;
                vert2(s,1) = p2[1]+ 0.5 +(double)j;
                vert2(s,2) = p2[2]+ 0.5 +(double)k;
                s = s+1;
            }
        }
    }
    /*
    mexPrintf("Here we go\n");
    for(k=0;k<8;k++){
        for(kk=0;kk<3;kk++){
            mexPrintf("%lf  ",vert2(k,kk));
        }
        mexPrintf("\n");
    }
    mexPrintf("\n");
    */
    
    /*
    mexPrintf("n_A_rows: %d\n", n_A_rows);
    mexPrintf("n_B_rows: %d\n", n_B_rows);
    mexPrintf("ncols: %d\n", ncols);
    */
    
    /* create a pointer to the real data in the input matrix  */
    double *A = vert1;
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
    double *B = vert2;
    /*
    mexPrintf("B\n");
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
