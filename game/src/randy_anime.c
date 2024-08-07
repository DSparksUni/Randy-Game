Animation create_animation(
    int length, Entity* entity, void (*callback)(Animation*, float32),
    void (*destructor)(Animation*)
) {
    Animation anim;
    
    anim.length = length;
    anim.elapsed = 0.f;
    anim.entity = entity;

    anim.callback = callback;
    anim.destructor = destructor;

    anim.active = false;

    return anim;
}

void update_animation(Animation* anim, float32 delta_time) {
    if(anim->active) {
        anim->callback(anim, delta_time);

        anim->elapsed += delta_time;
        if(anim->elapsed >= anim->length) {
            anim->destructor(anim);

            anim->active = false;
            anim->elapsed = 0.f;
        }
    }
}