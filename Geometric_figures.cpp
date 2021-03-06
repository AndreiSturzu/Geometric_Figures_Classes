#include <iostream>
#include<istream>
#include<vector>
#include<math.h>

using namespace std;


//POINT
class Point {
    float x;
    float y;

    public:
        Point() {
            this->x = 0;
            this->y = 0;
        };

        Point(float x, float y) {
            this->x = x;
            this->y = y;
        };

        ~Point() {
            //cout<<"Point destroyed"<<endl;
        };

        void setX(float x) { this->x = x;}
        void setY(float y) {this->y = y;}

        pair<float, float> getCoordinates() const{
            return std::make_pair(this->x, this->y);
        };

        Point & operator = (const Point& B) {
            this->x = B.getCoordinates().first;
            this->y = B.getCoordinates().second;

            return *this;
        };

        friend ostream & operator << (ostream &out, const Point& p) {
            pair<float, float> coord = p.getCoordinates();
            out<<"Point of coordinates: "<<coord.first<<" "<<coord.second<<endl;
            return out;
        };

        friend istream & operator >> (istream &in,  Point &p) {
            float x, y;
            cout<<"Input coordinates of point"<<endl;
            cout<<"x = ";
            in>>x;
            cout<<"y = ";
            in>>y;

            p = Point(x,y);

            return in;
        };
};


//rounds up a number to 4 decimals
float roundup(float number) {
    float value = (int)(number * 10000 + .5);
    return (float)value / 10000;
};

//calculate the distance between 2 points
float distance(const Point& A, const Point& B) {
    float xa = A.getCoordinates().first;
    float ya = A.getCoordinates().second;

    float xb = B.getCoordinates().first;
    float yb = B.getCoordinates().second;

    return roundup(sqrt (pow((xa - xb),2) + pow((ya - yb), 2)));
};


//LINE
class Line {
    Point A;
    Point B;
    float slope; //line equation is y = slope * x + c;
    float c;

    public:
        Line() {
            this->A = Point();
            this->B = Point();
            this->slope = 0;
        };

        Line(const Point& A, const Point& B) {
            this->A = A;
            this->B = B;
            this->slope = roundup((A.getCoordinates().second - B.getCoordinates().second) / (A.getCoordinates().first - B.getCoordinates().first));
            this->c = A.getCoordinates().second - this->slope * A.getCoordinates().first;
        };

        ~Line() {
            //cout<<"Line destroyed"<<endl;
        };

        Point getPointA() const{
            return this->A;
        };

        Point getPointB() const {
            return this->B;
        };

        float getSlope() const{
            return this->slope;
        };

        float getConsOfLineEq() const{
            return this->c;
        };

        bool checkPointOnLine(const Point &P) {
            float y = P.getCoordinates().second;
            float x = P.getCoordinates().first;

            if(y == this->slope * x + this->c) {
                return 1;

            } else {
                return 0;
            }
        };

        bool perpendicularOnLine(const Line& AB) {
            if(this->slope == -1 / AB.getSlope())
                return 1;
            else
                return 0;
        };


        friend ostream & operator << (ostream &out, const Line& AB) {
            out<<"Line generated by points: "<<endl<<AB.getPointA()<<endl<<AB.getPointB()<<endl;
            return out;
        };

        friend istream & operator >> (istream &in, Line& AB) {
            Point A, B;
            cout<<"Input points of Line: "<<endl;
            cout<<"First Point = ";
            in>>A;
            cout<<"Second Point = ";
            in>>B;

            AB = Line(A,B);

            return in;
        };

};

class Square {
    Point initial; //left bottom point
    float side1;
    bool valid;
    vector <Point> points;

    public:
        Square() {
            this->initial = Point();
            this->side1 = 0;
            this->valid = 0;
        };

        virtual void describePoints() {
            this->points.clear();
            this->points.shrink_to_fit();

            if(this->valid) {
                Point A = this->initial;
                float xa = A.getCoordinates().first;
                float ya = A.getCoordinates().second;
                Point B = Point(xa, ya + side1);
                Point C = Point(xa + side1, ya + side1);
                Point D = Point(xa + side1, ya);

                this->points.push_back(A);
                this->points.push_back(B);
                this->points.push_back(C);
                this->points.push_back(D);
            } else {
                return;
            }
        };

