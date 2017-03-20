#include "QuantizeFilter.h"
#include "ColorData.h"

QuantizeFilter::QuantizeFilter(int bins): m_bins(bins)
{
}

QuantizeFilter::~QuantizeFilter()
{
}


int compare(float upperBin, float lowerBin, float colorValue) {
	
	float lowerBinDifference, upperBinDifference;
	
	if(colorValue >= lowerBin && colorValue <= upperBin) {
		lowerBinDifference = colorValue - lowerBin;
		upperBinDifference = upperBin - colorValue;
			
		if(lowerBinDifference < upperBinDifference)
			return -1;
		else
			return 1;
	} else 
		return 0;
}


ColorData QuantizeFilter::convertPixel(ColorData pixel){

	float newRed, newBlue, newGreen;
	
	float currentRed   = pixel.getRed();
	float currentGreen = pixel.getGreen();
	float currentBlue  = pixel.getBlue();

	float binsContainer[m_bins];
	
	float multiplier = 1.0 / (float) m_bins;
	
		
	for(int i = 0; i < m_bins; i++) {
		binsContainer[i] = i * multiplier;
	}
	
	int result;
	bool rBinFound, gBinFound, bBinFound;
	rBinFound = gBinFound = bBinFound = false;
	
	for(int i = 0; i < m_bins-1; i++){
	
		if(!rBinFound) {
			result = compare(binsContainer[i+1], binsContainer[i], currentRed);
			
			if(result != 0) {
				if(result == -1) 
					newRed = binsContainer[i];
				else 
					newRed = binsContainer[i+1];
					
				rBinFound = true;
			}
		}
		
		if(!gBinFound) {
			result = compare(binsContainer[i+1], binsContainer[i], currentGreen);
			
			if(result != 0) {
				if(result == -1) 
					newGreen = binsContainer[i];
				else 
					newGreen = binsContainer[i+1];
					
				gBinFound = true;
			}
		}
		
		if(!bBinFound) {
			result = compare(binsContainer[i+1], binsContainer[i], currentBlue);
			
			if(result != 0) {
				if(result == -1) 
					newBlue = binsContainer[i];
				else 
					newBlue = binsContainer[i+1];
					
				bBinFound = true;
			}
		}
	
	}

	return ColorData(newRed, newGreen, newBlue);
}



