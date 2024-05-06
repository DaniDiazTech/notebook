
typedef double T;
struct point{
  T x, y;

  point(){
    x = y = 0;
  }

  point(T xx, T yy){
    x = xx;
    y = yy;
  }

  point operator + (point p){
    return {x + p.x, y + p.y};
  }

  point operator * (T s){
    return {s * x, s * y};
  }

  bool operator == (point p){
    return x == p.x && y== p.y;
  }

  bool operator != (point p){
    return !(*this == p);
  }

  T dot(point p){
    return p.x * x + p.y *y;
  }
  /*
  Returns true if the line between the two points
  is not horizontal.
  */
  bool slope(point p, double &s){
    if (p.x == x){
      s = 0;
      return 0;
    }
    else{
      s = ( 1.0 * (y - p.y))  / ( 1.0 * (x - p.x));
      return 1;
    }
  }
};