        Square(const Point& A, float side1) {
            this->initial = A;
            this->side1 = roundup(side1);
            this->valid = 1;
        };

        ~Square() {
            this->clearPoints();
            //cout<<"Square destroyed"<<endl;
        };

        Point getInitialPoint() const {
            return this->initial;
        };

        float getSide1() const {
            return this->side1;
        };

        bool getValid() const {
            return this->valid;
        };

        vector<Point> getPoints() {
            return this->points;
        };

        void clearPoints() {
            this->points.clear();
            this->points.shrink_to_fit();
        };

        void setPointsABCD(const Point& A, const Point& B, const Point& C, const Point& D) {
            this->clearPoints();
            this->points.push_back(A);
            this->points.push_back(B);
            this->points.push_back(C);
            this->points.push_back(D);
        };

        void setInitialPoint(const Point& A) {
            this->initial = A;
        };

        void setValid(int v) {
            this->valid = v;
        };

        void setSide1(float s) {
            this->side1 = roundup(s);
        };

        virtual float perimeter() {
            return this->getSide1() * 4;
        };

        virtual float area() {
            return this->getSide1() * this->getSide1();
        };

        void print() {
            if(this->getValid()) {
                this->describePoints();
            cout<<"Points describing the figure are shown clockwise, starting with bottom-left point\n";
                for(Point p: this->points)
                    cout<<'\t'<<p;
            } else {
                cout<<"Invalid figure";
            }
        };

        friend ostream & operator << (ostream &out, const Square& S) {
            out<<"Square generated by point: "<<endl<<S.getInitialPoint()<<"and side "<<S.getSide1()<<endl;
            return out;
        };

        friend istream & operator >> (istream &in, Square& S) {
            Point A;
            float side;

            cout<<"Input initial point: "<<endl;
            in>>A;

            cout<<"Input side length: ";
            in>>side;

            S = Square(A, side);

            return in;
        };
};

class Rectangle: public virtual Square
{
    private:
        float side2;

    public:

        Rectangle(): Square() {this->side2 = 0;};

        Rectangle(const Point& A, float s1 , float s2): Square(A, s1), side2(roundup(s2)) {};

        ~Rectangle() {
            this->clearPoints();
            //cout<<"Rectangle destroyed"<<endl;
        };

        float getSide2() const {
            return this->side2;
        };

        void describePoints() {
            this->clearPoints();

            if(this->getValid()) {
                Point A = this->getInitialPoint();
                float xa = A.getCoordinates().first;
                float ya = A.getCoordinates().second;
                float s1 = this->getSide1();
                float s2 = this->getSide2();
                Point B = Point(xa, ya + s1);
                Point C = Point(xa + s2, ya + s1);
                Point D = Point(xa + s2, ya);

                this->setPointsABCD(A, B, C, D);
            } else {
                return;
            }
        };

        friend ostream& operator<<(ostream& out, Rectangle& R) {
            float width, length;
            Point point = R.getInitialPoint();
            float s1 = R.getSide1();
            float s2 = R.getSide2();
            if (s1 > s2)
            {
                width = s2;
                length = s1;
            }
            else
            {
                width = s1;
                length = s2;
            }
            out<<"Rectangle generated by point:"<<endl<<point
            <<"and width "<<width<<" and length "<<length<<endl;
            return out;
        };

        friend istream& operator>>(istream& in, Rectangle& R)
        {
            Point A;
            float side1;
            float side2;
            cout<<"Input initial point(Bottom Left Point): "<<endl;
            cout<<endl;
            in>>A;
            cout<<endl;

            cout<<"Input the side1 length of the Rectangle: "<<endl;
            in>>side1;
            cout<<"Input the side2 length of the Rectangle: "<<endl;
            in>>side2;
            cout<<endl;

            R = Rectangle(A, side1, side2);
            return in;
        };

