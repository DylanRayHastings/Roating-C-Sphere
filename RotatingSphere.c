#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define WIDTH 80
#define HEIGHT 24

double to_radians(double degrees) {
    return degrees * M_PI / 180;
}

void clear_screen() {
    system("clear");
}

void sleep_ms(int ms) {
    struct timespec ts = {
        .tv_sec = ms / 1000,
        .tv_nsec = (ms % 1000) * 1000000
    };
    nanosleep(&ts, NULL);
}

void update_sphere(double angle, double rotation_speed) {
    int radius = 10;
    int num_points = 30;
    char sphere[HEIGHT][WIDTH];

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            sphere[i][j] = ' ';
        }
    }

    for (int u = 0; u < num_points; u++) {
        double theta = to_radians(u * 180.0 / (num_points - 1));
        for (int v = 0; v < num_points; v++) {
            double phi = to_radians(v * 360.0 / (num_points - 1));
            double x = radius * sin(theta) * cos(phi);
            double y = radius * sin(theta) * sin(phi);
            double z = radius * cos(theta);

            double x_rot = x * cos(angle * rotation_speed) - z * sin(angle * rotation_speed);
            double y_rot = y;
            double z_rot = x * sin(angle * rotation_speed) + z * cos(angle * rotation_speed);

            int x_screen = (int) (x_rot * 2 + WIDTH / 2);
            int y_screen = (int) (y_rot + HEIGHT / 2);

            if (x_screen >= 0 && x_screen < WIDTH && y_screen >= 0 && y_screen < HEIGHT) {
                sphere[y_screen][x_screen] = '#';
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", sphere[i][j]);
        }
        printf("\n");
    }
}

int main() {
    double angle = 0;
    double rotation_speed = 0.01;

    while (1) {
        clear_screen();
        update_sphere(angle, rotation_speed);
        angle += 1;
        sleep_ms(50);
    }

    return 0;
}
