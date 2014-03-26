//algoritmo para cargar una imagen

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int R_MIN = 0;
int R_MAX = 255;
int G_MIN = 0;
int G_MAX = 255;
int B_MIN = 0;
int B_MAX = 255;

void on_trackbar(int , void*)
{
	
}

void createTrackbars(){
	namedWindow("trackbars");

 	createTrackbar("R_MIN", "trackbars", &R_MIN, R_MAX, on_trackbar);
	createTrackbar("R_MAX", "trackbars", &R_MAX, R_MAX, on_trackbar);
	createTrackbar("G_MIN", "trackbars", &G_MIN, G_MAX, on_trackbar);
	createTrackbar("G_MAX", "trackbars", &G_MAX, G_MAX, on_trackbar);
	createTrackbar("B_MIN", "trackbars", &B_MIN, B_MAX, on_trackbar);
	createTrackbar("B_MAX", "trackbars", &B_MAX, B_MAX, on_trackbar);
}
int main (void){
 
    cv::Mat image1;//crea una imagen de dimensiones 0
    cv::Mat image2;
    cv::Mat image3;
    cv::Mat image4;
    cv::Mat image5;
    cv::Mat image6;
    cv::Mat image7;
    cv::Mat image8;
    cv::Mat ROI;
  
    
    image1 = imread("../media/1.JPG",1); //cargar una imagen de una ruta
    
	if(!image1.data){//comprueba si la imagen se cargo
		cout<<"error al leer"<<endl;
   	 }
    
    
    	else{
	  
	  int key = 0;
		while (key != 1)
		{
		namedWindow("original image");//crea ventana para mostrar la imagen
		createTrackbars();//llama la funcion que va crear las barras para controlar el filtro de la funcion inRange();
		ROI=image1(cv::Rect(500,1000,1000,800));
		
		
//   				inRange(ROI,//matriz de entrada
//   					Scalar(0,160,10),//limite inferior
//   					Scalar(255,255,255),//limite superior
//   					image4//matriz de salida
//   				  
//   				);
				
				
				
				cvtColor(ROI, image2, CV_BGR2XYZ);
				imshow("1  color XYZ",image2);
				//vamos a eliminar los insectos mas oscuros
				      threshold(image2, image3, 93, 255 ,1);
				      //threshold(image2, image3, R_MIN, R_MAX ,1);
				      imshow("2  threshold despues de xyz",image3);
				      
				      cvtColor(image3, image4, CV_BGR2GRAY);
				      imshow("3  escala de grises",image4);
				      
				      threshold(image4, image5, 82, 255 ,0);
				      dilate(image5, image5,cv::Mat(),cv::Point(-1,-1),3);
				      imshow("4  binario luego de grises",image5);
				      threshold(image5, image5, 82, 255 ,1);
				       
				//inputMat.copyTo(outputMat, maskMat);
				ROI.copyTo(image1, image5);					///**************ERROR******************
				imshow("insectos negros eliminados",image1);
				
				inRange(image1,//matriz de entrada
   					Scalar(5,160,10),//limite inferior
   					Scalar(255,255,255),//limite superior
   					image6//matriz de salida
   				  
   				);
				 
				 
				 
				//inRange(image1, Scalar(R_MIN,G_MIN,B_MIN), Scalar(R_MAX,G_MAX,B_MAX), image6);
				imshow("inrange",image6);
				//threshold(image4, image4, 0, 255 ,1);
				//ROI.copyTo(image5, image4);
				
				
			//threshold(image4, image5, 240, 255 ,0);
			//Canny(image4,image1,100,200);
			//erode(image2, image2,MORPH_RECT);
			//dilate(image2, image2,cv::Mat(),cv::Point(-1,-1),3);
			
// 			imshow("camera",ROI);
// 			imshow("XYZ",image4);
// 			imshow("mascar",image);
				image1.~Mat();
			waitKey(0);
		}
		
		
		
	}
    	//waitKey(0);//espera hasta que presiones alguna tecla
return 0;
}