        float perimeter() {
            return 2 * this->getSide1() + 2 * this->getSide2() ;
        };

        float area() {
            return this->getSide1() * this->getSide2();
        };

};

//RHOMBUS
class Rhombus: public virtual Square {
    Point opposite;

    public:
        Rhombus(): Square() {this->opposite = Point();};

        Rhombus(const Point& A, const Point& C, float s1): Square(A, s1), opposite(C) {
            float xa = A.getCoordinates().first;
            float ya = A.getCoordinates().second;

            float xd = xa + s1;
            float yd = ya;

            Point D = Point(xd, yd);
            if(distance(C, D) != s1)
                this->setValid(0);
        };

        ~Rhombus() {
            this->clearPoints();
            //cout<<"Rhombus destroyed"<<endl;
        };

        Point getOppositePoint() const {
            return this->opposite;
        };

        void describePoints() {
            this->clearPoints();

            if(this->getValid()) {
                Point A = this->getInitialPoint();
                Point C = this->getOppositePoint();
                float s1 = this->getSide1();
                float xa = A.getCoordinates().first;
                float ya = A.getCoordinates().second;
                float xc = C.getCoordinates().first;
                float yc = C.getCoordinates().second;

                Point B = Point(xc - s1, yc);
                Point D = Point(xa + s1, ya);

                this->setPointsABCD(A, B, C, D);
            } else {
                return;
            }
        };

        friend ostream & operator << (ostream &out, const Rhombus& Ro) {
            if(Ro.getValid()) {
                out<<"Rhombus generated by points: "<<endl<<Ro.getInitialPoint()<<Ro.getOppositePoint()
                <<"and side "<<Ro.getSide1()<<endl;
            } else {
                out<<"Cannot generate a Rhombus with specified parameters."<<endl;
            }
            return out;

        };

        friend istream & operator >> (istream &in, Rhombus& Ro) {
            Point A, C;
            float side;

            cout<<"Input initial point: "<<endl;
            in>>A;

            cout<<"Input opposite point: "<<endl;
            in>>C;

            cout<<"Input side length: ";
            in>>side;

            Ro = Rhombus(A, C, side);

            return in;
        };

        float perimeter() {
            if(this->getValid())
                return this->Square::perimeter();
            else
                return 0;
        }

        float area() {
            if(this->getValid()) {
                Point A = this->getInitialPoint();
                Point C = this->getOppositePoint();

                float ya = A.getCoordinates().second;
                float yc = C.getCoordinates().second;

                float side = this->getSide1();

                return side * (yc - ya);
            }
            else
                return 0;
        }

};

//PARALLELOGRAM
class Parallelogram: public Rectangle, public Rhombus {
    public:
        Parallelogram(): Rectangle(), Rhombus() {};

        Parallelogram(const Point& A, const Point& C, float s1, float s2): Rectangle(A, s1, s2), Rhombus(A, C, s1) {
            this->setSide1(s1);
            float xa = A.getCoordinates().first;
            float ya = A.getCoordinates().second;

            float xd = xa + s1;
            float yd = ya;

            Point D = Point(xd, yd);

            if(distance(C, D) != s2)
                this->setValid(0);
            else
                this->setValid(1);
        };

        ~Parallelogram() {
            this->clearPoints();
            //cout<<"Parallelogram destroyed"<<endl;
        };

        friend ostream & operator << (ostream &out, const Parallelogram& P) {
            if(P.getValid()) {
                out<<"Parallelogram generated by points: "<<endl<<P.getInitialPoint()<<P.getOppositePoint()
                <<"side1 "<<P.getSide1()<<", side2 "<<P.getSide2()<<endl;
            } else {
                out<<"Cannot generate a Parallelogram with specified parameters."<<endl;
            }
            return out;

        };

        friend istream & operator >> (istream &in, Parallelogram& P) {
            Point A, C;
            float s1, s2;

            cout<<"Input initial point: "<<endl;
            in>>A;

            cout<<"Input opposite point: "<<endl;
            in>>C;

            cout<<"Input side1 length: ";
            in>>s1;

            cout<<"Input side2 length: ";
            in>>s2;

            P = Parallelogram(A, C, s1, s2);

            return in;
        };

