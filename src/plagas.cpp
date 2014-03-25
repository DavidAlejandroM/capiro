//algoritmo para cargar una imagen

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int T_MIN = 0;
int T_MAX = 255;


void on_trackbar(int , void*)
{
	
}

void createTrackbars(){
	namedWindow("trackbars");

 	createTrackbar("Threshold", "trackbars", &T_MIN, T_MAX, on_trackbar);
	
}

int main (void){
 
    cv::Mat image1;//crea una imagen de dimensiones 0
    cv::Mat image2;
    cv::Mat image3;
    cv::Mat image4;
    cv::Mat image5;
    cv::Mat ROI;
  
    
    image1 = imread("../media/3.JPG",1); //cargar una imagen de una ruta
    
	if(!image1.data){//comprueba si la imagen se cargo
		cout<<"error al leer"<<endl;
   	 }
    
    
    	else{
		namedWindow("original image");//crea ventana para mostrar la imagen

		ROI=image1(cv::Rect(500,50,1600,1000));
				
				cvtColor(ROI, image2, CV_BGR2XYZ);
				threshold(image2, image3, 150, 255 ,1);
				cvtColor(image3, image4, CV_BGR2GRAY);
				//dilate(image4, image5,cv::Mat(),cv::Point(-1,-1),3);
					
			threshold(image4, image5, 240, 255 ,0);
			Canny(image5,image1,100,200);
	//		erode(image2, image2,MORPH_RECT);
	//		dilate(image2, image2,cv::Mat(),cv::Point(-1,-1),3);
			
			imshow("camera",ROI);
			imshow("XYZ",image4);
			imshow("Thresh",image1);
		
		
		
		
	}
    	waitKey(0);//espera hasta que presiones alguna tecla
return 0;
}
