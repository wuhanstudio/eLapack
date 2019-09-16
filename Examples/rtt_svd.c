#include <rtthread.h>
#include <stdio.h>
#include <time.h>
#include <LinearAlgebra/declareFunctions.h>

/* Matlab Code */
// A =[0.84245  ,  0.23405  ,  0.69751  ,  0.27905  ,  0.18851  ,  0.61018   ,  0.62182  ,  0.71839  ,  0.79161   ,  0.56156  ,  0.83395  ,  0.092388 ,  0.8511    ,  0.44826  ,  0.82158;
//     0.84614  ,  0.15947  ,  0.096336 ,  0.80793  ,  0.35114  ,  0.42583   ,  0.2134   ,  0.75324  ,  0.31391   ,  0.22892  ,  0.94773  ,  0.81204  ,  0.62554   ,  0.28367  ,  0.26637;
//     0.26509  ,  0.91429  ,  0.14222  ,  0.28321  ,  0.11607  ,  0.41188   ,  0.10071  ,  0.18224  ,  0.75723   ,  0.89125  ,  0.62494  ,  0.83016  ,  0.46448   ,  0.73119  ,  0.10982;
//     0.45197  ,  0.44562  ,  0.27909  ,  0.76019  ,  0.014571 ,  0.42705   ,  0.70214  ,  0.64936  ,  0.98451   ,  0.59632  ,  0.07654  ,  0.95633  ,  0.18574   ,  0.92716  ,  0.65401;
//     0.48034  ,  0.38327  ,  0.32906  ,  0.34794  ,  0.68673  ,  0.54113   ,  0.34142  ,  0.48561  ,  0.37221   ,  0.16097  ,  0.15569  ,  0.63287  ,  0.17518   ,  0.055447 ,  0.44536;
//     0.54119  ,  0.34478  ,  0.53297  ,  0.2796   ,  0.95212  ,  0.5353    ,  0.8202   ,  0.32707  ,  0.0062771 ,  0.64993  ,  0.057361 ,  0.59959  ,  0.16867   ,  0.67892  ,  0.52882;
//     0.082573 ,  0.96676  ,  0.080315 ,  0.48813  ,  0.33496  ,  0.4436    ,  0.01436  ,  0.89664  ,  0.49167   ,  0.37092  ,  0.31586  ,  0.54683  ,  0.65159   ,  0.38531  ,  0.20697;
//     0.35775  ,  0.42437  ,  0.79392  ,  0.49724  ,  0.01319  ,  0.0074932 ,  0.66462  ,  0.6506   ,  0.9889    ,  0.27213  ,  0.99607  ,  0.68418  ,  0.70238   ,  0.81493  ,  0.46062;
//     0.22609  ,  0.59924  ,  0.74631  ,  0.81566  ,  0.92784  ,  0.47376   ,  0.83531  ,  0.47031  ,  0.97093   ,  0.44778  ,  0.42997  ,  0.71882  ,  0.36504   ,  0.34216  ,  0.95187;
//     0.87475  ,  0.22003  ,  0.71901  ,  0.90968  ,  0.27265  ,  0.16106   ,  0.21283  ,  0.14918  ,  0.16776   ,  0.83038  ,  0.43605  ,  0.85075  ,  0.54771   ,  0.77479  ,  0.24739;
//     0.21203  ,  0.65616  ,  0.63534  ,  0.57569  ,  0.22113  ,  0.48063   ,  0.24207  ,  0.54873  ,  0.25042   ,  0.82671  ,  0.88986  ,  0.41674  ,  0.95235   ,  0.89875  ,  0.15004;
//     0.86164  ,  0.89058  ,  0.66423  ,  0.60958  ,  0.47708  ,  0.18674   ,  0.66359  ,  0.92383  ,  0.48073   ,  0.79466  ,  0.64519  ,  0.69876  ,  0.0066587 ,  0.55114  ,  0.10979;
//     0.35586  ,  0.94772  ,  0.28888  ,  0.63119  ,  0.42774  ,  0.82597   ,  0.90274  ,  0.40152  ,  0.96414   ,  0.84376  ,  0.028355 ,  0.040771 ,  0.85359   ,  0.92875  ,  0.32352;
//     0.39274  ,  0.27788  ,  0.41549  ,  0.90884  ,  0.042767 ,  0.64168   ,  0.086933 ,  0.47941  ,  0.91491   ,  0.26425  ,  0.11667  ,  0.49996  ,  0.12644   ,  0.87136  ,  0.30768;
//     0.86527  ,  0.92393  ,  0.47957  ,  0.32175  ,  0.87965  ,  0.13719   ,  0.4014   ,  0.25277  ,  0.83936   ,  0.73476  ,  0.97174  ,  0.65243  ,  0.85813   ,  0.62705  ,  0.0013063;
//     0.34355  ,  0.43424  ,  0.34352  ,  0.34341  ,  0.94343  ,  0.45452   ,  0.343    ,  0.1243   ,  0.12522   ,  0.214343 ,  0.12432  ,  0.54534  ,  0.12442   ,  0.12467  ,  0.9988;
//     0.84245  ,  0.23405  ,  0.69751  ,  0.27905  ,  0.18851  ,  0.61018   ,  0.62182  ,  0.71839  ,  0.79161   ,  0.56156  ,  0.83395  ,  0.092388 ,  0.8511    ,  0.44826  ,  0.82158]

// [U, S, V] = svd(A)

#define row 17
#define column 15

