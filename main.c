#include "./raylib.h"
#include <stdio.h>
#include <math.h>
#define WIDTH 1920
#define HEIGHT 1200

#define LINE_COLS 1920/160
#define LINE_ROWS 1200/100

typedef struct {
    int x, y, w, h;
    float angle;
    Color color;
} Line;

void draw(Line* lines, size_t lines_rows, size_t lines_cols, int rectx, int recty);
void update(Line* lines, size_t lines_rows, size_t lines_cols, int mx, int my, int maxw, int maxh);
void draw_lines(Line* lines, size_t lines_rows, size_t lines_cols, int x, int y, int w, int h);

void init_lines(Line* lines, size_t lines_rows, size_t lines_cols, int w, int h, int lw, int lh);

void PrintLine(Line line);

int main(void) {
    Line lines[LINE_ROWS * LINE_COLS];
    init_lines(lines, LINE_ROWS, LINE_COLS, WIDTH, HEIGHT, 5, 30);

    InitWindow(WIDTH, HEIGHT, "raylib");
    while(!WindowShouldClose()) {
        Vector2 mp = GetMousePosition();
        printf("%f:%f\n", mp.x, mp.y);
        update(lines, LINE_ROWS, LINE_COLS, mp.x, mp.y, WIDTH, HEIGHT);
        draw(lines, LINE_ROWS, LINE_COLS,0,0);
    }

    return 0;
}

void init_lines(Line* lines, size_t lines_rows, size_t lines_cols, int w, int h, int lw, int lh) {
    int separation_x = w / (lines_cols + 1);
    int separation_y = h / (lines_rows + 1);
    for (int i = 0; i < lines_rows; i++) {
        for (int j = 0; j < lines_cols; j++) {
            int line_x = j * separation_x + separation_x;
            int line_y = i * separation_y + separation_y;
            printf("line x: %d, line y: %d\n", line_x, line_y);
            Line l = {
                .x = line_x,
                .y = line_y,
                .w = lw,
                .h = lh,
                .angle = 0,
                .color = (Color){255,255,255,255}
            };
            lines[i*lines_cols + j] = l;
            // PrintLine(lines[j*lines_cols + i]);
        }
    }
}
void update(Line* lines, size_t lines_rows, size_t lines_cols, int mx, int my, int maxw, int maxh) {
    float maxd = sqrtf(maxh* maxh + maxh * maxh);
    for (int i = 0; i < lines_rows; i++) {
        for (int j = 0; j < lines_cols; j++) {
            Line* l = &lines[i*lines_cols + j];
            float angle = atanf((float)(my - l->y) / (float)(mx - l->x));
            angle = angle / (2*M_PI) * 360 - 90 ;
            l->angle = angle;
            float d = sqrtf((float)(my - l->y)*(float)(my - l->y) + (float)(mx - l->x)*(float)(mx - l->x));
            if (d > maxd) d = maxd;
            float rgb = 255 * (1 - ((float)d / (float)maxd));
            Color c = (Color){(int)rgb, (int)rgb, (int)rgb, 255};
            l->color = c;
        }
    }
}

void draw(Line* lines, size_t lines_rows, size_t lines_cols, int rectx, int recty) {
    BeginDrawing();
    ClearBackground((Color){0,0,0,255});
    for (int i = 0; i < lines_rows; i++) {
        for (int j = 0; j < lines_cols; j++) {
            Line l = lines[i*lines_cols + j];
            /*DrawRectangle(
                l.x - l.w/2 + rectx, l.y - l.h/2+recty,
                          l.w, l.h, (Color){255,255,255,255});*/
            DrawRectanglePro(
                (Rectangle){.x = l.x, .y = l.y, .width = l.w, .height = l.h},
                (Vector2){.x = l.w/2.0f, .y = l.h/2.0f},
                l.angle,
                l.color
            );
        }
    }
    EndDrawing();
}
void PrintLine(Line line) {
    printf(
        "Line Properties:\n"
        "  Position: (%d, %d)\n"
        "  Dimensions: Width = %d, Height = %d\n"
        "  Angle: %.2f degrees\n"
        "  Color: R = %d, G = %d, B = %d, A = %d\n",
        line.x, line.y, 
        line.w, line.h, 
        line.angle, 
        line.color.r, line.color.g, line.color.b, line.color.a
    );
}

