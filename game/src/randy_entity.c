Entity* make_entity() {
    Entity* found = NULL;
    for(size_t i = 0; i < MAX_ENTITY_COUNT; i++) {
        Entity* maybe = &world->entities[i];
        if(!maybe->valid) {
            found = maybe;
            found->valid = true;
            break;
        }
    }

    assert(found, "Ran out of entities for some reason");
    return found;
}

void destroy_entity(Entity* entity) {
    memset(entity, 0, sizeof(Entity));
}

void populate_entity(Entity* entity, EntityType eid, Vector2 pos) {
    entity->type = eid;
    entity->pos = pos;
    entity->face = v2(0, 0);
    entity->moving = false;
}

void init_world(Allocator allocator) {
    world = alloc(allocator, sizeof(World));
    assert(world, "Failed to create world for some reason");

    memset(world->entities, 0, sizeof(world->entities));
}