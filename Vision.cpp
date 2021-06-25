
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include "Global.h"
#include "Vision.h"

#include "Coordinate.h"

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
VideoCapture cap(webcamID);

int diameter = 40;

Coordinate leftVizorCoord;
Coordinate rightVizorCoord;

void setVizor(bool isLeft, Rect area) {
	int x = (((area.br().x - area.tl().x) / 2) + area.tl().x);
	int y = (((area.br().y - area.tl().y) / 2) + area.tl().y);
	circle(gameWindow, Point(x, y), (diameter * screenScale), detection, thickness);
	x -= halfScreenWidth;
	y -= (screenHeight / 2);
	if (isLeft)
	{

		leftVizorCoord.x = x;
		leftVizorCoord.y = y;
	}else{
		rightVizorCoord.x = x;
		rightVizorCoord.y = y;
	}

	

}

Coordinate getLeftVizorCoord() {
	return leftVizorCoord;
}

Coordinate getRightVizorCoord() {
	return rightVizorCoord;
}

void updateVision() {

		gameWindow = imread(gameBackgroundPath);
		resize(gameWindow, gameWindow, Size(screenWidth*screenScale, screenHeight*screenScale));
		cap.read(cam);
		cam.copyTo(target);
		cvtColor(target, target, COLOR_BGR2HSV);
		resize(cam, cam, gameWindow.size());
		resize(target, target, gameWindow.size());

		inRange(target, blueLow, blueHigh, mask);

		//find and draw contours
		vector<vector<Point>> contours ;
		findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
		vector<Rect> leftContours, rightContours;
		
		bool leftactive = false;
		bool rightactive = false;

		//divide contours
		for(vector<Point> var : contours)
		{
			Rect contourbind = boundingRect(var);
			if (contourbind.area()>distanceThreshold) {
				if(contourbind.br().x<(halfScreenWidth) && !leftactive){
					setVizor(true, contourbind);
					leftactive = true;
				}
				if(contourbind.tl().x> (halfScreenWidth) && !rightactive){
					setVizor(false, contourbind);
					rightactive = true;
				}
			}
		}
		//imshow("GameWindow", gameWindow);
		waitKey(1);
	}
