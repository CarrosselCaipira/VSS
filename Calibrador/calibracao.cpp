//objectTrackingTutorial.cpp

//Written by  Kyle Hounslow 2015

//Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software")
//, to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
//and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
//IN THE SOFTWARE.

#include <sstream>
#include <string>
#include <iostream>
#include <opencv2/opencv.hpp>

#define ENTRADA_VIDEO "outcpp3.avi"
// #define ENTRADA_VIDEO 1

using namespace cv;
using namespace std;
//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 255;
int S_MIN = 255;
int V_MIN = 255;
int H_MAX = 0;
int S_MAX = 0;
int V_MAX = 0;
int option = 0;

//names that will appear at the top of each window
const string Janela0 = "Imagem Original";
const string Janela1 = "Imagem em HSV";
const string Janela2 = "Imagem Thresholded";
const string JanelaTrackbars = "Trackbars";

bool mouseClicked;//used for showing debugging windows, trackbars etc.
bool mouseIsDragging;//used for showing a rectangle on screen as user clicks and drags mouse
bool mouseMove;
bool rectangleSelected;
cv::Point initialClickPoint, currentMousePoint; //keep track of initial point clicked and current position of mouse
cv::Rect rectangleROI; //this is the ROI that the user has selected
vector<int> H_ROI, S_ROI, V_ROI;// HSV values from the click/drag ROI region stored in separate vectors so that we can sort them easily

//matrix storage for HSV image
Mat HSV;
//Matrix to store each frame of the webcam feed
Mat cameraFeed;
void on_trackbar(int, void*)
{//This function gets called whenever a
	// trackbar position is changed

	//for now, this does nothing.



}
void createTrackbars(){
	//create window for trackbars


	namedWindow(JanelaTrackbars, 0);
	//create memory to store trackbar name on window
	char TrackbarName[50];
	sprintf(TrackbarName, "H_MIN", H_MIN);
	sprintf(TrackbarName, "H_MAX", H_MAX);
	sprintf(TrackbarName, "S_MIN", S_MIN);
	sprintf(TrackbarName, "S_MAX", S_MAX);
	sprintf(TrackbarName, "V_MIN", V_MIN);
	sprintf(TrackbarName, "V_MAX", V_MAX);
	sprintf(TrackbarName, "Opcao", option);

	//create trackbars and insert them into window
	//3 parameters are: the address of the variable that is changing when the trackbar is moved(eg.H_LOW),
	//the max value the trackbar can move (eg. H_HIGH),
	//and the function that is called whenever the trackbar is moved(eg. on_trackbar)
	//                                  ---->    ---->     ---->
	createTrackbar("H_MIN", JanelaTrackbars, &H_MIN, 255, on_trackbar);
	createTrackbar("H_MAX", JanelaTrackbars, &H_MAX, 255, on_trackbar);
	createTrackbar("S_MIN", JanelaTrackbars, &S_MIN, 255, on_trackbar);
	createTrackbar("S_MAX", JanelaTrackbars, &S_MAX, 255, on_trackbar);
	createTrackbar("V_MIN", JanelaTrackbars, &V_MIN, 255, on_trackbar);
	createTrackbar("V_MAX", JanelaTrackbars, &V_MAX, 255, on_trackbar);
	createTrackbar("0: Area Campo\n 1: Calibracao de Cor.", JanelaTrackbars, &option, 1, on_trackbar);


}

void trataEventosMouse(int event, int x, int y, int flags, void* param) {
	if (event == CV_EVENT_RBUTTONDOWN) {
		int H_MIN = 255;
		int S_MIN = 255;
		int V_MIN = 255;
		int H_MAX = 0;
		int S_MAX = 0;
		int V_MAX = 0;
	}

	if(option == 0) {
		//get handle to video feed passed in as "param" and cast as Mat pointer
		Mat* videoFeed = (Mat*)param;

		if (event == CV_EVENT_LBUTTONDOWN && mouseIsDragging == false) {
			//keep track of initial point clicked
			initialClickPoint = cv::Point(x, y);
			//user has begun dragging the mouse
			mouseIsDragging = true;
		}
		/* user is dragging the mouse */
		if (event == CV_EVENT_MOUSEMOVE && mouseIsDragging == true) {
			//keep track of current mouse point
			currentMousePoint = cv::Point(x, y);
			//user has moved the mouse while clicking and dragging
			mouseMove = true;
		}
		/* user has released left button */
		if (event == CV_EVENT_LBUTTONUP && mouseIsDragging == true) {
			//set rectangle ROI to the rectangle that the user has selected
			rectangleROI = Rect(initialClickPoint, currentMousePoint);

			//reset boolean variables
			mouseIsDragging = false;
			mouseMove = false;
			rectangleSelected = true;
		}
	}

	// se for 1, fazemos a calibragem das cores (pegamos o min e max do HSV)
	if(option == 1) {
		if (event == CV_EVENT_LBUTTONDOWN) {
			mouseClicked = true;
			//keep track of initial point clicked
			initialClickPoint = cv::Point(x, y);
			int tempH = ((int)HSV.at<cv::Vec3b>(initialClickPoint.y, initialClickPoint.x)[0]);
			int tempS = ((int)HSV.at<cv::Vec3b>(initialClickPoint.y, initialClickPoint.x)[1]);
			int tempV = ((int)HSV.at<cv::Vec3b>(initialClickPoint.y, initialClickPoint.x)[2]);

			// para componente H
			if(tempH > H_MAX)
				H_MAX = tempH;
			else{
				if(tempH < H_MIN)
					H_MIN = tempH;
			}
			// para componente S
			if(tempS > S_MAX)
				S_MAX = tempS;
			else{
				if(tempS < S_MIN)
					S_MIN = tempS;
			}
			// Para a componente V
			if(tempV > V_MAX)
				V_MAX = tempV;
			else{
				if(tempV < V_MIN)
					V_MIN = tempV;
			}
		}
	}
}