static void elapack_svd(int argc, char const *argv[])
{

   clock_t start, end;
   float cpu_time_used;
   start = clock();

   double A[row*column] = {
               0.84245  ,  0.23405  ,  0.69751  ,  0.27905  ,  0.18851  ,  0.61018   ,  0.62182  ,  0.71839  ,  0.79161   ,  0.56156  ,  0.83395  ,  0.092388 ,  0.8511    ,  0.44826  ,  0.82158,
               0.84614  ,  0.15947  ,  0.096336 ,  0.80793  ,  0.35114  ,  0.42583   ,  0.2134   ,  0.75324  ,  0.31391   ,  0.22892  ,  0.94773  ,  0.81204  ,  0.62554   ,  0.28367  ,  0.26637,
               0.26509  ,  0.91429  ,  0.14222  ,  0.28321  ,  0.11607  ,  0.41188   ,  0.10071  ,  0.18224  ,  0.75723   ,  0.89125  ,  0.62494  ,  0.83016  ,  0.46448   ,  0.73119  ,  0.10982,
               0.45197  ,  0.44562  ,  0.27909  ,  0.76019  ,  0.014571 ,  0.42705   ,  0.70214  ,  0.64936  ,  0.98451   ,  0.59632  ,  0.07654  ,  0.95633  ,  0.18574   ,  0.92716  ,  0.65401,
               0.48034  ,  0.38327  ,  0.32906  ,  0.34794  ,  0.68673  ,  0.54113   ,  0.34142  ,  0.48561  ,  0.37221   ,  0.16097  ,  0.15569  ,  0.63287  ,  0.17518   ,  0.055447 ,  0.44536,
               0.54119  ,  0.34478  ,  0.53297  ,  0.2796   ,  0.95212  ,  0.5353    ,  0.8202   ,  0.32707  ,  0.0062771 ,  0.64993  ,  0.057361 ,  0.59959  ,  0.16867   ,  0.67892  ,  0.52882,
               0.082573 ,  0.96676  ,  0.080315 ,  0.48813  ,  0.33496  ,  0.4436    ,  0.01436  ,  0.89664  ,  0.49167   ,  0.37092  ,  0.31586  ,  0.54683  ,  0.65159   ,  0.38531  ,  0.20697,
               0.35775  ,  0.42437  ,  0.79392  ,  0.49724  ,  0.01319  ,  0.0074932 ,  0.66462  ,  0.6506   ,  0.9889    ,  0.27213  ,  0.99607  ,  0.68418  ,  0.70238   ,  0.81493  ,  0.46062,
               0.22609  ,  0.59924  ,  0.74631  ,  0.81566  ,  0.92784  ,  0.47376   ,  0.83531  ,  0.47031  ,  0.97093   ,  0.44778  ,  0.42997  ,  0.71882  ,  0.36504   ,  0.34216  ,  0.95187,
               0.87475  ,  0.22003  ,  0.71901  ,  0.90968  ,  0.27265  ,  0.16106   ,  0.21283  ,  0.14918  ,  0.16776   ,  0.83038  ,  0.43605  ,  0.85075  ,  0.54771   ,  0.77479  ,  0.24739,
               0.21203  ,  0.65616  ,  0.63534  ,  0.57569  ,  0.22113  ,  0.48063   ,  0.24207  ,  0.54873  ,  0.25042   ,  0.82671  ,  0.88986  ,  0.41674  ,  0.95235   ,  0.89875  ,  0.15004,
               0.86164  ,  0.89058  ,  0.66423  ,  0.60958  ,  0.47708  ,  0.18674   ,  0.66359  ,  0.92383  ,  0.48073   ,  0.79466  ,  0.64519  ,  0.69876  ,  0.0066587 ,  0.55114  ,  0.10979,
               0.35586  ,  0.94772  ,  0.28888  ,  0.63119  ,  0.42774  ,  0.82597   ,  0.90274  ,  0.40152  ,  0.96414   ,  0.84376  ,  0.028355 ,  0.040771 ,  0.85359   ,  0.92875  ,  0.32352,
               0.39274  ,  0.27788  ,  0.41549  ,  0.90884  ,  0.042767 ,  0.64168   ,  0.086933 ,  0.47941  ,  0.91491   ,  0.26425  ,  0.11667  ,  0.49996  ,  0.12644   ,  0.87136  ,  0.30768,
               0.86527  ,  0.92393  ,  0.47957  ,  0.32175  ,  0.87965  ,  0.13719   ,  0.4014   ,  0.25277  ,  0.83936   ,  0.73476  ,  0.97174  ,  0.65243  ,  0.85813   ,  0.62705  ,  0.0013063,
               0.34355  ,  0.43424  ,  0.34352  ,  0.34341  ,  0.94343  ,  0.45452   ,  0.343    ,  0.1243   ,  0.12522   ,  0.214343 ,  0.12432  ,  0.54534  ,  0.12442   ,  0.12467  ,  0.9988,
               0.84245  ,  0.23405  ,  0.69751  ,  0.27905  ,  0.18851  ,  0.61018   ,  0.62182  ,  0.71839  ,  0.79161   ,  0.56156  ,  0.83395  ,  0.092388 ,  0.8511    ,  0.44826  ,  0.82158};

   double U[row*row];
   double S[row*column];
   double V[column*column];

   // Solve
   svd(A, U, S, V, row, column);

   // print
   print(U, row, row);
   print(S, row, column);
   print(V, column, column);

   end = clock();
   cpu_time_used = ((float) (end - start)) / CLOCKS_PER_SEC;
   printf("\nTotal speed  was %f ms\n", cpu_time_used * 1000);
}
MSH_CMD_EXPORT(elapack_svd, elapack svd decomposition example);
