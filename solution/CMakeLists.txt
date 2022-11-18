file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources} include/bmp.h include/bmp_reader.h include/bmp_writer.h include/image.h include/operations.h include/rotator.h src/bmp_reader.c src/bmp_writer.c src/image.c src/main.c src/operations.c include/rotator.h)
target_include_directories(image-transformer PRIVATE src include)
