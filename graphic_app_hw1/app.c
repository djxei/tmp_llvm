#include "sim.h"

#define TREE_DEPTH 14
#define MAIN_COLOUR 0xFFFF0000

int grad;

int get_abs(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

void draw_line(int x, int y, int a, int b) {
    y = SIM_Y_SIZE - 1 - y;
    b = SIM_Y_SIZE - 1 - b;
    int actual_colour = MAIN_COLOUR + --grad;
    int go = 1;
    if (get_abs(x - a) < get_abs(y - b)) {
        if (y > b) {
            go = -1;
        }
        for (int i = y; i != b; i += go) {
            simPutPixel((i - y) * (a - x) / (b - y) + x, i, actual_colour);
        }
    } else {
        if (x > a) {
            go = -1;
        }
        for (int i = x; i != a; i += go) {
            simPutPixel(i, (i - x) * (b - y) / (a - x) + y, actual_colour);
        }    
    }                                  
}

// turns on pi, x coo
int turn_x(int x, int y, int _, int y_right) {
    return x - y_right + y;
}

// turns on pi, y coo
int turn_y(int x, int y, int x_right, int _) {
    return y + x_right - x;
}

void draw_pythagoras_tree(int xld, int yld, int xrd, int yrd, int steps) {
    if (steps == 0) {
        return;
    }
    int xlup = turn_x(xld, yld, xrd, yrd);
    int ylup = turn_y(xld, yld, xrd, yrd);

    int xrup = turn_x(xlup, ylup, xld, yld);
    int yrup = turn_y(xlup, ylup, xld, yld);

    draw_line(xld, yld, xrd, yrd);
    draw_line(xld, yld, xlup, ylup);
    draw_line(xrup, yrup, xrd, yrd);
    draw_line(xlup, ylup, xrup, yrup);

    // builds 30 60 90 triangle vertex
    int x_star = (xlup + 3 * xrup - 7 * (yrup - ylup) / 4) / 4;
    int y_star = (ylup + 3 * yrup + 7 * (xrup - xlup) / 4) / 4;

    draw_line(xlup, ylup, x_star, y_star);
    draw_line(xrup, yrup, x_star, y_star);

    draw_pythagoras_tree(xlup, ylup, x_star, y_star, steps - 1);
    draw_pythagoras_tree(x_star, y_star, xrup, yrup, steps - 1);
}

void app() {
    int x_l = SIM_X_SIZE / 2;
    int x_r = x_l + SIM_Y_SIZE / 6;
    int y = SIM_Y_SIZE / 5;
    int steps = 0;
    int go = 1;
    while (1) {
        steps += go;
        if (steps == TREE_DEPTH || steps == 0) {
            go *= -1;
            if (steps == 0) {
                grad = simRand();
            }
        }
        for (int i = 0; i < steps; ++i)  {
            draw_pythagoras_tree(x_l, y, x_r, y, i);  
            simFlush();
        }
    }
}