/********************************************************************
*
* Copyright (c) 2017, Vanessa Feng.
*
* Rewrite from Alex-vad-ffnn which is writen by Python, we want to 
* use it to Andrews equipment which writen by Java. Because of better 
* transferring this feature， we need to rewrite it by C or C++.
*
*********************************************************************/
#ifndef __MFCCFRONTEND_H
#define __MFCCFRONTEND_H

#include <vector>
#include <deque>
#include <complex>
#include <cmath>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <bitset>

using namespace std;
#define INF 1000000000000
const double PI=3.1415926536;

class MFCCFrontEnd{
public:
	MFCCFrontEnd(int sample_rate, int frame_size, double preemcoef, int numchans, int numceps, int n_frames, int lofreq, int hifreq, bool mel_banks_only);
	~MFCCFrontEnd();
	void InitHamming();
	void HammingWindow(vector<double> buf, vector<double> &data);
	void preemphasis(vector<double> frame,vector<double> &out_frame);
	vector<double> param(vector<double> frame, vector<double> mfcc);
	void getMFCCs();
	
	//double FrmEnergy(short* data);
	void computerFFT(vector<double> buffer,vector<complex<double> >& vec);
	void FFT(const unsigned long & fftlen, vector<complex<double> >& vec);
	void InitFilt(double **w, int num_filt); 
	void CreateFilt(double **w, int num_filt, int Fs, int high, int low);
	void mag_square(vector<complex<double> > & vec, vector<double> & vec_mag);
	void Mel_EN(double **w, int num_filt, vector<double>& vec_mag, double * M_energy);
	void Cepstrum(double *M_energy,double *mfcc_queue);
	void Ceps_melonly(double *M_energy,double *mfcc_queue);
	
private:
	int samplerate;
	int framesize;
	unsigned int FFTsize;
	unsigned int filt_size;
	int FiltNum;
	double *Hamming;      
	double prior;
	int HIGH;
	int LOW;	
	double preemcoef_m;
	bool mel_only;
	int n_frames_m;	

	vector<double> buffer;
	vector<double> data;
	
	//double energy;
	double *mel_energy;        
	vector<double> out_frame;
	vector<complex<double> > zero_padded;
	vector <double> fft_mag;
	
	int numceps;
	double **FiltWeight;
	double **w;
	int LOGENERGY;
	double *mfcc_queue;
	vector<double> mfcc;

};

#endif // MFCCFRONTEND_H
