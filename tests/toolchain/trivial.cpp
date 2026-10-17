// Phase 0 toolchain probe: one class with a virtual function.
class Shape {
public:
    Shape() : id(0) {}
    virtual int area() const { return id; }
    virtual ~Shape() {}
    int id;
};

class Square : public Shape {
public:
    int side;
    virtual int area() const;
};

int Square::area() const { return side * side + id; }

int use(Shape *s) { return s->area(); }
