struct point{
  double x, y;
  point(int xx, int yy){
    x = xx * 1.0;
    y = yy * 1.0;
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
      s = (y - p.x)  / (x - p.x);
      return 1;
    }
  }
};
