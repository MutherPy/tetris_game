
void filled_field_init();

us_type** manage_field(Object *current_obj);

us_type get_mesh_sum(Object* current_obj);

bool edge_d_mover_check(Object* current_obj);

bool edge_lr_movers_check(Object*, ObjectAction);

void edge_rotator_check(Object*, void (*)(Object*));
