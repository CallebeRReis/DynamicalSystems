#include"../include/LyapExp.hpp"
#include"../include/rungekutta4thSquare.hpp"
#include"../include/penduli.hpp"
#include<cmath>
#include<iostream>

std::vector<double> LyapunovExponents (std::vector<double>(*function)(std::vector<double>,double)
                                      ,std::vector<double>initcoord, double step, int iterations)
{
    int NumEq=4; 
    std::vector<double> exponents(NumEq,0);
    std::vector<double> norm(NumEq,0);
    std::vector<double> GramCoef(NumEq,0);
    std::vector<std::vector<double>> coord(iterations);
for(int l=0;l<iterations;l++)
{
    coord[l+1]=rungeKutta4thSquare(function, coord[l], 1e-3, step, 4);
    //Normalização do primeiro vetor
        for(int i=0;i<NumEq;i++)
        {
            norm[0]+=pow(coord[l+1][NumEq*i+1],2);
        }
        norm[0]=sqrt(norm[0]);
        for(int i=0;i<NumEq;i++)
        {
            coord[l+1][NumEq*i+1]/=norm[0];        
        }
        //Normalização dos demais vetores
        for(int i=1;i<NumEq;i++)
        {
            for(int j=0;j<i-1;j++)
            {
                for(int k=0;k<NumEq;k++)
                {
                    GramCoef[j]+=coord[l+1][NumEq*k+i]*coord[l+1][NumEq*k+j];
                }
            }
            for(int j=0;j<NumEq;j++)
            {
                for(int k=0;k<i-1;k++)
                {
                    coord[l+1][NumEq*j+i]-=GramCoef[k]*coord[l+1][NumEq*j+i];
                }
            }
            for(int j=0;j<NumEq;j++)
            {
                norm[i]+=pow(coord[l+1][NumEq*j+i],2);
            }
            norm[i]=sqrt(norm[i]);
            for(int j=0;j<NumEq;j++)
            {
                coord[l+1][NumEq*j+i]*=norm[i];
            }
            //Cálculo de expoente de Lypunov
            for(int j=0;j<NumEq;j++)
            {
                exponents[j]=+log(norm[j])/log(2.0);
            }
            std::cout<<coord[l+1][0]<<"    "<<exponents[0]/coord[l+1][0]
                                    <<"    "<<exponents[1]/coord[l+1][0]
                                    <<"    "<<exponents[2]/coord[l+1][0]
                                    <<"    "<<exponents[3]/coord[l+1][0]<<std::endl;
            




        }
    }   








    return exponents;
}