cs4722::shape* new_shape = new cs4722::sphere(17, 43);
auto* part = new cs4722::part_rotating();
part->the_shape = (new_shape);
part->world_transform.translate = (glm::vec3(.7, 0, -.7));