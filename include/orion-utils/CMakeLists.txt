target_sources(
        orion-utils PUBLIC
        FILE_SET public_headers
        FILES
        allocators/linear_allocator.h
        assertion.h
        enum.h
        static_vector.h
        type.h
        uninitialized.h
)
