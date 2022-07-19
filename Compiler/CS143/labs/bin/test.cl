class Main {
x:Int <- 1;
y:Int <- x + 1;
  main():Int {{  x <- 1;
  y <- x + 1;
  y;
  }};

  test(p:Int):Int {{  x <- 1;
    y <- x + 1;
    y;
    }};
};

