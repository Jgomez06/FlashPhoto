#include <stdlib.h>

#include "TSDApplicationController.h"
#include "JPEGImageAdaptor.h"
#include "PNGImageAdaptor.h"


TSDApplicationController::TSDApplicationController() 
{
	// Initialize ImageAdaptors
	JPEGImageAdaptor* jpegAdaptor = new JPEGImageAdaptor();
	m_imageAdaptors.insert(std::make_pair("jpg", jpegAdaptor));
	m_imageAdaptors.insert(std::make_pair("jpeg", jpegAdaptor));
	m_imageAdaptors.insert(std::make_pair("png", new PNGImageAdaptor()));
	
}

TSDApplicationController::~TSDApplicationController()
{
}

