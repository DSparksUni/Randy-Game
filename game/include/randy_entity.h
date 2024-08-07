#ifndef RANDY_ENTITY_H_INCLUDED_
#define RANDY_ENTITY_H_INCLUDED_

#define MAX_ENTITY_COUNT 1024

typedef enum EntityType_t {
    EID_NULL      = 0,
    EID_TREE      = 1,
    EID_SWORD     = 2,
    EID_PLAYER    = 3,
    EID_ENEMY_001 = 4,
    EID_ENEMY_002 = 5,
    EID_ENEMY_003 = 6,
    EID_ENEMY_004 = 7,
    EID_ENEMY_005 = 8
} EntityType;
typedef struct Entity_t {
    Vector2 pos;
    Vector2 face;
    EntityType type;
    bool valid;
    bool moving;
} Entity;
Entity* make_entity();
void destroy_entity(Entity*);
void populate_entity(Entity*, EntityType, Vector2);
#define make_tree(ent, pos) populate_entity(ent, EID_TREE, pos)
#define make_sword(ent, pos) populate_entity(ent, EID_SWORD, pos)
#define make_player(ent, pos) populate_entity(ent, EID_PLAYER, pos)
#define make_enemy001(ent, pos) populate_entity(ent, EID_ENEMY_001, pos)
#define make_enemy002(ent, pos) populate_entity(ent, EID_ENEMY_002, pos)
#define make_enemy003(ent, pos) populate_entity(ent, EID_ENEMY_003, pos)
#define make_enemy004(ent, pos) populate_entity(ent, EID_ENEMY_004, pos)
#define make_enemy005(ent, pos) populate_entity(ent, EID_ENEMY_005, pos)

typedef struct World_t {
    Entity entities[MAX_ENTITY_COUNT];
} World;

World* world;
void init_world(Allocator);

#endif