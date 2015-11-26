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

#define vert1(i,j) vert1[(i) + (j)*n_cell_int]
#define vert2(i,j) vert2[(i) + (j)*n_cell_int]
#define V(i,j) V[(i) + (j)*6]
#define E(i,j) E[(i) + (j)*n_V]



double is_edge( double *V1, double *V2){
        
    int k;
    int kk;
    double p1[3] = {0,0,0};
    double q1[3] = {0,0,0};
    double p2[3] = {0,0,0};
    double q2[3] = {0,0,0};
    int n_cell_int = 8;
    int n_dim = 3;
    
    for(k=0;k<n_dim;k++){
        p1[k] = V1[k];
        q1[k] = V1[k+3];
        p2[k] = V2[k];
        q2[k] = V2[k+3];
    }
    
    double vert1_raw[24];
    memset( vert1_raw, 0, n_cell_int*n_dim*sizeof(double));
    double vert2_raw[24];
    memset( vert2_raw, 0, n_cell_int*n_dim*sizeof(double));
    
    double * vert1 = vert1_raw;
    double * vert2 = vert2_raw;
    
    int i;
    int j;
    int s = 0;
    
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
   mexPrintf("V1\n"); 
   for(k=0;k<6;k++){
        mexPrintf("%lf,",V1[k]);
   }
   mexPrintf("\n");
    
   for(k=0;k<n_cell_int;k++){
        for(kk=0;kk<3;kk++){
            mexPrintf("%lf  ",vert1(k,kk));
        }
        mexPrintf("\n");
    }
    mexPrintf("\n");
    mexPrintf("\n");
    */
    /* create a pointer to the real data in the input matrix  */
    /*
    double *A = vert1;
    
    double *B = vert2;
      */
    
    
    
    int a_rownum;
    int b_rownum;
    int colnum;
    int row_match;

    for(b_rownum = 0; b_rownum<n_cell_int; b_rownum++){
        for(a_rownum = 0; a_rownum<n_cell_int; a_rownum++){
            row_match = 0;
            
            for(colnum = 0; colnum < n_dim; colnum++){
                if(vert1(a_rownum,colnum)==vert2(b_rownum,colnum)){
                    row_match++;
                }
            }
             
            if(row_match==n_dim){    
                return 1;
            }        
            
        }
    }
    return 0;
}


/* The gateway function */
void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    int n_V;
    n_V = mxGetN(prhs[0]);
    
    
    double *V = mxGetPr(prhs[0]);
    plhs[0] = mxCreateDoubleMatrix(n_V,n_V, mxREAL);
    /*
    mexPrintf("num rows: %d\n",mxGetM(plhs[0]));
    mexPrintf("num cols: %d\n",mxGetN(plhs[0]));
     */
    double *E = mxGetPr(plhs[0]);
    
    int k;
    int kk;
    int kkk;
    double V1[6];
    double V2[6];
     
    for(k=0;k<n_V;k++){
        for(kk=0;kk<k;kk++){
            for(kkk=0;kkk<6;kkk++){
                V1[kkk] = V(kkk,k);
                V2[kkk] = V(kkk,kk);
            }
            E(k,kk) = is_edge(V1,V2);
        }
    }
}
