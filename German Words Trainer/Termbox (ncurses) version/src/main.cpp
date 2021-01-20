#include "termbox.h"

#include <exception>
#include <stdexcept>
#include <string>
#include <iostream>

#include "text_rectangle.hpp"
#include "button.hpp"

#include "types.hpp"

namespace config
{
    namespace color {
        Color FORE_DEFAULT = TB_BLACK;
        Color BACK_DEFAULT = TB_WHITE;
        Color BUTTON_FORE_DEFAULT = TB_WHITE;
        Color BUTTON_BACK_DEFAULT = TB_RED;
        Color BUTTON_TEXT_FORE_DEFAULT = TB_MAGENTA;
        Color BUTTON_TEXT_BACK_DEFAULT = TB_GREEN;
    };

    namespace text {
        static int LEFT = 0;
        static int CENTRE = 1;
        static int RIGHT = 2;
        static int BREAK_LINE = 3;
        static int NO_BREAK_LINE = 4;
    };
}; // namespace config










struct key {
        unsigned char x;
        unsigned char y;
        uint32_t ch;
};

static const char chars_hw[] = "hello world";

#define STOP {0,0,0}
struct key DOT[] = {{1,1,'o'},STOP};
struct key K_ESC[] = {{1,1,'E'},{2,1,'S'},{3,1,'C'},STOP};
void draw_key(struct key *k, uint16_t fg, uint16_t bg, int sx, int sy)
{
        while (k->x) {
                tb_change_cell(k->x + sx, k->y + sy, k->ch, fg, bg);
                k++;
        }
}

void write_on_pose(int x, 
                   int y, 
                   const std::string &s, 
                   Color foreground = config::color::FORE_DEFAULT, 
                   Color background = config::color::BACK_DEFAULT) {
    for (int i = 0; i < s.length(); ++i)
        tb_change_cell(x + i, y, s[i], foreground, background);
}

void write_button(int x, int y, const Button &btn, 
                  Color foreground = config::color::BUTTON_FORE_DEFAULT, 
                  Color background = config::color::BUTTON_BACK_DEFAULT,
                  Color txt_foreground = config::color::BUTTON_TEXT_FORE_DEFAULT, 
                  Color txt_background = config::color::BUTTON_TEXT_BACK_DEFAULT) {
    Rectangle active = btn.active();
    TextedRectangle txt = btn.text();
    for (int i = 0; i < active.width(); ++i) {
        for (int j = 0; j < active.height(); ++j) {
            tb_change_cell(x + i, y, ' ', foreground, background);
        }
    }

    for (int i = 0; i < std::min(txt.pose().width(), (int)txt.txt().size()); ++i) {
        for (int j = 0; j < txt.pose().height(); ++j) {
            tb_change_cell(x + i, y, txt.txt()[i][j], txt_foreground, txt_background);
        }
    }
}

int main(int argv, char **argc) {
        (void)argc; (void)argv;
        int code = tb_init();
        if (code < 0) {
                fprintf(stderr, "termbox init failed, code: %d\n", code);
                return -1;
        }

        tb_select_input_mode(TB_INPUT_ESC | TB_INPUT_MOUSE);
        tb_select_output_mode(TB_OUTPUT_256);
        tb_clear();

        int j, k;
        for (k = 0; k < 5; k++) {
                j = 0;
                while(chars_hw[j] != 0) {
                        tb_change_cell(j, k, chars_hw[j], 32+j, 231-k);
                        j++;
                }
        }

        draw_key(K_ESC, TB_WHITE, TB_BLUE, 2, 4);

        tb_set_cursor(10, 11);

        tb_present();

        for (;;) {
                tb_present();
                struct tb_event ev;
                int mx = -1;
                int my = -1;
                int t = tb_poll_event(&ev);
                if (t == -1) {
                        tb_shutdown();
                        fprintf(stderr, "termbox poll event error\n");
                        return -1;
                }

                switch (t) {
                case TB_EVENT_KEY:
                        if (ev.key == TB_KEY_ESC) {
                                tb_shutdown();
                                return 0;
                        }
                        break;
                case TB_EVENT_MOUSE:
                        if (ev.key == TB_KEY_MOUSE_LEFT) {
                                mx = ev.x;
                                my = ev.y;
                                Rectangle rct{mx, my + 3, mx + 5, my};
                                TextedRectangle trct(rct, "hello, my beautiful friend");
                                Button btn(trct);

                                if((mx >= 3 && mx <= 5) && my == 5) {
                                    tb_shutdown();
                                    return 0;
                                } else {
                                    tb_set_cursor(mx, my);
                                    //write_on_pose(mx, my, "hello, mates", TB_WHITE, TB_RED);
                                    write_button(mx, my, btn);
                                }
                        }
                        break;
                }
        }
}