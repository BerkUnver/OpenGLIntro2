bool draw_button(Rect rect, char *text) {
    draw_immediate_rect(rect, (Color) {33, 43, 86, 255}); // Dark blue
    if (get_mouse_position()
    draw_immediate_rect(rec
    draw_string(
}

typedef struct {
    Rect2i rect;
    char *title; // static string pls
    
    int width;
    int height;
    
    bool can_close;
    bool open;
    
    bool movable;
    bool moving;
    Vector2i move_position;
    
    float depth;
} Panel;

int panel_depth_current = 0;
Font panel_font;

void panel_start(Panel *panel) {
    if (panel->moving) {
        panel->pos = v2i_sub(input_mouse_pos(), panel->pos);
    }

    panel->width = 0;
    panel->height = 64;
    panel_depth_current = panel->depth;
}

void panel_end(Panel *panel) {
    draw_immediate_rect((Rect) {0, 0, panel->width, 64}, COLOR_DARK_PURPLE);
    draw_text(panel->title, (Vector2i) {0, (64 + draw_text_default_font.ascent) / 2});
    
    if ((panel->open && panel->can_close) || !panel->can_close) {
        if (draw_button_texture((Rect) {panel->width - 64, 0, 64, 64}, texture_arrow_up)) {
            panel->open = false;
        }
    } else {
        if (draw_button_texture((Rect) {panel->width - 64, 0, 64, 64}, texture_arrow_down)) {
            panel->open = true;
        }
    }

    if (panel->can_close && !panel->open) {
        panel->height = 64;
    } else {
        draw_immediate_rect((Rect) {0, 64, panel->width, panel->height}, COLOR_DARK_BLUE);
        panel->height += 64;
    }
}

bool panel_button(Panel *panel) {
    bool clicked = draw_button_shrunken((Vector2i) {0, panel->height}
    draw_button((Rect) {0, panel->height, 
}
