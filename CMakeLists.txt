# Nebula Example

# 3.7.2 required for using FindVulkan
cmake_minimum_required(VERSION 3.7.2)

get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include(${FIPS_ROOT_DIR}/cmake/fips.cmake)

fips_setup(PROJECT nebula-sandbox)
fips_include_directories(.)

nebula_begin_app(nebula-sandbox windowed)
    
    fips_dir(code)
        fips_files(
            main.cc
			exampleapp.h
            exampleapp.cc
			entitymanager.h
			entitymanager.cc
			gameentity.h
			componentbase.h
			componentbase.cc
			componentmanager.h
			componentmanager.cc
			graphicscomponent.h
			graphicscomponent.cc
			transformcomponent.h
			transformcomponent.cc
        )

    fips_deps(application foundation render resource dynui scripting)
nebula_end_app()

fips_finish()
