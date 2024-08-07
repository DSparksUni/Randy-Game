void init_assets(Allocator allocator) {
    player_image = load_image_from_disk(
        fixed_string("assets/player_pgp.png"), allocator
    );
    assert(player_image, "Failed to load player image for some reason");

    sword_image = load_image_from_disk(
        fixed_string("assets/sword001_pgp.png"), allocator
    );
    assert(sword_image, "Failed to load sword image for some reason");

    tree_image = load_image_from_disk(
        fixed_string("assets/tree001_pgp.png"), allocator
    );
    assert(tree_image, "Failed to load tree image for some reason");

    enemy001_image = load_image_from_disk(
        fixed_string("assets/enemy001_pgp.png"), allocator
    );
    assert(enemy001_image, "Failed to load enemy 001's image for some reason");

    enemy002_image = load_image_from_disk(
        fixed_string("assets/enemy002_pgp.png"), allocator
    );
    assert(enemy002_image, "Failed to load enemy 002's image for some reason");

    enemy003_image = load_image_from_disk(
        fixed_string("assets/enemy003_pgp.png"), allocator
    );
    assert(enemy003_image, "Failed to load enemy 003's image for some reason");

    enemy004_image = load_image_from_disk(
        fixed_string("assets/enemy004_pgp.png"), allocator
    );
    assert(enemy004_image, "Failed to load enemy 004's image for some reason");

    enemy005_image = load_image_from_disk(
        fixed_string("assets/enemy005_pgp.png"), allocator
    );
    assert(enemy005_image, "Failed to load enemy 005's image for some reason");
}