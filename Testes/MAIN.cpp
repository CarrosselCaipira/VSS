//#include "../camera.hpp"
//#include "../robo.hpp"
//#include "../CPH.hpp"
//#include "../radio.hpp"
//#include "../tecnicoOfensivo.hpp"
#include <opencv2/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

int alpha_slider;
cv::Mat img;
cv::Mat aux;

static void on_trackbar( int, void* ) {
    img = aux.clone();
    cv::circle(img, cv::Point(50, alpha_slider), 10, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    
}

int main(int argc, char** argv){
    std::string nome = "Nome";
    img = cv::imread(argv[1], 1);
    aux = cv::imread(argv[1], 1);
    cv::Mat3b canvas(300, 300, cv::Vec3b(0, 255, 0));
    cv::namedWindow("Linear Blend");
    alpha_slider = 0;
    // cv::circle(img, cv::Point(50, 50), 10, cv::Scalar(0,0,255), cv::FILLED, cv::LINE_8);
    // cv::imshow(nome, img);  
    cv::createTrackbar(nome, "Linear Blend", &alpha_slider, 100, on_trackbar);
    while (true){
        cv::imshow("Linear Blend", img);
        cv::waitKey(30);
        //cv::destroyAllWindows();
        //img = aux.clone();
    }
}