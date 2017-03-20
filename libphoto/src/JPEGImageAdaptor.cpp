#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

#include "JPEGImageAdaptor.h"
#include "jpeglib.h"
#include "PixelBuffer.h"
#include "ColorData.h"
#include "Image.h"
#include "ImageIOException.h"

Image JPEGImageAdaptor::load(const std::string fileName) 
{
    PixelBuffer* loadedImageBuffer = NULL;
    
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    
    FILE * infile;		
    JSAMPARRAY buffer;		
    int row_stride;		
    
    if ((infile = fopen(fileName.c_str(), "rb")) == NULL) {
        throw ImageIOException("Could not load JPEG file " + fileName);
    }

    cinfo.err = jpeg_std_error(&jerr);

    jpeg_create_decompress(&cinfo);
    
    jpeg_stdio_src(&cinfo, infile);
    
    (void) jpeg_read_header(&cinfo, TRUE);
   
    (void) jpeg_start_decompress(&cinfo);

    int width, height;
    width = cinfo.output_width;
    height = cinfo.output_height;

    loadedImageBuffer = new PixelBuffer(cinfo.output_width, cinfo.output_height, new ColorData(0.0,0.0,0.0));
  
    row_stride = cinfo.output_width * cinfo.output_components;

    buffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    int y = 0;
    while (cinfo.output_scanline < cinfo.output_height) {
 
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);

        for (int x = 0; x < cinfo.output_width; x++) {
            int r, g, b, a = 0;
            r = (int) *(buffer[0]+(x*3));
            g = (int) *(buffer[0]+(x*3)+1);
            b = (int) *(buffer[0]+(x*3)+2);
            a = 255;
            loadedImageBuffer->setPixel(x, cinfo.output_height-(y+1), ColorData(r/255.0f,g/255.0f,b/255.0f,a/255.0f));
        }
        y+=1;
    }
    
    (void) jpeg_finish_decompress(&cinfo);
    
    jpeg_destroy_decompress(&cinfo);
    
    fclose(infile);

    return Image(width, height, loadedImageBuffer->getData());
}

void JPEGImageAdaptor::save(const std::string fileName, Image image) 
{
    struct jpeg_compress_struct cinfo;
  
    struct jpeg_error_mgr jerr;

    FILE * outfile;		
    JSAMPROW row_pointer[1];	
    int row_stride;		
  
    cinfo.err = jpeg_std_error(&jerr);
 
    jpeg_create_compress(&cinfo);

    if ((outfile = fopen(fileName.c_str(), "wb")) == NULL) {
        throw ImageIOException("Could not save JPEG file " + fileName);
    }
    
    const ColorData *bufferToSave = image.getData();
    jpeg_stdio_dest(&cinfo, outfile);
    
    cinfo.image_width = image.getWidth(); 	
    cinfo.image_height = image.getHeight();
    cinfo.input_components = 3;		
    cinfo.in_color_space = JCS_RGB; 	

    jpeg_set_defaults(&cinfo);

    jpeg_set_quality(&cinfo, 100, TRUE );
 
    jpeg_start_compress(&cinfo, TRUE);

    row_stride = cinfo.image_width * 3;	
    
    const int width = image.getWidth();
    const int height = image.getHeight();
    JSAMPLE* image_buffer = new JSAMPLE[width * height * 3];
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            ColorData currentPixel = bufferToSave[x + ((y)  * width)];
            image_buffer[((height-(y+1))*width+x)*3] = (JSAMPLE) (currentPixel.getRed()*255.0);
            image_buffer[((height-(y+1))*width+x)*3+1] = (JSAMPLE) (currentPixel.getGreen()*255.0);
            image_buffer[((height-(y+1))*width+x)*3+2] = (JSAMPLE) (currentPixel.getBlue()*255.0);
        }
    }
    
    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = & image_buffer[cinfo.next_scanline * row_stride];
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    
    delete[] image_buffer;
    
    jpeg_finish_compress(&cinfo);

    fclose(outfile);

    jpeg_destroy_compress(&cinfo);
}

