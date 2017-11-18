include(Translations)
include(TranslationsMusl)
add_musl_translations_directory("musl" "${MUSL_LOCPATH}")
add_musl_translations_catalog("musl"
    ../musl)
