#include <iostream>
#include <cmath>
using namespace std;

//Smoking Gun Interactive C++ coding test
//All output is in main method, at the end of this code

bool isBetween (float numCheck, float num1, float num2); //function prototype declaration

struct Coord{        
//created as a struct instead of a class as suggested by the coding test. functionally the same as a class but the rectangle class constructor did not accept coordinates as objects. I don't know why this was the case.
    float x, y;
};

class Rectangle {
    // an axis-aligned rectangle has four corners but only needs two. the other two can be extrapolated.
    Coord coords[2];
public:
    Rectangle (Coord, Coord);        //constructor only needs two coordinates
    Rectangle (const Rectangle &rect){
        coords[0] = rect.coords[0];
        coords[1] = rect.coords[1];};    //copy constructor
    Rectangle& operator = (const Rectangle &rect){
        coords[0] = rect.coords[0];
        coords[1] = rect.coords[1];};    //assignment operator
    
    // test asked for a rectangle class with "initial size and coordinates." I am not sure what this meant, as the size is dependant on the coordinates and can't be determined without them. I added this unused area function in case that was what the test was asking for.
    float area();
    
    //Getter functions. Would have been nicer to simply return the array instead of, but C++ does not allow this, and I was having trouble understanding how to use pointers at all, let alone pointers which led to a data structure (the coordinate) instead of the value. This is my first foray into C++, but I still would have preferred a more elegant solution.
    Coord getc0() {return coords[0];};
    Coord getc1() {return coords[1];};
    
    bool isContained (Coord);
    bool intersects (Rectangle);
};


Rectangle::Rectangle (Coord r0, Coord r1) {
    //Constructor class. generates rectangle based on two input coordinates, but the two coordinates in the object are the upper left and bottom right.
    
    coords[0] = r0;
    coords[1] = r1;
    
    if(r0.x <= r1.x){
        coords[0].x = r0.x;
        coords[1].x = r1.x;
    }else{
        coords[0].x = r1.x;
        coords[1].x = r0.x;
    }

    if(r0.y <= r1.y){
        coords[0].y = r0.y;
        coords[1].y = r1.y;
    }else{
        coords[0].y = r1.y;
        coords[1].y = r0.y;
    }
}

float Rectangle::area(){
    //Simple area calculation. Uses absolute value since area is always positive.
    float area = abs((coords[0].x-coords[1].x)*(coords[0].y-coords[1].y));
    return area;
}



bool Rectangle::isContained(Coord test){
    //Very easy to determine if a point is within a rectangle. If the point is within the X and Y ranges, it is contained within the rectangle itself.
    if (isBetween(test.x, coords[0].x, coords[1].x) && isBetween(test.y, coords[0].y, coords[1].y)){
        return true;
    }else{
        return false;
    }
}

bool Rectangle::intersects(Rectangle rect1){
    //if the rightmost edge of one rectangle is to the left of the leftmost edge other, they do not intersect.
    if (coords[0].x > rect1.coords[1].x || rect1.coords[0].x > coords[1].x)
        return false;
        
    //if the uppermost edge of one rectangle is below the lowest edge of the other, they do not intersect.
    if (coords[0].y > rect1.coords[1].y || rect1.coords[0].y > coords[1].y)
        return false;
        
    //in the case that one rectangle totally overlaps another, they are not considered to be intersecting
    if(
        (isBetween(coords[0].x, rect1.coords[0].x, rect1.coords[1].x) &&
        isBetween(coords[1].x, rect1.coords[0].x, rect1.coords[1].x) &&
        isBetween(coords[0].y, rect1.coords[0].y, rect1.coords[1].y) &&
        isBetween(coords[1].y, rect1.coords[0].y, rect1.coords[1].y))
        ||
        (isBetween(rect1.coords[0].x, coords[0].x, coords[1].x) &&
        isBetween(rect1.coords[1].x, coords[0].x, coords[1].x) &&
        isBetween(rect1.coords[0].y, coords[0].y, coords[1].y) &&
        isBetween(rect1.coords[1].y, coords[0].y, coords[1].y))
        )
        return false;
        
    return true;
}

bool isBetween (float numCheck, float num1, float num2){
    //helper function with checks if the first input is between the second two, inclusive.
    if (num2 >= num1){
        if ((numCheck >= num1) && (numCheck <= num2)){
            return true;
        }else{
            return false;
        }
    }else{
        if ((numCheck >= num2) && (numCheck <= num1)){
            return true;
        }else{
            return false;
        }
    }
}

void rectangleInfo (Rectangle rect){
    //helper function which checks all information on a rectangle.
    cout << "Rectangle point 0: " << rect.getc0().x << ", " << rect.getc0().y << endl;
    cout << "Rectangle point 1: " << rect.getc1().x << ", " << rect.getc1().y << endl;
    //cout << "Rectangle area: " << rect.area() << endl << endl;;
}

void testIntersection (Rectangle objRect, Rectangle inputRect){
    if (objRect.intersects(inputRect)){
        cout << "The rectangles intersect" << endl << endl;
    }else{
        cout << "The rectangles don't intersect" << endl << endl;
    }
}

