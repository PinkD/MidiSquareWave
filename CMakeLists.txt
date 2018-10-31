cmake_minimum_required(VERSION 3.8)
project(MidiSquareWave C)

set(CMAKE_C_STANDARD 11)

add_library(MidiSquareWave
        midi_note_freq.c midi_note_freq.h
        midi_square_common.c midi_square_common.h
        midi_pre_process.c midi_pre_process.h
        midi_square_core.c midi_square_core.h
        )


include_directories(../MidiParser ../WaveParser)

add_subdirectory(../MidiParser MidiParser)
add_subdirectory(../WaveParser WaveParser)

# test
link_libraries(MidiSquareWave MidiParser WaveParser m)
add_executable(MidiSquareWave-bin demo.c)

