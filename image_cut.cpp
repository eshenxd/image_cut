#include "image_cut.h"


using namespace ImageEthan;


ImageCut::ImageCut(IplImage* img_src ,IplImage* img_color)
{
	image_In = img_src;
	image_In_color = img_color;
	image_Out = NULL;

	width = image_In->width;
	height = image_In->height;

	rect.left = 0;
	rect.right = width;

	black_pixel_num = 0;
	white_pixel_num = 0;
}

ImageCut::~ImageCut()
{
	if (!image_Out == NULL)
		cvReleaseImage(&image_Out);
}

IplImage* ImageCut::get_cut_image_Binary()
{
	return image_Out;
}

IplImage* ImageCut::get_cut_image_Color()
{
	return image_Out_Color;
}


void ImageCut::image_cut()
{
	image_scanning();

	image_Out = cvCreateImage(cvSize(width, rect.bottom - rect.top), image_In->depth, image_In->nChannels);
	image_Out_Color = cvCreateImage(cvSize(width, rect.bottom - rect.top), image_In_color->depth, image_In_color->nChannels);
	CvRect pos = cvRect(rect.left, rect.top, width, rect.bottom - rect.top);

	cvSetImageROI(image_In, pos);
	cvCopy(image_In, image_Out);
	cvResetImageROI(image_In);

	cvSetImageROI(image_In_color, pos);
	cvCopy(image_In_color, image_Out_Color);
	cvResetImageROI(image_In_color);

	return ;
}


/*
 *  扫描图片，获取图片中无内容的上边沿和下边沿
 */
void ImageCut::image_scanning()
{
	int i = 0;

	//由上至下扫描
	while (i<height)
	{
		uchar* tmp = (unsigned char*)(image_In->imageData + i*image_In->widthStep);

		for (int j = 0; j < width; j++)
		{
			int pvalue = (int)tmp[j];

			if (pvalue == 255)white_pixel_num++;
			else black_pixel_num++;
		}
		if ((double)black_pixel_num / width >= 0.1 && (double)white_pixel_num / width > 0.5)
		{

			rect.top = i > 25 ? i - 25 : i;
			break;
		}
		i = i + 5;
	}

	//由下至上扫描
	i = height-1;
	white_pixel_num = 0;
	black_pixel_num = 0;
	while (i>=0)
	{
		uchar* tmp = (unsigned char*)(image_In->imageData + i*image_In->widthStep);

		for (int j = 0; j < width; j++)
		{
			int pvalue = (int)tmp[j];

			if (pvalue == 255)white_pixel_num++;
			else black_pixel_num++;
		}
		if ((double)black_pixel_num / width >= 0.1 && (double)white_pixel_num / width > 0.5)
		{

			rect.bottom = (height-i) > 25 ? i + 25 : i;
			break;
		}
		i = i - 5;
	}

	return;
}