        void describePoints() {Rhombus::describePoints();}

        float perimeter() {
            if(this->getValid())
                return Rectangle::perimeter();
            else
                return 0;
        };

        float area() {
            if(this->getValid()) {
                Point A = this->getInitialPoint();
                Point C = this->getOppositePoint();

                float ya = A.getCoordinates().second;
                float yc = C.getCoordinates().second;

                float side = this->getSide1();

                return side * (yc - ya);
            }
            else
                return 0;
        };
};

//Trapezoid
class Trapezoid: public Parallelogram{
    float side3;

    public:
        Trapezoid(): Parallelogram() {this->side3 = 0;};

        Trapezoid(const Point& A, const Point& C, float s1, float s2, float s3): Parallelogram(A, C, s1, s2), side3(s3) {};

        ~Trapezoid(){
            this->clearPoints();
            //cout<<"Trapezoid destroyed"<<endl;
        };

        float getSide3() const {
            return this->side3;
        };

        void describePoints() {
            this->clearPoints();

            if(this->getValid()) {
                Point A = this->getInitialPoint();
                Point C = this->getOppositePoint();
                float s1 = this->getSide1();
                float s3 = this->getSide3();
                float xa = A.getCoordinates().first;
                float ya = A.getCoordinates().second;
                float xc = C.getCoordinates().first;
                float yc = C.getCoordinates().second;

                Point B = Point(xc - s3, yc);
                Point D = Point(xa + s1, ya);

                this->setPointsABCD(A, B, C, D);
            } else {
                return;
            }
        };

        friend ostream & operator << (ostream &out, const Trapezoid& T) {
            if(T.getValid()) {
                out<<"Trapezoid generated by points: "<<endl<<T.getInitialPoint()<<T.getOppositePoint()
                <<"first base "<<T.getSide1()<<", side "<<T.getSide2()<<", second base"<<T.getSide3()<<endl;
            } else {
                out<<"Cannot generate a Trapezoid with specified parameters."<<endl;
            }
            return out;

        };

        friend istream & operator >> (istream &in, Trapezoid& T) {
            Point A, C;
            float s1, s2, s3;

            cout<<"Input initial point: "<<endl;
            in>>A;

            cout<<"Input opposite point: "<<endl;
            in>>C;

            cout<<"Input side1 (first base) length: ";
            in>>s1;

            cout<<"Input side2 length: ";
            in>>s2;

            cout<<"Input side3 (second base) length: ";
            in>>s3;

            T = Trapezoid(A, C, s1, s2, s3);

            return in;
        };

        float perimeter() {
            if(this->getValid()) {
                Point A = this->getInitialPoint();
                Point C = this->getOppositePoint();
                float xc = C.getCoordinates().first;
                float yc = C.getCoordinates().second;
                return this->getSide1() + this->getSide2() + this->getSide3() + distance(A, Point(xc - this->getSide3(), yc));
            }
            else
                return 0;
        };

        float area() {
            if(this->getValid()) {
                Point A = this->getInitialPoint();
                Point C = this->getOppositePoint();

                float ya = A.getCoordinates().second;
                float yc = C.getCoordinates().second;

                float side1 = this->getSide1();
                float side3 = this->getSide1();

                return ((side1 + side3) / 2) * (yc - ya);
            }
            else
                return 0;
        };
};

//vectors which will store created figures
vector<Square> Sq;
vector<Rectangle> Re;
vector<Rhombus> Rho;
vector<Parallelogram> Pa;
vector<Trapezoid> Tr;

