/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

/*
    Rubber Band
    An audio time-stretching and pitch-shifting library.
    Copyright 2007-2011 Chris Cannam.
    
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of the
    License, or (at your option) any later version.  See the file
    COPYING included with this distribution for more information.
*/

#ifndef _PROFILER_H_
#define _PROFILER_H_

//#define NO_TIMING 1
//#define WANT_TIMING 1
//#define PROFILE_CLOCKS 1

// Define NO_TIMING or NDEBUG to switch off profilers
#ifdef NDEBUG
#define NO_TIMING 1
#endif

// But we always allow WANT_TIMING to switch them back on again
#ifdef WANT_TIMING
#undef NO_TIMING
#endif

#ifndef NO_TIMING
#ifdef PROFILE_CLOCKS
#include <time.h>
#else
#include "system/sysutils.h"
#ifndef _WIN32
#include <sys/time.h>
#endif
#endif
#endif

#include <map>

namespace RubberBand {

#ifndef NO_TIMING

class Profiler
{
public:
    Profiler(const char *name);
    ~Profiler();

    void end(); // same action as dtor

    static void dump();

protected:
    const char* m_c;
#ifdef PROFILE_CLOCKS
    clock_t m_start;
#else
    struct timeval m_start;
#endif
    bool m_showOnDestruct;
    bool m_ended;

    typedef std::pair<int, float> TimePair;
    typedef std::map<const char *, TimePair> ProfileMap;
    typedef std::map<const char *, float> WorstCallMap;
    static ProfileMap m_profiles;
    static WorstCallMap m_worstCalls;
    static void add(const char *, float);
};

#else

#ifdef NO_TIMING_COMPLETE_NOOP

// Fastest for release builds, but annoying because it can't be linked
// with code built in debug mode (expecting non-inline functions), so
// not preferred during development

class Profiler
{
public:
    Profiler(const char *) { }
    ~Profiler() { }

    void end() { }
    static void dump() { }
};

#else

class Profiler
{
public:
    Profiler(const char *);
    ~Profiler();

    void end();
    static void dump();
};

#endif
#endif

}

#endif
