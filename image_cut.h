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
		ImageCut(IplImage* BinaryImg,IplImage* SrcImage);//����1�������Ѿ���ֵ����ͼ�񣬲���2����ͨ����Դͼ��
		~ImageCut();

		void image_cut();//ͼ��ü�������

		IplImage* get_cut_image_Binary();//��ȡ���ú�Ķ�ֵͼ��
		IplImage* get_cut_image_Color();//��ȡ���ú�Ĳ�ɫͼ��
	
	private:
		IplImage* image_In; //����ͼ��
		IplImage* image_In_color;//������ͨ����ɫͼ��
		IplImage* image_Out; //���ͼ��
		IplImage* image_Out_Color;//�����ͨ����ɫͼ��

		Rect_Ethan rect;
		int width, height;

		int black_pixel_num;
		int white_pixel_num;

		void image_scanning();
	};
}


#endif