//creation of single objects
void single_menu()
{
    char selection;

    do {
        cout<<"\n\tFIGURES - named ABCD -  HAVE TWO SIDES PARALLEL WITH Ox AXIS\n";
        cout<<"\n\t         ****LENGTHS ARE ROUNDED TO 4 DECIMALS***\n";
        cout<<"\n\tSingle Menu";
        cout<<"\n\t========";
        cout<<"\n\tS - Create Square";
        cout<<"\n\ts - Create Square of point A(2,4) and side 10";
        cout<<"\n\tR - Create Rectangle";
        cout<<"\n\tr - Create Rectangle of point A(2,4) and width 5 and length 10";
        cout<<"\n\tH - Create Rhombus";
        cout<<"\n\ts - Create Rhombus of points A(0,0), C(6, 2 * sqrt(3)) and side 4";
        cout<<"\n\tP - Create Parallelogram";
        cout<<"\n\tp - Create Parallelogram of points A(0,0), C(8, 4 * sqrt(3)), width 4 and length 8";
        cout<<"\n\tT - Create Trapezoid";
        cout<<"\n\tt - Create Trapezoid of Points A(0,0), C(8, 4 * sqrt(3)), first-base 4, side 8 and second-base 2";
        cout<<"\n\tX - Exit\n";
        cout<<"\nEnter selection: ";

        // read the input
        cin>>selection;

        switch(selection)
        {
            case 'S' : {
                Square S;
                cin>>S;
                cout<<S;
                S.print();
                cout<<"Perimeter, Area: ";
                cout<<S.perimeter()<<" "<<S.area()<<endl;
                cout<<endl;
            }
            break;

            case 's' : {
                Square S = Square(Point(2,4), 10);
                Sq.push_back(S);
                cout<<S;
                S.print();
                cout<<"Perimeter, Area: ";
                cout<<S.perimeter()<<" "<<S.area()<<endl;
                cout<<endl;
                }
            break;

            case 'R' : {
                Rectangle R;
                cin>>R;
                cout<<R;
                R.print();
                cout<<"Perimeter, Area: ";
                cout<<R.perimeter()<<" "<<R.area()<<endl;
                cout<<endl;
            }
            break;

            case 'r' : {
                Rectangle R = Rectangle(Point(2,4), 5, 10);
                Re.push_back(R);
                cout<<R<<endl;
                R.print();
                cout<<endl;
                cout<<"Perimeter, Area: ";
                cout<<R.perimeter()<<" "<<R.area()<<endl;
                cout<<endl;
            }
            break;

            case 'H' :
            {
                Rhombus H;
                cin>>H;
                cout<<H;
                H.print();
                cout<<"Perimeter, Area: ";
                cout<<H.perimeter()<<" "<<H.area()<<endl;
                cout<<endl;
            }
            break;

            case 'h' : {
                Point A = Point(0,0);
                Point C = Point(6,2 * sqrt(3));
                Rhombus Ro = Rhombus(A, C, 4);
                Rho.push_back(Ro);
                cout<<Ro<<endl;
                Ro.print();
                cout<<endl;
                cout<<"Perimeter, Area: ";
                cout<<Ro.perimeter()<<" "<<Ro.area()<<endl;
                cout<<endl;
                }
            break;

            case 'P' :
            {
                Parallelogram P;
                cin>>P;
                cout<<P;
                P.print();
                cout<<"Perimeter, Area: ";
                cout<<P.perimeter()<<" "<<P.area()<<endl;
                cout<<endl;
            }
            break;

            case 'p' : {
                Point A = Point(0,0);
                Point C = Point(8, 4 * sqrt(3));
                Parallelogram P = Parallelogram(A, C, 4, 8);
                Pa.push_back(P);
                cout<<P<<endl;
                P.print();
                cout<<endl;
                cout<<"Perimeter, Area: ";
                cout<<P.perimeter()<<", "<<P.area()<<endl;
                }
            break;

            case 'T' :
            {
                Trapezoid T;
                cin>>T;
                cout<<T<<endl;
                T.print();
                cout<<endl;
                cout<<"Perimeter, Area: ";
                cout<<T.perimeter()<<", "<<T.area()<<endl;
            }
            break;

            case 't' : {
                Point A = Point(0,0);
                Point C = Point(8, 4 * sqrt(3));
                Trapezoid T = Trapezoid(A, C, 4, 8, 2);
                Tr.push_back(T);
                cout<<T<<endl;
                T.print();
                cout<<endl;
                cout<<"Perimeter, Area: ";
                cout<<T.perimeter()<<", "<<T.area()<<endl;
                }
            break;

            case 'X' :
            case 'x' :
            {
                cout<<"\n To exit the menu";
            }
            break;

            // other than mentioned selections
            default : cout<<"\n Invalid selection";
            // no break in the default case
            }

            cout<<"\n";

    } while(selection!='x' && selection!='X');
}

