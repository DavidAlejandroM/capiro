//algoritmo para cargar una imagen

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;


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
	
    int i=0;//iesima fila
    int j=0;//jesima columna
    
    std::vector<std::vector<cv::Point> > contornos;//vector de contornos de la imagen original
    
    image8 = imread("../media/3.JPG",1); //cargar una imagen de una ruta
    
	if(!image8.data){//comprueba si la imagen se cargo
		cout<<"error al leer"<<endl;
   	 }
    
    
    	else{
	  
	  
		
			
			
			namedWindow("ROI");//crea ventana para mostrar la imagen
			//createTrackbars();//llama la funcion que va crear las barras para controlar el filtro de la funcion inRange();
				//Creamos una ROI ya que la imagen original es demasiado grande
				ROI=image8(cv::Rect(1000,2000,2000,600));
				imshow("ROI",ROI);
	  								
				cvtColor(ROI, image2, CV_BGR2XYZ);
				imshow("1  color XYZ",image2);
				//vamos a eliminar los insectos mas oscuros
				      threshold(image2, image3, 93, 255 ,1);
				      imshow("2  threshold despues de xyz",image3);
				      
				      cvtColor(image3, image4, CV_BGR2GRAY);
				      imshow("3  escala de grises",image4);
				      
				      threshold(image4, image5, 82, 255 ,0);
				      dilate(image5, image5,cv::Mat(),cv::Point(-1,-1),3);
				      imshow("4  binario luego de grises",image5);
				      threshold(image5, image5, 82, 255 ,1);
				      imshow("5 treshol sobre la misma",image5);
				
				
				//recorre toda la imagen pixel por pixel analizando donde hay blanco captura la coordenada
				//y imprime en la ROI
 				for(i=0 ; i<= image5.rows - 1 ; i++)
 				{
 					
 					for(j=0 ; j<=image5.cols - 1 ; j++)
 					{
 						
 						if(image5.at<uchar>(i,j)==0)
 						{
 							ROI.at<cv::Vec3b>(i,j)[0]=238;//enviamos un valor a el canal azul
							ROI.at<cv::Vec3b>(i,j)[1]=230;
							ROI.at<cv::Vec3b>(i,j)[2]=193;
 							
 						}
 						else
 						{
 							
 						}
 					}
 					
 					
 				}
 				
 				imshow("6 Roi mod",ROI);
// 				
// 				//aplicamos un filtro de color para filtar lo que no es parecido al color de los insectos
 				inRange(ROI,//matriz de entrada
    					Scalar(5,160,10),//limite inferior
    					Scalar(255,255,255),//limite superior
    					image6//matriz de salida
    				  
    				);
				imshow("7 filtro",image6);
				threshold(image6, image6, 0, 255 ,1);
				
				dilate(image6, image6,cv::Mat(),cv::Point(-1,-1),0);
				imshow("7.5 dilate",image6);
				threshold(image6, image6, 240, 255 ,0);
				
				
				Canny(image6,image1,100,200);
				dilate(image1, image1,cv::Mat(),cv::Point(-1,-1),1);
				imshow("8 Filtro Canny",image1);
				//buscamos los contornos
					float n = 0;
					int numero = 0;
					cv::findContours(	image1,
								contornos,
								1,
								1
					);
					
					for(int i=0;i<contornos.size();i++)//dibujamos los contornos en la imagen
					{
						float aux = contourArea(contornos[i]);
						/*cv::drawContours(	ROI, //imagen donde se va a dibujar
									contornos,//vector de contorno
									i,
									Scalar(255,255,80),3,0);*/
						if(160<aux && aux<500)
						{
							cv::drawContours(ROI,contornos,i,Scalar(255,0,255),3,0);
							cout<<"aux =  "<<aux<<"contorno numero = "<<i<<endl;
							numero++;
						}
						
						/*if(n < contourArea(contornos[i]))
						{	
							n = contourArea(contornos[i]);
							cout << "Area " << i << ": " << contourArea(contornos[i]) << endl;
						}*/
						
					}
					//cv::drawContours(ROI,contornos,1752,Scalar(255,0,255),3,0);
					cout <<"Numero de Mosca Blanca Presente   ********" << numero <<"*******"<< endl;
					imshow("contornos",ROI);
		
					
		
		
	}
    	waitKey(0);//espera hasta que presiones alguna tecla
return 0;
}
