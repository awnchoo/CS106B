/*
 * File: fractals.cpp
 * --------------------------
 * Name:
 * Section leader:
 * This file contains fractal problems for CS106B.
 */


#include "fractals.h"
#include <cmath>

using namespace std;

const int LEAF_COLOR = 0x2e8b57;   /* Color of all leaves of recursive tree (level 1) */
const int BRANCH_COLOR = 0x8b7765; /* Color of all branches of recursive tree (level >=2) */

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * top-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the top-left corner of the triangle.
 * @param y - The y coordinate of the top-left corner of the triangle.
 * @param size - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */
double sqrt3=sqrt(3);
void drawSierpinskiTriangleHelper(GWindow& gw, double x, double y, double size, int order){
    if(order>0){
        if(order==1){
            gw.drawLine(x,y,x+size,y);
            gw.drawLine(x,y,x+size/2,y+sqrt3*size/2);
            gw.drawLine(x+size,y,x+size/2,y+sqrt3*size/2);
        }else{
            drawSierpinskiTriangleHelper(gw,x,y,size/2,order-1);
            drawSierpinskiTriangleHelper(gw,x+size/2,y,size/2,order-1);
            drawSierpinskiTriangleHelper(gw,x+size/4,y+sqrt3*size/4,size/2,order-1);
        }

    }
}
void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    if(x<0||y<0||size<0){
        throw("exception");
    }else{
        drawSierpinskiTriangleHelper(gw,x,y,size,order);
    }

}
/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */
double Pi=3.14159265;
void drawTreeHelper(GWindow& gw, double x, double y, double size, int order,int theta) {
    if(order>0){
        if(order==1){
            gw.setColor("#2e8b57");
            gw.drawPolarLine(x,y,size,theta);
        }else{
            gw.drawPolarLine(x,y,size,theta);
            drawTreeHelper(gw,x+size*cos(theta*Pi/180),y-size*sin(theta*Pi/180),size/2,order-1,theta-30);
            drawTreeHelper(gw,x+size*cos(theta*Pi/180),y-size*sin(theta*Pi/180),size/2,order-1,theta-15);
            drawTreeHelper(gw,x+size*cos(theta*Pi/180),y-size*sin(theta*Pi/180),size/2,order-1,theta);
            drawTreeHelper(gw,x+size*cos(theta*Pi/180),y-size*sin(theta*Pi/180),size/2,order-1,theta+15);
            drawTreeHelper(gw,x+size*cos(theta*Pi/180),y-size*sin(theta*Pi/180),size/2,order-1,theta+30);
        }
    }
}
void drawTree(GWindow& gw, double x, double y, double size, int order) {
    if(x<0||y<0||size<0){
        throw("exception");
    }else{
        gw.setColor("#8b7765");
        drawTreeHelper(gw,x+size/2,y+size,size/2,order,90);
    }

}

/**
 * Draws a Mandelbrot Set in the graphical window give, with maxIterations
 * (size in GUI) and in a given color (zero for palette)
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Mandelbrot set.
 * @param minX - left-most column of grid
 * @param incX - increment value of columns of grid
 * @param minY - top-most row of grid
 * @param incY - increment value of rows of grid
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal; zero if palette is to be used
 */
void mandelbrotSet(GWindow& gw, double minX, double incX,
                   double minY, double incY, int maxIterations, int color) {

    // Creates palette of colors
    // To use palette:
    // pixels[r][c] = palette[numIterations % palette.size()];
    Vector<int> palette = setPalette();

    int width = gw.getCanvasWidth();
    int height = gw.getCanvasHeight();
    GBufferedImage image(width,height,0xffffff);
    gw.add(&image);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    for(int i=0;i<pixels.numRows();i++){
        for(int j=0;j<pixels.numCols();j++){
            Complex c=Complex(minX+i*incX,minY+j*incY);
            int numIterations=mandelbrotSetIterations(c,maxIterations);
            if(numIterations==maxIterations){
                pixels[i][j]=color;
            }else{
                pixels[i][j] = palette[numIterations % palette.size()];
            }
        }
    }

    image.fromGrid(pixels); // Converts and puts the grid back into the image
}

/**
 * Runs the Mandelbrot Set recursive formula on complex number c a maximum
 * of maxIterations times.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param c - Complex number to use for recursive formula.
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */
int mandelbrotSetIterations(Complex c, int maxIterations) {
    Complex z= Complex(0,0);
    return maxIterations-mandelbrotSetIterations(z,c,maxIterations); // Only here to make this compile
}
/**
 * An iteration of the Mandelbrot Set recursive formula with given values z and c, to
 * run for a maximum of maxIterations.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param z - Complex number for a given number of iterations
 * @param c - Complex number to use for recursive formula.
 * @param remainingIterations - The remaining number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */
int mandelbrotSetIterations(Complex z, Complex c, int remainingIterations) {
    if((z.abs()<4)&&(remainingIterations>0)){
        z=z*z+c;
        return mandelbrotSetIterations(z,c,remainingIterations-1);
    }else{
        return remainingIterations;
    }
}

// Helper function to set the palette
Vector<int> setPalette() {
    Vector<int> colors;

    // Feel free to replace with any palette.
    // You can find palettes at:
    // http://www.colourlovers.com/palettes

    // Example palettes:
    // http://www.colourlovers.com/palette/4480793/in_the_middle
    // string colorSt = "#A0B965,#908F84,#BF3C43,#9D8E70,#C9BE91,#A0B965,#908F84,#BF3C43";

    // http://www.colourlovers.com/palette/4480786/Classy_Glass
    // string colorSt = "#9AB0E9,#C47624,#25269A,#B72202,#00002E,#9AB0E9,#C47624,#25269A";

    // The following is the "Hope" palette:
    // http://www.colourlovers.com/palette/524048/Hope
    string colorSt =  "#04182B,#5A8C8C,#F2D99D,#738585,#AB1111,#04182B,#5A8C8C,#F2D99D";
    Vector<string>colorsStrVec = stringSplit(colorSt,",");
    for (string color : colorsStrVec) {
        colors.add(convertColorToRGB(trim(color)));
    }
    return colors;
}
