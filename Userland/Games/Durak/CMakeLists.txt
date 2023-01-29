serenity_component(
    Durak
    RECOMMENDED
    TARGETS Durak
)

compile_gml(Durak.gml DurakGML.h durak_gml)

set(SOURCES
    Game.cpp
    main.cpp
)

set(GENERATED_SOURCES
    DurakGML.h
)

serenity_app(Durak ICON app-spider)
target_link_libraries(Durak PRIVATE LibCards LibGUI LibGfx LibCore LibConfig LibMain)
