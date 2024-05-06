struct circle{
  double x, y, r;
  circle(double xx, double yy, double rr){
    x = xx;
    y = yy;
    r = rr;
  }

  bool in(double i, double j){
    // distance {i, j} - > {x, y}
    return r * r >= (x - i) * (x - i) + (y - j) * (y - j);
  }
};