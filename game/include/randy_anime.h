#ifndef RANDY_ANIME_H_INCLUDED_
#define RANDY_ANIME_H_INCLUDED_

typedef struct Animation_t {
    int length;     // In milliseconds
    float32 elapsed;
    Entity* entity;

    void (*callback)(struct Animation_t*, float32);
    void (*destructor)(struct Animation_t*);
    
    bool active;
} Animation;

Animation create_animation(
    int, Entity*, void (*)(Animation*, float32), void (*)(Animation*)
);
void update_animation(Animation*, float32);

#endif  //RANDY_ANIME_H_INCLUDED_