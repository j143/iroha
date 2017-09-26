add_library(variant INTERFACE IMPORTED)

find_path(variant_INCLUDE_DIR variant/variant.h)
mark_as_advanced(variant_INCLUDE_DIR)

find_package(PackageHandleStandardArgs REQUIRED)
find_package_handle_standard_args(variant DEFAULT_MSG
    variant_INCLUDE_DIR
    )

if (NOT SPDLOG_FOUND)
  externalproject_add(mapbox_variant
      GIT_REPOSITORY https://github.com/mapbox/variant
      GIT_TAG f85a08622e20b74bff34381cafcb8ef8167b29d0
      CONFIGURE_COMMAND "" # remove configure step
      BUILD_COMMAND "" # remove build step
      INSTALL_COMMAND "" # remove install step
      TEST_COMMAND "" # remove test step
      UPDATE_COMMAND "" # remove update step
      )
  externalproject_get_property(mapbox_variant source_dir)
  set(variant_INCLUDE_DIR ${source_dir}/include)
  file(MAKE_DIRECTORY ${variant_INCLUDE_DIR})

  add_dependencies(variant mapbox_variant)
endif ()

set_target_properties(variant PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES ${variant_INCLUDE_DIR}
    )
