include(TranslationsMusl)
add_musl_translations_directory("musl" MUSL_LOCPATH)
add_musl_translations_catalog("musl"
    ../musl)
include(Translations)
add_translations_directory("musl-locales" "bin")
add_translations_catalog("musl-locales"
    ..)
