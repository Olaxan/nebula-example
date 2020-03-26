import entities as ent
import transform as trf
import graphics as gfx
import character as char
import nmath as nm

for i in range(5):
	e = ent.create_entity()
	
	e.register_component("Transform")
	e.register_component("Graphics")
	e.register_component("Character")

	trf.set_world_transform(e, nm.Matrix44.translation(nm.Point(i * -2, 0, i * -2)))
	
	gfx.set_resource_uri(e, "mdl:Units/Unit_Footman.n3")
	gfx.set_tag(e, "Examples")
	gfx.set_visibility_type(e, 0)
	gfx.setup(e)
	
	char.set_skeleton_uri(e, "ske:Units/Unit_Footman.nsk3")
	char.set_animation_uri(e, "ani:Units/Unit_Footman.nax3")
	char.set_tag(e, "Examples")
	char.setup(e)
	char.play(e, 0, 0)