# Translations.cmake, CMake macros written for Marlin, feel free to re-use them

macro (add_musl_translations_directory NLS_PACKAGE LOCPATH)
    add_custom_target (musl-i18n ALL COMMENT ?Building i18n messages for C library.?)
    find_program (MSGFMT_EXECUTABLE msgfmt)
    # be sure that all languages are present
    # Using all usual languages code from https://www.gnu.org/software/gettext/manual/html_node/Language-Codes.html#Language-Codes
    # Rare language codes should be added on-demand.
    file(STRINGS LOCALES LANGUAGES_NEEDED)
#     set (LANGUAGES_NEEDED aa ab ae af ak am an ar as ast av ay az ba be bg bh bi bm bn bo br bs ca ce ch ckb co cr cs cu cv cy da de dv dz ee el en_AU en_CA en_GB eo es et eu fa ff fi fj fo fr fr_CA fy ga gd gl gn gu gv ha he hi ho hr ht hu hy hz ia id ie ig ii ik io is it iu ja jv ka kg ki kj kk kl km kn ko kr ks ku kv kw ky la lb lg li ln lo lt lu lv mg mh mi mk ml mn mo mr ms mt my na nb nd ne ng nl nn nb nr nv ny oc oj om or os pa pi pl ps pt pt_BR qu rm rn ro ru rue rw sa sc sd se sg si sk sl sm sma sn so sq sr ss st su sv sw ta te tg th ti tk tl tn to tr ts tt tw ty ug uk ur uz ve vi vo wa wo xh yi yo za zh zh_CN zh_HK zh_TW zu)
#     string (REPLACE ";" " " LINGUAS "${LANGUAGES_NEEDED}")
#     configure_file (${CMAKE_CURRENT_SOURCE_DIR}/LINGUAS.in ${CMAKE_CURRENT_BINARY_DIR}/LINGUAS)
    foreach (LANGUAGE_NEEDED ${LANGUAGES_NEEDED})
        create_po_file (${LANGUAGE_NEEDED})
    endforeach (LANGUAGE_NEEDED ${LANGUAGES_NEEDED})
    # generate .mo from .po
    file (GLOB PO_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.po)
    foreach (PO_INPUT ${PO_FILES})
        get_filename_component (PO_INPUT_BASE ${PO_INPUT} NAME_WE)
        set (MO_OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${PO_INPUT_BASE}.UTF-8)
        set (PO_COPY ${CMAKE_CURRENT_BINARY_DIR}/${PO_INPUT_BASE}.po)
        file (COPY ${PO_INPUT} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
        add_custom_command (TARGET musl-i18n COMMAND ${MSGFMT_EXECUTABLE} -o ${MO_OUTPUT} ${PO_INPUT})

        install (FILES ${MO_OUTPUT} DESTINATION
            ${LOCPATH})
    endforeach (PO_INPUT ${PO_FILES})
endmacro (add_musl_translations_directory)

macro (add_musl_translations_catalog NLS_PACKAGE)
    add_custom_target (musl-pot COMMENT ?Building translation catalog for C library.?)
    find_program (XGETTEXT_EXECUTABLE xgettext)

    set(C_SOURCE "")

    foreach(FILES_INPUT ${ARGN})
        set(BASE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${FILES_INPUT})

        file (GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/ ${BASE_DIRECTORY}/*.c)
        foreach(C_FILE ${SOURCE_FILES})
            set(C_SOURCE ${C_SOURCE} ${C_FILE})
        endforeach()
    endforeach()

    set(BASE_XGETTEXT_COMMAND
        ${XGETTEXT_EXECUTABLE} -d ${NLS_PACKAGE}
        -o ${CMAKE_CURRENT_SOURCE_DIR}/${NLS_PACKAGE}.pot
        --add-comments="/" --extract-all --from-code=UTF-8)

   set(CONTINUE_FLAG "")

    IF(NOT "${C_SOURCE}" STREQUAL "")
        add_custom_command(TARGET musl-pot WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} COMMAND ${BASE_XGETTEXT_COMMAND} ${C_SOURCE})
        set(CONTINUE_FLAG "-j")
    ENDIF()
endmacro (add_musl_translations_catalog)
