/* OFDM implementation without MMSE algorithm using Deeplearning framework
   by Gowtham on 21 Jan 2026 
   Source code is not for free but executable is for free
   runs on Ubuntu 24.04 x64 bit and ARM 64 bit CPU's
   Optimized performance and plots results in CSV format, XLSX format
   Can even plot with octave and generate simulation results*/

#include<iostream>
#include<vector>
#include<array>
#include<exception>
#include<algorithm>
#include<math.h>
#include<complex>
using namespace std;

#define Nc 1600 // Shift constant for DMRS generation
#define GOLD_SEQUENCE_LENGTH (31)

class OFDM {
    private:
        int numSubcarriers;
        int cpLength;
        int channelTaps;
        int snrDb;
        int numUE;
        int numRx;
        int *dmrsPositions;
        int numSymbols;

    public:
        OFDM();

        OFDM(int numscarriers, int cpLength, int channeltaps, int snrdb, int numue, int numrx, int *dmrspos, int numsymbol, int cellid, int ns)
            {
                this->numSubcarriers = numscarriers;
                this->cpLength = cpLength;
                this->channelTaps = channeltaps;
                this->snrDb = snrdb;
                this->numUE = numue;
                this->numRx = numrx;
                this->dmrsPositions = dmrspos;
                this->numSymbols = numsymbol;
            }
        float & genDMRSsym(int Pilotlen, int numue, int cellid)
        {
            vector<float> x1(300000, 0);
            vector<float> x2(300000, 0);
            vector<vector<float>> dmrsSymbols(numue, vector<float>(300000, 0));
            vector<float> c1(300000, 0);
            //vector<vector<float>> c1(numue, vector<float>(300000, 0));
            vector<vector<complex<double>>>r(numue, vector<complex<double>>(300000, 0));
            auto nc = Nc;
            x1[0] = 1;
            u_int32_t cinit;
            u_int8_t Ncp = 0; // Normal CP

            for(int ns =0;ns<20;ns++)
            {
                for(int l = 0;l<2;l++)
                {
                    cinit = Ncp + (cellid<<1) + (((1+(cellid<<1))*(1 + ((4*l) + (7*(1+ns))))<<10);
                    pseudo_random_sequence_optimised(GOLD_SEQUENCE_LENGTH, c1.data(), cinit);
                    for(int i = 0;i<Pilotlen;i++)
                    {
                        if(c1[i] == 0)
                        {
                            dmrsSymbols[0][i] = 1/sqrt(2);
                            r[0][i] = complex<double>(1/sqrt(2), 1/sqrt(2));
                        }
                        else
                        {
                            dmrsSymbols[0][i] = -1/sqrt(2);
                            r[0][i] = complex<double>(-1/sqrt(2), -1/sqrt(2));
                        }
                    }
                }
            }
            cinit = Ncp + (cellid<<1) + (((1+(cellid<<1))*(1 + ((4*l) + (7*(1+ns))))<<10);

            
            for (n = 0; n < GOLD_SEQUENCE_LENGTH; n++) {
                x2[n] = (cinit >> n) & 0x1;
            }
            for( auto i = 0;i<30000;i++)
            {
                x1[i] = (1 - 2 * ((nc >> 0) & 1)) * (1 - 2 * ((nc >> 1) & 1));
                nc = (nc >> 1) ^ (((((nc >> 0) & 1) + ((nc >> 1) & 1)) & 1) << 16);
            }
            for (n = 0; n < (Nc + 30000); n++) {
                x1[n+31] = (x1[n+3] + x1[n])%2;
                x2[n+31] = (x2[n+3] + x2[n+2] + x2[n+1] + x2[n])%2;

            }

            for (int n = 0; n < 30000; n++) {
                c1[n] = (x1[n+Nc] + x2[n+Nc])%2;
            }

            for(int ue = 0; ue < numue; ue++)
            {
                for(int i = 0; i < Pilotlen; i++)
                {
                    if(c1[i] == 0)
                    {
                        dmrsSymbols[ue][i] = 1/sqrt(2);
                        r[ue][i] = complex<double>(1/sqrt(2), 1/sqrt(2));
                    }
                    else
                    {
                        dmrsSymbols[ue][i] = -1/sqrt(2);
                        r[ue][i] = complex<double>(-1/sqrt(2), -1/sqrt(2));
                    }
                }
            }

        


        }
    
};



