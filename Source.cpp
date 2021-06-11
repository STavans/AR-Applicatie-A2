
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat cam, gameWindow, target, mask;
string gameBackgroundPath = "Resources/gameWindow.png";

int webcamID = 0;

Scalar blueLow = Scalar(100, 150, 150);
Scalar blueHigh = Scalar(140, 255, 255);

int distanceThreshold = 300;

Scalar detection = Scalar(0, 0, 255);

int thickness = 3;


int scale = 1;

int diameter = 40;
int width = 640;
int height = 480;

void setVizor(bool isLeft, Rect area) {
	int x = ((area.br().x - area.tl().x) / 2) + area.tl().x;
	int y = ((area.br().y - area.tl().y) / 2) + area.tl().y;
	circle(gameWindow, Point(x, y), (diameter * scale), detection, thickness);
}

int main() {
	VideoCapture cap(webcamID);

	while (true)
	{
		gameWindow = imread(gameBackgroundPath);
		resize(gameWindow, gameWindow, Size(width*scale, height*scale));
		cap.read(cam);
		cam.copyTo(target);
		cvtColor(target, target, COLOR_BGR2HSV);
		resize(cam, cam, gameWindow.size());
		resize(target, target, gameWindow.size());

		inRange(target, blueLow, blueHigh, mask);

		//find and draw contours
		vector<vector<Point>> contours ;
		findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			cout << "this is the balls amount:" << contours.size() << endl;
		vector<Rect> leftContours, rightContours;
		
		bool leftactive = false;
		bool rightactive = false;

		//divide contours
		for(vector<Point> var : contours)
		{
			Rect contourbind = boundingRect(var);
			if (contourbind.area()>distanceThreshold) {
				if(contourbind.br().x<(width / 2) && !leftactive){
					setVizor(true, contourbind);
					leftactive = true;
				}
				if(contourbind.tl().x> (width / 2) && !rightactive){
					setVizor(false, contourbind);
					rightactive = true;
				}
			}
		}

		imshow("camera", cam);
		imshow("GameWindow", gameWindow);
		waitKey(1);
	}
	return 1;
}
