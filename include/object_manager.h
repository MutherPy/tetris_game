
void object_action_manager(ObjectAction action, Object* current_obj);

Object* new_object();
void next_object(Object** current_obj);

void set_object_as_acted(Object* current_obj);
void set_object_as_unacted(Object* current_obj);