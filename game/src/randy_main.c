bool animate_to_targetf32(
	float32* value, float32 target, float64 delta_time, float32 rate
) {
	*value += (target - *value) * (1.f - pow(2.f, -rate * delta_time));
	if(fabs(*value - target) >= 0.001f) {
		*value = target;
		return true;
	}

	return false;
}
void animate_to_targetv2(
	Vector2* value, Vector2 target, float64 delta_time, float32 rate
) {
	animate_to_targetf32(&value->x, target.x, delta_time, rate);
	animate_to_targetf32(&value->y, target.y, delta_time, rate);
}

void player_roll_animation_callback(Animation*, float32);
void player_roll_animation_destructor(Animation*);

int entry(int argc, char **argv) {
	
	window.title = STR("Randy Game Time!");
	window.scaled_width = 1280; // We need to set the scaled size if we want to handle system scaling (DPI)
	window.scaled_height = 720; 
	window.x = 200;
	window.y = 90;
	window.clear_color = hex_to_rgba(0x255665FF);

	init_world(get_heap_allocator());
	init_assets(get_heap_allocator());

	// Make the player
	Entity* player = make_entity();
	make_player(player, v2(0.f, 0.f));

	Animation player_roll_animation = create_animation(
		player_roll_time_millis, player, &player_roll_animation_callback,
		&player_roll_animation_destructor
	);

	for(size_t i = 0; i < 40; i++) {
		Entity* tree = make_entity();
		
		const Vector2 pos = v2(
			get_random_float32_in_range(-coord_width, coord_width-100),
			get_random_float32_in_range(-coord_height, coord_height-100)
		);
		make_tree(tree, pos);
	}

	bool log_timer = false;

	float32 view_zoom = 1.f;
	Vector2 camera_pos = v2(0, 0);

	float64 last_time = os_get_current_time_in_seconds();
	while (!window.should_close) {
		float64 now = os_get_current_time_in_seconds();
		const float64 delta_time = (now - last_time)*1000.f;
		if ((int)now != (int)last_time)
			log_timer = true;
		if(log_timer)
			log("--FRAMRATE: %.2f FPS\t%.2fms\n", 1.0/(now-last_time), (now-last_time)*1000);
		last_time = now;

		draw_frame.projection = m4_make_orthographic_projection(
			-coord_width, coord_width, -coord_height, coord_height,
			-1, 10
		);

		// Camera Transform

		animate_to_targetv2(&camera_pos, player->pos, delta_time, 200.3f);

		draw_frame.view = m4_make_scale(v3(1.f, 1.f, 1.f));
		draw_frame.view = m4_mul(draw_frame.view, m4_make_translation(
						      v3(camera_pos.x, camera_pos.y, 0.f)
						  ));
		draw_frame.view = m4_mul(draw_frame.view, m4_make_scale(
						      v3(1.f/view_zoom, 1.f/view_zoom, 1.f)
						  ));

		reset_temporary_storage();
		

		// Draw Entities

		for(size_t i = 0; i < MAX_ENTITY_COUNT; i++) {
			Entity* en = &world->entities[i];
			if(!en->valid) continue;

			Vector2 ent_size;
			Gfx_Image* ent_sprite;
			switch(en->type) {
				case EID_PLAYER: {
					ent_size = v2(60.f, 60.f);
					ent_sprite = player_image;
				} break;

				case EID_SWORD: {
					ent_size = v2(240.f, 240.f);
					ent_sprite = sword_image;
				} break;

				case EID_TREE: {
					ent_size = v2(100.f, 100.f);
					ent_sprite = tree_image;
				} break;

				case EID_ENEMY_001: {
					ent_size = v2(80.f, 40.f);
					ent_sprite = enemy001_image;
				} break;	

				case EID_ENEMY_002: {
					ent_size = v2(90.f, 70.f);
					ent_sprite = enemy002_image;
				} break;

				case EID_ENEMY_003: {
					ent_size = v2(65.f, 65.f);
					ent_sprite = enemy003_image;
				} break;

				case EID_ENEMY_004: {
					ent_size = v2(65.f, 65.f);
					ent_sprite = enemy004_image;
				} break;

				case EID_ENEMY_005: {
					ent_size = v2(66.f, 48.f);
					ent_sprite = enemy005_image;
				} break;

				case EID_NULL:
					assert(false, "Tried to draw a non-entity for some reason");
			}

			Matrix4 xform = m4_scalar(1.f);
			xform 		  = m4_translate(xform, v3(en->pos.x, en->pos.y, 0.f));
			xform         = m4_translate(xform, v3(ent_size.x * -0.5, 0.f, 0.f));
			draw_image_xform(ent_sprite, xform, ent_size, COLOR_WHITE);
		}


		// Handle Input

		if(!player_roll_animation.active) {
			Vector2 input_axis = v2(0, 0);
			if(is_key_down('W')) input_axis.y += 1.f;
			if(is_key_down('A')) input_axis.x -= 1.f;
			if(is_key_down('S')) input_axis.y -= 1.f;
			if(is_key_down('D')) input_axis.x += 1.f;

			if(input_axis.x != 0 || input_axis.y != 0) {
				player->face = input_axis;
				player->moving = true;
			} else player->moving = false;
		}

		if(is_key_just_pressed(' ') && !player_roll_animation.active) {
			player_roll_animation.active = true;
			log("--ROLLING: Player roll animation initiated\n");
		}

		for(size_t i = 0; i < input_frame.number_of_events; i++) {
			const Input_Event event = input_frame.events[i];

			if(event.kind == INPUT_EVENT_SCROLL) {
				view_zoom += event.yscroll;

				if(event.yscroll > 0.0) {
					if(view_zoom < 0.0 || view_zoom > camera_zoom_tollerance)
						view_zoom = camera_zoom_tollerance;
				} else if(event.yscroll < 0.0) {
					if(view_zoom < 1.0 || view_zoom > camera_zoom_tollerance)
						view_zoom = 1.0;
				}
			}
		}

		// Update animations

		update_animation(&player_roll_animation, delta_time);



		// Update player

		if(!player_roll_animation.active && player->moving) player->pos = v2_add(
			player->pos, v2_mulf(player->face, player_speed*delta_time)
		);


		if(log_timer) log_timer = false;
		os_update(); 
		gfx_update();
	}

	return 0;
}

void player_roll_animation_callback(
	Animation* anim, float32 delta_time
) {
	Entity* player = anim->entity;

	const float32 speed = player_roll_distance / (float32)anim->length;
	const Vector2 velocity = v2_mulf(player->face, speed);

	player->pos = v2_add(player->pos, v2_mulf(velocity, delta_time));	
}
void player_roll_animation_destructor(Animation* anim) {
	anim->entity->face = v2(0, 0);

	log("--ROLLING: Player roll animation ended\n");
}