#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>

using namespace cv;

void ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel);

int Zahyo2PosiX(int rv_x);
int Zahyo2PosiY(int rv_y);

int origin_x = 1190;
int origin_y = 250;
int koma_dist = 41;
int koma_dist_y = 45;

int main()
{
    int Width = 0;
    int Height = 0;
    int Bpp = 0;
    std::vector<uint8_t> Pixels;

    ImageFromDisplay(Pixels, Width, Height, Bpp);
    Mat img = Mat(Height, Width, Bpp > 24 ? CV_8UC4 : CV_8UC3, &Pixels[0]);

    Mat Fu  = imread("kmb1.png", IMREAD_GRAYSCALE);
    Mat Kyo = imread("kmb2.png", IMREAD_GRAYSCALE);
    Mat Kei = imread("kmb3.png", IMREAD_GRAYSCALE);
    Mat Gin = imread("kmb4.png", IMREAD_GRAYSCALE);
    Mat Kin = imread("kmb5.png", IMREAD_GRAYSCALE);
    Mat Kaku= imread("kmb6.png", IMREAD_GRAYSCALE);
    Mat Hi  = imread("kmb7.png", IMREAD_GRAYSCALE);
    Mat Ou  = imread("kmb8.png", IMREAD_GRAYSCALE);
    
    Mat eFu  = imread("kmw1.png", IMREAD_GRAYSCALE);
    Mat eKyo = imread("kmw2.png", IMREAD_GRAYSCALE);
    Mat eKei = imread("kmw3.png", IMREAD_GRAYSCALE);
    Mat eGin = imread("kmw4.png", IMREAD_GRAYSCALE);
    Mat eKin = imread("kmw5.png", IMREAD_GRAYSCALE);
    Mat eKaku= imread("kmw6.png", IMREAD_GRAYSCALE);
    Mat eHi  = imread("kmw7.png", IMREAD_GRAYSCALE);
    Mat eOu  = imread("kmw8.png", IMREAD_GRAYSCALE);

    Mat Ban = imread("ban.jpg", IMREAD_GRAYSCALE);
    
    Rect cut( 25,25,40,60 );
    Fu  = Fu(cut);
    Kyo = Kyo(cut);
    Kei = Kei(cut);
    Gin = Gin(cut);
    Kin = Kin(cut);
    Kaku= Kaku(cut);
    Hi  = Hi(cut);
    Ou  = Ou(cut);

    eFu  = eFu(cut);
    eKyo = eKyo(cut);
    eKei = eKei(cut);
    eGin = eGin(cut);
    eKin = eKin(cut);
    eKaku= eKaku(cut);
    eHi  = eHi(cut);
    eOu  = eOu(cut);

    resize(Fu , Fu , Size(), 0.4, 0.4);
    resize(Kyo, Kyo, Size(), 0.4, 0.4);
    resize(Kei, Kei, Size(), 0.4, 0.4);
    resize(Gin, Gin, Size(), 0.4, 0.4);
    resize(Kin, Kin, Size(), 0.4, 0.4);
    resize(Kaku,Kaku,Size(), 0.4, 0.4);
    resize(Hi , Hi , Size(), 0.4, 0.4);
    resize(Ou , Ou , Size(), 0.4, 0.4);

    resize(eFu , eFu , Size(), 0.4, 0.4);
    resize(eKyo, eKyo, Size(), 0.4, 0.4);
    resize(eKei, eKei, Size(), 0.4, 0.4);
    resize(eGin, eGin, Size(), 0.4, 0.4);
    resize(eKin, eKin, Size(), 0.4, 0.4);
    resize(eKaku,eKaku,Size(), 0.4, 0.4);
    resize(eHi , eHi , Size(), 0.4, 0.4);
    resize(eOu , eOu , Size(), 0.4, 0.4);

    Ban = Ban(Rect(10,240,640,20));
    resize(Ban, Ban, Size(), 0.6, 0.6);

    Mat result;
    Mat src_image = img;   
    Mat bin_image;
    cvtColor(src_image, bin_image, CV_BGR2GRAY);
    //--------------------Fu---------------------
    matchTemplate(bin_image,  Fu, result, TM_CCORR_NORMED);
    std::vector<Point> detected_point;
    float threshold = 0.97f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Fu.cols, it->y + Fu.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "P"  << std::endl;
    }
    //------------------------Kyo----------------------
    matchTemplate(bin_image, Kyo, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.96f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Kyo.cols, it->y + Kyo.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "L"  << std::endl;
    }
    //------------------------Kei-----------------------
    matchTemplate(bin_image, Kei, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.96f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Kei.cols, it->y + Kei.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "N"  << std::endl;
    }
    //------------------------Gin-----------------------
    matchTemplate(bin_image, Gin, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.94f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Gin.cols, it->y + Gin.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "S"  << std::endl;
    }
    //------------------------Kin-----------------------
    matchTemplate(bin_image, Kin, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.95f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Kin.cols, it->y + Kin.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "G"  << std::endl;
    }
    //------------------------Kaku-----------------------
    matchTemplate(bin_image, Kaku, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.96f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Kaku.cols, it->y + Kaku.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "B"  << std::endl;
    }
    //-----------------------------HI----------------------
    matchTemplate(bin_image, Hi, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.94f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Hi.cols, it->y + Hi.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "R"  << std::endl;
    }
    //-----------------------------Ou----------------------
    matchTemplate(bin_image, Ou, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.94f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Ou.cols, it->y + Ou.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "K"  << std::endl;
    }

    //--------------------eFu---------------------
    matchTemplate(bin_image,  eFu, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.97f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eFu.cols, it->y + eFu.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "p"  << std::endl;
    }
    //------------------------eKyo----------------------
    matchTemplate(bin_image, eKyo, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.96f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eKyo.cols, it->y + eKyo.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX(it->x) << "," << Zahyo2PosiY(it->y) << "," << "l"  << std::endl;
    }
    //------------------------eKei-----------------------
    matchTemplate(bin_image, eKei, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.96f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eKei.cols, it->y + eKei.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX( it->x) << "," << Zahyo2PosiY( it->y) << "," << "n"  << std::endl;
    }
    //------------------------eGin-----------------------
    matchTemplate(bin_image, eGin, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.94f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eGin.cols, it->y + eGin.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX( it->x) << "," << Zahyo2PosiY( it->y) << "," << "s"  << std::endl;
    }
    //------------------------Kin-----------------------
    matchTemplate(bin_image, eKin, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.95f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eKin.cols, it->y + eKin.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX( it->x) << "," << Zahyo2PosiY( it->y) << "," << "g"  << std::endl;
    }
    //------------------------eKaku-----------------------
    matchTemplate(bin_image, eKaku, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.96f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eKaku.cols, it->y + eKaku.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX( it->x) << "," << Zahyo2PosiY( it->y) << "," << "b"  << std::endl;
    }
    //-----------------------------eHI----------------------
    matchTemplate(bin_image, eHi, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.94f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eHi.cols, it->y + eHi.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX( it->x ) << "," <<Zahyo2PosiY( it->y) << "," << "r"  << std::endl;
    }
    //-----------------------------eOu----------------------
    matchTemplate(bin_image, eOu, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.94f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + eOu.cols, it->y + eOu.rows), Scalar(0,0,255), 1, 8, 0);
      std::cout << Zahyo2PosiX( it->x ) << "," << Zahyo2PosiY( it->y) << "," << "k"  << std::endl;
    }
    //-------------------------------Ban--------------------------------
    matchTemplate(bin_image, Ban, result, TM_CCORR_NORMED);
    detected_point.clear();
    threshold = 0.995f;
    for (int y=0; y<result.rows; y++) {
      for (int x=0; x<result.cols; x++) {
	if (result.at<float>(y,x) > threshold)
	  detected_point.push_back(Point(x,y));
      }
    }
    for(auto it = detected_point.begin(); it!=detected_point.end(); ++it) {
      rectangle( src_image, *it, Point(it->x + Ban.cols, it->y + Ban.rows), Scalar(0,0,255), 1, 8, 0);
      //std::cout << it->x << "," << it->y << "," << "Ban"  << std::endl;
    }
    
    waitKey(0);
    return 0;
}

void ImageFromDisplay(std::vector<uint8_t>& Pixels, int& Width, int& Height, int& BitsPerPixel)
{
    Display* display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);

    XWindowAttributes attributes = {0};
    XGetWindowAttributes(display, root, &attributes);

    Width = attributes.width;
    Height = attributes.height;

    XImage* img = XGetImage(display, root, 0, 0 , Width, Height, AllPlanes, ZPixmap);
    BitsPerPixel = img->bits_per_pixel;
    Pixels.resize(Width * Height * 4);

    memcpy(&Pixels[0], img->data, Pixels.size());

    XDestroyImage(img);
    XCloseDisplay(display);
}

int Zahyo2PosiX(int rv_x){
  for(int i=0; i<9; ++i){
    if( rv_x< origin_x -i*koma_dist  && rv_x>(origin_x - (i+1)*koma_dist) ) return i+1;
  }
  return 0;
}

int Zahyo2PosiY(int rv_y){
  for(int i=-2; i<10; ++i){
    if( rv_y> origin_y + i*koma_dist_y && rv_y < (origin_y + (i+1)*koma_dist_y) ) return i+1;
  }
  return 0;
}
