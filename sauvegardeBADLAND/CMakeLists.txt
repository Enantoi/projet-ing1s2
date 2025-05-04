cmake_minimum_required(VERSION 3.29)
project(sauvegardeBADLAND C)

set(CMAKE_C_STANDARD 11)

add_executable(sauvegardeBADLAND main.c
        sauvegarde.c)
