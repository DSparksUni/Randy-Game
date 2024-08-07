#ifndef RANDY_CONSTS_H_INCLUDED_
#define RANDY_CONSTS_H_INCLUDED_

static const float32 player_speed = 0.3f;

static const float32 coord_span_width  = 1024.f;
static const float32 coord_span_height = 576.f;
static const float32 coord_width = coord_span_width/2.f;
static const float32 coord_height = coord_span_height/2.f;

Gfx_Image* player_image;
Gfx_Image* sword_image;
Gfx_Image* tree_image;
Gfx_Image* enemy001_image;
Gfx_Image* enemy002_image;
Gfx_Image* enemy003_image;
Gfx_Image* enemy004_image;
Gfx_Image* enemy005_image;
void init_assets(Allocator);

static const float64 camera_zoom_tollerance = 3.5; 

static const float32 player_roll_distance = 200.f;
static const int player_roll_time_millis = 300;    // 0.5 seconds

#endif