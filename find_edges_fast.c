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
#include <stdbool.h>

#define vert1(i,j) vert1[(i) + (j)*n_cell_int_1]
#define vert2(i,j) vert2[(i) + (j)*n_cell_int_2]
#define V(i,j) V[(i) + (j)*6]
#define E(i,j) E[(i) + (j)*n_V]



__global__ void is_edge( double *V, bool *E, n_rows, n_V){
    int rownum = blockIdx.x%n_V;
    int colnum = blockIdx.x/n_V;
    int k;
    int kk;
    double p1[3] = {0,0,0};
    double q1[3] = {0,0,0};
    double p2[3] = {0,0,0};
    double q2[3] = {0,0,0};
    int n_cell_int_1 = 1;
    int n_cell_int_2 = 1;
    int n_dim = 3;
    /*
    double n_cell_1 = 1;
    double n_cell_2 =1;
     */
    
    for(k=0;k<n_dim;k++){
        p1[k] = V1[k];
        q1[k] = V1[k+3];
        p2[k] = V2[k];
        q2[k] = V2[k+3];
        
        n_cell_int_1 = n_cell_int_1*((int)q1[k]);
        n_cell_int_2 = n_cell_int_2*((int)q2[k]);
    }
    
    double * vert1_raw;
    vert1_raw = (double *)mxMalloc(n_cell_int_1*n_dim*sizeof(double));
    memset( vert1_raw, 0, n_cell_int_1*n_dim*sizeof(double));
    double * vert2_raw;
    vert2_raw = (double *)mxMalloc(n_cell_int_2*n_dim*sizeof(double));
    memset( vert2_raw, 0, n_cell_int_2*n_dim*sizeof(double));
    
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
    
    int vert1_rownum;
    int vert2_rownum;
    int colnum;
    int row_match;
    
    for(vert2_rownum = 0; vert2_rownum<n_cell_int_2; vert2_rownum++){
        for(vert1_rownum = 0; vert1_rownum<n_cell_int_1; vert1_rownum++){
            row_match = 0;
            
            for(colnum = 0; colnum < n_dim; colnum++){
                if(vert1(vert1_rownum,colnum)==vert2(vert2_rownum,colnum)){
                    row_match++;
                }
            }
             
            if(row_match==n_dim){
                mxFree(vert1_raw);
                mxFree(vert2_raw);
                return 1;
            }        
            
        }
    }
    mxFree(vert1_raw);
    mxFree(vert2_raw);   
    return 0;
}

void find_edges_fast(void)
{
    int n_V;
    int n_rows;
    FILE * datafp;
    FILE * valuefp;
    FILE * outfp;
    datafp = fopen("v_data.txt","r");
    valuefp = fopen("v_file.txt","r");
    outfp = fopen("E.txt","w");
    
    fscanf(datafp,"%d,%d",&n_rows,&n_V);
    fclose(datafp);
    printf("%d,%d",n_rows, n_V);
    
    int k;
    int kk;
    double *V = malloc(n_rows*n_V*sizeof(double));
    for(k=0; k<n_rows*n_V; k++){
        fscanf(valuefp,"%d,",V[k]);
    }
    fclose(valuefp);
    bool *E = malloc(n_V*n_V*sizeof(bool));

    double *V_d;
    bool *E_d;
    // Allocate device memory
    cudaMalloc((void **)&V_d, n_V*n_rows*sizeof(double));
    cudaMalloc((void **)&E_d, n_V*n_V*sizeof(bool));

    //Copy data to device memory
    cudaMemcpy(V_d, &V, n_V*n_rows*sizeof(double));

    is_edge<<<n_V*n_V,1 >>>(V_d,E_d,n_rows,n_V);
    /*
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
            E(kk,k) = E(k,kk);
        }
    }
    */

    //Copy result back to local from device
    cudaMemcpy(&E, E_d, n_V*n_V*sizeof(bool), cudaMemcpyDeviceToHost);
    cudaFree(E_d);
    cudaFree(V_d);
    free(V);
    for(k=0;k<n_V;k++){
        for(kk=0;kk<n_V;kk++){
            fprintf(outfp,"%d,",E(k,kk));
        }
        fprintf(outfp,"\n");
    }
    fclose(outfp)
}