void rectangleTest(){
//test coordinates
    Coord c0;
    c0.x = 2;
    c0.y = 4;
    Coord c1;
    c1.x = 11;
    c1.y = 17;
    Coord c2;
    c2.x = 1;
    c2.y = 8;
    Coord c3;
    c3.x = 10;
    c3.y = 15;



    //tests constructor, copy constructer, assignment operators:

    Rectangle rect(c0, c1);
    cout << "Initially created rectangle 1:" << endl;    
    rectangleInfo(rect);

    Rectangle rect2(c2, c3);
    cout << "Rectangle 2 created from different coordinates:" << endl;
    rectangleInfo(rect2);
    rect2 = rect;
    cout << "Rectangle 2 after assignment operator:" << endl;
    rectangleInfo(rect2);

    Rectangle rect3 = rect;
    cout << "Rectangle 3 created via copy constructor:" << endl;
    rectangleInfo(rect3);    
    
    Rectangle rect4(c2, c3);
    cout << "Rectangle 4 created from different coordinates:" << endl;
    rectangleInfo(rect4);

    //test contain function
    if (rect.isContained(c2)){
        cout << "Point " << c2.x << ", " << c2.y << " is contained within rectangle 1." << endl << endl;
    }else{
        cout << "Point " << c2.x << ", " << c2.y << " is not contained within rectangle 1." << endl << endl;
    }

    if (rect.isContained(c3)){
        cout << "Point " << c3.x << ", " << c3.y << " is contained within rectangle 1." << endl << endl;
    }else{
        cout << "Point " << c3.x << ", " << c3.y << " is not contained within rectangle 1." << endl << endl;
    }

    //test intersection function
    if (rect.intersects(rect3)){
        cout << "The rectangles 1 and 4 intersect" << endl << endl;
    }else{
        cout << "The rectangles 1 and 4 don't intersect" << endl << endl;
    }

    //Creates 16 vertices in a 4x4 grid, allowing all possible overlap conditions.
    Coord coords[16];
    coords[0].x = 1;
    coords[0].y = 4;
    coords[1].x = 2;
    coords[1].y = 4;
    coords[2].x = 3;
    coords[2].y = 4;
    coords[3].x = 4;
    coords[3].y = 4;
    coords[4].x = 1;
    coords[4].y = 3;
    coords[5].x = 2;
    coords[5].y = 3;
    coords[6].x = 3;
    coords[6].y = 3;
    coords[7].x = 4;
    coords[7].y = 3;
    coords[8].x = 1;
    coords[8].y = 2;
    coords[9].x = 2;
    coords[9].y = 2;
    coords[10].x = 3;
    coords[10].y = 2;
    coords[11].x = 4;
    coords[11].y = 2;
    coords[12].x = 1;
    coords[12].y = 1;
    coords[13].x = 2;
    coords[13].y = 1;
    coords[14].x = 3;
    coords[14].y = 1;
    coords[15].x = 4;
    coords[15].y = 1;

    //Creates array of 12 different rectangles allowing all overlap conditions
    Rectangle rects[12] = {
        Rectangle(coords[0],coords[6]),     //0
        Rectangle(coords[5],coords[15]),    //1
        Rectangle(coords[1],coords[10]),    //2
        Rectangle(coords[4],coords[15]),    //3
        Rectangle(coords[4],coords[10]),    //4
        Rectangle(coords[1],coords[15]),    //5
        Rectangle(coords[0],coords[15]),    //6
        Rectangle(coords[5],coords[10]),    //7
        Rectangle(coords[0],coords[5]),     //8
        Rectangle(coords[10],coords[15]),   //9
        Rectangle(coords[1],coords[14]),    //10
        Rectangle(coords[4],coords[11])     //11
    };

    for (int i = 0; i < 12; i++){
        cout << "Rectangle " << i << endl;
        rectangleInfo(rects[i]);
        cout << endl;
    }

	//all possible rectangle arrangements are tested

    cout << "Test 1: Rectangles 0 and 1 should intersect:" << endl;
    testIntersection(rects[0], rects[1]);

    cout << "Test 2: Rectangles 2 and 3 should intersect:" << endl;
    testIntersection(rects[2], rects[3]);
    testIntersection(rects[3], rects[2]);

    cout << "Test 3: Rectangles 4 and 5 should intersect:" << endl;
    testIntersection(rects[4], rects[5]);
    testIntersection(rects[5], rects[4]);

    cout << "Test 4: Rectangles 6 and 7 should not intersect:" << endl;
    testIntersection(rects[6], rects[7]);
    testIntersection(rects[7], rects[6]);

    cout << "Test 5: Rectangles 8 and 9 should not intersect:" << endl;
    testIntersection(rects[8], rects[9]);

    cout << "Test 6: Rectangles 10 and 11 should intersect:" << endl;
    testIntersection(rects[10], rects[11]);
    testIntersection(rects[11], rects[10]);
}

bool factorsTwoThreeFive(int num){
    //returns true if a number equals 1, or has 2, 3, and 5 as its only prime factors
    if (num == 0 || num == 1){
        return true;
    }else if (num%2 == 0){
        factorsTwoThreeFive(num/2);
    }else if (num%3 == 0){
        factorsTwoThreeFive(num/3);
    }else if (num%5 == 0){
        factorsTwoThreeFive(num/5);
    }else{
        return false;
    }
}

void factorTest(){
	//finds first 1500 numbers which have 2, 3, and 5 as their only prime factors
    int i = 1;
    int j = 1;
    
    while (i < 1501){
        if (factorsTwoThreeFive(j) || j == 1){
            if (i == 1500){
                cout << i << ". " << j << endl;
            }
            i++;
        }
        j++;
    }
}

int main (){
    
    rectangleTest();

    cout << endl;

    factorTest();

    return 0;
}





