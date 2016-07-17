#include "windowVercorized.h"

#include <string>
#include <sstream>
#include <iostream>

#ifdef _WIN32
#define CLEAR_CONSOLE() system("cls");
#else
#define CLEAR_CONSOLE() system("clear");
#endif

// console input
std::string readString(){
    std::string tmp;
    std::getline(std::cin, tmp);
    return tmp;
}
int readInt(){
    int value;
    std::stringstream sstr(readString());
    sstr >> value;
    while (sstr.bad()) {
        std::cout << "\nError: provided value is not of type integer, please enter a valid value" << std::endl;
        sstr.clear();
        sstr << readString();
        sstr >> value;
    }
    return value;
}
float readFloat(){
    float value;
    std::stringstream sstr(readString());
    sstr >> value;
    while (sstr.bad()) {
        std::cout << "\nError: provided value is not of type floatingpoint, please enter a valid value" << std::endl;
        sstr.clear();
        sstr << readString();
        sstr >> value;
    }
    return value;
}


int main() {
// read intervalls from console
    cf::Intervall range_x;
    std::cout << "Please provide a Intervall for the x-axes:\n";
    std::cout << "Intervall min: "; range_x.min = readFloat();
    std::cout << "Intervall max: "; range_x.max = readFloat();
    std::cout << std::endl;

    cf::Intervall range_y;
    std::cout << "Please provide a Intervall for the y-axes:\n";
    std::cout << "Intervall min: "; range_y.min = readFloat();
    std::cout << "Intervall max: "; range_y.max = readFloat();
    CLEAR_CONSOLE();

// create window and print mouse input
    cf::WindowRasterized window(800, range_x, range_y, "Hello world", cf::Color::ORANGE);
    std::cout << "Created window size:\n"
              << "Width : " << window.getImageWidth()  << std::endl
              << "Height: " << window.getImageHeight() << std::endl
                                                       << std::endl;
    window.show();
    cf::Point point;

    std::cout << "Please set 2 point on the window" << std::endl;
    window.waitMouseInput(point.x, point.y);
    window.drawCircle(point, 3, -1 /*fill circle*/, cf::Color::WHITE);
    window.show();

    std::cout << "Read intervall position:\n"
              << "Pos x: " << point.x << std::endl
              << "Pos y: " << point.y << std::endl
                                      << std::endl;

    point = window.transformPoint_fromImageIntervall(point);
    std::cout << "Read image position (in pixel):\n"
              << "Pos x: " << int(point.x) << std::endl
              << "Pos y: " << int(point.y) << std::endl
                                           << std::endl;

    std::cout << "\n\nPress enter to continue";
    getchar();
    CLEAR_CONSOLE();

// take 2 points from console and draw a line and a rectangle
//
// first   point: use interval position
// second  point: use pixel position
    std::cout << "Please provide a floatingpoint value within the intervall " << range_x << ":\n";
    point.x = readFloat();

    std::cout << std::endl;
    std::cout << "Please provide a floatingpoint value within the intervall " << range_y << ":\n";
    point.y = readFloat();

    cf::Point point2;
    std::cout << std::endl << std::endl;
    std::cout << "Please provide a integer value within the intervall [0-" << window.getImageWidth() - 1 << "]:\n";
    point2.x = readInt();

    std::cout << std::endl;
    std::cout << "Please provide a integer value within the intervall [0-" << window.getImageHeight() - 1 << "]:\n";
    point2.y = readInt();

    // translate position "point2" to intervall position
    point2 = window.transformPoint_toImgeIntervall(point2);

    // draw line and rectangle
    window.drawLine(point, point2, 2, cf::Color::BLACK);
    window.drawRectangle(point, point2, 2, cf::Color::GREEN);
    window.show();

    std::cout << "Press enter to finish the process";
    getchar();
    return 0;
}