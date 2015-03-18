#ifndef _IMAGE_CUT_H_
#define _IMAGE_CUT_H_

#include "header.h"

namespace ImageEthan
{
	typedef struct _rect
	{
		int top;
		int bottom;
		int left;
		int right;
	}Rect_Ethan;
	
	class ImageCut
	{
	public:
		ImageCut(IplImage* BinaryImg,IplImage* SrcImage);//参数1必须是已经二值化的图像，参数2是三通道的源图像
		~ImageCut();

		void image_cut();//图像裁剪主代码

		IplImage* get_cut_image_Binary();//获取剪裁后的二值图像
		IplImage* get_cut_image_Color();//获取剪裁后的彩色图像
	
	private:
		IplImage* image_In; //输入图像
		IplImage* image_In_color;//输入三通道彩色图像
		IplImage* image_Out; //输出图像
		IplImage* image_Out_Color;//输出三通道彩色图像

		Rect_Ethan rect;
		int width, height;

		int black_pixel_num;
		int white_pixel_num;

		void image_scanning();
	};
}


#endif