int main(int argc, char* argv[]) {

	//matrix storage for binary threshold image
	Mat threshold;

	//some boolean variables for different functionality within this
	//program
	bool trackObjects = true;
	//x and y values for the location of the object
	int x = 0, y = 0;
	//video capture object to acquire webcam feed
	VideoCapture capture;
	//open capture object at location zero (default location for webcam)
	// abrindo video de teste
	while(true) {
		capture.open(ENTRADA_VIDEO);
		//set height and width of capture frame
	    // disabling auto-focus -> nao funcionou
	    // capture.set(CV_CAP_PROP_SETTINGS, 1);
		//must create a window before setting mouse callback
		cv::namedWindow(Janela0);
		//set mouse callback function to be active on "Webcam Feed" window
		//we pass the handle to our "frame" matrix so that we can draw a rectangle to it
		//as the user clicks and drags the mouse
		cv::setMouseCallback(Janela0, trataEventosMouse, &cameraFeed);
		//initiate mouse move and drag to false
		mouseIsDragging = false;
		mouseMove = false;
		rectangleSelected = false;
		//start an infinite loop where webcam feed is copied to cameraFeed matrix
		//all of our operations will be performed within this loop

    int i = 0;
		while(1) {
			mouseClicked = false;
			//store image to matrix
			capture.read(cameraFeed);
			if(cameraFeed.empty())
				break;

       /* HISTOGRAM EQUALIZATION BEGIN */

      cv::Mat lab_image;
      cv::cvtColor(cameraFeed, lab_image, CV_BGR2Lab);
      // Extract the L channel
      std::vector<cv::Mat> lab_planes(3);
      cv::split(lab_image, lab_planes);  // now we have the L image in lab_planes[0]

      // apply the CLAHE algorithm to the L channel
      cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE();
      clahe->setClipLimit(4);
      cv::Mat dst;
      clahe->apply(lab_planes[0], dst);

      // Merge the the color planes back into an Lab image
      dst.copyTo(lab_planes[0]);
      cv::merge(lab_planes, lab_image);

      // convert back to RGB
      cv::Mat image_clahe;
      cv::cvtColor(lab_image, image_clahe, CV_Lab2BGR);

      /*HISTOGRAM EQUALIZATION END */

      /*Mat imageHist = equalizeIntensity(cameraFeed);

      imshow("HISTOGRAM", imageHist);
      waitKey(30);*/

			//convert frame from BGR to HSV colorspace
			cvtColor(image_clahe, HSV, CV_BGR2HSV);
			//filter HSV image between values and store filtered image to
			//threshold matrix
			inRange(HSV, Scalar(H_MIN, S_MIN, V_MIN), Scalar(H_MAX, S_MAX, V_MAX), threshold);

			//create slider bars for HSV filtering
			createTrackbars();
			imshow(Janela1, HSV);
			imshow(Janela2, threshold);


			cv::rectangle(image_clahe, rectangleROI, cv::Scalar(255), 1, 8, 0);
			imshow(Janela0, image_clahe);

			if(mouseClicked == true)
				cout << "CLICADO" << '\n';
			// se esta na opcao de desenhar retangulo, mostra as informacoes relevantes
			if((option == 0) && (rectangleROI.width > 0) && (rectangleROI.height > 0))
				cout << "OS CAMPO COMECA EM: x: " << rectangleROI.x << " y: " << rectangleROI.y << ". Com " << rectangleROI.width << "X" << rectangleROI.height << '\n';
			if(option == 1) {
				std::cout << "OS PARAMETROS MINIMO E MAXIMO DE COR SAO:" << '\n';
				cout << "H_MIN: " << H_MIN << endl;
				cout << "H_MAX: " << H_MAX << endl;
				cout << "S_MIN: " << S_MIN << endl;
				cout << "S_MAX: " << S_MAX << endl;
				cout << "V_MIN: " << V_MIN << endl;
				cout << "V_MAX: " << V_MAX << endl;
			}

			waitKey(30);
			i++;
		}
		capture.release();
	}






	return 0;
}
