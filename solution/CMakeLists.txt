file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources} include/files_operations.h src/open_and_close_files/files_operations.c include/bmp_struct.h include/abstract_image.h src/images/abstract_image.c include/bmp_reader.h src/read_and_write/bmp_reader.c include/bmp_writer.h src/read_and_write/bmp_writer.c include/rotator.h src/image_rotation/rotator.c include/bmp_reader.h src/bmp_reader.c include/bmp_writer.h src/bmp_writer.c include/rotator.h src/rotator.c src/main.c)
target_include_directories(image-transformer PRIVATE src include)