//creation of multiple objects
void multiple_menu()
{
    char selection;

    do {
        cout<<"\n\tFIGURES - named ABCD[i] -  HAVE TWO SIDES PARALLEL WITH Ox AXIS\n";
        cout<<"\n\t         ****LENGTHS ARE ROUNDED TO 4 DECIMALS***\n";
        cout<<"\n\tMultiple Menu";
        cout<<"\n\t========";
        cout<<"\n\tS - Create Squares";
        cout<<"\n\tR - Create Rectangles";
        cout<<"\n\tH - Create Rhombuses";
        cout<<"\n\tP - Create Parallelograms";
        cout<<"\n\tT - Create Trapezoids";
        cout<<"\n\tX - Exit\n";
        cout<<"\nEnter selection: ";

        // read the input
        cin>>selection;

        switch(selection)
        {
            case 'S' :
            case 's' : {
                int n;
                cout<<"Input the number of objects to be created: ";
                cin>>n;
                for(int i = 0; i < n; i++){
                    Square S;
                    cin>>S;
                    if(S.getValid())
                        Sq.push_back(S);
                    else continue;
                }
                Sq.shrink_to_fit();
            }
            break;

            case 'R' :
            case 'r' : {
                int n;
                cout<<"Input the number of objects to be created: ";
                cin>>n;
                for(int i = 0; i < n; i++){
                    Rectangle R;
                    cin>>R;
                    if(R.getValid())
                        Re.push_back(R);
                    else continue;
                }
                Re.shrink_to_fit();
            }
            break;

            case 'H' :
            case 'h' : {
                int n;
                cout<<"Input the number of objects to be created: ";
                cin>>n;
                for(int i = 0; i < n; i++){
                    Rhombus Ro;
                    cin>>Ro;
                    if(Ro.getValid())
                        Rho.push_back(Ro);
                    else continue;
                }
                Rho.shrink_to_fit();
            }
            break;

            case 'P' :
            case 'p' : {
                int n;
                cout<<"Input the number of objects to be created: ";
                cin>>n;
                for(int i = 0; i < n; i++){
                    Parallelogram P;
                    cin>>P;
                    if(P.getValid())
                        Pa.push_back(P);
                    else continue;
                }
                Pa.shrink_to_fit();
            }
            break;

            case 'T' :
            case 't' : {
                int n;
                cout<<"Input the number of objects to be created: ";
                cin>>n;
                for(int i = 0; i < n; i++){
                    Trapezoid T;
                    cin>>T;
                    if(T.getValid())
                        Tr.push_back(T);
                    else continue;
                }
                Tr.shrink_to_fit();
            }
            break;

            case 'X' :
            case 'x' : {
                cout<<"\n To exit the menu";
            }
            break;

            // other than mentioned selections
            default : cout<<"\n Invalid selection";
            // no break in the default case
            }

            cout<<"\n";

    } while(selection!='x' && selection!='X');
};

