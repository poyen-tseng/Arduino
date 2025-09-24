void lv() {
  if (3.7 < v) {
    //高電量
    b = 2;
  }
  if (3.2 < v && v < 3.7) {
    //中電量
    b = 1;
    low_power()
  }
  if (v < 3.2) {//低電量
    b = 0;
    no_power();
  }


}
