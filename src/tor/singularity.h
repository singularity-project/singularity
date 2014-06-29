/* Copyright (c) 2014, Singularity Developers */
/* See LICENSE for licensing information */

/**
 * \file singularity.h
 * \brief Headers for singularity.cpp
 **/

#ifndef TOR_SINGULARITY_H
#define TOR_SINGULARITY_H

#ifdef __cplusplus
extern "C" {
#endif

    char const* singularity_tor_data_directory(
    );

    char const* singularity_service_directory(
    );

    int check_interrupted(
    );

    void set_initialized(
    );

    void wait_initialized(
    );

#ifdef __cplusplus
}
#endif

#endif