//display of multiple objects
void output_menu()
{
    char selection;

    do {
        cout<<"\n\tFIGURES - named ABCD[i] -  HAVE TWO SIDES PARALLEL WITH Ox AXIS\n";
        cout<<"\n\t         ****LENGTHS ARE ROUNDED TO 4 DECIMALS***\n";
        cout<<"\n\tOutput Menu";
        cout<<"\n\t========";
        cout<<"\n\tS - Display Squares";
        cout<<"\n\tR - Display Rectangles";
        cout<<"\n\tH - Display Rhombuses";
        cout<<"\n\tP - Display Parallelograms";
        cout<<"\n\tT - Display Trapezoids";
        cout<<"\n\tX - Exit\n";
        cout<<"\nEnter selection: ";

        // read the input
        cin>>selection;

        switch(selection)
        {
            case 'S' :
            case 's' : {
                if(Sq.size()) {
                    for(Square S: Sq){
                        cout<<S;
                        S.print();
                        cout<<"Perimeter, Area: ";
                        cout<<S.perimeter()<<" "<<S.area()<<endl;
                        cout<<endl;
                    }
                } else {
                    cout<<"There are no Squares to display.\n";
                }
            }
            break;

            case 'R' :
            case 'r' : {
                if(Re.size()) {
                    for(Rectangle R: Re){
                        cout<<R;
                        R.print();
                        cout<<"Perimeter, Area: ";
                        cout<<R.perimeter()<<" "<<R.area()<<endl;
                        cout<<endl;
                    }
                } else {
                    cout<<"There are no Rectangles to display.\n";
                }
            }
            break;

            case 'H' :
            case 'h' : {
                if(Rho.size()) {
                    for(Rhombus H: Rho){
                        cout<<H;
                        H.print();
                        cout<<"Perimeter, Area: ";
                        cout<<H.perimeter()<<" "<<H.area()<<endl;
                        cout<<endl;
                    }
                } else {
                    cout<<"There are no Rhombuses to display.\n";
                }
            }
            break;

            case 'P' :
            case 'p' : {
                if(Pa.size()) {
                    for(Rhombus P: Pa){
                        cout<<P;
                        P.print();
                        cout<<"Perimeter, Area: ";
                        cout<<P.perimeter()<<" "<<P.area()<<endl;
                        cout<<endl;
                    }
                } else {
                    cout<<"There are no Parallelograms to display.\n";
                }
            }
            break;

            case 'T' :
            case 't' : {
                if(Tr.size()) {
                    for(Rhombus T: Tr){
                        cout<<T;
                        T.print();
                        cout<<"Perimeter, Area: ";
                        cout<<T.perimeter()<<" "<<T.area()<<endl;
                        cout<<endl;
                    }
                } else {
                    cout<<"There are no Trapezoids to display.\n";
                }
            }
            break;

            case 'X' :
            case 'x' : {
                cout<<"\n To exit the menu";
            }
            break;

            // other than mentioned selections
            default : cout<<"\n Invalid selection";
            // no break in the default case
            }

            cout<<"\n";

    } while(selection!='x' && selection!='X');
};

//selection menu
void menu(){
    char selection;

    do {
        cout<<"\n\tFIGURES - named ABCD -  HAVE TWO SIDES PARALLEL WITH Ox AXIS\n";
        cout<<"\n\t         ****LENGTHS ARE ROUNDED TO 4 DECIMALS***\n";
        cout<<"\n\tMenu";
        cout<<"\n\t========";
        cout<<"\n\tA - Create single objects";
        cout<<"\n\tB - Create multiple objects";
        cout<<"\n\tO - Output created objects";
        cout<<"\n\tX - Exit\n";
        cout<<"\nEnter selection: ";

        // read the input
        cin>>selection;

        switch(selection)
        {
            case 'A' :
            case 'a' : {
                single_menu();
            }
            break;

            case 'B' :
            case 'b' : {
                multiple_menu();
            }
            break;

            case 'O' :
            case 'o' : {
                output_menu();
            }
            break;

            case 'X' :
            case 'x' : {
                cout<<"\n To exit the menu";
            }
            break;

            // other than C, R, I, D and X...
            default : cout<<"\n Invalid selection";
            // no break in the default case
            }

            cout<<"\n";

    } while(selection!='x' && selection!='X');

};

int main() {

    menu();

    Sq.clear();
    Sq.shrink_to_fit();

    Re.clear();
    Re.shrink_to_fit();

    Rho.clear();
    Rho.shrink_to_fit();

    Pa.clear();
    Pa.shrink_to_fit();

    Tr.clear();
    Tr.shrink_to_fit();

    return 0;
}
